#include "power2calc.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <cmath>

power2calc::power2calc(QWidget *parent) : QWidget(parent) {

    // Set background color
    setStyleSheet("background-color: #f0f0f0;"); // Light gray background
    //add vertical layout
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(20, 20, 20, 30);

    QGridLayout *gridLayout = new QGridLayout(this); // Create a grid layout
    gridLayout->setVerticalSpacing(20);
    // Create labels
    QLabel *powerLabel = new QLabel("2 Power (0-32) :", this);
    QLabel *hexLabel = new QLabel("Hexadecimal:", this);
    QLabel *decimalLabel = new QLabel("Decimal:", this);

    // Set label styles
    powerLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #333;");
    hexLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #333;");
    decimalLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: #333;");

    // Create combo boxes
    powerComboBox = new QComboBox(this);
    hexComboBox = new QComboBox(this);
    decimalComboBox = new QComboBox(this);

    // Set font size
    QFont font = powerComboBox->font();
    font.setPointSize(12);
    powerComboBox->setFont(font);
    hexComboBox->setFont(font);
    decimalComboBox->setFont(font);

    // Style combo boxes
    powerComboBox->setStyleSheet("padding: 10px; border-radius: 5px; border: 1px solid #ccc; background-color: #fff;");
    hexComboBox->setStyleSheet("padding: 10px; border-radius: 5px; border: 1px solid #ccc; background-color: #fff;");
    decimalComboBox->setStyleSheet("padding: 10px; border-radius: 5px; border: 1px solid #ccc; background-color: #fff;");

    // Populate the combo boxes
    for (int i = 0; i <= 32; ++i) {
        int powerValue = std::pow(2, i);
        powerComboBox->addItem(QString::number(i));
        hexComboBox->addItem(QString("0x%1").arg(powerValue, 0, 16));
        decimalComboBox->addItem(QString::number(powerValue));
    }
    // Connect signal
    connect(powerComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            [=](int index) {
                hexComboBox->setCurrentIndex(index);
                decimalComboBox->setCurrentIndex(index);
            });

// Add labels and combo boxes to the grid layout
    gridLayout->addWidget(powerLabel, 0, 0); // Row 0, Column 0
    gridLayout->addWidget(hexLabel, 0, 1); // Row 0, Column 1
    gridLayout->addWidget(decimalLabel, 0, 2); // Row 0 , Column 2
    gridLayout->addWidget(powerComboBox, 1, 0); // Row 1, Column 0
    gridLayout->addWidget(hexComboBox, 1, 1); // Row 1, Column 1
    gridLayout->addWidget(decimalComboBox, 1, 2); // Row 1, Column 2

    // Set vertical spacing between rows
    gridLayout->setVerticalSpacing(10);
    gridLayout->setContentsMargins(10, 10, 10, 10); // Adjust margins

    mainLayout->addLayout(gridLayout);
    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    
}
