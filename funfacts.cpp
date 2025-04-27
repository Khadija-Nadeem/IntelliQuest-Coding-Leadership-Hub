#include "funfacts.h"
#include "ui_funfacts.h"

#include "home.h"

#include <algorithm> // For std::shuffle
#include <random>    // For random_device and mt19937

funFacts::funFacts(QWidget *parent, int userId)
    : QDialog(parent)
    , ui(new Ui::funFacts)
    , currentUserId(userId) // Initialize user ID
{
    ui->setupUi(this);

    // Shuffle facts when the dialog is initialized
    shuffleFacts();

    // Display the first fact
    ui->factsLabel->setText(shuffledFacts[currentFactIndex]);

    // Enable word wrapping for the facts label
    ui->factsLabel->setWordWrap(true);
}

funFacts::~funFacts()
{
    delete ui;
}


void funFacts::shuffleFacts() {
    // Copy the facts vector to the shuffledFacts vector
    shuffledFacts = facts;

    // Initialize a random number generator
    std::random_device rd;   // Seed generator
    std::mt19937 g(rd());    // Mersenne Twister generator

    // Shuffle the vector
    std::shuffle(shuffledFacts.begin(), shuffledFacts.end(), g);

    // Reset the index to start from the first fact
    currentFactIndex = 0;
}

void funFacts::on_nextFactButton_clicked()
{
    if (currentFactIndex >= shuffledFacts.size()) {
         // Reshuffle the facts if all have been displayed
        shuffleFacts();
    }

    ui->factsLabel->setText(shuffledFacts[currentFactIndex]); // Update the label with the next fact
    currentFactIndex++;
}


void funFacts::on_pushButton_4_clicked()
{
    this->hide();

    home *homewindow = new home(this, currentUserId);
    homewindow->show();
}

