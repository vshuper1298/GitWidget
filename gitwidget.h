#ifndef GITWIDGET_H
#define GITWIDGET_H

#include <QProcess>
#include <QMainWindow>

namespace Ui {
class GitWidget;
}

class GitWidget : public QMainWindow
{
    Q_OBJECT

public:
    explicit GitWidget(QWidget *parent = 0);
    ~GitWidget();

public slots:
    void setStdout();
    void setStderror();
    void command();

private:
    QProcess *process;
    Ui::GitWidget *ui;
};

#endif // GITWIDGET_H
