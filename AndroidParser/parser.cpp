#include "parser.h"
#include "ui_parser.h"
#include <QProcess>
#include <QDebug>

Parser::Parser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Parser)
{
    ui->setupUi(this);
    connect (ui->b_SearchProc, &QPushButton::clicked, this, &Parser::Processor);
    connect (ui->b_SearchRam, &QPushButton::clicked, this, &Parser::Ram);
    ui->l_ProcName->setReadOnly(1);
    ui->l_ProcBM->setReadOnly(1);
    ui->l_ProcHardware->setReadOnly(1);
    ui->l_ProcRevision->setReadOnly(1);
    ui->l_RamTotal->setReadOnly(1);
    ui->l_RamFree->setReadOnly(1);
    ui->l_RamAvailable->setReadOnly(1);
}

Parser::~Parser()
{
    delete ui;
}

QStringList Parser::Processor()
{
    QProcess Proc;
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
    ProcessParameters(outputList);
    return outputList;
}

void Parser::ProcessParameters(QStringList outputList)
{
    ui->l_ProcHardware->setText(" Unknown");    //set default
    ui->l_ProcName->setText(" Unknown");
    foreach (QString nameProc, outputList){
        if(nameProc.contains("model name"))
            ui->l_ProcName->setText(nameProc.remove(0, nameProc.indexOf(":")+1));

        if(nameProc.contains("BogoMIPS"))
            ui->l_ProcBM->setText(nameProc.remove(0, nameProc.indexOf(":")+1));

        if(nameProc.contains("Hardware"))
            ui->l_ProcHardware->setText(nameProc.remove(0, nameProc.indexOf(":")+1));

        if(nameProc.contains("CPU revision"))
            ui->l_ProcRevision->setText(nameProc.remove(0, nameProc.indexOf(":")+1));
    }
}

QStringList Parser::Ram()
{
    QProcess Proc(this);
    QStringList parameters;
    Proc.setWorkingDirectory("D:/platform-tools");
    Proc.setProgram("powershell");
    parameters << "./adb" << "devices" << ";"
         << "./adb" << "shell" << "cat" << "/proc/meminfo" << "|" << "more";
    Proc.setArguments(parameters);
    Proc.start();
    Proc.waitForFinished();
    QString output (Proc.readAllStandardOutput());
    QStringList outputList = output.split("\n");
    RamParameters(outputList);
    return outputList;
}

void Parser::RamParameters(QStringList outputList)
{
    foreach (QString mem, outputList){
        if(mem.contains("MemTotal"))
            ui->l_RamTotal->setText(mem.remove(0, mem.indexOf(":")+8));

        if(mem.contains("MemFree"))
            ui->l_RamFree->setText(mem.remove(0, mem.indexOf(":")+11));

        if(mem.contains("MemAvailable"))
            ui->l_RamAvailable->setText(mem.remove(0, mem.indexOf(":")+4));
    }
}
