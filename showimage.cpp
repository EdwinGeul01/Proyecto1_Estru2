#include "showimage.h"
#include "ui_showimage.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <QInputDialog>
#include <QDir>
#include <QLabel>


showImage::showImage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::showImage)
{
    ui->setupUi(this);
    bmp_information.Info_bmp.biImportan = 0;
}


bool showImage::readFileBmp()
{

    bool OkButton;
    QString text = QInputDialog::getText(this, tr("Lector de Archivos BMP"),
                                         tr("Ingrese Nombre y Ruta del archivo :"), QLineEdit::Normal,
                                         "./f16.bmp", &OkButton);



    if(!OkButton){

        this->close();
        return false;
    }


    fp = fopen(text.toUtf8().constData(),"r");

    if (fp == NULL) {
        ui->txtArea->insertPlainText("ERROR AL LEER EL ARCHIVO");
        return false;
    }

    fseek(fp,0,SEEK_SET);


    bmp_information.file_bmp.open(text.toUtf8().constData());
    bmp_information.header_bmp.ReadHeader_Header(bmp_information.file_bmp);
    bmp_information.Info_bmp.ReadHeader_Information(bmp_information.file_bmp);



    //Read Info File

    readFileHeader();
   readFileInfoHeader();

    //Read Colors

   readImage();

    return true;

}


void showImage::readFileHeader()
{




    //   show the header of the file
        char type[2];
        type[0] = bmp_information.header_bmp.filetype[0];
        type[1] = bmp_information.header_bmp.filetype[1];



        ui->txtArea->insertPlainText("Tipo de Archivo : " +  QString(type) + "\n");
        ui->txtArea->insertPlainText("Espacio Vacio : " +QString::number(bmp_information.header_bmp.unused1) + QString::number(bmp_information.header_bmp.unused2) + "\n");
        ui->txtArea->insertPlainText("Tamaño de la imagen  : " + QString::number(bmp_information.header_bmp.csize) + "\n");
        ui->txtArea->insertPlainText("Posicion donde Comienza la imagen : " + QString::number(bmp_information.header_bmp.imageSataOffset) + "\n");







}



void showImage::readFileInfoHeader()
{
    ui->txtArea->insertPlainText("Peso de la Imagen : " +  QString::number(bmp_information.Info_bmp.biSize) + "\n");
    ui->txtArea->insertPlainText("Ancho : " +QString::number(bmp_information.Info_bmp.width) + "\n");
    ui->txtArea->insertPlainText("Alto : " + QString::number(bmp_information.Info_bmp.height) + "\n");
    ui->txtArea->insertPlainText("Numero de planos : " + QString::number(bmp_information.Info_bmp.planes) + "\n");
    ui->txtArea->insertPlainText("bites por pixeles : " + QString::number(bmp_information.Info_bmp.bitPix) + "\n");
    ui->txtArea->insertPlainText("Compresion : " + QString::number(bmp_information.Info_bmp.biCompression) + "\n");
    ui->txtArea->insertPlainText("tamaño de la imagen : " + QString::number(bmp_information.Info_bmp.biSizeImage) + "\n");
    ui->txtArea->insertPlainText("numero de Pixeles en X por metro  : " + QString::number(bmp_information.Info_bmp.biXPelsPerMeter) + "\n");
    ui->txtArea->insertPlainText("numero de Pixeles en Y por metro  : "  + QString::number(bmp_information.Info_bmp.biYPelsPerMeter) + "\n");
    ui->txtArea->insertPlainText("Paleta de Colores usado : " + QString::number(bmp_information.Info_bmp.biClrUsed) + "\n");
    ui->txtArea->insertPlainText("Colores Importantes : " + QString::number(bmp_information.Info_bmp.biImportan) + "\n");

}


void showImage::readImage()

