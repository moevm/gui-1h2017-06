#ifndef FILTER_H
#define FILTER_H

#include <QPixmap>
#include <QDebug>

class Filter
{
private:
    QPixmap _filterImage;
public:
    Filter();

    int setImage(QPixmap _originalImage);

    QPixmap onFilter();
};

#endif // FILTER_H
