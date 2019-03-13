#include "DialogTest1.h"
#include "ui_DialogTest1.h"
////////////////////////////////////////////////////////////////////////////////
FEVV::DialogTest1::DialogTest1(QWidget *parent)
    : QDialog(parent), ui(new Ui::DialogTest1)
{
  ui->setupUi(this);
}
////////////////////////////////////////////////////////////////////////////////
FEVV::DialogTest1::~DialogTest1() { delete ui; }
////////////////////////////////////////////////////////////////////////////////
void
FEVV::DialogTest1::setProcess(double x, double y, double z)
{
  ui->lineEdit_X->setText(QString::number(x));
  ui->lineEdit_Y->setText(QString::number(y));
  ui->lineEdit_Z->setText(QString::number(z));
}
////////////////////////////////////////////////////////////////////////////////
void
FEVV::DialogTest1::getProcess(double &x, double &y, double &z)
{
  x = ui->lineEdit_X->text().toDouble();
  y = ui->lineEdit_Y->text().toDouble();
  z = ui->lineEdit_Z->text().toDouble();
}
////////////////////////////////////////////////////////////////////////////////
