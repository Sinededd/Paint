#ifndef PAINTSCENE_H
#define PAINTSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPoint>
#include <QKeyEvent>
#include <QtGlobal>
#include "myrect.h"
#include "myellipse.h"
#include "mystar.h"
#include "mytriangle.h"


class PaintScene : public QGraphicsScene
{
    Q_OBJECT
public:
    enum Mode { InsertFigure, MoveItem };
    enum FigureType {None, Rect, Ellipse, Star, Hexagon, Triangle};

    explicit PaintScene(QObject *parent = nullptr);

public slots:
    void setMode(Mode mode);
    void insertFigure(FigureType ftype);
    void deleteItem();
    void setXtoSelected(int x);
    void setYtoSelected(int x);
    void setWtoSelected(int x);
    void setHtoSelected(int x);
    void setRotationtoSelected(int x);
    void setAmountStar(int x);
    void setRadiusStar(qreal x);

signals:
    void figureHasAdded();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent) override;
    void keyPressEvent(QKeyEvent *keyEvent) override;
    void keyReleaseEvent(QKeyEvent *keyEvent) override;


private:
    bool squareDrawMode = 0;

    Mode myMode;
    FigureType myFType;
    Figure *tempFigure;
};

#endif // PAINTSCENE_H
