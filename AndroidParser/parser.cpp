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
    connect (ui->b_SearchOther, &QPushButton::clicked, this, &Parser::OtherResolution);
    ui->l_ProcName->setReadOnly(1);
    ui->l_ProcBM->setReadOnly(1);
    ui->l_ProcHardware->setReadOnly(1);
    ui->l_ProcRevision->setReadOnly(1);
    ui->l_ProcCores->setReadOnly(1);
    ui->l_ProcArch->setReadOnly(1);
    ui->l_ProcVariant->setReadOnly(1);
    ui->l_ProcPart->setReadOnly(1);
    ui->l_ProcImp->setReadOnly(1);
    ui->l_RamTotal->setReadOnly(1);
    ui->l_RamFree->setReadOnly(1);
    ui->l_RamAvailable->setReadOnly(1);
    ui->l_RamBuffers->setReadOnly(1);
    ui->l_RamCached->setReadOnly(1);
    ui->l_RamActive->setReadOnly(1);
    ui->l_RamInactive->setReadOnly(1);
    ui->l_RamUnevictable->setReadOnly(1);
    ui->l_RamMlocked->setReadOnly(1);
    ui->l_RamAnon->setReadOnly(1);
    ui->l_RamSwapT->setReadOnly(1);
    ui->l_RamSwapF->setReadOnly(1);
    ui->l_RamSwapC->setReadOnly(1);
    ui->l_RamSlab->setReadOnly(1);
    ui->l_RamSRec->setReadOnly(1);
    ui->l_RamSUnreclaim->setReadOnly(1);
    ui->l_RamMapped->setReadOnly(1);
    ui->l_RamKernelS->setReadOnly(1);
    ui->l_RamPageT->setReadOnly(1);
    ui->l_OtherRes->setReadOnly(1);
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
    foreach (QString mem, outputList){
        if(mem.contains("MemTotal"))
            ui->l_RamTotal->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("MemFree"))
            ui->l_RamFree->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("MemAvailable"))
            ui->l_RamAvailable->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("Buffers"))
            ui->l_RamBuffers->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("Cached"))
            ui->l_RamCached->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("Active:"))
            ui->l_RamActive->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("Inactive:"))
            ui->l_RamInactive->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("Unevictable"))
            ui->l_RamUnevictable->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("Mlocked"))
            ui->l_RamMlocked->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("AnonPages"))
            ui->l_RamAnon->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("SwapTotal"))
            ui->l_RamSwapT->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("SwapFree"))
            ui->l_RamSwapF->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("SwapCached"))
            ui->l_RamSwapC->setText(mem.remove(0, mem.indexOf(":")+1)); //unwork(
        if(mem.contains("Slab"))
            ui->l_RamSlab->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("SReclaimable"))
            ui->l_RamSRec->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("SUnreclaim"))
            ui->l_RamSUnreclaim->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("Mapped"))
            ui->l_RamMapped->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("KernelStack"))
            ui->l_RamKernelS->setText(mem.remove(0, mem.indexOf(":")+1));
        if(mem.contains("PageTables"))
            ui->l_RamPageT->setText(mem.remove(0, mem.indexOf(":")+1));
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
    OtherParameters(outputList);
    return outputList;
}

void Parser::OtherParameters(QStringList outputList)
{
    foreach (QString res, outputList){
        if(res.contains("Physical size"))
            ui->l_OtherRes->setText(res.remove(0, res.indexOf(":")+1));
    }
}
