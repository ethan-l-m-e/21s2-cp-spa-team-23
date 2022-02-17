#include "Validator.h"
#include "Constants.h"
#include "Tokenizer.h"
#include "Exception.h"

#include <string>
#include <regex>
#include <vector>
#include <set>

using namespace qp;

void Validator::validateQueryStructure(std::string pql) {
    std::string formatRegex = PQL_FORMAT;
    std::regex reg(formatRegex);
    bool isValid = regex_match(pql, reg);

    if (!isValid) {
        throw QPInvalidSyntacticException("Invalid Syntax");
    }
}

void Validator::checkForSemantics(QueryToken& queryToken) {
    std::set<std::string> declarationSet = convertVectorToSet(queryToken.declarations->first);

    // check declarations
    validateDeclarations(declarationSet, queryToken.declarations->first.size(), queryToken.declarations->second);

    // Check if Select Clause synonym is part of the declarations
    if (declarationSet.find(queryToken.selectClauseToken) == declarationSet.end()) {
        throw QPInvalidSemanticException("Synonym not declared");
    };

    // Check pattern arguments
    validatePatterns(*(queryToken.declarationTokens), *(queryToken.patternTokens));

    validateSuchThatClauses(*(queryToken.declarationTokens), *(queryToken.suchThatClauseTokens));
}

void Validator::validateDeclarations(std::set<std::string> declarationSet, int length, std::vector<std::string> designEntities) {
    // check duplicate declaration names
    if (declarationSet.size() != length) {
        throw QPInvalidSemanticException("Repeated declaration names");
    }

    // check duplicate design entity declarations
    std::set<std::string> designEntitySet = convertVectorToSet(designEntities);
    if (designEntitySet.size() != designEntities.size()) {
        throw QPInvalidSemanticException("Repeated declarations of same design entity");
    }
}

void Validator::validateSuchThatClauses(std::map<std::string, std::string> declarationTokens,
                                        std::vector<SuchThatClauseToken> suchThatClauseTokens) {
    std::string relationshipCheck = "Follows|Follows*|Parent|Parent*";
    for (SuchThatClauseToken suchThatClauseToken : suchThatClauseTokens) {
        // Check for relationship
        bool isStatementRelationship = regex_match(suchThatClauseToken.relRef, std::regex(relationshipCheck));
        if (isStatementRelationship) {
            handleSuchThatStatementClause(declarationTokens, *suchThatClauseToken.arguments);
        } else {
            std::set<std::string> argSet = relationshipAndArgumentsMap.at(suchThatClauseToken.relRef);
            checkFirstArgForOtherClauses(suchThatClauseToken.arguments->first, argSet, declarationTokens);
            checkSecondArgForOtherClauses(suchThatClauseToken.arguments->first, declarationTokens);
        }
    }
}

void Validator::handleSuchThatStatementClause(std::map<std::string, std::string>& declarationTokens,
                                              std::pair<std::string, std::string>& arguments) {
    checkArgumentForStatementClauses(declarationTokens, "(_|[0-9]+)", arguments.first);
    checkArgumentForStatementClauses(declarationTokens, "(_|[0-9]+)", arguments.second);
}

void Validator::checkArgumentForStatementClauses(std::map<std::string, std::string>& declarationTokens,
                                                 std::string reg, std::string argument) {
    if (!regex_match(argument, std::regex(reg))) {
        if (declarationTokens.find(argument) == declarationTokens.end() ||
        stmtSet.find(declarationTokens.at(argument)) == stmtSet.end()) {
            throw QPInvalidSemanticException("Invalid Argument");
        }
    }
}

void Validator::checkFirstArgForOtherClauses(std::string argument, std::set<std::string>& argSet,
                                             std::map<std::string, std::string>& declarationTokens) {
    if (argument == "_") {
        throw QPInvalidSemanticException("Invalid First Argument");
    }

    bool isArgumentIdent = regex_match(argument, std::regex("\""+ IDENT + "\""));
    if (!isArgumentIdent && argSet.find(declarationTokens.at(argument)) == argSet.end()) {
        throw QPInvalidSemanticException("Invalid First Argument");
    }
}

void Validator::checkSecondArgForOtherClauses(std::string argument, std::map<std::string,
                                              std::string>& declarationTokens) {
    if (!regex_match(argument, std::regex("(_|\""+ IDENT + "\")"))) {
        if (declarationTokens.find(argument) == declarationTokens.end()
        || declarationTokens.at(argument) != "variable") {
            throw QPInvalidSemanticException("Invalid Second Argument");
        }
    }
}

void Validator::validatePatterns(std::map<std::string, std::string> declarationTokens,
                                 std::vector<PatternToken> patternTokens) {
    for (PatternToken patternToken : patternTokens) {
        if (declarationTokens.find(patternToken.synonym) == declarationTokens.end()
        || declarationTokens.at(patternToken.synonym) != "assign") {
            throw QPInvalidSemanticException("Invalid Pattern");
        }
    }
}

std::set<std::string> Validator::convertVectorToSet(std::vector<std::string> vec) {
    std::set<std::string> s;
    for (std::string x : vec) {
        s.insert(x);
    }
    return s;
}
