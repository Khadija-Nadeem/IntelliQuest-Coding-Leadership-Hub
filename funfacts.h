#ifndef FUNFACTS_H
#define FUNFACTS_H

#include <QDialog>

#include <QString>
#include <vector>

namespace Ui {
class funFacts;
}

class funFacts : public QDialog
{
    Q_OBJECT

public:
    explicit funFacts(QWidget *parent = nullptr, int userId = -1);
    ~funFacts();

private slots:
    void on_pushButton_4_clicked();
    void shuffleFacts();
    void on_nextFactButton_clicked();

private:
    Ui::funFacts *ui;
    int currentUserId;

    // List of fun facts to display
    std::vector<QString> facts = {
        "HTML is like the skeleton of a website—without it, everything would just be a pile of code!",
        "CSS is like the magic wand of websites. It makes everything look dazzling, but try to wave it without causing a mini disaster!"
        "JavaScript was created in 10 days, but it feels like it was written in 10 years with all those bugs!",
        "Python is named after Monty Python, which means every time you run a Python script, you're one step closer to becoming a comedian.",
        "Java was originally called 'Oak,' but it was too busy being the Java we know and love to care about the name!",
        "C was developed by Dennis Ritchie in the '70s, and it’s still around, proving that even old school can be cool!",
        "Ruby is like the diamond of programming languages. It's shiny, precious, and everyone wants a piece of it!",
        "PHP started as a tool for tracking visitors to a website, but now it’s like the Swiss Army knife of the internet. Who knew?",
        "Swift came to replace Objective-C like a superhero. Faster, sleeker, and with fewer existential crises!",
        "Go was made by Google to make coding faster. They should've called it 'Speedy Gonzales'!",
        "Rust was designed to be fast and safe, like your mom telling you not to touch the hot stove—except it actually listens!",
        "Kotlin was designed to be more fun than Java. If Java were a cup of coffee, Kotlin would be a double shot of espresso!",
        "SQL is the secret agent of databases. It’s been around forever, still looking cool while everyone else panics.",
        "TypeScript is like JavaScript, but with a seatbelt on—making sure things don't crash as much!",
        "Assembly language: The closest thing to talking to computers directly. It’s like telling your computer, 'Hey, do this!' and hoping it listens.",
        "Ada was named after Ada Lovelace, the first computer programmer. If she were alive today, she’d probably be coding in space!",
        "Perl was originally created to manipulate text, but now it manipulates the web like a magician with a keyboard!",
        "Ruby on Rails makes web development feel like magic. One minute you're coding, the next minute you have a website. Presto!",
        "Lisp: The language that never lets go of its parentheses. It’s like trying to find your glasses, only to realize they were on your face the whole time.",
        "The first computer virus was called Brain, written in Assembly. It was less of a virus and more of a software headache!",
        "Eiffel was named after the Eiffel Tower, so it’s strong, sturdy, and a bit taller than most languages. But try not to climb it!",
        "Python's logo is a snake because Guido van Rossum wanted it to be cool. And who wouldn’t want a programming language with a reptilian mascot?",
        "Scratch makes programming so easy, even your dog could do it. Okay, maybe not your dog, but your little brother could!",
        "Fortran is still alive and kicking in the world of scientific computing. It's like the grandma of programming languages—still going strong!",
        "Haskell is for people who love logic. It’s so pure, you might start questioning everything in life—like whether you really need that second cup of coffee.",
        "The 'Hello World' program in C is the gateway drug to the programming world. Once you print that, there’s no turning back!"
    };


    std::vector<QString> shuffledFacts; // Shuffled version of the facts
    size_t currentFactIndex = 0;        // Current fact index

};

#endif // FUNFACTS_H
