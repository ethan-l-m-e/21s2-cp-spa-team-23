#include "QueryParser.h"
#include "Exception.h"
#include "Tokenizer.h"
#include "Validator.h"

#include <string>
#include <vector>
#include <utility>
#include <regex>

using namespace qp;

Query QueryParser::getQuery(std::string pql) {
    Tokenizer tokenizer = Tokenizer();
    Validator validator = Validator();

    validator.validateQueryStructure(pql);
    QueryToken queryToken = tokenizer.getQueryToken(pql);
    validator.checkForSemantics(queryToken);

    Query query = Query();
    getDeclarations(queryToken, query);
    getSynonym(queryToken, query);
    getSuchThatClauses(queryToken, query);
    getPattern(queryToken, query);

    return query;
};

void QueryParser::getDeclarations(QueryToken& queryToken, Query& query) {
    std::map<std::string, std::string> declarationTokens = *(queryToken.declarationTokens);
    std::vector<std::string> declarationNames = queryToken.declarations->first;
    unordered_map<std::string, DesignEntity> declarationsMap = unordered_map<std::string, DesignEntity>();

    for (std::string declarationName : declarationNames) {
        std::string designEntityString = declarationTokens.at(declarationName);
        DesignEntity designEntity = getDesignEntity(designEntityString);
        declarationsMap.insert(make_pair(declarationName, designEntity));
    }
    query.setDeclarations(declarationsMap);
}

DesignEntity QueryParser::getDesignEntity(std::string designEntityString) {
    DesignEntity designEntity = stringToDesignEntityMap.at(designEntityString);
    // TODO: catch exception if DesignEntity cannot be found
    return designEntity;
}

void QueryParser::getSynonym(QueryToken& queryToken, Query& query) {
    query.setSynonym(queryToken.selectClauseToken);
}

void QueryParser::getSuchThatClauses(QueryToken& queryToken, Query& query) {
    std::vector<SuchThatClauseToken> suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    std::vector<SuchThatClause> suchThatClauses = std::vector<SuchThatClause>();

    for (SuchThatClauseToken suchThatClauseToken : suchThatClauseTokens) {
        std::string relationship = suchThatClauseToken.relRef;
        std::pair<std::string, std::string> argumentTokens = *(suchThatClauseToken.arguments);
        std::string synonym = queryToken.selectClauseToken;
        std::vector<Argument> argList = getArgumentList(argumentTokens, *(queryToken.declarationTokens));
        RelRef relRef = getRelRefFromString(relationship, argList[0], *(queryToken.declarationTokens));

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
    } catch (std::exception e) {
        throw QPParserException("RelRef: " + relationship + " cannot be found!");
    }
}

std::string QueryParser::determineRelationshipBasedOnArg(Argument firstArgument, std::string relationship,
                                                         std::map<std::string, std::string> declarationsMap) {
    // TODO: Refactor code
    if (std::regex_match(relationship, std::regex("(Follows|Follows\\*|Parent|Parent\\*)"))) {
        return "";
    }
    if (firstArgument.argumentType == ArgumentType::STMT_NO) {
        return "_S";
    } else if (firstArgument.argumentType == ArgumentType::IDENT) {
        return "_P";
    } else if (firstArgument.argumentType == ArgumentType::SYNONYM) {
        std::string designEntity = declarationsMap.at(firstArgument.argumentValue);
        if (std::regex_match(designEntity, std::regex("(read|print|call|while|if|assign|stmt)"))) {
            return "_S";
        }
        return "_P";
    } else {
        return "_P";
    }
};

std::vector<Argument> QueryParser::getArgumentList(std::pair<std::string, std::string> argumentTokens,
                                                   std::map<std::string, std::string> declarations) {
    // Get Argument Strings from clauseToken
    std::string firstArgumentString = argumentTokens.first;
    std::string secondArgumentString = argumentTokens.second;

    // Convert strings to arguments
    Argument firstArgument = getArgument(firstArgumentString, declarations);
    Argument secondArgument = getArgument(secondArgumentString, declarations);

    // Create Argument List
    std::vector<Argument> argList = std::vector<Argument>();
    argList.push_back(firstArgument);
    argList.push_back(secondArgument);
    return argList;
}

Argument QueryParser::getArgument(std::string argumentString, std::map<std::string, std::string> declarations) {
    Argument argument = Argument();
    ArgumentType argumentType = getArgumentType(argumentString, declarations);
    argument.argumentType = argumentType;
    argument.argumentValue = argumentString;
    return argument;
}

ArgumentType QueryParser::getArgumentType(std::string argumentString, std::map<std::string, std::string> declarations) {
    if (declarations.find(argumentString) != declarations.end()) {
        return ArgumentType::SYNONYM;
    }

    for (std::string reg : argumentTypeRegex) {
        if (regex_match(argumentString, std::regex(reg))) {
            return stringToArgumentType.at(reg);
        }
    }

    throw QPParserException("Parser::getArgumentType cannot identify " + argumentString + "'");
}

void QueryParser::getPattern(QueryToken& queryToken, Query& query) {
    std::vector<PatternToken> patternTokens = *(queryToken.patternTokens);
    std::vector<PatternClause> patternClauses = std::vector<PatternClause>();

    for (PatternToken patternToken : patternTokens) {
        std::pair<std::string, std::string> argumentTokens = *(patternToken.arguments);
        std::vector<Argument> argList = getArgumentList(argumentTokens, *(queryToken.declarationTokens));
        Argument synAssign = getArgument(patternToken.synonym, *(queryToken.declarationTokens));
        argList.insert(argList.begin(), synAssign);

        PatternClause patternClause = PatternClause();
        patternClause.argList = argList;
        patternClause.synonymType = SynonymType::ASSIGN;
        patternClauses.push_back(patternClause);
    }

    query.setPatternClauses(patternClauses);
}
