#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QColorDialog>
#include "ui_dialog.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    dlg.setupUi(&dNew);

    setValues();
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    // Antialiasing
    p.setRenderHints(QPainter::Antialiasing,true);

    p.drawImage((width()/2)-(image.width()/2),
                (height()/2)-(image.height()/2),
                image);
    imgX = (width()/2)-(image.width()/2);
    imgY = (height()/2)-(image.height()/2);
    if(locked==false)
    {
        int margin = 3;

        drawReRect(imgX,imgY,image.width(),image.height(),p);

        p.setBrush(penColor);
        pen.setStyle(Qt::SolidLine);
        p.setPen(pen);
        p.drawRoundRect(ui->pushButton_pen->x()-margin,
                        ui->pushButton_pen->y()-margin,
                        ui->pushButton_pen->width()+margin*2,
                        ui->pushButton_pen->height()+margin*2,
                        25,25);

        p.setBrush(brushColor);
        p.drawRoundRect(ui->pushButton_brush->x()-margin,
                        ui->pushButton_pen->y()-margin,
                        ui->pushButton_brush->width()+margin*2,
                        ui->pushButton_brush->height()+margin*2,25,25);
        setStyle();

        if(clicked)
        {
            pen.setColor(penColor);
            setStyle();
            pen.setWidth(bold);
            p.setPen(pen);
            p.setBrush(brushColor);


            if(ui->comboBox_drawMode->currentIndex() == shapeRectangle)
            {
                p.drawRect(startX+imgX,
                           startY+imgY,
                           moveX-startX-imgX,
                           moveY-startY-imgY);
            }

            if(ui->comboBox_drawMode->currentIndex() == shapeCircle)
            {
                pen.setStyle(Qt::DashLine);
                pen.setWidth(1);
                p.setPen(pen);
                p.setBrush(QColor(255,255,255));
                p.drawRect((startX-bold/2)+imgX,
                           (startY-bold/2)+imgY,
                           moveX-startX+bold-imgX,
                           moveY-startY+bold-imgY);
                p.setBrush(brushColor);
                pen.setStyle(Qt::SolidLine);
                pen.setWidth(bold);
                p.setPen(pen);
                p.drawEllipse(startX+imgX,
                              startY+imgY,
                              moveX-startX-imgX,
                              moveY-startY-imgY);
            }

            if(ui->comboBox_drawMode->currentIndex() == shapeLine)
            {
                p.drawLine(startX+imgX,
                           startY+imgY,
                           moveX,
                           moveY);
            }
            oldPen = p.pen();
            pen.setStyle(Qt::SolidLine);
            p.setPen(pen);
        }
    }
    else
    {
        p.setBrush(QColor(100,100,100));
        pen.setColor(QColor(255,255,255));
        p.drawRect(-1,-1,width()+1,height()+1);
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    clicked = true;

    startX = event->x()-imgX;
    startY = event->y()-imgY;
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    moveX = event->x();
    moveY = event->y();

    update();
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    clicked = false;
    endX = event->x()-imgX;
    endY = event->y()-imgY;

    if(locked == false )
    {
        QPainter p(&image);

        pen.setColor(penColor);
        pen.setWidth(bold);
        p.setPen(oldPen);
        p.setBrush(brushColor);
        p.setRenderHints(QPainter::Antialiasing,true);


        if(ui->comboBox_drawMode->currentIndex() == shapeRectangle)
        {
            p.drawRect(startX,startY,endX-startX,endY-startY);
        }

        if(ui->comboBox_drawMode->currentIndex() == shapeCircle)
        {
            p.drawEllipse(startX,startY,endX-startX,endY-startY);
        }

        if(ui->comboBox_drawMode->currentIndex() == shapeLine)
        {
            p.drawLine(startX,startY,endX,endY);
        }
        p.setPen(pen);

        update();
    }
}

void Widget::setValues()
{
    locked = true;
    clicked = false;
    size = dSize;
    newWidth = 0;
    newHeight = 0;
    ui->spinBox_bold->setValue(dBold);
    drawMode = dDrawMode;
    bold = dBold;
    penColor = QColor(0,0,0);
    brushColor = QColor(255,255,255);

    dSaveName = "unnamed.jpg";
}

void Widget::unlock()
{
    ui->pushButton_brush->setEnabled(true);
    ui->pushButton_new->setEnabled(true);
    ui->pushButton_open->setEnabled(true);
    ui->pushButton_pen->setEnabled(true);
    ui->pushButton_save->setEnabled(true);
    ui->comboBox_style->setEnabled(true);
    ui->comboBox_drawMode->setEnabled(true);
    ui->spinBox_bold->setEnabled(true);
}

void Widget::drawReRect(int x, int y, int w, int h, QPainter &p)
{
    pen.setWidth(0);
    pen.setColor(QColor(100,100,100));
    p.setPen(pen);
    p.setBrush(QColor(100,100,100));

    p.drawRect(-1,-1,x+1,height()+1);
    p.drawRect(-1,-1,width()+1,y+1);

    p.drawRect(x+w,y,width(),height());
    p.drawRect(x,y+h,width(),height());
}

void Widget::setStyle()
{
    if(ui->comboBox_style->currentIndex() == styleSolid)
    {
        pen.setStyle(Qt::SolidLine);
    }

    if(ui->comboBox_style->currentIndex() == styleDot)
    {
        pen.setStyle(Qt::DotLine);
    }

    if(ui->comboBox_style->currentIndex() == styleDash)
    {
        pen.setStyle(Qt::DashLine);
    }

    if(ui->comboBox_style->currentIndex() == styleDashDot)
    {
        pen.setStyle(Qt::DashDotLine);
    }

    if(ui->comboBox_style->currentIndex() == styleDashDotDot)
    {
        pen.setStyle(Qt::DashDotDotLine);
    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_spinBox_bold_valueChanged(int value)
{
    bold = value;
}
