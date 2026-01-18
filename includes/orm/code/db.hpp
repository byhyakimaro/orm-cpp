// includes/orm/code/db.hpp
#include "query_builder.hpp"

namespace orm {
  class DB {
  private:
    std::shared_ptr<drivers::Driver> driver;
    drivers::Dialect* dialect;

  public:
    DB(std::shared_ptr<drivers::Driver> drv, drivers::Dialect* dia)
      : driver(drv), dialect(dia) {}

    code::QueryBuilder table(const std::string& name) {
      // Retorna o Builder com as dependências injetadas
      return code::QueryBuilder(name, driver, dialect);
    }
  };
}
