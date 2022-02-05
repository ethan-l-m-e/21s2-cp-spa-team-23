#include "PreProcessor.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Tokenizer.h"

using namespace qp;

void PreProcessor::getQuery(std::string filename) {
    // Load File
    std::fstream file;
    file.open(filename,std::ios::in);
    std::vector<std::string> queries;

    if (file.is_open()) {
        std::string text;
        int lineNo = 0;
        std::string query;
        // Read data from file and put it into string.
        while(getline(file, text)){
            if (lineNo % 2 == 0 && lineNo % 4 != 0) { // TODO: need to edit
                query = text;
            } else if (lineNo % 3 == 0) {
                query += "\n" + text;
                queries.push_back(query);
            }
            lineNo += 1;
        }
    }
    file.close();

    Tokenizer tokenizer = Tokenizer();
    std::vector<QueryToken> queryTokens = tokenizer.getQueryTokens(queries);
};
