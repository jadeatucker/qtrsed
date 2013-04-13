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

#ifndef QTRSED_H
#define QTRSED_H

#include <QMainWindow>

namespace Ui {
class QtrSed;
}

class QtrSed : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit QtrSed(QWidget *parent = 0);
    ~QtrSed();
    
private slots:
    void on_quitBtn_clicked();

    void on_actionOpen_triggered();

    void on_runBtn_clicked();

    void on_lineSedstr_textChanged(const QString &arg1);

    void on_textInput_textChanged();

private:
    Ui::QtrSed *ui;
};

#endif // QTRSED_H
