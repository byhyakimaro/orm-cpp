# C++ ORM

A modern, header-only C++20 Object-Relational Mapper designed for simplicity, type-safety, and performance. This project provides a minimalistic and expressive API to bridge the gap between C++ data structures and relational databases.

## Features

- **Fluent Query Builder**: A powerful and type-safe DSL for constructing SQL queries.
- **Schema & Data Migration**: Simple and automated schema migration based on your C++ struct definitions.
- **Extensible Driver System**: Easily extendable to support different database backends.
  - Currently ships with a **PostgreSQL** driver.
- **Header-Only**: For easy integration into any C++ project.
- **`.env` Configuration**: Simple project configuration using `.env` files for database credentials.

## Prerequisites

To build and run this project, you will need:
- A C++20 compatible compiler (e.g., g++)
- `make`

## Building

The project uses a standard `Makefile` for compilation.

1.  **Clone the repository:**
    ```sh
    git clone <repository_url>
    cd orm
    ```

2.  **Build the project:**
    ```sh
    make
    ```
    This will compile the sources and create the executable at `build/orm_app.exe`.

## Configuration

The database connection is configured via a `.env` file in the root of the project.

Create a `.env` file with the following variables:
```
DB_HOST=localhost
DB_PORT=5432
DB_NAME=your_db
DB_USER=your_user
DB_PASSWORD=your_password
```

## Usage

The following is a demonstration of the ORM's core functionalities.

### 1. Database Connection

First, establish a connection to the database. The ORM uses a driver and dialect system to handle database-specific operations.

```cpp
#include "includes/orm/code/db.hpp"
#include "includes/dotenv.h"
#include "dialects/postgres/postgres_driver.cpp"
#include "dialects/postgres/postgres_dialect.hpp"
#include <memory>

// Load .env file
EnvLoader::load();

// Build connection string from environment variables
std::string conn_str = "dbname=" + EnvLoader::get("DB_NAME") +
                     " user=" + EnvLoader::get("DB_USER") +
                     " password=" + EnvLoader::get("DB_PASS") +
                     " host=" + EnvLoader::get("DB_HOST") +
                     " port=" + EnvLoader::get("DB_PORT");

// Initialize driver and dialect
auto driver = std::make_shared<orm::dialects::PostgresDriver>();
auto dialect = new orm::dialects::PostgresDialect();

if (driver->connect(conn_str)) {
    // Create a DB instance
    orm::DB db(driver, dialect);
    
    // ... proceed with ORM operations
}
```

### 2. Schema Definition & Migration

Define your table schema using the `TableSchema` struct. The ORM can then use this definition to automatically create or update your database schema.

```cpp
// Product entity schema definition
orm::TableSchema produtoSchema;
produtoSchema.name = "produtos";
produtoSchema.columns = {
    {"id", "SERIAL", false, true, true}, // Name, Type, Nullable, PK, Auto-Increment
    {"nome", "VARCHAR(100)", false},
    {"preco", "DECIMAL(10,2)", false}
};

// This will execute a "CREATE TABLE IF NOT EXISTS..." statement
db.auto_migrate(produtoSchema);
```

### 3. Querying Data

The fluent Query Builder provides a simple and readable way to construct complex queries.

#### Find Records

Use the `find()` method to retrieve a collection of records matching the specified conditions.

```cpp
// Retrieve all records from 'usuarios' where 'valor = 0'
auto usuarios = db.table("usuarios")
                  .where("valor = 0")
                  .find();

std::cout << "Registros encontrados: " << usuarios.size() << std::endl;

for (const auto &user : usuarios) {
  std::cout << "ID: " << user.at("id") << " | Nome: " << user.at("nome")
    << " | Criado em: " << user.at("criado_em") << std::endl;
}
```

*Note: Further examples for `create`, `update`, and `delete` can be extrapolated from the query builder's design. The current example in `orm.cpp` focuses on selection.*

## Database Dialects

The ORM is designed to be database-agnostic through a dialect and driver system. The core components are:
- **`Driver`**: An interface for database connection and query execution.
- **`Dialect`**: An interface for handling database-specific SQL syntax, such as parameter binding and identifier quoting.

Currently, a **PostgreSQL** dialect is implemented. To support another database (e.g., MySQL, SQLite), you would need to:
1.  Implement the `Driver` interface for the target database.
2.  Implement the `Dialect` interface to handle its specific SQL grammar.

## How to Contribute

1.  Fork the repository.
2.  Create a new feature branch (`git checkout -b feature/YourFeature`).
3.  Commit your changes (`git commit -am 'Add some feature'`).
4.  Push to the branch (`git push origin feature/YourFeature`).
5.  Open a new Pull Request.

## License

This project is licensed under the MIT License.
