#include "Tokenizer.h"
#include "Constants.h"
#include "QP_Evaluator/Query/Query.h"

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
                                                                        {"Calls", RelRef::CALLS},
                                                                        {"Calls*", RelRef::CALLS_T},
                                                                        {"Affects", RelRef::AFFECTS},
                                                                        {"Affects*", RelRef::AFFECTS_T},
                                                                        {"Next", RelRef::NEXT},
                                                                        {"Next*", RelRef::NEXT_T},
                                                                });

    const std::set<std::string> argumentTypeRegex({INTEGER, "BOOLEAN", ATTR_REF, "\"" + IDENT + "\"", "_", "_(.)*_", "\"(.*)\""});
    const std::map<std::string, ArgumentType> stringToArgumentType({
        // TODO: edit boolean and attr references argument type
                                                                           {INTEGER, ArgumentType::STMT_NO},
                                                                           {"BOOLEAN", ArgumentType::EXPRESSION},
                                                                           {ATTR_REF, ArgumentType::EXPRESSION},
                                                                           {("\"" + IDENT + "\""), ArgumentType::IDENT},
                                                                           {"_", ArgumentType::UNDERSCORE},
                                                                           {"_(.)*_", ArgumentType::PARTIAL_UNDERSCORE},
                                                                           {"\"(.*)\"", ArgumentType::IDENT},
    });
    const std::map<std::string, AttrName> stringToAttrName({
                                                                   {"procName", AttrName::PROC_NAME},
                                                                   {"varName", AttrName::VAR_NAME},
                                                                   {"value", AttrName::VALUE},
                                                                   {"stmt#", AttrName::STMT_NO},
                                                                   });

    class QueryParser {
    public:
        Query getQuery(std::string);
    private:
        void getDeclarations(QueryToken&, Query&);
        void getSynonym(QueryToken&, Query&);
        void getSuchThatClauses(QueryToken&, Query&);
        void getPattern(QueryToken&, Query&);
        void getWithClauses(QueryToken&, Query&);
        Argument getArgument(std::string, std::map<std::string, std::string>);
        ArgumentType getArgumentType(std::string, std::map<std::string, std::string>);
        DesignEntity getDesignEntity(std::string);
        std::vector<Argument> getArgumentList(std::vector<std::string>, std::map<std::string, std::string>);
        RelRef getRelRefFromString(std::string, Argument, std::map<std::string, std::string>);
        std::string determineRelationshipBasedOnArg(Argument, std::string, std::map<std::string, std::string>);
        SynonymType getPatternSynonymType(std::string, std::map<std::string, std::string>);
        std::pair<std::string, AttrName> getAttrName(std::string);
    };
}

