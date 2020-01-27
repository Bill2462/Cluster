/**
 * @file Preprocessor.cpp
 * @brief This source file contains source code for the preprocessing stage of the pipeline.
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
#include "ImageUtils.hpp"
#include <algorithm>

using namespace magic;

void Pipeline::preprocessImage()
{
    auto worker = [](std::pair<size_t, size_t>&range,
                          std::atomic<size_t>& progressCounter,
                          ImagePool& images)
    {
        //generate path bath
        images.first.lock();
        ImageDataset imageBatch
        (
            images.second.begin() + range.first,
            images.second.begin() + range.second
        );
        images.first.unlock();
        
        //perform image loading
        resizeDataset(imageBatch, progressCounter, 300, 300);
        
        //insert result
        images.first.lock();
        std::copy(imageBatch.begin(), imageBatch.end(), images.second.begin() + range.first);
        images.first.unlock();
    };
    
    for(unsigned int i=0; i<threads; i++)
    {
        workerPool.push_back
        (
            std::thread
            (
                worker,
                std::ref(batchIntervals[i]),
                std::ref(preprocessedCounter),
                std::ref(images)
            )
        );
    }
}
