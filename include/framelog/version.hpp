#pragma once

namespace flog {

/// Semantic version compiled into the library, for example "0.1.0".
[[nodiscard]] const char* version() noexcept;

}  // namespace flog
