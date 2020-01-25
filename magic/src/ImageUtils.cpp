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
std::shared_ptr<Image> magic::loadImageFromFile(const std::string& filePath)
{
    cv::Mat img = cv::imread(filePath);
    if(img.data == nullptr)
        throw(std::runtime_error("Cannot load file: " + filePath));
    
    std::shared_ptr<Image> ptr(new Image);
    ptr->path = filePath;
    ptr->image = img;
    return ptr;
}

/**
 * @brief Load a batch of images.
 * @param filePaths
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
 * @brief Generate features dataset.
 * @param dataset Image daaset.
 * @return Feature dataset.
 */
FeatureDataset magic::generateFeaturesDataset(const ImageDataset& dataset)
{
    FeatureDataset featureDataset;
    featureDataset.reserve(dataset.size());
    
    for(auto it=dataset.begin(); it<dataset.end(); it++)
        featureDataset.push_back(std::shared_ptr<FeatureVector>(new FeatureVector((*it)->featureVector)));

    return featureDataset;
}