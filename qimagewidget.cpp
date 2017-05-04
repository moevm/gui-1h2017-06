#include "qimagewidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>

QPixmap* QImageWidget::_toSaveImage;

QImageWidget::QImageWidget(QWidget *parent) : QWidget(parent)
{
    _noImageMessage = "No Image";
    _backgroundColor = Qt::white;
    connect(this, SIGNAL(pixmapChanged()), SLOT(repaint()));
    connect(this, SIGNAL(filteredImageChanged(QPixmap)), SLOT(setChangedImage(QPixmap)));
}

QRect QImageWidget::actualImageRect()
{
    QRect imageRect = rect();
    imageRect.setSize(_viewImage.size().scaled(size(), Qt::KeepAspectRatio));
    imageRect.moveCenter(rect().center());
    return imageRect;
}

void QImageWidget::setPixmap(QPixmap pixmap)
{
    _viewImage = pixmap;
    QImageWidget::_toSaveImage = &_viewImage;
    emit pixmapChanged();
}

void QImageWidget::saveCurrentImage()
{
    QString fileName = QFileDialog::getSaveFileName(0, "Сохранить как", QDir::currentPath(), "PNG (*.png);;JPG (*.jpg);; BMP (*.bmp)");
    QImageWidget::_toSaveImage->save(fileName,"PNG");
}


void QImageWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
   if (event->button() != Qt::LeftButton)
       return;
   QString filename = QFileDialog::getOpenFileName(this);
   if (filename.isEmpty())
       return;
   try {
       emit newImageLoaded(0);
       _originalImage = QPixmap(filename);
       _changedImage = _originalImage.copy(0,0,_originalImage.width(),_originalImage.height());
       //_changedImage = QPixmap(filename);
       setPixmap(_changedImage);
   } catch(int e) {
       qDebug() << "An exception occurred. Exception Nr. " << e << '\n';
   }
}

void QImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();

    painter.setBrush(_backgroundColor);
    painter.drawRect(rect());

    painter.restore();
    if (_viewImage.isNull()){
        painter.drawText(rect(), Qt::AlignCenter, _noImageMessage);
    }else{
        QRect imageRect = actualImageRect();
        painter.drawPixmap(imageRect, _viewImage);
    }
}


void QImageWidget::setupNegativeFilter()
{
    QImage editableImage = _originalImage.toImage();
    QRgb value;
    for (int i = 0; i < editableImage.width(); i++) {
        for (int j = 0; j < editableImage.height(); j++) {
            QColor sourceColor = editableImage.pixel(i,j);
            value = qRgb(255 - sourceColor.red(), 255 - sourceColor.green(), 255 - sourceColor.blue());
            editableImage.setPixel(i,j,value);
        }
    }
    _changedImage = QPixmap::fromImage(editableImage);
    setPixmap(_changedImage);
}

void QImageWidget::setupSepiaFilter()
{
    QImage editableImage = _originalImage.toImage();
    QRgb value;
    for (int i = 0; i < editableImage.width(); i++) {
        for (int j = 0; j < editableImage.height(); j++) {
            QColor sourceColor = editableImage.pixel(i,j);
            int tone = (int)(0.299 * sourceColor.red() + 0.587 * sourceColor.green() + 0.114 * sourceColor.blue());
            value = qRgb(tone > 206 ? 255 : tone + 49, tone < 14 ? 0 : tone - 14, tone < 56 ? 0 : tone - 56);
            editableImage.setPixel(i,j,value);
        }
    }
    _changedImage = QPixmap::fromImage(editableImage);
    setPixmap(_changedImage);
}

