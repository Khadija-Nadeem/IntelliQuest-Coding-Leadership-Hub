#include "dailychallengequestions.h"
#include "ui_dailychallengequestions.h"
#include <QMessageBox>
#include <QDate>
#include <QSettings>
#include "home.h"
#include "databasemanager.h"

dailychallengequestions::dailychallengequestions(QWidget *parent, int userId)
    : QDialog(parent)
    , ui(new Ui::dailychallengequestions)
    , currentQuestionIndex(-1)
    , correctAnswerCount(0)
    , totalScore(0)
    , timer(new QTimer(this))  // Create the timer
    , timeLeft(7)              // Set initial time for each question
    , currentUserId(userId) // Initialize user ID
{
    ui->setupUi(this);

    ui->lcdNumber->display(0); // Initialize the QLCDNumber to 0

    // Connect timer to updateTimer slot
    connect(timer, &QTimer::timeout, this, &dailychallengequestions::updateTimer);

    // Load challenges and update today's challenge
    loadChallenges();
    updateChallenge();
}

dailychallengequestions::~dailychallengequestions() {
    delete ui;
}

void dailychallengequestions::updateChallenge() {
    QDate today = QDate::currentDate();

    // Check if the user has already completed today's quiz
    if (completedChallenges.contains(today)) {
        QMessageBox::information(this, "Daily Challenge", "You have already completed today's challenge!");
        this->reject();  // Close the daily challenge dialog
        return;
    }

    // Reset variables for a new quiz
    correctAnswerCount = 0; // Ensure it starts from 0
    totalScore = 0;
    currentQuestionIndex = 0;
    selectedAnswer = ""; // Reset selected answer

    // Display the initial LCD value (0)
    ui->lcdNumber->display(0); // Ensure LCD shows 0 initially

    // Check if there are questions for today
    if (dailyChallenges.contains(today)) {
        QStringList questionData = dailyChallenges[today];

        if (!questionData.isEmpty()) {
            // Display the first question
            QStringList questionParts = questionData[currentQuestionIndex].split('|');
            if (questionParts.size() >= 5) { // Ensure valid format
                setupQuestionUI(
                    questionParts[0],            // First question
                    questionParts.mid(1, 4),     // First 4 options
                    currentQuestionIndex         // First question index (0)
                    );
            } else {
                ui->challengeLabel->setText("Error: Invalid question format.");
            }
        } else {
            ui->challengeLabel->setText("No questions available for today.");
        }
    } else {
        ui->challengeLabel->setText("No challenge available for today.");
    }
}

void dailychallengequestions::setupQuestionUI(const QString &question, const QStringList &options, int questionIndex) {

    // Uncheck all radio buttons before displaying the next question
    ui->option1->setAutoExclusive(false);
    ui->option2->setAutoExclusive(false);
    ui->option3->setAutoExclusive(false);
    ui->option4->setAutoExclusive(false);

    ui->option1->setChecked(false);
    ui->option2->setChecked(false);
    ui->option3->setChecked(false);
    ui->option4->setChecked(false);

    // Restore auto-exclusive mode after resetting
    ui->option1->setAutoExclusive(true);
    ui->option2->setAutoExclusive(true);
    ui->option3->setAutoExclusive(true);
    ui->option4->setAutoExclusive(true);

    // Set question and options
    ui->challengeLabel->setText(question);
    ui->option1->setText(options[0]);
    ui->option2->setText(options[1]);
    ui->option3->setText(options[2]);
    ui->option4->setText(options[3]);

    // Reset timer and progress bar
    timeLeft = 7; // Reset time for the question
    ui->progressBar->setMaximum(7 * 10); // Assuming updates every 100 ms
    ui->progressBar->setValue(0);

    // Start the timer
    timer->start(1000); // Update every 1 second

    // Connect radio buttons to store the selected answer
    connect(ui->option1, &QRadioButton::clicked, this, [=]() { selectedAnswer = options[0]; });
    connect(ui->option2, &QRadioButton::clicked, this, [=]() { selectedAnswer = options[1]; });
    connect(ui->option3, &QRadioButton::clicked, this, [=]() { selectedAnswer = options[2]; });
    connect(ui->option4, &QRadioButton::clicked, this, [=]() { selectedAnswer = options[3]; });
}


