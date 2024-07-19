#include "mainwindow.h"
#include <QApplication>

// Main function of the program.
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);  // Creates the Qt application, passing command line arguments.

    MainWindow w;  // Creates the main window of the application.
    w.show();  // Displays the main window on the screen.

    return a.exec();  // Enters the application's event loop, waiting for user actions, such as clicks and keyboard entries.
}
