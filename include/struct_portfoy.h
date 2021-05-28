#ifndef PORTFOY_H
#define PORTFOY_H

struct Portfoy{
    char **List;
    int satir_sayisi;
    char **ID;
    char **Sembol;
    char **Maliyet;
    char **Adet;
};

void Portfoy_Parse_ID(struct Portfoy *portfoy);
void Portfoy_Parse_Sembol(struct Portfoy *portfoy);
void Portfoy_Parse_Maliyet(struct Portfoy *portfoy);
void Portfoy_Parse_Adet(struct Portfoy *portfoy);

#endif