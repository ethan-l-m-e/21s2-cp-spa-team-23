#include <string>
#include <vector>

using namespace std;

#include "PKB.h"


PKB *PKB::singleton = nullptr;

PKB::PKB() {

}

PKB* PKB::getInstance() {

    if (PKB::singleton == nullptr) {
        PKB::singleton = new PKB();
    }

    return PKB::singleton;

}


void PKB::clearPKB() {

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

    relationship.next.clear();

    relationship.calls.clear();
    relationship.callsT.clear();


}