#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qimagewidget.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QImageWidget *image;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_comboBox_currentIndexChanged(int index);


    void on_action_triggered();

    void on_action_3_triggered();

private:
    void setQImageWidget(QImageWidget *image);
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
