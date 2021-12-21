#ifndef TRANSITION_H
#define TRANSITION_H

#include <QPainter>
#include <QString>



class Transition
{
public:
    static const int DEFAULT_DELTA = 30;
private:
    QString
        from,
        to,
        in_signal,
        out_signal;
    QPoint start, end;
    int hight = 0;
    static void arrow(QPainter *painter, const QPoint &point, int direction);
    enum direction{
        right = 0,
        left = 1
    };
public:
    Transition();
    Transition(const QString &from, const QString &to, const QString &in_signal, const QString &out_signal);
    void doPainting(QPainter *painter);
    void setStart(QPoint newStart);
    void setEnd(QPoint newEnd);
    const QString &getFrom() const;
    const QString &getTo() const;
    void setHight(int newHight);
};

#endif // TRANSITION_H
