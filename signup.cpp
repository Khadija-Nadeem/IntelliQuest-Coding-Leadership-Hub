#include "signup.h"
#include "ui_signup.h"
#include "login.h"
#include "databasemanager.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

signup::signup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signup)
{
    ui->setupUi(this);

    connect(ui->checkBox, &QCheckBox::toggled, this, [=](bool checked) {
        if (checked) {
            ui->lineEdit_password->setEchoMode(QLineEdit::Normal); // Show password 1
            ui->lineEdit_confirmPassword->setEchoMode(QLineEdit::Normal); // Show password 2
            ui->checkBox->setText("Hide Passwords");
        } else {
            ui->lineEdit_password->setEchoMode(QLineEdit::Password); // Hide password 1
            ui->lineEdit_confirmPassword->setEchoMode(QLineEdit::Password); // Hide password 2
            ui->checkBox->setText("Show Passwords");
        }
    });
}

signup::~signup()
{
    delete ui;
}

void signup::on_pushButton_3_clicked()
{
    this->hide();

    login *loginupwindow= new login(this);
    loginupwindow->show();
}

void signup::on_pushButton_signup_clicked()
{
    if (validateSignup()) {
        if (!checkDuplicateUser()) {
            insertSignUpDetails();
        } else {
            QMessageBox::warning(this, "Signup Error", "Username already exists.");
        }
    }
}

// Method to validate inputs
bool signup::validateSignup()
{
    QString username = ui->lineEdit_username->text();
    QString email = ui->lineEdit_email->text();
    QString password = ui->lineEdit_password->text();
    QString confirmPassword = ui->lineEdit_confirmPassword->text();

    if (username.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter a username.");
        return false;
    }
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter an email address.");
        return false;
    }
    if (!isValidEmail(email)) {
        QMessageBox::warning(this, "Validation Error", "Invalid email format.");
        return false; // Prevent signup
    }
    if (password.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter a password.");
        return false;
    }
    if (confirmPassword.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please confirm your password.");
        return false;
    }
    if (password != confirmPassword) {
        QMessageBox::warning(this, "Validation Error", "Passwords do not match.");
        return false;
    }
    return true;
}

// Method to check for duplicate username
bool signup::checkDuplicateUser()
{
    QString username = ui->lineEdit_username->text();
    QSqlQuery query(DatabaseManager::getDatabase());

    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec()) {
        if (query.next()) {
            return true; // Username exists
        }
    } else {
        qDebug() << "Query error: " << query.lastError().text();
    }
    return false;
}

// Method to insert user details into the database
void signup::insertSignUpDetails()
{
    QString username = ui->lineEdit_username->text();
    QString email = ui->lineEdit_email->text();
    QString password = ui->lineEdit_password->text();

    QSqlQuery query(DatabaseManager::getDatabase()); // Corrected the class name to DatabaseManager

    query.prepare("INSERT INTO users (username, email, password) VALUES (:username, :email, :password)");
    query.bindValue(":username", username);
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (query.exec()) {
        QMessageBox::information(this, "Signup Complete", "Your account has been created successfully.");
        login *loginWindow = new login(this);
        loginWindow->show();  // Show the login page
        this->close();        // Close the signup window
    } else {
        QMessageBox::critical(this, "Database Error", "Failed to insert user details: " + query.lastError().text());
    }
}

// Method to validate email format
bool signup::isValidEmail(const QString &email)
{
    QRegularExpression emailRegex(
        R"(^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$)");
    return emailRegex.match(email).hasMatch();
}

void signup::on_lineEdit_username_editingFinished()
{
    if (checkDuplicateUser()) {
        QMessageBox::warning(this, "Signup Error", "Username already exists.");
    }
}


void signup::on_lineEdit_email_editingFinished()
{
    QString email = ui->lineEdit_email->text();
    if (!email.isEmpty() && !isValidEmail(email)) {
        QMessageBox::warning(this, "Validation Error", "Invalid email format.");
        ui->lineEdit_email->setFocus(); // Refocus to the email field
    }
}

