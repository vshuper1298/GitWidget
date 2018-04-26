#include "gitwidget.h"
#include "ui_gitwidget.h"
#include <QProcess>

GitWidget::GitWidget(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GitWidget)
{
    ui->setupUi(this);
    process = new QProcess;
    ui->textEdit->setReadOnly(true);
    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("PATH", env.value("Path") + ";D:\\Git");
    process->setProcessEnvironment(env);
        
    process->start("cmd");
    process->write("git-cmd \n");

    connect(ui->lineEdit, SIGNAL(returnPressed()), this, SLOT(command()));
    connect(process, SIGNAL(readyReadStandardOutput()), this, SLOT(setStdout()));
    connect(process, SIGNAL(readyReadStandardError()), this, SLOT(setStderror()));
}

GitWidget::~GitWidget()
{
    delete ui;
}

void GitWidget::setStdout()
{
    QString line;
    process->setReadChannel(QProcess::StandardOutput);
    while (process->canReadLine())
    {
       line = "<font color=blue>"+process->readLine()+"</font>";
       ui->textEdit->append(line);
    }
}

void GitWidget::setStderror()
{
    QString line;
    process->setReadChannel(QProcess::StandardError);
    while (process->canReadLine())
    {
       line = "<font color=red>"+process->readLine()+"</font>";
       ui->textEdit->append(line);
    }
}
void GitWidget::command()
{
    process->write((ui->lineEdit->text() + "\n").toLocal8Bit());
    ui->lineEdit->clear();
}
