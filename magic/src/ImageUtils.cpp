#include "ImageUtils.hpp"
#include <exception>
#include <opencv2/opencv.hpp>

using namespace magic;

/**
 * @brief Load a single image.
 * @param filePath Path to the image.
 * @return Image object.
 * @throw std::runtime_error If error occurs dring loading.
 */
Image magic::loadImageFromFile(const std::string& filePath)
{
    Image img = cv::imread(filePath);
    if(img.data == nullptr)
        throw(std::runtime_error("Cannot load file: " + filePath));
    
    return img;
}

/**
 * @brief Load a batch of images.
 * @param filePaths
 * @return Vector of image objects.
 * @throw std::runtime_error If error occurs during loading.
 */
std::vector<Image> magic::loadImageBatch(const std::vector<std::string>& filePaths)
{
    std::vector<Image> images;
    
    for(auto it=filePaths.begin(); it<filePaths.end(); it++)
        images.push_back(magic::loadImageFromFile(*it));
    
    return images;
}
