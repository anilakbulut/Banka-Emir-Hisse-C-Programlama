#include "struct_portfoy.h"
#include <stdio.h>
#include <stdlib.h>     
#include <string.h>     

void Portfoy_Parse_ID(struct Portfoy *portfoy){
    int tirnak_sayisi=0;
    int bas_tirnak,son_tirnak;
    int index;
    int count=0;
    char *pch;

    portfoy->ID = malloc((portfoy->satir_sayisi -2) * sizeof(char *));
    
    /*ID bilgileri*/
    for(index = 0; index < portfoy->satir_sayisi -2; index++){

        tirnak_sayisi=0;
        bas_tirnak=0;
        son_tirnak=0;   
        pch = strchr(portfoy->List[index+1],'\"');
        while(tirnak_sayisi != 4){
            tirnak_sayisi++;
            if(tirnak_sayisi == 3) bas_tirnak = pch-portfoy->List[index+1];
            if(tirnak_sayisi == 4) son_tirnak = pch-portfoy->List[index+1];
            pch = strchr(pch+1,'\"');
        }

        portfoy->ID[index] = (char*)malloc((son_tirnak-bas_tirnak) * sizeof(char*));

        count=0;
        while(bas_tirnak != son_tirnak){
            if(portfoy->List[index+1][bas_tirnak] != '\"'){
                portfoy->ID[index][count] = portfoy->List[index+1][bas_tirnak];      
                count++;
            }
            bas_tirnak++;
        }
        portfoy->ID[index][count] = '\0';
 
    //    printf("ID :%s\n",portfoy->ID[index]);
    }
}


void Portfoy_Parse_Sembol(struct Portfoy *portfoy){
    int tirnak_sayisi=0;
    int bas_tirnak,son_tirnak;
    int index;
    int count=0;
    char *pch;

    portfoy->Sembol = malloc((portfoy->satir_sayisi -2) * sizeof(char *));
    
    /*Sembol*/
    for(index = 0; index < portfoy->satir_sayisi -2; index++){

        tirnak_sayisi=0;
        bas_tirnak=0;
        son_tirnak=0;   
        pch = strchr(portfoy->List[index+1],'\"');
        while(tirnak_sayisi != 8){
            tirnak_sayisi++;
            if(tirnak_sayisi == 7) bas_tirnak = pch-portfoy->List[index+1];
            if(tirnak_sayisi == 8) son_tirnak = pch-portfoy->List[index+1];
            pch = strchr(pch+1,'\"');
        }

        portfoy->Sembol[index] = (char*)malloc((son_tirnak-bas_tirnak) * sizeof(char*));

        count=0;
        while(bas_tirnak != son_tirnak){
            if(portfoy->List[index+1][bas_tirnak] != '\"'){
                portfoy->Sembol[index][count] = portfoy->List[index+1][bas_tirnak];      
                count++;
            }
            bas_tirnak++;
        }
        portfoy->Sembol[index][count] = '\0';
 
   //     printf("Sembol :%s\n",portfoy->Sembol[index]);
    }    
}

void Portfoy_Parse_Maliyet(struct Portfoy *portfoy){
    int tirnak_sayisi=0;
    int bas_tirnak,son_tirnak;
    int index;
    int count=0;
    char *pch;

    portfoy->Maliyet = malloc((portfoy->satir_sayisi -2) * sizeof(char *));
    
    /*Maliyet*/
    for(index = 0; index < portfoy->satir_sayisi -2; index++){

        tirnak_sayisi=0;
        bas_tirnak=0;
        son_tirnak=0;   
        pch = strchr(portfoy->List[index+1],'\"');
        while(tirnak_sayisi != 11){
            tirnak_sayisi++;
            if(tirnak_sayisi == 10) bas_tirnak = pch-portfoy->List[index+1];
            if(tirnak_sayisi == 11) son_tirnak = pch-portfoy->List[index+1];
            pch = strchr(pch+1,'\"');
        }

        portfoy->Maliyet[index] = (char*)malloc((son_tirnak-bas_tirnak) * sizeof(char*));

        count=0;
        while(bas_tirnak != son_tirnak){
            /*ignore edilenler*/
            if(
                portfoy->List[index+1][bas_tirnak] != '\"' &&
                portfoy->List[index+1][bas_tirnak] != ' '  &&
                portfoy->List[index+1][bas_tirnak] != ','  &&
                portfoy->List[index+1][bas_tirnak] != ':'
              ){
                
                portfoy->Maliyet[index][count] = portfoy->List[index+1][bas_tirnak];      
                count++;
            }
            bas_tirnak++;
        }
        portfoy->Maliyet[index][count] = '\0';
 
     //   printf("Maliyet :%s\n",portfoy->Maliyet[index]);
    }     
}

void Portfoy_Parse_Adet(struct Portfoy *portfoy){
    int tirnak_sayisi=0;
    int bas_tirnak,ters_s_parantez;
    int index;
    int count=0;
    char *pch;
    char *pch2;
    portfoy->Adet = malloc((portfoy->satir_sayisi -2) * sizeof(char *));
    
    /*Adet -> 12.tırnak ve } arasında*/
    for(index = 0; index < portfoy->satir_sayisi -2; index++){
        
        tirnak_sayisi=0;
        bas_tirnak=0;
        ters_s_parantez =0;
        pch = strchr(portfoy->List[index+1],'\"');
        while(tirnak_sayisi != 12){
            tirnak_sayisi++; 
            if(tirnak_sayisi == 12) bas_tirnak = pch-portfoy->List[index+1];
            pch = strchr(pch+1,'\"');
        }

        pch2 = strchr(portfoy->List[index+1],'}');
        ters_s_parantez = pch2-portfoy->List[index+1];
        
        portfoy->Adet[index] = (char*)malloc((ters_s_parantez-bas_tirnak) * sizeof(char*));

        count=0;
        while(bas_tirnak != ters_s_parantez){
            /*ignore edilenler*/
            if(
                portfoy->List[index+1][bas_tirnak] != '\"'  &&
                portfoy->List[index+1][bas_tirnak] != ' '  &&
                portfoy->List[index+1][bas_tirnak] != ','  &&
                portfoy->List[index+1][bas_tirnak] != ':'
              ){
                
                portfoy->Adet[index][count] = portfoy->List[index+1][bas_tirnak];      
                count++;
            }
            bas_tirnak++;
        }
        portfoy->Adet[index][count] = '\0';
 
     //   printf("Adet :%s\n",portfoy->Adet[index]);
    }        
}