#include "Tokenizer.h"
#include "StringFormatter.h"

#include <iostream>
#include <string>
#include <regex>
#include <utility>
#include <vector>
#include <sstream>

using namespace qp;

QueryToken Tokenizer::getQueryToken(std::string query) {

    QueryToken queryToken = QueryToken();

    // check if length of query is non-zero
    if (query.length() == 0) {
        return queryToken;
    }

    getDeclarationTokens(query, queryToken);
    getSelectClauseTokens(query, queryToken);
    return queryToken;
}

void Tokenizer::getDeclarationTokens(std::string pql, QueryToken& queryToken) {
    std::string selectLine = StringFormatter::extractFrontStringByRegex(pql, "\n");
    std::vector<std::string> declarations = StringFormatter::tokenizeByRegex(selectLine, "[]*;");
    std::vector<std::string>* declarationPtr = new std::vector<std::string>();
    for (std::string declaration : declarations) {
        declarationPtr->push_back(StringFormatter::removeTrailingSpace(declaration));
    }
    queryToken.declarationTokens = declarationPtr;
}

void Tokenizer::getSelectClauseTokens(std::string& pql, QueryToken& queryToken) {
    string selectLine = StringFormatter::extractSecondStringByRegex(pql, "\n");
    vector<string> tokens = StringFormatter::tokenizeByRegex(selectLine, "(Select[ ]*|[ ]+)");
    queryToken.selectClauseToken = tokens[0];
}

void Tokenizer::getSuchThatClause(std::string& pql, QueryToken& queryToken) {
    std::string selectLine = StringFormatter::extractSecondStringByRegex(pql, "\n");
    std::vector<std::string> backClauses = StringFormatter::tokenizeByRegex(selectLine, "(.*)such that ");
    std::vector<std::string> suchThatClauses = StringFormatter::tokenizeByRegex(backClauses[0], "(\\()|(\\))|([ ]*,[ ]*)");
    cout << "such that: " << suchThatClauses[0] << "\n";
    cout << "leftArg: " << suchThatClauses[1] << "\n";
    cout << "rightArg:" << suchThatClauses[2] << "\n";
    queryToken.suchThatClauseToken = &suchThatClauses;
}

void Tokenizer::getPatternClause(std::string& pql, QueryToken& queryToken) {
    string selectLine = StringFormatter::extractSecondStringByRegex(pql, "\n");
    vector<string> backClauses = StringFormatter::tokenizeByRegex(selectLine, "(.*)pattern[ ]*");
    vector<string> pattternClause = StringFormatter::tokenizeByRegex(backClauses[0], "(\\()|(\\))|(,)");
    cout << "LHS: " << pattternClause[1] << "\n";
    cout << "RHS: " << pattternClause[2] << "\n";
}