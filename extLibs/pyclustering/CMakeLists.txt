
find_package(Doxygen)
    if(DOXYGEN_FOUND)
        #set input and output files
        set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doc)

        #request to configure the file
        configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

        #note the option ALL which allows to build the docs together with the application
        add_custom_target(doc_cluster
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
            WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Generating documentation with Doxygen"
            VERBATIM)
    else (DOXYGEN_FOUND)
        message(WARNING "Doxygen not installed, documentation build aborted!")
endif(DOXYGEN_FOUND)

include_directories(include)

set(SOURCES
src/cluster/bsas.cpp
src/cluster/fcm.cpp
src/cluster/kmedoids.cpp
src/cluster/silhouette.cpp
src/cluster/clique_block.cpp
src/cluster/gmeans.cpp
src/cluster/mbsas.cpp 
src/cluster/silhouette_ksearch.cpp
src/cluster/clique.cpp
src/cluster/hsyncnet.cpp
src/cluster/optics.cpp
src/cluster/somsc.cpp
src/cluster/cluster_algorithm.cpp
src/cluster/kmeans.cpp
src/cluster/optics_descriptor.cpp
src/cluster/syncnet.cpp
src/cluster/cluster_data.cpp
src/cluster/kmeans_data.cpp
src/cluster/ordering_analyser.cpp
src/cluster/ttsas.cpp
src/cluster/cure.cpp
src/cluster/kmeans_plus_plus.cpp
src/cluster/random_center_initializer.cpp
src/cluster/xmeans.cpp

src/container/adjacency_bit_matrix.cpp
src/container/adjacency_factory.cpp
src/container/adjacency_matrix.cpp
src/container/kdnode.cpp
src/container/adjacency_connector.cpp
src/container/adjacency_list.cpp
src/container/adjacency_weight_list.cpp
src/container/kdtree.cpp

src/differential/differ_factor.cpp

src/interface/agglomerative_interface.cpp
src/interface/interface_property.cpp
src/interface/pyclustering_package.cpp
src/interface/bsas_interface.cpp
src/interface/kmeans_interface.cpp
src/interface/rock_interface.cpp
src/interface/clique_interface.cpp
src/interface/kmedians_interface.cpp
src/interface/silhouette_interface.cpp
src/interface/cure_interface.cpp
src/interface/kmedoids_interface.cpp
src/interface/som_interface.cpp
src/interface/dbscan_interface.cpp
src/interface/legion_interface.cpp
src/interface/sync_interface.cpp
src/interface/elbow_interface.cpp
src/interface/mbsas_interface.cpp
src/interface/syncnet_interface.cpp
src/interface/fcm_interface.cpp
src/interface/metric_interface.cpp
src/interface/syncpr_interface.cpp
src/interface/gmeans_interface.cpp
src/interface/optics_interface.cpp
src/interface/ttsas_interface.cpp
src/interface/hhn_interface.cpp
src/interface/pcnn_interface.cpp
src/interface/xmeans_interface.cpp
src/interface/hsyncnet_interface.cpp
src/interface/pyclustering_interface.cpp

src/nnet/dynamic_analyser.cpp
src/nnet/hhn.cpp
src/nnet/legion.cpp
src/nnet/pcnn.cpp
src/nnet/som.cpp
src/nnet/sync.cpp
src/nnet/syncpr.cpp

src/parallel/spinlock.cpp
src/parallel/task.cpp
src/parallel/thread_executor.cpp
src/parallel/thread_pool.cpp

src/utils/linalg.cpp
src/utils/math.cpp
src/utils/metric.cpp
src/utils/random.cpp
src/utils/stats.cpp
)

add_library(pycluster STATIC ${SOURCES})
