#ifndef BITMODIFIERWINDOW_H
#define BITMODIFIERWINDOW_H


#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QLabel>

class bitmodifierwindow : public QWidget
{
    Q_OBJECT

public:
    explicit bitmodifierwindow(QWidget *parent = nullptr);

private slots:
    void onHex2BinClicked();
    void onBitClicked();
    void onClearClicked();

private:
    void updateBinaryRepresentation();
    void updateHexValue();
    void toggleBit(int bitIndex);

    QLineEdit *hexInput;
    QLineEdit *updatedHexOutput;
    QPushButton *hex2BinButton;
    QPushButton *clearButton;
    QLabel *bitLabels[32];
    QPushButton *bitButtons[32];
    uint32_t currentValue;
};


#endif // BITMODIFIERWINDOW_H
