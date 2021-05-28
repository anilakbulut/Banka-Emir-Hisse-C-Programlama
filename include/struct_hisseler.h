#ifndef HISSELER_H
#define HISSELER_H

struct Hisseler{
    char **List;
    int satir_sayisi;
    char **ID;
    char **Sembol;
    char **Ad;
    char **Fiyat;
};

void Hisseler_Parse_ID(struct Hisseler *hisseler);
void Hisseler_Parse_Sembol(struct Hisseler *hisseler);
void Hisseler_Parse_Ad(struct Hisseler *hisseler);
void Hisseler_Parse_Fiyat(struct Hisseler *hisseler);

#endif