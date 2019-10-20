#pragma once
#include <string>
#include <sstream>
#include <algorithm>

#define DELIMITER "\\"

namespace Doxydown {
    namespace Path {
        namespace Detail {
            inline void join(std::stringstream& ss, const std::string& first) {
                ss << first;
            }
            
            template <typename... Args>
            inline void join(std::stringstream& ss, const std::string& first, const Args&... args) {
                ss << first << DELIMITER;
                Detail::join(ss, args...);
            }
        }
        
        template <typename... Args>
        inline std::string join(const Args&... args) {
            std::stringstream ss;
            Detail::join(ss, args...);
            return ss.str();
        }

        inline std::string filename(const std::string& path) {
            const auto a = path.find_last_of('/');
            const auto b = path.find_last_of('\\');
            if (a != std::string::npos && b != std::string::npos) {
                return path.substr(std::max(a, b) + 1);
            } else if (a != std::string::npos) {
                return path.substr(a + 1);
            } else if (b != std::string::npos) {
                return path.substr(b + 1);
            } else {
                return path;
            }
        }
    };
}

#define __FILENAME__ Doxydown::Path::filename(__FILE__)
