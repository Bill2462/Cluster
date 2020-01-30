# This file is a part of Cluster - Application for image clustering.
# Copyright (C) 2020 Krzysztof Adamkiewicz <kadamkiewicz835@gmail.com>
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

include_directories(include)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCES
    src/ImageUtils.cpp
    
    src/DimensionRedox/DimRedoxFactory.cpp
    src/DimensionRedox/MDS.cpp
    
    src/FeatureExtractors/FeatureExtractor.cpp
    src/FeatureExtractors/GlobalHistogram.cpp
    src/FeatureExtractors/OpenCV_Descriptors.cpp
    
    src/Clustering/ClusteringAlgorithm.cpp
    src/Clustering/ROCK.cpp
    src/Clustering/DBSCAN.cpp
    
    src/Pipeline/Clustering.cpp
    src/Pipeline/FeatureExtractor.cpp
    src/Pipeline/ImageLoader.cpp
    src/Pipeline/Pipeline.cpp
    src/Pipeline/Preprocessor.cpp
    src/Pipeline/Update.cpp
    src/Pipeline/Status.cpp
    src/Pipeline/Process.cpp
    src/Pipeline/Data.cpp
    src/Pipeline/FeatureReduction.cpp
)

add_library(magic STATIC ${SOURCES})

target_link_libraries(magic ${OpenCV_LIBS})
target_link_libraries(magic mathtoolbox)
target_link_libraries(magic pycluster)
target_link_libraries(magic pthread)
