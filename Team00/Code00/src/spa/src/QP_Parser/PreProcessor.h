#include <string>
#include "Tokenizer.h"
#include "pql/query_obj/Query.h"

namespace qp {
    class PreProcessor {
    public:
        Query getQuery(std::string);
        void getDeclarations(QueryToken&, Query&);
        void getSynonym(QueryToken&, Query&);
        void getRelationship(QueryToken&, Query&);
        Argument getArgument(std::string, std::string);
    };
}

