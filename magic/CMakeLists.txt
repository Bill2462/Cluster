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
include_directories(../extLibs/mathtoolbox/include)

set(SOURCES
    src/ImageUtils.cpp
    
    src/DimensionRedox/DimRedoxFactory.cpp
    src/DimensionRedox/MDS.cpp
)

add_library(magic STATIC ${SOURCES})

link_directories("../extLibs/build/mathtoolbox/")
target_link_libraries(magic ${OpenCV_LIBS})
target_link_libraries(magic mathtoolbox)
