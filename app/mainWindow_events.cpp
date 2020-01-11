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
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <iostream>

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
}

/**
 * @brief Handler for sorting start button.
 */
void MainWindow::on_sortImages_button_pressed()
{
}
