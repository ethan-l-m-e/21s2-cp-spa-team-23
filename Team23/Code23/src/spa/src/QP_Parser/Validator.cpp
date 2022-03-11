#include "Validator.h"
#include "Constants.h"
#include "Tokenizer.h"
#include "Exception.h"
#include "StringFormatter.h"

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

    // Check declarations
    validateDeclarations(declarationSet, queryToken.declarations->first.size(), queryToken.declarations->second);

    // Check if Select Clause synonyms are part of the declarations
    validateSelectClauseTokens(declarationSet, *(queryToken.selectClauseTokens), *(queryToken.declarationTokens));

    // Check pattern arguments
    validatePatterns(*(queryToken.declarationTokens), *(queryToken.patternTokens));

    // Check Such That clauses
    validateSuchThatClauses(*(queryToken.declarationTokens), *(queryToken.suchThatClauseTokens));

    // Check with clauses
    validateWithClauses(*(queryToken.withClauses), *(queryToken.declarationTokens));
}

void Validator::validateSelectClauseTokens(std::set<std::string> declarationSet,
                                           std::vector<std::string> selectClauseTokens,
                                           std::map<std::string, std::string> declarationTokens) {
    // If select clause is a boolean, then it is valid
    if (selectClauseTokens[0] == "BOOLEAN") {
        return;
    }

    // Otherwise, the select clause is a tuple of elements or single element
    // Check the validity of each element
    for (std::string selectClauseToken : selectClauseTokens) {
        validateSynonym(selectClauseToken, declarationSet, declarationTokens);
    }
}

void Validator::validateSynonym(std::string synonym, std::set<std::string> declarationSet,
                                std::map<std::string, std::string> declarationTokens) {
    // If synonym is an attribute reference, check that it's a valid reference
    bool isAttrRef = std::regex_match(synonym, std::regex(ATTR_REF));
    if (isAttrRef) {
        validateAttrRefArgument(synonym, declarationTokens);
    }

    // Otherwise, check that the synonym has been declared
    if (declarationSet.find(synonym) == declarationSet.end()) {
        throw QPInvalidSemanticException("Invalid Select Clause");
    }
}

void Validator::validateDeclarations(std::set<std::string> declarationSet, int length, std::vector<std::string> designEntities) {
    // Check for duplicate declaration names
    bool isDeclarationNamesDuplicate = declarationSet.size() != length;
    if (isDeclarationNamesDuplicate) {
        throw QPInvalidSemanticException("Repeated declaration names");
    }

    // check duplicate design entity declarations
    std::set<std::string> designEntitySet = convertVectorToSet(designEntities);
    bool isDesignEntityDeclarationsDuplicate = designEntitySet.size() != designEntities.size();
    if (isDesignEntityDeclarationsDuplicate) {
        throw QPInvalidSemanticException("Repeated declarations of same design entity");
    }
}

void Validator::validateSuchThatClauses(std::map<std::string, std::string> declarationTokens,
                                        std::vector<SuchThatClauseToken> suchThatClauseTokens) {
    for (SuchThatClauseToken suchThatClauseToken : suchThatClauseTokens) {
        checkArguments(*(suchThatClauseToken.arguments), declarationTokens);
        // Check for type of relationship
        bool isStatementRelationship = regex_match(suchThatClauseToken.relRef, std::regex(STMT_RS));
        bool isVariableRelationship = regex_match(suchThatClauseToken.relRef, std::regex(VARIABLE_RS));

        if (isStatementRelationship) {
            handleSuchThatStatementClause(declarationTokens, *suchThatClauseToken.arguments);
        } else if (isVariableRelationship) {
            // Get set of possible first argument types
            std::set<std::string> argSet = relationshipAndArgumentsMap.at(suchThatClauseToken.relRef);
            std::vector<std::string> arguments = *(suchThatClauseToken.arguments);

            // Check arguments
            checkFirstArgForOtherClauses(arguments[0], argSet, declarationTokens);
            checkSecondArgForOtherClauses(arguments[1], declarationTokens);
        } else {
            checkProcAssignArguments(suchThatClauseToken, declarationTokens);
        }
    }
}

