#ifndef PSEUDOMANWINDOW_H
#define PSEUDOMANWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtGui>
#include "mainwindow.h" //delete

class pseudoManWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit pseudoManWindow(QWidget *parent = 0);

private:
    QWidget *mainWidget;
    QVBoxLayout *sliderLayout;
    QSlider *p_red_slider;
    void createMat();
    void createActions();
    cv::Mat sourceImage;
signals:

public slots:
    void affect(int var);

};

#endif // PSEUDOMANWINDOW_H
