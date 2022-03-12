#include "Tokenizer.h"
#include "StringFormatter.h"
#include "Constants.h"

#include <string>
#include <utility>
#include <vector>
#include <map>
#include <regex>
#include <sstream>
#include <iostream>

using namespace qp;

QueryToken Tokenizer::getQueryToken(std::string query) {
    QueryToken queryToken = QueryToken();

    // check if length of query is non-zero
    if (query.length() == 0) {
        return queryToken;
    }

    // Replace all newlines in the query
    query = std::regex_replace(query, regex("\n"), "");

    // Gets all the different tokens
    getDeclarationTokens(query, queryToken);
    getSelectClauseTokens(query, queryToken);
    getSuchThatClauseTokens(query, queryToken);
    getPatternClauseTokens(query, queryToken);
    getWithClauseToken(query, queryToken);

    return queryToken;
}

void Tokenizer::getDeclarationTokens(std::string pql, QueryToken& queryToken) {
    std::string allDeclarationsOnly = StringFormatter::tokenizeByRegex(pql, DECLARATIONS_LINE)[0];
    // Separates declarations by design entities
    std::vector<std::string> declarationsToken = StringFormatter::tokenizeByRegex(allDeclarationsOnly, SPLIT_DESIGN_ENTITIES);
    splitDeclarations(declarationsToken, queryToken);
}

void Tokenizer::splitDeclarations(std::vector<std::string>& declarations, QueryToken& queryToken) {
    auto declarationsMap = new std::map<std::string, std::string>();
    std::string designEntity, synonymsString, declarationString;
    std::vector<std::string> declarationNames = std::vector<std::string>();
    std::vector<std::string> designEntities = std::vector<std::string>();

    for (std::string declaration : declarations) {
        std::vector<std::string> declarationArgs = StringFormatter::tokenizeByRegex(declaration, SPACE_OR_COMMA);
        designEntity = declarationArgs[0];
        // Add declarations of same design entity to the tokens
        for (int i = 1; i < declarationArgs.size(); i++) {
            std::string synonym = declarationArgs[i];
            declarationNames.push_back(synonym);
            declarationsMap->insert({synonym, designEntity});
        }
        designEntities.push_back(designEntity);
    }
    queryToken.declarationTokens = declarationsMap;
    queryToken.declarations = new std::pair<std::vector<std::string>,
            std::vector<std::string>>(declarationNames, designEntities);
}

void Tokenizer::getSelectClauseTokens(std::string pql, QueryToken& queryToken) {
    // Get Select Synonym string
    std::smatch sm;
    std::regex_search (pql, sm, std::regex(SPLIT_SELECT_SYNONYM + RESULT_CL));
    std::string synonym = sm[0];
    // Remove Select from Select clause
    synonym = synonym.substr(6);

    // Split Select Synonym string into a list of synonyms
    std::string synonyms = std::regex_replace(synonym, std::regex(SELECT_SPACE_ANGLE_BRACKETS), "");
    std::vector<std::string> synonymStrings = StringFormatter::tokenizeByRegex(synonyms, ",");

    std::vector<std::string>* selectClauseTokens = new std::vector<std::string>();
    selectClauseTokens->insert(selectClauseTokens->end(), synonymStrings.begin(), synonymStrings.end());

    queryToken.selectClauseTokens = selectClauseTokens;
}

void Tokenizer::getSuchThatClauseTokens(std::string pql, QueryToken& queryToken) {
    std::smatch sm;
    std::vector<std::string> suchThatClauses = std::vector<std::string>();

    // Get each such that clause substring
    while (std::regex_search (pql, sm, std::regex(REL_REF))) {
        std::string x = sm[0];
        x = StringFormatter::removeTrailingSpace(x);
        suchThatClauses.push_back(x);
        pql = sm.suffix().str();
    }

    // Convert each such that clause substring to SuchThatClauseToken
    std::vector<SuchThatClauseToken>* suchThatClauseTokens = new std::vector<SuchThatClauseToken>();
    for (std::string suchThatClause : suchThatClauses) {
        SuchThatClauseToken suchThatClauseToken = convertStringToSuchThatClauseToken(suchThatClause);
        suchThatClauseTokens->push_back(suchThatClauseToken);
    }

    queryToken.suchThatClauseTokens = suchThatClauseTokens;
}

