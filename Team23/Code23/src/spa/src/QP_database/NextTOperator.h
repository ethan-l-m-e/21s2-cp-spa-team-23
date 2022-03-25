//
// Created by Tin Hong Wen on 22/3/22.
//

#ifndef SPA_NEXTTOPERATOR_H
#define SPA_NEXTTOPERATOR_H

#include "CacheOperator.h"

class NextTOperator : protected CacheOperator {
public:
    bool computeRelation(string left, string right) override;
    stmtSetStr computeLHS(string rightNode) override;
    stmtSetStr computeRHS(string leftNode) override;
    static NextTOperator *getInstance();

protected:
    NextTOperator();
    static NextTOperator* singleton;
};


#endif //SPA_NEXTTOPERATOR_H
