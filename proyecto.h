#ifndef PROYECTO_H
#define PROYECTO_H

#include <QMainWindow>
#include <stdio.h>
#include <string.h>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class proyecto; }
QT_END_NAMESPACE

class proyecto : public QMainWindow
{
    Q_OBJECT

public:
    proyecto(QWidget *parent = nullptr );
    ~proyecto();

private slots:
    void on_btnsalir_clicked();

    void on_btnShowFile_pressed();

    void on_btnReadFile_pressed();


private:
    Ui::proyecto *ui;

};



#endif // PROYECTO_H
