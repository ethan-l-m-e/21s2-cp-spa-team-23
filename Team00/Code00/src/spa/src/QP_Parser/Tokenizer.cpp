#include "Tokenizer.h"
#include "StringFormatter.h"

#include <string>
#include <utility>
#include <vector>
#include <iostream>
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
    getPatternClause(query, queryToken);

    return queryToken;
}

void Tokenizer::getDeclarationTokens(string pql, QueryToken& queryToken) {
    string declarationsLine = StringFormatter::extractFrontStringByRegex(pql, "\n");
    // Separates declarations by design entities
    vector<string> declarations = StringFormatter::tokenizeByRegex(declarationsLine, "[]*;");
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
    vector<string> tokens = StringFormatter::tokenizeByRegex(pql, "(Select[ ]+|[ ]+|(.*;))");
    queryToken.selectClauseToken = tokens[0];
}

void Tokenizer::getSuchThatClauseTokens(string& pql, QueryToken& queryToken) {
    vector<string> backClauses = StringFormatter::tokenizeByRegex(pql, "(.*)such [ ]*that[ ]+");
    vector<string> suchThatClauses = StringFormatter::tokenizeByRegex(backClauses[0], "[ ]*[\\(\\),][ ]*");

    auto suchThatClausesPtr = new vector<string>(suchThatClauses);
    queryToken.suchThatClauseToken = suchThatClausesPtr;
}

void Tokenizer::getPatternClause(string& pql, QueryToken& queryToken) {
    vector<string> backClauses = StringFormatter::tokenizeByRegex(pql, "(.*)[ ]+pattern[ ]+");
    vector<string> patternClause = StringFormatter::tokenizeByRegex(backClauses[0], "[ ]*[\\(\\),][ ]*");

    string synonym = StringFormatter::removeTrailingSpace(patternClause[0]);
    PatternToken* patternToken = new PatternToken();
    patternToken->synonym = synonym;
    patternToken->arguments = new pair<string, string>(patternClause[1], patternClause[2]);
    queryToken.patternToken = patternToken;
}
