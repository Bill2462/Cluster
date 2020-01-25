/**
 * @file DimRedoxFactory.cpp
 * @brief This source file contains source code for the dimensionality algorithm factory.
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

#include "DimensionRedox/MDS.hpp"
#include <exception>

using namespace magic;

/**
 * @brief Dimensionality reductor factory.
 * @param type Type of the dimensionality reduction algorithm. 
 * @return Returns a shared pointer to the dimensionality reduction algorithm.
 * @throw std::runtime_error If the type of the algorithm is invalid.
 */
std::shared_ptr<DimReductionAlgorithm> magic::DimReductionAlgorithm::build(DimReductionAlgorithm::Type type)
{
    switch(type)
    {
        case MDS_ALGORITHM:
            return std::shared_ptr<DimReductionAlgorithm>(new MDS);

        default:
            break;
    };
    
    throw(std::runtime_error("Invalid dimensionality reduction algorithm type"));
    
    return std::shared_ptr<DimReductionAlgorithm>(nullptr);
}
