#include "struct_hisseler.h"
#include <stdio.h>
#include <stdlib.h>     
#include <string.h>     


void Hisseler_Parse_ID(struct Hisseler *hisseler){
    int tirnak_sayisi=0;
    int bas_tirnak,son_tirnak;
    int index;
    int count=0;
    char *pch;

    hisseler->ID = malloc((hisseler->satir_sayisi -2) * sizeof(char *));
    
    /*ID bilgileri*/
    for(index = 0; index < hisseler->satir_sayisi -2; index++){

        tirnak_sayisi=0;
        bas_tirnak=0;
        son_tirnak=0;   
        pch = strchr(hisseler->List[index+1],'\"');
        while(tirnak_sayisi != 4){
            tirnak_sayisi++;
            if(tirnak_sayisi == 3) bas_tirnak = pch-hisseler->List[index+1];
            if(tirnak_sayisi == 4) son_tirnak = pch-hisseler->List[index+1];
            pch = strchr(pch+1,'\"');
        }

        hisseler->ID[index] = (char*)malloc((son_tirnak-bas_tirnak) * sizeof(char*));

        count=0;
        while(bas_tirnak != son_tirnak){
            if(hisseler->List[index+1][bas_tirnak] != '\"'){
                hisseler->ID[index][count] = hisseler->List[index+1][bas_tirnak];      
                count++;
            }
            bas_tirnak++;
        }
        hisseler->ID[index][count] = '\0';
 
    //    printf("ID :%s\n",hisseler->ID[index]);
    }

}

void Hisseler_Parse_Sembol(struct Hisseler *hisseler){
    int tirnak_sayisi=0;
    int bas_tirnak,son_tirnak;
    int index;
    int count=0;
    char *pch;

    hisseler->Sembol = malloc((hisseler->satir_sayisi -2) * sizeof(char *));
    
    /*Sembol*/
    for(index = 0; index < hisseler->satir_sayisi -2; index++){

        tirnak_sayisi=0;
        bas_tirnak=0;
        son_tirnak=0;   
        pch = strchr(hisseler->List[index+1],'\"');
        while(tirnak_sayisi != 8){
            tirnak_sayisi++;
            if(tirnak_sayisi == 7) bas_tirnak = pch-hisseler->List[index+1];
            if(tirnak_sayisi == 8) son_tirnak = pch-hisseler->List[index+1];
            pch = strchr(pch+1,'\"');
        }

        hisseler->Sembol[index] = (char*)malloc((son_tirnak-bas_tirnak) * sizeof(char*));

        count=0;
        while(bas_tirnak != son_tirnak){
            if(hisseler->List[index+1][bas_tirnak] != '\"'){
                hisseler->Sembol[index][count] = hisseler->List[index+1][bas_tirnak];      
                count++;
            }
            bas_tirnak++;
        }
        hisseler->Sembol[index][count] = '\0';
 
    //    printf("Sembol :%s\n",hisseler->Sembol[index]);
    }        
}

void Hisseler_Parse_Ad(struct Hisseler *hisseler){
     int tirnak_sayisi=0;
    int bas_tirnak,son_tirnak;
    int index;
    int count=0;
    char *pch;

    hisseler->Ad = malloc((hisseler->satir_sayisi -2) * sizeof(char *));
    
    /*Ad*/
    for(index = 0; index < hisseler->satir_sayisi -2; index++){

        tirnak_sayisi=0;
        bas_tirnak=0;
        son_tirnak=0;   
        pch = strchr(hisseler->List[index+1],'\"');
        while(tirnak_sayisi != 12){
            tirnak_sayisi++;
            if(tirnak_sayisi == 11) bas_tirnak = pch-hisseler->List[index+1];
            if(tirnak_sayisi == 12) son_tirnak = pch-hisseler->List[index+1];
            pch = strchr(pch+1,'\"');
        }

        hisseler->Ad[index] = (char*)malloc((son_tirnak-bas_tirnak) * sizeof(char*));

        count=0;
        while(bas_tirnak != son_tirnak){
            if(hisseler->List[index+1][bas_tirnak] != '\"'){
                hisseler->Ad[index][count] = hisseler->List[index+1][bas_tirnak];      
                count++;
            }
            bas_tirnak++;
        }
        hisseler->Ad[index][count] = '\0';
 
    //    printf("Ad :%s\n",hisseler->Ad[index]);
    }
}

void Hisseler_Parse_Fiyat(struct Hisseler *hisseler){
    int tirnak_sayisi=0;
    int bas_tirnak,ters_s_parantez;
    int index;
    int count=0;
    char *pch;
    char *pch2;
    hisseler->Fiyat = malloc((hisseler->satir_sayisi -2) * sizeof(char *));
    
    /*Fiyat -> 14.tırnak ve } arasında*/
    for(index = 0; index < hisseler->satir_sayisi -2; index++){
        
        tirnak_sayisi=0;
        bas_tirnak=0;
        ters_s_parantez =0;
        pch = strchr(hisseler->List[index+1],'\"');
        while(tirnak_sayisi != 14){
            tirnak_sayisi++; 
            if(tirnak_sayisi == 14) bas_tirnak = pch-hisseler->List[index+1];
            pch = strchr(pch+1,'\"');
        }

        pch2 = strchr(hisseler->List[index+1],'}');
        ters_s_parantez = pch2-hisseler->List[index+1];
        
        hisseler->Fiyat[index] = (char*)malloc((ters_s_parantez-bas_tirnak) * sizeof(char*));

        count=0;
        while(bas_tirnak != ters_s_parantez){
            /*ignore edilenler*/
            if(
                hisseler->List[index+1][bas_tirnak] != '\"'  &&
                hisseler->List[index+1][bas_tirnak] != ' '  &&
                hisseler->List[index+1][bas_tirnak] != ','  &&
                hisseler->List[index+1][bas_tirnak] != ':'
              ){
                
                hisseler->Fiyat[index][count] = hisseler->List[index+1][bas_tirnak];      
                count++;
            }
            bas_tirnak++;
        }
        hisseler->Fiyat[index][count] = '\0';
 
   //     printf("Fiyat :%s\n",hisseler->Fiyat[index]);
    }        
}