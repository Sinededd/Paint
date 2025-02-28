#include "mystar.h"
#include<QBrush>
#include<QPainter>

MyStar::MyStar(QGraphicsItem *parent) : Figure{parent}
{}

QPainterPath MyStar::shape() const
{
    QPainterPath path;

    QPointF center = myRect.center();
    int points = amountVert();
    qreal innerRadius = myRadius;
    qreal angleStep = 2 * M_PI / points;
    qreal a = myRect.size().width();
    qreal b = myRect.size().height();
    QVector<QPointF> starPoints;

    for (int i = 0; i < points; ++i) {
        qreal outerAngle = i * angleStep - M_PI / 2;
        qreal xOuter = a / 2 * qCos(outerAngle);
        qreal yOuter = b / 2 * qSin(outerAngle);
        starPoints.append(QPointF(xOuter + center.x(), yOuter + center.y()));

        if(this->figureType() == Figure::FigureType::Star)
        {
            qreal innerAngle = outerAngle + angleStep / 2;
            qreal xInner = innerRadius * a / 2 * qCos(innerAngle);
            qreal yInner = innerRadius * b / 2 * qSin(innerAngle);
            starPoints.append(QPointF(xInner + center.x(), yInner + center.y()));
        }
    }
    QPolygonF starPolygon(starPoints);
    path.addPolygon(starPolygon);

    return path;
}

void MyStar::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(this->myColor);

    QPointF center = rectDraw().center();
    int points = amountVert();
    qreal innerRadius = myRadius;
    qreal angleStep = 2 * M_PI / points;
    qreal a = rectDraw().size().width();
    qreal b = rectDraw().size().height();
    QVector<QPointF> starPoints;

    for (int i = 0; i < points; ++i) {
        qreal outerAngle = i * angleStep - M_PI / 2;
        qreal xOuter = a / 2 * qCos(outerAngle);
        qreal yOuter = b / 2 * qSin(outerAngle);
        starPoints.append(QPointF(xOuter + center.x(), yOuter + center.y()));


        if(this->figureType() == Figure::FigureType::Star)
        {
            qreal innerAngle = outerAngle + angleStep / 2;
            qreal xInner = innerRadius * a / 2 * qCos(innerAngle);
            qreal yInner = innerRadius * b / 2 * qSin(innerAngle);
            starPoints.append(QPointF(xInner + center.x(), yInner + center.y()));
        }
    }
    QPolygonF starPolygon(starPoints);
    painter->drawPolygon(starPolygon);


    Figure::paint(painter, option, widget);
}

void MyStar::updateSquare()
{
    mySquare = 0;
}

void MyStar::updatePerimeter()
{
    myPerimeter = 0;
}
