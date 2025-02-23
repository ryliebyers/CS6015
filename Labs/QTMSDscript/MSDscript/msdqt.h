#ifndef MSDQT_H
#define MSDQT_H

#include <QWidget>
#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>

class MSDQT : public QWidget
{
    Q_OBJECT
public:
    explicit MSDQT(QWidget *parent = nullptr);
    QLineEdit *inputLineEdit;
    QPushButton *submitButton;
    QLineEdit *resultLineEdit;
    QPushButton *resetButton;
    QGroupBox *radioGroupBox;
    QString evaluateExpression(const QString &expression);
   QRadioButton *interpRadioButton;
   QRadioButton *prettyPrintRadioButton;
private slots:
    void handleSubmit();
    void handleReset();
signals:
};

#endif // MSDQT_H
