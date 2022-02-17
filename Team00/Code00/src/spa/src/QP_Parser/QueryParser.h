#include "Tokenizer.h"
#include "Constants.h"
#include "pql/query_obj/Query.h"

#include <string>
#include <map>
#include <set>

namespace qp {
    const std::map<std::string, DesignEntity> stringToDesignEntityMap({
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

    const std::map<std::string, RelRef> stringToRelRefMap({
                                                                        {"Follows", RelRef::FOLLOWS},
                                                                        {"Follows*", RelRef::FOLLOWS_T},
                                                                        {"Parent", RelRef::PARENT},
                                                                        {"Parent*", RelRef::PARENT_T},
                                                                        {"Uses_S", RelRef::USES_S},
                                                                        {"Uses_P", RelRef::USES_P},
                                                                        {"Modifies_S", RelRef::MODIFIES_S},
                                                                        {"Modifies_P", RelRef::MODIFIES_P},
                                                                });

    const std::set<std::string> argumentTypeRegex({INTEGER, IDENT, "_", "_(.)*_"});
    const std::map<std::string, ArgumentType> stringToArgumentType({
                                                                           {INTEGER, ArgumentType::STMT_NO},
                                                                           {IDENT, ArgumentType::IDENT},
                                                                           {"_", ArgumentType::UNDERSCORE},
                                                                           {"_(.)*_", ArgumentType::PARTIAL_UNDERSCORE},
    });

    class QueryParser {
    public:
        Query getQuery(std::string);
    private:
        void getDeclarations(QueryToken&, Query&);
        void getSynonym(QueryToken&, Query&);
        void getSuchThatClauses(QueryToken&, Query&);
        void getPattern(QueryToken&, Query&);
        Argument getArgument(std::string, std::string);
        ArgumentType getArgumentType(std::string, std::string);
        DesignEntity getDesignEntity(std::string);
        std::vector<Argument> getArgumentList(std::pair<std::string, std::string>, std::string);
        RelRef getRelRefFromString(std::string, Argument);
        std::string determineRelationshipBasedOnArg(Argument);
    };
}

