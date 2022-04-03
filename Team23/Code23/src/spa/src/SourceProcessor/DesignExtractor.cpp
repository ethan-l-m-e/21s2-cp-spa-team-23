#include "DesignExtractor.h"
#include "SemanticsVerifier.h"
#include "EntityExtractor.h"
#include "RelationshipExtractor.h"

void DesignExtractor::Extract(Node* programNode){
    // check for semantics error
    SemanticsVerifier::detectDuplicateProcedure(programNode);
    SemanticsVerifier::detectCyclicCalls(programNode);
    //extract variables and constants etc
    EntityExtractor::extractAllEntities(programNode);
    //attaches each stmt node to a procedure
    EntityExtractor::assignProcedureToNodes(programNode,nullptr);
    //extract relationships
    RelationshipExtractor::extractRelationships(programNode);

}