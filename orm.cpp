#include "dialects/postgres/postgres_dialect.hpp"
#include "dialects/postgres/postgres_driver.cpp" // Implementação do Driver
#include "includes/orm/code/db.hpp"
#include <memory>

int main() {
  auto driver = std::make_shared<orm::dialects::PostgresDriver>();
  auto dialect = new orm::dialects::PostgresDialect();

  if (driver->connect("host=localhost user=postgres password=root dbname=evia")) {
    orm::DB db(driver, dialect);

    auto usuarios = db.table("usuarios")
      .where("valor = 0")
      .find();

    std::cout << "Registros encontrados: " << usuarios.size() << std::endl;

    for (const auto &user : usuarios) {
      std::cout << "ID: " << user.at("id") << " | Nome: " << user.at("nome")
        << " | Criado em: " << user.at("criado_em") << std::endl;
    }
  }

  return 0;
}
