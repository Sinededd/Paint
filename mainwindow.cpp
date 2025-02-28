#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    scene = new PaintScene(this);
    scene->setSceneRect(QRectF(0,0,2000, 1000));
    scene->addItem(new MyRect());

    createToolBar();
    createDock();

    QVBoxLayout *layout = new QVBoxLayout;
    view = new QGraphicsView(scene);
    view->setMouseTracking(true);
    layout->addWidget(view);

    QWidget *widget = new QWidget;
    widget->setLayout(layout);


    setCentralWidget(widget);

    connect(rectButton, &QAction::toggled, this, &MainWindow::setPressedFigType);
    connect(ellipseButton, &QAction::toggled, this, &MainWindow::setPressedFigType);
    connect(starButton, &QAction::toggled, this, &MainWindow::setPressedFigType);
    connect(hexagonButton, &QAction::toggled, this, &MainWindow::setPressedFigType);
    connect(triangleButton, &QAction::toggled, this, &MainWindow::setPressedFigType);
    connect(this, &MainWindow::sendInsertFigure, scene, &PaintScene::insertFigure);
    connect(scene, &PaintScene::figureHasAdded, this, &MainWindow::resetFigureAction);
    // connect(scene, &QGraphicsScene::selectionChanged, this, &MainWindow::setSpinBoxes);
    connect(scene, &QGraphicsScene::changed, this, &MainWindow::setSpinBoxes);

}

void MainWindow::setPressedFigType(bool isPressed)
{
    PaintScene::FigureType ftype = PaintScene::FigureType::None;
    if(isPressed == 0)
    {
        emit this->sendInsertFigure(ftype);
        return;
    }
    if(sender() == this->rectButton)
    {
        ftype = PaintScene::FigureType::Rect;
    }
    else if(sender() == this->ellipseButton)
    {
        ftype = PaintScene::FigureType::Ellipse;
    }
    else if(sender() == this->starButton)
    {
        ftype = PaintScene::FigureType::Star;
    }
    else if(sender() == this->hexagonButton)
    {
        ftype = PaintScene::FigureType::Hexagon;
    }
    else if(sender() == this->triangleButton)
    {
        ftype = PaintScene::FigureType::Triangle;
    }

    emit this->sendInsertFigure(ftype);
}

void MainWindow::resetFigureAction()
{
    figureAction->checkedAction()->toggle();
}

void MainWindow::setSpinBoxes()
{
    if(scene->selectedItems().size() != 1)
    {
        xSpinBox->setEnabled(false);
        ySpinBox->setEnabled(false);
        wSpinBox->setEnabled(false);
        hSpinBox->setEnabled(false);
        rotateSpinBox->setEnabled(false);
        squareLable->setText("Площадь:  0");
        perimeterLable->setText("Периметр: 0");
        amountStarLable->hide();
        amountStarSpinBox->hide();
        radiusStarLable->hide();
        radiusStarSpinBox->hide();
    }
    else
    {
        disconnectSpinBoxs();

        xSpinBox->setEnabled(true);
        ySpinBox->setEnabled(true);
        wSpinBox->setEnabled(true);
        hSpinBox->setEnabled(true);
        rotateSpinBox->setEnabled(true);

        Figure *tempFig = dynamic_cast<Figure *>(scene->selectedItems().at(0));
        if(tempFig->figureType() == Figure::FigureType::Star)
        {
            squareLable->hide();
            perimeterLable->hide();
            amountStarLable->show();
            amountStarSpinBox->show();
            radiusStarLable->show();
            radiusStarSpinBox->show();
            amountStarSpinBox->setValue(dynamic_cast<MyStar *>(tempFig)->amountVert());
            radiusStarSpinBox->setValue(dynamic_cast<MyStar *>(tempFig)->innerRadius());
        }
        else if(tempFig->figureType() == Figure::FigureType::Hexagon)
        {
            squareLable->hide();
            perimeterLable->hide();
            amountStarLable->show();
            amountStarSpinBox->show();
            radiusStarLable->hide();
            radiusStarSpinBox->hide();
            amountStarSpinBox->setValue(dynamic_cast<MyStar *>(tempFig)->amountVert());
            radiusStarSpinBox->setValue(dynamic_cast<MyStar *>(tempFig)->innerRadius());
        }
        else
        {
            amountStarLable->hide();
            amountStarSpinBox->hide();
            radiusStarLable->hide();
            radiusStarSpinBox->hide();
            squareLable->show();
            perimeterLable->show();
        }

        QPointF newPosit(tempFig->posDraw() + tempFig->pos());
        xSpinBox->setValue(newPosit.x());
        ySpinBox->setValue(newPosit.y());
        wSpinBox->setValue(tempFig->rectDraw().size().width());
        hSpinBox->setValue(tempFig->rectDraw().size().height());
        rotateSpinBox->setValue(tempFig->rotation());
        squareLable->setText("Площадь:  " + QString::number(tempFig->square()));
        perimeterLable->setText("Периметр: " + QString::number(tempFig->perimeter()));

        connectSpinBoxs();
    }
}

