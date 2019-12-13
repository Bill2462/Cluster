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
