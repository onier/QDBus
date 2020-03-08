#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "student.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void receiveAnswer(QString answer);

private slots:
    void sendLetter();

private:
    Ui::MainWindow *ui;
    Student *m_student;
};

#endif // MAINWINDOW_H