{

    if(bmp_information.Info_bmp.bitPix==8){
            const size_t width=bmp_information.Info_bmp.width;
            const size_t height=bmp_information.Info_bmp.height;
            QImage image(width,height,(QImage::Format_Indexed8));
            image.setColorCount(255);
            image.invertPixels();


            int padding = (width*1 + 3);
                unsigned char* imagedata = new unsigned char[padding];
                int y=height-1;
                QVector<QRgb> tabla;

                for(int i=0;i<256;i++){
                    tabla.push_back(qRgb(i,i,i));
                }
                image.setColorTable(tabla);
                for(int i = 0; i < height; i++)
                {
                    int pos=0;

                    fread(imagedata, sizeof(unsigned char), padding, fp);
                    for(int j = 0; j < width ; j += 1)
                    {
                        image.setPixel(pos,y,(int)imagedata[j]);
                        pos++;
                    }
                    y--;
                }
                QLabel lbl;
                lbl.setPixmap(QPixmap::fromImage(image));
                lbl.show();

                QGraphicsScene *graphics = new QGraphicsScene(this);
                QBrush brush(Qt::GlobalColor::white);
                graphics->setBackgroundBrush(brush);
                graphics->addPixmap(QPixmap::fromImage(image));
                ui->graphicsView->setScene(graphics);

                cout << "HASTA AQUI LLEGA";
                return;


    }



    if (bmp_information.Info_bmp.bitPix==24 || bmp_information.Info_bmp.bitPix==32) {

    QImage *image= new QImage(bmp_information.Info_bmp.width,bmp_information.Info_bmp.height,QImage::Format_RGB32);
    image->setDotsPerMeterX(bmp_information.Info_bmp.biXPelsPerMeter);
    image->setDotsPerMeterY(bmp_information.Info_bmp.biYPelsPerMeter);
    image->invertPixels();
    image->scaledToWidth(bmp_information.Info_bmp.biXPelsPerMeter);
    image->scaledToHeight(bmp_information.Info_bmp.biYPelsPerMeter);
 //  image->setDevicePixelRatio(0.4);
 //   image->setDevicePixelRatio()



            fseek(fp,bmp_information.header_bmp.imageSataOffset,SEEK_SET);

            int bytesxRow = (bmp_information.Info_bmp.width)*(bmp_information.Info_bmp.bitPix/8);
            int relleno=0;


            while (bytesxRow % 4 != 0) {

                bytesxRow++;
                relleno ++;

            }


            for (int y = bmp_information.Info_bmp.height-1; y >0;y--) {

                for (int x = 0; x < bmp_information.Info_bmp.width; x++) {

                    fread(&colors_bmp.a,1,3,fp);

                   // fread(&s,1,3,fp);
                    //fread(&d,1,3,fp);



                    colors_bmp.s = (colors_bmp.a/256)%256;
                    colors_bmp.d = colors_bmp.a%256;
                    colors_bmp.a = (colors_bmp.a/(256*256));


                  // ui->txtArea->insertPlainText(QString::number(a) + " " +  QString::number(s) +" " + QString::number(d) + "\n");

                    image->setPixel(x,y,qRgb(colors_bmp.a,colors_bmp.s,colors_bmp.d));




                }
                fread(&colors_bmp.e,1,relleno,fp);

            }

            ui->txtArea->insertPlainText("relleno : " + QString::number(relleno));









    QGraphicsScene *graphics = new QGraphicsScene(this);
    QBrush brush(Qt::GlobalColor::white);
    graphics->setBackgroundBrush(brush);
    graphics->addPixmap(QPixmap::fromImage(*image));
    ui->graphicsView->setScene(graphics);
   // ui->graphicsView->scale(10,10);

}


    QImage *image= new QImage(bmp_information.Info_bmp.width,bmp_information.Info_bmp.height,QImage::Format_RGB16);
    image->setDotsPerMeterX(bmp_information.Info_bmp.biXPelsPerMeter);
    image->setDotsPerMeterY(bmp_information.Info_bmp.biYPelsPerMeter);
    image->invertPixels();
    image->scaledToWidth(bmp_information.Info_bmp.biXPelsPerMeter);
    image->scaledToHeight(bmp_information.Info_bmp.biYPelsPerMeter);
 //  image->setDevicePixelRatio(0.4);
 //   image->setDevicePixelRatio()



            fseek(fp,bmp_information.header_bmp.imageSataOffset,SEEK_SET);

            int bytesxRow = (bmp_information.Info_bmp.width)*(bmp_information.Info_bmp.bitPix/8);
            int relleno=0;


            while (bytesxRow % 4 != 0) {

                bytesxRow++;
                relleno ++;

            }



            for (int y = bmp_information.Info_bmp.height-1; y >0;y--) {

                for (int x = 0; x < bmp_information.Info_bmp.width; x++) {

                    fread(&colors_bmp.a,1,2,fp);

                   // fread(&s,1,3,fp);
                    //fread(&d,1,3,fp);



                    colors_bmp.s = (colors_bmp.a << 5);
                    colors_bmp.d = (colors_bmp.a << 10);
                    colors_bmp.a = (colors_bmp.a << 15);


                  // ui->txtArea->insertPlainText(QString::number(a) + " " +  QString::number(s) +" " + QString::number(d) + "\n");

                    image->setPixel(x,y,qRgb(colors_bmp.a,colors_bmp.s,colors_bmp.d));




                }
                fread(&colors_bmp.e,1,relleno,fp);

            }

            ui->txtArea->insertPlainText("relleno : " + QString::number(relleno));









    QGraphicsScene *graphics = new QGraphicsScene(this);
    QBrush brush(Qt::GlobalColor::white);
    graphics->setBackgroundBrush(brush);
    graphics->addPixmap(QPixmap::fromImage(*image));
    ui->graphicsView->setScene(graphics);
   // ui->graphicsView->scale(10,10);


}

showImage::~showImage()
{
    delete ui;
}

void showImage::on_pushButton_pressed()
{
    close();
}
