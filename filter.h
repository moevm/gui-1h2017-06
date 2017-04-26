#ifndef FILTER_H
#define FILTER_H

#include <QPixmap>
#include <QDebug>

class Filter : public QObject
{
     Q_OBJECT

private:
    QPixmap _filterImage;
public:
    Filter();


    QPixmap onFilter();


public slots:
    void setImage(QPixmap originalImage);
};

#endif // FILTER_H
