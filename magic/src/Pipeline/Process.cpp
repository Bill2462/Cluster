/**
 * @file Process.cpp
 * @brief This source file contains source code for starting processing.
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
#include <chrono>

using namespace magic;

/**
 * @brief Start the processing.
 * @param threads Number of threads.
 * @throw std::runtime_error If number of threads is invalid or status != READY
 * or if the data or not loaded.
 */
void Pipeline::startProcessing(unsigned int threads)
{
    if(status != READY)
        throw(std::runtime_error("Trying to start processing when status != READY"));
    
    if(threads == 0)
        throw(std::runtime_error("Number of threads cannot be equal to 0"));
    
    if(inputSize == 0)
        throw(std::runtime_error("Cannot start processing without any images loaded!"));

    loadImages();//start loading
}

/**
 * @brief Reset the entire pipeline.
 * @throw std::runtime_error If pipeline is working.
 */
void Pipeline::reset()
{
    if(status != PROCESSING_COMPLETED && status != READY)
        throw(std::runtime_error("Trying to call reset method when pipeline is working."));

    inputSize = 0;
    threads = 1;
    batchIntervals.clear();
    workerPool.clear();

    loadedCounter = 0;
    preprocessedCounter = 0;
    featuredExtractedCounter = 0;
    clusteringCompleted = false;
    dimRedoxCompleted = false;

    imagePaths.first.unlock();
    imagePaths.second.clear();

    images.first.unlock();
    images.second.clear();
    
    imageFeatures.first.unlock();
    imageFeatures.second.clear();
    
    reducedFeatures.get().clear();
    clusters.get().clear();
    
    status = READY;
}

/**
 * @brief Check if current pipeline stage is finished.
 * @return True if current pipeline step is finished.
 */
bool Pipeline::isCurrentStageFinished()
{
    std::future_status asyncStatus;
    switch(status)
    {
        case LOADING_IMAGES:
            return loadedCounter.load() == inputSize;

        case PREPROCESSING_IMAGES:
            return preprocessedCounter.load() == inputSize;
            
        case GENERATING_FEATURES:
            return featuredExtractedCounter.load() == inputSize;
            
        case PERFORMING_CLUSTERING:
            asyncStatus = clusters.wait_for(std::chrono::nanoseconds(1));
            if(asyncStatus == std::future_status::ready)
            {
                clusteringCompleted = true;
                return true;
            }
            return false;
            
        case PERFORMING_DIM_REDOX:
            asyncStatus = reducedFeatures.wait_for(std::chrono::nanoseconds(1));
            if(asyncStatus == std::future_status::ready)
            {
                dimRedoxCompleted = true;
                return true;
            }
            return false;
        
        default:
            return true;
    }

    return false;
}
