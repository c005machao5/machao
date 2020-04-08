/********************************************************************************
** Form generated from reading UI file 'giftwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GIFTWIDGET_H
#define UI_GIFTWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GiftWidget
{
public:
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnHeart;
    QPushButton *btnCar;
    QPushButton *btnRocket;
    QPushButton *btnDunker;

    void setupUi(QWidget *GiftWidget)
    {
        if (GiftWidget->objectName().isEmpty())
            GiftWidget->setObjectName(QStringLiteral("GiftWidget"));
        GiftWidget->resize(400, 300);
        label = new QLabel(GiftWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(130, 30, 91, 20));
        label_2 = new QLabel(GiftWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(90, 90, 211, 20));
        btnHeart = new QPushButton(GiftWidget);
        btnHeart->setObjectName(QStringLiteral("btnHeart"));
        btnHeart->setGeometry(QRect(10, 170, 75, 23));
        btnCar = new QPushButton(GiftWidget);
        btnCar->setObjectName(QStringLiteral("btnCar"));
        btnCar->setGeometry(QRect(110, 170, 75, 23));
        btnRocket = new QPushButton(GiftWidget);
        btnRocket->setObjectName(QStringLiteral("btnRocket"));
        btnRocket->setGeometry(QRect(210, 170, 75, 23));
        btnDunker = new QPushButton(GiftWidget);
        btnDunker->setObjectName(QStringLiteral("btnDunker"));
        btnDunker->setGeometry(QRect(300, 170, 75, 23));

        retranslateUi(GiftWidget);

        QMetaObject::connectSlotsByName(GiftWidget);
    } // setupUi

    void retranslateUi(QWidget *GiftWidget)
    {
        GiftWidget->setWindowTitle(QApplication::translate("GiftWidget", "Form", nullptr));
        label->setText(QApplication::translate("GiftWidget", "  \347\244\274 \347\211\251 \345\210\227 \350\241\250", nullptr));
        label_2->setText(QApplication::translate("GiftWidget", "\346\257\217\346\254\241\351\200\201\347\244\274\345\260\206\344\273\216\344\275\231\351\242\235\344\270\255\346\211\243\351\231\244\347\233\270\345\272\224\347\232\204\351\207\221\351\242\235", nullptr));
        btnHeart->setText(QApplication::translate("GiftWidget", "\347\272\242\345\277\20310\345\205\203", nullptr));
        btnCar->setText(QApplication::translate("GiftWidget", "\350\267\221\350\275\24650\345\205\203", nullptr));
        btnRocket->setText(QApplication::translate("GiftWidget", "\347\201\253\347\256\255100\345\205\203", nullptr));
        btnDunker->setText(QApplication::translate("GiftWidget", "\346\275\234\350\211\207200\345\205\203", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GiftWidget: public Ui_GiftWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GIFTWIDGET_H
