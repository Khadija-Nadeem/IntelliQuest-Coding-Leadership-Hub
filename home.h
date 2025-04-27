#ifndef HOME_H
#define HOME_H

#include <QDialog>

namespace Ui {
class home;
}

class home : public QDialog
{
    Q_OBJECT

public:
    explicit home(QWidget *parent = nullptr, int userId = -1);
    ~home();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_8_clicked();

    void on_startQuizButton_clicked();

private:
    Ui::home *ui;
    int currentUserId; // Store the user ID

};

#endif // HOME_H
