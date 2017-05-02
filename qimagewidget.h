#ifndef QIMAGEWIDGET_H
#define QIMAGEWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QMargins>
#include <QDebug>

class QImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QImageWidget(QWidget *parent = 0);

    void setupFilter1();
    void setupNegativeFilter();
    void setupSepiaFilter();
    void setupGrayScaleFilter();
    private:
    QPixmap _viewImage;
    QPixmap _originalImage;
    QPixmap _changedImage;
    static QPixmap * _toSaveImage;


    QString _noImageMessage;
    QColor _backgroundColor;
    QRect actualImageRect();

    public:
    void setPixmap(QPixmap pixmap);
    static void saveCurrentImage();
    QPixmap pixmap(){
        return _viewImage;
    }

    signals:
    void pixmapChanged();
    void filteredImageChanged(QPixmap);


    public slots:
    void setChangedImage(QPixmap);
    //void mousePressEvent(QMouseEvent* event);
    void mousePress();
    void mousePress1();
    void setupFilter(int choosen);


    protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

};

#endif // QIMAGEWIDGET_H

