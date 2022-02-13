#include "PreProcessor.h"
#include <string>
#include <vector>
#include <utility>
#include <sstream>
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
    std::vector<std::string> declarations = *(queryToken.declarationTokens);
    std::string designEntityString;
    unordered_map<string, DesignEntity> declarationsMap = unordered_map<string, DesignEntity>();

    for (std::string declaration : declarations) {
        int spaceIndex = declaration.find(' ');
        designEntityString = declaration.substr(0, spaceIndex);
        std::string synonymString = declaration.substr(spaceIndex);

        // get all synonyms
        std::stringstream ds(synonymString);
        std::vector<std::string> synonyms = std::vector<std::string>();
        while (ds.good()) {
            std::string substring;
            getline(ds, substring, ',');
            substring = substring.substr(1);
            synonyms.push_back(substring);
        }

        DesignEntity designEntity = DesignEntity::EMPTY;

        // place design entity here then add all variables later
        if (designEntityString == "stmt") {
            designEntity = DesignEntity::STMT;
        } else if (designEntityString == "read") {
            designEntity = DesignEntity::READ;
        } else if (designEntityString == "print") {
            designEntity = DesignEntity::PRINT;
        } else if (designEntityString == "call") {
            designEntity = DesignEntity::CALL;
        } else if (designEntityString == "while") {
            designEntity = DesignEntity::WHILE;
        } else if (designEntityString == "if") {
            designEntity = DesignEntity::IF;
        } else if (designEntityString == "assign") {
            designEntity = DesignEntity::ASSIGN;
        } else if (designEntityString == "variable") {
            designEntity = DesignEntity::VARIABLE;
        } else if (designEntityString == "constant") {
            designEntity = DesignEntity::CONSTANT;
        } else if (designEntityString == "procedure") {
            designEntity = DesignEntity::PROCEDURE;
        }

         for (std::string synonym : synonyms) {
             declarationsMap.insert(std::make_pair(synonym, designEntity));
         }
    }
    query.setDeclarations(declarationsMap);
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
