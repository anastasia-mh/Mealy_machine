#ifndef ITEM_H
#define ITEM_H

#include <QPainter>
#include <QString>



class Item
{
public:
    static const int DEFAULT_DISTANCE = 160;
private:
    static const QSize DEFAULT_SIZE;
    //QString name;
    QPoint point;//точка центра
    QSize size;//размер
public:
    enum last_lines{
        right_top = 0,
        right_bottom = 1,
        left_top = 2,
        left_bottom = 3,
        count
    };
    int height_lines[count] = {0, 0, 0, 0};
    Item(QPoint point = QPoint(0,0), const QSize &size = DEFAULT_SIZE);
    void doPainting(QPainter *painter, const QString &name);
    QPoint getPoint() const;
    void setPoint(QPoint newPoint);
    const QSize &getSize() const;
    void setSize(const QSize &newSize);
};

#endif // ITEM_H
