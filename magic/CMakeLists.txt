include_directories(include)

find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

set(SOURCES
    src/ImageUtils.cpp
)

add_library(magic STATIC ${SOURCES})
target_link_libraries(magic ${OpenCV_LIBS})
