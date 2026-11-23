#include <framelog/version.hpp>

#ifndef FRAMELOG_VERSION
#error "FRAMELOG_VERSION must be defined by the build system"
#endif

namespace flog {

const char* version() noexcept { return FRAMELOG_VERSION; }

}  // namespace flog
