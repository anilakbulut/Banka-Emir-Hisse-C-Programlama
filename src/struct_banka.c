#include "struct_banka.h"
#include <stdio.h>
#include <stdlib.h>     
#include <string.h>     
#include <math.h>
#include "read.h"

void Banka_Sistemi_Olustur(struct Banka *banka){
    FILE *fp_hisseler,*fp_portfoy,*fp_emirler;

    Set_Banka(banka);

    fp_hisseler = fopen("doc/hisseler.json", "rt");
    banka->hisseler.List = read_lines(fp_hisseler, &banka->hisseler.satir_sayisi);

    fp_portfoy = fopen("doc/portfoy.json", "rt");
    banka->portfoy.List = read_lines(fp_portfoy, &banka->portfoy.satir_sayisi);

    fp_emirler = fopen("doc/emirler.json", "rt");
    banka->emirler.List = read_lines(fp_emirler, &banka->emirler.satir_sayisi);

    fclose(fp_hisseler);
    fclose(fp_portfoy);
    fclose(fp_emirler);

    Parse(banka);
    Islemler(banka);
    Banka_Free(banka);

}
void Set_Banka(struct Banka *banka){
    banka->hisseler.List = NULL;
    banka->hisseler.ID = NULL;
    banka->hisseler.Sembol = NULL;
    banka->hisseler.Ad = NULL;
    banka->hisseler.Fiyat = NULL;
    banka->hisseler.satir_sayisi = 0;

    banka->portfoy.List = NULL;
    banka->portfoy.ID = NULL;
    banka->portfoy.Sembol = NULL;
    banka->portfoy.Maliyet = NULL;
    banka->portfoy.Adet = NULL;
    banka->portfoy.satir_sayisi = 0;

    banka->emirler;
    banka->emirler.List = NULL;
    banka->emirler.ID = NULL;
    banka->emirler.Sembol = NULL;
    banka->emirler.Islem = NULL;
    banka->emirler.Adet = NULL;
    banka->emirler.satir_sayisi = 0;
}
void Parse(struct Banka *banka){
    Hisseler_Parse_ID(&banka->hisseler);
    Hisseler_Parse_Sembol(&banka->hisseler);
    Hisseler_Parse_Ad(&banka->hisseler);
    Hisseler_Parse_Fiyat(&banka->hisseler);

    Portfoy_Parse_ID(&banka->portfoy);
    Portfoy_Parse_Sembol(&banka->portfoy);
    Portfoy_Parse_Maliyet(&banka->portfoy);
    Portfoy_Parse_Adet(&banka->portfoy);

    Emirler_Parse_ID(&banka->emirler);
    Emirler_Parse_Sembol(&banka->emirler);
    Emirler_Parse_Islem(&banka->emirler);
    Emirler_Parse_Adet(&banka->emirler); 
}