void QImageWidget::setupGrayScaleFilter()
{
    QImage editableImage = _originalImage.toImage();
    QRgb value;
    //float cr = 0.299f, cg = 0.587f , cb = 0.114f;
    //float cr = 0.500f, cg = 0.419f, cb = 0.081f;
    //float cr = 0.2125f, cg = 0.7154f, cb = 0.0721f;
    float cr = 0.333f, cg = 0.333f, cb = 0.333f;
    for (int i = 0; i < editableImage.width(); i++) {
        for (int j = 0; j < editableImage.height(); j++) {
            if (!editableImage.isNull()) {
            QColor sourceColor = editableImage.pixel(i,j);
            float gray = (float)(sourceColor.red()*cr + sourceColor.green()*cg + sourceColor.blue()*cb);
            value = qRgb(gray, gray, gray);
            editableImage.setPixel(i,j,value);
            }
        }
    }
    _changedImage = QPixmap::fromImage(editableImage);
    setPixmap(_changedImage);
}

void QImageWidget::setupBinaryGrayFilter()
{
    QImage editableImage = _originalImage.toImage();
    QRgb value;
    int adjustment = 290;
    for (int i = 0; i < editableImage.width(); i++) {
        for (int j = 0; j < editableImage.height(); j++) {
            QColor sourceColor = editableImage.pixel(i,j);
            float gray = (float)(sourceColor.red() + sourceColor.green() + sourceColor.blue());
            if (gray > adjustment) value = qRgb(255, 255, 255);
            else value = qRgb(0, 0, 0);
            editableImage.setPixel(i,j,value);
        }
    }
    _changedImage = QPixmap::fromImage(editableImage);
    setPixmap(_changedImage);
}

void QImageWidget::setupBrightness(int brightness)
{
    QImage editableImage = _changedImage.toImage();
    QRgb value;
    for (int i = 0; i < editableImage.width(); i++) {
        for (int j = 0; j < editableImage.height(); j++) {
            QColor sourceColor = editableImage.pixel(i,j);
            int newRed = sourceColor.red() - brightness;
            if (newRed > 255) newRed = 255;
            if (newRed < 0) newRed = 0;

            int newGreen = sourceColor.green() - brightness;
            if (newGreen > 255) newGreen = 255;
            if (newGreen < 0) newGreen = 0;

            int newBlue = sourceColor.blue() - brightness;
            if (newBlue > 255) newBlue = 255;
            if (newBlue < 0) newBlue = 0;
            value = qRgb(newRed, newGreen, newBlue);
            editableImage.setPixel(i,j,value);
        }
    }
    _changedImage = QPixmap::fromImage(editableImage);
}

void QImageWidget::setupContrast(int contrast)
{
    QImage editableImage = _changedImage.toImage();
    QRgb value;
    for (int i = 0; i < editableImage.width(); i++) {
        for (int j = 0; j < editableImage.height(); j++) {
            QColor sourceColor = editableImage.pixel(i,j);
            float tmpContrast = (100.0f+contrast)/100.0f;
            tmpContrast *= tmpContrast;

            float newRed = sourceColor.red()/255.0;
            newRed -= 0.5;
            newRed *= tmpContrast;
            newRed += 0.5;
            newRed *= 255;
            if (newRed > 255) newRed = 255;
            if (newRed < 0) newRed = 0;

            float newGreen = sourceColor.green()/255.0;
            newGreen -= 0.5;
            newGreen *= tmpContrast;
            newGreen += 0.5;
            newGreen *= 255;
            if (newGreen > 255) newGreen = 255;
            if (newGreen < 0) newGreen = 0;

            float newBlue = sourceColor.blue()/255.0;
            newBlue -= 0.5;
            newBlue *= tmpContrast;
            newBlue += 0.5;
            newBlue *= 255;
            if (newBlue > 255) newBlue = 255;
            if (newBlue < 0) newBlue = 0;
            value = qRgb(newRed, newGreen, newBlue);
            editableImage.setPixel(i,j,value);
        }
    }
    _changedImage = QPixmap::fromImage(editableImage);
}


