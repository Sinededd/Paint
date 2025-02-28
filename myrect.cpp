#include "myrect.h"
#include<QBrush>
#include<QPainter>

MyRect::MyRect(QGraphicsItem *parent) : Figure{parent}
{}

QPainterPath MyRect::shape() const
{
    QPainterPath path;
    path.addRect(myRect);
    return path;
}

void MyRect::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QBrush brush = QBrush(this->myColor);
    painter->fillRect(myRect, brush);

    Figure::paint(painter, option, widget);
}
