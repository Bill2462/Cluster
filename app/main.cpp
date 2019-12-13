#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    //initialize the application
    QApplication a(argc, argv);
    
    //create main window
    MainWindow w(891, 483);
    w.show();
    
    //start the application
    return a.exec();
}
