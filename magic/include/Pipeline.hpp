/**
 * @file Pipeline.hpp
 * @brief This header file contains processing pipeline class.
 * @author Krzysztof Adamkiewicz
 * @date 25/1/2020
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

#ifndef PIPELINE_HPP_INCLUDED
#define PIPELINE_HPP_INCLUDED

#include <atomic>
#include <mutex>
#include <thread>
#include <utility>
#include <future>
#include "Types.hpp"
#include "Clustering/ClusteringAlgorithm.hpp"
#include "DimensionRedox/DimensionalityRedox.hpp"
#include "FeatureExtractors/FeatureExtractor.hpp"

namespace magic
{
    /**
     * @brief Processing pipeline.
     */
    class Pipeline
    {
    public:
        Pipeline(DimReductionAlgorithm::Type dimRedoxType,
                 ClusteringAlgorithm::Type clusteringAlgorithmType,
                 FeatureExtractor::Type featureExtractorType);
        
        Pipeline(ClusteringAlgorithm::Type clusteringAlgorithmType,
                 FeatureExtractor::Type featureExtractorType);
        
        void setInput(const std::vector<std::string>& paths);
        std::vector<Cluster> getClusters() const;
        FeatureDataset getReducedFeatures() const;
        
        void update();
        void startProcessing(unsigned int threads);
        void resetProcessing();
        
        /**
         * @brief Pipeline status.
         */
        enum Status
        {
            READY,
            LOADING_IMAGES,
            PREPROCESSING_IMAGES,
            GENERATING_FEATURES,
            PERFORMING_CLUSTERING,
            PERFORMING_DIM_REDOX,
            PROCESSING_COMPLETED
        };
        Status getStatus() const;
        
        /**
         * @brief Clustering pipeline progress report.
         */
        struct Progress
        {
            float loadedingState= 0;
            float preprocessingState = 0;
            float featuresExtractionState = 0;
            bool clusteringCompleted = false;
            bool dimRedoxCompleted = false;
        };
        Progress progress() const;

    private:
        using ImagePathPool = std::pair<std::mutex, std::vector<std::string>>;
        using ImagePool = std::pair<std::mutex, ImageDataset>;
        using FeaturePool = std::pair<std::mutex, FeatureDataset>;
        
        //stages
        void loadImages();
        void preprocessImage();
        void extractFeatures();
        void cluster();
        void reduceFeatures();
        unsigned int threads = 1; /** @brief Number of threads. */
        std::vector<std::thread> workerPool; /** @brief All currently running threads. */

        //progress counters
        size_t inputSize = 0; /** @brief Size of the input. */
        std::atomic<size_t> loadedCounter; /** @brief Counter of the loaded images. */
        std::atomic<size_t> preprocessedCounter; /** @brief Counter of the preprocessed images. */
        std::atomic<size_t> featuredExtractedCounter; /** @brief Counter of the extracted features. */
        bool clusteringCompleted = false; /** @brief Is clustering completed. */
        bool dimRedoxCompleted = false; /** @brief Is dimensionality reduction completed. */
        
        //data storage
        ImagePathPool imagePaths; /** @brief Paths to images ordered in batches. */
        ImagePool images; /** @brief Images dataset. */
        FeaturePool imageFeatures; /** @brief Image features. */
        std::future<FeatureDataset> reducedFeatures; /** @brief Recuded image features. */
        std::future<std::vector<Cluster>> clusters; /** @brief Clusters computed. */
         
        //processors
        std::shared_ptr<ClusteringAlgorithm> clusteringAlgorithm; /** @brief Clustering algorithm. */
        std::shared_ptr<DimReductionAlgorithm> dimensionalityReductionAlgorithm; /** @brief Dimensionality reduction algorithm. */
        std::shared_ptr<FeatureExtractor> featureExtractor; /** @brief Feature extractor. */
        
        //status
        Status status = READY; /** @brief Status of the pipeline. */
    };
}

#endif
