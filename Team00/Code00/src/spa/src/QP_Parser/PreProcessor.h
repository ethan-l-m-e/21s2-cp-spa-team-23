#include <string>
#include <map>
#include "Tokenizer.h"
#include "pql/query_obj/Query.h"

namespace qp {
    std::map<std::string, DesignEntity> stringToDesignEntityMap({
                                                                        {"stmt", DesignEntity::STMT},
                                                                        {"read", DesignEntity::READ},
                                                                        {"print", DesignEntity::PRINT},
                                                                        {"call", DesignEntity::CALL},
                                                                        {"while", DesignEntity::WHILE},
                                                                        {"if", DesignEntity::IF},
                                                                        {"assign", DesignEntity::ASSIGN},
                                                                        {"variable", DesignEntity::VARIABLE},
                                                                        {"constant", DesignEntity::CONSTANT},
                                                                        {"procedure", DesignEntity::PROCEDURE},
                                                        });
    class PreProcessor {
    public:
        Query getQuery(std::string);
        void getDeclarations(QueryToken&, Query&);
        void getSynonym(QueryToken&, Query&);
        void getRelationship(QueryToken&, Query&);
        Argument getArgument(std::string, std::string);
        DesignEntity getDesignEntity(std::string);
    };
}

