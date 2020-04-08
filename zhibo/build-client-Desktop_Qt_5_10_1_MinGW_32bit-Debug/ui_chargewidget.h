/********************************************************************************
** Form generated from reading UI file 'chargewidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CHARGEWIDGET_H
#define UI_CHARGEWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ChargeWidget
{
public:
    QLabel *label_2;
    QPushButton *btnEnsure;
    QLabel *label;
    QPushButton *btnCancel;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *lbChargeNum;
    QLineEdit *leChargeNum;

    void setupUi(QWidget *ChargeWidget)
    {
        if (ChargeWidget->objectName().isEmpty())
            ChargeWidget->setObjectName(QStringLiteral("ChargeWidget"));
        ChargeWidget->resize(400, 300);
        label_2 = new QLabel(ChargeWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(100, 110, 150, 21));
        label_2->setStyleSheet(QStringLiteral("font: italic 8pt \"Arial\";"));
        btnEnsure = new QPushButton(ChargeWidget);
        btnEnsure->setObjectName(QStringLiteral("btnEnsure"));
        btnEnsure->setGeometry(QRect(40, 160, 75, 23));
        label = new QLabel(ChargeWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(100, 130, 108, 16));
        label->setStyleSheet(QStringLiteral("font: italic 8pt \"Arial\";"));
        btnCancel = new QPushButton(ChargeWidget);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setGeometry(QRect(180, 160, 75, 23));
        widget = new QWidget(ChargeWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(42, 81, 189, 22));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        lbChargeNum = new QLabel(widget);
        lbChargeNum->setObjectName(QStringLiteral("lbChargeNum"));

        horizontalLayout->addWidget(lbChargeNum);

        leChargeNum = new QLineEdit(widget);
        leChargeNum->setObjectName(QStringLiteral("leChargeNum"));

        horizontalLayout->addWidget(leChargeNum);


        retranslateUi(ChargeWidget);

        QMetaObject::connectSlotsByName(ChargeWidget);
    } // setupUi

    void retranslateUi(QWidget *ChargeWidget)
    {
        ChargeWidget->setWindowTitle(QApplication::translate("ChargeWidget", "Form", nullptr));
        label_2->setText(QApplication::translate("ChargeWidget", "\345\205\205\345\200\274\351\207\221\351\242\235\344\270\272\345\244\247\344\272\2160\347\232\204\346\225\264\346\225\260\351\207\221\351\242\235", nullptr));
        btnEnsure->setText(QApplication::translate("ChargeWidget", "\347\241\256\345\256\232", nullptr));
        label->setText(QApplication::translate("ChargeWidget", "\346\257\217\346\254\241\346\234\200\351\253\230\345\205\205\345\200\2741000\345\205\203", nullptr));
        btnCancel->setText(QApplication::translate("ChargeWidget", "\345\217\226\346\266\210", nullptr));
        lbChargeNum->setText(QApplication::translate("ChargeWidget", "\345\205\205\345\200\274\351\207\221\351\242\235", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ChargeWidget: public Ui_ChargeWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CHARGEWIDGET_H
