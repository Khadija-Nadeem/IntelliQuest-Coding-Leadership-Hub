#ifndef DAILYCHALLENGE_H
#define DAILYCHALLENGE_H

#include <QDialog>

namespace Ui {
class dailyChallenge;
}

class dailyChallenge : public QDialog
{
    Q_OBJECT

public:
    explicit dailyChallenge(QWidget *parent = nullptr, int userId = -1);
    ~dailyChallenge();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_clicked();


private:
    Ui::dailyChallenge *ui;
    int currentUserId;
    QSet<QDate> completedChallenges;  // Store completed challenges locally
};

#endif // DAILYCHALLENGE_H
