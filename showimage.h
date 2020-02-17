#ifndef SHOWIMAGE_H
#define SHOWIMAGE_H

#include <QWidget>
#include "Information_bmp.h"

namespace Ui {
class showImage;
}

class showImage : public QWidget
{
    Q_OBJECT

    FILE *fp;
    colors colors_bmp;
    BMP_INFORMATION bmp_information;





public:
    ifstream read_file;
    bool readFileBmp();
    void readFileHeader();
    void readFileInfoHeader();
    void readImage();
    explicit showImage(QWidget *parent = nullptr);
    ~showImage();

private slots:
    void on_pushButton_pressed();

private:
    Ui::showImage *ui;
};

#endif // SHOWIMAGE_H
