#ifndef PROFILE_H
#define PROFILE_H

#include <QDialog>

namespace Ui {
class profile;
}

class profile : public QDialog
{
    Q_OBJECT

public:
    explicit profile(QWidget *parent = nullptr, int userId = -1); // Accept user ID
    ~profile();

    void loadUserData(int userId); // New method declaration
    void reloadProfileData(); // Method declaration

private slots:
    void on_pushButton_clicked();

    void on_pushButton_changePassword_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_saveChanges_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_deleteProfile_clicked();

private:
    Ui::profile *ui;
     int currentUserId; // Store the user ID for the current session
};

#endif // PROFILE_H
