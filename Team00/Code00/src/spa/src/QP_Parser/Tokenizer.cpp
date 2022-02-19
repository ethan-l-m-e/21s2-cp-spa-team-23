#include "Tokenizer.h"
#include "StringFormatter.h"
#include "Constants.h"

#include <string>
#include <utility>
#include <vector>
#include <map>
#include <regex>

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

    for (std::string &declaration : declarations) {
        designEntity = StringFormatter::extractFrontStringByRegex(declaration, " ");
        synonymsString = declaration.substr(designEntity.length() + 1);
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
    std::vector<std::string> tokens = StringFormatter::tokenizeByRegex(pql, SELECT_LINE);
    std::string synonym = tokens[0].substr(0, tokens[0].find(" "));
    queryToken.selectClauseToken = synonym;
}

void Tokenizer::getSuchThatClauseTokens(std::string& pql, QueryToken& queryToken) {
    // Replace * with - in the query
    pql = std::regex_replace(pql, regex("\\*"), "-");
    std::vector<std::string> backClauses = StringFormatter::tokenizeByRegex(pql, SUCH_THAT_CLAUSE);

    bool noSuchThatClause = backClauses[0] == pql;
    if (noSuchThatClause) {
        return;
    }

    std::vector<std::string> suchThatClauses = StringFormatter::tokenizeByRegex(backClauses[0], SPLIT_SUCH_THAT_CLAUSE);
    std::string relRef = std::regex_replace(suchThatClauses[0], regex("-"), "*");

    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    suchThatClauseToken.relRef = relRef;
    suchThatClauseToken.arguments = new std::pair<std::string, std::string>(suchThatClauses[1], suchThatClauses[2]);
    queryToken.suchThatClauseTokens = new std::vector<SuchThatClauseToken>{suchThatClauseToken};
}


void Tokenizer::getPatternClauseTokens(std::string pql, QueryToken& queryToken) {
    std::vector<std::string> backClauses = StringFormatter::tokenizeByRegex(pql, PATTERN_LINE);
    bool noPattern = backClauses[0] == pql;
    bool isSynonymCalledPattern = queryToken.selectClauseToken == "pattern";

    if (noPattern) {
        return;
    } else if (isSynonymCalledPattern) {
        // Handle the case where pattern is chosen as a synonym
        backClauses = StringFormatter::tokenizeByRegex(pql, REGEX_FOR_PATTERN_SYNONYM);
        backClauses[0] = "pattern (" + backClauses[0];
    }

    std::vector<std::string> patternClause = StringFormatter::tokenizeByRegex(backClauses[0], PATTERN_ARGUMENTS);
    std::string synonym = StringFormatter::removeTrailingSpace(patternClause[0]);

    PatternToken patternToken = PatternToken();
    patternToken.synonym = synonym;
    patternToken.arguments = new std::pair<std::string, std::string>(patternClause[1], patternClause[2]);
    queryToken.patternTokens = new std::vector<PatternToken>{patternToken};
}
