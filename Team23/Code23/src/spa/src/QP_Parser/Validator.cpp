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
    std::regex reg(PQL_FORMAT);
    bool isValid = regex_match(pql, reg);

    if (!isValid) {
        throw QPInvalidSyntacticException("Invalid Syntax");
    }
}

void Validator::checkForSemantics(QueryToken& queryToken) {
    std::set<std::string> declarationSet = convertVectorToSet(queryToken.declarations->first);

    try {
        validateDeclarations(declarationSet, queryToken.declarations->first.size(), queryToken.declarations->second);
        validateSelectClauseTokens(declarationSet, *(queryToken.selectClauseTokens), *(queryToken.declarationTokens));
        validatePatterns(*(queryToken.declarationTokens), *(queryToken.patternTokens));
        validateSuchThatClauses(*(queryToken.declarationTokens), *(queryToken.suchThatClauseTokens));
        validateWithClauses(*(queryToken.withClauses), *(queryToken.declarationTokens));
    } catch (QPInvalidSemanticException e) {
        Tokenizer::cleanQueryToken(queryToken);
        throw e;
    }
}

void Validator::validateDeclarations(std::set<std::string> declarationSet, int length, std::vector<std::string> designEntities) {
    // Check for duplicate declaration names
    bool isDeclarationNamesDuplicate = declarationSet.size() != length;
    if (isDeclarationNamesDuplicate) {
        throw QPInvalidSemanticException("Repeated declaration names");
    }

    // Check for duplicate design entity declarations
    std::set<std::string> designEntitySet = convertVectorToSet(designEntities);
    bool isDesignEntityDeclarationsDuplicate = designEntitySet.size() != designEntities.size();
    if (isDesignEntityDeclarationsDuplicate) {
        throw QPInvalidSemanticException("Repeated declarations of same design entity");
    }
}

void Validator::validateSelectClauseTokens(std::set<std::string> declarationSet,
                                           std::vector<std::string> selectClauseTokens,
                                           std::map<std::string, std::string> declarationTokens) {
    if (selectClauseTokens[0] == "BOOLEAN") {
        return;
    }

    for (std::string selectClauseToken : selectClauseTokens) {
        validateSynonym(selectClauseToken, declarationSet, declarationTokens);
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
            handleVariableRelationshipClause(declarationTokens, suchThatClauseToken);
        } else {
            handleCallsAffectsClauses(suchThatClauseToken, declarationTokens);
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

        // Check that pattern synonym is valid
        std::string patternSynonym = declarationTokens.at(patternToken.synonym);
        bool isValidPatternSynonym = std::regex_match(patternSynonym, std::regex(PATTERN_SYNONYMS));
        bool isInvalidPatternType = (patternArguments.size() == 3) && (patternSynonym != "if");

        if (!isValidPatternSynonym || isInvalidPatternType) {
            throw QPInvalidSemanticException("Invalid Pattern Synonym");
        }

        // Check validity of if and while patterns
        bool isInvalidWhilePatternArgument = (patternSynonym == "while") && (patternArguments[1] != "_");
        bool isInvalidIfPattern = (patternSynonym == "if") && (patternArguments[1] != "_");

        if (isInvalidWhilePatternArgument || isInvalidIfPattern) {
            throw QPInvalidSemanticException("Invalid Pattern Argument");
        }

        validatePatternFirstArgument(declarationTokens, patternArguments[0]);
    }
}

void Validator::validateWithClauses(std::vector<std::pair<std::string, std::string>> withClauses,
                                    std::map<std::string, std::string> declarationTokens) {
    for (std::pair<std::string, std::string> withClause : withClauses) {
        validateAttrRefArgument(withClause.first, declarationTokens);
        validateAttrRefArgument(withClause.second, declarationTokens);
    }
}

void Validator::validateSynonym(std::string synonym, std::set<std::string> declarationSet,
                                std::map<std::string, std::string> declarationTokens) {
    // If synonym is an attribute reference, check that it's a valid reference
    bool isAttrRef = std::regex_match(synonym, std::regex(ATTR_REF));
    if (isAttrRef) {
        validateAttrRefArgument(synonym, declarationTokens);
        return;
    }

    // Otherwise, check that the synonym has been declared
    if (declarationSet.find(synonym) == declarationSet.end()) {
        throw QPInvalidSemanticException("Invalid Select Clause");
    }
}

void Validator::checkArguments(std::vector<std::string> arguments,
                               std::map<std::string, std::string> declarationTokens) {
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
    checkArgumentForStatementClauses(declarationTokens, arguments[0]);
    checkArgumentForStatementClauses(declarationTokens, arguments[1]);
}

