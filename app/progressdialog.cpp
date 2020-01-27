/**
 * @file mainWindow.cpp
 * @brief This source file contains code for the progress dialog class
 * related to application settings.
 * @author Krzysztof Adamkiewicz
 * @date 27/1/2020
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

#include "progressdialog.h"
#include "ui_progressdialog.h"

/**
 * @param parent Parent window.
 * @param pipeline Pointer to the processing pipeline.
 */
ProgressDialog::ProgressDialog(QWidget *parent, std::shared_ptr<magic::Pipeline> pipeline):
    QDialog(parent),
    ui(new Ui::ProgressDialog),
    processingPipeline(pipeline)
{
    ui->setupUi(this);

    //initialize progress bars
    ui->cluster_progress->setValue(0);
    ui->cluster_progress->setFormat("Waiting...");
    
    ui->dimRedox_progress->setValue(0);
    ui->dimRedox_progress->setFormat("Waiting...");
    
    ui->feature_ext_progres->setValue(0);
    ui->feature_ext_progres->setFormat("Waiting...");
    
    ui->load_progress->setValue(0);
    ui->load_progress->setFormat("Waiting...");
    
    ui->preprocess_progres->setValue(0);
    ui->preprocess_progres->setFormat("Waiting...");
    
    //set title
    setWindowTitle("Processing...");
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
}