void dailychallengequestions::updateTimer() {
    // Decrease time left and update progress bar
    timeLeft--;
    ui->progressBar->setValue((7 - timeLeft) * 10); // Progress bar in steps of 100 ms

    // Check if time is up and quiz is not finished
    if (timeLeft <= 0 && !quizFinished) {
        timer->stop();
        QMessageBox::information(this, "Time Up!", "Time is up for this question.");
        // Check the answer when time is up
        checkAnswer(selectedAnswer, currentQuestionIndex); // Check the last selected answer
        moveToNextQuestion();
    }
}

void dailychallengequestions::moveToNextQuestion() {
    timer->stop(); // Stop the timer for the current question

    QDate today = QDate::currentDate();
    QStringList currentQuestions = dailyChallenges[today];

    currentQuestionIndex++;
    if (currentQuestionIndex >= currentQuestions.size()) {
        finishQuiz(); // Finish the quiz if all questions have been answered
    } else {
        QStringList questionParts = currentQuestions[currentQuestionIndex].split('|');
        setupQuestionUI(questionParts[0], questionParts.mid(1, 4), currentQuestionIndex);
    }
}


void dailychallengequestions::checkAnswer(const QString &selectedOption, int questionIndex) {
    QDate today = QDate::currentDate();
    QStringList correctAnswersToday = correctAnswers[today];

    bool isCorrect = (selectedOption == correctAnswersToday[questionIndex]);

    // If the answer is correct, increment the correctAnswerCount
    if (isCorrect) {
        correctAnswerCount++; // Increment by 1 for correct answer only
        totalScore += 50;     // Add points for correct answer
    }
}

void dailychallengequestions::finishQuiz() {
    if (quizFinished) return; // Prevent multiple calls

    timer->stop(); // Stop the timer when the quiz is completed
    quizFinished = true;

    QDate today = QDate::currentDate();
    completedChallenges.insert(today);

    QSettings settings("MyCompany", "MyApp");
    QStringList completedDates = settings.value("completedChallenges").toStringList();
    completedDates.append(today.toString());
    settings.setValue("completedChallenges", completedDates);

    // Prepare the message to display the total score
    QString message = QString("Quiz Completed!\nYour total score is: %1").arg(totalScore);

    // Save the score in the leaderboard table
    saveScoreToLeaderboard(currentUserId, totalScore);

    // Show the message box with the total score
    QMessageBox::information(this, "Quiz Completed", message);

    this->hide();

    if (currentUserId > 0) {
        home *homewindow = new home(this, currentUserId);
        homewindow->show();
    } else {
        qDebug() << "Error: Invalid User ID";
    }
}

void dailychallengequestions::loadChallenges() {
    // Define sets of questions and answers
    QStringList set1Questions;
    set1Questions << "What does 'OOP' stand for in programming?|Object-Oriented Programming|Object-Oriented Process|Optimized Object Programming|Operational Object Programming"
                  << "Which keyword is used to create an object in Java?|new|create|object|instance"
                  << "What is Encapsulation?|Hiding internal details|Multiple inheritance|Runtime polymorphism|None of the above"
                  << "Which is not an OOP principle?|Encapsulation|Abstraction|Polymorphism|Functional Programming"
                  << "Which of the following supports OOP?|C++|C|COBOL|Assembly";

    QStringList set2Questions;
    set2Questions << "What does 'Polymorphism' mean in OOP?|Ability to take multiple forms|Inheritance of methods|Compile-time binding|Static classes"
                  << "What is the default access modifier in a C++ class?|private|public|protected|static"
                  << "Which feature of OOP is demonstrated by method overloading?|Polymorphism|Inheritance|Encapsulation|None of the above"
                  << "What is the main purpose of a constructor?|Initialize an object|Destroy an object|Define a method|None of the above"
                  << "Which of these is not a programming paradigm?|Procedural|OOP|Declarative|Static";

    QStringList set3Questions;
    set3Questions << "Which is a non-primitive data type in C++?|Class|Int|Float|Char"
                  << "What is a destructor used for in OOP?|Release resources|Initialize an object|Overload operators|None of the above"
                  << "Which language supports multiple inheritance?|C++|Java|Python|All of the above"
                  << "What is the main purpose of 'inheritance' in OOP?|Reuse code|Encapsulation|Binding|None of the above"
                  << "What is a static member in OOP?|Shared across all instances|Unique to each instance|Constant value|None of the above";

    QStringList set4Questions;
    set4Questions << "What is a 'pointer' in programming?|Variable storing memory address|Primitive data type|A constant|None of the above"
                  << "What does the keyword 'virtual' indicate in C++?|Dynamic binding|Compile-time polymorphism|Static allocation|None of the above"
                  << "Which is a linear data structure?|Stack|Tree|Graph|Hash Table"
                  << "What is a friend function in C++?|Access private data|Overload operators|Define an interface|None of the above"
                  << "What is the role of a pure virtual function?|Define an abstract class|Provide default behavior|Allocate memory|None of the above";

    // Assign initial sets of questions and answers for 14 consecutive days starting from today
    QDate startDate = QDate::currentDate(); // Start from today

    for (int i = 0; i < 14; ++i) {
        QDate day = startDate.addDays(i); // Add i days to today

        QStringList questions = (i % 4 == 0) ? set1Questions
                                : (i % 4 == 1) ? set2Questions
                                : (i % 4 == 2) ? set3Questions
                                               : set4Questions;

        QStringList answers = (i % 4 == 0) ? QStringList{"Object-Oriented Programming", "new", "Hiding internal details", "Functional Programming", "C++"}
                              : (i % 4 == 1) ? QStringList{"Ability to take multiple forms", "private", "Polymorphism", "Initialize an object", "Static"}
                              : (i % 4 == 2) ? QStringList{"Class", "Release resources", "C++", "Reuse code", "Shared across all instances"}
                                             : QStringList{"Variable storing memory address", "Dynamic binding", "Stack", "Access private data", "Define an abstract class"};

        dailyChallenges[day] = questions;
        correctAnswers[day] = answers;
    }
}