void MainWindow::createToolBar()
{
    editToolBar = new QToolBar(this);
    addToolBar(editToolBar);

    rectButton = new QAction("Rect");
    ellipseButton = new QAction("Ellipse");
    starButton = new QAction("Star");
    hexagonButton = new QAction("Hexagon");
    triangleButton = new QAction("Triangle");
    rectButton->setCheckable(true);
    ellipseButton->setCheckable(true);
    starButton->setCheckable(true);
    hexagonButton->setCheckable(true);
    triangleButton->setCheckable(true);

    QPixmap pixmap(16, 16);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    painter.setBrush(Qt::white);
    painter.drawRect(0, 2, 16, 14);
    rectButton->setIcon(QIcon(pixmap));
    painter.end();


    painter.begin(&pixmap);
    pixmap.fill(Qt::transparent);
    painter.setBrush(Qt::white);
    painter.drawEllipse(0, 2, 16, 14);
    ellipseButton->setIcon(QIcon(pixmap));
    painter.end();

    QVector<QPointF> starPoints = {QPointF(8,1), QPointF(9.88091,6.41115),
                                   QPointF(15.6085,6.52786), QPointF(11.0434,9.98885),
                                   QPointF(12.7023,15.4721), QPointF(8,12.2),
                                   QPointF(3.29772,15.4721), QPointF(4.95662,9.98885),
                                   QPointF(0.391548,6.52786), QPointF(6.11909,6.41115)};
    painter.begin(&pixmap);
    pixmap.fill(Qt::transparent);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawPolygon(starPoints);
    starButton->setIcon(QIcon(pixmap));
    painter.end();


    starPoints = {QPointF(8,1), QPointF(15.6085,6.52786),
                  QPointF(12.7023,15.4721), QPointF(3.29772,15.4721),
                  QPointF(0.391548,6.52786)};
    painter.begin(&pixmap);
    pixmap.fill(Qt::transparent);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawPolygon(starPoints);
    hexagonButton->setIcon(QIcon(pixmap));
    painter.end();


    starPoints = {QPointF(0,17), QPointF(8.33333,1), QPointF(16,17)};
    painter.begin(&pixmap);
    pixmap.fill(Qt::transparent);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawPolygon(starPoints);
    triangleButton->setIcon(QIcon(pixmap));
    painter.end();


    figureAction = new QActionGroup(editToolBar);
    figureAction->addAction(rectButton);
    figureAction->addAction(ellipseButton);
    figureAction->addAction(starButton);
    figureAction->addAction(hexagonButton);
    figureAction->addAction(triangleButton);
    figureAction->setExclusionPolicy(QActionGroup::ExclusionPolicy::ExclusiveOptional);

    editToolBar->addAction(rectButton);
    editToolBar->addAction(ellipseButton);
    editToolBar->addAction(starButton);
    editToolBar->addAction(hexagonButton);
    editToolBar->addAction(triangleButton);
    editToolBar->addSeparator();
}

