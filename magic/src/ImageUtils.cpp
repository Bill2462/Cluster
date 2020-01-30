/**
 * @file ImageUtils.cpp
 * @brief This source file contains source code for the image utility functions.
 * @author Krzysztof Adamkiewicz
 * @date 11/1/2020
 */

// This file is a part of Cluster - Application for image clustering.
// Copyright (C) 2020 Krzysztof Adamkiewicz <kadamkiewicz835@gmail.com>
// 
// This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <http://www.gnu.org/licenses/>.

#include "ImageUtils.hpp"
#include <exception>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <algorithm>

using namespace magic;

/**
 * @brief Allowed image extensions.
 */
inline const std::vector<std::string> ALLOWED_FILE_EXTENSIONS = 
{
    ".bmp",
    ".dib",
    ".jpeg",
    ".jpg",
    ".jpe",
    ".jp2",
    ".png",
    ".web",
    ".pbm",
    ".pgm",
    ".ppm",
    ".pxm",
    ".pnm",
    ".pfm",
    ".sr",
    ".ras",
    ".tiff",
    ".tif",
    ".exr",
    ".hdr",
    ".pic"
};

/**
 * @brief Check if image format is supported.
 * @param fileName Name of the file.
 * @return True if file format is supported.
 */
inline bool isFileFormatSupported(const std::string& fileName)
{
    std::size_t found = fileName.find_last_of(".");
    if(found == std::string::npos)
        return false;
    
    std::string extension = fileName.substr(found);
    for(auto it=ALLOWED_FILE_EXTENSIONS.begin(); it<ALLOWED_FILE_EXTENSIONS.end(); it++)
    {
        if((*it) == extension)
            return true;
    }
    
    return false;
}

/**
 * @brief Load a single image.
 * @param filePath Path to the image.
 * @return Image object.
 * @throw std::runtime_error If error occurs dring loading.
 */
Image magic::loadImageFromFile(const std::string& filePath)
{
    cv::Mat img = cv::imread(filePath);
    if(img.data == nullptr)
        throw(std::runtime_error("Cannot load file: " + filePath));

    return {filePath, img};
}

/**
 * @brief Load a batch of images.
 * @param filePaths Vector of image paths.
 * @return Vector of image objects.
 * @throw std::runtime_error If error occurs during loading.
 */
ImageDataset magic::loadImageBatch(const std::vector<std::string>& filePaths)
{
    ImageDataset images;
    
    for(auto it=filePaths.begin(); it<filePaths.end(); it++)
    {
        if(!isFileFormatSupported(*it))
            continue;
        
        images.push_back(magic::loadImageFromFile(*it));
    }
    
    return images;
}

/**
 * @brief Load a batch of images with a progress counter.
 * @param filePaths Vector of image paths.
 * @return Vector of image objects.
 * @throw std::runtime_error If error occurs during loading.
 */
ImageDataset magic::loadImageBatch(const std::vector<std::string>& filePaths, std::atomic<size_t>& progressCounter)
{
    ImageDataset images;
    
    for(auto it=filePaths.begin(); it<filePaths.end(); it++)
    {
        progressCounter.fetch_add(1, std::memory_order_relaxed);//increment progress counter
        if(!isFileFormatSupported(*it))
            continue;

        images.push_back(magic::loadImageFromFile(*it));
    } 
    
    return images;
}

/**
 * @brief Resize the entire dataset.
 * @param images Image dataset.
 * @param width Width of the output images.
 * @param height Height of the output images.
 */
void magic::resizeDataset(ImageDataset& images, unsigned int width, unsigned int height)
{
    for(auto it=images.begin(); it<images.end(); it++)
    {
        cv::resize((*it).image, (*it).image, cv::Size(width, height), cv::INTER_LINEAR);
    }
}

/**
 * @brief Resize the entire dataset with the progress counter.
 * @param images Image dataset.
 * @param progressCounter Progress counter.
 * @param width Width of the output images.
 * @param height Height of the output images.
 */
void magic::resizeDataset(ImageDataset& images, std::atomic<size_t>& progressCounter, unsigned int width, unsigned int height)
{
    for(auto it=images.begin(); it<images.end(); it++)
    {
        cv::resize((*it).image, (*it).image, cv::Size(width, height), cv::INTER_LINEAR);
        progressCounter.fetch_add(1, std::memory_order_relaxed);
    }
}
