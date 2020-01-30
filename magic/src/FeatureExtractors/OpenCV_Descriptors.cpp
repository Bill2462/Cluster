/**
 * @file OpenCV_Descriptors.cpp
 * @brief This source file contains code for describing dataset using KAZE descriptor.
 * @author Krzysztof Adamkiewicz
 * @date @date 23/1/2020
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

#include "FeatureExtractors/OpenCV_Descriptors.hpp"
#include <exception>
#include <algorithm>
#include <cmath>

using namespace magic;

OpenCV_Descriptor::OpenCV_Descriptor()
{
    kaze = cv::KAZE::create();
}

/**
 * @brief Set how many keypoints is the descriptor going to use.
 * @param count Number of keypoints.
 * @throw std::runtime_error If number of keypoints is equal to 0.
 */
void OpenCV_Descriptor::setKeypointCount(unsigned int count)
{
    if(count == 0)
        throw(std::runtime_error("Number of keypoints is invalid! (must be > 0, got 0)"));
    
    keypointCount = count;
}

/**
 * @brief Get number of keypoints the descriptor is using.
 * @return Number of keypoints.
 */
unsigned int OpenCV_Descriptor::getKeypointCount() const
{
    return keypointCount;
}

/**
 * @brief Get feature vector size.
 * @return Feature vector size.
 */
unsigned int OpenCV_Descriptor::featureVectorSize() const
{
    return keypointCount*64;
}

/**
 * @brief Compute OpenCV descriptors for the entire dataset.
 * @param dataset Dataset for which we want to compute the features.
 * @return Feature dataset.
 */
FeatureDataset OpenCV_Descriptor::buildFeatures(const ImageDataset& dataset) const
{
    FeatureDataset featureDataset;
    featureDataset.reserve(dataset.size());

    std::vector<cv::KeyPoint> keyPoints;
    FeatureVector featureVector;
    cv::Mat features;
    
    for(auto it=dataset.begin(); it<dataset.end(); it++)
    {
        //extract keypoints
        kaze->detect((*it).image, keyPoints);
        
        //sort keypoints by the response, the higher response, the better the keypoint
        std::sort(keyPoints.begin(), keyPoints.end(), [](auto& a, auto& b) ->bool { return a.response > b.response; });
        
        //truncate the keypoints vector, we will leave max keypointCount vector
        if(keyPoints.size() > keypointCount)
            keyPoints.resize(keypointCount);
        
        //compute features
        kaze->compute((*it).image, keyPoints, features);

        //flatten the features matrix 
        featureVector.assign(features.datastart, features.dataend);
        
        //truncate if necessary
        if(featureVector.size() > featureVectorSize())
            featureVector.resize(featureVectorSize());
        
        //add 0's to the end of the matrix to match the size if necessary
        if(featureVector.size() < featureVectorSize())
        {
            for(size_t i=featureVector.size(); i<featureVectorSize(); i++)
                featureVector.push_back(0);
        }
        
        ImageFeature feature;
        feature.path = (*it).path;
        feature.featureVector = featureVector;

        featureDataset.push_back(feature);

        if(progressCounter)
            progressCounter->fetch_add(1, std::memory_order_relaxed);//increment progress counter
    }
    
    return featureDataset;
}
