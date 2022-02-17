#include "QueryParser.h"
#include "Constants.h"

#include <string>
#include <vector>
#include <utility>
#include <regex>
#include "Tokenizer.h"

using namespace qp;

Query QueryParser::getQuery(string pql) {
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
    unordered_map<string, DesignEntity> declarationsMap = unordered_map<string, DesignEntity>();

    for (string declarationName : declarationNames) {
        string designEntityString = declarationTokens.at(declarationName);
        DesignEntity designEntity = getDesignEntity(designEntityString);
        declarationsMap.insert(make_pair(declarationName, designEntity));
    }
    query.setDeclarations(declarationsMap);
}

DesignEntity QueryParser::getDesignEntity(string designEntityString) {
    DesignEntity designEntity = stringToDesignEntityMap.at(designEntityString);
    // TODO: catch exception if DesignEntity cannot be found
    return designEntity;
}

void QueryParser::getSynonym(QueryToken& queryToken, Query& query) {
    query.setSynonym(queryToken.selectClauseToken);
}

void QueryParser::getSuchThatClauses(QueryToken& queryToken, Query& query) {
    std::vector<SuchThatClauseToken> suchThatClauseTokens = *(queryToken.suchThatClauseTokens);
    vector<SuchThatClause> suchThatClauses = vector<SuchThatClause>();

    // TODO: Refactor Code
    for (SuchThatClauseToken suchThatClauseToken : suchThatClauseTokens) {
        string relationship = suchThatClauseToken.relRef;
        pair<string, string> argumentTokens = *(suchThatClauseToken.arguments);
        string synonym = queryToken.selectClauseToken;
        vector<Argument> argList = getArgumentList(argumentTokens, synonym);
        RelRef relRef = getRelRefFromString(relationship, argList[0]);

        SuchThatClause suchThatClause = SuchThatClause();
        suchThatClause.argList = argList;
        suchThatClause.relRef = relRef;
        suchThatClauses.push_back(suchThatClause);
    }
    query.setSuchThatClauses(suchThatClauses);
}

RelRef QueryParser::getRelRefFromString(string relationship, Argument firstArgument) {
    string additionalString = determineRelationshipBasedOnArg(firstArgument);
    relationship += additionalString;
    RelRef relRef = stringToRelRefMap.at(relationship);
    // TODO: Handle any exception thrown
    return relRef;
}

string QueryParser::determineRelationshipBasedOnArg(Argument firstArgument) {
    if (firstArgument.argumentType == ArgumentType::STMT_NO) {
        return "_S";
    } else if (firstArgument.argumentType == ArgumentType::IDENT) {
        return "_P";
    }
    return "";
};

vector<Argument> QueryParser::getArgumentList(pair<string, string> argumentTokens, string synonym) {
    // Get Argument Strings from clauseToken
    string firstArgumentString = argumentTokens.first;
    string secondArgumentString = argumentTokens.second;

    // Convert strings to arguments
    Argument firstArgument = getArgument(firstArgumentString, synonym);
    Argument secondArgument = getArgument(secondArgumentString, synonym);

    // Create Argument List
    vector<Argument> argList = vector<Argument>();
    argList.push_back(firstArgument);
    argList.push_back(secondArgument);
    return argList;
}

Argument QueryParser::getArgument(string argumentString, string synonym) {
    Argument argument = Argument();
    ArgumentType argumentType = getArgumentType(argumentString, synonym);
    argument.argumentType = argumentType;
    argument.argumentValue = argumentString;
    return argument;
}

ArgumentType QueryParser::getArgumentType(string argumentString, string synonym) {
    ArgumentType argumentType;
    regex stmtNo(INTEGER);
    regex ident(IDENT);
    if (argumentString == synonym) {
        argumentType = ArgumentType::SYNONYM;
    } else if (regex_match(argumentString.c_str(), stmtNo)) {
        argumentType = ArgumentType::STMT_NO;
    } else if (argumentString == "_") {
        argumentType = ArgumentType::UNDERSCORE;
    } else if (regex_match(argumentString.c_str(), ident)) {
        argumentType = ArgumentType::IDENT;
    } else {
        // TODO: Throw Exception
        throw "PreProcessor::getArgumentType cannot identify '" + argumentString + "'";
    }
    return argumentType;
}

void QueryParser::getPattern(QueryToken& queryToken, Query& query) {
    // TODO: Refactor Code
    std::vector<PatternToken> patternTokens = *(queryToken.patternTokens);
    vector<PatternClause> patternClauses = vector<PatternClause>();

    for (PatternToken patternToken : patternTokens) {
        pair<string, string> argumentTokens = *(patternToken.arguments);
        vector<Argument> argList = getArgumentList(argumentTokens, queryToken.selectClauseToken);
        Argument synAssign = getArgument(patternToken.synonym, queryToken.selectClauseToken);
        argList.insert(argList.begin(), synAssign);

        PatternClause patternClause = PatternClause();
        patternClause.argList = argList;
        patternClauses.push_back(patternClause);
    }

    query.setPatternClauses(patternClauses);
}
