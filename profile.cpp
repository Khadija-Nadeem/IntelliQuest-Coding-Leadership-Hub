#include "profile.h"
#include "ui_profile.h"
#include "home.h"
#include <QMessageBox>
#include "databasemanager.h" // Include DatabaseManager
#include <QRegularExpression>
#include "start.h"

profile::profile(QWidget *parent, int userId)
    : QDialog(parent)
    , ui(new Ui::profile)
    , currentUserId(userId) // Initialize user ID

{
    ui->setupUi(this);

    reloadProfileData();
    loadUserData(currentUserId);  // Reload data

    // Set initial states for the fields
    ui->lineEdit_name->setReadOnly(true); // Assuming lineEdit_name is the name field
    ui->lineEdit_email->setReadOnly(true); // Assuming lineEdit_email is the email field
    ui->pushButton_changePassword->setEnabled(false); // Assuming pushButton_changePassword is the change password button

    // Initially hide the change password form widget
      ui->widget->setVisible(false);

    connect(ui->checkBox_showPassword, &QCheckBox::toggled, this, [=](bool checked) {
        QLineEdit::EchoMode mode = checked ? QLineEdit::Normal : QLineEdit::Password; // Set echo mode
        ui->lineEdit_current->setEchoMode(mode);  // Toggle current password visibility
        ui->lineEdit_new->setEchoMode(mode);      // Toggle new password visibility
        ui->lineEdit_confirm->setEchoMode(mode);  // Toggle confirm password visibility

        // Update checkbox text
        ui->checkBox_showPassword->setText(checked ? "Hide Passwords" : "Show Passwords");
    });
}


profile::~profile()
{
    delete ui;
}

void profile::reloadProfileData() {
    DatabaseManager dbManager;

    // Ensure the database connection is open before proceeding
    if (!dbManager.connectToDatabase() || !dbManager.getDatabase().isOpen()) {
        qDebug() << "Failed to connect to database or database is not open.";
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
        return;
    }

    QSqlQuery query(DatabaseManager::getDatabase());
    query.prepare("SELECT username, email FROM users WHERE id = :id");
    query.bindValue(":id", currentUserId);

    if (query.exec() && query.next()) {
        ui->lineEdit_name->setText(query.value("username").toString());
        ui->lineEdit_email->setText(query.value("email").toString());
    } else {
        qDebug() << "Error fetching user data:" << query.lastError().text();
    }
}

void profile::on_pushButton_clicked() {
    // Enable the name and email fields
    ui->lineEdit_name->setReadOnly(false);
    ui->lineEdit_email->setReadOnly(false);

    // Enable the Change Password button
    ui->pushButton_changePassword->setEnabled(true);

    // Display a popup message
    QMessageBox::information(this, "Edit Profile", "You can now edit your profile information.");
}

void profile::on_pushButton_changePassword_clicked() {
    // Toggle the visibility of the change password form widget
    bool isVisible = ui->widget->isVisible();
    ui->widget->setVisible(!isVisible);
}

void profile::on_pushButton_4_clicked() {
    this->hide();

    home *homewindow = new home(this, currentUserId); // Pass user ID back
    homewindow->show();
}

// Add this method to load user data
void profile::loadUserData(int userId) {
    // Use DatabaseManager to get the active database connection
    DatabaseManager dbManager;
    if (!dbManager.connectToDatabase()) {
        qDebug() << "Failed to connect to database.";
        return;
    }

    QSqlQuery query(DatabaseManager::getDatabase());
    query.prepare("SELECT username, email FROM users WHERE id = :userId");
    query.bindValue(":userId", userId); // Use userId (int)

    if (query.exec()) {
        if (query.next()) {
            // Populate UI fields with user data
            ui->lineEdit_name->setText(query.value("username").toString());
            ui->lineEdit_email->setText(query.value("email").toString());
        } else {
            qDebug() << "No user found with the given ID.";
        }
    } else {
        qDebug() << "Failed to execute query:" << query.lastError().text();
    }
}

void profile::on_pushButton_saveChanges_clicked() {
    QString name = ui->lineEdit_name->text();
    QString email = ui->lineEdit_email->text();

    QRegularExpression emailRegex("^[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\\.[A-Za-z]{2,}$");
    QRegularExpressionMatch match = emailRegex.match(email);

    if (!match.hasMatch()) {
        QMessageBox::warning(this, "Invalid Email", "Please enter a valid email address.");
        return;
    }

    DatabaseManager dbManager;
    // Ensure the database connection is open before proceeding
    if (!dbManager.connectToDatabase() || !dbManager.getDatabase().isOpen()) {
        qDebug() << "Failed to connect to database or database is not open.";
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
        return;
    }

    QSqlQuery query(DatabaseManager::getDatabase());
    query.prepare("UPDATE users SET username = :name, email = :email WHERE id = :id");
    query.bindValue(":name", name);
    query.bindValue(":email", email);
    query.bindValue(":id", currentUserId);

    if (query.exec()) {
        QMessageBox::information(this, "Update Successful", "Your profile has been updated.");
    } else {
        qDebug() << "Error updating profile:" << query.lastError().text();
    }
}
void profile::on_pushButton_3_clicked() {
    // Show confirmation message box
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Cancel Changes", "Are you sure you want to cancel changes?",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        profile *profileWindow = new profile(this, currentUserId);  // Create a new instance of profile with the correct userId
        profileWindow->show();
        this->close();  // Close current profile window
    }
    // If user clicks No, do nothing (stay on the page and allow editing)
}

