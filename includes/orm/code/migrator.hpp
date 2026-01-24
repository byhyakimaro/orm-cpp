#ifndef ORM_MIGRATOR_HPP
#define ORM_MIGRATOR_HPP

#include "schema.hpp"
#include "../drivers/driver.hpp"
#include <iostream>
#include <sstream>
#include <memory>

namespace orm {
    class Migrator {
    private:
        std::shared_ptr<drivers::Driver> driver;

    public:
      Migrator(std::shared_ptr<drivers::Driver> d) : driver(d) {}

      void auto_migrate(const TableSchema& schema) {
        if (driver->table_exists(schema.name)) {
          std::cout << "Table '" << schema.name << "' already exists. Skipping..." << std::endl;
          return;
        }

        std::stringstream sql;
        sql << "CREATE TABLE \"" << schema.name << "\" (";

        for (size_t i = 0; i < schema.columns.size(); ++i) {
          const auto& col = schema.columns[i];
          sql << "\"" << col.name << "\" " << col.type;

          if (col.primary_key) sql << " PRIMARY KEY";
          if (col.auto_increment && col.type == "SERIAL") {}
          if (!col.nullable) sql << " NOT NULL";

          if (i < schema.columns.size() - 1) sql << ", ";
        }

        sql << ");";

        std::cout << "Migrating: " << sql.str() << std::endl;
        driver->execute(sql.str());
      }
    };
}
#endif
