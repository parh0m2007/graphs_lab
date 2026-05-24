/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *addVertexButton;
    QPushButton *removeVertexButton;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *addEdgeButton;
    QPushButton *removeEdgeButton;
    QPushButton *clearButton;
    QGroupBox *groupBox_2;
    QFormLayout *formLayout;
    QLabel *label;
    QSpinBox *startVertexSpinBox;
    QLabel *label_2;
    QSpinBox *endVertexSpinBox;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_3;
    QPushButton *bfsButton;
    QPushButton *dfsButton;
    QPushButton *dijkstraButton;
    QPushButton *floydButton;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_4;
    QTextEdit *resultText;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1200, 700);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setMinimumSize(QSize(600, 500));

        horizontalLayout->addWidget(graphicsView);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        addVertexButton = new QPushButton(groupBox);
        addVertexButton->setObjectName(QString::fromUtf8("addVertexButton"));

        horizontalLayout_2->addWidget(addVertexButton);

        removeVertexButton = new QPushButton(groupBox);
        removeVertexButton->setObjectName(QString::fromUtf8("removeVertexButton"));

        horizontalLayout_2->addWidget(removeVertexButton);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        addEdgeButton = new QPushButton(groupBox);
        addEdgeButton->setObjectName(QString::fromUtf8("addEdgeButton"));

        horizontalLayout_3->addWidget(addEdgeButton);

        removeEdgeButton = new QPushButton(groupBox);
        removeEdgeButton->setObjectName(QString::fromUtf8("removeEdgeButton"));

        horizontalLayout_3->addWidget(removeEdgeButton);


        verticalLayout->addLayout(horizontalLayout_3);

        clearButton = new QPushButton(groupBox);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));

        verticalLayout->addWidget(clearButton);


        verticalLayout_2->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        formLayout = new QFormLayout(groupBox_2);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        startVertexSpinBox = new QSpinBox(groupBox_2);
        startVertexSpinBox->setObjectName(QString::fromUtf8("startVertexSpinBox"));
        startVertexSpinBox->setMinimum(0);
        startVertexSpinBox->setMaximum(999);
        startVertexSpinBox->setValue(20);

        formLayout->setWidget(0, QFormLayout::FieldRole, startVertexSpinBox);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        endVertexSpinBox = new QSpinBox(groupBox_2);
        endVertexSpinBox->setObjectName(QString::fromUtf8("endVertexSpinBox"));
        endVertexSpinBox->setMinimum(0);
        endVertexSpinBox->setMaximum(999);
        endVertexSpinBox->setValue(1);

        formLayout->setWidget(1, QFormLayout::FieldRole, endVertexSpinBox);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        verticalLayout_3 = new QVBoxLayout(groupBox_3);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        bfsButton = new QPushButton(groupBox_3);
        bfsButton->setObjectName(QString::fromUtf8("bfsButton"));

        verticalLayout_3->addWidget(bfsButton);

        dfsButton = new QPushButton(groupBox_3);
        dfsButton->setObjectName(QString::fromUtf8("dfsButton"));

        verticalLayout_3->addWidget(dfsButton);

        dijkstraButton = new QPushButton(groupBox_3);
        dijkstraButton->setObjectName(QString::fromUtf8("dijkstraButton"));

        verticalLayout_3->addWidget(dijkstraButton);

        floydButton = new QPushButton(groupBox_3);
        floydButton->setObjectName(QString::fromUtf8("floydButton"));

        verticalLayout_3->addWidget(floydButton);


        verticalLayout_2->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        verticalLayout_4 = new QVBoxLayout(groupBox_4);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        resultText = new QTextEdit(groupBox_4);
        resultText->setObjectName(QString::fromUtf8("resultText"));
        resultText->setReadOnly(true);

        verticalLayout_4->addWidget(resultText);


        verticalLayout_2->addWidget(groupBox_4);


        horizontalLayout->addLayout(verticalLayout_2);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1200, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "\320\233\320\260\320\261\320\276\321\200\320\260\321\202\320\276\321\200\320\275\320\260\321\217 \321\200\320\260\320\261\320\276\321\202\320\260: \320\236\320\261\321\205\320\276\320\264 \320\263\321\200\320\260\321\204\320\276\320\262 (\320\222\320\260\321\200\320\270\320\260\320\275\321\202 20)", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\263\321\200\320\260\321\204\320\276\320\274", nullptr));
        addVertexButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\262\320\265\321\200\321\210\320\270\320\275\321\203", nullptr));
        removeVertexButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \320\262\320\265\321\200\321\210\320\270\320\275\321\203", nullptr));
        addEdgeButton->setText(QCoreApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \321\200\320\265\320\261\321\200\320\276", nullptr));
        removeEdgeButton->setText(QCoreApplication::translate("MainWindow", "\320\243\320\264\320\260\320\273\320\270\321\202\321\214 \321\200\320\265\320\261\321\200\320\276", nullptr));
        clearButton->setText(QCoreApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\263\321\200\320\260\321\204", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200\321\213 \320\276\320\261\321\205\320\276\320\264\320\260", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\320\235\320\260\321\207\320\260\320\273\321\214\320\275\320\260\321\217 \320\262\320\265\321\200\321\210\320\270\320\275\320\260:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\320\232\320\276\320\275\320\265\321\207\320\275\320\260\321\217 \320\262\320\265\321\200\321\210\320\270\320\275\320\260:", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("MainWindow", "\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274\321\213", nullptr));
        bfsButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\205\320\276\320\264 \320\262 \321\210\320\270\321\200\320\270\320\275\321\203 (BFS)", nullptr));
        dfsButton->setText(QCoreApplication::translate("MainWindow", "\320\236\320\261\321\205\320\276\320\264 \320\262 \320\263\320\273\321\203\320\261\320\270\320\275\321\203 (DFS)", nullptr));
        dijkstraButton->setText(QCoreApplication::translate("MainWindow", "\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274 \320\224\320\265\320\271\320\272\321\201\321\202\321\200\321\213", nullptr));
        floydButton->setText(QCoreApplication::translate("MainWindow", "\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274 \320\244\320\273\320\276\320\271\320\264\320\260-\320\243\320\276\321\200\321\210\320\265\320\273\320\273\320\260", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("MainWindow", "\320\240\320\265\320\267\321\203\320\273\321\214\321\202\320\260\321\202", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
