#ifndef APP_SETTINGS_HPP_INCLUDED
#define APP_SETTINGS_HPP_INCLUDED

#include <string>
#include <map>
#include <ostream>

//TODO: Add actual algorithms and not placeholder.
namespace settings
{
    /**
     * @brief Feature selection algorithms.
     */
    enum FeatureSelectionAlgorithm
    {
        INVALID_FEATURE_ALG,
        MAGIC
    };
    /** @brief Map containing feature selection algorithms and their names. */
    const std::map<std::string, FeatureSelectionAlgorithm> FEATURE_SELECTION_ALGORITHMS = 
    {
        {"invalid", INVALID_FEATURE_ALG},
        {"magic", MAGIC}
    };

    /**
     * @brief Clustering algorithms.
     */
    enum ClusteringAlgorithm
    {
        K_MEANS,
        INVALID_CLUTERING_ALG
    };
    /** @brief Map containing feature selection algorithms and their names. */
    const std::map<std::string, ClusteringAlgorithm> CLUSTERING_ALGORITHMS = 
    {
        {"K_mean", K_MEANS},
        {"INVALID_CLUTERING_ALG", INVALID_CLUTERING_ALG}
    };

    /**
     * @brief Application settings
     */
    struct UserSettings
    {
        std::string inputDir;
        std::string outputDir;
        bool includeSubdirectories = false;
        bool leaveOryginalImages = true;
        FeatureSelectionAlgorithm featureAlgorithm = INVALID_FEATURE_ALG;
        ClusteringAlgorithm clusterAlgorithm = K_MEANS;
        unsigned short threadNumber = 1;
    };
}

#endif