void QImageWidget::setupTemperature(int temperature)
{
    QImage editableImage = _changedImage.toImage();
    QRgb value;
    for (int i = 0; i < editableImage.width(); i++) {
        for (int j = 0; j < editableImage.height(); j++) {
            QColor sourceColor = editableImage.pixel(i,j);
//            int newRed = sourceColor.red() + temperature*1.5;
//            if (newRed > 255) newRed = 255;
//            if (newRed < 0) newRed = 0;

//            int newGreen = sourceColor.green() + temperature/1.8;
//            if (newGreen > 255) newGreen = 255;
//            if (newGreen < 0) newGreen = 0;

//            int newBlue = sourceColor.blue() + temperature/16;
//            if (newBlue > 255) newBlue = 255;
//            if (newBlue < 0) newBlue = 0;
            int newRed;
            if(temperature < 0)
                newRed = sourceColor.red() + temperature*1.9 + 0;
            else newRed = sourceColor.red() + temperature*1.8 + 10;
            if (newRed > 255) newRed = 255;
            if (newRed < 0) newRed = 0;

            int newGreen;
            if (temperature < 0)
            newGreen = sourceColor.green() + temperature/1.3 + 10;
            else
            newGreen = sourceColor.green() + temperature/1.0 + 10 ;
            if (newGreen > 255) newGreen = 255;
            if (newGreen < 0) newGreen = 0;

            int newBlue;
            if (temperature < 0) newBlue = sourceColor.blue() + temperature/16 + 10;
            else newBlue = sourceColor.blue() + temperature/18 + 10;
            if (newBlue > 255) newBlue = 255;
            if (newBlue < 0) newBlue = 0;


            value = qRgb(newRed, newGreen, newBlue);
            editableImage.setPixel(i,j,value);



        }
    }
    _changedImage = QPixmap::fromImage(editableImage);

}



void QImageWidget::setupSharpness(int sharpness)
{

//    qDebug()<<"SHARPNES SETUP";

//    STATIC DEBUG
//    float Offset = 0.0f;
//    float Factor = 4.0f;
//    float SharpConfig[3][3] ={
//        {0.0f , -2.0f    , 0.0f },
//        { -2.0f, 11.0f    ,-2.0f  },
//        {0.0f , -2.0f    , 0.0f  }
//      };


//  DYNAMIC DEBUG WITH 3 SLIDERS
//    float weight =this->weight ;
    float Factor = this->factor;
    float Offset = this->offset;
//    float tmpSharpness = (100.0f+sharpness)/100.0f;

//    ONE USER SLIDER
    float weight = this->sharpness;

    float SharpConfig[3][3] ={
        {-1.0f , -1.0f    , -1.0f },
        { -1.0f, weight   ,-1.0f  },
        {-1.0f , -1.0f    , -1.0f  }
      };

    QColor nearPixels [3][3];

    QImage editableImage = _changedImage.toImage();
    QRgb value;
float cacheR,caheG,cacheB;
    for (int i = 0; i < editableImage.width() - 2; i++) {
        for (int j = 0; j < editableImage.height() - 2; j++) {
            QColor sourceColor = editableImage.pixel(i,j);
            // get pixel matrix
             for(int k = 0; k < 3; ++k) {
                 for(int l = 0; l < 3; ++l) {
                     nearPixels[k][l] = editableImage.pixel(i + k, j + l);
                 }
             }

             float newR =0; float newG = 0; float  newB = 0;

            // get sum of RGB on matrix
             for(int k = 0; k < 3; ++k) {
                 for(int l = 0; l < 3; ++l) {
//                BAD QUALITY OF MATH OPERATIONS
//                newR += (nearPixels[k][l].red() * SharpConfig[k][l]);
//                newG += (nearPixels[k][l].green() * SharpConfig[k][l]);
//                newB += (nearPixels[k][l].blue() * SharpConfig[k][l]);
//                     GOOD QUALITY OF ROUNDING
                      newR += (((((nearPixels[k][l].red()/255.0)-0.5) * SharpConfig[k][l])+0.5)*255.0);
                     newG += (((((nearPixels[k][l].green()/255.0)-0.5) * SharpConfig[k][l])+0.5)*255.0);
                    newB += (((((nearPixels[k][l].blue()/255.0)-0.5) * SharpConfig[k][l])+0.5)*255.0);
                 }
             }
            newR = (newR / Factor + Offset);
            if (newR > 255) newR = 255;
            if (newR < 0) newR = 0;

            newG = (newG / Factor + Offset);
            if (newG > 255) newG = 255;
            if (newG < 0) newG = 0;

            newB = (newB / Factor + Offset);
            if (newB > 255) newB = 255;
            if (newB < 0) newB = 0;

            value = qRgb(newR, newG, newB);
            editableImage.setPixel(i+1,j+1,value);
        }
    }
    _changedImage = QPixmap::fromImage(editableImage);
}

