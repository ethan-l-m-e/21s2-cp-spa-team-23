#include "Tokenizer.h"
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
    // find select synonym
    std::regex re("Select [A-Za-z][A-Za-z|0-9]*");
    std::smatch match;
    std::regex_search(pql.cbegin(), pql.cend(), match, re);
    std::string selectString = match[0];
    selectString = selectString.substr(7);
    queryToken.selectClauseToken = &selectString;
}
