#ifndef MYSTAR_H
#define MYSTAR_H


// #include <QPolygonF>
#include"figure.h"

class MyStar : public Figure
{
public:
    MyStar(QGraphicsItem *parent = nullptr);
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    int amountVert() const { return myAmountVert; }
    void setAmountVert(int x) { myAmountVert = x; }
    qreal innerRadius() { return myRadius * 100.0; }
    void setInnerRadius(qreal x) { myRadius = x / 100.0; }

protected:
    void updateSquare() override;
    void updatePerimeter() override;

private:
    int myAmountVert = 5;
    qreal myRadius = 0.4;
};

#endif // MYSTAR_H
