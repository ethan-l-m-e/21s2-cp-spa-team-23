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
        std::vector<std::string> declarationArgs = StringFormatter::tokenizeByRegex(declaration, "([ |\t]+|,)");
        designEntity = declarationArgs[0];

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
    std::smatch sm;
    std::regex_search (pql, sm, std::regex("Select[( |\t)]+" + RESULT_CL));
    std::string synonym = sm[0];
    std::string synonyms = std::regex_replace(synonym, std::regex("(Select|[ |\t]+|<|>)"), "");
    synonyms = std::regex_replace(synonyms, regex(","), " ");

    std::vector<std::string>* selectClauseTokens = new std::vector<std::string>();
    std::stringstream ss(synonyms);
    std::string selectClauseToken;
    while (getline(ss, selectClauseToken, ' ')) {
        selectClauseTokens->push_back(selectClauseToken);
    }

    queryToken.selectClauseTokens = selectClauseTokens;
}

void Tokenizer::getSuchThatClauseTokens(std::string pql, QueryToken& queryToken) {
    std::smatch sm;
    std::vector<std::string> suchThatClauses = std::vector<std::string>();

    while (std::regex_search (pql, sm, std::regex(REL_REF))) {
        std::string x = sm[0];
        x = StringFormatter::removeTrailingSpace(x);
        suchThatClauses.push_back(x);
        pql = sm.suffix().str();
    }

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
    suchThatClauseToken.arguments = new std::pair<std::string, std::string>(suchThatClauseArgs[1], suchThatClauseArgs[2]);
    return suchThatClauseToken;
}


void Tokenizer::getPatternClauseTokens(std::string pql, QueryToken& queryToken) {
    std::smatch sm;
    std::vector<std::string> patternClauses = std::vector<std::string>();

    while (std::regex_search (pql, sm, std::regex("pattern[ |\t]*" + PATTERN))) {
        std::string x = sm[0];
        x = StringFormatter::removeTrailingSpace(x);
        patternClauses.push_back(x);
        pql = sm.suffix().str();
    }

    std::vector<PatternToken>* patternTokens = new std::vector<PatternToken>();
    for (std::string patternClause : patternClauses) {
        PatternToken patternToken = convertStringToPatternToken(patternClause);
        patternTokens->push_back(patternToken);
    }

    queryToken.patternTokens = patternTokens;
}

PatternToken Tokenizer::convertStringToPatternToken(std::string patternClause) {
    std::vector<std::string> patternClauseArgs = StringFormatter::tokenizeByRegex(patternClause, PATTERN_ARGUMENTS);
    std::string synonym = StringFormatter::removeTrailingSpace(patternClauseArgs[0]);

    PatternToken patternToken = PatternToken();
    patternToken.synonym = StringFormatter::tokenizeByRegex(synonym, "[ |\t]+")[1];
    patternToken.arguments = new std::vector<std::string>(patternClauseArgs.begin()+1, patternClauseArgs.end());
    return patternToken;
}

void Tokenizer::getWithClauseToken(std::string pql, QueryToken& queryToken) {
    std::smatch sm;
    std::string withClauseString = "";

    while (std::regex_search (pql, sm, std::regex(WITH_CL))) {
        cout << sm[0];
        withClauseString += sm[0];
        pql = sm.suffix().str();
    }

    std::vector<std::string> withClauseStrings = StringFormatter::tokenizeByRegex(withClauseString, "[ |\\t]*(with|and)[ |\\t]*");
    std::vector<std::pair<std::string, std::string>>* withClauses = new std::vector<std::pair<std::string, std::string>>();

    for (std::string withClause : withClauseStrings) {
        std::vector<std::string> withClauseArgs = StringFormatter::tokenizeByRegex(withClause, "[ |\\t]*=[ |\\t]*");
        withClauses->push_back(std::make_pair(withClauseArgs[0], withClauseArgs[1]));
    }

    queryToken.withClauses = withClauses;
}
