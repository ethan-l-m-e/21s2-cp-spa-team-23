#include <string>
#include "Tokenizer.h"

namespace qp {
    class PreProcessor {
    public:
        void getQuery(std::string);
        void getDeclarations(QueryToken);
    };
}

