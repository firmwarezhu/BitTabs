#include "mainwindow.h"
#include <QTabWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include "bitviewerwindow.h"
#include "bitmodifierwindow.h"
#include "addrsizecalc.h"
#include "power2calc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Create the tab widget
    QTabWidget *tabWidget = new QTabWidget(this);

    tabWidget->setStyleSheet("QTabBar::tab { min-width: 100px; max-width: 200px; }");

    // Create the first tab with a layout
    QWidget *BitViewerTab = new BitViewerWindow();
    tabWidget->addTab(BitViewerTab, "BitViewer");

    // Create the BitModifier tab with a layout
    QWidget *BitModifierTab = new bitmodifierwindow();
    tabWidget->addTab(BitModifierTab, "BitModifier");

    // Create the third tab with a layout
    QWidget *Addrizecalc = new addrsizeCalc();
    tabWidget->addTab(Addrizecalc, "AddrSizeCalc");

    // Create the forth tab with a layout
    QWidget *Power2Calc = new power2calc();
    tabWidget->addTab(Power2Calc, "Power2Calc");

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
