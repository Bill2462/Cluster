
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set(SOURCES
  main.cpp
  mainwindow.cpp
  mainwindow.h
  mainwindow.ui
)

add_executable(app ${SOURCES})

target_link_libraries(app PRIVATE Qt5::Widgets)
