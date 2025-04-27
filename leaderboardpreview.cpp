#include "leaderboardpreview.h"
#include "ui_leaderboardpreview.h"
#include "databasemanager.h"
#include "home.h"
#include "QMessageBox"

leaderboardPreview::leaderboardPreview(QWidget *parent, int userId)
    : QDialog(parent)
    , ui(new Ui::leaderboardPreview)
    , currentUserId(userId) // Initialize user ID
{
    ui->setupUi(this);

    DatabaseManager dbManager;
    if (!dbManager.connectToDatabase()) {
        qDebug() << "Failed to connect to database.";
        return;
    }

    displayLeaderboard();  // Display leaderboard when the dialog is shown
}

leaderboardPreview::~leaderboardPreview()
{
    delete ui;
}

void leaderboardPreview::on_pushButton_4_clicked()
{
    this->hide();

    home *homewindow= new home(this, currentUserId);
    homewindow->show();
}

void leaderboardPreview::displayLeaderboard()
{
    // Use DatabaseManager to get the active database connection
    DatabaseManager dbManager;
    if (!dbManager.connectToDatabase()) {
        qDebug() << "Failed to connect to database.";
        return;
    }

    // Query to get the leaderboard data
    QSqlQuery query;
    query.prepare("SELECT users.username, leaderboard.score, leaderboard.user_id "
                  "FROM leaderboard "
                  "JOIN users ON leaderboard.user_id = users.id "
                  "ORDER BY leaderboard.score DESC");

    if (!query.exec()) {
        qDebug() << "Query execution failed:" << query.lastError().text();
        return;
    }

    int rank = 1;
    ui->leaderboardTableWidget->setRowCount(0);  // Clear the table before populating

    // Loop through each row in the query result
    while (query.next()) {
        QString username = query.value(0).toString();
        int score = query.value(1).toInt();
        int userId = query.value(2).toInt();

        // Insert a new row for each player
        int row = ui->leaderboardTableWidget->rowCount();
        ui->leaderboardTableWidget->insertRow(row);

        // Add rank, username, and score to the table
        ui->leaderboardTableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(rank)));
        ui->leaderboardTableWidget->setItem(row, 1, new QTableWidgetItem(username));
        ui->leaderboardTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(score)));

        rank++;  // Increment rank for the next user
    }
}


void leaderboardPreview::on_refreshButton_clicked()
{
     displayLeaderboard();  // Simply call the existing method

    // Show a popup message
    QMessageBox::information(this, "Refresh", "Leaderboard has been refreshed successfully!");
}


void leaderboardPreview::on_searchButton_clicked()
{
    DatabaseManager dbManager;
    if (!dbManager.connectToDatabase()) {
        qDebug() << "Failed to connect to database.";
        return;
    }
    QString searchUsername = ui->searchLineEdit->text().trimmed();

    if (searchUsername.isEmpty()) {
        QMessageBox::warning(this, "Search", "Please enter a username to search.");
        return;
    }

    // Query to get the specific user's record
    QSqlQuery query;
    query.prepare("SELECT users.username, leaderboard.score, leaderboard.user_id "
                  "FROM leaderboard "
                  "JOIN users ON leaderboard.user_id = users.id "
                  "WHERE users.username = :username "
                  "ORDER BY leaderboard.score DESC");
    query.bindValue(":username", searchUsername);

    if (!query.exec()) {
        qDebug() << "Search query execution failed:" << query.lastError().text();
        QMessageBox::critical(this, "Search Error", "Unable to search the leaderboard.");
        return;
    }

    ui->leaderboardTableWidget->setRowCount(0);  // Clear the table before populating

    if (query.next()) {
        QString username = query.value(0).toString();
        int score = query.value(1).toInt();
        int userId = query.value(2).toInt();

        // Insert a new row for the matching user
        int row = ui->leaderboardTableWidget->rowCount();
        ui->leaderboardTableWidget->insertRow(row);

        ui->leaderboardTableWidget->setItem(row, 0, new QTableWidgetItem("1"));  // Rank is 1 for single search result
        ui->leaderboardTableWidget->setItem(row, 1, new QTableWidgetItem(username));
        ui->leaderboardTableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(score)));

        QMessageBox::information(this, "Search Result", "User found and displayed!");
    } else {
        QMessageBox::information(this, "Search Result", "No matching user found in the leaderboard.");
    }
}

