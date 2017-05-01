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
    QColor _backgroundColor;
    QRect actualImageRect();
public:
    void setPixmap(QPixmap pixmap);
    QPixmap pixmap() {
        return _originalImage;
    }


signals:
    void pixmapChanged();

public slots:

protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
};

#endif // QIMAGEWIDGET_H
