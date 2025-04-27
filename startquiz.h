#ifndef STARTQUIZ_H
#define STARTQUIZ_H

#include <QDialog>

namespace Ui {
class startQuiz;
}

class startQuiz : public QDialog
{
    Q_OBJECT

public:
    explicit startQuiz(QWidget *parent = nullptr, int userId = -1);
    ~startQuiz();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();

private:
    Ui::startQuiz *ui;
    int currentUserId;
};

#endif // STARTQUIZ_H
