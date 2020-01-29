/**
 * @file mainWindow.cpp
 * @brief This source file contains code for the progress dialog class
 * related to displaying progress and updating pipeline.
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
    
    //start update timer
    displayUpdateTimer  = new QTimer(this);
    pipelineUpdateTimer = new QTimer(this);
    connect(displayUpdateTimer, SIGNAL(timeout()), this, SLOT(updateDisplay()));
    connect(pipelineUpdateTimer, SIGNAL(timeout()), this, SLOT(updatePipeline()));
    displayUpdateTimer->start(DISPLAY_UPDATE_INTERVAL);
    pipelineUpdateTimer->start(PIPELINE_UPDATE_INTERVAL);

    updatePipeline();
    updateDisplay();
    
    //set title
    setWindowTitle("Processing your images...");
}

ProgressDialog::~ProgressDialog()
{
    delete ui;
    delete displayUpdateTimer;
    delete pipelineUpdateTimer;
}

/**
 * @brief Update pipeline.
 */
void ProgressDialog::updatePipeline()
{
    processingPipeline->update();
}

/**
 * @brief Update displayed progress.
 */
void ProgressDialog::updateDisplay()
{
    //get and display progress
    const magic::Pipeline::Progress progress = processingPipeline->getProgress();

    ui->load_progress->setValue(static_cast<int>(progress.loadingState*100));
    ui->preprocess_progres->setValue(static_cast<int>(progress.preprocessingState*100));
    ui->feature_ext_progres->setValue(static_cast<int>(progress.featureExtractionState*100));
    ui->cluster_progress->setValue(static_cast<int>(progress.clusteringCompleted*100));
    ui->dimRedox_progress->setValue(static_cast<int>(progress.dimRedoxCompleted*100));
    
    //update based on pipeline status (waiting, done indicators)
    const magic::Pipeline::Status status = processingPipeline->getStatus();
    if(lastPipelineStatus == status)
        return;
    
    lastPipelineStatus = status;
    
    //display waiting... percentage and done messages according to the pipeline status
    switch(status)
    {
        case magic::Pipeline::READY:
            ui->load_progress->setFormat("Waiting...");
            ui->preprocess_progres->setFormat("Waiting...");
            ui->feature_ext_progres->setFormat("Waiting...");
            ui->cluster_progress->setFormat("Waiting...");
            ui->dimRedox_progress->setFormat("Waiting...");
            break;
        
        case magic::Pipeline::LOADING_IMAGES:
            ui->load_progress->setFormat("%p%");
            ui->preprocess_progres->setFormat("Waiting...");
            ui->feature_ext_progres->setFormat("Waiting...");
            ui->cluster_progress->setFormat("Waiting...");
            ui->dimRedox_progress->setFormat("Waiting...");
            break;
            
        case magic::Pipeline::PREPROCESSING_IMAGES:
            ui->load_progress->setFormat("Done!");
            ui->preprocess_progres->setFormat("%p%");
            ui->feature_ext_progres->setFormat("Waiting...");
            ui->cluster_progress->setFormat("Waiting...");
            ui->dimRedox_progress->setFormat("Waiting...");
            break;
            
        case magic::Pipeline::GENERATING_FEATURES:
            ui->load_progress->setFormat("Done!");
            ui->preprocess_progres->setFormat("Done!");
            ui->feature_ext_progres->setFormat("%p%");
            ui->cluster_progress->setFormat("Waiting...");
            ui->dimRedox_progress->setFormat("Waiting...");
            break;
            
        case magic::Pipeline::PERFORMING_CLUSTERING:
            ui->load_progress->setFormat("Done!");
            ui->preprocess_progres->setFormat("Done!");
            ui->feature_ext_progres->setFormat("Done!");
            ui->cluster_progress->setFormat("Processing...");
            ui->dimRedox_progress->setFormat("Waiting...");
            break;
            
        case magic::Pipeline::PERFORMING_DIM_REDOX:
            ui->load_progress->setFormat("Done!");
            ui->preprocess_progres->setFormat("Done!");
            ui->feature_ext_progres->setFormat("Done!");
            ui->cluster_progress->setFormat("Done!");
            ui->dimRedox_progress->setFormat("Processing...");
            break;
            
        case magic::Pipeline::PROCESSING_COMPLETED:
            close();
            break;
    }
}
