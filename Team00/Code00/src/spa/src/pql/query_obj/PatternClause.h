//
// Created by リム・イーサン on 31/1/22.
//

#ifndef SPA_PATTERNCLAUSE_H
#define SPA_PATTERNCLAUSE_H

#include <vector>
#include "Clause.h"
#include "Argument.h"

enum class SynonymType { ASSIGN };

class PatternClause : public Clause {
private:
    SynonymType synonymType;
public:
    PatternClause (SynonymType synonymType, std::vector<Argument> args) : synonymType{synonymType}, Clause(args) {}

    Result evaluateClause(
            PKB* pkb,
            unordered_map<string, DesignEntity> declarations) override {
        std::string synonym = argList[0].argumentValue;
        std::string entRef = argList[1].argumentValue;
        std::string expressionSpec = argList[2].argumentValue;

        ResultType resultType = ResultType::LIST;
        vector<ResultItem> resultItems;
        vector<std::string> response;
        switch (synonymType) {
            case SynonymType::ASSIGN:
                // response = pkb->getPattern(synonym, entRef, expressionSpec);
                resultItems.reserve(response.size());
                for(auto & i : response) { resultItems.emplace_back(i); }
                return {resultType, synonym, resultItems};
            default:
                return {ResultType::EMPTY, {}};
        }
    }
};


#endif //SPA_PATTERNCLAUSE_H
