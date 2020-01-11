#ifndef IMAGE_UTILS_HPP_INCLUDED
#define IMAGE_UTILS_HPP_INCLUDED

#include "Types.hpp"

namespace magic
{
    Image loadImageFromFile(const std::string& filePath);
    std::vector<Image> loadImageBatch(const std::vector<std::string>& filePaths);
}

#endif
