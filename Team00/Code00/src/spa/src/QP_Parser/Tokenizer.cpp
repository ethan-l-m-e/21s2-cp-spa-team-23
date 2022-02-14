#include "Tokenizer.h"
#include "StringFormatter.h"

#include <iostream>
#include <string>
#include <regex>
#include <utility>
#include <vector>

using namespace qp;

QueryToken Tokenizer::getQueryToken(std::string query) {

    QueryToken queryToken = QueryToken();

    // check if length of query is non-zero
    if (query.length() == 0) {
        return queryToken;
    }
    // TODO: transfer regex to constants file
    getDeclarationTokens(query, queryToken);
    getSelectClauseTokens(query, queryToken);
    getSuchThatClauseTokens(query, queryToken);
    return queryToken;
}

void Tokenizer::getDeclarationTokens(std::string pql, QueryToken& queryToken) {
    string selectLine = StringFormatter::extractFrontStringByRegex(pql, "\n");
    vector<string> declarations = StringFormatter::tokenizeByRegex(selectLine, "[]*;");
    auto declarationPtr = splitDeclarations(declarations);
    queryToken.declarationTokens = declarationPtr;
}

vector<DeclarationToken>* Tokenizer::splitDeclarations(vector<string> &declarations) {
    auto declarationPtr = new vector<DeclarationToken>();
    string designEntity, synonymsString, declarationString;

    for (string &declaration : declarations) {
        designEntity = StringFormatter::extractFrontStringByRegex(declaration, " ");
        synonymsString = declaration.substr(designEntity.length() + 1);
        vector<string> synonyms = StringFormatter::tokenizeByRegex(synonymsString, "[]*, ");

        // Create Declaration token
        DeclarationToken declarationToken = DeclarationToken();
        declarationToken.designEntity = designEntity;
        declarationToken.synonyms = new vector<string>(synonyms);
        declarationPtr->push_back(declarationToken);
    }
    return declarationPtr;
}

void Tokenizer::getSelectClauseTokens(string& pql, QueryToken& queryToken) {
    string selectLine = StringFormatter::extractSecondStringByRegex(pql, "\n");
    vector<string> tokens = StringFormatter::tokenizeByRegex(selectLine, "(Select[ ]*|[ ]+)");
    queryToken.selectClauseToken = tokens[0];
}

void Tokenizer::getSuchThatClauseTokens(std::string& pql, QueryToken& queryToken) {
    string selectLine = StringFormatter::extractSecondStringByRegex(pql, "\n");
    vector<string> backClauses = StringFormatter::tokenizeByRegex(selectLine, "(.*)such that ");
    vector<string> suchThatClauses = StringFormatter::tokenizeByRegex(backClauses[0], "(\\()|(\\))|([ ]*,[ ]*)");
    auto suchThatClausesPtr = new vector<string>(suchThatClauses);
    queryToken.suchThatClauseToken = suchThatClausesPtr;
}

void Tokenizer::getPatternClause(std::string& pql, QueryToken& queryToken) {
    string selectLine = StringFormatter::extractSecondStringByRegex(pql, "\n");
    vector<string> backClauses = StringFormatter::tokenizeByRegex(selectLine, "(.*)pattern[ ]*");
    vector<string> patternClause = StringFormatter::tokenizeByRegex(backClauses[0], "(\\()|(\\))|(,)");

    string synonym = StringFormatter::removeTrailingSpace(patternClause[0]);
    PatternToken* patternToken = new PatternToken();
    patternToken->synonym = synonym;
    patternToken->arguments = new pair<string, string>(patternClause[1], patternClause[2]);
    queryToken.patternToken = patternToken;
}
