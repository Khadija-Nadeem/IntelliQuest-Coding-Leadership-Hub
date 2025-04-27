#ifndef HOWTOPLAY_H
#define HOWTOPLAY_H

#include <QDialog>

namespace Ui {
class howToPlay;
}

class howToPlay : public QDialog
{
    Q_OBJECT

public:
    explicit howToPlay(QWidget *parent = nullptr, int userId = -1);
    ~howToPlay();

private slots:
    void on_pushButton_4_clicked();

private:
    Ui::howToPlay *ui;
    int currentUserId;
};

#endif // HOWTOPLAY_H
