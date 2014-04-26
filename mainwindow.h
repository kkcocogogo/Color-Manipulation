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
#include "clrman.h" // holds all the opencv headers, functions

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    // build the GUI using Qt stuff
    QBoxLayout *mainLayout;
    QGraphicsView *imageView;
    QGraphicsScene *imageScene;
    QSlider *slider;
    QGraphicsPixmapItem *pixmapItem4display;
    QAction *setImageAct;
    QMenu *fileMenu;

    void createMenus();
    void createActions();

    // opencv member goes here
    cv::Mat sourceImage;

private slots:

    void setImage();

};

#endif // MAINWINDOW_H
