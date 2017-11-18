#ifndef CLIENT_H
#define CLIENT_H

#include <QtGui/QMainWindow>
#include "ui_Client.h"

class Client : public QMainWindow
{
    Q_OBJECT

public:
    Client(QWidget *parent = 0, Qt::WFlags flags = 0);
    ~Client();

private:
    Ui::ClientClass ui;
};

#endif // CLIENT_H
