#include "power2calc.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QGridLayout>
#include <QString>
#include <cmath>
#include <QGroupBox>

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
    QLabel *powerLabel = new QLabel("2<sup>n</sup>   n(0-60) :", this);
    QLabel *hexLabel = new QLabel("Hexadecimal:", this);
    QLabel *decimalLabel = new QLabel("Decimal:", this);

    // Set label styles
    // powerLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2196F3;");
    // hexLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2196F3;");
    // decimalLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2196F3;");

    powerLabel->setStyleSheet(
            "background-color: #2196F3; color: white; border: none; padding: 10px 15px; border-radius: 5px; font-size: 14px;"
            "font-weight: bold; cursor: pointer;"
            "}"
            "QPushButton:hover { background-color: #1976D2; }"
            );
    hexLabel->setStyleSheet(
            "background-color: #2196F3; color: white; border: none; padding: 10px 15px; border-radius: 5px; font-size: 14px;"
            "font-weight: bold; cursor: pointer;"
            "}"
            "QPushButton:hover { background-color: #1976D2; }"
            );
    decimalLabel->setStyleSheet(
            "background-color: #2196F3; color: white; border: none; padding: 10px 15px; border-radius: 5px; font-size: 14px;"
            "font-weight: bold; cursor: pointer;"
            "}"
            "QPushButton:hover { background-color: #1976D2; }"
            );



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
    powerComboBox->setStyleSheet("padding: 10px; border-radius: 5px; border: 1px solid black; background-color: #fff;");
    hexComboBox->setStyleSheet("padding: 10px; border-radius: 5px; border: 1px solid black; background-color: #fff;");
    decimalComboBox->setStyleSheet("padding: 10px; border-radius: 5px; border: 1px solid black; background-color: #fff;");
    // Populate the combo boxes
    for (int i = 0; i <= 60; ++i) { // Change back to 60
        unsigned long long powerValue = 1ULL << i; // Use bit shifting
        powerComboBox->addItem(QString::number(i));
        hexComboBox->addItem(QString("0x%1").arg(powerValue, 0, 16));
        decimalComboBox->addItem(QString::number(powerValue));
    }
    // Connect signals
    connect(powerComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &power2calc::updateComboBoxes);
    connect(hexComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &power2calc::updateComboBoxes);
    connect(decimalComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &power2calc::updateComboBoxes);

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

    mainLayout->addSpacing(20);

        // QLabel as a custom title with HTML for "2^n" formatting
        QLabel *titleLabel = new QLabel("<b>2<sup>n</sup></b> representations:", this);
        titleLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: #2196F3;");
        titleLabel->setAlignment(Qt::AlignLeft);
        mainLayout->addWidget(titleLabel);

        // GroupBox to group the results and add a title "2^n"
        QGroupBox *resultGroup = new QGroupBox(this);
        resultGroup->setStyleSheet("background-color: #f0f0f0; padding: 10px;");  // Light grey background with padding
        QVBoxLayout *groupLayout = new QVBoxLayout(resultGroup);

        // Custom font for labels
        QFont fixedLabelFont;
        fixedLabelFont.setBold(true);

        QFont valueFont;
        valueFont.setItalic(true);

        // Row 1: Address Line number
        QHBoxLayout *addrlineLayout = new QHBoxLayout();
        QLabel *addrlineLabel = new QLabel("Address Line number:", this);
        addrlineLabel->setFont(fixedLabelFont);

        QLabel *addrlineValueLabel = new QLabel("0 address line", this);  // Placeholder for dynamic text
        addrlineValueLabel->setFont(valueFont);
        addrlineValueLabel->setAlignment(Qt::AlignRight);

        addrlineLayout->addWidget(addrlineLabel);
        addrlineLayout->addStretch();  // Add stretch to push value to the right
        addrlineLayout->addWidget(addrlineValueLabel);
        groupLayout->addLayout(addrlineLayout);

        // Row 2: Address space size
        QHBoxLayout *addrSpaceSizeLayout = new QHBoxLayout();
        QLabel *addrSpaceSizeLabel = new QLabel("Address space size:", this);
        addrSpaceSizeLabel->setFont(fixedLabelFont);

        QLabel *addrSpaceSizeValueLabel = new QLabel("0x0 = 0 Byte", this);  // Placeholder for dynamic text
        addrSpaceSizeValueLabel->setFont(valueFont);
        addrSpaceSizeValueLabel->setAlignment(Qt::AlignRight);

        addrSpaceSizeLayout->addWidget(addrSpaceSizeLabel);
        addrSpaceSizeLayout->addStretch();
        addrSpaceSizeLayout->addWidget(addrSpaceSizeValueLabel);
        groupLayout->addLayout(addrSpaceSizeLayout);

        // Row 3: Address range
        QHBoxLayout *addrRangeLayout = new QHBoxLayout();
        QLabel *addrRangeLabel = new QLabel("Address range:", this);
        addrRangeLabel->setFont(fixedLabelFont);

        QLabel *addrRangeValueLabel = new QLabel("From 0 to 0", this);  // Placeholder for dynamic text
        addrRangeValueLabel->setFont(valueFont);
        addrRangeValueLabel->setAlignment(Qt::AlignRight);

        addrRangeLayout->addWidget(addrRangeLabel);
        addrRangeLayout->addStretch();
        addrRangeLayout->addWidget(addrRangeValueLabel);
        groupLayout->addLayout(addrRangeLayout);

        // Add the group box to the main layout
        mainLayout->addWidget(resultGroup);



    mainLayout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding));
    
}

// Define the updateComboBoxes function
void power2calc::updateComboBoxes() {    
    //get the combox that triggered the event
    QComboBox *senderComboBox = qobject_cast<QComboBox *>(sender());
    //get the index of the selected item
    int currentIndex = senderComboBox->currentIndex();
    //set the text of the other combo box
    if (senderComboBox == powerComboBox) {
        hexComboBox->setCurrentIndex(currentIndex);
        decimalComboBox->setCurrentIndex(currentIndex);
    } else if (senderComboBox == hexComboBox) {
        powerComboBox->setCurrentIndex(currentIndex);
        decimalComboBox->setCurrentIndex(currentIndex);
    } else if (senderComboBox == decimalComboBox) {
        powerComboBox->setCurrentIndex(currentIndex);
        hexComboBox->setCurrentIndex(currentIndex);
    }
}