#ifndef FIGURE_H
#define FIGURE_H

#include<QGraphicsItem>
#include<QPointF>
#include <QPainter>
#include <QRectF>


class Figure : public QGraphicsItem
{
public:
    enum FigureType {None, Rect, Ellipse, Star, Hexagon, Triangle};

    Figure(QGraphicsItem *parent = nullptr);
    QRectF boundingRect() const override;

    void setGeometryDraw(QRectF rect);
    void setGeometryDraw(qreal x, qreal y, qreal w, qreal h);
    void setPosDraw(QPointF pos);
    void setPosDraw(qreal x, qreal y);
    void setSizeDraw(QPointF size);
    void setSizeDraw(qreal w, qreal h);
    void setFigureType(FigureType t) { myType = t; }

    QPointF posDraw() { return myRect.topLeft(); }
    QPointF sizeDraw() { return myRect.bottomRight(); }
    QRectF rectDraw() const { return myRect.normalized(); }
    QPointF centerMass() { return myCenterMass; }
    qreal square() { return mySquare; }
    qreal perimeter() { return myPerimeter; }
    FigureType figureType() const { return myType; }

    void updateProperties();


protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    // QVariant itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value) override;

    virtual void updateCenterMass();
    virtual void updateSquare();
    virtual void updatePerimeter();

    QRectF myRect = QRectF(0, 0, 0, 0);
    QPointF myCenterMass = QPoint(0, 0);
    qreal mySquare = 0;
    qreal myPerimeter = 0;
    QColor myColor = "white";
    QColor myBorderColor = "black";
    qreal myBorderSize = 1;



private:
    FigureType myType = None;
    QMarginsF marginRect = QMarginsF(5, 5, 5, 5);
};

#endif // FIGURE_H
