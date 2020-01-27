/**
 * @file appSettings.hpp
 * @brief This header file contains defiitions and data structures
 * related to application settings.
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

#ifndef APP_SETTINGS_HPP_INCLUDED
#define APP_SETTINGS_HPP_INCLUDED

#include "Clustering/ClusteringAlgorithm.hpp"
#include "FeatureExtractors/FeatureExtractor.hpp"

#include <string>
#include <map>

namespace settings
{
    /** @brief Map containing feature selection algorithms and their names. */
    const std::map<std::string, magic::FeatureExtractor::Type> FEATURE_SELECTION_ALGORITHMS = 
    {
        {"OpenCV descriptors", magic::FeatureExtractor::OPENCV2_EXTRAXTORS},
        {"Color histogram", magic::FeatureExtractor::GLOBAL_HIST}
    };

    /** @brief Map containing feature selection algorithms and their names. */
    const std::map<std::string, magic::ClusteringAlgorithm::Type> CLUSTERING_ALGORITHMS = 
    {
        {"DBSCAN", magic::ClusteringAlgorithm::DBSCAN_ALGORITHM},
        {"k-means", magic::ClusteringAlgorithm::K_MEANS_ALGORITHM},
        {"k-medians", magic::ClusteringAlgorithm::K_MEDIANS_ALGORITHM},
        {"ROCK", magic::ClusteringAlgorithm::ROCK_ALGORITHM}
    };

    /**
     * @brief Application settings
     */
    struct UserSettings
    {
        std::string inputDir;
        std::string outputDir;
        bool includeSubdirectories = false;
        bool leaveOryginalImages = true;
        magic::FeatureExtractor::Type featureAlgorithm = magic::FeatureExtractor::GLOBAL_HIST;
        magic::ClusteringAlgorithm::Type clusterAlgorithm = magic::ClusteringAlgorithm::K_MEANS_ALGORITHM;
        unsigned short threadNumber = 1;
    };
}

#endif
