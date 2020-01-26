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

using namespace magic;

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
    images.reserve(filePaths.size());
    
    for(auto it=filePaths.begin(); it<filePaths.end(); it++)
        images.push_back(magic::loadImageFromFile(*it));
    
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
    images.reserve(filePaths.size());
    
    for(auto it=filePaths.begin(); it<filePaths.end(); it++)
    {
        images.push_back(magic::loadImageFromFile(*it));
        progressCounter.fetch_add(1, std::memory_order_relaxed);//increment progress counter
    }
    
    return images;
}
