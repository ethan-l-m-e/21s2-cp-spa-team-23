#include "PreProcessor.h"
#include <string>
#include <vector>
#include <regex>
#include "Tokenizer.h"

using namespace qp;

void PreProcessor::getQuery(std::string pql) {
    Tokenizer tokenizer = Tokenizer();
    QueryToken queryToken = tokenizer.getQueryToken(pql);

};

void PreProcessor::getDeclarations(QueryToken queryToken) {
    std::vector<std::string> declarations = *(queryToken.declarationTokens);
    std::string designEntity;

    for (std::string declaration : declarations) {
        designEntity = declaration.substr(0, declaration.find(' '));
        if (designEntity == "stmt") {
            
        } else if (designEntity == "read") {

        } else if (designEntity == "print") {

        } else if (designEntity == "call") {

        } else if (designEntity == "while") {

        } else if (designEntity == "if") {

        } else if (designEntity == "assign") {

        } else if (designEntity == "variable") {

        } else if (designEntity == "constant") {

        } else if (designEntity == "procedure") {

        }
    }
}