void profile::on_pushButton_2_clicked() {
    QString currentPassword = ui->lineEdit_current->text();
    QString newPassword = ui->lineEdit_new->text();
    QString confirmPassword = ui->lineEdit_confirm->text();

    // Step 1: Check if the current password is entered correctly
    if (currentPassword.isEmpty()) {
        QMessageBox::warning(this, "Empty Current Password", "Please enter your current password.");
        return;  // Exit function if current password is empty
    }

    // Ensure the database connection is open
    DatabaseManager dbManager;
    if (!dbManager.connectToDatabase() || !dbManager.getDatabase().isOpen()) {
        qDebug() << "Failed to connect to database.";
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
        return;
    }

    // Step 2: Validate current password in the database
    QSqlQuery query(DatabaseManager::getDatabase());
    query.prepare("SELECT password FROM users WHERE id = :id");
    query.bindValue(":id", currentUserId);

    if (query.exec() && query.next()) {
        QString storedPassword = query.value("password").toString();

        if (currentPassword == storedPassword) {
            // Step 3: Check if new password and confirm password are entered and match
            if (newPassword.isEmpty() || confirmPassword.isEmpty()) {
                QMessageBox::warning(this, "Empty Fields", "New password and confirm password cannot be empty.");
                return;  // Exit function if any of these fields are empty
            }

            if (newPassword == confirmPassword) {
                // Show confirmation message box
                QMessageBox::StandardButton reply;
                reply = QMessageBox::question(this, "Confirm Password Change", "Are you sure you want to change your password?",
                                              QMessageBox::Yes | QMessageBox::No);

                if (reply == QMessageBox::Yes) {
                    // Step 4: Update the password in the database
                    QSqlQuery updateQuery(DatabaseManager::getDatabase());
                    updateQuery.prepare("UPDATE users SET password = :newPassword WHERE id = :id");
                    updateQuery.bindValue(":newPassword", newPassword);
                    updateQuery.bindValue(":id", currentUserId);

                    if (updateQuery.exec()) {
                        QMessageBox::information(this, "Password Changed", "Your password has been successfully updated.");
                        ui->lineEdit_current->clear();
                        ui->lineEdit_new->clear();
                        ui->lineEdit_confirm->clear();
                    } else {
                        qDebug() << "Error updating password:" << updateQuery.lastError().text();
                        QMessageBox::critical(this, "Error", "Failed to change password.");
                    }
                } else {
                    QMessageBox::information(this, "Password Change Canceled", "Password change was canceled.");
                }
            } else {
                // Step 5: Show error if new and confirm passwords don't match
                QMessageBox::warning(this, "Password Mismatch", "New password and confirm password do not match.");
            }
        } else {
            // Show error if current password is incorrect
            QMessageBox::warning(this, "Incorrect Password", "The current password is incorrect.");
        }
    } else {
        qDebug() << "Error fetching current password:" << query.lastError().text();
        QMessageBox::critical(this, "Error", "Failed to fetch current password.");
    }
}


void profile::on_pushButton_deleteProfile_clicked()
{
    DatabaseManager dbManager;

    // Ensure the database connection is open before proceeding
    if (!dbManager.connectToDatabase() || !dbManager.getDatabase().isOpen()) {
        qDebug() << "Failed to connect to database or database is not open.";
        QMessageBox::critical(this, "Database Error", "Failed to connect to the database.");
        return;
    }

    // Confirm with the user before deleting
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Delete Profile", "Are you sure you want to delete your profile? This action cannot be undone.",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // Proceed with deleting the profile from the database
        QSqlQuery query(DatabaseManager::getDatabase());
        query.prepare("DELETE FROM users WHERE id = :id");
        query.bindValue(":id", currentUserId);

        if (query.exec()) {
            QMessageBox::information(this, "Profile Deleted", "Your profile has been successfully deleted.");
            // Close the profile window after deletion
            this->close();
            // Optionally, redirect to home or logout screen
            start *startwindow = new start(this);  // Assuming you have a home window
            startwindow->show();
        } else {
            qDebug() << "Error deleting profile:" << query.lastError().text();
            QMessageBox::critical(this, "Error", "Failed to delete profile. Please try again.");
        }
    }
}
