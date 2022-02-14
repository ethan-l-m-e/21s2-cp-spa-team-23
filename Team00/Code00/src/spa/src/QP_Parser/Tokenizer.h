#include <vector>
#include <string>

#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

namespace qp {
    class DeclarationToken {
    public:
        std::string designEntity;
        std::vector<std::string>* synonyms;

        DeclarationToken() : designEntity(""), synonyms(nullptr) {};
    };

    class PatternToken {
    public:
        std::string synonym;
        std::pair<std::string, std::string>* arguments;

        PatternToken() : synonym(""), arguments(nullptr) {};
    };

    class QueryToken {
    public:
        std::vector<DeclarationToken>* declarationTokens;
        std::string selectClauseToken;
        std::vector<std::string>* suchThatClauseToken;
        PatternToken* patternToken;

        QueryToken() : declarationTokens(nullptr), selectClauseToken(""), suchThatClauseToken(nullptr), patternToken(
                "") {};

    };

    class Tokenizer {
    public:
        QueryToken getQueryToken(std::string);
        void getDeclarationTokens(std::string, QueryToken&);
        void getSelectClauseTokens(std::string&, QueryToken&);
        void getSuchThatClauseTokens(std::string&, QueryToken&);
        void getPatternClause(std::string&, QueryToken&);
        std::vector<DeclarationToken>* splitDeclarations(std::vector<std::string>&);

    };
}

#endif //SPA_TOKENIZER_H
