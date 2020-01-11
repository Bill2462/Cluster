/**
 * @file utils.cpp
 * @brief This source file contains definition of utility functions.
 * @author Krzysztof Adamkiewicz
 * @date 11/1/2020
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

#include "utils.hpp"
#include <filesystem>

namespace filesys = std::filesystem;

/**
 * @brief Check if file exists.
 * @param filePath Path.
 * @return True of path leads to a file.
 * @throw std::runtime_error If filesystem error occurs.
 */
inline bool checkIfFile(const std::string& filePath)
{
    try
    {
        filesys::path pathObj(filePath);
            
        if(filesys::exists(pathObj) && filesys::is_regular_file(pathObj))
            return true;
    }
    catch(filesys::filesystem_error & e)
	{
		throw(std::runtime_error("Filesystem error: " + std::string(e.what())));
	}
    
    return false;
}

/**
 * @brief Check if directory exists.
 * @param filePath Path.
 * @return True if path leads to a directory.
 * @throw std::runtime_error If filesystem error occurs.
 */
inline bool checkIfDirectory(const std::string& filePath)
{
    try
    {
        filesys::path pathObj(filePath);

        if(filesys::exists(pathObj) && filesys::is_directory(pathObj))
            return true;
    }
    catch (filesys::filesystem_error & e)
	{
		throw(std::runtime_error("Filesystem error: " + std::string(e.what())));
	}
	
    return false;
}

/**
 * @brief Check if path is a directory, throws runtime error if it is a file or
 * if it does not exists.
 * @param path Path.
 * @throw std::runtime_error If path is a file or does not exists.
 */
inline void requireDirectory(const std::string& path)
{
    if(!checkIfDirectory(path))
    {
        std::string errorMessage;
        if(checkIfFile(path))
            errorMessage = "'" + path + "' is a file!";
        else
            errorMessage = "'" + path + "' does not exists!";
        
        throw(std::runtime_error(errorMessage));
    }
}

/**
 * @brief Check if path is a file, throws runtime error if it is a directory or
 * if it does not exists.
 * @param path Path.
 * @throw std::runtime_error If path is a directory or does not exists.
 */
inline void requireFile(const std::string& path)
{
    if(!checkIfFile(path))
    {
        std::string errorMessage;
        if(checkIfDirectory(path))
            errorMessage = "'" + path + "' is a file!";
        else
            errorMessage = "'" + path + "' does not exists!";
        
        throw(std::runtime_error(errorMessage));
    }
}

/**
 * @brief List all files in the directory
 * @param path Path to the directory.
 * @param includeSubdirs Recursively inclide subdirectories.
 * @return Vector of file paths.
 * @throw std::runtime_error If path leads to nowhere or to a file.
 */
std::vector<std::string> utils::listFiles(const std::string& path, bool includeSubdirs)
{
    requireDirectory(path);

    std::vector<std::string> files;
    
    if(includeSubdirs)
    {
        for(auto& path: filesys::recursive_directory_iterator(path))
        {
            std::string pathStr(std::string(path.path()));
            if(checkIfFile(pathStr))
                files.push_back(pathStr);
        }
    }
    else
    {
        for(auto& path: filesys::directory_iterator(path))
            files.push_back(std::string(path.path()));   
    }
    
    return files;
}

/**
 * @brief Move file.
 * @param source Path to a source file.
 * @param dest Path to a destination file.
 * @throw std::runtime_error If source or destination path does not exists.
 */
void utils::moveFile(const std::string& source, const std::string& dest)
{
    requireFile(source);
    requireDirectory(dest);

    std::string sourceFilename = source.substr(source.find_last_of("/\\") + 1);
    
    try
    {
        filesys::rename(source, dest + "/" + sourceFilename);
    }
    catch (filesys::filesystem_error& e)
    {
        throw(std::runtime_error("Filesystem error: " + std::string(e.what())));
    }
}

/**
 * @brief Copy file.
 * @param source Path to the source file.
 * @param dest Path to the destination file.
 * @throw std::runtime_error If source or destination path does not exists.
 */
void utils::copyFile(const std::string& source, const std::string& dest)
{
    requireFile(source);
    requireDirectory(dest);
    
    std::string sourceFilename = source.substr(source.find_last_of("/\\") + 1);
    
    try
    {
        filesys::copy(source, dest + "/" + sourceFilename);
    }
    catch (filesys::filesystem_error& e)
    {
        throw(std::runtime_error("Filesystem error: " + std::string(e.what())));
    }
}

/**
 * @brief Create directory.
 * @param path Path to the new directory.
 * @throw std::runtime_error If directory already ezists or if something else happens.
 */
void utils::makeDir(const std::string& path)
{
    if(checkIfDirectory(path) || checkIfFile(path))
        throw(std::runtime_error("'" + path + "' Already exists!"));
    
    try
    {
        filesys::create_directories(path);
    }
    catch (filesys::filesystem_error& e)
    {
        throw(std::runtime_error("Filesystem error: " + std::string(e.what())));
    }
}
