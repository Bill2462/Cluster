/**
 * @file Status.cpp
 * @brief This source file contains source code for getting pipeline status.
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
#include <exception>

using namespace magic;

/**
 * @brief Get pipeline status.
 * @return Pipeline status,
 */
Pipeline::Status Pipeline::getStatus() const
{
    return status;
}

/**
 * @brief Get pipeline progress report.
 * @return Pipeline progress report object.
 */
Pipeline::Progress Pipeline::getProgress() const
{
    if(inputSize == 0)
        throw(std::runtime_error("Input is not loaded, cannot calculate progress!"));
    
    return 
    {
        static_cast<float>(loadedCounter.load())/inputSize,
        static_cast<float>(preprocessedCounter.load())/inputSize,
        static_cast<float>(featuredExtractedCounter.load())/inputSize,
        clusteringCompleted,
        dimRedoxCompleted
    };
}
