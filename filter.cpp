#include "filter.h"

Filter::Filter()
{

}



int Filter::setImage(QPixmap filterImage)
{
    try {
        _filterImage = filterImage;
    } catch(int e) {
        qDebug() << "An exception occurred. Exception Nr. " << e << '\n';
        return e;
    }
    return 0;
}

QPixmap Filter::onFilter()
{
    return NULL;
}
