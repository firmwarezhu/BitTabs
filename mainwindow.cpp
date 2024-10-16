#include "mainwindow.h"
#include <QTabWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "bitviewerwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create the tab widget
    QTabWidget *tabWidget = new QTabWidget(this);

    // Create the first tab with a layout
    QWidget *BitViewerTab = new BitViewerWindow();
    QVBoxLayout *layoutBitViewerTab = new QVBoxLayout(BitViewerTab);
    QLabel *label1 = new QLabel("This is the bitviewer tab");
    QPushButton *button1 = new QPushButton("Button in Tab 1");
    layoutBitViewerTab->addWidget(label1);
    layoutBitViewerTab->addWidget(button1);
    tabWidget->addTab(BitViewerTab, "BitViewer");

    // Create the second tab with a layout
    QWidget *secondTab = new QWidget();
    QVBoxLayout *layout2 = new QVBoxLayout(secondTab);
    QLabel *label2 = new QLabel("This is the second tab");
    QPushButton *button2 = new QPushButton("Button in Tab 2");
    layout2->addWidget(label2);
    layout2->addWidget(button2);
    tabWidget->addTab(secondTab, "Tab 2");

    // Create the third tab with a layout
    QWidget *thirdTab = new QWidget();
    QVBoxLayout *layout3 = new QVBoxLayout(thirdTab);
    QLabel *label3 = new QLabel("This is the third tab");
    QPushButton *button3 = new QPushButton("Button in Tab 3");
    layout3->addWidget(label3);
    layout3->addWidget(button3);
    tabWidget->addTab(thirdTab, "Tab 3");

    // Style the tab bar to bold the font of the selected tab
    tabWidget->setStyleSheet(R"(
        QTabBar::tab {
            font: normal; /* Normal font for unselected tabs */
        }
        QTabBar::tab:selected {
            font: bold; /* Bold font for the selected tab */
        }
    )");

    // Set the tab widget as the central widget of the main window
    setCentralWidget(tabWidget);


}

MainWindow::~MainWindow() {}
