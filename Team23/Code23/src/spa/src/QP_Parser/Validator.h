#include "Tokenizer.h"

#include <string>
#include <vector>
#include <set>
#include <map>

#ifndef SPA_VALIDATOR_H
#define SPA_VALIDATOR_H


namespace qp {
    const std::set<std::string> stmtSet({"stmt", "read", "print", "assign", "call", "while", "if"});
    const std::set<std::string> usesFirstArgSet({"assign", "print", "if", "while", "procedure", "call", "stmt"});
    const std::set<std::string> modifiesFirstArgSet({"assign", "read", "if", "while", "procedure", "call", "stmt"});
    const std::map<std::string, std::set<std::string>> relationshipAndArgumentsMap({
                                                                              {"Uses", usesFirstArgSet},
                                                                              {"Modifies", modifiesFirstArgSet},
                                                                      });
    class Validator {
    public:
        void validateQueryStructure(std::string);
        void checkForSemantics(QueryToken& queryToken);
    private:
        void validateDeclarations(std::set<std::string>, int, std::vector<std::string>);
        std::set<std::string> convertVectorToSet(std::vector<std::string>);
        void validateSuchThatClauses(std::map<std::string, std::string>, std::vector<SuchThatClauseToken>);
        void validatePatterns(std::map<std::string, std::string>, std::vector<PatternToken>);
        void handleSuchThatStatementClause(std::map<std::string, std::string>&, std::pair<std::string, std::string>&);
        void checkArgumentForStatementClauses(std::map<std::string, std::string>&, std::string, std::string);
        void checkFirstArgForOtherClauses(std::string, std::set<std::string>&, std::map<std::string, std::string>&);
        void checkSecondArgForOtherClauses(std::string, std::map<std::string, std::string>&);
        void validatePatternFirstArgument(std::map<std::string, std::string>, std::string);
        void checkArguments(std::pair<std::string, std::string>, std::map<std::string, std::string>);
        void checkSynonymIsDeclared(std::string, std::map<std::string, std::string>);
    };
}


#endif //SPA_VALIDATOR_H