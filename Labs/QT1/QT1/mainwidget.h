#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QRadioButton>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QSpacerItem>
#include <QSpinBox>
class mainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit mainWidget(QWidget *parent = nullptr);
    ~mainWidget();
    QLabel *firstNameLabel;
    QLabel *lastNameLabel;
    QPushButton *refreshButton;
    QRadioButton *radioButton;
    QPushButton *finishButton;
    QTextEdit *textEdit;
    QRadioButton *maleRadioButton;
    QRadioButton *femaleRadioButton;
    QSpinBox *ageSpinBox;
    QLineEdit *lastNameLineEdit;
    QLineEdit *firstNameLineEdit;
private slots:
    void fillSummary();
    void refresh();
    void displayEnteredInfo();


signals:
};

#endif // MAINWIDGET_H
