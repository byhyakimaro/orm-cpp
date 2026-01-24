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

      bool table_exists(const std::string& name) override {
          std::string sql = "SELECT EXISTS (SELECT FROM information_schema.tables WHERE table_name = '" + name + "');";
          auto rs = this->query(sql);
          return !rs.empty() && rs.rows[0].at("exists") == "t";
      }

      code::ResultSet query(const std::string& sql) override {
        code::ResultSet rs;
        PGresult* res = PQexec(conn, sql.c_str());

        // Validate query execution and result set integrity
        if (PQresultStatus(res) == PGRES_TUPLES_OK) {
          int n_rows = PQntuples(res);    // Schema rows cardinality
          int n_cols = PQnfields(res);    // Schema column cardinality

          for (int i = 0; i < n_rows; i++) {
            code::Row row_data;
            for (int j = 0; j < n_cols; j++) {
              // Column-to-value mapping for the current record
              std::string col_name = PQfname(res, j);
              std::string col_value = PQgetvalue(res, i, j);
              row_data[col_name] = col_value;
            }
            rs.rows.push_back(row_data);
          }
        } else {
          std::cerr << "Erro na busca: " << PQerrorMessage(conn) << std::endl;
        }

        PQclear(res); // Explicitly deallocate PGresult to ensure proper resource cleanup
        return rs;    // Return the internal C++ collection by value
      }

      void disconnect() override {
        if (conn) PQfinish(conn);
      }

      ~PostgresDriver() { disconnect(); }
    };
  }
}
