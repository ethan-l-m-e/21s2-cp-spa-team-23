//
// Created by Tin Hong Wen on 19/2/22.
//
#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <sstream>
#include <map>
#include <regex>

#include "SourceProcessor.h"
#include "Parser.h"
#include "DesignExtractor.h"

void SourceProcessor::run(string filename) {
    // load file
    ifstream file;
    file.open(filename);
    stringstream codeStream;
    codeStream << file.rdbuf();
    string sourceCode = codeStream.str();
    file.close();

    //Perform parsing and extraction
    Node* programNode = Parser::Parse(sourceCode);
    DesignExtractor::Extract(programNode);
}