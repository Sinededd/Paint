#ifndef MYRECT_H
#define MYRECT_H

#include"figure.h"

class MyRect : public Figure
{
public:
    MyRect(QGraphicsItem *parent = nullptr);
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
};

#endif // MYRECT_H
