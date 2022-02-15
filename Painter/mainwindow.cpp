#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QDesktopWidget>
#include <QDir>
MainWindow::MainWindow(QWidget *parent)//the constructor 
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    currimage=0;
    mImage =new QImage(QApplication::desktop()->size(),QImage::Format_ARGB32_Premultiplied);
    mImage->fill(Qt::white);
    QImage o=*mImage;
    QImage* a=new QImage();
    *a=o;
    sketch[0]=a; 
    mPainter=new QPainter(mImage);
    mEnabled=false; 
    mColor=Qt::black; 
    mSize=5;
    currentTool= linetool;//the initial type of the shape 
    hide_inputDialog();// function to hide all text boxes and labels and others
    rightClick=false;
}

MainWindow::~MainWindow()
{
    delete ui;
     delete mPainter;
delete mImage;
    delete oldImage;
}

void MainWindow::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    QRect space=e->rect();
    painter.drawImage(space,*mImage,space);
 update();
}

void MainWindow::mousePressEvent(QMouseEvent *e) //what happens when you press the mouse click
{
   hide_inputDialog(); 
    if(e->button()==Qt::LeftButton)
    {
        hide_inputDialog();
        rightClick=false; // disable the right click to make no exceptions or bugs  
    mEnabled=true;  //enable the mouse
    mBegin=e->pos();
    mEnd = e->pos();

    }
    else
    {
        rightClick=true;
        return;
    }
}

void MainWindow::hide_inputDialog() // function to hide all text boxes and labels and all others
{
    ui->statusbar->setVisible(false);            // hide the status bar
    ui->length->setVisible(false);              // hide the length text box 
    ui->height->setVisible(false);             // hide the height text box
    ui->ok->setVisible(false);                // hide the ok button
    ui->width_length_raduisLabel->setVisible(false); //hide the label of the width,length and raduis for different shapes
    ui->heightLabel->setVisible(false);     // hide the height label
}

void MainWindow::mouseMoveEvent(QMouseEvent *e) // this function for what happens when the mouse move from position to another 
{

    if(!mEnabled)
    {
        e->accept();
        return ;
    }
    if(rightClick)      // when we make right click by mouse don't do anything 
        return;
    if(mImage->isNull())    
        return;
    mEnd=e->pos();         // the end point when we try to draw using the mouse 
    QPen pen;               // declaration of the pen that we will draw with 
   pen.setWidth(mSize);     //  thickness of the pen
    pen.setColor(mColor);   // color of the pen 
    mPainter->setPen(pen);  //set the pen to use it 
    update();

}

