#include "stdafx.h"
#include "TrafficJam.h"
#include <fstream>
#include <iostream>
#include <sstream>

TrafficJam::TrafficJam(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    connect(mPushButton, &QPushButton::clicked, this, &TrafficJam::readOBJ);
    connect(mRenderer, SIGNAL(shapeUpdate()), mRenderer, SLOT(update()));
}

TrafficJam::~TrafficJam()
{}
void TrafficJam::setupUi()
{

    resize(700, 650);
    mCentralWidget = new QWidget(this);
    mCentralWidget->setObjectName("centralWidget");
    mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);
    mRenderer->setGeometry(QRect(40, 30, 421, 200));
    mPushButton = new QPushButton(mCentralWidget);
    mPushButton->setObjectName("pushButton");
    mPushButton->setText("Start");
    mPushButton->setGeometry(QRect(220, 560, 75, 24));
    setCentralWidget(mCentralWidget);
    mMenuBar = new QMenuBar(this);
    mMenuBar->setObjectName("menuBar");
    mMenuBar->setGeometry(QRect(0, 0, 600, 22));
    setMenuBar(mMenuBar);
    mMainToolBar = new QToolBar(this);
    mMainToolBar->setObjectName("mainToolBar");
    addToolBar(Qt::TopToolBarArea, mMainToolBar);
    mStatusBar = new QStatusBar(this);
    mStatusBar->setObjectName("statusBar");
    setStatusBar(mStatusBar);

    //retranslateUi(this);

    QMetaObject::connectSlotsByName(this);
} // setupUi
void TrafficJam::readOBJ() {
    std::string filePath = "D:\\Shweta_Workplace\\TrafficJam\\11497_Car_v2.obj";
    std::ifstream dataFile;
    dataFile.open(filePath);
    if (!dataFile.is_open()) {
        std::cout << "File not exit" << std::endl;
        return;
    }
    std::vector<float> objVertices;
    std::vector<float> objColors;
    std::string line;
    while (std::getline(dataFile, line)) {
        std::istringstream iss(line);
        std::string token;
        iss >> token;
        if (token == "v") {
            float x, y, z;
            iss >> x >> y >> z;
            objVertices.push_back(x * 0.1);
            objVertices.push_back(y* 0.1);
            objVertices.push_back(z* 0.1);
            objColors.push_back(1.0);
            objColors.push_back(0.0);
            objColors.push_back(1.0);
        }  
    }
    for (int i = 0; i < objVertices.size(); i+=3) {
        mVertices << objVertices[i] << objVertices[i + 1] << objVertices[i + 2];
        mColors << 1.0 << 1.0 << 1.0;
    }
    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);

    mVertices.clear();
    mColors.clear();


}