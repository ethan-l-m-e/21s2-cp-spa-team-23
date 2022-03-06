#include "Tokenizer.h"
#include "StringFormatter.h"
#include "Constants.h"

#include <string>
#include <utility>
#include <vector>
#include <map>
#include <regex>
#include <sstream>

using namespace qp;

QueryToken Tokenizer::getQueryToken(std::string query) {
    QueryToken queryToken = QueryToken();

    // check if length of query is non-zero
    if (query.length() == 0) {
        return queryToken;
    }

    // Replace all newlines in the query
    query = std::regex_replace(query, regex("\n"), "");
//    query = std::regex_replace(query, regex("\\*"), "-");

    // Gets all the different tokens
    getDeclarationTokens(query, queryToken);
    getSelectClauseTokens(query, queryToken);
    getSuchThatClauseTokens(query, queryToken);
    getPatternClauseTokens(query, queryToken);

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
        std::smatch sm;
        std::regex_search(declaration, sm, std::regex(DESIGN_ENTITY));
        designEntity = sm[0];
        synonymsString = declaration.substr(designEntity.length());
        synonymsString = StringFormatter::removeTrailingSpace(synonymsString);
        std::vector<std::string> synonyms = StringFormatter::tokenizeByRegex(synonymsString, SPLIT_DECLARATIONS);

        for (auto synonym : synonyms) {
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
    patternToken.synonym = synonym;
    patternToken.arguments = new std::vector<std::string>(patternClauseArgs.begin()+1, patternClauseArgs.end());
    return patternToken;
}

void Tokenizer::getWithClauseToken(std::string pql, QueryToken& queryToken) {
    std::smatch sm;

//    while (std::regex_search (pql, sm, std::regex("pattern[ |\t]*" + PATTERN))) {
//        std::string x = sm[0];
//        x = StringFormatter::removeTrailingSpace(x);
//        patternClauses.push_back(x);
//        pql = sm.suffix().str();
//    }
//
//    std::vector<PatternToken>* patternTokens = new std::vector<PatternToken>();
//    for (std::string patternClause : patternClauses) {
//        PatternToken patternToken = convertStringToPatternToken(patternClause);
//        patternTokens->push_back(patternToken);
//    }
//
//    queryToken.patternTokens = patternTokens;
}
