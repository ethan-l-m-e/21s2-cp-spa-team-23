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
//    if(file.is_open()){
//        cout<<"file is open\n";
//    }else{
////        std::ofstream outfile ("trace.txt");
////        outfile<<"mytext"<< std::endl;
////        outfile.close();
//        cout<<filename;
//        cout<<"\nfile cannot open\n";
//        cout<<system("ls");
//    }
    // preferably throw exception if file invalid
    // extract text
    stringstream codeStream;
    codeStream << file.rdbuf();
    string sourceCode = codeStream.str();
    file.close();
    Node* programNode = Parser::Parse(sourceCode);
    DesignExtractor::Extract(programNode);
}