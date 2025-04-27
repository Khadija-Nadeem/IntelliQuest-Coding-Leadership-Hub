#include "howtoplay.h"
#include "ui_howtoplay.h"
#include "home.h"

howToPlay::howToPlay(QWidget *parent, int userId)
    : QDialog(parent)
    , ui(new Ui::howToPlay)
    , currentUserId(userId) // Initialize user ID
{
    ui->setupUi(this);
}

howToPlay::~howToPlay()
{
    delete ui;
}

void howToPlay::on_pushButton_4_clicked()
{
    this->hide();

    home *homewindow= new home(this, currentUserId);
    homewindow->show();
}

