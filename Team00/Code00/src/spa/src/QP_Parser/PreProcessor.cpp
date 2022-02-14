#include "PreProcessor.h"

#include <string>
#include <vector>
#include <utility>
#include <regex>
#include "Tokenizer.h"
#include <iostream>
#include "./pql/query_obj/Query.h"
#include "./pql/query_obj/Clause.h"

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
    // TODO: throw exception if DesignEntity cannot be found
    return designEntity;
}

void PreProcessor::getSynonym(QueryToken& queryToken, Query& query) {
    query.setSynonym(queryToken.selectClauseToken);
}

void PreProcessor::getRelationship(QueryToken& queryToken, Query& query) {
    std::vector<std::string> suchThatClausesString = *(queryToken.suchThatClauseToken);
    std::string relationship = suchThatClausesString[0];
    std::string firstArgumentString = suchThatClausesString[1];
    std::string secondArgumentString = suchThatClausesString[2];
    SuchThatClause suchThatClause = SuchThatClause();
    if (relationship == "Follows") {
        suchThatClause.relRef = RelRef::FOLLOWS;
    } else if (relationship == "Follows*") {
        suchThatClause.relRef = RelRef::FOLLOWS_T;
    } else if (relationship == "Parent") {
        suchThatClause.relRef = RelRef::PARENT;
    } else if (relationship == "Parent*") {
        suchThatClause.relRef = RelRef::PARENT_T;
    }

    Argument firstArgument = getArgument(firstArgumentString, queryToken.selectClauseToken);
    Argument secondArgument = getArgument(secondArgumentString, queryToken.selectClauseToken);
    std::vector<Argument> argList = std::vector<Argument>();
    argList.push_back(firstArgument);
    argList.push_back(secondArgument);
    suchThatClause.argList = argList;
    std::vector<SuchThatClause> suchThatClauses = std::vector<SuchThatClause>();
    suchThatClauses.push_back(suchThatClause);
    query.setSuchThatClauses(suchThatClauses);
}

Argument PreProcessor::getArgument(std::string argumentString, std::string synonym) {
    Argument argument = Argument();
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
        // Throw Exception
    }

}
