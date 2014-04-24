#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFileDialog>
#include <QString>
#include <QLabel>
#include <QBoxLayout>
#include <QSlider>
#include <QAction>
#include <QMenu>
#include <QMenuBar>
#include <QGraphicsPixmapItem>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

// when subfunctions are getting large in number, pack them in namespace to avoid name pollution
void cvt2websafe(cv::Mat& src, cv::Mat& dst);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    QBoxLayout *mainLayout;
    QGraphicsView *imageView;
    QGraphicsScene *imageScene;
    QSlider *slider;
    QGraphicsPixmapItem *pixmapItem4display;
    QAction *setImageAct;
    QMenu *fileMenu;
    QImage *sourceImage;

    void createMenus();
    void createActions();

private slots:

    void setImage();

};

#endif // MAINWINDOW_H
