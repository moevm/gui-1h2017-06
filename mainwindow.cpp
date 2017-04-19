#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qimagewidget.h>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/socialphotobucketcircularbutton_80093.png"));
//    QImageWidget* image = new QImageWidget();
//    ui->verticalLayout->addWidget(image);
//    connect(ui->horizontalSlider, SIGNAL(valueChanged(int)), image, SLOT(setMargin(int)));
    ui->widget_2->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}