void Islemler(struct Banka *banka){
    double guncel_fiyat; // hisseler.jsondan cekilecek
    double maliyet;      // portfoy.jsondan cekilecek
    double yeni_maliyet; // portfoy.jsona yazilacak
    double kar_zarar=0.0;
    int dongu_sayisi = banka->emirler.satir_sayisi - 2 ;
    int index = 0;
    int i;
    int index_adet;

    printf("\nSatislar Kar/Zarar:\n");
    for(index=0 ; index < dongu_sayisi; index++){
        guncel_fiyat=0.0;
        maliyet=0.0;
        
        if ( strcmp( banka->emirler.Islem[index],"SATIS") == 0 &&
             Hisse_Kontrol(banka,index) == 1 && Portfoy_Kontrol(banka,index) == 1
           ) {
            for(i=0 ; i< banka->portfoy.satir_sayisi-2;i++){
                if ( strcmp( banka->emirler.Sembol[index], banka->portfoy.Sembol[i]) == 0 ){//ayni ise
                    if( atoi(banka->emirler.Adet[index]) > atoi(banka->portfoy.Adet[i])){
                        maliyet = atof(banka->portfoy.Maliyet[i]) * atof(banka->portfoy.Adet[i]);
                    }
                    else maliyet = atof(banka->portfoy.Maliyet[i]) * atof(banka->emirler.Adet[index]);
                    index_adet = i; /*portfoyun adet bilgisini kullanmak icin tutuldu*/
                    break;
                }
            }
            for(i=0 ; i< banka->hisseler.satir_sayisi-2;i++){
                if ( strcmp( banka->emirler.Sembol[index], banka->hisseler.Sembol[i]) == 0 ){//ayni ise
                    if( atoi(banka->emirler.Adet[index]) > atoi(banka->portfoy.Adet[index_adet])){
                        guncel_fiyat = atof(banka->hisseler.Fiyat[i]) * atof(banka->portfoy.Adet[index_adet]);
                    }
                    else guncel_fiyat = atof(banka->hisseler.Fiyat[i]) * atof(banka->emirler.Adet[index]);
                    break;
                }
            }
            Portfoy_Guncelle(banka,banka->emirler.Sembol[index],atof(banka->emirler.Adet[index]));
            printf("%s : %.2lf TL ",banka->emirler.Sembol[index], fabs(guncel_fiyat-maliyet));
            if(guncel_fiyat-maliyet > 0) printf("Kar\n");
            else printf("Zarar\n");
            kar_zarar += guncel_fiyat - maliyet ;
        }
    }
    printf("Toplam Kar/Zarar: ");
    if( kar_zarar > 0) printf("+ ");
    else if(kar_zarar < 0) printf("-");
    printf("%.1lf TL\n",fabs(kar_zarar));

    printf("\nGuncel Portfoy:\n");
    for(index=0 ; index < dongu_sayisi; index++){
        guncel_fiyat=0.0;
        maliyet=0.0;
        yeni_maliyet=0.0;

        if ( strcmp( banka->emirler.Islem[index],"ALIS") == 0 &&
             Hisse_Kontrol(banka,index) == 1 
           ){   
            if(Portfoy_Ara(banka,banka->emirler.Sembol[index]) == 1){
                for(i=0 ; i< banka->hisseler.satir_sayisi-2;i++){
                    if ( strcmp( banka->emirler.Sembol[index], banka->hisseler.Sembol[i]) == 0 ){//ayni ise
                        guncel_fiyat = atof(banka->hisseler.Fiyat[i]) * atof(banka->emirler.Adet[index]);
                        yeni_maliyet += guncel_fiyat;
                        break;
                    }
                }
                for(i=0 ; i< banka->portfoy.satir_sayisi-2;i++){
                    if ( strcmp( banka->emirler.Sembol[index], banka->portfoy.Sembol[i]) == 0 ){//ayni ise
                        maliyet = atof(banka->portfoy.Maliyet[i]) * atof(banka->portfoy.Adet[i]);
                        yeni_maliyet +=maliyet;
                        break;
                    }
                }
                yeni_maliyet = yeni_maliyet / (atof(banka->emirler.Adet[index]) + atof(banka->portfoy.Adet[i]));
                sprintf(banka->portfoy.Maliyet[i],"%lf",yeni_maliyet);
                sprintf(banka->portfoy.Adet[i],"%lf",atof(banka->portfoy.Adet[i])+atof(banka->emirler.Adet[index]));
            }
            else{
               Portfoy_realloc(banka,index);
            }
        }
    }

    for(index = 0 ; index < banka->portfoy.satir_sayisi-2 ; index++){
        if( atof(banka->portfoy.Adet[index]) > 0){
            printf("Hisse: %s\n",banka->portfoy.Sembol[index]);
            printf("Adet: %d\n",atoi(banka->portfoy.Adet[index]));
            printf("Maliyet: %.2lf\n", atof(banka->portfoy.Maliyet[index]));
            if( index != banka->portfoy.satir_sayisi-3) printf("--------------------\n");
            else printf("\n");
        }
    }
}

int Portfoy_Kontrol(struct Banka *banka,int index){
    int i;
    int portfoy_kontrol=0;
    for(i=0; i<banka->portfoy.satir_sayisi-2;i++){
        if ( strcmp( banka->emirler.Sembol[index], banka->portfoy.Sembol[i]) == 0){
             portfoy_kontrol=1;
             break;
        }
    }
    return portfoy_kontrol;
}
int Hisse_Kontrol(struct Banka *banka,int index){
    int i;
    int hisse_kontrol=0;

    for(i=0; i<banka->hisseler.satir_sayisi-2;i++){
        if ( strcmp( banka->emirler.Sembol[index], banka->hisseler.Sembol[i]) == 0){
             hisse_kontrol=1;
             break;
        }
    }

    return hisse_kontrol;
}

