#ifndef ORM_DIALECT_HPP
#define ORM_DIALECT_HPP

#include <string>

namespace orm {
  namespace drivers {
    class Dialect {
    public:
      virtual ~Dialect() = default;
      // Each Engine handlers parameter placeholders differently
      virtual std::string bind_parameter(int index) = 0;
      virtual std::string quote_identifier(const std::string& name) = 0;
    };
  }
}

#endif
