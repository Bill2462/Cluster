/**
 * @file mainWindow_events.cpp
 * @brief This source file event handles for main window.
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

#include "mainwindow.h"
#include "utils/utils.hpp"
#include "./ui_mainwindow.h"
#include "progressdialog.h"
#include <QFileDialog>
#include <QMessageBox>

/**
 * @brief Update string displayed in combo box.
 * Directories are displayed in combo boxes.
 */
inline void updateDirectoryDisplay(QComboBox* box, QString newState)
{
    //if box is not empty, remove the current itme
    if(box->count() > 0)
        box->removeItem(0);
    
    //add new item to the box
    box->addItem(newState);
}

/**
 * @brief Handler for input directory browsing button.
 */
void MainWindow::on_inputDir_browse_pressed()
{
    //show the dialog
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose input directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly | 
                                                    QFileDialog::DontResolveSymlinks);
    
    //update the state of inputDir_combo to show current directory
    updateDirectoryDisplay(ui->inputDir_combo, dir);
}

/**
 * @brief Handler for output directory browsing button.
 */
void MainWindow::on_outputDir_browse_pressed()
{
    //show dialog
    QString dir = QFileDialog::getExistingDirectory(this, tr("Choose output directory"),
                                                    "/home",
                                                    QFileDialog::ShowDirsOnly | 
                                                    QFileDialog::DontResolveSymlinks);
        
    //update the state of outputDir_combo to show current directory
    updateDirectoryDisplay(ui->outputDir_combo, dir);
}

/**
 * @brief Handler for clustering start button.
 */
void MainWindow::on_cluster_button_pressed()
{
    if(getSettings().inputDir.empty())
    {
        QMessageBox::critical(this, "Error", "Input directory not specified!");
        return;
    }

    //build pipeline
    std::shared_ptr<magic::Pipeline> pipeline
    (
        new magic::Pipeline
        (
            magic::DimReductionAlgorithm::MDS_ALGORITHM,
            getSettings().clusterAlgorithm,
            getSettings().featureAlgorithm
        )
    );

    //browse filenames
    std::vector<std::string> imageFilenames;
    try
    {
        imageFilenames = utils::listFiles(getSettings().inputDir, getSettings().includeSubdirectories);
    }
    catch(std::runtime_error& e)
    {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    
    //ensure that they are some detected files
    if(imageFilenames.empty())
    {
        QMessageBox::critical(this, "Error", "Specifies path is empty!");
        return;
    }
    
    //add files to the pipeline and start processing
    pipeline->setInput(imageFilenames);
    pipeline->startProcessing(getSettings().threadNumber);
    
    ProgressDialog dialog(this, pipeline);
    dialog.exec();
    
    //show reduced images on the screen
    this->clusters = pipeline->getClusters();
    this->features = pipeline->getReducedFeatures();
    
    QMessageBox::information(this, "Success!", std::string(std::to_string(clusters.size()) + std::string(" clusters found!")).c_str());
    
    displayFeatures();
}

/**
 * @brief Handler for sorting start button.
 */
void MainWindow::on_sortImages_button_pressed()
{
    sortImages();
}
