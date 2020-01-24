######################################################################
# Prerequisites
######################################################################

find_package(Eigen3 REQUIRED)
if((NOT TARGET Eigen3::Eigen) AND (DEFINED EIGEN3_INCLUDE_DIR))
	add_library(AliasEigen3 INTERFACE)
	target_include_directories(AliasEigen3 INTERFACE ${EIGEN3_INCLUDE_DIR})
	add_library(Eigen3::Eigen ALIAS AliasEigen3)
endif()

find_package(Doxygen)
    if(DOXYGEN_FOUND)
        #set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doc)

        #request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

        #note the option ALL which allows to build the docs together with the application
        add_custom_target(doc_mathtoolbox
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating documentation with Doxygen"
            VERBATIM)
    else (DOXYGEN_FOUND)
        message(WARNING "Doxygen not installed, documentation build aborted!")
endif(DOXYGEN_FOUND)

######################################################################
# Core library
######################################################################

file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/include/mathtoolbox/*.hpp)
file(GLOB sources ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_library(mathtoolbox STATIC ${headers} ${sources})
target_link_libraries(mathtoolbox PUBLIC Eigen3::Eigen)
target_include_directories(mathtoolbox PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
