#include <vector>
#include <string>
#include <map>

#ifndef SPA_TOKENIZER_H
#define SPA_TOKENIZER_H

namespace qp {
    struct PatternToken {
    public:
        std::string synonym;
        std::vector<std::string>* arguments;

        PatternToken() : synonym(""), arguments(nullptr) {};
    };

    struct SuchThatClauseToken {
    public:
        std::string relRef;
        std::vector<std::string>* arguments;

        SuchThatClauseToken() : relRef(""), arguments(nullptr) {};
    };

    struct QueryToken {
    public:
        std::map<std::string, std::string>* declarationTokens;
        std::vector<std::string>* selectClauseTokens;
        std::vector<SuchThatClauseToken>* suchThatClauseTokens;
        std::vector<PatternToken>* patternTokens;
        std::pair<std::vector<std::string>, std::vector<std::string>>* declarations;
        std::vector<std::pair<std::string, std::string>>* withClauses;

        QueryToken() : declarationTokens(nullptr), selectClauseTokens(nullptr), suchThatClauseTokens(nullptr),
        patternTokens(nullptr), declarations(nullptr),  withClauses(nullptr) {};

    };

    class Tokenizer {
    public:
        QueryToken getQueryToken(std::string);
        void cleanQueryToken(QueryToken&);
    private:
        void getDeclarationTokens(std::string, QueryToken&);
        void getSelectClauseTokens(std::string, QueryToken&);
        void getSuchThatClauseTokens(std::string, QueryToken&);
        void getPatternClauseTokens(std::string, QueryToken&);
        void getWithClauseToken(std::string, QueryToken&);
        void splitDeclarations(std::vector<std::string>&, QueryToken&);
        SuchThatClauseToken convertStringToSuchThatClauseToken(std::string);
        PatternToken convertStringToPatternToken(std::string);
        std::vector<std::string> getSplitStringsWithRegex(std::string, std::string, std::string);
    };
}

#endif //SPA_TOKENIZER_H
