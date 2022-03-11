#include "QueryParser.h"
#include "Exception.h"
#include "Tokenizer.h"
#include "Validator.h"
#include "StringFormatter.h"

#include <string>
#include <vector>
#include <utility>
#include <regex>

using namespace qp;

Query QueryParser::getQuery(std::string pql) {
    Tokenizer tokenizer = Tokenizer();
    Validator validator = Validator();

    // Check for syntactic errors
    validator.validateQueryStructure(pql);
    QueryToken queryToken = tokenizer.getQueryToken(pql);
    // Check for semantic errors
    validator.checkForSemantics(queryToken);

    // Process query tokens and create query object
    Query query = Query();
    getDeclarations(queryToken, query);
    getSynonym(queryToken, query);
    getSuchThatClauses(queryToken, query);
    getPattern(queryToken, query);
    getWithClauses(queryToken, query);

    // Clean up memory
    tokenizer.cleanQueryToken(queryToken);

    return query;
};

void QueryParser::getDeclarations(QueryToken& queryToken, Query& query) {
    std::map<std::string, std::string> declarationTokens = *(queryToken.declarationTokens);
    std::vector<std::string> declarationNames = queryToken.declarations->first;
    unordered_map<std::string, DesignEntity> declarationsMap = unordered_map<std::string, DesignEntity>();

    // Create a declarations map with declaration names as keys and design entities as values
    for (std::string declarationName : declarationNames) {
        std::string designEntityString = declarationTokens.at(declarationName);
        DesignEntity designEntity = getDesignEntity(designEntityString);
        declarationsMap.insert(make_pair(declarationName, designEntity));
    }
    query.setDeclarations(declarationsMap);
}

DesignEntity QueryParser::getDesignEntity(std::string designEntityString) {
    // Find DesignEntity based on the given string
    try {
        DesignEntity designEntity = stringToDesignEntityMap.at(designEntityString);
        return designEntity;
    } catch (...) {
        throw QPParserException("design entity string cannot be found");
    }
}

void QueryParser::getSynonym(QueryToken& queryToken, Query& query) {
    vector<Argument> argList = vector<Argument>();
    for (string synonym : *(queryToken.selectClauseTokens)) {
        Argument argument = getArgument(synonym, *(queryToken.declarationTokens));
        argList.push_back(argument);
    }
    // TODO: Set synonyms in query object.
//    query.setSynonyms(*(queryToken.selectClauseTokens));
}

void QueryParser::getSuchThatClauses(QueryToken& queryToken, Query& query) {
    std::vector<SuchThatClauseToken> suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    std::vector<SuchThatClause> suchThatClauses = std::vector<SuchThatClause>();

    for (SuchThatClauseToken suchThatClauseToken : suchThatClauseTokens) {
        std::string relationship = suchThatClauseToken.relRef;
        std::vector<std::string> argumentTokens = *(suchThatClauseToken.arguments);
        std::vector<Argument> argList = getArgumentList(argumentTokens, *(queryToken.declarationTokens));
        RelRef relRef = getRelRefFromString(relationship, argList[0], *(queryToken.declarationTokens));

        // Create SuchThatClause Object
        SuchThatClause suchThatClause = SuchThatClause();
        suchThatClause.argList = argList;
        suchThatClause.relRef = relRef;
        suchThatClauses.push_back(suchThatClause);
    }
    query.setSuchThatClauses(suchThatClauses);
}

RelRef QueryParser::getRelRefFromString(std::string relationship, Argument firstArgument,
                                        std::map<std::string, std::string> declarationsMap) {
    std::string additionalString = determineRelationshipBasedOnArg(firstArgument, relationship, declarationsMap);
    relationship += additionalString;
    try {
        RelRef relRef = stringToRelRefMap.at(relationship);
        return relRef;
    } catch (...) {
        throw QPParserException("RelRef: " + relationship + " cannot be found!");
    }
}

std::string QueryParser::determineRelationshipBasedOnArg(Argument firstArgument, std::string relationship,
                                                         std::map<std::string, std::string> declarationsMap) {
    bool isVariableRelationship = std::regex_match(relationship, std::regex(VARIABLE_RS));
    if (!isVariableRelationship) {
        return "";
    }

    // Check for arguments that are not of synonym type
    if (firstArgument.argumentType == ArgumentType::STMT_NO) {
        return "_S";
    } else if (firstArgument.argumentType != ArgumentType::SYNONYM) {
        return "_P";
    }

    // Check for arguments that are of synonym type
    std::string designEntity = declarationsMap.at(firstArgument.argumentValue);
    bool isStmtDesignEntity = std::regex_match(designEntity, std::regex(STMT_DESIGN_ENTITIES));
    if (isStmtDesignEntity) {
        return "_S";
    }
    return "_P";
};

