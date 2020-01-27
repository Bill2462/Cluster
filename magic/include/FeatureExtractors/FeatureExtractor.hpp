/**
 * @file FeatureExtractor.hpp
 * @brief This header file contains feature extractor base class.
 * @author Krzysztof Adamkiewicz
 * @date 17/1/2020
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

#ifndef MAGIC_FEATURE_EXTRACTOR_HPP_INCLUDED
#define MAGIC_FEATURE_EXTRACTOR_HPP_INCLUDED

#include "Types.hpp"
#include <memory>
#include <atomic>

namespace magic
{
    /**
     * @brief Feature extractor base class.
     */
    class FeatureExtractor
    {
    public:
        enum Type
        {
            OPENCV2_EXTRAXTORS,
            GLOBAL_HIST,
            NONE
        };

        static std::shared_ptr<FeatureExtractor> build(Type type);
        
        /**
         * @brief Build feature vector for the image dataset.
         * @param dataset Image dataset.
         * @return Feature dataset.
         */
        virtual FeatureDataset buildFeatures(const ImageDataset& dataset) const = 0;

        void setProgressCounter(std::atomic<size_t>& progressCounter);
        
        /**
         * @brief Get the lenght of the feature vector.
         * @return Lenght of the feature vector.
         */
        virtual unsigned int featureVectorSize() const = 0;
        
    protected:
        mutable std::atomic<size_t>* progressCounter = nullptr; /** @brief Progress counter. */
    };
}

#endif
