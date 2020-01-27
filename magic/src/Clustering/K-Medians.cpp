/**
 * @file K-Medians.cpp
 * @brief This source file contains source code for K-Medians clustering algorithm.
 * @author Krzysztof Adamkiewicz
 * @date 25/1/2020
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

#include "pyclustering/cluster/kmedians.hpp"
#include "Clustering/K-Medians.hpp"

using namespace magic;

/**
 * @brief Perform clustering operation using K-Medians algorithm.
 * @param features Points.
 * @return Vector of clusters.
 */
std::vector<Cluster> K_Medians::cluster(const FeatureDataset& dataset) const
{
    std::vector<FeatureVector> features = copyFeatures(dataset);
    pyclustering::clst::cluster_data clusters;
    
    //perform clustering
    pyclustering::clst::kmedians kmedians;
    kmedians.process(features, clusters);
    
    //export clustering results
    return exportClusters(clusters, dataset);
}
