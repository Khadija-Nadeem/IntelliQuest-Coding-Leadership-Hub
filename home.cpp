#include "home.h"
#include "ui_home.h"
#include <QMessageBox>
#include "start.h"
#include "profile.h"
#include "howtoplay.h"
#include "leaderboardpreview.h"
#include "funfacts.h"
#include "dailychallenge.h"
#include "startquiz.h"

home::home(QWidget *parent, int userId)
    : QDialog(parent)
    , ui(new Ui::home)
    , currentUserId(userId) // Initialize user ID
{
    ui->setupUi(this);

    // Set the user ID on the label
    ui->userIdLabel->setText("User ID: " + QString::number(currentUserId));
}

home::~home()
{
    delete ui;
}

void home::on_pushButton_4_clicked()
{
    this->hide();
    profile *profileWindow = new profile(this, currentUserId);
    profileWindow->reloadProfileData();  // Reload user data when navigating back to profile
    profileWindow->show();

}


void home::on_pushButton_5_clicked()
{
    this->hide();

    howToPlay *howToPlaywindow= new howToPlay(this, currentUserId);
    howToPlaywindow->show();
}


void home::on_pushButton_2_clicked()
{
    this->hide();

    leaderboardPreview *leaderboardPreviewwindow= new leaderboardPreview(this, currentUserId);
    leaderboardPreviewwindow->show();
}


void home::on_pushButton_6_clicked()
{
    this->hide();

    funFacts *funFactswindow= new funFacts(this, currentUserId);
    funFactswindow->show();
}


void home::on_pushButton_3_clicked()
{
    this->hide();

    dailyChallenge *dailyChallengewindow= new dailyChallenge(this, currentUserId);
    dailyChallengewindow->show();
}


void home::on_pushButton_8_clicked()
{
    // Create a message box for confirmation
    QMessageBox::StandardButton reply = QMessageBox::question(this, "Logout", "Are you sure you want to log out?",
                                                              QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        // If Yes is clicked, go to the Get Started page
        this->hide();

        start *startwindow= new start(this);
        startwindow->show();
    } else {
        // If No is clicked, stay on the current page
        // No action is needed
    }
}


void home::on_startQuizButton_clicked()
{
    this->hide();

    startQuiz *startQuizwindow= new startQuiz(this, currentUserId);
    startQuizwindow->show();
}

