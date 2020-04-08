/********************************************************************************
** Form generated from reading UI file 'loginwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWIDGET_H
#define UI_LOGINWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWidget
{
public:
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *lbUsername;
    QLineEdit *leUsername;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lbUserpwd;
    QLineEdit *leUserpwd;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *btnRegister;
    QPushButton *btnLogin;

    void setupUi(QWidget *LoginWidget)
    {
        if (LoginWidget->objectName().isEmpty())
            LoginWidget->setObjectName(QStringLiteral("LoginWidget"));
        LoginWidget->resize(292, 238);
        widget = new QWidget(LoginWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(40, 20, 191, 151));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lbUsername = new QLabel(widget);
        lbUsername->setObjectName(QStringLiteral("lbUsername"));

        horizontalLayout->addWidget(lbUsername);

        leUsername = new QLineEdit(widget);
        leUsername->setObjectName(QStringLiteral("leUsername"));

        horizontalLayout->addWidget(leUsername);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        lbUserpwd = new QLabel(widget);
        lbUserpwd->setObjectName(QStringLiteral("lbUserpwd"));

        horizontalLayout_2->addWidget(lbUserpwd);

        leUserpwd = new QLineEdit(widget);
        leUserpwd->setObjectName(QStringLiteral("leUserpwd"));

        horizontalLayout_2->addWidget(leUserpwd);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        btnRegister = new QPushButton(widget);
        btnRegister->setObjectName(QStringLiteral("btnRegister"));

        horizontalLayout_3->addWidget(btnRegister);

        btnLogin = new QPushButton(widget);
        btnLogin->setObjectName(QStringLiteral("btnLogin"));

        horizontalLayout_3->addWidget(btnLogin);


        verticalLayout->addLayout(horizontalLayout_3);


        retranslateUi(LoginWidget);

        QMetaObject::connectSlotsByName(LoginWidget);
    } // setupUi

    void retranslateUi(QWidget *LoginWidget)
    {
        LoginWidget->setWindowTitle(QApplication::translate("LoginWidget", "Form", nullptr));
        lbUsername->setText(QApplication::translate("LoginWidget", "\347\224\250\346\210\267\345\220\215", nullptr));
        lbUserpwd->setText(QApplication::translate("LoginWidget", "\345\257\206  \347\240\201", nullptr));
        btnRegister->setText(QApplication::translate("LoginWidget", "\346\263\250\345\206\214", nullptr));
        btnLogin->setText(QApplication::translate("LoginWidget", "\347\231\273\345\275\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWidget: public Ui_LoginWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWIDGET_H
