#include "mytriangle.h"

MyTriangle::MyTriangle(QGraphicsItem *parent) : Figure{parent}
{}

QPainterPath MyTriangle::shape() const
{
    QPainterPath path;
    QPointF p1 = QPointF(pointFromRect1.x() * rectDraw().width() + rectDraw().topLeft().x(), pointFromRect1.y() * rectDraw().height() + rectDraw().topLeft().y());
    QPointF p2 = QPointF(pointFromRect2.x() * rectDraw().width() + rectDraw().topLeft().x(), pointFromRect2.y() * rectDraw().height() + rectDraw().topLeft().y());
    QPointF p3 = QPointF(pointFromRect3.x() * rectDraw().width() + rectDraw().topLeft().x(), pointFromRect3.y() * rectDraw().height() + rectDraw().topLeft().y());
    path.addPolygon(QPolygonF({p1, p2, p3}));
    return path;
}

void MyTriangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QBrush brush = QBrush(this->myColor);
    painter->setBrush(brush);
    painter->setPen(QPen(Qt::white, 1));
    if(myPoint1 != QPointF(-1, -1) && myPoint2 != QPointF(-1, -1) && myPoint3 == QPointF(-1, -1))
    {
        painter->drawLine(myPoint1, myPoint2);
    }
    else if(myPoint1 != QPointF(-1, -1) && myPoint2 != QPointF(-1, -1) && myPoint3 != QPointF(-1, -1))
    {
        QPolygonF poly;
        updatePoints();
        poly = QPolygonF({p1, p2, p3});
        painter->drawPolygon(poly);
    }

    Figure::paint(painter, option, widget);
}

void MyTriangle::setPoint1(QPointF x)
{
    myPoint1 = x;
    updateRect();

}

void MyTriangle::setPoint2(QPointF x)
{
    myPoint2 = x;
    updateRect();
}

void MyTriangle::setPoint3(QPointF x)
{
    myPoint3 = x;
    updateRect();
}

void MyTriangle::setCreatedPoints()
{
    pointFromRect1 = QPointF(( myPoint1.x() - rectDraw().topLeft().x()) / rectDraw().width(), (myPoint1.y() - rectDraw().topLeft().y()) / rectDraw().height());
    pointFromRect2 = QPointF(( myPoint2.x() - rectDraw().topLeft().x()) / rectDraw().width(), (myPoint2.y() - rectDraw().topLeft().y()) / rectDraw().height());
    pointFromRect3 = QPointF(( myPoint3.x() - rectDraw().topLeft().x()) / rectDraw().width(), (myPoint3.y() - rectDraw().topLeft().y()) / rectDraw().height());
}

void MyTriangle::updateRect()
{
    if(myPoint3 == QPointF(-1, -1))
    {
        int x = qMin(myPoint1.x(), myPoint2.x());
        int y = qMin(myPoint1.y(), myPoint2.y());
        int w = qMax(myPoint1.x(), myPoint2.x());
        int h = qMax(myPoint1.y(), myPoint2.y());
        setGeometryDraw(x, y, w-x, h-y);
    }
    else
    {
        int x = qMin(myPoint1.x(), qMin(myPoint2.x(), myPoint3.x()));
        int y = qMin(myPoint1.y(), qMin(myPoint2.y(), myPoint3.y()));
        int w = qMax(myPoint1.x(), qMax(myPoint2.x(), myPoint3.x()));
        int h = qMax(myPoint1.y(), qMax(myPoint2.y(), myPoint3.y()));

        setGeometryDraw(x, y, w-x, h-y);
    }
}

void MyTriangle::updatePoints()
{
    p1 = QPointF(pointFromRect1.x() * rectDraw().width() + rectDraw().topLeft().x(), pointFromRect1.y() * rectDraw().height() + rectDraw().topLeft().y());
    p2 = QPointF(pointFromRect2.x() * rectDraw().width() + rectDraw().topLeft().x(), pointFromRect2.y() * rectDraw().height() + rectDraw().topLeft().y());
    p3 = QPointF(pointFromRect3.x() * rectDraw().width() + rectDraw().topLeft().x(), pointFromRect3.y() * rectDraw().height() + rectDraw().topLeft().y());
}

void MyTriangle::updateCenterMass()
{
    updatePoints();
    this->myCenterMass = QPointF((p1.x() + p2.x() + p3.x()) / 3, (p1.y() + p2.y() + p3.y()) / 3);
}

void MyTriangle::updateSquare()
{
    updatePoints();
    this->mySquare = qAbs((p1.x()-p3.x()) * (p2.y() - p3.y()) - (p2.x() - p3.x()) * (p1.y() - p3.y())) / 2;
}

void MyTriangle::updatePerimeter()
{
    updatePoints();
    this->myPerimeter = qHypot(p1.x() - p2.x(), p1.y() - p2.y()) +
                        qHypot(p1.x() - p3.x(), p1.y() - p3.y()) +
                        qHypot(p2.x() - p3.x(), p2.y() - p3.y());
}