void MainWindow::createDock()
{
    //Инициализация боковой панели
    dock = new QDockWidget(this);
    dock->setFeatures(QDockWidget::DockWidgetFeatures({QDockWidget::DockWidgetClosable, QDockWidget::DockWidgetMovable}));
    dock->setAllowedAreas(Qt::DockWidgetAreas({Qt::LeftDockWidgetArea, Qt::RightDockWidgetArea}));
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, dock);

    dockContent = new QWidget(dock);
    dock->setWidget(dockContent);

    QVBoxLayout *contentLayout = new QVBoxLayout(dockContent);
    QGridLayout *posSpinBoxes = new QGridLayout();
    contentLayout->addLayout(posSpinBoxes);
    contentLayout->addStretch();

    QLabel *posLable = new QLabel("Позиция", dockContent);
    QLabel *sizeLable = new QLabel("Размер", dockContent);
    QLabel *rotateLable = new QLabel("Поворот", dockContent);
    amountStarLable = new QLabel("Вершины", dockContent);
    amountStarLable->hide();
    radiusStarLable = new QLabel("Радиус", dockContent);
    amountStarLable->hide();
    squareLable = new QLabel("Площадь:  0", dockContent);
    perimeterLable = new QLabel("Периметр: 0", dockContent);

    xSpinBox = new QSpinBox(dockContent);
    ySpinBox = new QSpinBox(dockContent);
    xSpinBox->setMaximum(9999);
    ySpinBox->setMaximum(9999);
    wSpinBox = new QSpinBox(dockContent);
    hSpinBox = new QSpinBox(dockContent);
    wSpinBox->setMaximum(9999);
    hSpinBox->setMaximum(9999);
    rotateSpinBox = new QSpinBox(dockContent);
    rotateSpinBox->setMaximum(9999);
    rotateSpinBox->setMinimum(-9999);
    rotateSpinBox->setSuffix("°");
    amountStarSpinBox = new QSpinBox(dockContent);
    amountStarSpinBox->setMinimum(3);
    amountStarSpinBox->hide();
    radiusStarSpinBox = new QSpinBox(dockContent);
    radiusStarSpinBox->hide();
    radiusStarSpinBox->setMaximum(100);
    radiusStarSpinBox->setSuffix("%");
    posSpinBoxes->addWidget(posLable, 0, 0);
    posSpinBoxes->addWidget(xSpinBox, 1, 0);
    posSpinBoxes->addWidget(ySpinBox, 1, 1);
    posSpinBoxes->addWidget(sizeLable, 2, 0);
    posSpinBoxes->addWidget(wSpinBox, 3, 0);
    posSpinBoxes->addWidget(hSpinBox, 3, 1);
    posSpinBoxes->addWidget(rotateLable, 4, 0);
    posSpinBoxes->addWidget(rotateSpinBox, 5, 0);
    posSpinBoxes->addWidget(squareLable, 6, 0, 1, 0);
    posSpinBoxes->addWidget(perimeterLable, 7, 0, 1, 0);
    posSpinBoxes->addWidget(amountStarLable, 8, 0);
    posSpinBoxes->addWidget(radiusStarLable, 8, 1);
    posSpinBoxes->addWidget(amountStarSpinBox, 9, 0);
    posSpinBoxes->addWidget(radiusStarSpinBox, 9, 1);

    connectSpinBoxs();
    connect(amountStarSpinBox, &QSpinBox::valueChanged, scene, &PaintScene::setAmountStar);
    connect(radiusStarSpinBox, &QSpinBox::valueChanged, scene, &PaintScene::setRadiusStar);
    // dock->setLayout(vlayout);



}

void MainWindow::disconnectSpinBoxs()
{
    disconnect(xSpinBox, &QSpinBox::valueChanged, scene, &PaintScene::setXtoSelected);
    disconnect(ySpinBox, &QSpinBox::valueChanged, scene, &PaintScene::setYtoSelected);
    disconnect(hSpinBox, &QSpinBox::valueChanged, scene, &PaintScene::setHtoSelected);
    disconnect(wSpinBox, &QSpinBox::valueChanged, scene, &PaintScene::setWtoSelected);
    disconnect(rotateSpinBox, &QSpinBox::valueChanged, scene, &PaintScene::setRotationtoSelected);
}

void MainWindow::connectSpinBoxs()
{
    connect(xSpinBox, &QSpinBox::valueChanged, scene, &PaintScene::setXtoSelected);
    connect(ySpinBox, &QSpinBox::valueChanged, scene, &PaintScene::setYtoSelected);
    connect(hSpinBox, &QSpinBox::valueChanged, scene, &PaintScene::setHtoSelected);
    connect(wSpinBox, &QSpinBox::valueChanged, scene, &PaintScene::setWtoSelected);
    connect(rotateSpinBox, &QSpinBox::valueChanged, scene, &PaintScene::setRotationtoSelected);
}