void Validator::checkArguments(std::vector<std::string> arguments,
                                           std::map<std::string, std::string> declarationTokens) {
    // Check if both arguments contain the same synonym
    bool isArgumentsSameSynonym = (std::regex_match(arguments[0], std::regex (SYNONYM))
            && arguments[0] == arguments[1]);
    if (isArgumentsSameSynonym) {
        throw QPInvalidSemanticException("Both arguments contain the same synonym");
    }

    // Check if the synonym is declared if the argument is a synonym
    checkSynonymIsDeclared(arguments[0], declarationTokens);
    checkSynonymIsDeclared(arguments[1], declarationTokens);

}

void Validator::checkSynonymIsDeclared(std::string argument,
                                           std::map<std::string, std::string> declarationTokens) {
    // If argument is a synonym, check that the synonym is declared
    bool isSynonymArgumentNotDeclared = (std::regex_match(argument, std::regex (SYNONYM))
            && declarationTokens.find(argument) == declarationTokens.end());
    if (isSynonymArgumentNotDeclared) {
        throw QPInvalidSemanticException("Argument synonym is not declared!");
    }
}

void Validator::handleSuchThatStatementClause(std::map<std::string, std::string>& declarationTokens,
                                              std::vector<std::string> arguments) {
    checkArgumentForStatementClauses(declarationTokens, "(_|[0-9]+)", arguments[0]);
    checkArgumentForStatementClauses(declarationTokens, "(_|[0-9]+)", arguments[1]);
}

void Validator::checkArgumentForStatementClauses(std::map<std::string, std::string>& declarationTokens,
                                                 std::string reg, std::string argument) {
    if (regex_match(argument, std::regex(reg))) {
        return;
    }
    // Check that if the argument is a synonym, that it is a statement synonym and is declared
    bool isArgumentDeclaredWithIncorrectSynonym = (declarationTokens.find(argument) == declarationTokens.end()
                                                 || stmtSet.find(declarationTokens.at(argument)) == stmtSet.end());
    if (isArgumentDeclaredWithIncorrectSynonym) {
        throw QPInvalidSemanticException("Invalid Argument");
    }
}

void Validator::checkFirstArgForOtherClauses(std::string argument, std::set<std::string>& argSet,
                                             std::map<std::string, std::string>& declarationTokens) {
    // If argument is wildcard, throw semantic exception
    bool isWildcard = argument == "_";
    if (isWildcard) {
        throw QPInvalidSemanticException("Invalid First Argument");
    }

    // If argument is a synonym but is not declared, throw semantic exception
    bool isArgumentIdent = regex_match(argument, std::regex(IDENT_INT_CHECK));
    bool isSynonymArgumentNotInDeclarations = !isArgumentIdent &&
            argSet.find(declarationTokens.at(argument)) == argSet.end();
    if (isSynonymArgumentNotInDeclarations) {
        throw QPInvalidSemanticException("Invalid First Argument");
    }
}

void Validator::checkSecondArgForOtherClauses(std::string argument, std::map<std::string,
                                              std::string>& declarationTokens) {
    // If the argument is a synonym, check that it's a declared variable
    bool isArgumentSynonym = std::regex_match(argument, std::regex(SYNONYM));
    bool isSynonymArgumentNotADeclaredVariable = (declarationTokens.find(argument) == declarationTokens.end()
                                              || declarationTokens.at(argument) != "variable");
    if (isArgumentSynonym && isSynonymArgumentNotADeclaredVariable) {
        throw QPInvalidSemanticException("Invalid Second Argument");
    }
}

