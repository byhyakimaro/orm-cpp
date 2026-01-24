#ifndef ORM_SCHEMA_HPP
#define ORM_SCHEMA_HPP

#include <string>
#include <vector>

namespace orm {
    struct Column {
        std::string name;
        std::string type;
        bool nullable = true;
        bool primary_key = false;
        bool auto_increment = false;
    };

    struct TableSchema {
        std::string name;
        std::vector<Column> columns;
    };
}
#endif
