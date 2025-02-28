#include "paintscene.h"



PaintScene::PaintScene(QObject *parent)
    : QGraphicsScene{parent}
{
    tempFigure = nullptr;
    myMode = Mode::MoveItem;
}

void PaintScene::setMode(Mode mode)
{
    myMode = mode;
}

void PaintScene::insertFigure(FigureType ftype)
{
    myMode = Mode::InsertFigure;
    myFType = ftype;
}

void PaintScene::deleteItem()
{
    QList<QGraphicsItem *> selectedItems = this->selectedItems();
    for(int i = 0; i < selectedItems.size(); i++)
    {
        this->removeItem(selectedItems[i]);
        delete selectedItems[i];
    }
}

void PaintScene::setXtoSelected(int x)
{
    if(selectedItems().size()>0)
    {
        Figure *temp = dynamic_cast<Figure *>(selectedItems().at(0));
        temp->setGeometryDraw(QRectF(QPointF(x - temp->pos().x(), temp->posDraw().y()), temp->rectDraw().size()));
        temp->setTransformOriginPoint(temp->centerMass());
    }
}

void PaintScene::setYtoSelected(int x)
{
    if(selectedItems().size()>0)
    {
        Figure *temp = dynamic_cast<Figure *>(selectedItems().at(0));
        temp->setGeometryDraw(QRectF(QPointF(temp->posDraw().x(), x - temp->pos().y()), temp->rectDraw().size()));
        temp->setTransformOriginPoint(temp->centerMass());
    }
}

void PaintScene::setWtoSelected(int x)
{
    Figure *temp = dynamic_cast<Figure *>(selectedItems().at(0));
    temp->setGeometryDraw(QRectF(temp->rectDraw().topLeft(), QSizeF(x, temp->rectDraw().size().height())));
}

void PaintScene::setHtoSelected(int x)
{
    Figure *temp = dynamic_cast<Figure *>(selectedItems().at(0));
    temp->setGeometryDraw(QRectF(temp->rectDraw().topLeft(), QSizeF(temp->rectDraw().size().width(), x)));
}

void PaintScene::setRotationtoSelected(int x)
{
    Figure *temp = dynamic_cast<Figure *>(selectedItems().at(0));
    temp->setTransformOriginPoint(temp->centerMass());
    temp->setRotation(x);
}

void PaintScene::setAmountStar(int x)
{
    MyStar *star = dynamic_cast<MyStar *>(selectedItems().at(0));
    star->setAmountVert(x);
    star->update();
}

void PaintScene::setRadiusStar(qreal x)
{
    MyStar *star = dynamic_cast<MyStar *>(selectedItems().at(0));
    star->setInnerRadius(x);
    star->update();
}

void PaintScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(mouseEvent->button() != Qt::LeftButton)
    {
        QGraphicsScene::mousePressEvent(mouseEvent);
        return;
    }

    switch (myMode) {
    case Mode::InsertFigure:
        if(tempFigure == nullptr)
        {
            switch (myFType) {
            case FigureType::Rect:
                this->tempFigure = new MyRect();
                this->tempFigure->setFigureType(Figure::FigureType::Rect);
                break;
            case FigureType::Ellipse:
                this->tempFigure = new MyEllipse();
                this->tempFigure->setFigureType(Figure::FigureType::Ellipse);
                break;
            case FigureType::Star:
                this->tempFigure = new MyStar();
                this->tempFigure->setFigureType(Figure::FigureType::Star);
                break;
            case FigureType::Hexagon:
                this->tempFigure = new MyStar();
                dynamic_cast<MyStar *>(this->tempFigure)->setInnerRadius(100);
                this->tempFigure->setFigureType(Figure::FigureType::Hexagon);
                break;
            case FigureType::Triangle:
                this->tempFigure = new MyTriangle();
                this->tempFigure->setFigureType(Figure::FigureType::Triangle);
                break;
            default:
                QGraphicsScene::mousePressEvent(mouseEvent);
                qInfo() << "none";
                myMode = Mode::MoveItem;
                return;
                break;
            }
            if(this->tempFigure->figureType() == Figure::FigureType::Triangle)
            {
                MyTriangle *tempTriangle = dynamic_cast<MyTriangle *>(this->tempFigure);
                tempTriangle->setPoint1(mouseEvent->scenePos());
                tempTriangle->setPoint2(mouseEvent->scenePos());
                this->addItem(tempFigure);
            }
            else
            {
                this->tempFigure->setPosDraw(mouseEvent->scenePos());
                this->tempFigure->setSizeDraw(mouseEvent->scenePos());
                this->addItem(tempFigure);
            }
        }
        else
        {
            if(tempFigure->figureType() == Figure::FigureType::Triangle)
            {
                MyTriangle *tempTriangle = dynamic_cast<MyTriangle *>(this->tempFigure);
                if(tempTriangle->points().at(2) == QPointF(-1, -1))
                {
                    tempTriangle->setPoint3(mouseEvent->scenePos());
                }
                else
                {
                    emit figureHasAdded();
                    this->tempFigure->setSelected(true);
                    tempTriangle->setCreatedPoints();
                    this->tempFigure->updateProperties();
                    this->tempFigure = nullptr;
                    myMode = Mode::MoveItem;
                }
            }
            else
            {
                emit figureHasAdded();
                this->tempFigure->setSelected(true);
                this->tempFigure->updateProperties();
                this->tempFigure = nullptr;
                myMode = Mode::MoveItem;
            }
        }
        return;
        break;
    case Mode::MoveItem:

        break;
    default:
        break;
    }

    QGraphicsScene::mousePressEvent(mouseEvent);
}

void PaintScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(this->tempFigure == nullptr)
    {
        QGraphicsScene::mouseMoveEvent(mouseEvent);
        return;
    }
    if(this->tempFigure->figureType() == Figure::FigureType::Triangle)
    {
        MyTriangle *tempTriangle = dynamic_cast<MyTriangle *>(this->tempFigure);
        if(tempTriangle->points().at(2) == QPointF(-1, -1))
        {
            tempTriangle->setPoint2(mouseEvent->scenePos());
        }
        else
        {
            tempTriangle->setPoint3(mouseEvent->scenePos());
            tempTriangle->setCreatedPoints();
        }
        update();
        return;
    }

    if(squareDrawMode)
    {
        qreal width = mouseEvent->scenePos().x() - this->tempFigure->posDraw().x();
        qreal height = mouseEvent->scenePos().y() - this->tempFigure->posDraw().y();
        char hSign = (height > 0) ? 1 : -1;
        char wSign = (width > 0) ? 1 : -1;
        if(qAbs(width) < qAbs(height))
        {
            height = qAbs(width) * hSign;
        }
        else
        {
            width = qAbs(height) * wSign;
        }


        this->tempFigure->setSizeDraw(this->tempFigure->posDraw().x() + width, this->tempFigure->posDraw().y() + height);
    }
    else
    {
        this->tempFigure->setSizeDraw(mouseEvent->scenePos());
    }
    update();
}

void PaintScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if(this->tempFigure == nullptr)
    {
        QGraphicsScene::mouseReleaseEvent(mouseEvent);
        return;
    }

    if(mouseEvent->scenePos() != this->tempFigure->posDraw() && tempFigure->figureType() != Figure::FigureType::Triangle)
    {
        emit figureHasAdded();
        this->tempFigure->setSelected(true);
        this->tempFigure->updateProperties();
        // this->tempFigure->setGeometryDraw(this->tempFigure->rectDraw().normalized());
        this->tempFigure = nullptr;
        myMode = Mode::MoveItem;
    }

    QGraphicsScene::mouseReleaseEvent(mouseEvent);
}

void PaintScene::keyPressEvent(QKeyEvent *keyEvent)
{
    if(keyEvent->key() == Qt::Key_Delete)
    {
        deleteItem();
    }
    if(keyEvent->key() == Qt::Key_Control)
    {
        squareDrawMode = 1;
    }
}

void PaintScene::keyReleaseEvent(QKeyEvent *keyEvent)
{
    if(keyEvent->key() == Qt::Key_Control)
    {
        squareDrawMode = 0;
    }
}



