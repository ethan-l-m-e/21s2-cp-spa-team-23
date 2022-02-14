#include "PreProcessor.h"

#include <string>
#include <vector>
#include <utility>
#include <regex>
#include "Tokenizer.h"

using namespace qp;

Query PreProcessor::getQuery(std::string pql) {
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(pql);
    Query query = Query();
    getDeclarations(queryToken, query);
    getSynonym(queryToken, query);
    return query;
};

void PreProcessor::getDeclarations(QueryToken& queryToken, Query& query) {
    vector<DeclarationToken> declarationTokens = *(queryToken.declarationTokens);
    unordered_map<string, DesignEntity> declarationsMap = unordered_map<string, DesignEntity>();

    for (DeclarationToken declarationToken : declarationTokens) {
        string designEntityString = declarationToken.designEntity;
        vector<string> synonyms = *(declarationToken.synonyms);

        DesignEntity designEntity = getDesignEntity(designEntityString);

        for (string synonym : synonyms) {
            declarationsMap.insert(std::make_pair(synonym, designEntity));
        }
    }
    query.setDeclarations(declarationsMap);
}

DesignEntity PreProcessor::getDesignEntity(string designEntityString) {
    DesignEntity designEntity = stringToDesignEntityMap.at(designEntityString);
    // TODO: catch exception if DesignEntity cannot be found
    return designEntity;
}

void PreProcessor::getSynonym(QueryToken& queryToken, Query& query) {
    query.setSynonym(queryToken.selectClauseToken);
}

void PreProcessor::getSuchThatClauses(QueryToken& queryToken, Query& query) {
    vector<string> suchThatClausesString = *(queryToken.suchThatClauseToken);
    string relationship = suchThatClausesString[0];
    pair<string, string> argumentTokens = pair<string, string>(suchThatClausesString[1], suchThatClausesString[2]);
    string synonym = queryToken.selectClauseToken;

    vector<SuchThatClause> suchThatClauses = vector<SuchThatClause>();
    vector<Argument> argList = getArgumentList(argumentTokens, synonym);
    RelRef relRef = getRelRefFromString(relationship, argList[0]);

    SuchThatClause suchThatClause = SuchThatClause();

    suchThatClause.argList = argList;
    suchThatClause.relRef = relRef;
    suchThatClauses.push_back(suchThatClause);
    query.setSuchThatClauses(suchThatClauses);
}

RelRef PreProcessor::getRelRefFromString(string relationship, Argument firstArgument) {
    string additionalString = determineRelationshipBasedOnArg(firstArgument);
    relationship += additionalString;
    RelRef relRef = stringToRelRefMap.at(relationship);
    // TODO: Handle any exception thrown
    return relRef;
}

string PreProcessor::determineRelationshipBasedOnArg(Argument firstArgument) {
    if (firstArgument.argumentType == ArgumentType::STMT_NO) {
        return "_S";
    } else if (firstArgument.argumentType == ArgumentType::IDENT) {
        return "_P";
    }
    return "";
};

vector<Argument> PreProcessor::getArgumentList(pair<string, string> argumentTokens, string synonym) {
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

Argument PreProcessor::getArgument(string argumentString, string synonym) {
    Argument argument = Argument();
    ArgumentType argumentType = getArgumentType(argumentString, synonym);
    argument.argumentType = argumentType;
    argument.argumentValue = argumentString;
    return argument;
}

ArgumentType PreProcessor::getArgumentType(string argumentString, string synonym) {
    // TODO: transfer regex to constants file
    ArgumentType argumentType;
    std::regex stmtNo("[0-9]+");
    std::regex ident("([a-z]|[A-Z])+([a-z]|[A-Z]|[0-9])*");
    if (argumentString == synonym) {
        argumentType = ArgumentType::SYNONYM;
    } else if (std::regex_match(argumentString.c_str(), stmtNo)) {
        argumentType = ArgumentType::STMT_NO;
    } else if (argumentString == "_") {
        argumentType = ArgumentType::UNDERSCORE;
    } else if (std::regex_match(argumentString.c_str(), ident)) {
        argumentType = ArgumentType::IDENT;
    } else {
        // TODO: Throw Exception
    }
    return argumentType;
}

void PreProcessor::getPattern(QueryToken& queryToken, Query& query) {
    // TODO: Add synonym to pattern clause
    PatternToken patternToken = *(queryToken.patternToken);
    pair<string, string> argumentTokens = *(patternToken.arguments);
    vector<Argument> argList = getArgumentList(argumentTokens, queryToken.selectClauseToken);

    PatternClause patternClause = PatternClause();
    patternClause.argList = argList;
    vector<PatternClause> patternClauses = vector<PatternClause>();
    patternClauses.push_back(patternClause);

    query.setPatternClauses(patternClauses);
}
