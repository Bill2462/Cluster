/**
 * @file progressdialog.h
 * @brief This header file contains declaration of the progress dialog class.
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


#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>
#include <QTimer>
#include <memory>
#include "Magic/Pipeline.hpp"

namespace Ui {
class ProgressDialog;
}

/**
 * @brief Progress dialog.
 */
class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    ProgressDialog(QWidget *parent, std::shared_ptr<magic::Pipeline> pipeline);
    ~ProgressDialog();

public slots:
    void updatePipeline();
    void updateDisplay();

private:
    magic::Pipeline::Status lastPipelineStatus = magic::Pipeline::READY;
    
    const long DISPLAY_UPDATE_INTERVAL = 100; /** @brief Update interval of the display. */
    const long PIPELINE_UPDATE_INTERVAL = 10; /** @brief Update interval of the pipeline. */
    QTimer* displayUpdateTimer; /** @brief Timer for updating display. */
    QTimer* pipelineUpdateTimer; /** @brief Timer for updating pipeline. */
    Ui::ProgressDialog* ui;
    
    std::shared_ptr<magic::Pipeline> processingPipeline; /** @brief Processing pipeline. */
};

#endif
