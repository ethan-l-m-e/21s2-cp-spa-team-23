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

    // Check declarations
    validateDeclarations(declarationSet, queryToken.declarations->first.size(), queryToken.declarations->second);

    // Check if Select Clause synonym is part of the declarations
    bool isSelectClauseDeclared = declarationSet.find(queryToken.selectClauseToken) == declarationSet.end();
    if (isSelectClauseDeclared) {
        throw QPInvalidSemanticException("Synonym not declared");
    };

    // Check pattern arguments
    validatePatterns(*(queryToken.declarationTokens), *(queryToken.patternTokens));

    // Check Such That clauses
    validateSuchThatClauses(*(queryToken.declarationTokens), *(queryToken.suchThatClauseTokens));
}

void Validator::validateDeclarations(std::set<std::string> declarationSet, int length, std::vector<std::string> designEntities) {
    // check duplicate declaration names
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

        if (isStatementRelationship) {
            handleSuchThatStatementClause(declarationTokens, *suchThatClauseToken.arguments);
        } else {
            // Get set of possible first argument types
            std::set<std::string> argSet = relationshipAndArgumentsMap.at(suchThatClauseToken.relRef);

            // Check arguments
            checkFirstArgForOtherClauses(suchThatClauseToken.arguments->first, argSet, declarationTokens);
            checkSecondArgForOtherClauses(suchThatClauseToken.arguments->second, declarationTokens);
        }
    }
}

void Validator::checkArguments(std::pair<std::string, std::string> arguments,
                                           std::map<std::string, std::string> declarationTokens) {
    // Check if both arguments contain the same synonym
    bool isArgumentsSameSynonym = (std::regex_match(arguments.first, std::regex (SYNONYM))
            && arguments.first == arguments.second);
    if (isArgumentsSameSynonym) {
        throw QPInvalidSemanticException("Both arguments contain the same synonym");
    }

    // Check if the synonym is declared if the argument is a synonym
    checkSynonymIsDeclared(arguments.first, declarationTokens);
    checkSynonymIsDeclared(arguments.second, declarationTokens);

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
                                              std::pair<std::string, std::string>& arguments) {
    checkArgumentForStatementClauses(declarationTokens, "(_|[0-9]+)", arguments.first);
    checkArgumentForStatementClauses(declarationTokens, "(_|[0-9]+)", arguments.second);
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

void Validator::validatePatterns(std::map<std::string, std::string> declarationTokens,
                                 std::vector<PatternToken> patternTokens) {
    for (PatternToken patternToken : patternTokens) {
        // Check that the pattern's syn-assign and first argument do not have the same synonym and synonym is declared
        std::pair<std::string, std::string> arguments = std::make_pair(patternToken.synonym, patternToken.arguments->first);
        checkArguments(arguments, declarationTokens);

        bool isSynonymNotAnAssignment = declarationTokens.at(patternToken.synonym) != "assign";
        if (isSynonymNotAnAssignment) {
            throw QPInvalidSemanticException("Invalid Pattern");
        }

        validatePatternFirstArgument(declarationTokens, patternToken.arguments->first);
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

std::set<std::string> Validator::convertVectorToSet(std::vector<std::string> vec) {
    std::set<std::string> s;
    for (std::string x : vec) {
        s.insert(x);
    }
    return s;
}