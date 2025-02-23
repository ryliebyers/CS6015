#include "msdqt.h"
#include <QVBoxLayout>
#include <QLabel>
#include "expr.h"
#include "Env.h"
#include "val.h"
#include "parse.hpp"
#include "pointer.h"
MSDQT::MSDQT(QWidget *parent)
    : QWidget{parent}
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Expression input
    QLabel *inputLabel = new QLabel("Expression:", this);
    layout->addWidget(inputLabel);

    inputLineEdit = new QLineEdit(this);
    inputLineEdit->setFixedHeight(150); // Set height
    inputLineEdit->setFixedWidth(500); // Set width

    layout->addWidget(inputLineEdit);



    // Radio buttons
    QGroupBox *radioGroupBox = new QGroupBox(this);
    QHBoxLayout *radioLayout = new QHBoxLayout(radioGroupBox);

    interpRadioButton = new QRadioButton("Interp", radioGroupBox);
    prettyPrintRadioButton = new QRadioButton("PrettyPrint", radioGroupBox);

    radioLayout->addWidget(interpRadioButton);
    radioLayout->addWidget(prettyPrintRadioButton);

    layout->addWidget(radioGroupBox);

    // Submit button
    submitButton = new QPushButton("Submit", this);
    layout->addWidget(submitButton);
    connect(submitButton, &QPushButton::clicked, this, &MSDQT::handleSubmit);

    // Result display
    QLabel *resultLabel = new QLabel("Result:", this);
    layout->addWidget(resultLabel);

    resultLineEdit = new QLineEdit(this);
    resultLineEdit->setReadOnly(true);
    resultLineEdit->setFixedHeight(150); // Set height
    resultLineEdit->setFixedWidth(500); // Set height

    layout->addWidget(resultLineEdit);

    // Reset button
    resetButton = new QPushButton("Reset", this);
    layout->addWidget(resetButton);


    connect(resetButton, &QPushButton::clicked, this, &MSDQT::handleReset);



}
void MSDQT::handleSubmit() {
    // Get expression from inputLineEdit
    QString expression = inputLineEdit->text();

    // Convert QString to std::string
    std::string expressionStr = expression.toUtf8().constData();

    // Parse the expression
    try {
        auto expr = parse_str(expressionStr);

        // Evaluate the expression
        PTR(Env) env;
        PTR(Val) result = expr->interp(env);

        // Convert result to a printable string
        std::string resultStr = result->to_string();

        // Convert the result std::string to QString
        QString resultDisplay = QString::fromStdString(resultStr);

        // Display result in resultLineEdit
        resultLineEdit->setText(resultDisplay);
    } catch (const std::runtime_error& e) {
        // Display error message if parsing or evaluation fails
        QString errorMessage = QString::fromStdString(e.what());
        resultLineEdit->setText(errorMessage);
    }
}

void MSDQT::handleReset() {
    // Clear both inputLineEdit and resultLineEdit
    inputLineEdit->clear();
    resultLineEdit->clear();
}


