/**
 * @file FeatureExtractor.cpp
 * @brief This source file contains code for feature extractor base class.
 * @author Krzysztof Adamkiewicz
 * @date @date 17/1/2020
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

#include "FeatureExtractors/FeatureExtractor.hpp"
#include "FeatureExtractors/GlobalHist.hpp"
#include "FeatureExtractors/OpenCV_Descriptors.hpp"
#include <exception>

using namespace magic;

/**
 * @brief Build feature extractor.
 * @param type Feature extractor type.
 * @return Shared pointer to the feature extractor object.
 * @throw std::runtime_error If the type of the algorithm is invalid.
 */
std::shared_ptr<FeatureExtractor> FeatureExtractor::build(FeatureExtractor::Type type)
{
    switch(type)
    {
        case FeatureExtractor::OPENCV2_EXTRAXTORS:
            return std::shared_ptr<FeatureExtractor>(new OpenCV_Descriptor());

        case FeatureExtractor::GLOBAL_HIST:
            return std::shared_ptr<FeatureExtractor>(new OpenCV_Descriptor());

        default:
            break;
    }
    
    throw(std::runtime_error("Invalid feature extraction algorithm type"));
    
    return std::shared_ptr<FeatureExtractor>(nullptr);
}

/**
 * @brief Set progress variable counter.
 * @param progressCounter Progress counter atomic variable.
 */
void FeatureExtractor::setProgressCounter(std::atomic<size_t>& progressCounter)
{
    this->progressCounter = &progressCounter;
}
