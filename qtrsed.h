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
