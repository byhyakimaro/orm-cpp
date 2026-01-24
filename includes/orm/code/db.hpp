// includes/orm/code/db.hpp
#include "query_builder.hpp"
#include "migrator.hpp"

namespace orm {
  class DB {
  private:
    std::shared_ptr<drivers::Driver> driver;
    drivers::Dialect* dialect;

  public:
    DB(std::shared_ptr<drivers::Driver> drv, drivers::Dialect* dia)
      : driver(drv), dialect(dia) {}

    code::QueryBuilder table(const std::string& name) {
      // Return the builder instance with resolved dependencies
      return code::QueryBuilder(name, driver, dialect);
    }

    void auto_migrate(const TableSchema& schema) {
        Migrator(driver).auto_migrate(schema);
    }
  };
}
