/**
 * @file OpenCV_Descriptors.hpp
 * @brief This header file contains openCV descriptor class.
 * @author Krzysztof Adamkiewicz
 * @date 17/1/2020
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

#ifndef MAGIC_OPENCV_DESCRIPTOR_HPP_INCLUDED
#define MAGIC_OPENCV_DESCRIPTOR_HPP_INCLUDED

#include "FeatureExtractor.hpp"
#include <opencv2/xfeatures2d.hpp>

namespace magic
{
    /**
     * @brief Class implementing feature extraction using openCV VGG descriptor.
     */
    class OpenCV_Descriptor : public FeatureExtractor
    {
    public:
        OpenCV_Descriptor();
        void buildFeatures(ImageDataset& dataset) const override;
        unsigned int featureVectorSize() const override;
        
        void setKeypointCount(unsigned int count);
        unsigned int getKeypointCount() const;
        
    private:
        cv::Ptr<cv::xfeatures2d::VGG> vgg; /** @brief VGG descriptor. */
        unsigned int keypointCount = 5; /** @brief How many keypoints do we want to use. */
    };
}
#endif
