#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <vector>
#include <string>
#include <exception>

namespace utils
{
    std::vector<std::string> listFiles(const std::string& path, bool includeSubdirs);
    void moveFile(const std::string& source, const std::string& dest);
    void copyFile(const std::string& source, const std::string& dest);
    void makeDir(const std::string& path);
}

#endif