SuchThatClauseToken Tokenizer::convertStringToSuchThatClauseToken(std::string suchThatClause) {
    std::vector<std::string> suchThatClauseArgs = StringFormatter::tokenizeByRegex(suchThatClause, SPLIT_SUCH_THAT_CLAUSE);

    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    suchThatClauseToken.relRef = suchThatClauseArgs[0];
    suchThatClauseToken.arguments = new std::vector<std::string>(suchThatClauseArgs.begin()+1, suchThatClauseArgs.end());
    return suchThatClauseToken;
}


void Tokenizer::getPatternClauseTokens(std::string pql, QueryToken& queryToken) {
    std::smatch sm;
    std::vector<std::string> patternClauses = std::vector<std::string>();

    // Get each pattern substring from pql query
    while (std::regex_search (pql, sm, std::regex(FIND_PATTERN))) {
        std::string x = sm[0];
        x = StringFormatter::removeTrailingSpace(x);
        patternClauses.push_back(x);
        pql = sm.suffix().str();
    }

    // Convert each pattern clause substring to PatternToken
    std::vector<PatternToken>* patternTokens = new std::vector<PatternToken>();
    for (std::string patternClause : patternClauses) {
        PatternToken patternToken = convertStringToPatternToken(patternClause);
        patternTokens->push_back(patternToken);
    }

    queryToken.patternTokens = patternTokens;
}

PatternToken Tokenizer::convertStringToPatternToken(std::string patternClause) {
    // Remove 'pattern' in substring
    patternClause = patternClause.substr(7);
    std::vector<std::string> patternClauseArgs = StringFormatter::tokenizeByRegex(patternClause, PATTERN_ARGUMENTS);

    // Split pattern synonym substring and first argument
    int indexOfOpeningBracket = patternClauseArgs[0].find("(");
    std::string synonym = StringFormatter::removeTrailingSpace(patternClauseArgs[0].substr(0, indexOfOpeningBracket));
    std::string firstArgument = StringFormatter::removeTrailingSpace(patternClauseArgs[0].substr(indexOfOpeningBracket+1));

    PatternToken patternToken = PatternToken();
    patternToken.synonym = synonym;
    patternToken.arguments = new std::vector<std::string>({firstArgument});

    // Get other pattern argument substrings
    for (int i = 1; i < patternClauseArgs.size(); i++) {
        std::string argument = StringFormatter::removeTrailingSpace(patternClauseArgs[i]);
        if (i == patternClauseArgs.size()-1) {
            argument = argument.substr(0, argument.size()-1);
        }
        patternToken.arguments->push_back(argument);
    }
    return patternToken;
}

void Tokenizer::getWithClauseToken(std::string pql, QueryToken& queryToken) {
    std::smatch sm;
    std::string withClauseString = "";

    // Get all with clauses substring and combine them all into one string
    while (std::regex_search (pql, sm, std::regex(WITH_CL))) {
        cout << sm[0];
        withClauseString += sm[0];
        pql = sm.suffix().str();
    }

    // Split with clauses into each with clause substring
    std::vector<std::string> withClauseStrings = StringFormatter::tokenizeByRegex(withClauseString, SPLIT_WITH_CL);
    std::vector<std::pair<std::string, std::string>>* withClauses = new std::vector<std::pair<std::string, std::string>>();

    for (std::string withClause : withClauseStrings) {
        std::vector<std::string> withClauseArgs = StringFormatter::tokenizeByRegex(withClause, SPLIT_EQUALS);
        withClauses->push_back(std::make_pair(withClauseArgs[0], withClauseArgs[1]));
    }

    queryToken.withClauses = withClauses;
}

void Tokenizer::cleanQueryToken(QueryToken& queryToken) {
    for (SuchThatClauseToken suchThatClauseToken : *(queryToken.suchThatClauseTokens)) {
        delete suchThatClauseToken.arguments;
    }

    for (PatternToken patternToken : *(queryToken.patternTokens)) {
        delete patternToken.arguments;
    }

    delete queryToken.declarationTokens;
    delete queryToken.selectClauseTokens;
    delete queryToken.suchThatClauseTokens;
    delete queryToken.patternTokens;
    delete queryToken.declarations;
    delete queryToken.withClauses;
}
