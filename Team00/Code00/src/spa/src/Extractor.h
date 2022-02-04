//
// Created by Lucas Tai on 3/2/22.
//

#ifndef SPA_EXTRACTOR_H
#define SPA_EXTRACTOR_H
#include <string>


class Extractor {
    static std::string* information;


public:
    Extractor* extractAssign(std::string sourceCode );

    Extractor* extractProcedure(std::string sourceCode );

    std::string getAssignVar();

    std::string getAssignExpr();

    std::string getProcStmtLst();

    std::string getProcName();

    Extractor *extractExpression(std::string sourceCode);

    Extractor(){
    }
};


#endif //SPA_EXTRACTOR_H
