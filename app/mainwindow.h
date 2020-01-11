/**
 * @file mainWindow.h
 * @brief This header file contains declaration of the MainWindow class.
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

#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED

#include <QMainWindow>
#include "appSettings.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/**
 * @brief Main window class.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int sizeX, int sizeY);
    MainWindow(QWidget* parent, int sizeX, int sizeY);
    ~MainWindow();

private slots:
    //button handlers
    void on_inputDir_browse_pressed();
    void on_outputDir_browse_pressed();
    void on_cluster_button_pressed();
    void on_sortImages_button_pressed();
    
private:
    Ui::MainWindow* ui;
    settings::UserSettings getSettings();
    void setSettings(settings::UserSettings settings);
};

#endif
