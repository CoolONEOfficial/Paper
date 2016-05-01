#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QMouseEvent>
#include <QFileDialog>
#include <QColorDialog>
#include "ui_dialog.h"

void Widget::on_pushButton_save_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"),
                                                    openName,
                                                    tr("All files (*.*)"));

    image.save(fileName);
    openName = dSaveName;
}

void Widget::on_pushButton_open_clicked()
{
    openName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "",
                                                    tr("Images (*.jpg *.png *.bmp)"));
    image.load(openName);
    update();
}

void Widget::on_pushButton_pen_clicked()
{
    penColor = QColorDialog::getColor();
    update();
}

void Widget::on_pushButton_brush_clicked()
{
    brushColor = QColorDialog::getColor();
    update();
}

void Widget::on_spinBox_valueChanged(int arg1)
{
    bold = ui->spinBox_bold->value();
}

void Widget::on_verticalSlider_valueChanged(int value)
{
    size = value;
}

void Widget::on_pushButton_new_clicked()
{
    int res = dNew.exec();

    if( res == QDialog::Accepted )
    {
        locked = false;
        unlock();
        newHeight = dlg.spinBox_height->value();
        newWidth = dlg.spinBox_width->value();
        image = QImage(newWidth,newHeight,QImage::Format_RGB32);
        QPainter p(&image);
        p.setBrush(QColor(255,255,255));
        p.drawRect(-1,-1,newWidth+1,newHeight+1);
    }
}

void Widget::on_spinBox_width_valueChanged(int arg1)
{
    dlg.comboBox->setCurrentIndex(0);
}

void Widget::on_spinBox_height_valueChanged(int arg1)
{
    dlg.comboBox->setCurrentIndex(0);
}

void Widget::on_comboBox_currentIndexChanged(int index)
{
    if(index == 1)
    {
        dlg.spinBox_height->setValue(128);
        dlg.spinBox_width->setValue(128);
    }
}

void Widget::on_comboBox_style_currentIndexChanged(int index)
{
    setStyle();
}

