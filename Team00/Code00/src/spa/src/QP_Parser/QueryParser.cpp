#include "QueryParser.h"
#include "Exception.h"
#include "Tokenizer.h"

#include <string>
#include <vector>
#include <utility>
#include <regex>

using namespace qp;

Query QueryParser::getQuery(std::string pql) {
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(pql);
    Query query = Query();
    getDeclarations(queryToken, query);
    getSynonym(queryToken, query);
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
        std::vector<Argument> argList = getArgumentList(argumentTokens, synonym);
        RelRef relRef = getRelRefFromString(relationship, argList[0]);

        SuchThatClause suchThatClause = SuchThatClause();
        suchThatClause.argList = argList;
        suchThatClause.relRef = relRef;
        suchThatClauses.push_back(suchThatClause);
    }
    query.setSuchThatClauses(suchThatClauses);
}

RelRef QueryParser::getRelRefFromString(std::string relationship, Argument firstArgument) {
    std::string additionalString = determineRelationshipBasedOnArg(firstArgument);
    relationship += additionalString;
    RelRef relRef = stringToRelRefMap.at(relationship);
    // TODO: Handle any exception thrown
    return relRef;
}

std::string QueryParser::determineRelationshipBasedOnArg(Argument firstArgument) {
    if (firstArgument.argumentType == ArgumentType::STMT_NO) {
        return "_S";
    } else if (firstArgument.argumentType == ArgumentType::IDENT) {
        return "_P";
    }
    return "";
};

std::vector<Argument> QueryParser::getArgumentList(std::pair<std::string, std::string> argumentTokens,
                                                   std::string synonym) {
    // Get Argument Strings from clauseToken
    std::string firstArgumentString = argumentTokens.first;
    std::string secondArgumentString = argumentTokens.second;

    // Convert strings to arguments
    Argument firstArgument = getArgument(firstArgumentString, synonym);
    Argument secondArgument = getArgument(secondArgumentString, synonym);

    // Create Argument List
    std::vector<Argument> argList = std::vector<Argument>();
    argList.push_back(firstArgument);
    argList.push_back(secondArgument);
    return argList;
}

Argument QueryParser::getArgument(std::string argumentString, std::string synonym) {
    Argument argument = Argument();
    ArgumentType argumentType = getArgumentType(argumentString, synonym);
    argument.argumentType = argumentType;
    argument.argumentValue = argumentString;
    return argument;
}

ArgumentType QueryParser::getArgumentType(std::string argumentString, std::string synonym) {
    if (argumentString == synonym) {
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
        std::vector<Argument> argList = getArgumentList(argumentTokens, queryToken.selectClauseToken);
        Argument synAssign = getArgument(patternToken.synonym, queryToken.selectClauseToken);
        argList.insert(argList.begin(), synAssign);

        PatternClause patternClause = PatternClause();
        patternClause.argList = argList;
        patternClause.synonymType = SynonymType::ASSIGN;
        patternClauses.push_back(patternClause);
    }

    query.setPatternClauses(patternClauses);
}
