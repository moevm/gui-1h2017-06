#include "qimagewidget.h"
#include <QMouseEvent>
#include <QPainter>
#include <QFileDialog>

QImageWidget::QImageWidget(QWidget *parent) : QWidget(parent)
{
    _noImageMessage = "No Image";
    _backgroundColor = Qt::white;
//    _margin = 4;


//    connect(this, SIGNAL(marginChanged()), SLOT(repaint()));
    connect(this, SIGNAL(pixmapChanged()), SLOT(repaint()));
}

void QImageWidget::setPixmap(QPixmap pixmap)
{
    _originalImage = pixmap;
    emit pixmapChanged();
}

//void QImageWidget::setMargin(int value)
//{
//    if (value < 2)
//        value = 2;
//    if (value > 20)
//        value = 20;

//    if (value != _margin){
//        _margin = value;
//        emit marginChanged();
//    }
//}


void QImageWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
   if (event->button() != Qt::LeftButton)
       return;
   QString filename = QFileDialog::getOpenFileName(this);
   if (filename.isEmpty())
       return;
   setPixmap(QPixmap(filename));
}

void QImageWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.save();

    painter.setBrush(_backgroundColor);
    painter.drawRect(rect());

    painter.restore();
    if (_originalImage.isNull()){
        painter.drawText(rect(), Qt::AlignCenter, _noImageMessage);
    }else{
        QRect imageRect = rect();
        painter.drawPixmap(imageRect, _originalImage);
    }
}





