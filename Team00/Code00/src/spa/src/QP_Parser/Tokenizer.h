#include <vector>
#include <string>

namespace qp {
    class QueryToken {
    public:
        std::vector<std::string>* declarationTokens;
        std::string* selectClauseToken;
        std::string* relationshipToken;
        std::string* patternToken;

        QueryToken() : declarationTokens(nullptr), selectClauseToken(nullptr), relationshipToken(nullptr), patternToken(
                nullptr) {};

    };

    class Tokenizer {
    public:
        std::vector<QueryToken> getQueryTokens(std::vector<std::string>);
        void getDeclarationTokens(std::string, QueryToken&);
        void getSelectClause(std::string&, QueryToken&);
    };
}
