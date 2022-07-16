#ifndef PARSER_H
#define PARSER_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>
#include <QTimer>

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
    void getOther();
    QStringList OtherResolution();
    QStringList OtherVersion();
    QStringList OtherStorage();
private:
    Ui::Parser *ui;
    int cores = 0;
    QTimer* timer;
};
#endif // PARSER_H
