#include "readbmp.h"
#include "ui_readbmp.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <QInputDialog>
#include <vector>

readBmp::readBmp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::readBmp)
{
    ui->setupUi(this);
    //readFileBmp();
}





bool readBmp::readFileBmp()
{

    bool OkButton;
    QString text = QInputDialog::getText(this, tr("Lector de Archivos BMP"),
                                         tr("Ingrese Nombre y Ruta del archivo :"), QLineEdit::Normal,
                                         "./m.bmp", &OkButton);


    //IF OK BUTTON IS PRESSED

    if(!OkButton){

        this->close();
        return false;
    }  


    fp = fopen(text.toUtf8().constData(),"r"); // OPEN THE FILE


    //IF THE FILE DOES NOT EXIST------>
    if (fp == NULL) {
        ui->txtArea->insertPlainText("ERROR AL LEER EL ARCHIVO");
        return false;
    }



    //READ THE FILE  [ HEADER & INFO HEADER ]

        fseek(fp,0,SEEK_SET);
        bmp_information.file_bmp.open(text.toUtf8().constData()); // OPEN THE FILE
        bmp_information.header_bmp.ReadHeader_Header(bmp_information.file_bmp);// READ AND UNPACK THE HEADER
        bmp_information.Info_bmp.ReadHeader_Information(bmp_information.file_bmp);// READ AND UNPACK THE INFO_HEADER

        readFileHeader(); // PRINT THE HEADER
        readFileInfoHeader(); // PRINT THE INFO HEADER


    //READ A COLORS




    return true;

}


void readBmp::readFileHeader()
{



    //READ THE FILE FORMAT
    char type[2];
    type[0] = bmp_information.header_bmp.filetype[0];
    type[1] = bmp_information.header_bmp.filetype[1];


    //SHOW THE HEADER OF THE FILE

    ui->txtArea->insertPlainText("Tipo de Archivo : " +  QString(type) + "\n");
    ui->txtArea->insertPlainText("Espacio Vacio : " +QString::number(bmp_information.header_bmp.unused1) + QString::number(bmp_information.header_bmp.unused2) + "\n");
    ui->txtArea->insertPlainText("Tamaño de la imagen  : " + QString::number(bmp_information.header_bmp.csize) + "\n");
    ui->txtArea->insertPlainText("Posicion donde Comienza la imagen : " + QString::number(bmp_information.header_bmp.imageSataOffset) + "\n");





}



void readBmp::readFileInfoHeader()
{

    // SHOW THE INFO OF THE HEADER FILE
    ui->txtArea->insertPlainText("Peso de la Imagen : " +  QString::number(bmp_information.Info_bmp.biSize) + "\n");
    ui->txtArea->insertPlainText("Ancho : " +QString::number(bmp_information.Info_bmp.width) + "\n");
    ui->txtArea->insertPlainText("Alto : " + QString::number(bmp_information.Info_bmp.height) + "\n");
    ui->txtArea->insertPlainText("Numero de planos : " + QString::number(bmp_information.Info_bmp.planes) + "\n");
    ui->txtArea->insertPlainText("bites por pixeles : " + QString::number(bmp_information.Info_bmp.biSize) + "\n");
    ui->txtArea->insertPlainText("Compresion : " + QString::number(bmp_information.Info_bmp.biCompression) + "\n");
    ui->txtArea->insertPlainText("tamaño de la imagen : " + QString::number(bmp_information.Info_bmp.biSizeImage) + "\n");
    ui->txtArea->insertPlainText("numero de Pixeles en X por metro  : " + QString::number(bmp_information.Info_bmp.biXPelsPerMeter) + "\n");
    ui->txtArea->insertPlainText("numero de Pixeles en Y por metro  : "  + QString::number(bmp_information.Info_bmp.biYPelsPerMeter) + "\n");
    ui->txtArea->insertPlainText("Paleta de Colores usado : " + QString::number(bmp_information.Info_bmp.biClrUsed) + "\n");
    ui->txtArea->insertPlainText("Colores Importantes : " + QString::number(bmp_information.Info_bmp.biImportan) + "\n");






//    fread(&b,1, sizeof(unsigned char), fp);
//    fread(&g,1, sizeof(unsigned char), fp);
//    fread(&r,1, sizeof(unsigned char), fp);





}


void readBmp::readColors()

{

            fseek(fp,bmp_information.header_bmp.imageSataOffset,SEEK_SET); // MOVE WHERE THE COLORS BEGIN
            std::vector<int> color_data;    //COLORS INFO CONTAINER




            int bytesxRow = (bmp_information.Info_bmp.width)*(bmp_information.Info_bmp.bitPix/8);
            int relleno=0;


            while (bytesxRow % 4 != 0) {

                bytesxRow++;
                relleno ++;

            }//CALCULATE HOW MANY BYTES TO FILL




            for (int y = bmp_information.Info_bmp.height; y >0;y--) {

                for (int x = 0; x < bmp_information.Info_bmp.width; x++) {
                    fread(&colors_bmp.a,1,3,fp);

                    colors_bmp.s = (colors_bmp.a/256)%256;
                    colors_bmp.d = colors_bmp.a%256;
                    colors_bmp.a = (colors_bmp.a/(256*256));

                    color_data.push_back(colors_bmp.a);
                    color_data.push_back(colors_bmp.s);
                    color_data.push_back(colors_bmp.d);




                }
                fread(&colors_bmp.e,1,relleno,fp);

            }//SAVE THE COLORS IN TO COLOR_DATA


            QString texto = "";
            for (int var = 0; var < color_data.size(); var+=3) {



                     ui->txtcolors->insertPlainText(texto + (QString::number(color_data[var]) + " " +
                QString::number(color_data[var+1]) + " " + QString::number(color_data[var+2]) + "\n"));

            }







}

readBmp::~readBmp()
{
    delete ui;
}

void readBmp::on_pushButton_pressed()
{
    close();
}