void QImageWidget::setChangedImage(QPixmap changedImage)
{

    setPixmap(changedImage);
}

//void QImageWidget::mousePressEvent(QMouseEvent *event)
//{
//    if(event->button() == Qt::LeftButton)
//    {setPixmap(_originalImage);
//    qDebug() << "показывает оригинал";}
//    if(event->button() == Qt::RightButton)
//    {
//        setPixmap(_changedImage);
//            qDebug() << "показывает оригинал2";
//    }
//}

void QImageWidget::mousePress()
{
    setPixmap(_originalImage);
        //qDebug() << "показывает оригинал";
}
void QImageWidget::mousePress1()
{
    setPixmap(_changedImage);
        //qDebug() << "показывает обработанное изображение";
}

void QImageWidget::setupFilter(int choosen)
{
    switch(choosen) {
    case (0):
        _changedImage = _originalImage;
        setPixmap(_changedImage);
        break;
    case (1):
        setupNegativeFilter();
        break;
    case (2):
        setupSepiaFilter();
        break;
    case(3):
        setupGrayScaleFilter();
        break;
    case(4):
        setupBinaryGrayFilter();
        break;
    }
}

void QImageWidget::brightnessChanged(int brightness)
{
    this->brightness = brightness;
}


void QImageWidget::contrastChanged(int contrast)
{
    this->contrast = contrast;
}

void QImageWidget::temperatureChanged(int temperature)
{
	this->temperature = temperature;
}

void QImageWidget::sharpnessChanged(int sharpness)
{
    this->sharpness = sharpness;
    if(sharpness>25)
        this->factor = 13;
    else if(sharpness<18)
        this->factor = 8;
    else
        this->factor = 6;

    qDebug()<<"sharpness"<<sharpness;
}

void QImageWidget::sliderValueChanged()
{
    _changedImage = _originalImage.copy(0,0,_originalImage.width(),_originalImage.height());
    setupBrightness(this->brightness);
    setupContrast(this->contrast);
    setupSharpness(this->sharpness);
	setupTemperature(this->temperature);
    setPixmap(_changedImage);
}


void QImageWidget::sliderBrightnessValueChanged() {
    _changedImage = _originalImage.copy(0,0,_originalImage.width(),_originalImage.height());
    setupBrightness(this->brightness);
    setPixmap(_changedImage);
}

void QImageWidget::sliderContrastValueChanged() {
    _changedImage = _originalImage.copy(0,0,_originalImage.width(),_originalImage.height());
    setupContrast(this->contrast);
    setPixmap(_changedImage);
}

void QImageWidget::sliderSharpnessValueChanged()
{
    _changedImage = _originalImage.copy(0,0,_originalImage.width(),_originalImage.height());
    setupSharpness(this->sharpness);
    setPixmap(_changedImage);
}

void QImageWidget::sliderTemperatureValueChanged()
{
    _changedImage = _originalImage.copy(0,0,_originalImage.width(),_originalImage.height());
    setupTemperature(this->temperature);
    setPixmap(_changedImage);
}


void QImageWidget::sharpnessWeightChanged(int weight) {
    this->weight = weight;
//    qDebug()<<"weight"<<weight;
}

void QImageWidget::sharpnessFactorChanged(int factor) {
    this->factor = factor;
//    qDebug()<<"factor"<<factor;
}

void QImageWidget::sharpnessOffsetChanged(int offset) {
    this->offset = offset;
//    qDebug()<<"offset"<<offset;
}
