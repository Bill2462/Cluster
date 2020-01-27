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

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets PrintSupport REQUIRED)

include_directories(qcustomplot)
include_directories(${CMAKE_SOURCE_DIR}/magic/include)

set(SOURCES
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
  mainWindow_events.cpp
  progressdialog.cpp
  qcustomplot/qcustomplot.cpp
)

add_executable(app ${SOURCES})

find_library(${CMAKE_SOURCE_DIR} utils)
find_library(${CMAKE_SOURCE_DIR} magic)
target_link_libraries(app PRIVATE utils)
target_link_libraries(app PRIVATE magic)
target_link_libraries(app PRIVATE Qt5::Widgets)
target_link_libraries(app PRIVATE Qt5::PrintSupport)
