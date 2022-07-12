#include "parser.h"
#include "ui_parser.h"
#include <QProcess>
#include <QDebug>

Parser::Parser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Parser)
{
    ui->setupUi(this);
    connect (ui->b_Search, &QPushButton::clicked, this, &Parser::addedStorage);
    connect (ui->l_Proc, &QLineEdit::textChanged, this, &Parser::addedStorage);
}

Parser::~Parser()
{
    delete ui;
}

void Parser::addedStorage()
{
    QProcess Proc(this);
    QStringList parameters;
    Proc.setWorkingDirectory("D:/platform-tools");
    Proc.setProgram("powershell");
    parameters << "./adb" << "devices" << ";"
         << "./adb" << "shell" << "cat" << "/proc/cpuinfo" << "|" << "more";
    Proc.setArguments(parameters);
    Proc.start();
    Proc.waitForFinished();
    QString output (Proc.readAllStandardOutput());
    QStringList outputList = output.split("\n");
    foreach (QString proc, outputList)
        if(proc.contains("Hardware")){
            ui->l_Proc->setText(proc);
            break;
        }
        else
            ui->l_Proc->setText("Unknown");
}