void dailychallengequestions::saveScoreToLeaderboard(int userId, int score) {
    // Use DatabaseManager to get the active database connection
    DatabaseManager dbManager;
    if (!dbManager.connectToDatabase()) {
        qDebug() << "Failed to connect to database.";
        return;
    }

    QSqlQuery query(DatabaseManager::getDatabase());

    // Check if user already exists in leaderboard
    query.prepare("SELECT COUNT(*) FROM leaderboard WHERE user_id = :user_id");
    query.bindValue(":user_id", userId);

    if (!query.exec()) {
        qDebug() << "Failed to check user existence:" << query.lastError().text();
        return;
    }

    query.next();
    int count = query.value(0).toInt();
    qDebug() << "User  exists count:" << count;

    if (count > 0) {
        // Prepare the query to fetch the current score of the user
        query.prepare("SELECT score FROM leaderboard WHERE user_id = :user_id");
        query.bindValue(":user_id", userId);

        // Execute the query to retrieve the current score
        if (query.exec() && query.next()) {
            // Get the current score from the query result
            int currentScore = query.value(0).toInt(); // Use index 0 instead of "score"

            // Add the new score to the current score
            int newScore = currentScore + score;

            // Now, prepare the query to update the leaderboard with the new score
            query.prepare("UPDATE leaderboard SET score = :score WHERE user_id = :user_id");
            query.bindValue(":score", newScore);  // New total score
            query.bindValue(":user_id", userId);  // User ID

            // Execute the query to update the score
            if (query.exec()) {
                qDebug() << "Score updated successfully. User ID:" << userId << "New Score:" << newScore;
            } else {
                // Error handling, e.g., log or display an error message
                qDebug() << "Failed to update score:" << query.lastError().text();
            }
        } else {
            // Error handling if the user was not found or there was an issue fetching the current score
            qDebug() << "Failed to fetch current score for User ID:" << userId << query.lastError().text();
        }

    } else {
        // User doesn't exist; insert a new record
        query.prepare("INSERT INTO leaderboard (user_id, score) VALUES (:user_id, :score)");
        query.bindValue(":user_id", userId);
        query.bindValue(":score", score);

        if (!query.exec()) {
            qDebug() << "Failed to save new score:" << query.lastError().text();
        } else {
            qDebug() << "New score saved successfully. User ID:" << userId << "Score:" << score;
        }
    }
}


void dailychallengequestions::on_nextsubmitbtn_clicked()
{
    checkAnswer(selectedAnswer, currentQuestionIndex); // Check the last selected answer

    // Update the LCD display
    ui->lcdNumber->display(correctAnswerCount);

    // Move to the next question or finish the quiz if all questions are done
    moveToNextQuestion();
}

