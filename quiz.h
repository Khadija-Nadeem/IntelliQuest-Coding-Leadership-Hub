#ifndef QUIZ_H
#define QUIZ_H

#include <QDialog>
#include <vector>

#include <QLCDNumber> // Include QLCDNumber

#include <QProgressBar>
#include <QTimer>

namespace Ui {
class quiz;
}

// Define the Question struct
struct Question {
    QString question;
    QString options[4];
    int correctAnswer;
    QString category;
    QString level;
};

class quiz : public QDialog
{
    Q_OBJECT

public:
    // Constructor with category and level parameters
    explicit quiz(QWidget *parent = nullptr, const QString& category = "", const QString& level = "", int userId = -1);
    //Declaration of shuffleOptions
    void shuffleOptions(Question& question);  // Declaration of shuffleOptions

    ~quiz();

protected:
    void closeEvent(QCloseEvent* event) override;



private slots:
    void on_pushButton_2_clicked();
    void updateProgress();  // Slot to update the progress bar
    void onTimeUp();  // Slot to handle time up event


private:
    Ui::quiz *ui;

    std::vector<Question> questions;  // Store questions
    int currentQuestionIndex;         // To keep track of current question
    int score;                        // To store score

    int elapsedTime;  // Elapsed time in milliseconds

    QString category; // Selected category
    QString level;    // Selected difficulty level

     int currentUserId;  // Declare currentUserId

    // Function to load the quiz questions
    void loadQuiz(const QString& category, const QString& level);

    // Function to display the current question
    void displayQuestion();

    // Slot for handling submit button click
    void on_submitButton_clicked();

    // Function to get the score for the current level
    int getScoreForLevel();

    // Function to get the questions based on category and level
    std::vector<Question> getQuestionsForCategoryAndLevel(const QString& category, const QString& level);

    // Function to save score to leaderboard
    void saveScoreToLeaderboard(int userId, int score);  // Declare function

    QProgressBar *progressBar;  // Progress bar widget
    QTimer *timer;  // Timer to update progress

    static bool quizCompleted;  // Declare quizCompleted as a static member

};

#endif // QUIZ_H
