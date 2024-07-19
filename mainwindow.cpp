#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "dialog.h"
#include <QGraphicsPixmapItem>

// Constructor of the MainWindow class
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)  // Initializes the base class QMainWindow with the provided parent
    , ui(new Ui::MainWindow)  // Instantiates the graphical interface defined in the UI file for this window
{
    ui->setupUi(this);  // Sets up the user interface in the current window
    QGraphicsScene* scene = new QGraphicsScene(this);  // Creates a new graphical scene
    ui->graphicsView->setScene(scene);  // Sets the scene in the graphicsView widget
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);  // Enables antialiasing to improve rendering quality

    // Attempts to load a background image
    QPixmap background("C:/Users/sebas/OneDrive/Documents/RoboCupSoccer/RoboCupIntroImage.png");
    if (!background.isNull()) {  // Checks if the image was loaded correctly
        QGraphicsPixmapItem* backgroundItem = scene->addPixmap(background);  // Adds the image to the scene
        backgroundItem->setZValue(-1);  // Sets the rendering order so the image is in the background
        backgroundItem->setPos(0, 0);  // Positions the image at the start point of the scene
        backgroundItem->setScale(1.0);  // Sets the scale of the image to 1.0 (no resizing)
    } else {
        qDebug() << "Background image not found";  // Logs an error message if the image is not found
    }
}

// Destructor of the MainWindow class
MainWindow::~MainWindow()
{
    delete ui;  // Releases the user interface resources
}

// Slot called when the pushButton is clicked
void MainWindow::on_pushButton_clicked()
{
    Dialog* dialog = new Dialog(this);  // Creates a new instance of Dialog
    dialog->show();  // Displays the dialog
}
