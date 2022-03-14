#include <string>
#include <vector>

using namespace std;

#include "PKB/PKB.h"

#include "PKB/Statement/Statement.h"

//#include "Statement-Old/AbstractStatement.h"


PKB *PKB::singleton = nullptr;

PKB::PKB() {
    assignStatementClass = new AssignStatement(statementClass);
    readStatementClass = new ReadStatement(statementClass);
    ifStatementClass = new IfStatement(statementClass);

}

PKB* PKB::getInstance() {

    if (PKB::singleton == nullptr) {
        PKB::singleton = new PKB(stat);
    }

    return PKB::singleton;

}


void PKB::clearPKB() {

    entity.variables.clear();
    entity.procedures.clear();
    entity.constants.clear();


    statement.statementClass.clear();
    statement.assignStatementClass.clear();
    statement.readStatementClass.clear();
    statement.ifStatementClass.clear();

    relationship.followsRelationshipClass.clear();
    relationship.tFollowsRelationshipClass.clear();

    relationship.parentRelationshipClass.clear();
    relationship.tParentRelationshipClass.clear();

    relationship.usesSRelationshipClass.clear();
    relationship.usesPRelationshipClass.clear();

    relationship.tUsesSRelationshipClass.clear();
    relationship.tUsesPRelationshipClass.clear();

    relationship.modifiesSRelationshipClass.clear();
    relationship.modifiesPRelationshipClass.clear();

    relationship.tModifiesSRelationshipClass.clear();
    relationship.tModifiesPRelationshipClass.clear();


}