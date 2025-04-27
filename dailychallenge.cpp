#include "dailychallenge.h"
#include "ui_dailychallenge.h"
#include <QMessageBox>
#include <QDate>
#include <QSettings>
#include "dailychallengequestions.h"
#include "home.h"

dailyChallenge::dailyChallenge(QWidget *parent, int userId)
    : QDialog(parent)
    , ui(new Ui::dailyChallenge)
    , currentUserId(userId) // Initialize user ID
{
    ui->setupUi(this);
    // Load completed challenges from persistent storage (optional)
    QSettings settings("MyCompany", "MyApp");
    QStringList completedDates = settings.value("completedChallenges").toStringList();
    for (const QString &dateStr : completedDates) {
        completedChallenges.insert(QDate::fromString(dateStr));
    }
}

dailyChallenge::~dailyChallenge()
{
    delete ui;
}

void dailyChallenge::on_pushButton_4_clicked()
{
    this->hide();

    home *homewindow = new home(this, currentUserId);
    homewindow->show();
}


void dailyChallenge::on_pushButton_clicked()
{
    // Check if the user has already completed today's challenge
    QDate today = QDate::currentDate();
    if (completedChallenges.contains(today)) {
        // If completed, show a message box indicating it's already completed
        QMessageBox::information(this, "Daily Challenge", "You have already completed today's challenge!");

        // Navigate to the home page
        this->hide();  // Hide current window
        home *homewindow = new home(this, currentUserId);
        homewindow->show();  // Show the home page
    } else {
        // If not completed, show the challenge questions
        this->hide();
        dailychallengequestions *questionsWindow = new dailychallengequestions(this, currentUserId);
        questionsWindow->show();
    }
}