void Validator::checkProcAssignArguments(SuchThatClauseToken suchThatClauseToken, std::map<std::string, std::string> declarationTokens) {
    std::vector<std::string> arguments = *suchThatClauseToken.arguments;
    if (std::regex_match(arguments[0], std::regex(SYNONYM))) {
        if (std::regex_match(suchThatClauseToken.relRef, std::regex("(Calls|Calls\\*)"))) {
            if (declarationTokens.at(arguments[0]) != "procedure") {
                throw QPInvalidSemanticException("Invalid First Argument");
            }
        } else {
            if (declarationTokens.at(arguments[0]) != "assign") {
                throw QPInvalidSemanticException("Invalid First Argument");
            }
        }
    }

    if (std::regex_match(arguments[1], std::regex(SYNONYM))) {
        if (std::regex_match(suchThatClauseToken.relRef, std::regex("(Calls|Calls\\*)"))) {
            if (declarationTokens.at(arguments[1]) != "procedure") {
                throw QPInvalidSemanticException("Invalid Second Argument");
            }
        } else {
            if (declarationTokens.at(arguments[1]) != "assign") {
                throw QPInvalidSemanticException("Invalid Second Argument");
            }
        }
    }
}

void Validator::validatePatterns(std::map<std::string, std::string> declarationTokens,
                                 std::vector<PatternToken> patternTokens) {
    for (PatternToken patternToken : patternTokens) {
        // Check that the pattern's syn-assign and first argument do not have the same synonym and synonym is declared
        std::vector<std::string> patternArguments = *patternToken.arguments;
        std::vector<std::string> arguments = std::vector<std::string>({patternToken.synonym, patternArguments[0]});
        checkArguments(arguments, declarationTokens);

        if (declarationTokens.at(patternToken.synonym) == "if") {
            if (patternArguments[1] != "_" || patternArguments[2] != "_") {
                throw QPInvalidSemanticException("Invalid Pattern Argument");
            }
        } else if (declarationTokens.at(patternToken.synonym) == "while") {
            if (patternArguments[1] != "_") {
                throw QPInvalidSemanticException("Invalid Pattern Argument");
            }
        } else if (declarationTokens.at(patternToken.synonym) != "assign") {
            throw QPInvalidSemanticException("Invalid Pattern Synonym");
        }

        validatePatternFirstArgument(declarationTokens, patternArguments[0]);
    }
}

void Validator::validatePatternFirstArgument(std::map<std::string, std::string> declarationTokens, std::string argument) {
    // Check that the pattern's first argument is a declared variable if it's a synonym
    bool isArgumentSynonym = std::regex_match(argument, std::regex(SYNONYM));
    bool isSynonymArgumentNotADeclaredVariable = isArgumentSynonym &&
            (declarationTokens.find(argument) ==  declarationTokens.end() || declarationTokens.at(argument) != "variable");

    if (isSynonymArgumentNotADeclaredVariable) {
        throw QPInvalidSemanticException("Invalid Pattern First Argument");
    }
}

void Validator::validateWithClauses(std::vector<std::pair<std::string, std::string>> withClauses, std::map<std::string, std::string> declarationTokens) {
    for (std::pair<std::string, std::string> withClause : withClauses) {
        validateAttrRefArgument(withClause.first, declarationTokens);
        validateAttrRefArgument(withClause.second, declarationTokens);
    }
}

void Validator::validateAttrRefArgument(std::string argument, std::map<std::string, std::string> declarationTokens) {
    if (std::regex_match(argument, std::regex(IDENT_INT_CHECK))) {
        return;
    }

    std::vector<std::string> attrs = StringFormatter::tokenizeByRegex(argument, "\\.");
    if (declarationTokens.find(attrs[0]) == declarationTokens.end()) {
        throw QPInvalidSemanticException("Invalid With Clause");
    }

    std::set<std::string> expectedSynonymSet = attrNameAndSynonymMap.at(attrs[1]);
    if (expectedSynonymSet.find(declarationTokens.at(attrs[0])) == expectedSynonymSet.end()) {
        throw QPInvalidSemanticException("Invalid With Clause");
    }
}

std::set<std::string> Validator::convertVectorToSet(std::vector<std::string> vec) {
    std::set<std::string> s;
    for (std::string x : vec) {
        s.insert(x);
    }
    return s;
}
