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
            objVertices.push_back(y* 0.10);
            objVertices.push_back(z* 0.10);
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
/*#include "stdafx.h"
#include "TrafficJam.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <Grid.h>
#include <Car.h>

TrafficJam::TrafficJam(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();
    connect(pushButton_2, &QPushButton::clicked, this, &TrafficJam::readOBJ);
    connect(pushButton_4, &QPushButton::clicked, this, &TrafficJam::UpperMove);
    connect(pushButton_3, &QPushButton::clicked, this, &TrafficJam::DownMove);
    connect(pushButton, &QPushButton::clicked, this, &TrafficJam::LeftMove);
    connect(pushButton5, &QPushButton::clicked, this, &TrafficJam::RightMove);
    connect(pushButton6, &QPushButton::clicked, this, &TrafficJam::stop);

    connect(mRenderer, SIGNAL(shapeUpdate()), mRenderer, SLOT(update()));
}

TrafficJam::~TrafficJam()
{}
void TrafficJam::setupUi()
{

    resize(944, 895);
    centralWidget = new QWidget(this);
    centralWidget->setObjectName("centralWidget");
    gridLayoutWidget = new QWidget(centralWidget);
    gridLayoutWidget->setObjectName("gridLayoutWidget");
    gridLayoutWidget->setGeometry(QRect(-1, -1, 641, 361));
    gridLayout_2 = new QGridLayout(gridLayoutWidget);
    gridLayout_2->setSpacing(6);
    gridLayout_2->setContentsMargins(11, 11, 11, 11);
    gridLayout_2->setObjectName("gridLayout_2");
    gridLayout_2->setContentsMargins(0, 0, 0, 0);
    verticalLayout_2 = new QVBoxLayout();
    verticalLayout_2->setSpacing(6);
    verticalLayout_2->setObjectName("verticalLayout_2");
    mRenderer = new OpenGLWindow(QColor(0, 0, 0), this);
    mRenderer->setObjectName("openGLWidget");
    verticalLayout_2->addWidget(mRenderer, 3);

    gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);

    horizontalLayoutWidget = new QWidget(centralWidget);
    horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
    horizontalLayoutWidget->setGeometry(QRect(0, 360, 641, 80));
    horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget);
    horizontalLayout_3->setSpacing(6);
    horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
    horizontalLayout_3->setObjectName("horizontalLayout_3");
    horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
    horizontalLayout_4 = new QHBoxLayout();
    horizontalLayout_4->setSpacing(6);
    horizontalLayout_4->setObjectName("horizontalLayout_4");
    pushButton_2 = new QPushButton(horizontalLayoutWidget);
    pushButton_2->setObjectName("pushButton_2");
    pushButton_2->setText("Start");

    horizontalLayout_4->addWidget(pushButton_2);

    pushButton_4 = new QPushButton(horizontalLayoutWidget);
    pushButton_4->setObjectName("pushButton_4");
    pushButton_4->setText("FORWARD");
    horizontalLayout_4->addWidget(pushButton_4);

    pushButton_3 = new QPushButton(horizontalLayoutWidget);
    pushButton_3->setObjectName("pushButton_3");
    pushButton_3->setText("BACKWARD");
    horizontalLayout_4->addWidget(pushButton_3);

    pushButton = new QPushButton(horizontalLayoutWidget);
    pushButton->setObjectName("pushButton");
    pushButton->setText("LEFT");
    horizontalLayout_4->addWidget(pushButton);
    pushButton5 = new QPushButton(horizontalLayoutWidget);
    pushButton5->setObjectName("pushButton");
    pushButton5->setText("RIGHT");
    horizontalLayout_4->addWidget(pushButton5);
    pushButton6 = new QPushButton(horizontalLayoutWidget);
    pushButton6->setObjectName("pushButton");
    pushButton6->setText("RESTART");
    horizontalLayout_4->addWidget(pushButton6);



    horizontalLayout_3->addLayout(horizontalLayout_4);

    setCentralWidget(centralWidget);
    menuBar = new QMenuBar(this);
    menuBar->setObjectName("menuBar");
    menuBar->setGeometry(QRect(0, 0, 644, 22));
    setMenuBar(menuBar);
    mainToolBar = new QToolBar(this);
    mainToolBar->setObjectName("mainToolBar");
    addToolBar(Qt::TopToolBarArea, mainToolBar);
    statusBar = new QStatusBar(this);
    statusBar->setObjectName("statusBar");
    setStatusBar(statusBar);

    QMetaObject::connectSlotsByName(this);
} 
void TrafficJam::sceneStatic() {
    std::vector<float> vertices;
    std::vector<float> color;
    Grid grid(vertices, color, 8);

    for (int i = 0; i < vertices.size(); i += 3) {
        mVertices << vertices[i] << vertices[i + 1] << vertices[i + 2];
        mColors << 1 << 0 << 1;
    }

    
    mVertices.clear();
    mColors.clear();
    std::vector<float>carVertices;
    std::vector<float>carColor;
    carVertices.push_back(-1);
    float car1_data[12] = { -1, 4, 0, 1, 4, 0, 1, 2, 0, -1, 2, 0 };
    const float car2_data[12] = { 2,4,0,4,4,0,4,2,0,2,2,0 };
    const float car3_data[12] = { -4, 1,0,-2,1,0,-2,-1,0,-1,-1,0 };
    const float car4_data[12] = { -1,1,0,1,1,0,1,-1,0,-1,-1,0 };
    const float car5_data[12] = { -4,-2,0,-2,-2,0,-2,-4,0,-4,-4,0 };
    const float car6_data[12] = { 2,-2,0,4,-2,0,4,-4,0,2,-4,0 };
    for (int i = 0; i < sizeof(car1_data)-3; i++) {
        carVertices.push_back(car1_data[i]);
        carColor.push_back(1.0);
        mVertices.push_back(car1_data[i]);
        mColors.push_back(1.0);
    }
    Car car1(carVertices, carColor);
    carVertices.clear();
    carColor.clear();
    for (int i = 0; i < sizeof(car2_data); i++) {
        carVertices.push_back(car2_data[i]);
        carColor.push_back(1.0);
       // mVertices.push_back(car2_data[i]);
        //mColors.push_back(1.0);
    }
    Car car2(carVertices, carColor);
    carVertices.clear();
    carColor.clear();
    for (int i = 0; i < sizeof(car3_data); i++) {
        carVertices.push_back(car3_data[i]);
        carColor.push_back(1.0);
       mVertices.push_back(car3_data[i]);
       mColors.push_back(1.0);
    }
    Car car3(carVertices, carColor);
    carVertices.clear();
    carColor.clear();
    for (int i = 0; i < sizeof(car4_data); i++) {
        carVertices.push_back(car4_data[i]);
        carColor.push_back(1.0);
       // mVertices.push_back(car4_data[i]);
       // mColors.push_back(1.0);
    }
    Car car4(carVertices, carColor);
    carVertices.clear();
    carColor.clear();
    for (int i = 0; i < sizeof(car5_data); i++) {
        carVertices.push_back(car5_data[i]);
        carColor.push_back(1.0);
       // mVertices.push_back(car5_data[i]);
       // mColors.push_back(1.0);
    }
    Car car5(carVertices, carColor);
    carVertices.clear();
    carColor.clear();
    for (int i = 0; i < sizeof(car6_data); i++) {
        carVertices.push_back(car6_data[i]);
        carColor.push_back(1.0);
        //mVertices.push_back(car6_data[i]);
        //mColors.push_back(1.0);
    }
    Car car6(carVertices, carColor);
    carVertices.clear();
    carColor.clear();

    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    mVertices.clear();
    mColors.clear();
}
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
            objVertices.push_back(y * 0.1);
            objVertices.push_back(z * 0.1);
            objColors.push_back(1.0);
            objColors.push_back(0.0);
            objColors.push_back(1.0);
        
        }  
    }
    for (int i = 0; i < objVertices.size(); i+=3) {
        mVertices << objVertices[i] << objVertices[i + 1] << objVertices[i + 2];
        mColors << objColors[i] << objColors[i + 1] << objColors[i + 1];
    }
    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
    
    
}
void TrafficJam::LeftMove() {
    for (int i = 0; i < mVertices.size(); i+=3) {
        mVertices[i] -= 1;
    }

    mRenderer->setVectorOfLines(mVertices);
}
void TrafficJam::RightMove() {
    for (int i = 0; i < mVertices.size(); i += 3) {
        mVertices[i] += 1;
    }
    mRenderer->setVectorOfLines(mVertices);
}
void TrafficJam::UpperMove() {
    for (int i = 0; i < mVertices.size(); i += 3) {
        mVertices[i+1] += 1;
    }

    mRenderer->setVectorOfLines(mVertices);
}
void TrafficJam::DownMove() {
    for (int i = 0; i < mVertices.size(); i += 3) {
        mVertices[i + 1] -= 1;
    }

    mRenderer->setVectorOfLines(mVertices);
}
void TrafficJam::stop() {
    mVertices.clear();
    mColors.clear();
    mRenderer->setVectorOfLines(mVertices);
    mRenderer->setColorOfLines(mColors);
}*/
