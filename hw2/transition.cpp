#include "transition.h"

void Transition::setStart(QPoint newStart)
{
    start = newStart;
}

void Transition::setEnd(QPoint newEnd)
{
    end = newEnd;
}

const QString &Transition::getFrom() const
{
    return from;
}

const QString &Transition::getTo() const
{
    return to;
}

void Transition::setHight(int newHight)
{
    hight = newHight;
}

Transition::Transition(const QString &from, const QString &to, const QString &in_signal, const QString &out_signal) : from(from),
    to(to),
    in_signal(in_signal),
    out_signal(out_signal)
{}

void Transition::doPainting(QPainter *painter)
{
    QFont font = painter->font();
    font.setPixelSize(15);
    painter->setFont(font);
    QPen pen = painter->pen();
    pen.setWidth(1);
    painter->setPen(pen);
    QRect rect(start, end);
    if(from.compare(to) == 0){
        //end = start + QPoint(DEFAULT_DELTA*2, 0);
        rect.adjust(0, DEFAULT_DELTA, DEFAULT_DELTA*2, -DEFAULT_DELTA);
        painter->drawArc(rect, 150*16, -300*16);
        painter->drawText(rect, Qt::AlignRight | Qt::AlignVCenter, in_signal + "|" + out_signal + " ");
        arrow(painter, rect.center() - QPoint(0, DEFAULT_DELTA), right);
        arrow(painter, rect.center() + QPoint(0, DEFAULT_DELTA), left);
    } else {
        rect.adjust(0, hight, 0, -hight);
        if (hight > 0){
            painter->drawArc(rect, 0, -180*16);
            QRect text = painter->boundingRect(rect, Qt::AlignHCenter | Qt::AlignTop, in_signal + "|" + out_signal);
            text.moveBottom(text.bottom() + 3);
            painter->drawText(text, in_signal + "|" + out_signal);
            arrow(painter, rect.center() + QPoint(0, hight), left);
        }
        else {
            painter->drawArc(rect, 0, 180*16);
            QRect text = painter->boundingRect(rect, Qt::AlignHCenter | Qt::AlignTop, in_signal + "|" + out_signal);
            text.moveBottom(text.bottom() - text.height() - 3);
            painter->drawText(text, in_signal + "|" + out_signal);
            arrow(painter, rect.center() + QPoint(0, hight), right);
        }
    }
}

void Transition::arrow(QPainter *painter, const QPoint &point, int direction)
{
    painter->setBrush(QBrush(Qt::black));
    QPolygon triangle;
    if(direction == left) {
        triangle << point + QPoint(5, -5);
        triangle << point + QPoint(5, 5);
        triangle << point + QPoint(-5, 0);
    } else{
        triangle << point + QPoint(-5, -5);
        triangle << point + QPoint(-5, 5);
        triangle << point + QPoint(5, 0);
    }
    painter->drawPolygon(triangle);
}

Transition::Transition()
{

}
