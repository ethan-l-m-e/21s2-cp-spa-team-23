#include "TestWrapper.h"
#include "AbstractWrapper.h"
#include "QP_Parser/Exception.h"
#include "SourceProcessor/Parser.h"


// implementation code of WrapperFactory - do NOT modify the next 5 lines
AbstractWrapper* WrapperFactory::wrapper = 0;
AbstractWrapper* WrapperFactory::createWrapper() {
    if (wrapper == 0) wrapper = new TestWrapper;
    return wrapper;
}
// Do not modify the following line
volatile bool AbstractWrapper::GlobalStop = false;
AbstractWrapper::~AbstractWrapper() = default;

// a default constructor
TestWrapper::TestWrapper() {
  // create any objects here as instance variables of this class
  // as well as any initialization required for your spa program
  pkb = PKB::getInstance();
  preProcessor = new qp::QueryParser();
  queryEvaluator = new QueryEvaluator(pkb);
}

TestWrapper::~TestWrapper() = default;

// method for parsing the SIMPLE source
void TestWrapper::parse(std::string filename) {
    try {
        SourceProcessor::run(filename);
    } catch (std::exception ex) {
        std::cout << "Invalid source code: " << ex.what();
    }
    // call your parser to do the parsing
    // ...rest of your code...
}

// method to evaluating a query
void TestWrapper::evaluate(std::string query, std::list<std::string>& results){
  // call your ClauseEvaluators to evaluate the query here
  // ...code to evaluate query...
  try {
      Query processedQuery = preProcessor->getQuery(query);
      results = queryEvaluator->evaluate(&processedQuery);
  } catch (qp::QPInvalidSyntacticException e) {
      std::cout << "Invalid Syntax: " << e.what();
  } catch (qp::QPInvalidSemanticException e) {
    std::cout << "Invalid Semantics: " << e.what();
  } catch (qp::QPTokenizerException e) {
      std::cout << "Invalid Syntax: " << e.what();
  } catch (qp::QPEvaluatorException e) {
      std::cout << "Evaluator exception: " << e.what();
  } catch (InvalidSyntacticException e) {
      std::cout << "Invalid Syntax: " << e.what();
  }
  // store the answers to the query in the results list (it is initially empty)
  // each result must be a string.
}
