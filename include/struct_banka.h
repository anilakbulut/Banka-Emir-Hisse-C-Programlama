#ifndef BANKA_H
#define BANKA_h

#include "read.h"
#include "struct_emirler.h"
#include "struct_hisseler.h"
#include "struct_portfoy.h"


struct Banka{
    struct Emirler emirler;
    struct Hisseler hisseler;
    struct Portfoy portfoy;
};

void Banka_Sistemi_Olustur(struct Banka *banka);
void Parse(struct Banka *banka);
void Banka_Free(struct Banka * banka);
void Islemler(struct Banka *banka);
void Portfoy_Guncelle(struct Banka *banka,char *arama,double adet);
int Portfoy_Ara(struct Banka *banka,char *arama);
void Portfoy_realloc(struct Banka *banka,int index);
int Hisse_Kontrol(struct Banka *banka,int index);
int Portfoy_Kontrol(struct Banka *banka,int index);
void Set_Banka(struct Banka *banka);

#endif