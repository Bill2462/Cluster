/**
 * @file MDS.hpp
 * @brief This header file contains MDS algorithm class.
 * @author Krzysztof Adamkiewicz
 * @date 16/1/2020
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

#ifndef MDS_HPP_INCLUDED
#define MDS_HPP_INCLUDED

#include <eigen3/Eigen/Core>
#include "DimensionalityRedox.hpp"

namespace magic
{
    /**
     * @brief Multidimensional scaling (MDS) algorithm.
     */
    class MDS : public magic::DimReductionAlgorithm
    {
    public:
        void reduce(FeatureDataset& dataset, unsigned short outputDim) override;
        
    private:
        void computeDistanceMatrix(const FeatureDataset& points);
        
        Eigen::MatrixXd distanceMatrix; /** @brief Distance matrix. */
    };
}

#endif
