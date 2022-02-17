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
    // TODO: Refactor Code
    string relationshipCheck = "Follows|Follows*|Parent|Parent*";
    bool isValid = true;
    for (SuchThatClauseToken suchThatClauseToken : suchThatClauseTokens) {
        // Check for rs
        bool isStatementRelationship = regex_match(suchThatClauseToken.relRef, regex(relationshipCheck));
        if (isStatementRelationship) {
            if (!regex_match(suchThatClauseToken.arguments->first, regex("(_|[0-9]+)"))) {
                if (declarationTokens.find(suchThatClauseToken.arguments->first) == declarationTokens.end()) {
                    return false;
                }
                isValid = isValid && stmtSet.find(declarationTokens.at(suchThatClauseToken.arguments->first)) != stmtSet.end();
            }

            if (!regex_match(suchThatClauseToken.arguments->second, regex("(_|[0-9]+)"))) {
                if (declarationTokens.find(suchThatClauseToken.arguments->second) == declarationTokens.end()) {
                    return false;
                }
                isValid = isValid && stmtSet.find(declarationTokens.at(suchThatClauseToken.arguments->second)) != stmtSet.end();
            }
        } else {
            std::set<std::string> argSet = relationshipAndArgumentsMap.at(suchThatClauseToken.relRef);
            if (suchThatClauseToken.arguments->first == "_") {
                return false;
            }
            if (argSet.find(suchThatClauseToken.arguments->first) == argSet.end()) {
                return false;
            }

            if (!regex_match(suchThatClauseToken.arguments->first, regex("\""+ IDENT + "\""))) {
                isValid = isValid && argSet.find(declarationTokens.at(suchThatClauseToken.arguments->first)) != argSet.end();
            }

            if (!regex_match(suchThatClauseToken.arguments->second, regex("(_|\""+ IDENT + "\")"))) {
                if (argSet.find(suchThatClauseToken.arguments->second) == argSet.end()) {
                    return false;
                }
                isValid = isValid && suchThatClauseToken.arguments->second == "variable";
            }
        }
    }
    return isValid;
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
