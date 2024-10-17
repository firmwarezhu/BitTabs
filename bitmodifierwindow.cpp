#include "bitmodifierwindow.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QRegularExpression>
#include <QMessageBox>

bitmodifierwindow::bitmodifierwindow(QWidget *parent) : QWidget(parent), currentValue(0)
{
    // Layouts
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Fix the spacing between items and the edges of the layout
    mainLayout->setSpacing(10); // Set the fixed space between items
    mainLayout->setContentsMargins(20, 10, 20, 40); // Remove any default 

    // Reminder label
    patternReminderLabel = new QLabel("Reminder:\n- Hex: start with '0x' or end with 'h' or without them (e.g., 0x1F,1Fh,1F) \n- It's case-insensitive", this);
    patternReminderLabel->setStyleSheet("font-size: 14px; color: #333; padding: 5px;");
    mainLayout->addWidget(patternReminderLabel);

    // Input label 
    QLabel *inputLabel = new QLabel("Enter Hex:", this);
    inputLabel->setStyleSheet("font-size: 14px; color: #333;");
    inputLabel->setContentsMargins(0, 0, 0, 5); // Adjust the bottom margin

    // Hex input
    hexInput = new QLineEdit(this);
    hexInput->setPlaceholderText("Enter a value...");
    hexInput->setStyleSheet("padding: 10px; border-radius: 5px; border: 1px solid #ccc; font-size: 14px;");

    mainLayout->addWidget(inputLabel);
    mainLayout->addWidget(hexInput);

    hex2BinButton = new QPushButton("Hex2Bin", this);
    hex2BinButton->setStyleSheet(
    "background-color: #4CAF50; color: white; border: none; padding: 10px 15px; border-radius: 5px; font-size: 14px;"
    "font-weight: bold; cursor: pointer;"
    "}"
    "QPushButton:hover { background-color: #45a049; }"
    );
    mainLayout->addWidget(hex2BinButton);

    // Create bit labels and buttons for 32 bits
    QGridLayout *bitLayout = new QGridLayout();

    for (int i = 0; i < 32; i++) {

        // Ensure grayPalette and boldFont are defined
        QPalette grayPalette;
        grayPalette.setColor(QPalette::WindowText, Qt::gray);
        QFont boldFont;
        boldFont.setBold(true);

        bitLabels[i] = new QLabel(QString::number(31 - i), this);
        bitLabels[i]->setAlignment(Qt::AlignCenter);
        bitLabels[i]->setPalette(grayPalette);
        bitLabels[i]->setFont(boldFont);        // Apply bold font
        bitLabels[i]->setCursor(Qt::PointingHandCursor);
        bitLabels[i]->setAttribute(Qt::WA_Hover, true);


        bitButtons[i] = new QPushButton("0", this);
        bitButtons[i]->setStyleSheet("padding: 10px; border: 1px solid #ccc; border-radius: 5px; font-size: 14px;");
        bitButtons[i]->setFixedSize(QSize(30, 50)); // Set a fixed size for the buttons

        if (i < 16) {
            bitLayout->addWidget(bitLabels[i], 0, i);
            bitLayout->addWidget(bitButtons[i], 1, i);
        } else {
            bitLayout->addWidget(bitLabels[i], 2, i - 16);
            bitLayout->addWidget(bitButtons[i], 3, i - 16);
        }

        connect(bitButtons[i], &QPushButton::clicked, this, &bitmodifierwindow::onBitClicked);
    }

    mainLayout->addLayout(bitLayout);

    mainLayout->setSpacing(10);

    QLabel *updatedLabel = new QLabel("Updated Hex:", this);
    updatedLabel->setStyleSheet("font-size: 14px; color: #333;");
    mainLayout->addWidget(updatedLabel);

    updatedHexOutput = new QLineEdit(this);
    updatedHexOutput->setReadOnly(true);
    updatedHexOutput->setStyleSheet("padding: 10px; border-radius: 5px; border: 1px solid #ccc; font-size: 14px;");
    mainLayout->addWidget(updatedHexOutput);

    clearButton = new QPushButton("Clear", this);
    clearButton->setStyleSheet(
    "background-color: #4CAF50; color: white; border: none; padding: 10px 15px; border-radius: 5px; font-size: 14px;"
    "font-weight: bold; cursor: pointer;"
    "}"
    "QPushButton:hover { background-color: #45a049; }"
    );
    mainLayout->addWidget(clearButton);

    // Set the layout's size constraint to prevent it from expanding indefinitely
    mainLayout->setSizeConstraint(QLayout::SetFixedSize);
    
    // Connect buttons
    connect(hex2BinButton, &QPushButton::clicked, this, &bitmodifierwindow::onHex2BinClicked);
    connect(clearButton, &QPushButton::clicked, this, &bitmodifierwindow::onClearClicked);
}

