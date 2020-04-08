#ifndef CHARGEWIDGET_H
#define CHARGEWIDGET_H

#include <QWidget>
#include <QCloseEvent>
namespace Ui {
class ChargeWidget;
}

class ChargeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ChargeWidget(QWidget *parent = 0);
    ~ChargeWidget();

private slots:
    void on_btnEnsure_clicked();

    void on_btnCancel_clicked();

private:
    Ui::ChargeWidget *ui;

protected:
    virtual void closeEvent(QCloseEvent * event);
};

#endif // CHARGEWIDGET_H
