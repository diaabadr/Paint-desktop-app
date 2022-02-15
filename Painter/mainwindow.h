#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "shape.h"
#include <QMainWindow>
#include "Constants.h"
#include <QGeoCircle>
#include <QVector>
#include "straightline.h"
#include "circle.h"
#include "rectangle.h"
#include <QStack>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QPainter;
class QImage;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
protected:
   QString getShapeName();
   void paintEvent(QPaintEvent *e)override;
    void mousePressEvent(QMouseEvent *e)override;
    void mouseMoveEvent(QMouseEvent *e)override;
    void mouseReleaseEvent(QMouseEvent *e)override;
    QRect directionOfDraw(const QPoint &endPoint);
    void drawRectangle( QPoint begin, QPoint end);
    void draw_circle(const QPoint startPoint,const QPoint endPoint);
    QLine directionOfDrawLine(const QPoint &endPoint);
    void DrawLine(QPoint begin,QPoint end);
    bool isValidName(QString name);
    void mouseDoubleClickEvent(QMouseEvent *e)override;

private slots:

    void on_actionQuit_triggered();

    void on_actionLine_triggered();

    void on_actionRectangle_triggered();

    void on_actionColor_triggered();

    void on_actionThickness_triggered();

    void on_actionNew_triggered();

    void on_actionCircle_triggered();
    void on_actionUndo_triggered();

    void on_actionRedo_triggered();

    void on_ok_clicked();
void hide_inputDialog();
void on_actionManual_input_triggered();

void on_actionSearch_triggered();

void on_actionSort_triggered();

private:
    Ui::MainWindow *ui;
    QVector <Shape*>shapes;
    QStack<Shape*>removedshapes;
    QImage* sketch[100];
    QImage* redoImgs[100];
    int currimage=0;
    int undotimes=0;
    QVector <QString>sketchname;
    QPainter *mPainter;
    QImage *mImage;
    QImage *oldImage;
    QPoint mBegin;
    QPoint mEnd;
    bool mEnabled;
    int mSize;
    QColor mColor;
     QRect rect;
     QLine line;
bool rightClick;
int redoCounter=0;
     //QGeoCircle circle;
     ToolType currentTool;
};
#endif // MAINWINDOW_H
