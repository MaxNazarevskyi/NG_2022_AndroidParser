#ifndef PARSER_H
#define PARSER_H

#include <QMainWindow>
#include <QFileSystemWatcher>
#include <QFileDialog>

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
    void addedStorage();

private:
    Ui::Parser *ui;
    QStringList system_info;
    QString output;
};
#endif // PARSER_H
