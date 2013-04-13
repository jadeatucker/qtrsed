/*
 * QtrSed - Qt GUI for sed
 * Copyright (C) 2013  Jade Tucker
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

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
