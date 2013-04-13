#include "qtrsed.h"
#include "ui_qtrsed.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QProcess>

QtrSed::QtrSed(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtrSed)
{
    ui->setupUi(this);
}

QtrSed::~QtrSed()
{
    delete ui;
}

void QtrSed::on_quitBtn_clicked()
{
    qApp->quit();
}

void QtrSed::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), QString(), tr("All Files (*.*)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
            return;
        }
        QTextStream in(&file);
        ui->textInput->setPlainText(in.readAll());
        file.close();
    }
}

void QtrSed::on_runBtn_clicked()
{
    QString inputTxt = ui->textInput->toPlainText() + "\n";
    QString sedCmd = ui->lineSedstr->text();
    QStringList params;
    params << "-e" << sedCmd;

    QProcess p;
    p.start("/usr/bin/sed", params);

    p.write(inputTxt.toStdString().c_str());
    p.closeWriteChannel();

    p.waitForStarted();
    if (p.waitForFinished() && p.exitCode() == 0) {
      ui->textOutput->setText(p.readAllStandardOutput());
    } else {
      ui->textOutput->setText(p.readAllStandardError());
    }
}

void QtrSed::on_lineSedstr_textChanged(const QString &arg1)
{
    if(ui->autorunChk->isChecked())
      on_runBtn_clicked();
}

void QtrSed::on_textInput_textChanged()
{
    if(ui->autorunChk->isChecked())
      on_runBtn_clicked();
}
