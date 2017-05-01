#ifndef QIMAGEWIDGET_H
#define QIMAGEWIDGET_H

#include <QWidget>
#include <QMargins>
#include <QDebug>

class QImageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit QImageWidget(QWidget *parent = 0);

    void setupFilter1();

private:
    QPixmap _viewImage;
    QPixmap _originalImage;
    QPixmap _changedImage;

    QString _noImageMessage;
    QColor _backgroundColor;
    QRect actualImageRect();

public:
    void setPixmap(QPixmap pixmap);
<<<<<<< Updated upstream
    QPixmap pixmap(){
        return _viewImage;
=======
    QPixmap pixmap() {
        return _originalImage;
>>>>>>> Stashed changes
    }

signals:
    void pixmapChanged();
    void filteredImageChanged(QPixmap);

public slots:
    void setChangedImage(QPixmap);
protected:
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
};

#endif // QIMAGEWIDGET_H
