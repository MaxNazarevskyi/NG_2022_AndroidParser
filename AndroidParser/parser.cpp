#include "parser.h"
#include "ui_parser.h"
#include <QProcess>
#include <QDebug>

Parser::Parser(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Parser)
{
    ui->setupUi(this);
    timer = new QTimer;
    connect (timer, &QTimer::timeout, this, &Parser::Ram);
    connect (ui->b_Search, &QPushButton::clicked, this, &Parser::Processor);
    connect (ui->b_Search, &QPushButton::clicked, this, &Parser::Ram);
    connect (ui->b_Search, &QPushButton::clicked, this, &Parser::getOther);
    timer->start(1000);
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
    cores = 0;
    foreach (QString nameProc, outputList){
        if(nameProc.contains("processor")){
            cores++;
            ui->l_ProcCores->setText(" " + QString::number(cores));
        }
        if(nameProc.contains("model name"))
            ui->l_ProcName->setText(nameProc.remove(0, nameProc.indexOf(":")+1));
        if(nameProc.contains("BogoMIPS"))
            ui->l_ProcBM->setText(nameProc.remove(0, nameProc.indexOf(":")+1));
        if(nameProc.contains("Hardware"))
            ui->l_ProcHardware->setText(nameProc.remove(0, nameProc.indexOf(":")+1));
        if(nameProc.contains("CPU revision"))
            ui->l_ProcRevision->setText(nameProc.remove(0, nameProc.indexOf(":")+1));
        if(nameProc.contains("CPU architecture"))
            ui->l_ProcArch->setText(nameProc.remove(0, nameProc.indexOf(":")+1));
        if(nameProc.contains("CPU variant"))
            ui->l_ProcVariant->setText(nameProc.remove(0, nameProc.indexOf(":")+1));
        if(nameProc.contains("CPU part"))
            ui->l_ProcPart->setText(nameProc.remove(0, nameProc.indexOf(":")+1));
        if(nameProc.contains("CPU implementer"))
            ui->l_ProcImp->setText(nameProc.remove(0, nameProc.indexOf(":")+1));
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
    QLineEdit* line = nullptr;
    foreach (QString mem, outputList){
        if(mem.contains("MemTotal"))
            line = ui->l_RamTotal;
        else if(mem.contains("MemFree"))
            line = ui->l_RamFree;
        else if(mem.contains("MemAvailable"))
            line = ui->l_RamAvailable;
        else if(mem.contains("Buffers"))
            line = ui->l_RamBuffers;
        else if(mem.indexOf("Cached:")== 0)
            line = ui->l_RamCached;
        else if(mem.contains("SwapCached:"))
            line = ui->l_RamSwapC;
        else if(mem.contains("Active:"))
            line = ui->l_RamActive;
        else if(mem.contains("Inactive:"))
            line = ui->l_RamInactive;
        else if(mem.contains("Unevictable"))
            line = ui->l_RamUnevictable;
        else if(mem.contains("Mlocked"))
            line = ui->l_RamMlocked;
        else if(mem.contains("AnonPages"))
            line = ui->l_RamAnon;
        else if(mem.contains("SwapTotal"))
            line = ui->l_RamSwapT;
        else if(mem.contains("SwapFree"))
            line = ui->l_RamSwapF;
        else if(mem.contains("Shmem"))
            line = ui->l_RamShmem;
        else if(mem.contains("Slab"))
            line = ui->l_RamSlab;
        else if(mem.contains("SReclaimable"))
            line = ui->l_RamSRec;
        else if(mem.contains("SUnreclaim"))
            line = ui->l_RamSUnreclaim;
        else if(mem.contains("Mapped"))
            line = ui->l_RamMapped;
        else if(mem.contains("KernelStack"))
            line = ui->l_RamKernelS;
        else if(mem.contains("PageTables"))
            line = ui->l_RamPageT;
        else continue;
        line->setText(mem.remove(0, mem.indexOf(":")+1).remove(0,mem.count(" ")-1));
    }
}

QStringList Parser::OtherResolution()
{
    QProcess Proc(this);
    QStringList parameters;
    Proc.setWorkingDirectory("D:/platform-tools");
    Proc.setProgram("powershell");
    parameters << "./adb" << "devices" << ";"
         << "./adb" << "shell" << "wm" << "size";
    Proc.setArguments(parameters);
    Proc.start();
    Proc.waitForFinished();
    QString output (Proc.readAllStandardOutput());
    QStringList outputList = output.split("\n");
    return outputList;
}

QStringList Parser::OtherVersion()
{
    QProcess Proc(this);
    QStringList parameters;
    Proc.setWorkingDirectory("D:/platform-tools");
    Proc.setProgram("powershell");
    parameters << "./adb" << "devices" << ";"
         << "./adb" << "shell" << "cat" << "/proc/version";
    Proc.setArguments(parameters);
    Proc.start();
    Proc.waitForFinished();
    QString output (Proc.readAllStandardOutput());
    QStringList outputList = output.split("\n");
    return outputList;
}

void Parser::getOther()
{
    QStringList params = OtherVersion()+OtherResolution();
    foreach (QString other, params){
        if(other.contains("Physical size"))
            ui->l_OtherRes->setText(other.remove(0, other.indexOf(":")+1));
        if(other.contains("Linux version"))
            ui->l_OtherVersion->setText(other.left(other.indexOf("+")).remove(0,13));
    }
}