void Portfoy_realloc(struct Banka *banka,int index){
    int i;
    int maliyet_index=0;
    for(i=0;i<banka->hisseler.satir_sayisi-2;i++){
        if ( strcmp( banka->emirler.Sembol[index], banka->hisseler.Sembol[i]) == 0){
            maliyet_index = i;
            break;
        }
    }

    banka->portfoy.satir_sayisi++;

    banka->portfoy.ID = realloc(banka->portfoy.ID,(banka->portfoy.satir_sayisi -2) * sizeof(char *));
    banka->portfoy.Sembol = realloc(banka->portfoy.Sembol,(banka->portfoy.satir_sayisi -2) * sizeof(char *));
    banka->portfoy.Maliyet = realloc(banka->portfoy.Maliyet,(banka->portfoy.satir_sayisi -2) * sizeof(char *));
    banka->portfoy.Adet = realloc(banka->portfoy.Adet,(banka->portfoy.satir_sayisi -2) * sizeof(char *)); 

    banka->portfoy.ID[banka->portfoy.satir_sayisi -3] = (char*)malloc( strlen(banka->emirler.ID[index]) * sizeof(char*));
    banka->portfoy.Sembol[banka->portfoy.satir_sayisi -3] = (char*)malloc( strlen(banka->emirler.ID[index]) * sizeof(char*));
    banka->portfoy.Maliyet[banka->portfoy.satir_sayisi -3] = (char*)malloc( strlen(banka->emirler.ID[index]) * sizeof(char*));
    banka->portfoy.Adet[banka->portfoy.satir_sayisi -3] = (char*)malloc( strlen(banka->emirler.ID[index]) * sizeof(char*));

    sprintf(banka->portfoy.ID[banka->portfoy.satir_sayisi -3],"%s",banka->emirler.ID[index]);
    sprintf(banka->portfoy.Sembol[banka->portfoy.satir_sayisi -3],"%s",banka->emirler.Sembol[index]);
    sprintf(banka->portfoy.Maliyet[banka->portfoy.satir_sayisi -3],"%s",banka->hisseler.Fiyat[maliyet_index]);
    sprintf(banka->portfoy.Adet[banka->portfoy.satir_sayisi -3],"%s",banka->emirler.Adet[index]);

}
/*arama dizisini bankanın portfoyunun indexlerinde ara,bulunca adet bilgisini guncelle*/
void Portfoy_Guncelle(struct Banka *banka,char *arama,double adet){
    int index;
    for(index = 0 ; index < banka->portfoy.satir_sayisi-2 ; index++){
        if ( strcmp(banka->portfoy.Sembol[index],arama ) == 0 ){
            sprintf(banka->portfoy.Adet[index],"%lf", atof(banka->portfoy.Adet[index]) - adet );
        }
    }
}

int Portfoy_Ara(struct Banka *banka,char *arama){
    int index;
    for(index=0; index<banka->portfoy.satir_sayisi-2;index++){
        if( strcmp( arama, banka->portfoy.Sembol[index]) == 0 ){ // esitse
      //      printf("%s ile %s karsilastirildi\n",arama,banka->portfoy.Sembol[index]);
            return 1; // emirlerde yer alan sembol, portfoyde var ise 1 return eder
        }
    }
    return 0; // // emirlerde yer alan sembol, portfoyde yok ise 0 return eder
}

void Banka_Free(struct Banka * banka){
    int index = 0;
    for (index = 0; index < banka->portfoy.satir_sayisi; index++)      free(banka->portfoy.List[index]);
    for (index = 0; index < banka->portfoy.satir_sayisi-2; index++)    free(banka->portfoy.ID[index]);
    for (index = 0; index < banka->portfoy.satir_sayisi-2; index++)    free(banka->portfoy.Maliyet[index]);
    for (index = 0; index < banka->portfoy.satir_sayisi-2; index++)    free(banka->portfoy.Adet[index]);

    for (index = 0; index < banka->hisseler.satir_sayisi; index++)      free(banka->hisseler.List[index]);
    for (index = 0; index < banka->hisseler.satir_sayisi-2; index++)    free(banka->hisseler.ID[index]);
    for (index = 0; index < banka->hisseler.satir_sayisi-2; index++)    free(banka->hisseler.Sembol[index]);
    for (index = 0; index < banka->hisseler.satir_sayisi-2; index++)    free(banka->hisseler.Ad[index]);
    for (index = 0; index < banka->hisseler.satir_sayisi-2; index++)    free(banka->hisseler.Fiyat[index]);

    for (index = 0; index < banka->emirler.satir_sayisi; index++)      free(banka->emirler.List[index]);
    for (index = 0; index < banka->emirler.satir_sayisi-2; index++)    free(banka->emirler.ID[index]);
    for (index = 0; index < banka->emirler.satir_sayisi-2; index++)    free(banka->emirler.Islem[index]);
    for (index = 0; index < banka->emirler.satir_sayisi-2; index++)    free(banka->emirler.Adet[index]);

    free(banka->emirler.List);
    free(banka->emirler.ID);
    free(banka->emirler.Islem);
    free(banka->emirler.Adet);

    free(banka->portfoy.List);
    free(banka->portfoy.ID);
    free(banka->portfoy.Maliyet);
    free(banka->portfoy.Adet);

    free(banka->hisseler.List);
    free(banka->hisseler.ID);
    free(banka->hisseler.Sembol);
    free(banka->hisseler.Ad);
    free(banka->hisseler.Fiyat);

    banka->emirler.List = NULL;
    banka->emirler.ID = NULL;
    banka->emirler.Islem = NULL;
    banka->emirler.Adet = NULL;

    banka->portfoy.List = NULL;
    banka->portfoy.ID = NULL;
    banka->portfoy.Maliyet = NULL;
    banka->portfoy.Adet = NULL;

    banka->hisseler.List = NULL;
    banka->hisseler.ID = NULL;
    banka->hisseler.Sembol = NULL;
    banka->hisseler.Ad = NULL;
    banka->hisseler.Fiyat = NULL;
}
