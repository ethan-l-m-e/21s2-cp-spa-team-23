#include "Validator.h"
#include "Constants.h"
#include <string>
#include <regex>

using namespace qp;

bool Validator::validateQueryStructure(std::string pql) {
    std::string formatRegex = PQL_FORMAT;
    std::regex reg(formatRegex);
    bool isValid = regex_match(pql, reg);
    return isValid;
}