std::vector<Argument> QueryParser::getArgumentList(std::vector<std::string> argumentTokens,
                                                   std::map<std::string, std::string> declarations) {
    // Create Argument List
    std::vector<Argument> argList = std::vector<Argument>();

    for (string argumentString : argumentTokens) {
        // Convert string to arguments
        Argument argument = getArgument(argumentString, declarations);
        argList.push_back(argument);
    }

    return argList;
}

Argument QueryParser::getArgument(std::string argumentString, std::map<std::string, std::string> declarations) {
    Argument argument = Argument();
    ArgumentType argumentType = getArgumentType(argumentString, declarations);
    argument.argumentType = argumentType;
    if (argumentType == ArgumentType::IDENT) {
        // remove quotation marks from the string
        argument.argumentValue = argumentString.substr(1, argumentString.size()-2);
    } else if (argumentType == ArgumentType:: EXPRESSION) {
        // TODO: edit to include argument value for booleans and attr references
        std::pair<std::string, AttrName> argumentValue = getAttrName(argumentString);
    } else {
        argument.argumentValue = argumentString;
    }
    return argument;
}

std::pair<std::string, AttrName> QueryParser::getAttrName(std::string argValue) {
    vector<std::string> arguments = StringFormatter::tokenizeByRegex(argValue, "\\.");
    AttrName attrName = stringToAttrName.at(arguments[1]);
    return std::pair<std::string, AttrName>(arguments[0], attrName);
}

ArgumentType QueryParser::getArgumentType(std::string argumentString, std::map<std::string, std::string> declarations) {
    bool isArgumentASynonym = declarations.find(argumentString) != declarations.end();
    if (isArgumentASynonym) {
        return ArgumentType::SYNONYM;
    }

    // Find Argument Type based on regex expressions
    for (std::string reg : argumentTypeRegex) {
        bool isMatch = regex_match(argumentString, std::regex(reg));
        if (isMatch) {
            return stringToArgumentType.at(reg);
        }
    }

    throw QPParserException("Parser::getArgumentType cannot identify " + argumentString + "'");
}

void QueryParser::getPattern(QueryToken& queryToken, Query& query) {
    std::vector<PatternToken> patternTokens = *(queryToken.patternTokens);
    std::vector<PatternClause> patternClauses = std::vector<PatternClause>();

    for (PatternToken patternToken : patternTokens) {
        std::vector<std::string> arguments = *(patternToken.arguments);
        std::vector<Argument> argList = getArgumentList(arguments, *(queryToken.declarationTokens));
        Argument synAssign = getArgument(patternToken.synonym, *(queryToken.declarationTokens));
        argList.insert(argList.begin(), synAssign);

        // Create PatternClause Object
        PatternClause patternClause = PatternClause();
        patternClause.argList = argList;
        patternClause.synonymType = getPatternSynonymType(synAssign.argumentValue, *(queryToken.declarationTokens));
        patternClauses.push_back(patternClause);
    }

    query.setPatternClauses(patternClauses);
}

SynonymType QueryParser::getPatternSynonymType(std::string argumentValue, std::map<std::string, std::string> declarations) {
    if (declarations.at(argumentValue) == "assign") {
        return SynonymType::ASSIGN;
    } else if (declarations.at(argumentValue) == "if") {
        return SynonymType::IF;
    } else if (declarations.at(argumentValue) == "while") {
        return SynonymType::WHILE;
    }

    throw QPParserException("Parser::getPatternSynonymType invalid synonym type");
}

void QueryParser::getWithClauses(QueryToken& queryToken, Query& query) {
    std::vector<std::pair<std::string, std::string>> withClauseTokens = *(queryToken.withClauses);
    std::vector<WithClause> withClauses = std::vector<WithClause>();

    for (std::pair<std::string, std::string> withClauseToken : withClauseTokens) {
        std::vector<std::string> arguments = std::vector<std::string>({withClauseToken.first, withClauseToken.second});
        std::vector<Argument> argList = getArgumentList(arguments, *(queryToken.declarationTokens));

        // Create WithClause Object
        WithClause withClause = WithClause();
        withClause.argList = argList;
        withClauses.push_back(withClause);
    }

    query.setWithClauses(withClauses);
}
