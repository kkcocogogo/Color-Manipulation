#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // define what's in mainwindow
    mainWidget = new QWidget();
    webSafeColorButton = new QPushButton("Web Safe Color");
    setImageButton = new QPushButton("Open Image");
    pseudoColorButton = new QPushButton("Pseudo Color");
    mainLayout = new QVBoxLayout;

    mainLayout->addWidget(setImageButton);
    mainLayout->addWidget(webSafeColorButton);
    mainLayout->addWidget(pseudoColorButton);
    setCentralWidget(mainWidget);
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
    cv::imshow("Source Image", sourceImage);

}

void MainWindow::on_pseudoColorButton_clicked() {
    pseudoManWindow *pseudo_man_window = new pseudoManWindow(this);
    pseudo_man_window->show();
}

void MainWindow::createActions() {
    setImageAct = new QAction(tr("&Open"),this);
    setImageAct->setShortcut(tr("Ctrl+O"));
    connect(setImageAct,SIGNAL(triggered()),this,SLOT(setImage()));
    connect(setImageButton,SIGNAL(clicked()),this,SLOT(setImage()));

    connect(pseudoColorButton,SIGNAL(clicked()),this,SLOT(on_pseudoColorButton_clicked()));
}

void MainWindow::createMenus() {

    fileMenu = new QMenu(tr("&File"),this);
    fileMenu->addAction(setImageAct);
    menuBar()->addMenu(fileMenu);

}

MainWindow::~MainWindow()
{

}
