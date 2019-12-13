#include "mainwindow.h"
#include "./ui_mainwindow.h"

/**
 * @brief Add items to the combo box.
 * @param cmb Pointer to the combo box.
 * @param options Map containing options and corresponding strings.
 */
inline void addItemsToComboBox(QComboBox* cmb, std::map<std::string, auto> options)
{
    for (auto it=options.begin(); it!=options.end(); ++it)
        cmb->addItem(QString(it->first.c_str()));
}

/**
 * @param parent Pointer to the parent window.
 * @param sizeX Width of the window.
 * @param sizeY Height of the window.
 */
MainWindow::MainWindow(QWidget* parent, int sizeX, int sizeY):
QMainWindow(parent),
ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    
    //set window size to a fixed value
    setFixedSize(QSize(sizeX, sizeY));
    
    //add items to combo boxes
    addItemsToComboBox(ui->featureSelection_comboBox, settings::FEATURE_SELECTION_ALGORITHMS);
    addItemsToComboBox(ui->clusteringAlgorithm_comboBox, settings::CLUSTERING_ALGORITHMS);
    
    //set the default UserSettings values to the magic
    setSettings(settings::UserSettings());
}

/**
 * @param sizeX Width of the window.
 * @param sizeY Height of the window.
 */
MainWindow::MainWindow(int sizeX, int sizeY):
MainWindow(nullptr, sizeX, sizeY)
{}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Get current settings.
 * @return Current controls state.
 */
settings::UserSettings MainWindow::getSettings()
{
    settings::UserSettings settings;
    
    settings.inputDir = ui->inputDir_combo->itemText(0).toStdString();
    settings.outputDir = ui->outputDir_combo->itemText(0).toStdString();
    
    settings.includeSubdirectories = ui->inputDir_includeSubdirs->checkState() == Qt::Checked;
    settings.leaveOryginalImages = ui->leaveOryginals_checkbox->checkState() == Qt::Checked;
    
    settings.featureAlgorithm = settings::FEATURE_SELECTION_ALGORITHMS.at(ui->featureSelection_comboBox->currentText().toStdString());
    settings.clusterAlgorithm = settings::CLUSTERING_ALGORITHMS.at(ui->clusteringAlgorithm_comboBox->currentText().toStdString());
    
    settings.threadNumber = ui->threadCount->value();
    
    return settings;
}

/**
 * @brief Set controls state. 
 * @param settings Settings to be set to the control panel.
 */
void MainWindow::setSettings(settings::UserSettings settings)
{
    ui->inputDir_combo->clear();
    ui->outputDir_combo->clear();
    ui->inputDir_combo->addItem(QString(settings.inputDir.c_str()));
    ui->inputDir_combo->addItem(QString(settings.outputDir.c_str()));
    
    auto boolToQtState = [](bool state)->Qt::CheckState
    {
        if(state)
            return Qt::Checked;
        else
            return Qt::Unchecked;
    };
    ui->inputDir_includeSubdirs->setCheckState(boolToQtState(settings.includeSubdirectories));
    ui->inputDir_includeSubdirs->setCheckState(boolToQtState(settings.leaveOryginalImages));
    
    ui->threadCount->setValue(settings.threadNumber);
}
