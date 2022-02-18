#include <vector>
#include <string>
#include <map>

#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

namespace qp {
    class PatternToken {
    public:
        std::string synonym;
        std::pair<std::string, std::string>* arguments;

        PatternToken() : synonym(""), arguments(nullptr) {};
    };

    class SuchThatClauseToken {
    public:
        std::string relRef;
        std::pair<std::string, std::string>* arguments;

        SuchThatClauseToken() : relRef(""), arguments(nullptr) {};
        SuchThatClauseToken(std::string relRef, std::pair<std::string, std::string> arguments) : relRef(relRef),
        arguments(&arguments) {};
    };

    class QueryToken {
    public:
        std::map<std::string, std::string>* declarationTokens;
        std::string selectClauseToken;
        std::vector<SuchThatClauseToken>* suchThatClauseTokens;
        std::vector<PatternToken>* patternTokens;
        std::pair<std::vector<std::string>, std::vector<std::string>>* declarations;

        QueryToken() : declarationTokens(nullptr), selectClauseToken(""), suchThatClauseTokens(nullptr), patternTokens(
                nullptr), declarations(nullptr) {};

    };

    class Tokenizer {
    public:
        QueryToken getQueryToken(std::string);
    private:
        void getDeclarationTokens(std::string, QueryToken&);
        void getSelectClauseTokens(std::string, QueryToken&);
        void getSuchThatClauseTokens(std::string&, QueryToken&);
        void getPatternClauseTokens(std::string, QueryToken&);
        void splitDeclarations(std::vector<std::string>&, QueryToken&);
    };
}

#endif //SPA_TOKENIZER_H
