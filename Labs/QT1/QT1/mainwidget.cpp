#include "mainwidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSpacerItem>

mainWidget::mainWidget(QWidget *parent)
    : QWidget{parent}
{

    // Create and initialize the QLabel for First Name
    QLabel *firstNameLabel = new QLabel("First Name:");
    // Create and initialize the QLineEdit for entering the first name
    QLineEdit *firstNameLineEdit = new QLineEdit;

    // Create and initialize the QLabel for Last Name
    QLabel *lastNameLabel = new QLabel("Last Name:");
    // Create and initialize the QLineEdit for entering the last name
    QLineEdit *lastNameLineEdit = new QLineEdit;


    // Create and initialize the Refresh button

    refreshButton = new QPushButton("Refresh");
    // Create and initialize the QPushButton
    finishButton = new QPushButton("Finish");

    // Create and initialize the QTextEdit
    textEdit = new QTextEdit;

    // Create and initialize the QSpinBox
    ageSpinBox = new QSpinBox;
    ageSpinBox->setMinimum(0); // Set minimum age
    ageSpinBox->setMaximum(120); // Set maximum age

    // Create a vertical layout for the labels, line edit, and age spin box
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(firstNameLabel);
    verticalLayout->addWidget(firstNameLineEdit);
    verticalLayout->addWidget(lastNameLabel);
    verticalLayout->addWidget(lastNameLineEdit);
    verticalLayout->addWidget(ageSpinBox); // Add ageSpinBox to the layout

    // Create a grid layout for the radio buttons
    QGridLayout *gridLayout = new QGridLayout;
    QGroupBox *groupBox = new QGroupBox("Gender");
    maleRadioButton = new QRadioButton("Male");
    femaleRadioButton = new QRadioButton("Female");
    gridLayout->addWidget(maleRadioButton, 0, 0);
    gridLayout->addWidget(femaleRadioButton, 0, 1);
    groupBox->setLayout(gridLayout);

    // Add a spacer item for better display
    gridLayout->addItem(new QSpacerItem(50, 10), 0, 2, 1, 1);

    // Create a vertical layout to hold the vertical layout, group box, and button
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(verticalLayout);
    mainLayout->addWidget(groupBox);
    mainLayout->addWidget(refreshButton);
    mainLayout->addWidget(textEdit);
    mainLayout->addWidget(finishButton);

    // Set the main layout for the mainWidget
    setLayout(mainLayout);


    // Connect the clicked signal of the refreshButton to the slot function refresh

    connect(refreshButton, &QPushButton::clicked, this, &mainWidget::refresh);


    // Connect the clicked signal of the finishButton to the slot function fillSummary
    connect(finishButton, &QPushButton::clicked, this, &mainWidget::fillSummary);



    connect(firstNameLineEdit, &QLineEdit::returnPressed, this, &mainWidget::displayEnteredInfo);
    connect(lastNameLineEdit, &QLineEdit::returnPressed, this, &mainWidget::displayEnteredInfo);
    connect(ageSpinBox, QOverload<int>::of(&QSpinBox::valueChanged), this, &mainWidget::displayEnteredInfo);
    connect(maleRadioButton, &QRadioButton::toggled, this, &mainWidget::displayEnteredInfo);
    connect(femaleRadioButton, &QRadioButton::toggled, this, &mainWidget::displayEnteredInfo);



}


mainWidget::~mainWidget()
{
    // Clean up dynamically allocated memory
    delete firstNameLabel;
    delete lastNameLabel;
    delete refreshButton;
    delete radioButton;
    delete finishButton;
    delete textEdit;
}
void mainWidget::fillSummary()
{
    // Retrieve data entered by the user
    QString firstName = firstNameLineEdit->text();
    QString lastName = lastNameLineEdit->text();
    int age = ageSpinBox->value();
    QString gender;
    if (maleRadioButton->isChecked())
        gender = "Male";
    else if (femaleRadioButton->isChecked())
        gender = "Female";
    else
        gender = "Unknown";

    // Write the data to the QTextEdit
    QString summary = "First Name: " + firstName + "\n"
                      + "Last Name: " + lastName + "\n"
                      + "Age: " + QString::number(age) + "\n"
                      + "Gender: " + gender + "\n";

    textEdit->setText(summary);
}

void mainWidget::refresh()
{
    // Clear the text in the QLineEdit widgets
    firstNameLineEdit->clear();
    lastNameLineEdit->clear();
    // Clear the text in the QTextEdit widget
    textEdit->clear();
    // Clear the selection in the QSpinBox
    ageSpinBox->clear();
    // Clear the selection in the radio buttons
    maleRadioButton->setChecked(false);
    femaleRadioButton->setChecked(false);
}
void mainWidget::displayEnteredInfo()
{
    QString firstName = firstNameLineEdit->text();
    QString lastName = lastNameLineEdit->text();
    QString gender = maleRadioButton->isChecked() ? "Male" : "Female";
    int age = ageSpinBox->value();

    QString enteredInfo = "First Name: " + firstName + "\n"
                          + "Last Name: " + lastName + "\n"
                          + "Age: " + QString::number(age) + "\n"
                          + "Gender: " + gender + "\n\n";

    textEdit->append(enteredInfo);
}

