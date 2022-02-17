#include "Tokenizer.h"

#include <string>
#include <vector>
#include <set>
#include <map>

#ifndef SPA_VALIDATOR_H
#define SPA_VALIDATOR_H


namespace qp {
    const std::set<std::string> stmtSet({"stmt", "read", "print", "assign", "call", "while", "if"});
    const std::set<std::string> usesFirstArgSet({"assign", "print", "if", "while", "procedure", "call"});
    const std::set<std::string> modifiesFirstArgSet({"assign", "read", "if", "while", "procedure", "call"});
    const std::map<std::string, std::set<std::string>> relationshipAndArgumentsMap({
                                                                              {"Uses", usesFirstArgSet},
                                                                              {"Modifies", modifiesFirstArgSet},
                                                                      });
    class Validator {
    public:
        bool validateQueryStructure(std::string);
        bool validateDeclarations(std::set<std::string>, int, std::vector<std::string>);
        bool checkForSemantics(QueryToken& queryToken);
        std::set<std::string> convertVectorToSet(std::vector<std::string>);
        bool validateSuchThatClauses(std::map<std::string, std::string>, std::vector<SuchThatClauseToken>);
        bool validatePatterns(std::map<std::string, std::string>, std::vector<PatternToken>);
    };
}


#endif //SPA_VALIDATOR_H
