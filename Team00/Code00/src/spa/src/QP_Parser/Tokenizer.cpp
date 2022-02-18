#include "Tokenizer.h"
#include "StringFormatter.h"
#include "Constants.h"

#include <string>
#include <utility>
#include <vector>
#include <map>
#include <regex>

using namespace qp;
// TODO: transfer regex to constants file
QueryToken Tokenizer::getQueryToken(std::string query) {
    QueryToken queryToken = QueryToken();

    // check if length of query is non-zero
    if (query.length() == 0) {
        return queryToken;
    }

    query = std::regex_replace(query, regex("\n"), "");

    // Gets all the different tokens
    getDeclarationTokens(query, queryToken);
    getSelectClauseTokens(query, queryToken);
    getSuchThatClauseTokens(query, queryToken);
    getPatternClauseTokens(query, queryToken);

    return queryToken;
}

void Tokenizer::getDeclarationTokens(std::string pql, QueryToken& queryToken) {
    std::string allDeclarationsOnly = StringFormatter::tokenizeByRegex(pql, "[ |\n]*;[ |\n]*(Select.*)")[0];
    // Separates declarations by design entities
    std::vector<std::string> declarationsToken = StringFormatter::tokenizeByRegex(allDeclarationsOnly, "[ ]*;[ ]*");
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
        std::vector<std::string> synonyms = StringFormatter::tokenizeByRegex(synonymsString, "[ ]*,[ ]*");

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
    std::vector<std::string> tokens = StringFormatter::tokenizeByRegex(pql, "(.*);[ |\n]*(Select[ ]+|[ ]+|(.*;))");
    std::string synonym = tokens[0].substr(0, tokens[0].find(" "));
    queryToken.selectClauseToken = synonym;
}

void Tokenizer::getSuchThatClauseTokens(std::string& pql, QueryToken& queryToken) {
    pql = std::regex_replace(pql, regex("\\*"), "-");
    std::vector<std::string> backClauses = StringFormatter::tokenizeByRegex(pql, "(.)*such [ ]*that[ ]+");

    if (backClauses[0] == pql) {
        return;
    }

    std::vector<std::string> suchThatClauses = StringFormatter::tokenizeByRegex(backClauses[0], "[ ]*[\\(\\),][ ]*");
    std::string relRef = std::regex_replace(suchThatClauses[0], regex("-"), "*");

    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    suchThatClauseToken.relRef = relRef;
    suchThatClauseToken.arguments = new std::pair<std::string, std::string>(suchThatClauses[1], suchThatClauses[2]);
    queryToken.suchThatClauseTokens = new std::vector<SuchThatClauseToken>{suchThatClauseToken};
}

void Tokenizer::getPatternClauseTokens(std::string pql, QueryToken& queryToken) {
    std::vector<std::string> backClauses = StringFormatter::tokenizeByRegex(pql, "(.*)[ ]+pattern[ ]+");
    if (backClauses[0] == pql) {
        return;
    } else if (queryToken.selectClauseToken == "pattern") {
        backClauses = StringFormatter::tokenizeByRegex(pql, "(.*)[ ]+pattern[ ]+" + SYNONYM + "[ ]*\\(");
        backClauses[0] = "pattern (" + backClauses[0];
    }

    std::vector<std::string> patternClause = StringFormatter::tokenizeByRegex(backClauses[0], "[ ]*[\\(\\),][ ]*");
    std::string synonym = StringFormatter::removeTrailingSpace(patternClause[0]);

    PatternToken patternToken = PatternToken();
    patternToken.synonym = synonym;
    patternToken.arguments = new std::pair<std::string, std::string>(patternClause[1], patternClause[2]);
    queryToken.patternTokens = new std::vector<PatternToken>{patternToken};
}
