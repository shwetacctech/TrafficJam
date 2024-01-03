#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TrafficJam.h"
#include "OpenGLWindow.h"

class TrafficJam : public QMainWindow
{
    Q_OBJECT

public:
    TrafficJam(QWidget *parent = nullptr);
    ~TrafficJam();
    void setupUi();

private slots:
    void readOBJ();

private:
    Ui::TrafficJamClass ui;
    QWidget* mCentralWidget;
    QPushButton* mPushButton;
    QMenuBar* mMenuBar;
    QToolBar* mMainToolBar;
    QStatusBar* mStatusBar;
    OpenGLWindow* mRenderer;
    QVector<GLfloat> mVertices;
    QVector<GLfloat> mColors;
};
