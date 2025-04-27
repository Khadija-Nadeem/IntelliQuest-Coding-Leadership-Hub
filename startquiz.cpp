#include "startquiz.h"
#include "ui_startquiz.h"
#include "home.h"
#include "quiz.h"
#include "QMessageBox"

startQuiz::startQuiz(QWidget *parent, int userId)
    : QDialog(parent)
    , ui(new Ui::startQuiz)
    , currentUserId(userId) // Initialize user ID
{
    ui->setupUi(this);
}

startQuiz::~startQuiz()
{
    delete ui;
}

void startQuiz::on_pushButton_4_clicked()
{
    this->hide();

    home *homewindow = new home(this, currentUserId);
    homewindow->show();
}


void startQuiz::on_pushButton_clicked()
{
    // Get the selected category from the combo box
    QString selectedCategory = ui->categoryComboBox->currentText();

    // Get the selected difficulty level from the radio buttons
    QString selectedLevel;
    if (ui->radioButtonEasy->isChecked()) {
        selectedLevel = "Easy";
    } else if (ui->radioButtonMedium->isChecked()) {
        selectedLevel = "Medium";
    } else if (ui->radioButtonHard->isChecked()) {
        selectedLevel = "Hard";
    }

    // Check if both category and level are selected
    if (selectedCategory.isEmpty() || selectedLevel.isEmpty()) {
        // Show a message if the user has not selected both category and level
        QMessageBox::warning(this, "Input Error", "Please select both category and difficulty level.");
        return;
    }

    // Pass selected values to the quiz page
    quiz *quizwindow = new quiz(this, selectedCategory, selectedLevel, currentUserId);
    quizwindow->show();
     qDebug() << "Quiz window should be shown now.";
}

