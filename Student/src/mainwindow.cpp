#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_student(0)
{
    ui->setupUi(this);
    m_student = new Student(this);

    connect(ui->sendLetterButton, SIGNAL(clicked()), this, SLOT(sendLetter()));
    connect(m_student, SIGNAL(parcelRecived(QString)), ui->answerText, SLOT(setText(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_student;
}

void MainWindow::receiveAnswer(QString answer)
{
    ui->answerText->setText(answer);
}

void MainWindow::sendLetter()
{
    QString letterText = ui->letterText->document()->toPlainText();
    m_student->sendLetterToParents(letterText);
}
