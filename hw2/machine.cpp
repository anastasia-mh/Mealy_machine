#include "machine.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <qmath.h>

QMap<QString, Item> Machine::machine;

QVector<Transition> Machine::transitions;

int Machine::load(QString filename = "input.json")
{
    QFile file(filename);
    if (file.size() == 0)
        return 2;

    if(!file.open(QIODevice::ReadOnly)){
        return 1;
    }

    QMap<QString, Item> loaded_data;
    QVector<Transition> transitions_loaded;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonObject itemObj;
    QJsonObject transitionObj;

    QJsonObject machineObj = doc.object();
    QJsonArray arrayTransitions = machineObj["Mealy machine"].toArray();
    for(const auto &trans:qAsConst(arrayTransitions)){
        transitionObj = trans.toObject();
        QString from = transitionObj["from"].toString();
        QString in_signal = transitionObj["in_signal"].toString();
        QString to = transitionObj["to"].toString();
        QString out_signal = transitionObj["out_signal"].toString();
        transitions_loaded.append(*(new Transition(from, to, in_signal, out_signal)));
        if (!loaded_data.contains(from))
            loaded_data.insert(from, *(new Item()));
        if (!loaded_data.contains(to))
            loaded_data.insert(to, *(new Item()));
    }

    machine = loaded_data;
    transitions = transitions_loaded;
    return 0;
}

void Machine::doPainting(QPainter *painter)
{
    setPositions();//позиционирование
    for (QMap<QString, Item>::iterator item = machine.begin(); item != machine.end(); item++){
        item->doPainting(painter, item.key());
    }
    for(Transition transition:qAsConst(transitions))
        transition.doPainting(painter);
}

void Machine::setPositions(){
    int i = 0;
    //для состояний
    for (QMap<QString, Item>::iterator item = machine.begin(); item != machine.end(); item++,i++){
            int x = Item::DEFAULT_DISTANCE;
            if (item!=machine.begin())
                x += (item-1).value().getPoint().x();
            int y = 0;
            item.value().setPoint(QPoint(x,y));
            for (int &h:item->height_lines)
                h = 0;
    }
    //для переходов
    //сортировка по длине
    std::sort(transitions.begin(),transitions.end(), [](const Transition &a, const Transition &b){
        int res_a = abs(a.getFrom().compare(a.getTo()));
        int res_b = abs(b.getFrom().compare(b.getTo()));
        return res_a < res_b;
    });
    for(int i = 0; i < transitions.count(); i++){
        QString from = transitions[i].getFrom(),
                to = transitions[i].getTo();
        int flag = from.compare(to);
        if(flag == 0){
            int delta = machine.value(from).getSize().width();
            transitions[i].setStart(machine.value(from).getPoint() + QPoint(delta, 0));
            transitions[i].setEnd(machine.value(to).getPoint() + QPoint(delta, 0));
        } else {
            int hight;
            if (flag < 0){
                int &top_from = machine[from].height_lines[machine.value(from).right_top];
                int &top_to = machine[to].height_lines[machine.value(from).left_top];
                if(top_from <= top_to){
                    top_from -= Transition::DEFAULT_DELTA;
                    top_to = top_from;
                } else {
                    top_to -= Transition::DEFAULT_DELTA;
                    top_from = top_to;
                }
                hight = top_from;
            } else //if (flag > 0)
            {
                int &bottom_from = machine[from].height_lines[machine.value(from).left_bottom];
                int &bottom_to = machine[to].height_lines[machine.value(from).right_bottom];
                if(bottom_from >= bottom_to){
                    bottom_from += Transition::DEFAULT_DELTA;
                    bottom_to = bottom_from;
                } else {
                    bottom_to += Transition::DEFAULT_DELTA;
                    bottom_from = bottom_to;
                }
                hight = bottom_from;
            }
            transitions[i].setHight(hight);

            int delta = machine.value(from).getSize().height();
            if(hight < 0)
                delta = -delta;
            transitions[i].setStart(machine.value(from).getPoint() + QPoint(0, delta));
            delta = machine.value(to).getSize().height();
            if(hight < 0)
                delta = -delta;
            transitions[i].setEnd(machine.value(to).getPoint() + QPoint(0, delta));
        }
    }
}

//позиционирование многоугольником (по кругу) (не прямая линия)
//void Machine::setPositions(QPainter *painter)
//{
//    int count = machine.count();
//    int i = 0;
//    for (QMap<QString, Item>::iterator item = machine.begin(); item != machine.end(); item++,i++){
//        int x = value_x(painter->window(), 90, i, count);
//        int y = value_y(90, i, count);
//        item.value().setPoint(QPoint(x,y));
//    }

//}

//int Machine::value_x(const QRect &rect, int f0, int i, int n)
//{
//    int x_centre = rect.width()/2;
//    int res = x_centre + 50*n*qCos(f0 + 2*M_PI*i/n);
//    return res;
//}

//int Machine::value_y(int f0, int i, int n)
//{
//    int y_centre = 150 + n*50;
//    int res = y_centre + 50*n*qSin(f0 + 2*M_PI*i/n);
//    return res;
//}
