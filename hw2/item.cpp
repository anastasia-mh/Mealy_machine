#include "item.h"

const QSize Item::DEFAULT_SIZE = QSize(25,25);

QPoint Item::getPoint() const
{
    return point;
}

void Item::setPoint(QPoint newPoint)
{
    point = newPoint;
}

const QSize &Item::getSize() const
{
    return size;
}

void Item::setSize(const QSize &newSize)
{
    size = newSize;
}

Item::Item(QPoint point, const QSize &size):point(std::move(point)),
    size(size)
{

}

void Item::doPainting(QPainter *painter, const QString& name)
{
    painter->drawEllipse(getPoint(), getSize().width(), getSize().height());
    int x_text = getPoint().x() - painter->fontMetrics().boundingRect(name).width()/2;
    int y_text = getPoint().y() + painter->fontMetrics().boundingRect(name).height()/3;
    painter->drawText(x_text, y_text, name);

}
