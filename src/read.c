#include "read.h"
#include <stdlib.h>     /* For dynamic memory allocation */
#include <string.h>     /* For string functions */

char** read_lines(FILE* jsonFile, int* count) {
    char** List = NULL;      
    char okunan_satir[200];           
    int satir_sayisi=0;          
    int satir_genislik;         
    int index;       

    /*Dosyada kac satir oldugu sayilir*/
    while (fgets(okunan_satir, sizeof(okunan_satir), jsonFile) != NULL) {                                      
       satir_sayisi++;
    }
     *count = satir_sayisi;
    
    rewind(jsonFile); /*isaretcimiz dosya basina gelir*/
    List = malloc(satir_sayisi * sizeof(char *)); /* malloc islemi ile yer ayrilir*/

    for (index = 0; index < satir_sayisi; index++) {    
        fgets(okunan_satir, sizeof(okunan_satir), jsonFile); /*json dosyasindan satirlari tutan diziye satir okunur*/

        satir_genislik = strlen(okunan_satir);

        List[index] = malloc(satir_genislik);
        okunan_satir[satir_genislik-1] = '\0';  /*satirdaki son elemana satirin bittigi bilgisi atanir -> '\0'*/

        /* Copy the line into the newly allocated space. */
        strcpy(List[index], okunan_satir);
    }
   
    return List;
}