#include "login.h"
#include "ui_login.h"
#include "start.h"
#include "signup.h"
#include "home.h"

#include "databasemanager.h" // Include DatabaseManager


login::login(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);



    // Initialize the database connection
    if (!dbManager.connectToDatabase()) {
        qDebug() << "Error: Failed to connect to the database.";
    } else {
        qDebug() << "Database connected successfully.";
    }

    // Make the CheckBox toggle show/hide password
    connect(ui->checkBox, &QCheckBox::toggled, this, [=](bool checked) {
        if (checked) {
            ui->txtPswrd->setEchoMode(QLineEdit::Normal); // Show password
            ui->checkBox->setText("Hide Password");
        } else {
            ui->txtPswrd->setEchoMode(QLineEdit::Password); // Hide password
            ui->checkBox->setText("Show Password");
        }
    });
}

login::~login()
{
    delete ui;
}

void login::on_pushButton_2_clicked()
{
    this->hide();

    signup *signupwindow= new signup(this);
    signupwindow->show();
}


void login::on_pushButton_3_clicked()
{
    this->hide();

    start *startupwindow= new start(this);
    startupwindow->show();
}


void login::on_pushButton_clicked()
{
    if (validateLogin()) {
        attemptLogin(); // Call attemptLogin instead of login()
    }
}

// Method for login validation
bool login::validateLogin()
{
    QString name = ui->txtName->text(); // Assuming 'txtName' is your username input field
    QString pwd = ui->txtPswrd->text(); // Assuming 'txtPswrd' is your password input field

    if (name.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter username");
        return false;
    }
    if (pwd.isEmpty()) {
        QMessageBox::warning(this, "Validation Error", "Please enter password");
        return false;
    }
    return true;
}

// Method to check login credentials from the database
void login::attemptLogin()
{
    QString name = ui->txtName->text();
    QString pwd = ui->txtPswrd->text();

    if (!dbManager.getDatabase().isOpen()) {
        QMessageBox::warning(this, "Database Error", "Failed to connect to the database.");
        return;
    }

    QSqlQuery query(dbManager.getDatabase());
    query.prepare("SELECT id FROM users WHERE username = :name AND password = :password");
    query.bindValue(":name", name);
    query.bindValue(":password", pwd);

    if (query.exec()) {
        if (query.next()) {
            int userId = query.value(0).toInt(); // Fetch user ID
            QMessageBox::information(this, "Login Complete", "Glad to see you again!");

            // Pass user ID to the home page
            home *homeWindow = new home(this, userId);
            homeWindow->show();
            this->close();
        } else {
            QMessageBox::warning(this, "Authentication Error", "Invalid login details.");
        }
    } else {
        qDebug() << "Query execution failed:" << query.lastError().text();
    }
}

