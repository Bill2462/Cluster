/**
 * @file Data.cpp
 * @brief This source file contains source code for importing data into the pipeline and extracting them.
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
 * @brief Set the input paths,
 * @param paths Paths to the images.
 * @throw std::runtime_error If pipeline status is != READY.
 */
void Pipeline::setInput(const std::vector<std::string>& paths)
{
    if(getStatus() != READY)
        throw(std::runtime_error("Cannot set pipeline input when pipeline status != READY"));
    
    imagePaths.second = paths;
    inputSize = paths.size();
}

/**
 * @brief Get copy of computed clusters.
 * @return Clusters.
 * @throw std::runtime_error If pipeline status is != PROCESSING_COMPLETED.
 */
std::vector<Cluster> Pipeline::getClusters() const
{
    if(getStatus() != PROCESSING_COMPLETED)
        throw(std::runtime_error("Cannot get clusters when pipeline status != PROCESSING_COMPLETED"));

    return std::vector<Cluster>(clusters.get());
}

/**
 * @brief Get copy of reduced features.
 * @return Reduced features.
 * @throw std::runtime_error If pipeline status is != PROCESSING_COMPLETED.
 */
FeatureDataset Pipeline::getReducedFeatures() const
{
    if(getStatus() != PROCESSING_COMPLETED)
        throw(std::runtime_error("Cannot get reduced features when pipeline status != PROCESSING_COMPLETED"));

    return FeatureDataset(reducedFeatures.get());
}

/**
 * @brief Generate intervals batch intervals.
 * @throw std::runtime_error If pipeline status != READY or if the data are not loaded.
 */
void Pipeline::generateBatchIntervals()
{
    if(inputSize == 0)
        throw(std::runtime_error("Cannot generate batch intervals when input is not loaded"));

    if(getStatus() != READY)
        throw(std::runtime_error("Cannot generate batch intervals when pipeline status != READY"));
    
    //if size of the input is smaller than number of threads, fall back to 1 thread
    if(threads > inputSize)
        threads = 1;

    const size_t batchSize = inputSize/threads;
    for(unsigned int i=0; i<threads; i++)
    {
        if(i == threads-1)
            batchIntervals.push_back(std::make_pair(i*batchSize, inputSize)); //last batch must be a little larger to cover the whole dataset
        else
            batchIntervals.push_back(std::make_pair(i*batchSize, (i+1)*batchSize));
    }
}
