#include "Tokenizer.h"
#include "StringFormatter.h"
#include "Constants.h"

#include <string>
#include <utility>
#include <vector>
#include <regex>
#include <map>

using namespace qp;
// TODO: transfer regex to constants file
QueryToken Tokenizer::getQueryToken(string query) {
    QueryToken queryToken = QueryToken();

    // check if length of query is non-zero
    if (query.length() == 0) {
        return queryToken;
    }

    // Gets all the different tokens
    getDeclarationTokens(query, queryToken);
    getSelectClauseTokens(query, queryToken);
    getSuchThatClauseTokens(query, queryToken);
    getPatternClauseTokens(query, queryToken);

    return queryToken;
}

void Tokenizer::getDeclarationTokens(std::string pql, QueryToken& queryToken) {
    string allDeclarationsOnly = StringFormatter::tokenizeByRegex(pql, "[ |\n]*(Select.*)")[0];
    // Separates declarations by design entities
    vector<string> declarationsToken = StringFormatter::tokenizeByRegex(allDeclarationsOnly, "[ ]*;[ ]*");
    splitDeclarations(declarationsToken, queryToken);
}

void Tokenizer::splitDeclarations(vector<string>& declarations, QueryToken& queryToken) {
    auto declarationsMap = new map<string, string>();
    string designEntity, synonymsString, declarationString;
    vector<string> declarationNames = vector<string>();
    vector<string> designEntities = vector<string>();

    for (string &declaration : declarations) {
        designEntity = StringFormatter::extractFrontStringByRegex(declaration, " ");
        synonymsString = declaration.substr(designEntity.length() + 1);
        vector<string> synonyms = StringFormatter::tokenizeByRegex(synonymsString, "[ ]*,[ ]*");

        for (auto synonym : synonyms) {
            declarationNames.push_back(synonym);
            declarationsMap->insert({synonym, designEntity});
        }
        designEntities.push_back(designEntity);
    }
    queryToken.declarationTokens = declarationsMap;
    queryToken.declarations = new pair<vector<string>, vector<string>>(declarationNames, designEntities);
}

void Tokenizer::getSelectClauseTokens(string& pql, QueryToken& queryToken) {
    vector<string> tokens = StringFormatter::tokenizeByRegex(pql, "(Select[ ]+|[ ]+|(.*;))");
    queryToken.selectClauseToken = tokens[0];
}

void Tokenizer::getSuchThatClauseTokens(string& pql, QueryToken& queryToken) {
    std::regex relationshipReg(RELATIONSHIP_MATCH);
    bool hasRelationship = regex_match(pql, relationshipReg);
    if (!hasRelationship) {
        return;
    }

    vector<string> backClauses = StringFormatter::tokenizeByRegex(pql, "(.*)such [ ]*that[ ]+");
    vector<string> suchThatClauses = StringFormatter::tokenizeByRegex(backClauses[0], "[ ]*[\\(\\),][ ]*");

    SuchThatClauseToken suchThatClauseToken = SuchThatClauseToken();
    suchThatClauseToken.relRef = suchThatClauses[0];
    suchThatClauseToken.arguments = new pair<string, string>(suchThatClauses[1], suchThatClauses[2]);
    queryToken.suchThatClauseTokens = new vector<SuchThatClauseToken>{suchThatClauseToken};
}

void Tokenizer::getPatternClauseTokens(string& pql, QueryToken& queryToken) {
    std::regex patternReg(PATTERN_MATCH);
    bool hasPattern = regex_match(pql, patternReg);
    if (!hasPattern) {
        return;
    }

    vector<string> backClauses = StringFormatter::tokenizeByRegex(pql, "(.*)[ ]+pattern[ ]+");
    vector<string> patternClause = StringFormatter::tokenizeByRegex(backClauses[0], "[ ]*[\\(\\),][ ]*");
    string synonym = StringFormatter::removeTrailingSpace(patternClause[0]);

    PatternToken patternToken = PatternToken();
    patternToken.synonym = synonym;
    patternToken.arguments = new pair<string, string>(patternClause[1], patternClause[2]);
    queryToken.patternTokens = new vector<PatternToken>{patternToken};
}
