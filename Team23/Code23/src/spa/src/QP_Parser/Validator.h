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
    const std::set<std::string> procNameSet({"procedure", "call"});
    const std::set<std::string> varNameSet({"variable", "read", "print"});
    const std::set<std::string> valueSet({"constant"});
    const std::set<std::string> stmtNumSet({"stmt", "read", "print", "call", "while", "if", "assign"});
    const std::map<std::string, std::set<std::string>> relationshipAndArgumentsMap({
                                                                              {"Uses", usesFirstArgSet},
                                                                              {"Modifies", modifiesFirstArgSet},
                                                                      });
    const std::map<std::string, std::set<std::string>> attrNameAndSynonymMap({
                                                                                           {"procName", procNameSet},
                                                                                           {"varName", varNameSet},
                                                                                           {"value", valueSet},
                                                                                           {"stmt#", stmtNumSet},
                                                                                   });
    class Validator {
    public:
        void validateQueryStructure(std::string);
        void checkForSemantics(QueryToken& queryToken);
    private:
        // Main validate functions
        void validateSelectClauseTokens(std::set<std::string>, std::vector<std::string>, std::map<std::string, std::string>);
        void validateDeclarations(std::set<std::string>, int, std::vector<std::string>);
        void validateSuchThatClauses(std::map<std::string, std::string>, std::vector<SuchThatClauseToken>);
        void validatePatterns(std::map<std::string, std::string>, std::vector<PatternToken>);
        void validateWithClauses(std::vector<std::pair<std::string, std::string>>, std::map<std::string, std::string>);

        // Helper functions to validate arguments
        void validateSynonym(std::string, std::set<std::string>, std::map<std::string, std::string>);
        void checkArguments(std::vector<std::string>, std::map<std::string, std::string>);
        void checkSynonymIsDeclared(std::string, std::map<std::string, std::string>);

        // Helper functions to validate different such that clauses
        void handleSuchThatStatementClause(std::map<std::string, std::string>&, std::vector<std::string>);
        void handleVariableRelationshipClause(std::map<std::string, std::string>, SuchThatClauseToken);
        void handleCallsAffectsClauses(SuchThatClauseToken, std::map<std::string, std::string>);
        void checkArgumentForStatementClauses(std::map<std::string, std::string>&, std::string);
        void checkFirstArgForVariableClauses(std::string, std::set<std::string>&, std::map<std::string, std::string>&);
        void checkSecondArgForVariableClauses(std::string, std::map<std::string, std::string>&);
        void checkProcAssignArgument(std::string, std::string, std::map<std::string, std::string>);

        // Helper functions for Validating Pattern clauses
        void validatePatternFirstArgument(std::map<std::string, std::string>, std::string);
        void validateAttrRefArgument(std::string, std::map<std::string, std::string>);

        std::set<std::string> convertVectorToSet(std::vector<std::string>);
    };
}


#endif //SPA_VALIDATOR_H
