#ifndef power2calc_H
#define power2calc_H

#include <QWidget>
#include <QComboBox>
#include <QGridLayout> // Include QGridLayout

class power2calc : public QWidget {
    Q_OBJECT

public:
    explicit power2calc(QWidget *parent = nullptr);
//slot functions
private slots:
    void updateComboBoxes();
private:
    QComboBox *powerComboBox;
    QComboBox *hexComboBox;
    QComboBox *decimalComboBox;
    QComboBox *unitsComboBox;
    QGridLayout *gridLayout; // Declare the grid layout
};

#endif // power2calc_H