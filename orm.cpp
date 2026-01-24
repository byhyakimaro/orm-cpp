#include "dialects/postgres/postgres_dialect.hpp"
#include "dialects/postgres/postgres_driver.cpp"
#include "includes/orm/code/db.hpp"
#include "includes/dotenv.h"
#include <memory>

int main() {
  EnvLoader::load();

  std::string dbname = EnvLoader::get("DB_NAME", "evia");
  std::string user = EnvLoader::get("DB_USER", "postgres");
  std::string pass = EnvLoader::get("DB_PASS", "");
  std::string host = EnvLoader::get("DB_HOST", "localhost");
  std::string port = EnvLoader::get("DB_PORT", "5432");

  std::string conn_str = "dbname=" + dbname + " user=" + user +
    " password=" + pass + " host=" + host + " port=" + port;

  auto driver = std::make_shared<orm::dialects::PostgresDriver>();
  auto dialect = new orm::dialects::PostgresDialect();

  if (driver->connect(conn_str)) {
    orm::DB db(driver, dialect);

    // Product entity schema definition
    orm::TableSchema produtoSchema;
    produtoSchema.name = "produtos";
    produtoSchema.columns = {
        {"id", "SERIAL", false, true, true}, // Name, Type, Nullable, PK, AI
        {"nome", "VARCHAR(100)", false},
        {"preco", "DECIMAL(10,2)", false}
    };

    // Trigger database schema migration
    db.auto_migrate(produtoSchema);

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
