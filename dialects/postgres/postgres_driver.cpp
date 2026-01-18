#include "../../includes/orm/drivers/driver.hpp"
#include <iostream>
#include <libpq-fe.h>
#include <ostream>
#include <string>

namespace orm {
  namespace dialects {
    class PostgresDriver : public drivers::Driver {
    private:
      PGconn* conn = nullptr;

    public:
      bool connect(const std::string& conn_str) override {
        conn = PQconnectdb(conn_str.c_str());
        if (PQstatus(conn) != CONNECTION_OK) {
          std::cerr << "Err Connection failed: " << PQerrorMessage(conn) << std::endl;
          return false;
        }
        std::cout << "PostgreSQL connection established." << std::endl;
        return true;
      }

      void execute(const std::string& sql) override {
        PGresult* res = PQexec(conn, sql.c_str());
        if (PQresultStatus(res) != PGRES_COMMAND_OK && PQresultStatus(res) != PGRES_TUPLES_OK) {
          std::cerr << "Erro na query: " << PQerrorMessage(conn) << std::endl;
        }
        PQclear(res);
      }

      void disconnect() override {
        if (conn) PQfinish(conn);
      }

      ~PostgresDriver() { disconnect(); }
    };
  }
}
