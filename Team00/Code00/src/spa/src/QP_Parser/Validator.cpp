#include "Validator.h"
#include "Constants.h"
#include "StringFormatter.h"
#include <string>
#include <vector>
#include <regex>

using namespace qp;

bool Validator::validateQueryStructure(std::string pql) {
    // check if string has two lines
    std::vector<std::string> lines = StringFormatter::tokenizeByRegex(pql, "\n");
    if (lines.size() != 2) {
        // TODO: throw error
    }

    // validate first line
    string reg = DECLARATION+"+";
    std::regex declarationRegex(DECLARATION+"+");
    bool result = regex_match(lines[0], declarationRegex);
    bool result2 = regex_match("variable v1", std::regex ("(stmt|read|print|call|while|if|assign|variable|constant|procedure) [A-Za-z][A-Za-z|0-9]*"));
    if (!regex_match(lines[0], declarationRegex)) {
        // TODO: throw error
    }

    // validate second line
}