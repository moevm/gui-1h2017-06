#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/image/socialphotobucketcircularbutton_80093.png"));

    QImageWidget* image = new QImageWidget();
    setQImageWidget(image);
    //connect(ui->original, SIGNAL(pressed()), image, SLOT(mousePress()));
    //connect(ui->changeImage, SIGNAL(pressed()), image, SLOT(mousePress1()));
    ui->widget_2->hide();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ////here enum with associating indexes and filters
}



void MainWindow::on_action_triggered()
{
    QImageWidget::saveCurrentImage();
}

void MainWindow::setQImageWidget(QImageWidget *image)
{
    this->image = image;
}

