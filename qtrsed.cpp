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
    connect(ui->optEChk, SIGNAL(clicked()),
            ui->runBtn, SLOT(click()));
    connect(ui->optnChk, SIGNAL(clicked()),
            ui->runBtn, SLOT(click()));
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

void QtrSed::on_actionSaveInput_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "qtrsed_input.txt", tr("Text Files (*.txt)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
            QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
        } else {
            QTextStream stream(&file);
            stream << ui->textInput->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

void QtrSed::on_actionSaveOutput_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "qtrsed_output.txt", tr("Text Files (*.txt)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
           QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
        } else {
            QTextStream stream(&file);
            stream << ui->textOutput->toPlainText();
            stream.flush();
            file.close();
        }
    }
}

void QtrSed::on_runBtn_clicked()
{
    QString inputTxt = ui->textInput->toPlainText() + "\n";
    QString sedCmd = ui->textSed->toPlainText();
    QString options = "";
    QStringList params;

    if(ui->optEChk->isChecked())
        options += "E";
    if(ui->optnChk->isChecked())
        options += "n";
    if(options.length() > 0) {
        options = "-" + options;
        params << options;
    }

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

void QtrSed::on_textSed_textChanged()
{
    if(ui->autorunChk->isChecked())
      on_runBtn_clicked();
}

void QtrSed::on_textInput_textChanged()
{
    if(ui->autorunChk->isChecked())
      on_runBtn_clicked();
}

void QtrSed::on_actionBash_Script_triggered()
{
    QString script = "#!/bin/bash\nsed ";
    QString options = "";

    if(ui->optEChk->isChecked())
        options += "E";
    if(ui->optnChk->isChecked())
        options += "n";
    if(options.length() > 0) {
        options = "-" + options;
        script += options;
    }

    script += "-e '\n";
    script += ui->textSed->toPlainText() + "\n'\n";

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "qtrsed.sh", tr("Shell Script (*.sh)"));

    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)) {
           QMessageBox::critical(this, tr("Error"), tr("Could not save file"));
        } else {
            QTextStream stream(&file);
            stream << script;
            stream.flush();
            file.close();
        }
    }
}
