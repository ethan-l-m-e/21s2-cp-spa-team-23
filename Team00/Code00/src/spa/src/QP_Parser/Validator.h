#include <string>
#include <vector>
#include <set>
#include "Tokenizer.h"

#ifndef SPA_VALIDATOR_H
#define SPA_VALIDATOR_H


namespace qp {
    class Validator {
    public:
        bool validateQueryStructure(std::string);
//        bool validateRelationship(std::string);
//        bool validatePattern(std::string);
        bool validateDeclarations(std::set<std::string>, int, std::vector<std::string>);
        bool checkForSemantics(QueryToken& queryToken);
        std::set<std::string> convertVectorToSet(std::vector<std::string>);
    };
}


#endif //SPA_VALIDATOR_H
