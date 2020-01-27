/**
 * @file Clustering.cpp
 * @brief This source file contains source code for the general methods for the pipeline.
 * @author Krzysztof Adamkiewicz
 * @date 26/1/2020
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

#include "Pipeline.hpp" 

using namespace magic;

/**
 * @brief Build pipeline.
 * @param dimRedoxType Type of the dimensionality reduction algorithm.
 * @param clusteringAlgorithmType Type of the clustering algorithm.
 * @param featureExtractorType Type of the feature extractor.
 */
Pipeline::Pipeline(DimReductionAlgorithm::Type dimRedoxType,
                   ClusteringAlgorithm::Type clusteringAlgorithmType,
                   FeatureExtractor::Type featureExtractorType)
{
    clusteringAlgorithm = ClusteringAlgorithm::build(clusteringAlgorithmType);
    dimensionalityReductionAlgorithm = DimReductionAlgorithm::build(dimRedoxType);
    featureExtractor = FeatureExtractor::build(featureExtractorType);
}

/**
 * @brief Build pipeline that does not perform dimensionality reduction;
 * @param clusteringAlgorithmType Type of the clustering algorithm.
 * @param featureExtractorType Type of the feature extractor.
 */
Pipeline::Pipeline(ClusteringAlgorithm::Type clusteringAlgorithmType,
                   FeatureExtractor::Type featureExtractorType)
{
    clusteringAlgorithm = ClusteringAlgorithm::build(clusteringAlgorithmType);
    dimensionalityReductionAlgorithm = std::shared_ptr<DimReductionAlgorithm>(nullptr);
    featureExtractor = FeatureExtractor::build(featureExtractorType);
}
