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

bool Validator::checkForSemantics(QueryToken& queryToken) {
    set<string> declarationSet = convertVectorToSet(queryToken.declarations->first);

    // check declarations
    bool isValid = validateDeclarations(declarationSet, queryToken.declarations->first.size(), queryToken.declarations->second);

    // Check if Select Clause synonym is part of the declarations
    isValid = isValid && declarationSet.find(queryToken.selectClauseToken) != declarationSet.end();

    // Check pattern arguments
    isValid = isValid && validatePatterns(*(queryToken.declarationTokens), *(queryToken.patternTokens));

    isValid = isValid && validateSuchThatClauses(*(queryToken.declarationTokens), *(queryToken.suchThatClauseTokens));
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

bool Validator::validateSuchThatClauses(map<string, string> declarationTokens,
                                        vector<SuchThatClauseToken> suchThatClauseTokens) {
    string relationshipCheck = "Follows|Follows*|Parent|Parent*";
    bool isValid = true;
    for (SuchThatClauseToken suchThatClauseToken : suchThatClauseTokens) {
        // Check for relationship
        bool isStatementRelationship = regex_match(suchThatClauseToken.relRef, regex(relationshipCheck));
        if (isStatementRelationship) {
            isValid = isValid && handleSuchThatStatementClause(declarationTokens, *suchThatClauseToken.arguments);
        } else {
            std::set<std::string> argSet = relationshipAndArgumentsMap.at(suchThatClauseToken.relRef);
            isValid = isValid && checkFirstArgForOtherClauses(suchThatClauseToken.arguments->first, argSet, declarationTokens);
            isValid = isValid && checkSecondArgForOtherClauses(suchThatClauseToken.arguments->first, declarationTokens);
        }
    }
    return isValid;
}

bool Validator::handleSuchThatStatementClause(map<string, string>& declarationTokens, std::pair<std::string, std::string>& arguments) {
    bool isValidFirstArg = checkSynonymForStatementClauses(declarationTokens, "(_|[0-9]+)", arguments.first);
    bool isValidSecondArg = checkSynonymForStatementClauses(declarationTokens, "(_|[0-9]+)", arguments.first);
    return isValidFirstArg && isValidSecondArg;
}

bool Validator::checkSynonymForStatementClauses(map<string, string>& declarationTokens, string reg, string synonym) {
    if (!regex_match(synonym, regex(reg))) {
        if (declarationTokens.find(synonym) == declarationTokens.end()) {
            return false;
        }
        return stmtSet.find(declarationTokens.at(synonym)) != stmtSet.end();
    }
    return true;
}

bool Validator::checkFirstArgForOtherClauses(string argument, std::set<std::string>& argSet, map<string, string>& declarationTokens) {
    if (argument == "_") {
        return false;
    }

    if (!regex_match(argument, regex("\""+ IDENT + "\""))) {
        return argSet.find(declarationTokens.at(argument)) != argSet.end();
    }

    return true;
}

bool Validator::checkSecondArgForOtherClauses(string argument, map<string, string>& declarationTokens) {
    if (!regex_match(argument, regex("(_|\""+ IDENT + "\")"))) {
        if (declarationTokens.find(argument) == declarationTokens.end()) {
            return false;
        }
        return declarationTokens.at(argument) == "variable";
    }
    return true;
}

bool Validator::validatePatterns(map<string, string> declarationTokens, std::vector<PatternToken> patternTokens) {
    for (PatternToken patternToken : patternTokens) {
        if (declarationTokens.find(patternToken.synonym) == declarationTokens.end()
        || declarationTokens.at(patternToken.synonym) != "assign") {
            return false;
        }
    }
}

set<string> Validator::convertVectorToSet(vector<string> vec) {
    set<string> s;
    for (string x : vec) {
        s.insert(x);
    }
    return s;
}
