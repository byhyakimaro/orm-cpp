#include "includes/orm/code/db.hpp"
#include "dialects/postgres/postgres_driver.cpp" // Implementação do Driver
#include "dialects/postgres/postgres_dialect.hpp"
#include <memory>

int main() {
  auto driver = std::make_shared<orm::dialects::PostgresDriver>();
  auto dialect = new orm::dialects::PostgresDialect();

  if (driver->connect("host=localhost user=postgres password=root dbname=evia")) {
    orm::DB db(driver, dialect);

    db.table("usuarios")
      .where("valor = 0")
      .find();
  }

  return 0;
}
