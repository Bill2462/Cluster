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

namespace magic
{
    /**
     * @brief Feature extractor class.
     */
    class FeatureExtractor
    {
    public:
        enum Type
        {
            OPENCV2_EXTRAXTORS,
            GLOBAL_HIST,
            COLOR_WISE
        };

        static std::shared_ptr<FeatureExtractor> build(Type type);
        
        virtual void buildFeatures(ImageDataset& dataset) const = 0;
    };
}

#endif
