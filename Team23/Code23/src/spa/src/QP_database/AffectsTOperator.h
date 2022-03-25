//
// Created by Tin Hong Wen on 25/3/22.
//

#ifndef SPA_AFFECTSTOPERATOR_H
#define SPA_AFFECTSTOPERATOR_H

#include "CacheOperator.h"
#include "AffectsOperator.h"
#include "NextTOperator.h"

class AffectsTOperator: protected CacheOperator  {
public:
    AffectsTOperator(PKB *pkb);

    bool computeRelation(string left, string right) override;
    stmtSetStr computeLHS(string right) override;
    stmtSetStr computeRHS(string left) override;
    static AffectsTOperator *getInstance();

protected:
    AffectsTOperator();
    static AffectsTOperator* singleton;
    AffectsOperator* affectsOperator = AffectsOperator::getInstance();
    NextTOperator* nextTOperator = NextTOperator::getInstance();

};


#endif //SPA_AFFECTSTOPERATOR_H