QString MainWindow::getShapeName() // to enter the name of the shape when you draw it 
{
    bool ok;
            QString text = QInputDialog::getText(this, tr("Get Shape Name"),
                                                 tr("Enter Shape Name:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
            while (!ok && text.isEmpty())
            {
                text = QInputDialog::getText(this, tr("Get Shape Name"),
                                                                 tr("Please Enter the Name:"), QLineEdit::Normal,
                                                                 QDir::home().dirName(), &ok);
            }
            while(!isValidName(text))
            {
                text = QInputDialog::getText(this, tr("Get Shape Name"),
                                                                 tr("Please Enter another Name:"), QLineEdit::Normal,
                                                                 QDir::home().dirName(), &ok);
            }
            return text;
}

bool MainWindow::isValidName(QString name) //check if the name is valid and not used before
{
    for(int i=0;i<shapes.size();i++)
    {
        if(name==shapes[i]->getName())
        {
          return false;
        }
    }
    return true;
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e)// what happens when you release the click of the mouse and start to draw 
{
    if(rightClick)
    {
        rightClick=false;
        return;
    }
    if (mBegin == mEnd)
        return;

    if(currentTool==linetool) // check the type of the shape is line
    {
        undotimes=0;
        QImage m=*mImage;
        QImage* s=new QImage();
        *s=m;
        currimage++;
        sketch[currimage]=s;
        line=QLine(mBegin,mEnd);
        mPainter->drawLine(line);

        Shape *shape=new StraightLine(getShapeName(),line.p1(),line.p2(),mSize,mColor);
        shapes.push_back(shape);
    }
    else if(currentTool==rectangletool)   // check the type of the shape is rectangle
    {

        undotimes=0;
        QImage m=*mImage;
        QImage* s=new QImage();
        *s=m;
        currimage++;
        sketch[currimage]=s;
  rect=directionOfDraw(mEnd);
  mPainter->drawRect(rect);
  Shape *shape=new Rectangle(getShapeName(),mBegin,mEnd,mSize,mColor);
  shapes.push_back(shape);

    }
    else{       // if not line or rectangle then it is circle 

        draw_circle(mBegin,mEnd);
     }


    mEnabled=false;
    e->accept();
    update();
}



void MainWindow::mouseDoubleClickEvent( QMouseEvent * e ) // what happens when you duble click the mouse
{
    hide_inputDialog();

    if ( e->button() == Qt::LeftButton )
    {
        mBegin=e->pos();
       on_actionManual_input_triggered();
    }
    else if(e->button()==Qt::RightButton)
    {
        rightClick=true;
        return;
    }
    e->accept();
    update();
}



void MainWindow::on_actionQuit_triggered() // when you click quit icon
{
    close();
}


QRect MainWindow::directionOfDraw(const QPoint &endPoint) // select the direction of painting to the right or to the left
{
    QRect rect;
    if(endPoint.x() < mBegin.x())
    {
        rect = QRect(endPoint, mBegin);
   QPoint p;
   p=mBegin;
   mBegin=endPoint;
   mEnd=p;
    }
    else
        rect = QRect(mBegin, endPoint);
    return rect;
}

void MainWindow::drawRectangle(QPoint begin, QPoint end) //function of drawing rectangle
{
       rect = QRect(begin, end);
    undotimes=0;
    QImage m=*mImage;
    QImage* s=new QImage();
    *s=m;
    currimage++;
    sketch[currimage]=s;
    mPainter->drawRect(rect);
    Shape *shape=new Rectangle(getShapeName(),begin,end,mSize,mColor);
     shapes.push_back(shape);
}




void MainWindow::draw_circle(const QPoint startPoint,const QPoint endPoint) // this function to draw a circle with start point and its end point as it claculate the raduis and other informations
{ 
    int d=(startPoint.x()-endPoint.x())*(startPoint.x()-endPoint.x())+(startPoint.y()-endPoint.y())*(startPoint.y()-endPoint.y());
       d=sqrt(d);
       double x,y;
       x=(startPoint.x()+endPoint.x())/2;
       y=(startPoint.y()+endPoint.y())/2;
       QPoint p;
       p.setX(x);
       p.setY(y);
       undotimes=0;
       QImage m=*mImage;
       QImage* s=new QImage();
       *s=m;
       currimage++;
       sketch[currimage]=s;
    mPainter->drawEllipse(p,d/2,d/2);
    Shape *shape=new Circle(getShapeName(),startPoint,endPoint,mSize,mColor);
       shapes.push_back(shape);
}

QLine MainWindow::directionOfDrawLine(const QPoint &endPoint) // select the direction of the line from up to down or reverse 
{
    QLine Line_;
    if(endPoint.x() < mBegin.x())
    {
        Line_ = QLine(endPoint, mBegin);
        QPoint p;
        p=mBegin;
        mBegin=endPoint;
        mEnd=p;
    }
    else
        Line_ = QLine(mBegin, endPoint);
    return Line_;
}
void MainWindow::DrawLine(QPoint begin,QPoint end) // for drawing the line
{
    QLine line;
        line= QLine(begin, end);
        undotimes=0;
        QImage m=*mImage;
        QImage* s=new QImage();
        *s=m;
        currimage++;
        sketch[currimage]=s;
mPainter->drawLine(line);
Shape *shape=new StraightLine(getShapeName(),line.p1(),line.p2(),mSize,mColor);
       shapes.push_back(shape);
}



void MainWindow::on_actionLine_triggered() // what happens when we select the line icon
{
        currentTool=linetool;
       hide_inputDialog();
}


void MainWindow::on_actionRectangle_triggered() // what happens when we select rectangle icon   
{
    currentTool=rectangletool;
 hide_inputDialog();
}


void MainWindow::on_actionCircle_triggered() // what happens when we select the circle icon
{
    currentTool=circletool;
  hide_inputDialog();
}

void MainWindow::on_actionColor_triggered()  // for all the colors that we can select
{
    hide_inputDialog();
    mColor=QColorDialog::getColor(Qt::black,this,"Color");
}

void MainWindow::on_actionThickness_triggered() // thickness of the pen
{
    hide_inputDialog();
    mSize=QInputDialog::getInt(this,"Size","Enter the Size",5,1);
}

void MainWindow::on_actionNew_triggered() // when we select the new icon
{
    hide_inputDialog();
    oldImage=mImage;
    mImage =new QImage(QApplication::desktop()->size(),QImage::Format_ARGB32_Premultiplied);
    mImage->fill(Qt::white);
    mPainter=new QPainter(mImage);
}



void MainWindow::on_actionUndo_triggered() // undo function when we select its icon
{
    hide_inputDialog();
    if(currimage>0)
    {
        removedshapes.push(shapes.back());
        shapes.pop_back();
     delete mPainter;
        redoImgs[redoCounter++]=mImage;
     mImage=sketch[currimage];
     mPainter=new QPainter(mImage);
     mPainter->setPen(Qt::black);
     currimage--;
     undotimes++;

    }
}


void MainWindow::on_actionRedo_triggered() // redo function when we select its icon
{
    hide_inputDialog();
    if(undotimes>0)
    {
        shapes.push_back(removedshapes.top());
        removedshapes.pop();
        delete mPainter;
         currimage+=1;
        mImage=redoImgs[--redoCounter];
        mPainter=new QPainter(mImage);
        mPainter->setPen(Qt::black);
        undotimes--;
    }
}



void MainWindow::on_ok_clicked() // when we click ok while entering the data manually 
{   bool isNumber;
    QPen pen;
   pen.setWidth(mSize);
    pen.setColor(mColor);
    mPainter->setPen(pen);
    hide_inputDialog();


    if(currentTool==linetool)
    { double angle;
      double length=ui->length->text().toDouble(&isNumber);
      if(isNumber)
        angle=ui->height->text().toDouble(&isNumber)/180.0*3.14*-1;
      if(!isNumber)
        QMessageBox::warning(this,"invalid data","please enter a valid input");
        else
     { QPoint p2;
      p2.setX(mBegin.x()+length*cos(angle));
      p2.setY(mBegin.y()+length*sin(angle));
      DrawLine(mBegin,p2);}
    }
    else if(currentTool==rectangletool)
    {
     double h,w;
     w=ui->length->text().toDouble(&isNumber);
     if(isNumber)
     h=ui->height->text().toDouble(&isNumber);
     if(!isNumber)
      QMessageBox::critical(this,"invalid data","please enter a valid input");
     else{
     QPoint p2;
     p2.setX(mBegin.x()+w);
     p2.setY(mBegin.y()+h);
     drawRectangle(mBegin,p2);
        }
            }
    else{

   double r;
    r=ui->length->text().toDouble(&isNumber);
    if(!isNumber)
    QMessageBox::critical(this,"invalid data","please enter a valid input");
    else{
    QPoint p2;
    p2.setX(mBegin.x()+r);
    p2.setY(mBegin.y());
    mBegin.setX(mBegin.x()-r);
    draw_circle(mBegin,p2);
}
}

}


void MainWindow::on_actionManual_input_triggered() // when we press double left click to enter the data manually 
{
     ui->length->setVisible(true);
     ui->ok->setVisible(true);
     ui->width_length_raduisLabel->setVisible(true);

    if(currentTool==rectangletool)
    {
    ui->width_length_raduisLabel->setText("Enter width");
    ui->heightLabel->setVisible(true);  
    ui->height->setVisible(true);
    ui->heightLabel->setText("Enter the Height");
    }
    if(currentTool==circletool)
    ui->width_length_raduisLabel->setText("Enter Raduis");

    else if(currentTool==linetool)
    {
     ui->width_length_raduisLabel->setText("Enter Length");
     ui->heightLabel->setVisible(true);
     ui->heightLabel->setText("angle in Degree");
     ui->height->setVisible(true);
        }


}


void MainWindow::on_actionSearch_triggered() // when we select the search icon
{
    hide_inputDialog();
    bool ok;
            QString text = QInputDialog::getText(this, tr("Search"),
                                                 tr("Enter Shape Name:"), QLineEdit::Normal,
                                                 QDir::home().dirName(), &ok);
            if (ok && !text.isEmpty())
                       {
                           for(int i=0;i<shapes.size();i++)
                           {
                            if(shapes[i]->getName()==text)
                            {
                                if(shapes[i]->getType()==linetool)
                                  {
                                    QMessageBox::information(this,"Shape data","Name: "+shapes[i]->getName()+"\nPerimeter: "+QString::number(shapes[i]->perimeter())+"\nType: Line");
                                    return;
                                  }
                                if(shapes[i]->getType()==circletool)
                                  {
                                    QMessageBox::information(this,"Shape data","Name: "+shapes[i]->getName()+"\nPerimeter: "+QString::number(shapes[i]->perimeter())+"\nType: Circle ");
                                    return;
                                  }
                                if(shapes[i]->getType()==rectangletool)
                                  {

                                    QMessageBox::information(this,"Shape data","Name: "+shapes[i]->getName()+"\nPerimeter: "+QString::number(shapes[i]->perimeter())+"\nType: Rectangle");
                                    return;
                                  }
                            }
                       }
                QMessageBox::information(this,"Shape data","Shape not found!");

            }
}


void MainWindow::on_actionSort_triggered()      // when we select the sort icon
{
    ui->statusbar->setVisible(true);
    bool isSorted=false;
    QVector<Shape*>sorted;
    for(int i=0;i<shapes.size();i++)
    {
        sorted.push_back(shapes[i]);
    }
    for(int i=0;i<sorted.size();i++)
    {

        for(int j=0;j<sorted.size()-1-i;j++)
        {
            Shape*t;
            if(sorted[j]->perimeter()>sorted[j+1]->perimeter())
            {
                t=sorted[j];
                sorted[j]=sorted[j+1];
                sorted[j+1]=t;
                isSorted=true;
            }
        }
        if(!isSorted)
            break;
    }
    QString name;
       for(int i=0;i<sorted.size();i++)
       {
           name+=sorted[i]->getName();
           name+=" ";
       }
       ui->statusbar->showMessage(name);
}

