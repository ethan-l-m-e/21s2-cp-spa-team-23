#include <string>

namespace qp {
    class PreProcessor {
    public:
        void getQuery(std::string);
        void readFile(std::string, std::vector<std::string>&);
    };
}

