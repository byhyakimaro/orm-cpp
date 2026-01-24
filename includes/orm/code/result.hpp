#ifndef ORM_RESULT_HPP
#define ORM_RESULT_HPP

#include <vector>
#include <map>
#include <string>

namespace orm {
  namespace code {
    // Map<ColumnName, Value> representation for the row
    using Row = std::map<std::string, std::string>;

    struct ResultSet {
      std::vector<Row> rows;

      // Helper methods for collection iteration
      auto begin() { return rows.begin(); }
      auto end() { return rows.end(); }
      bool empty() const { return rows.empty(); }
      size_t size() const { return rows.size(); }
    };
  }
}
#endif
