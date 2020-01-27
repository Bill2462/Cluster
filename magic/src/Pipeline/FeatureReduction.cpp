/**
 * @file FeatureReduction.cpp
 * @brief This source file contains source code for dimensionality reduction.
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

void Pipeline::reduceFeatures()
{
    auto worker = [](FeatureDataset& featureDataset,
                     std::shared_ptr<DimReductionAlgorithm> reductor) -> FeatureDataset
    {
        return reductor->reduce(featureDataset, 2);
    };
    
    reducedFeatures = std::async(worker, std::ref(imageFeatures.second), dimensionalityReductionAlgorithm);
}
