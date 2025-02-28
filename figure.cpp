#include "figure.h"

Figure::Figure(QGraphicsItem *parent)
    : QGraphicsItem(parent)
{
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);
    this->setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

QRectF Figure::boundingRect() const
{
    QRectF geom = QRectF(myRect);
    geom = geom.normalized();
    geom += marginRect;
    return geom;
}

void Figure::setGeometryDraw(QRectF rect)
{
    prepareGeometryChange();
    this->myRect = rect;
    this->updateProperties();
}

void Figure::setGeometryDraw(qreal x, qreal y, qreal w, qreal h)
{
    prepareGeometryChange();
    this->myRect = QRectF(x, y, w, h);
    this->updateProperties();
}

void Figure::setPosDraw(QPointF pos)
{
    prepareGeometryChange();
    this->myRect.setTopLeft(pos);
    this->updateProperties();
}

void Figure::setPosDraw(qreal x, qreal y)
{
    prepareGeometryChange();
    this->myRect.setTopLeft(QPointF(x, y));
    this->updateProperties();
}

void Figure::setSizeDraw(QPointF size)
{
    prepareGeometryChange();
    this->myRect.setBottomRight(size);
    this->updateProperties();
}

void Figure::setSizeDraw(qreal w, qreal h)
{
    prepareGeometryChange();
    this->myRect.setBottomRight(QPointF(w, h));
    this->updateProperties();
}

void Figure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option)
    Q_UNUSED(widget)

    if(this->isSelected())
    {
        painter->setPen(QPen(Qt::red, 2, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(this->boundingRect());
        painter->setPen(QPen(Qt::red, 5));
        painter->drawPoint(myCenterMass);
    }
}

void Figure::updateCenterMass()
{
    myCenterMass = rectDraw().center();
}

void Figure::updateSquare()
{
    mySquare = rectDraw().size().height() * rectDraw().size().width();
}

void Figure::updatePerimeter()
{
    myPerimeter = (rectDraw().size().height() + rectDraw().size().width())*2;
}

void Figure::updateProperties()
{
    this->updateCenterMass();
    this->updatePerimeter();
    this->updateSquare();
}
