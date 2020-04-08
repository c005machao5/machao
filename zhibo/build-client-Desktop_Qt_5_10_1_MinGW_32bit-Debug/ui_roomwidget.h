/********************************************************************************
** Form generated from reading UI file 'roomwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROOMWIDGET_H
#define UI_ROOMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RoomWidget
{
public:
    QListWidget *lwUser;
    QLabel *lbVideo;
    QLabel *lbScroll;
    QLabel *label;
    QTextEdit *teShow;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *leIput;
    QPushButton *btnSend;
    QPushButton *pushButton;
    QCheckBox *cbCamera;
    QCheckBox *checkBox;

    void setupUi(QWidget *RoomWidget)
    {
        if (RoomWidget->objectName().isEmpty())
            RoomWidget->setObjectName(QStringLiteral("RoomWidget"));
        RoomWidget->resize(587, 405);
        lwUser = new QListWidget(RoomWidget);
        lwUser->setObjectName(QStringLiteral("lwUser"));
        lwUser->setGeometry(QRect(420, 40, 121, 191));
        lwUser->setMaximumSize(QSize(121, 16777215));
        lbVideo = new QLabel(RoomWidget);
        lbVideo->setObjectName(QStringLiteral("lbVideo"));
        lbVideo->setGeometry(QRect(20, 30, 381, 201));
        lbVideo->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 127);"));
        lbScroll = new QLabel(RoomWidget);
        lbScroll->setObjectName(QStringLiteral("lbScroll"));
        lbScroll->setGeometry(QRect(20, 30, 381, 81));
        lbScroll->setStyleSheet(QStringLiteral("background-color: rgb(85, 255, 127);"));
        label = new QLabel(RoomWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(450, 20, 71, 20));
        label->setStyleSheet(QLatin1String("background-color: rgb(255, 170, 255);\n"
"font: 12pt \"04b_21\";"));
        teShow = new QTextEdit(RoomWidget);
        teShow->setObjectName(QStringLiteral("teShow"));
        teShow->setGeometry(QRect(19, 241, 519, 101));
        teShow->setMaximumSize(QSize(16777215, 101));
        layoutWidget = new QWidget(RoomWidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 350, 521, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        leIput = new QLineEdit(layoutWidget);
        leIput->setObjectName(QStringLiteral("leIput"));

        horizontalLayout->addWidget(leIput);

        btnSend = new QPushButton(layoutWidget);
        btnSend->setObjectName(QStringLiteral("btnSend"));
        btnSend->setMinimumSize(QSize(75, 23));
        btnSend->setMaximumSize(QSize(75, 23));

        horizontalLayout->addWidget(btnSend);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(75, 23));
        pushButton->setMaximumSize(QSize(75, 23));

        horizontalLayout->addWidget(pushButton);

        cbCamera = new QCheckBox(RoomWidget);
        cbCamera->setObjectName(QStringLiteral("cbCamera"));
        cbCamera->setGeometry(QRect(80, 10, 71, 16));
        checkBox = new QCheckBox(RoomWidget);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(220, 10, 71, 16));
        checkBox->setChecked(true);

        retranslateUi(RoomWidget);

        QMetaObject::connectSlotsByName(RoomWidget);
    } // setupUi

    void retranslateUi(QWidget *RoomWidget)
    {
        RoomWidget->setWindowTitle(QApplication::translate("RoomWidget", "Form", nullptr));
        lbVideo->setText(QString());
        lbScroll->setText(QString());
        label->setText(QApplication::translate("RoomWidget", "\347\224\250\346\210\267\345\210\227\350\241\250", nullptr));
        btnSend->setText(QApplication::translate("RoomWidget", "\345\217\221\351\200\201", nullptr));
        pushButton->setText(QApplication::translate("RoomWidget", "\351\200\201\347\244\274\347\211\251", nullptr));
        cbCamera->setText(QApplication::translate("RoomWidget", "\346\221\204\345\203\217\345\244\264", nullptr));
        checkBox->setText(QApplication::translate("RoomWidget", "\345\274\271\345\271\225\345\274\200\345\205\263", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RoomWidget: public Ui_RoomWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROOMWIDGET_H
