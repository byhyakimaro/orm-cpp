#include "../../includes/orm/drivers/dialect.hpp"
#include <string>

namespace orm {
  namespace dialects {
    class PostgresDialect : public drivers::Dialect {
    public:
      std::string bind_parameter(int index) override {
       return "$" + std::to_string(index); // postgres use $1, $2 to parameters
      }

      std::string quote_identifier(const std::string& name) override {
        return "\"" + name + "\""; // postgres use double quoting for tables/coluns
      }
    };
  }
}
