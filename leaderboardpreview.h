#ifndef LEADERBOARDPREVIEW_H
#define LEADERBOARDPREVIEW_H

#include <QDialog>

namespace Ui {
class leaderboardPreview;
}

class leaderboardPreview : public QDialog
{
    Q_OBJECT

public:
    explicit leaderboardPreview(QWidget *parent = nullptr, int userId = -1);
    ~leaderboardPreview();

private slots:
    void on_pushButton_4_clicked();
    void on_refreshButton_clicked();

    void on_searchButton_clicked();

private:
    Ui::leaderboardPreview *ui;
    int currentUserId;

    // Declare the displayLeaderboard function here
    void displayLeaderboard();
};

#endif // LEADERBOARDPREVIEW_H
