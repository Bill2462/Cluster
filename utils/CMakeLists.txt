include_directories(include)

set(SOURCES
  src/utils.cpp
)

add_library(utils STATIC ${SOURCES})
