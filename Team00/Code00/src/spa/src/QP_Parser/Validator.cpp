#include "Validator.h"
#include "Constants.h"
#include "Tokenizer.h"
#include "StringFormatter.h"
#include <string>
#include <regex>
#include <vector>
#include <set>

using namespace qp;

bool Validator::validateQueryStructure(std::string pql) {
    std::string formatRegex = PQL_FORMAT;
    std::regex reg(formatRegex);
    bool isValid = regex_match(pql, reg);
    return isValid;
}

//bool Validator::validateRelationship(std::string pql) {
//    std::regex relationshipReg(RELATIONSHIP_MATCH);
//    bool hasRelationship = regex_match(pql, relationshipReg);
//    if (!hasRelationship) {
//        return true;
//    }
//    std::string relationshipString = StringFormatter::tokenizeByRegex(pql, "(.*)such [ ]*that[ ]+")[0];
//    bool isValid = regex_match(relationshipString, std::regex (SUCH_THAT_CL_ARG));
//    return isValid;
//}
//
//bool Validator::validatePattern(std::string pql) {
//    std::regex patternReg(PATTERN_MATCH);
//    bool hasPattern = regex_match(pql, patternReg);
//    if (!hasPattern) {
//        return true;
//    }
//    std::string patternString = StringFormatter::tokenizeByRegex(pql, "(.*)[ ]+pattern[ ]+")[0];
//    bool isValid = regex_match(patternString, std::regex (PATTERN_CL_ARG));
//    return isValid;
//}

bool Validator::checkForSemantics(QueryToken& queryToken) {
    // TODO: need declarationNames, designEntities
    set<string> declarationSet = convertVectorToSet(*(queryToken.declarationNames));

    // check declarations
    bool isValid = validateDeclarations(declarationSet, queryToken.declarationNames->size(), *(queryToken.designEntities));

    // Check if Select Clause synonym is part of the declarations
    isValid = isValid && declarationSet.find(queryToken.selectClauseToken) != declarationSet.end();

    // Check pattern arguments
    std::regex synonymReg(SYNONYM);
    if (regex_match(queryToken.patternToken->arguments->first, synonymReg)) {
        isValid = isValid && declarationSet.find(queryToken.patternToken->arguments->first) != declarationSet.end();
    }
    isValid = isValid && declarationSet.find(queryToken.patternToken->synonym) != declarationSet.end();

    // Check synonm for such that clause arguments
    for (auto str = std::next(queryToken.suchThatClauseToken->begin()); str != queryToken.suchThatClauseToken->end(); ++str) {
        if (regex_match(*str, synonymReg)) {
            isValid = isValid && declarationSet.find(*str) != declarationSet.end();
        }
    }
    return isValid;
}

bool Validator::validateDeclarations(set<string> declarationSet, int length, vector<string> designEntities) {
    // check duplicate declaration names
    if (declarationSet.size() != length) {
        return false;
    }

    // check duplicate design entity declarations
    set<string> designEntitySet = convertVectorToSet(designEntities);
    if (designEntitySet.size() != designEntities.size()) {
        return false;
    }
    return true;
}

set<string> Validator::convertVectorToSet(vector<string> vec) {
    set<string> s;
    for (string x : vec) {
        s.insert(x);
    }
    return s;
}
