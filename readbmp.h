#ifndef READBMP_H
#define READBMP_H

#include <QMainWindow>
#include <string.h>
#include "Information_bmp.h"

namespace Ui {
class readBmp;
}

class readBmp : public QWidget
{
    Q_OBJECT

    FILE *fp;
    colors colors_bmp;
    BMP_INFORMATION bmp_information;



public:
    bool readFileBmp();
    void readFileHeader();
    void readFileInfoHeader();
    void readColors();
    explicit readBmp(QWidget *parent = nullptr);
    ~readBmp();

private slots:
    void on_pushButton_pressed();


public:

    Ui::readBmp *ui;


};

#endif // READBMP_H
