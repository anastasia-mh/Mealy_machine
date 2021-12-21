#ifndef MACHINE_H
#define MACHINE_H

#include "item.h"
#include "transition.h"

#include <QMap>
#include <QVector>


class Machine
{
private:
    static QMap<QString, Item> machine;
    static QVector<Transition> transitions;
    static void setPositions();

public:
    static int load(QString filename);
    static void doPainting(QPainter *painter);
};

#endif // MACHINE_H
