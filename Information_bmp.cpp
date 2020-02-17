#include "Information_bmp.h"
#include <fstream>
#include <iostream>
#include <inttypes.h>
#include <stdio.h>
#include <stdint.h>
#include <cstring>
using namespace std;

void header::UnPackBuffer_Header()
{

    char * c = bufferheader;
    memcpy(&filetype,c,2);
    memcpy(&csize,c+=2,4);
    memcpy(&unused1,c+=4,2);
    memcpy(&unused2,c+=2,2);
    memcpy(&imageSataOffset,c+=2,4);




}
void header::ReadHeader_Header(ifstream &filename)
{

    filename.read((char *) &bufferheader,sizeof (bufferheader));
    UnPackBuffer_Header();



}


void Information_File::ReadHeader_Information(ifstream &filename)
{

    filename.read((char *) &bufferheader,sizeof (bufferheader));
    UnPackBuffer_Information();




}
void Information_File::UnPackBuffer_Information()
{

    char* c = bufferheader;

    memcpy(&biSize,c,4);
    memcpy(&width,c+=4,4);
    memcpy(&height,c+=4,4);
    memcpy(&planes,c+=4,2);
    memcpy(&bitPix,c+=2,2);
    memcpy(&biCompression,c+=2,4);
    memcpy(&biSizeImage,c+=4,4);
    memcpy(&biXPelsPerMeter,c+=4,4);
    memcpy(&biYPelsPerMeter,c+=4,4);
    memcpy(&biClrUsed,c+=4,4);
    memcpy(&biImportan,c+=4,4);




}

