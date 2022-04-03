//
// Created by リム・イーサン on 2/3/22.
//

#ifndef SPA_STMTNODE_H
#define SPA_STMTNODE_H

#include "Node.h"

//stmt: read | print | while | if | assign
class StmtNode: public Node {
    int statementNumber;
    Node* proc;

public:
    StmtNode(int num);
    int getStmtNumber() const override;
    void setProc(Node *proc);
    Node *getProc() const;

};

#endif //SPA_STMTNODE_H
