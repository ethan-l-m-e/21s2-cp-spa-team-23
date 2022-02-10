#include "Tokenizer.h"
#include "StringFormatter.h"

#include<iostream>
#include <string>
#include <regex>
#include <utility>
#include <vector>
#include <sstream>

using namespace qp;

QueryToken Tokenizer::getQueryToken(std::string query) {

    QueryToken queryToken = QueryToken();

    // check if length of queries is non-zero
    if (query.length() == 0) {
        return queryToken;
    }

    getDeclarationTokens(query, queryToken);
    getSelectClauseTokens(query, queryToken);
    return queryToken;
}

void Tokenizer::getDeclarationTokens(std::string pql, QueryToken& queryToken) {
    // TODO: Replace with regex
    std::stringstream ds(pql);

    queryToken.declarationTokens = new std::vector<std::string>();
    int count = 0;

    // Split declarations
    while (ds.good()) {
        std::string substring;
        getline(ds, substring, ';');
        if (count != 0) {
            substring = substring.substr(1);
        }
        queryToken.declarationTokens->push_back(substring);
        count += 1;
    }

    // Remove the line that comes after declarations
    queryToken.declarationTokens->pop_back();
}

void Tokenizer::getSelectClauseTokens(std::string& pql, QueryToken& queryToken) {
    string selectLine = StringFormatter::extractSecondStringByRegex(pql, "\n");
    vector<string> tokens = StringFormatter::tokenizeByRegex(selectLine, "(Select[ ]*|[ ]+)");
    queryToken.selectClauseToken = tokens[0];
}

void Tokenizer::getSuchThatClause(std::string& pql, QueryToken& queryToken) {
    string selectLine = StringFormatter::extractSecondStringByRegex(pql, "\n");
    vector<string> backClauses = StringFormatter::tokenizeByRegex(selectLine, "(.*)such that ");
    if(regex_match(backClauses[0], std::regex("(Modifies[\\*]*|Uses[\\*]*|Follows[\\*]*|Parents[\\*]*)(.*)"))) {
        vector<string> suchThatClauses = StringFormatter::tokenizeByRegex(backClauses[0], "(\\()|(\\))|([ ]*,[ ]*)");
        cout << "such that: " << suchThatClauses[0] << "\n";
        cout << "leftArg: " << suchThatClauses[1] << "\n";
        cout << "rightArg:" << suchThatClauses[2] << "\n";
    } else {
        cout << "there is no such that clause in this query." << "\n";
    }
}

void Tokenizer::getPatternClause(std::string& pql, QueryToken& queryToken) {
    string selectLine = StringFormatter::extractSecondStringByRegex(pql, "\n");
    vector<string> backClauses = StringFormatter::tokenizeByRegex(selectLine, "(.*)pattern[ ]*");
    vector<string> pattternClause = StringFormatter::tokenizeByRegex(backClauses[0], "(a\\()|(\\))|(,)");
    cout << "LHS: " << pattternClause[0] << "\n";
    cout << "RHS: " << pattternClause[1] << "\n";
}