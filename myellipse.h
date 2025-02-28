#ifndef MYELLIPSE_H
#define MYELLIPSE_H

#include "figure.h"

class MyEllipse : public Figure
{
public:
    explicit MyEllipse(QGraphicsItem *parent = nullptr);
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

protected:
    void updateSquare() override;
    void updatePerimeter() override;
signals:
};

#endif // MYELLIPSE_H
