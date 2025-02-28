#ifndef MYTRIANGLE_H
#define MYTRIANGLE_H

#include <QPolygonF>
#include "figure.h"

class MyTriangle : public Figure
{
public:
    MyTriangle(QGraphicsItem *parent = nullptr);
    QPainterPath shape() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    QList<QPointF> points() { return QList<QPointF>{myPoint1, myPoint2, myPoint3}; };
    void setPoint1(QPointF x);
    void setPoint2(QPointF x);
    void setPoint3(QPointF x);
    void setCreatedPoints();
    void updateRect();
    void updatePoints();

protected:
    void updateCenterMass() override;
    void updateSquare() override;
    void updatePerimeter() override;

private:
    QPointF myPoint1 = QPointF(0, 0);
    QPointF myPoint2 = QPointF(0, 0);
    QPointF myPoint3 = QPointF(-1, -1);
    QPointF pointFromRect1 = QPointF(-1, -1);
    QPointF pointFromRect2 = QPointF(-1, -1);
    QPointF pointFromRect3 = QPointF(-1, -1);
    QPointF p1;
    QPointF p2;
    QPointF p3;
};

#endif // MYTRIANGLE_H
