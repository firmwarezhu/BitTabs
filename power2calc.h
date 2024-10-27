#ifndef power2calc_H
#define power2calc_H

#include <QWidget>
#include <QComboBox>
#include <QGridLayout> // Include QGridLayout
#include <QLabel>
#include <QMenu>
#include <QClipboard>
#include <QApplication> // Include QApplication for QClipboard

class CopyableComboBox : public QComboBox {
    Q_OBJECT

public:
    explicit CopyableComboBox(QWidget *parent = nullptr) : QComboBox(parent) {
        setContextMenuPolicy(Qt::CustomContextMenu);
        connect(this, &QComboBox::customContextMenuRequested, this, &CopyableComboBox::showContextMenu);
    }

private slots:
    void showContextMenu(const QPoint &pos) {
        QMenu contextMenu;

        QAction *copyAction = new QAction("Copy", &contextMenu);
        connect(copyAction, &QAction::triggered, this, &CopyableComboBox::copyText);
        contextMenu.addAction(copyAction);

        contextMenu.exec(mapToGlobal(pos));
    }

    void copyText() {
        QClipboard *clipboard = QApplication::clipboard();  // No longer an incomplete type
        clipboard->setText(currentText());
    }
};

class power2calc : public QWidget {
    Q_OBJECT

public:
    explicit power2calc(QWidget *parent = nullptr);
//slot functions
private slots:
    void updateComboBoxes();
private:
    CopyableComboBox *powerComboBox;
    CopyableComboBox *hexComboBox;
    CopyableComboBox *decimalComboBox;
    CopyableComboBox *unitsComboBox;
    QGridLayout *gridLayout; // Declare the grid layout
    QLabel *titleLabel;
    QLabel *addrlineValueLabel;
    QLabel *addrSpaceSizeValueLabel;
    QLabel *addrRangeValueLabel;
    
};

#endif // power2calc_H