#ifndef QIMAGEWIDGET_H
#define QIMAGEWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QMargins>

class QImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit QImageWidget(QWidget *parent = 0);

private:
    QPixmap _originalImage;
    QString _noImageMessage;
//    int _margin;
//    QMargins _margins;
    QColor _backgroundColor;
public:
    void setPixmap(QPixmap pixmap);
    QPixmap pixmap(){
        return _originalImage;
    }

//    int margin(){
//        return _margin;
//    }

signals:
    void pixmapChanged();
//    void marginChanged();

public slots:
//void setMargin(int value);
    // QWidget interface
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
};

#endif // QIMAGEWIDGET_H
