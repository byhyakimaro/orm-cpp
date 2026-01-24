#ifndef ORM_QUERY_BUILDER_HPP
#define ORM_QUERY_BUILDER_HPP

#include "../drivers/dialect.hpp"
#include "../drivers/driver.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

namespace orm {
  namespace code {

    class QueryBuilder {
    private:
      std::string table_name;
      std::vector<std::string> clauses;
      int limit_val = -1;

      // Using shared_ptr to manage shared ownership and prevent dangling pointers
      std::shared_ptr<drivers::Driver> driver;
      drivers::Dialect* dialect;

    public:
      // Decoupling components by passing all required state via constructor
      QueryBuilder(std::string table, std::shared_ptr<drivers::Driver> drv, drivers::Dialect* dia)
        : table_name(std::move(table)), driver(drv), dialect(dia) {}

      QueryBuilder& where(const std::string& condition) {
        clauses.push_back(condition);
        return *this;
      }

      QueryBuilder& limit(int value) {
        limit_val = value;
        return *this;
      }

      ResultSet find() {
        std::string table = dialect->quote_identifier(table_name);
        std::string sql = "SELECT * FROM " + table;

        if(!clauses.empty()) {
          sql += " WHERE ";
          for (size_t i = 0; i < clauses.size(); ++i) {
            sql += clauses[i] + (i == clauses.size() - 1 ? "" : " AND ");
          }
        }

        if (limit_val != -1) {
          sql += " LIMIT " + std::to_string(limit_val);
        }

        std::cout << "Enviando ao Postgres: " << sql << std::endl;
        driver->execute(sql);

        return driver->query(sql);
      }
    };
  }
}
#endif
