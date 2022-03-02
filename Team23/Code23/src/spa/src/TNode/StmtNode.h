//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_STMTNODE_H
#define SPA_STMTNODE_H

#include "Node.h"

//stmt: read | print | while | if | assign
class StmtNode: public Node {
    int statementNumber;
public:
    StmtNode(int num);
    int getStmtNumber() const override;
};

#endif //SPA_STMTNODE_H
