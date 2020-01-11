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

#include <string>
#include <map>
#include <ostream>

//TODO: Add actual algorithms and not placeholder.
namespace settings
{
    /**
     * @brief Feature selection algorithms.
     */
    enum FeatureSelectionAlgorithm
    {
        INVALID_FEATURE_ALG,
        MAGIC
    };
    /** @brief Map containing feature selection algorithms and their names. */
    const std::map<std::string, FeatureSelectionAlgorithm> FEATURE_SELECTION_ALGORITHMS = 
    {
        {"invalid", INVALID_FEATURE_ALG},
        {"magic", MAGIC}
    };

    /**
     * @brief Clustering algorithms.
     */
    enum ClusteringAlgorithm
    {
        K_MEANS,
        INVALID_CLUTERING_ALG
    };
    /** @brief Map containing feature selection algorithms and their names. */
    const std::map<std::string, ClusteringAlgorithm> CLUSTERING_ALGORITHMS = 
    {
        {"K_mean", K_MEANS},
        {"INVALID_CLUTERING_ALG", INVALID_CLUTERING_ALG}
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
        FeatureSelectionAlgorithm featureAlgorithm = INVALID_FEATURE_ALG;
        ClusteringAlgorithm clusterAlgorithm = K_MEANS;
        unsigned short threadNumber = 1;
    };
}

#endif
