#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

#include <QMessageBox>

#include "databasemanager.h" // Include DatabaseManager

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    bool validateLogin(); // Validation method
    void attemptLogin();  // Renamed the login method to attemptLogin

    Ui::login *ui;

    DatabaseManager dbManager; // Instance of DatabaseManager
};

#endif // LOGIN_H
