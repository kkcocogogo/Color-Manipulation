#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // define what's in mainwindow
    QWidget *mainWidget = new QWidget();
    setCentralWidget(mainWidget);

    imageScene = new QGraphicsScene;
    imageView = new QGraphicsView;
    imageView->setScene(imageScene);
    slider = new QSlider(Qt::Horizontal);
    mainLayout = new QVBoxLayout;

    pixmapItem4display = new QGraphicsPixmapItem;
    imageScene->addItem(pixmapItem4display);
    mainLayout->addWidget(imageView);
    mainLayout->addWidget(slider);

    mainWidget->setLayout(mainLayout);

    // build action and menu
    createActions();
    createMenus();
}

void MainWindow::setImage() {

    QString imageDirectory =
            QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                QDir::homePath(),
                tr("Images (*.png *.jpg *.tif"));
    // convert qstring to std::string so that we
    sourceImage = cv::imread(imageDirectory.toStdString());

    // convert sourceImage to QPixmap for displaying

}

void MainWindow::createActions() {
    setImageAct = new QAction(tr("&Open"),this);
    setImageAct->setShortcut(tr("Ctrl+O"));
    connect(setImageAct,SIGNAL(triggered()),this,SLOT(setImage()));
}

void MainWindow::createMenus() {

    fileMenu = new QMenu(tr("&File"),this);
    fileMenu->addAction(setImageAct);
    menuBar()->addMenu(fileMenu);

}

MainWindow::~MainWindow()
{

}
