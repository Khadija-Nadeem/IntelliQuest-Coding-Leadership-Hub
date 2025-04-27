#ifndef DAILYCHALLENGEQUESTIONS_H
#define DAILYCHALLENGEQUESTIONS_H

#include <QDialog>
#include <QTimer>
#include <QHash>
#include <QStringList>
#include <QSet>
#include <QDate>

namespace Ui {
class dailychallengequestions;
}

class dailychallengequestions : public QDialog
{
    Q_OBJECT

public:
    explicit dailychallengequestions(QWidget *parent = nullptr, int userId = -1);
    ~dailychallengequestions();

private slots:
    void updateTimer();               // Update progress bar and handle timeout
    void on_nextsubmitbtn_clicked();   // Handle next/submit button click

private:
    Ui::dailychallengequestions *ui;

    int currentQuestionIndex;
    int correctAnswerCount;
    int totalScore;
    QString selectedAnswer;

    QTimer *timer;                    // Timer for question countdown
    int timeLeft;                     // Time left in seconds
    bool answerCorrect;               // Declare answerCorrect here
    bool quizFinished;  // Add this member variable

    QHash<QDate, QStringList> dailyChallenges;
    QHash<QDate, QStringList> correctAnswers;
    QSet<QDate> completedChallenges;

    int currentUserId;                // Declare currentUserId here

    void updateChallenge();
    void setupQuestionUI(const QString &question, const QStringList &options, int questionIndex);
    void moveToNextQuestion();
    void checkAnswer(const QString &selectedOption, int questionIndex);
    void finishQuiz();
    void loadChallenges();
    void saveScoreToLeaderboard(int userId, int score);  // Declare the saveScoreToLeaderboard function
};

#endif // DAILYCHALLENGEQUESTIONS_H
