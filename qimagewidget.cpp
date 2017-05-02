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


void QImageWidget::setupFilter1()
{
////    here will be seting of filter
//    QPixmap.setMask();
//    _changedImage.setTexture(_changedImage.createMaskFromColor(QColor(0,255,255),Qt::MaskOutColor));
    emit filteredImageChanged(_changedImage);
}

void QImageWidget::setupNegativeFilter()
{
    QImage editableImage = _changedImage.toImage();
    QRgb value;
    for (int i = 0; i < editableImage.height(); i++) {
        for (int j = 0; j < editableImage.width(); j++) {
            QColor sourceColor = editableImage.pixel(i,j);
            value = qRgb(255 - sourceColor.red(), 255 - sourceColor.green(), 255 - sourceColor.blue());
            editableImage.setPixel(i,j,value);
        }
    }
    _changedImage = QPixmap::fromImage(editableImage);
    setPixmap(_changedImage);
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
        qDebug() << "показывает оригинал";

}
void QImageWidget::mousePress1()
{

    setPixmap(_changedImage);
        qDebug() << "показывает обработанное изображение";

}

void QImageWidget::setupFilter(int choosen)
{
    if (choosen == 1) setupNegativeFilter();
}

