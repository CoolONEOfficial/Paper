#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QImage>
#include <QColorDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include "ui_dialog.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void setValues();
    void unlock();
    void drawReRect(int x,int y,int w,int h,QPainter &p);
    void setStyle();
    ~Widget();

    static const int dSize = 10;
    static const int dDrawMode = 2; // 1 - Rect; 2 - Circle;
    static const int dBold = 10;
    QString dSaveName;

    // Shapes
    static const int shapeRectangle = 0;
    static const int shapeCircle = 1;
    static const int shapeLine = 2;

    // Styles
    static const int styleSolid = 0;
    static const int styleDot = 1;
    static const int styleDash = 2;
    static const int styleDashDot = 3;
    static const int styleDashDotDot = 4;

    QImage image;
    QColor brushColor,penColor;
    QPen oldPen;

    int size, drawMode, bold;
    int imgX,imgY;
    int startX, startY;
    int endX, endY;
    int moveX, moveY;
    int newHeight,newWidth;
    bool clicked;
    bool locked;
    QString openName;
    QDialog dNew;
    QPen pen;

    Ui::Dialog dlg;

private slots:
    void on_pushButton_save_clicked();

    void on_pushButton_pen_clicked();

    void on_pushButton_brush_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_verticalSlider_valueChanged(int value);

    void on_pushButton_open_clicked();


    void on_pushButton_new_clicked();

    void on_spinBox_width_valueChanged(int arg1);

    void on_spinBox_height_valueChanged(int arg1);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_style_currentIndexChanged(int index);

    void on_spinBox_bold_valueChanged(int arg1);

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
