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
void MDS::computeDistanceMatrix(const std::vector<FeatureVector>& points)
{
    //if size of dimensional matrix is different than point vector lenght we have to build a new one
    const size_t pointCount = points.size();
    const size_t currentMatrixSize = distanceMatrix.rows();
    if(currentMatrixSize != pointCount)
        distanceMatrix.resize(pointCount, pointCount);
    
    //compute dimension matrix
    for (size_t i = 0; i < pointCount; ++i)
    {
        for (size_t j = i; j < pointCount; ++j)
        {
            const double d = (points[i] - points[j]).norm();
            distanceMatrix(i, j) = d;
            distanceMatrix(j, i) = d;
        }
    }
}

/**
 * @brief Perform dimensionality reduction using multidimensional scaling.
 * @param input Input points.
 * @param outputDim Number of dimensions in the
 * @return Points reduced to outputDim numer of dimensions.
 */
std::vector<FeatureVector> MDS::reduce(const std::vector<FeatureVector>& input, unsigned short outputDim)
{
    computeDistanceMatrix(input);
    
    //perform reduction
    const Eigen::MatrixXd reduced = mathtoolbox::ComputeClassicalMds(distanceMatrix, outputDim);
    
    //convert to array of vector
    std::vector<FeatureVector> points;
    for(size_t i=0; i<(size_t)reduced.cols(); i++)
    {
        FeatureVector vect(reduced.rows());
        for(size_t r=0; r<(size_t)reduced.rows(); r++)
            vect[r] = reduced(r, i);
        
        points.push_back(vect);
    }
    
    return points;
}
