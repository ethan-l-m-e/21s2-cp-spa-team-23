#include "Tokenizer.h"
#include <string>
#include <regex>
#include <utility>
#include <string>
#include <vector>

std::vector<QueryToken> Tokenizer::getQueryTokens(std::vector<std::string> queries) {
    // check if length of pql string is non-zero
    if (pql.length() == 0) {
        return nullptr;
    }

    std::vector<QueryToken> resultTokens;

    // loop thru each query string to get declarations, synonym, rs, pattern
    for (std::string query : queries) {
        QueryToken queryToken = QueryToken();
        queryToken.declarationTokens = getDeclarationTokens(query);
        // find select synonym
        std::regex re("Select [A-Za-z][A-Za-z|0-9]*");
        std::smatch match;
        std::regex_search(query.begin(), query.end(), match, re);
        std::string selectString = match.str(0);
        queryToken.selectClauseToken = selectString.substr(7);

        resultTokens.push_back(queryToken);
    }

     return resultTokens
}

std::vector<std::string> Tokenizer::getDeclarationTokens(std::string pql) {
    // TODO: Replace with regex
    std::vector<std::string> declarations;
    std::stringstream ds(pql);

    // Split declarations
    while (ds.good()) {
        std::string substring;
        getline(ds, substring, ';');
        declarations.push_back(substring);
    }

    // Remove the line that comes after declarations
    declarations.pop_back();
    return declarations;
}
