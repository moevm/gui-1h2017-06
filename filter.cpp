#include "filter.h"

Filter::Filter()
{

}

void Filter::setImage(QPixmap filterImage)
{
    try {
        _filterImage = filterImage;
    } catch(int e) {
        qDebug() << "An exception occurred. Exception Nr. " << e << '\n';
    }
}

QPixmap Filter::onFilter()
{
    return NULL;
}
