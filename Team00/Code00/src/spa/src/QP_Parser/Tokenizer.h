#include <vector>
#include <string>

#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

namespace qp {
    class QueryToken {
    public:
        std::vector<std::string>* declarationTokens;
        std::string selectClauseToken;
        std::vector<std::string>* suchThatClauseToken;
        std::string patternToken;

        QueryToken() : declarationTokens(nullptr), selectClauseToken(""), suchThatClauseToken(nullptr), patternToken(
                "") {};

    };

    class Tokenizer {
    public:
        QueryToken getQueryToken(std::string);
        void getDeclarationTokens(std::string, QueryToken&);
        void getSelectClauseTokens(std::string&, QueryToken&);
        void getSuchThatClause(std::string&, QueryToken&);
        void getPatternClause(std::string&, QueryToken&);


    };
}

#endif //SPA_TOKENIZER_H
