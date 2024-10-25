#include "addrsizecalc.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QButtonGroup>
#include <QString>
#include <QMessageBox>
#include <cmath>
#include <QDebug>

addrsizeCalc::addrsizeCalc(QWidget *parent)
    : QWidget{parent} {

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(10);
    layout->setContentsMargins(20, 20, 20, 30);

    // Hex/Decimal conversion section
    QLabel *inputLabel = new QLabel("<b>Integer Break Down:      </b>Enter Hex (e.g. 0x1A2B3C) or Decimal (e.g. 123456):", this);
    inputLabel->setStyleSheet("font-size: 12px; padding: 10px;");
    layout->addWidget(inputLabel);

    // Create a horizontal layout for input and result display
    QHBoxLayout *conversionLayout = new QHBoxLayout();

    // Input field for conversion
    inputField = new QLineEdit(this);
    inputField->setStyleSheet("font-size: 12px; padding: 10px;");
    inputField->setPlaceholderText("Enter a value...");
    conversionLayout->addWidget(inputField);

    // Equals sign
    QLabel *equalsLabel = new QLabel("=", this);
    equalsLabel->setStyleSheet("font-size: 12px; padding: 10px;");
    conversionLayout->addWidget(equalsLabel);

    // Result label
    resultConversionLineEdit = new QLineEdit(this);
    resultConversionLineEdit->setStyleSheet("font-size: 12px; padding: 10px;");
    conversionLayout->addWidget(resultConversionLineEdit);

    layout->addLayout(conversionLayout);

    // Create a horizontal layout
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    QPushButton *convertButton = new QPushButton("Break Down", this);
    convertButton->setStyleSheet(
        "QPushButton {"
        "   background-color: green;"
        "   color: white;"
        "   font-size: 12px;"
        "   padding: 10px;"
        "   border: 2px solid darkgray;"
        "   border-radius: 5px;"
        "}"
        );
    buttonLayout->addWidget(convertButton); // Add convert button to layout

    // Create the clear button
    QPushButton *clearBDButton = new QPushButton("Clear Breakdown", this);
    clearBDButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4A90E2;"  // Darker blue with a gray tint, same as before but slightly adjusted for thickness
        "   color: white;"
        "   font-size: 12px;"
        "   padding: 10px;"
        "   border: 2px solid #4A90E2;"  // Darker blue with a gray tint border to match the background
        "   border-radius: 5px;"
        "}"
    );
    buttonLayout->addWidget(clearBDButton); // Add clear button to layout
    // Add the button layout to your main layout
    layout->addLayout(buttonLayout); // Assuming mainLayout is your main layout

    resultLine = new QLineEdit(this);  // Ensure resultLine is a member variable
    resultLine->setPlaceholderText("Result will be displayed here");
    //set it read only and copiable
    resultLine->setReadOnly(true);
    resultLine->setStyleSheet("font-size: 12px; padding: 10px; text-align: left;");
    layout->addWidget(resultLine);

    // // Add a vertical spacer
    // QSpacerItem *spacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding);
    // layout->addItem(spacer); // Assuming mainLayout is your main layout

    // Hex/Decimal conversion section
    QLabel *SizeReminderLabel = new QLabel("<b>Unit to Hex:      </b> Decimal (e.g. 123456):", this);
    SizeReminderLabel->setStyleSheet("font-size: 12px; padding: 10px;");
    layout->addWidget(SizeReminderLabel);

    // Size to hex conversion section (in one line)
    QHBoxLayout *sizeConversionLayout = new QHBoxLayout();

    sizeInputField = new QLineEdit(this);
    sizeInputField->setStyleSheet("font-size: 12px; padding: 10px;");
    sizeInputField->setPlaceholderText("Enter a decimal value...");
    sizeConversionLayout->addWidget(sizeInputField);

    // Radio buttons for KB, MB, GB selection (CheckBoxes but only one can be selected)
    byteRadio = new QRadioButton("Byte", this);
    kbRadio = new QRadioButton("KB", this);
    mbRadio = new QRadioButton("MB", this);
    gbRadio = new QRadioButton("GB", this);

    // Group the radio buttons to allow only one selection
    QButtonGroup *unitGroup = new QButtonGroup(this);
    unitGroup->addButton(byteRadio);
    unitGroup->addButton(kbRadio);
    unitGroup->addButton(mbRadio);
    unitGroup->addButton(gbRadio);

    // Default selection is KB
    kbRadio->setChecked(true);

    // Add the radio buttons to the layout
    sizeConversionLayout->addWidget(byteRadio);
    sizeConversionLayout->addWidget(kbRadio);
    sizeConversionLayout->addWidget(mbRadio);
    sizeConversionLayout->addWidget(gbRadio);

    // Add equals sign and result label
    QLabel *equalsSign = new QLabel("=", this);
    sizeConversionLayout->addWidget(equalsSign);

    // Fixed size for the result label to accommodate 18 characters starting with 0x
    resultLabelForSize = new QLineEdit(this);
    resultLabelForSize->setFixedWidth(250);  // Adjust to ensure result fits 18 characters
    resultLabelForSize->setAlignment(Qt::AlignLeft);  // Left align the result
    resultLabelForSize->setStyleSheet("font-size: 12px; padding: 10px;");
    sizeConversionLayout->addWidget(resultLabelForSize);

    layout->addLayout(sizeConversionLayout);

    // Create a horizontal layout for calculate and clear size buttons
    QHBoxLayout *sizeButtonLayout = new QHBoxLayout();

    // Calculate button for size-to-hex conversion
    QPushButton *calculateButton = new QPushButton("Calculate", this);
    calculateButton->setStyleSheet(
        "QPushButton {"
        "   background-color: green;"
        "   color: white;"
        "   font-size: 12px;"
        "   padding: 10px;"
        "   border: 2px solid darkgray;"
        "   border-radius: 5px;"
        "}"
        );
    sizeButtonLayout->addWidget(calculateButton); // Add calculate button to layout

    // Create the clear size button
    QPushButton *clearSizeButton = new QPushButton("Clear Size", this);
    clearSizeButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4A90E2;"  // Darker blue with a gray tint, same as before but slightly adjusted for thickness
        "   color: white;"
        "   font-size: 12px;"
        "   padding: 10px;"
        "   border: 2px solid #4A90E2;"  // Darker blue with a gray tint border to match the background
        "   border-radius: 5px;"
        "}"
        );

    sizeButtonLayout->addWidget(clearSizeButton); // Add clear size button to layout

    // Add the size button layout to your main layout
    layout->addLayout(sizeButtonLayout); // Assuming mainLayout is your main layout

    // Hex/Decimal conversion section
    QLabel *TransformReminderLabel = new QLabel("<b>Where to Hex:      </b> Decimal (e.g. 123456):", this);
    TransformReminderLabel->setStyleSheet("font-size: 12px; padding: 10px;");
    layout->addWidget(TransformReminderLabel);

    // Create radio buttons for operation selection
    addButton = new QRadioButton("Add", this);
    subtractButton = new QRadioButton("Subtract", this);
    addButton->setChecked(true); // Set addition as the default selected

    // Add radio buttons to the layout
    QHBoxLayout *operationLayout = new QHBoxLayout();
    operationLayout->addWidget(addButton);
    operationLayout->addWidget(subtractButton);
    operationLayout->setAlignment(Qt::AlignLeft); // Align to the left
    layout->addLayout(operationLayout); // Ensure they are in the same layout

    // Create a horizontal layout for all inputs, labels, equals, and result
    QHBoxLayout *chunkCalcLayout = new QHBoxLayout();
    // Create input fields and labels
    createInputLabel(gbInput, gbLabel, "<b>GB +</b>", chunkCalcLayout);
    createInputLabel(mbInput, mbLabel, "<b>MB +</b>", chunkCalcLayout);
    createInputLabel(kbInput, kbLabel, "<b>KB +</b>", chunkCalcLayout);
    createInputLabel(bInput, bLabel, "<b>Byte</b>", chunkCalcLayout);

    // Equals label
    QLabel *newequalsLabel = new QLabel("<b>=</b>", this);
    newequalsLabel->setStyleSheet("font-size: 12px; padding: 10px;");
    chunkCalcLayout->addWidget(newequalsLabel);

    // Result line edit
    resulttransformLineEdit = new QLineEdit(this);
    resulttransformLineEdit->setStyleSheet("font-size: 12px; padding: 10px;");
    chunkCalcLayout->addWidget(resulttransformLineEdit);

    // Add the chunkCalcLayout to the conversion layout
    layout->addLayout(chunkCalcLayout);

    // Create a horizontal layout for the buttons
    QHBoxLayout *tfbuttonLayout = new QHBoxLayout();

    // Transform button
    QPushButton *transformButton = new QPushButton("Transform", this);
    transformButton->setStyleSheet(
        "QPushButton {"
        "   background-color: green;"
        "   color: white;"
        "   font-size: 12px;"
        "   padding: 10px;"
        "   border: 2px solid darkgray;"
        "   border-radius: 5px;"
        "}"
        );

    tfbuttonLayout->addWidget(transformButton);

    // Clear button
    QPushButton *clearButton = new QPushButton("Clear Tranform", this);
    clearButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #4A90E2;"  // Darker blue with a gray tint, same as before but slightly adjusted for thickness
        "   color: white;"
        "   font-size: 12px;"
        "   padding: 10px;"
        "   border: 2px solid #4A90E2;"  // Darker blue with a gray tint border to match the background
        "   border-radius: 5px;"
        "}"
        );

    tfbuttonLayout->addWidget(clearButton);

    // Add button layout to the main layout
    layout->addLayout(tfbuttonLayout);


    // Connect Transform button to calculation logic
    connect(transformButton, &QPushButton::clicked, [this]() {
        long long totalBytes = 0;

        // Read values from input fields
        bool ok;
        if (addButton->isChecked()){
            totalBytes += gbInput->text().toLongLong(&ok) * 1024 * 1024 * 1024;
            totalBytes += mbInput->text().toLongLong(&ok) * 1024 * 1024;
            totalBytes += kbInput->text().toLongLong(&ok) * 1024;
            totalBytes += bInput->text().toLongLong(&ok);
        }

        if (subtractButton ->isChecked()){
            if (gbInput->text().toLongLong(&ok) != 0) {
                totalBytes += gbInput->text().toLongLong(&ok) * 1024 * 1024 * 1024;
                totalBytes -= mbInput->text().toLongLong(&ok) * 1024 * 1024;
                totalBytes -= kbInput->text().toLongLong(&ok) * 1024;
                totalBytes -= bInput->text().toLongLong(&ok);
            }else if (mbInput->text().toLongLong(&ok) != 0) {
                totalBytes += mbInput->text().toLongLong(&ok) * 1024 * 1024;
                totalBytes -= kbInput->text().toLongLong(&ok) * 1024;
                totalBytes -= bInput->text().toLongLong(&ok);
            }else if (kbInput->text().toLongLong(&ok) != 0) {
                totalBytes += kbInput->text().toLongLong(&ok) * 1024;
                totalBytes -= bInput->text().toLongLong(&ok);
            }else if (bInput->text().toLongLong(&ok) != 0) {
                totalBytes += bInput->text().toLongLong(&ok);
            }
        }
        // Convert to hex and display result
        resulttransformLineEdit->setText(QString::number(totalBytes, 16).toUpper().prepend("0x"));
    });

    // Connect Clear button to reset inputs and output
    connect(clearButton, &QPushButton::clicked, [this]() {
        gbInput->clear();
        mbInput->clear();
        kbInput->clear();
        bInput->clear();
        resulttransformLineEdit->clear();
    });

    // Connect signals
    connect(convertButton, &QPushButton::clicked, this, &addrsizeCalc::convert);
    // Connect the return key event
    connect(inputField, &QLineEdit::returnPressed, this, &addrsizeCalc::convert);
    // Connect the clear button to the clear function
    connect(clearBDButton, &QPushButton::clicked, this, &addrsizeCalc::clearFields);
    connect(calculateButton, &QPushButton::clicked, this, &addrsizeCalc::convertSizeToHex);
    // Connect the clear size button to the clear function
    connect(clearSizeButton, &QPushButton::clicked, this, &addrsizeCalc::clearSizeFields);
    connect(sizeInputField, &QLineEdit::returnPressed, this, &addrsizeCalc::convertSizeToHex);
    connect(kbRadio, &QRadioButton::toggled, this, &addrsizeCalc::clearResultLabel);
    connect(mbRadio, &QRadioButton::toggled, this, &addrsizeCalc::clearResultLabel);
    connect(gbRadio, &QRadioButton::toggled, this, &addrsizeCalc::clearResultLabel);
    connect(addButton, &QRadioButton::toggled, this, &addrsizeCalc::addSubtractRadioChecked);
    connect(subtractButton, &QRadioButton::toggled, this, &addrsizeCalc::addSubtractRadioChecked);

    qDebug() << "The end of addrsizeCalc";



}

