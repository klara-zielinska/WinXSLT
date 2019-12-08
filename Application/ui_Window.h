/********************************************************************************
** Form generated from reading UI file 'Window.ui'
**
** Created by: Qt User Interface Compiler version 5.12.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_H
#define UI_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Window
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QTextEdit *xsltBox;
    QHBoxLayout *horizontalLayout;
    QPushButton *xsltLoadButton;
    QPushButton *xsltSaveButton;
    QWidget *widget;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_2;
    QLineEdit *targetPathBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *targetFileButton;
    QPushButton *targetFolderButton;
    QPushButton *transformButton;
    QLabel *label_3;
    QListWidget *logsBox;

    void setupUi(QMainWindow *Window)
    {
        if (Window->objectName().isEmpty())
            Window->setObjectName(QString::fromUtf8("Window"));
        Window->resize(780, 298);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/resources/icon.ico"), QSize(), QIcon::Normal, QIcon::Off);
        Window->setWindowIcon(icon);
        Window->setLocale(QLocale(QLocale::English, QLocale::UnitedStates));
        centralWidget = new QWidget(Window);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        horizontalLayout_3 = new QHBoxLayout(centralWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label);

        xsltBox = new QTextEdit(centralWidget);
        xsltBox->setObjectName(QString::fromUtf8("xsltBox"));
        QFont font;
        font.setFamily(QString::fromUtf8("Courier New"));
        font.setPointSize(10);
        xsltBox->setFont(font);

        verticalLayout->addWidget(xsltBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        xsltLoadButton = new QPushButton(centralWidget);
        xsltLoadButton->setObjectName(QString::fromUtf8("xsltLoadButton"));

        horizontalLayout->addWidget(xsltLoadButton);

        xsltSaveButton = new QPushButton(centralWidget);
        xsltSaveButton->setObjectName(QString::fromUtf8("xsltSaveButton"));

        horizontalLayout->addWidget(xsltSaveButton);


        verticalLayout->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(verticalLayout);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(350, 0));
        widget->setMaximumSize(QSize(350, 16777215));
        widget->setBaseSize(QSize(0, 0));
        verticalLayout_3 = new QVBoxLayout(widget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        targetPathBox = new QLineEdit(widget);
        targetPathBox->setObjectName(QString::fromUtf8("targetPathBox"));
        targetPathBox->setFont(font);

        verticalLayout_3->addWidget(targetPathBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        targetFileButton = new QPushButton(widget);
        targetFileButton->setObjectName(QString::fromUtf8("targetFileButton"));

        horizontalLayout_2->addWidget(targetFileButton);

        targetFolderButton = new QPushButton(widget);
        targetFolderButton->setObjectName(QString::fromUtf8("targetFolderButton"));

        horizontalLayout_2->addWidget(targetFolderButton);


        verticalLayout_3->addLayout(horizontalLayout_2);

        transformButton = new QPushButton(widget);
        transformButton->setObjectName(QString::fromUtf8("transformButton"));

        verticalLayout_3->addWidget(transformButton);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        verticalLayout_3->addWidget(label_3);

        logsBox = new QListWidget(widget);
        logsBox->setObjectName(QString::fromUtf8("logsBox"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Shell Dlg 2"));
        font1.setPointSize(8);
        logsBox->setFont(font1);

        verticalLayout_3->addWidget(logsBox);


        horizontalLayout_3->addWidget(widget);

        Window->setCentralWidget(centralWidget);

        retranslateUi(Window);

        QMetaObject::connectSlotsByName(Window);
    } // setupUi

    void retranslateUi(QMainWindow *Window)
    {
        Window->setWindowTitle(QApplication::translate("Window", "WinXSLT", nullptr));
        label->setText(QApplication::translate("Window", "XSLT code", nullptr));
        xsltLoadButton->setText(QApplication::translate("Window", "Load", nullptr));
        xsltSaveButton->setText(QApplication::translate("Window", "Save", nullptr));
        label_2->setText(QApplication::translate("Window", "Files to trasform", nullptr));
        targetFileButton->setText(QApplication::translate("Window", "Choose file", nullptr));
        targetFolderButton->setText(QApplication::translate("Window", "Choose folder", nullptr));
        transformButton->setText(QApplication::translate("Window", "Transform", nullptr));
        label_3->setText(QApplication::translate("Window", "Logs", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Window: public Ui_Window {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_H
