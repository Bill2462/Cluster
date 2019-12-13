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