addrsizeCalc::~addrsizeCalc() {
}

void addrsizeCalc::clearResultLabel() {
    resultLabelForSize->setText("");  // Clear result and reset to 0x
}

void addrsizeCalc::convert() {
    QString inputText = inputField->text();
    bool isHex = inputText.startsWith("0x", Qt::CaseInsensitive);
    bool ok;
    quint64 number = 0;

    // Convert the input to a number
    if (isHex) {
        number = inputText.toULongLong(&ok, 16);
        qDebug() << "hex number:" << number;
    } else {
        number = inputText.toULongLong(&ok, 10);
        qDebug() << "decnumber:" << number;
    }

    if (!ok) {
        QMessageBox::warning(this, "Conversion Error", "Invalid input! Please enter a valid number.");
        return;
    }

    //update the result to resultConversionLineEdit, if is hex then show decimal else show hex
    if (isHex) {
        resultConversionLineEdit->setText(QString::number(number));
    } else {
        resultConversionLineEdit->setText(QString("0x%1").arg(number, 0, 16).toUpper().replace("0X", "0x"));
    }

    // Calculate sizes
    quint64 bytes = number;
    quint64 kb = bytes / 1024;
    quint64 mb = kb / 1024;
    quint64 gb = mb / 1024;
    mb = mb % 1024;  // Remaining megabytes after full gigabytes
    kb = kb % 1024;  // Remaining kilobytes after full megabytes
    quint64 remainingBytes = bytes % 1024;  // Remaining bytes after full kilobytes
    // Debugging output
    qDebug() << "Bytes:" << bytes;
    qDebug() << "GB:" << gb;
    qDebug() << "MB:" << mb;
    qDebug() << "KB:" << kb;
    qDebug() << "Remaining Bytes:" << remainingBytes;
    // Generate the result message in format: xxxGB + yyyMB + zzzKB + sssBytes
    QString result = QString("%1 = %2GB + %3MB + %4KB + %5Byte")
                         .arg(inputText)
                         .arg(gb)
                         .arg(mb)
                         .arg(kb)
                         .arg(remainingBytes);

    // Display the result in resultLine

    if (result.length() < resultLine->maxLength()) {
        resultLine->setText(result);
    } else {
        // Handle the case where the text is too long
        resultLine->setText("Text too long");
    }


}