void bitmodifierwindow::onHex2BinClicked()
{
    QString hexStr = hexInput->text();

    // Validate hex input
    if (hexStr.startsWith("0x", Qt::CaseInsensitive)) {
        hexStr = hexStr.mid(2); // Remove the "0x" prefix
    }

    if (hexStr.endsWith("h", Qt::CaseInsensitive)) {
        hexStr.chop(1); // Remove the "h" suffix
    }

    QRegularExpression hexRegex("^[0-9A-Fa-f]{1,8}$");
    if (!hexRegex.match(hexStr).hasMatch()) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid hex value (1-8 characters).");
        return;
    }

    // Convert hex to integer
    bool ok;
    currentValue = hexStr.toUInt(&ok, 16);

    if (!ok) {
        QMessageBox::warning(this, "Conversion Error", "Failed to convert hex to binary.");
        return;
    }

    updateBinaryRepresentation();
    updateHexValue();
}

void bitmodifierwindow::onBitClicked()
{
    QPushButton *clickedButton = qobject_cast<QPushButton *>(sender());
    if (!clickedButton)
        return;

    int bitIndex = -1;

    // Find the bit index for the clicked button
    for (int i = 0; i < 32; i++) {
        if (bitButtons[i] == clickedButton) {
            bitIndex = 31 - i; // Reverse the index to match MSB to LSB order
            break;
        }
    }

    if (bitIndex != -1) {
        toggleBit(bitIndex);
    }
}

void bitmodifierwindow::onClearClicked()
{
    hexInput->clear();
    updatedHexOutput->clear();

    currentValue = 0;
    for (int i = 0; i < 32; i++) {
        bitButtons[i]->setText("0");
        bitButtons[i]->setStyleSheet("background-color: none; padding: 10px; border: 1px solid #ccc; border-radius: 5px; font-size: 14px;");
    }
}

void bitmodifierwindow::updateBinaryRepresentation()
{
    for (int i = 0; i < 32; i++) {
        int bitValue = (currentValue >> (31 - i)) & 1;
        bitButtons[i]->setText(QString::number(bitValue));
        bitButtons[i]->setStyleSheet("background-color: none; padding: 10px; border: 1px solid #ccc; border-radius: 5px; font-size: 14px;");
    }
}

void bitmodifierwindow::updateHexValue()
{
    updatedHexOutput->setText(QString::number(currentValue, 16).toUpper());
}

void bitmodifierwindow::toggleBit(int bitIndex)
{
    // Toggle the bit
    currentValue ^= (1 << bitIndex);

    // Update the button text and background color
    int newBitValue = (currentValue >> bitIndex) & 1;
    bitButtons[31 - bitIndex]->setText(QString::number(newBitValue));

    // Toggle the button's background color 
    QString currentStyle = bitButtons[31 - bitIndex]->styleSheet();
    // Print the content of clickedBits
    qDebug() << "currentStyle:" << currentStyle;

    if (currentStyle.contains("yellow") == false) {
        bitButtons[31 - bitIndex]->setStyleSheet("background-color: yellow; padding: 10px; border: 1px solid #ccc; border-radius: 5px; font-size: 14px;");
        bitButtons[31 - bitIndex]->setFixedSize(QSize(30, 50)); 
    } else {
        bitButtons[31 - bitIndex]->setStyleSheet("background-color: none; padding: 10px; border: 1px solid #ccc; border-radius: 5px; font-size: 14px;");
        bitButtons[31 - bitIndex]->setFixedSize(QSize(30, 50)); 
    }

    updateHexValue();
}
