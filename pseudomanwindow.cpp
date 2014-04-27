#include "pseudomanwindow.h"
#include "mainwindow.h"

pseudoManWindow::pseudoManWindow(QWidget *parent) :
    QMainWindow(parent)
{
    mainWidget = new QWidget;
    sliderLayout = new QVBoxLayout;
    p_red_slider = new QSlider(Qt::Horizontal);
    p_red_slider->setMaximum(255);

    sourceImage = cv::Mat(1,1,CV_8UC1);
    cv::imshow("bar",sourceImage);
    setCentralWidget(mainWidget);
    sliderLayout->addWidget(p_red_slider);
    mainWidget->setLayout(sliderLayout);
}

void pseudoManWindow::affect(int foo) {
    sourceImage = cv::Mat(1,1,CV_8UC1,cv::Scalar::all(foo));
    imshow("bar",sourceImage);

}

void pseudoManWindow::createActions() {
    connect(p_red_slider, SIGNAL(sliderMoved(int)),this,SLOT(affect(int)));
}