// Implement the clearFields function
void addrsizeCalc::clearFields() {
    inputField->clear(); // Clear the input label
    resultLine->setText(""); // Clear the result line
    resultConversionLineEdit->setText(""); // Clear result and reset
}

void addrsizeCalc::convertSizeToHex() {
    bool ok;
    quint64 userInput = sizeInputField->text().toULongLong(&ok, 10);  // Read decimal input

    if (!ok || userInput == 0) {
        QMessageBox::warning(this, "Conversion Error", "Please enter a valid number.");
        return;
    }

    quint64 bytes = 0;

    // Convert input to bytes based on the selected unit
    if(byteRadio->isChecked()) {
        bytes = userInput;
    } else if (kbRadio->isChecked()) {
        bytes = userInput * 1024;  // KB to bytes
    } else if (mbRadio->isChecked()) {
        bytes = userInput * 1024 * 1024;  // MB to bytes
    } else if (gbRadio->isChecked()) {
        bytes = userInput * 1024 * 1024 * 1024;  // GB to bytes
    }

    // Convert bytes to hexadecimal (lowercase '0x' but uppercase letters A-F)
    QString hexValue = QString("0x%1").arg(bytes, 0, 16).toUpper().replace("0X", "0x");

    // Ensure result label has a fixed size of 18 characters and is left-aligned
    resultLabelForSize->setText(QString("%1").arg(hexValue, 18, QLatin1Char(' ')));
}

