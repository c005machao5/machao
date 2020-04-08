#include "chargewidget.h"
#include "ui_chargewidget.h"
#include <QIntValidator>
#include <QMessageBox>

#include "socket/socketmanager.h"
#include "protocol/protocol.h"
#include "widgetmanager.h"

ChargeWidget::ChargeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChargeWidget)
{
    ui->setupUi(this);
    QIntValidator *validator = new QIntValidator(0,1000,this);
    ui->leChargeNum->setValidator(validator);
}

ChargeWidget::~ChargeWidget()
{
    delete ui;
}

void ChargeWidget::on_btnEnsure_clicked()
{
    //1.获取充值金额
    int chargenum = ui->leChargeNum->text().toInt();
    QString chargenumber = ui->leChargeNum->text();
    ui->leChargeNum->clear();

    if( chargenumber.isEmpty() || chargenum == 0){
        QMessageBox::warning(this,"充值信息","输入的金额不正确");
        return ;
    }

    Protocol p;
    p.setType(Protocol::charge);
    p["type"] = "charge";
    p["username"] = this->windowTitle();
    p["chargenum"] = chargenum;

    SocketManager::getInstance()->write(p.pack());
}

void ChargeWidget::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
    WidgetManager::getInstance()->getHallWidget()->show();
}

void ChargeWidget::on_btnCancel_clicked()
{
    ui->leChargeNum->clear();
    this->hide();
    WidgetManager::getInstance()->getHallWidget()->show();
}