void Validator::handleVariableRelationshipClause(std::map<std::string, std::string> declarationTokens,
                                                 SuchThatClauseToken suchThatClauseToken) {
    // Get set of possible first argument types
    std::set<std::string> argSet = relationshipAndArgumentsMap.at(suchThatClauseToken.relRef);
    std::vector<std::string> arguments = *(suchThatClauseToken.arguments);

    checkFirstArgForVariableClauses(arguments[0], argSet, declarationTokens);
    checkSecondArgForVariableClauses(arguments[1], declarationTokens);
}

void Validator::handleCallsAffectsClauses(SuchThatClauseToken suchThatClauseToken, std::map<std::string, std::string> declarationTokens) {
    std::vector<std::string> arguments = *suchThatClauseToken.arguments;
    checkProcAssignArgument(arguments[0], suchThatClauseToken.relRef, declarationTokens);
    checkProcAssignArgument(arguments[1], suchThatClauseToken.relRef, declarationTokens);
}

void Validator::checkArgumentForStatementClauses(std::map<std::string, std::string>& declarationTokens, std::string argument) {
    // If argument is an ident or integer, then it's valid
    if (regex_match(argument, std::regex((INT_WILDCARD)))) {
        return;
    }
    // Check that if the argument is a synonym, that it is a statement synonym and is declared
    bool isArgumentDeclaredWithIncorrectSynonym = stmtSet.find(declarationTokens.at(argument)) == stmtSet.end();
    if (isArgumentDeclaredWithIncorrectSynonym) {
        throw QPInvalidSemanticException("Invalid Argument");
    }
}

void Validator::checkFirstArgForVariableClauses(std::string argument, std::set<std::string>& argSet,
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

void Validator::checkSecondArgForVariableClauses(std::string argument, std::map<std::string,
                                              std::string>& declarationTokens) {
    // If the argument is a synonym, check that it's a declared variable
    bool isArgumentSynonym = std::regex_match(argument, std::regex(SYNONYM));
    bool isSynonymArgumentNotVariable = isArgumentSynonym && declarationTokens.at(argument) != "variable";
    if (isSynonymArgumentNotVariable) {
        throw QPInvalidSemanticException("Invalid Second Argument");
    }
}

void Validator::checkProcAssignArgument(std::string argument, std::string relRef,
                                         std::map<std::string, std::string> declarationTokens) {
    bool isSynonym = std::regex_match(argument, std::regex(SYNONYM));
    if (!isSynonym) {
        return;
    }

    std::string synonymType = declarationTokens.at(argument);
    bool isCallsRelationship = std::regex_match(relRef, std::regex(CALLS_RS));

    // Checking validity of Calls argument
    bool isSynonymProcedure = synonymType == "procedure";
    bool isValidCallsArgument = (isCallsRelationship && !isSynonymProcedure);

    // Checking validity of Affects argument
    bool isSynonymAssign = synonymType == "assign";
    bool isValidAffectsArgument = (!isCallsRelationship && !isSynonymAssign);

    if (isValidCallsArgument || isValidAffectsArgument) {
        throw QPInvalidSemanticException("Invalid Argument");
    }
}

void Validator::validatePatternFirstArgument(std::map<std::string, std::string> declarationTokens, std::string argument) {
    bool isArgumentSynonym = std::regex_match(argument, std::regex(SYNONYM));
    bool isSynonymArgumentNotVariable = isArgumentSynonym && declarationTokens.at(argument) != "variable";

    if (isSynonymArgumentNotVariable) {
        throw QPInvalidSemanticException("Invalid Pattern First Argument");
    }
}

void Validator::validateAttrRefArgument(std::string argument, std::map<std::string, std::string> declarationTokens) {
    // If argument is an ident or integer, then it's valid
    bool isArgumentIdentOrInt = std::regex_match(argument, std::regex(IDENT_INT_CHECK));
    if (isArgumentIdentOrInt) {
        return;
    }

    std::vector<std::string> attrs = StringFormatter::tokenizeByRegex(argument, "\\.");
    bool isValidSynonym = declarationTokens.find(attrs[0]) != declarationTokens.end();

    std::set<std::string> expectedSynonymSet = attrNameAndSynonymMap.at(attrs[1]);
    bool isInvalidSynonymForRef = !isValidSynonym || expectedSynonymSet.find(declarationTokens.at(attrs[0])) == expectedSynonymSet.end();

    if (isInvalidSynonymForRef) {
        throw QPInvalidSemanticException("Invalid ATTR REF");
    }
}

std::set<std::string> Validator::convertVectorToSet(std::vector<std::string> vec) {
    std::set<std::string> s;
    for (std::string x : vec) {
        s.insert(x);
    }
    return s;
}
