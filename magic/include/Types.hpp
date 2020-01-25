/**
 * @file Types.hpp
 * @brief This header file contains magic library type definitions.
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

#ifndef MAGIC_TYPES_HPP_INCLUDED
#define MAGIC_TYPES_HPP_INCLUDED

#include <vector>
#include <memory>
#include <opencv2/core/core.hpp>
#include <eigen3/Eigen/Core>

namespace magic
{
    typedef std::vector<double> FeatureVector;
    
    /**
     * @brief Image structure.
     */
    struct Image
    {
        std::string path;
        cv::Mat image;
        FeatureVector featureVector;
    };

    typedef std::vector<Image> ImageDataset;
    typedef std::vector<std::shared_ptr<FeatureVector>> FeatureDataset;
    
    typedef std::vector<std::shared_ptr<Image>> Cluster;
}

#endif 
