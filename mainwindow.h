#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QAction>
#include <QToolButton>
#include <QHBoxLayout>
#include <QToolBar>
#include <QAbstractButton>
#include <QAction>
#include <QPixmap>
#include <QActionGroup>
#include <QDockWidget>
#include <QDoubleSpinBox>
#include <QGridLayout>
#include <QLabel>
#include "paintscene.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:
    void sendInsertFigure(PaintScene::FigureType);

private slots:
    void setPressedFigType(bool isPressed);
    void resetFigureAction();

public slots:
    void setSpinBoxes();

private:
    void createToolBar();
    void createDock();
    void disconnectSpinBoxs();
    void connectSpinBoxs();

    PaintScene *scene;
    QGraphicsView *view;

    QToolBar *editToolBar;

    QActionGroup *figureAction;
    QAction *rectButton;
    QAction *ellipseButton;
    QAction *starButton;
    QAction *hexagonButton;
    QAction *triangleButton;

    QDockWidget *dock;
    QWidget *dockContent;
    QSpinBox *xSpinBox;
    QSpinBox *ySpinBox;
    QSpinBox *wSpinBox;
    QSpinBox *hSpinBox;
    QSpinBox *rotateSpinBox;
    QSpinBox *amountStarSpinBox;
    QSpinBox *radiusStarSpinBox;
    QLabel *amountStarLable;
    QLabel *radiusStarLable;
    QLabel *squareLable;
    QLabel *perimeterLable;
};

#endif // MAINWINDOW_H
