#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include "clrman.h" // holds all the opencv headers, functions
#include "pseudomanwindow.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    // build the GUI using Qt stuff
    QWidget *mainWidget;
    QPushButton
    *setImageButton,
    *pseudoColorButton,
    *webSafeColorButton;
    QBoxLayout *mainLayout;
    QAction
    *setImageAct,
    *webSafeAct,
    *pseudoAct;
    QMenu *fileMenu;

    void createMenus();
    void createActions();

    // opencv member goes here
    cv::Mat sourceImage;

private slots:
    void on_pseudoColorButton_clicked();
    void setImage();

};

#endif // MAINWINDOW_H
