#include <string>
#include <vector>

using namespace std;

//#include "PKB/FKB.h"
#include "FKB.h"

//#include "PKB/Statement/Statement.h"

//#include "Statement-Old/AbstractStatement.h"


FKB *FKB::singleton = nullptr;

FKB::FKB() {

}

FKB* FKB::getInstance() {

    if (FKB::singleton == nullptr) {
        FKB::singleton = new FKB();
    }

    return FKB::singleton;

}


void FKB::clearFKB() {

    entity.variables.clear();
    entity.procedures.clear();
    entity.constants.clear();


    statement.statements.clear();
    statement.assignStatements.clear();
    statement.readStatements.clear();
    statement.printStatements.clear();
    statement.ifStatements.clear();
    statement.whileStatements.clear();
    statement.callStatements.clear();


    relationship.follows.clear();
    relationship.followsT.clear();

    relationship.parent.clear();
    relationship.parentT.clear();

    relationship.usesS.clear();
    relationship.usesP.clear();

    relationship.modifiesS.clear();
    relationship.modifiesP.clear();

}