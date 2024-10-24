#ifndef ADDRSIZECALC_H
#define ADDRSIZECALC_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>



class addrsizeCalc : public QWidget
{
    Q_OBJECT

public:
    explicit addrsizeCalc(QWidget *parent = nullptr);
    ~addrsizeCalc();

private slots:
    void convert();               // Slot for handling hex/decimal input conversion
    void convertSizeToHex();      // Slot for handling KB/MB/GB input conversion to hex
    void clearResultLabel();
    void clearFields();
    void clearSizeFields();
    void addSubtractRadioChecked();
private:
    void createInputLabel(QLineEdit *&inputField, QLabel *&label, const QString &labelText, QHBoxLayout *layout);
private:
    QLineEdit *inputField;        // Input field for hex/decimal conversions
    QLineEdit *sizeInputField;    // Input field for size (KB, MB, GB) conversions
    QLineEdit *resultConversionLineEdit;
    QRadioButton *byteRadio;        // Radio button for Byte
    QRadioButton *kbRadio;        // Radio button for KB
    QRadioButton *mbRadio;        // Radio button for MB
    QRadioButton *gbRadio;        // Radio button for GB
    QLineEdit *resultLine;          // Label to display hex/decimal conversion results
    QLineEdit *resultLabelForSize;   // Label to display size-to-hex conversion results (18 chars fixed size)
    QRadioButton *addButton;
    QRadioButton *subtractButton;
    QLabel *gbLabel;               // Added gbLabel
    QLabel *mbLabel;               // Added mbLabel
    QLabel *kbLabel;               // Added kbLabel
    QLabel *bLabel;             // Added byteLabel
    QLineEdit *gbInput;
    QLineEdit *mbInput;
    QLineEdit *kbInput;
    QLineEdit *bInput;
    QLineEdit *resulttransformLineEdit;
};

#endif // ADDRSIZECALC_H
