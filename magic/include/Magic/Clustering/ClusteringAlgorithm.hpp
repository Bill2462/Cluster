/**
 * @file ClusteringAlgorithm.hpp
 * @brief This header file contains Clustering algorithm class.
 * @author Krzysztof Adamkiewicz
 * @date 23/1/2020
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

#ifndef CLUSTERING_ALGORITHM_HPP_INCLUDED
#define CLUSTERING_ALGORITHM_HPP_INCLUDED

#include <vector>
#include <memory>
#include "pyclustering/cluster/cluster_data.hpp"
#include "../Types.hpp"

namespace magic
{
    /**
     * @brief Clustering algorithm base class.
     */
    class ClusteringAlgorithm
    {
    public:
        /**
         * @brief Clustering algorithm type.
         */
        enum Type
        {
            DBSCAN_ALGORITHM,
            ROCK_ALGORITHM,
            NONE
        };
        static std::shared_ptr<ClusteringAlgorithm> build(Type type);
        
        /**
         * @brief Perform clustering on image dataset.
         * @param dataset Image dataset with computed features.
         * @return Clusters found.
         */
        virtual std::vector<Cluster> cluster(const FeatureDataset& dataset) const = 0;
        
        virtual ~ClusteringAlgorithm();
        
    protected:
        std::vector<FeatureVector> copyFeatures(const FeatureDataset& dataset) const;
        std::vector<Cluster> exportClusters(const pyclustering::clst::cluster_data& clusters, const FeatureDataset& dataset) const;
    };
}

#endif
