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
#include "RelationshipExtractor.h"
#include "EntityExtractor.h"
#include "SemanticsVerifier.h"

void SourceProcessor::run(string filename) {
    // load file
    ifstream file;
    file.open(filename);
    // preferably throw exception if file invalid
    // extract text
    stringstream codeStream;
    codeStream << file.rdbuf();
    string sourceCode = codeStream.str();
    file.close();

    Node* programNode = Parser::Parse(sourceCode);
    // check for semantics error
    SemanticsVerifier::detectDuplicateProcedure(programNode);
    SemanticsVerifier::detectCyclicCalls(programNode);
    //extract variables and constants etc
    EntityExtractor::extractAllEntities(programNode);
    //extract relationships
    RelationshipExtractor::extractRelationships(programNode);
}