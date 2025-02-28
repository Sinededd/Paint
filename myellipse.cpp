#include "myellipse.h"

MyEllipse::MyEllipse(QGraphicsItem *parent) : Figure{parent}
{}

QPainterPath MyEllipse::shape() const
{
    QPainterPath path;
    path.addEllipse(myRect);
    return path;
}

void MyEllipse::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QBrush brush = QBrush(this->myColor);
    QPainterPath path = QPainterPath();
    path.addEllipse(myRect);
    painter->fillPath(path, brush);

    Figure::paint(painter, option, widget);
}

void MyEllipse::updateSquare()
{
    mySquare = rectDraw().size().height() * rectDraw().size().width() / 4 * M_PI;
}

void MyEllipse::updatePerimeter()
{
    qreal a = rectDraw().size().width() / 2;
    qreal b = rectDraw().size().height() / 2;
    myPerimeter = 4 * (M_PI * a * b + (a - b)*(a - b)) / (a + b);
}
