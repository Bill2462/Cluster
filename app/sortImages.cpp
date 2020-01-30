/**
 * @file sortImages.cpp
 * @brief This source file contains code for sorting images according to computed clusters.
 * @author Krzysztof Adamkiewicz
 * @date 29/1/2020
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

#include "mainwindow.h"
#include "utils/utils.hpp"
#include <QMessageBox>

/**
 * @brief Sort images according to calculated clusters.
 */
void MainWindow::sortImages()
{
    if(clusters.empty())
    {
        QMessageBox::critical(this, "I can't do that!", "Clusters not computed! Run clustering first!");
        return;
    }
    
    if(getSettings().outputDir.empty())
    {
        QMessageBox::critical(this, "Error", "Output directory not specified!");
        return;
    }
    
    //check if destination directory exists
    if(!utils::dirExists(getSettings().outputDir))
        utils::makeDir(getSettings().outputDir); //if it doesn't exist, create one
    
    //do sorting
    try
    {
        for(size_t i=0; i<clusters.size(); i++)
        {
            //ensure that directory exists
            std::string destination = getSettings().outputDir+"/"+std::to_string(i);
            if(!utils::dirExists(destination))
                utils::makeDir(destination);
            
            //move or copy files
            std::size_t found;
            std::string filename;
            for(auto it=clusters[i].begin(); it<clusters[i].end(); it++)
            {
                found = (*it).path.find_last_of("/\\");
                if(found == std::string::npos)
                    filename = (*it).path;
                else
                    filename = (*it).path.substr(found+1);
                
                if(getSettings().leaveOryginalImages)
                    utils::copyFile((*it).path, destination+"/");
                else
                    utils::moveFile((*it).path, destination+"/");
            }
        }
    }
    catch(std::runtime_error& e)
    {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    
    QMessageBox::information(this, "Success!", "Finished moving images!");
}
