#ifndef ORM_DRIVER_HPP
#define ORM_DRIVER_HPP

#include <string>

namespace orm {
  namespace drivers {
    class Driver {
    public:
      virtual ~Driver() = default;
      virtual bool connect(const std::string& conn_str) = 0;
      virtual void disconnect() = 0;
      virtual void execute(const std::string& sql) = 0;
    };
  }
}

#endif
