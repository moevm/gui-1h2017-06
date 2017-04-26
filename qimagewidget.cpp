#include "qimagewidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>

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
    emit pixmapChanged();
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
       _changedImage = _originalImage;
       setPixmap(_originalImage);
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


void QImageWidget::setChangedImage(QPixmap changedImage)
{
    setPixmap(changedImage);
}

