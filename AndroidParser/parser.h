#ifndef PARSER_H
#define PARSER_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Parser; }
QT_END_NAMESPACE

class Parser : public QMainWindow
{
    Q_OBJECT

public:
    Parser(QWidget *parent = nullptr);
    ~Parser();
private slots:
    QStringList Processor();
    void ProcessParameters(QStringList outputList);
    QStringList Ram();
    void RamParameters(QStringList outputList);
    QStringList Other();
    void OtherParameters(QStringList outputList);


private:
    Ui::Parser *ui;
    int cores = 0;
};
#endif // PARSER_H
