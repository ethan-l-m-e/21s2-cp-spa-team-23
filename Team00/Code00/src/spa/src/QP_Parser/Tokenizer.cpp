#include "Tokenizer.h"
#include <string>
#include <regex>
#include <utility>
#include <string>
#include <vector>
#include <sstream>

using namespace qp;

std::vector<QueryToken> Tokenizer::getQueryTokens(std::vector<std::string> queries) {

    std::vector<QueryToken> resultTokens;

    // check if length of queries is non-zero
    if (queries.size() == 0) {
        return resultTokens;
    }

    // loop thru each query string to get declarations, synonym, rs, pattern
    for (std::string query : queries) {
        QueryToken queryToken = QueryToken();
        getDeclarationTokens(query, queryToken);
        // find select synonym
        std::regex re("Select [A-Za-z][A-Za-z|0-9]*");
        std::smatch match;
        std::regex_search(query, match, re);
        std::string selectString = match.str(0);
        selectString = selectString.substr(7);
        queryToken.selectClauseToken = &selectString;

        resultTokens.push_back(queryToken);
    }

     return resultTokens;
}

void Tokenizer::getDeclarationTokens(std::string pql, QueryToken& queryToken) {
    // TODO: Replace with regex
    std::stringstream ds(pql);

    queryToken.declarationTokens = new std::vector<std::string>();

    // Split declarations
    while (ds.good()) {
        std::string substring;
        getline(ds, substring, ';');
        queryToken.declarationTokens->push_back(substring);
    }

    // Remove the line that comes after declarations
    queryToken.declarationTokens->pop_back();
}
