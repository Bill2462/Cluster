/**
 * @file GlobalHistogram.cpp
 * @brief This source file contains code for describing dataset using global color histogram.
 * @author Krzysztof Adamkiewicz
 * @date @date 18/1/2020
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

#include "FeatureExtractors/FeatureExtractor.hpp"
#include "FeatureExtractors/GlobalHist.hpp"
#include <exception>
#include <opencv2/imgproc/imgproc.hpp>

using namespace magic;
/**
 * @brief Set how many bins do we want in our histogram.
 * @param count Number of bins that we want in our histogram.
 * @throw std::runtime_error If number of bins is invalid.
 */
void GlobalHistogram::setBinCount(unsigned int count)
{
    if(count == 0)
        throw(std::runtime_error("Number of bins is invalid! (must be > 0, got 0)"));
    
    binCount = count;
}

/**
 * @brief Get bin count setting.
 * @return Bin count setting.
 */
unsigned int GlobalHistogram::getBinCount() const
{
    return binCount;
}

/**
 * @brief Compute color histogram features for the entire dataset.
 * @param dataset Image dataset for which we want to compute all the features.
 */
void GlobalHistogram::buildFeatures(ImageDataset& dataset) const
{
    cv::Mat hsvImage;
    cv::Mat channels[3];
    cv::Mat hist;
    cv::Mat dummy;
    for(auto it=dataset.begin(); it<dataset.end(); it++)
    {
        //convert image to HSV
        cv::cvtColor((*it).image, hsvImage, cv::COLOR_RGB2HSV);
        
        //extract channels
        cv::split(hsvImage, channels);
       
        //compute histogram
        const float range[] = {0, 256};
        const float* histRange = {range};
        const int histSize = 256;
        const int sourceChannelNum = 1;
        const int channelDim = 0;
        const int histogramDimensionality = 1;
        const bool uniform = true;
        const bool accumulate = false;
        cv::calcHist(&channels[0], sourceChannelNum, &channelDim, dummy, hist, histogramDimensionality, &histSize, &histRange, uniform, accumulate);
        
        //save it into the vector
        (*it).featureVector.reserve(hist.cols);
        for(int x=0; x<hist.cols; x++)
            (*it).featureVector.push_back(hist.at<double>(0, x));
    }
}