// Implement the clearSizeFields function
void addrsizeCalc::clearSizeFields() {
    sizeInputField->clear(); // Clear the size input field
    resultLabelForSize->clear(); // Clear the result label for size
}

// Helper function to create input and label
void addrsizeCalc::createInputLabel(QLineEdit *&inputField, QLabel *&label, const QString &labelText, QHBoxLayout *layout) {
    inputField = new QLineEdit(this);
    inputField->setStyleSheet("font-size: 12px; padding: 10px;");
    inputField->setPlaceholderText("0");

    label = new QLabel(labelText, this);

    layout->addWidget(inputField);
    layout->addWidget(label);
}

// add and subtract radio checked event slot function
void addrsizeCalc::addSubtractRadioChecked() {
    // Modify the label text based on the checked radio button
    if (addButton->isChecked()) {
        gbLabel->setText("<b>GB +</b>");
        mbLabel->setText("<b>MB +</b>");
        kbLabel->setText("<b>KB +</b>");
    } else if (subtractButton->isChecked()) {
        gbLabel->setText("<b>GB -</b>");
        mbLabel->setText("<b>MB -</b>");
        kbLabel->setText("<b>KB -</b>");
    }

    gbInput->clear();
    mbInput->clear();
    kbInput->clear();
    bInput->clear();
    resulttransformLineEdit->clear();
}

