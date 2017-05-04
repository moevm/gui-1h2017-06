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
    void setupBinaryGrayFilter();
    void setupBrightness(int brightness);
    void setupContrast(int contrast);
    void setupTemperature(int temperature);

    private:
    QPixmap _viewImage;
    QPixmap _originalImage;
    QPixmap _changedImage;
    static QPixmap * _toSaveImage;
    int brightness = 0;
    int contrast = 0;
    int temperature = 0;


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
    void newImageLoaded(int newIndex);


    public slots:
    void setChangedImage(QPixmap);
    //void mousePressEvent(QMouseEvent* event);
    void mousePress();
    void mousePress1();
    void setupFilter(int choosen);
    void brightnessChanged(int brightness);
    void sharpnessChanged(int sharpness);
    void contrastChanged(int contrast);
    void temperatureChanged(int temperature);
    void sliderValueChanged();
    void leftRotate();
    void rightRotate();


    protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

};

#endif // QIMAGEWIDGET_H

