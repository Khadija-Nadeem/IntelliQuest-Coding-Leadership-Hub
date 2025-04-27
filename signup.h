#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>

namespace Ui {
class signup;
}

class signup : public QDialog
{
    Q_OBJECT

public:
    explicit signup(QWidget *parent = nullptr);
    ~signup();

private slots:
    void on_pushButton_3_clicked();
    void on_pushButton_signup_clicked();

    void on_lineEdit_username_editingFinished();

    void on_lineEdit_email_editingFinished();

private:
    Ui::signup *ui;

    bool validateSignup();              // Declare validateSignup function
    bool checkDuplicateUser();          // Declare checkDuplicateUser function
    void insertSignUpDetails();         // Declare insertSignUpDetails function
    bool isValidEmail(const QString &email);
};

#endif // SIGNUP_H
