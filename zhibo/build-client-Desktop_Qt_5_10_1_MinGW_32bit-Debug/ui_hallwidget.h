/********************************************************************************
** Form generated from reading UI file 'hallwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HALLWIDGET_H
#define UI_HALLWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HallWidget
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QListWidget *lwRoom;
    QPushButton *btnCreate;
    QPushButton *btnCharge;

    void setupUi(QWidget *HallWidget)
    {
        if (HallWidget->objectName().isEmpty())
            HallWidget->setObjectName(QStringLiteral("HallWidget"));
        HallWidget->resize(400, 300);
        widget = new QWidget(HallWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(31, 21, 258, 252));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        lwRoom = new QListWidget(widget);
        lwRoom->setObjectName(QStringLiteral("lwRoom"));

        verticalLayout->addWidget(lwRoom);

        btnCreate = new QPushButton(widget);
        btnCreate->setObjectName(QStringLiteral("btnCreate"));

        verticalLayout->addWidget(btnCreate);

        btnCharge = new QPushButton(widget);
        btnCharge->setObjectName(QStringLiteral("btnCharge"));

        verticalLayout->addWidget(btnCharge);


        retranslateUi(HallWidget);

        QMetaObject::connectSlotsByName(HallWidget);
    } // setupUi

    void retranslateUi(QWidget *HallWidget)
    {
        HallWidget->setWindowTitle(QApplication::translate("HallWidget", "Form", nullptr));
        btnCreate->setText(QApplication::translate("HallWidget", "\345\210\233\345\273\272\346\210\277\351\227\264", nullptr));
        btnCharge->setText(QApplication::translate("HallWidget", "\345\205\205    \345\200\274", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HallWidget: public Ui_HallWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HALLWIDGET_H
