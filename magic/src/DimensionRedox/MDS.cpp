/**
 * @file MDS.cpp
 * @brief This source file contains source code for MDS algorithm.
 * @author Krzysztof Adamkiewicz
 * @date 16/1/2020
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

#include "DimensionRedox/MDS.hpp"
#include <eigen3/Eigen/Core>
#include <mathtoolbox/classical-mds.hpp>

using namespace magic;

/**
 * @brief Compute distance matrix for the list of points.
 * Distance matrix is saved as private variable. This allows for reuse of allocated space.
 * Matrix is not reallocated when size between calls does not change.
 * @param points Points.
 */
void MDS::computeDistanceMatrix(const FeatureDataset& points)
{
    //if size of dimensional matrix is different than point vector lenght we have to build a new one
    const size_t pointCount = points.size();
    const size_t currentMatrixSize = this->distanceMatrix.rows();
    if(currentMatrixSize != pointCount)
        distanceMatrix.resize(pointCount, pointCount);
    
    //compute dimension matrix
    for (size_t i = 0; i < pointCount; ++i)
    {
        Eigen::VectorXd vect1 = Eigen::Map<Eigen::VectorXd>((double*)points[i].featureVector.data(), points[i].featureVector.size());
        for (size_t j = i; j < pointCount; ++j)
        {
            //TODO Use low level memory access to avoid rebuilding Eigen vectors on each iteration
            Eigen::VectorXd vect2 = Eigen::Map<Eigen::VectorXd>((double*)points[j].featureVector.data(), points[j].featureVector.size());
            const double d = (vect1 - vect2).norm();
            distanceMatrix(i, j) = d;
            distanceMatrix(j, i) = d;
        }
    }
}

/**
 * @brief Perform dimensionality reduction using multidimensional scaling.
 * @param dataset Dataset that we want to reduce.
 * @param outputDim Number of dimensions in the output.
 * @return Reduced feature dataset.
 */
FeatureDataset MDS::reduce(const FeatureDataset& dataset, unsigned short outputDim)
{
    computeDistanceMatrix(dataset);
    
    //perform reduction
    const Eigen::MatrixXd reduced = mathtoolbox::ComputeClassicalMds(distanceMatrix, outputDim);
    
    //convert to array of vector
    FeatureDataset featureDataset;
    featureDataset.reserve(dataset.size());
    for(size_t i=0; i<(size_t)reduced.cols(); i++)
    {
        //copy contents of the reduces matrix to the  feature vector
        ImageFeature feature;
        feature.path = dataset[i].path;

        for(size_t r=0; r<(size_t)reduced.rows(); r++)
            feature.featureVector.push_back(reduced(r, i));
        
        featureDataset.push_back(feature);
    }
    
    return featureDataset;
}
