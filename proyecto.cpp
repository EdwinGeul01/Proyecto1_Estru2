#include "proyecto.h"
#include "ui_proyecto.h"
#include <qmovie.h>
#include "readbmp.h"
#include "showimage.h"

proyecto::proyecto(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::proyecto)
{
    ui->setupUi(this);
    QMovie *movie = new QMovie("/home/edwin/Documentos/animacion.gif");
    ui->label->setMovie(movie);
    movie->start();


}

proyecto::~proyecto()
{
    delete ui;
}


void proyecto::on_btnsalir_clicked()
{
    exit(0);
}

void proyecto::on_btnShowFile_pressed()
{
    showImage *win = new showImage();
    if(win->readFileBmp() == false)
    {
        delete win;
        return;
    }
    //win->readImage();
    win->show();
}

void proyecto::on_btnReadFile_pressed()
{
    readBmp *win = new readBmp;
    if(win->readFileBmp() == false)
      {
        delete  win;
        return;
    }
       win->readColors();
        win->show();
}

