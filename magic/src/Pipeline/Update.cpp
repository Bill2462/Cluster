/**
 * @file Update.cpp
 * @brief This source file contains source code for updating pipeline.
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
 * @brief Update pipeline state.
 */
void Pipeline::update()
{
    if(!isCurrentStageFinished())
        return;
    
    //if processing is finished or not started, return
    if(getStatus() == PROCESSING_COMPLETED || getStatus() == READY)
        return;
    
    //join all threads that are currently running
    for(auto it=workerPool.begin(); it<workerPool.end(); it++)
        (*it).join();

    //start next stage of the processing
    switch(status)
    {
        case LOADING_IMAGES:
            status = PREPROCESSING_IMAGES;
            preprocessImage();
            break;

        case PREPROCESSING_IMAGES:
            status = GENERATING_FEATURES;
            extractFeatures();
            break;

        case GENERATING_FEATURES:
            status = PERFORMING_CLUSTERING;
            cluster();
            break;

        case PERFORMING_CLUSTERING:
            status = PERFORMING_DIM_REDOX;
            reduceFeatures();
            break;

        case PERFORMING_DIM_REDOX:
            status = PROCESSING_COMPLETED;
            break;
        
        default:
            break;
    }
}
