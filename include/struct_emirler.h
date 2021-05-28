#ifndef EMIRLER_H
#define EMIRLER_H

struct Emirler{
    char **List;
    int satir_sayisi;
    char **ID;
    char **Sembol;
    char **Islem;
    char **Adet;
};

void Emirler_Parse_ID(struct Emirler *emirler);
void Emirler_Parse_Sembol(struct Emirler *emirler);
void Emirler_Parse_Islem(struct Emirler *emirler);
void Emirler_Parse_Adet(struct Emirler *emirler);

#endif