#include "struct_emirler.h"
#include <stdio.h>
#include <stdlib.h>     
#include <string.h>     

void Emirler_Parse_ID(struct Emirler *emirler){
    int tirnak_sayisi=0;
    int bas_tirnak,son_tirnak;
    int index;
    int count=0;
    char *pch;

    emirler->ID = malloc((emirler->satir_sayisi -2) * sizeof(char *));
    
    /*ID bilgileri*/
    for(index = 0; index < emirler->satir_sayisi -2; index++){

        tirnak_sayisi=0;
        bas_tirnak=0;
        son_tirnak=0;   
        pch = strchr(emirler->List[index+1],'\"');
        while(tirnak_sayisi != 4){
            tirnak_sayisi++;
            if(tirnak_sayisi == 3) bas_tirnak = pch-emirler->List[index+1];
            if(tirnak_sayisi == 4) son_tirnak = pch-emirler->List[index+1];
            pch = strchr(pch+1,'\"');
        }

        emirler->ID[index] = (char*)malloc((son_tirnak-bas_tirnak) * sizeof(char*));

        count=0;
        while(bas_tirnak != son_tirnak){
            if(emirler->List[index+1][bas_tirnak] != '\"'){
                emirler->ID[index][count] = emirler->List[index+1][bas_tirnak];      
                count++;
            }
            bas_tirnak++;
        }
        emirler->ID[index][count] = '\0';
 
   //     printf("ID :%s\n",emirler->ID[index]);
    }

}

void Emirler_Parse_Sembol(struct Emirler *emirler){
    int tirnak_sayisi=0;
    int bas_tirnak,son_tirnak;
    int index;
    int count=0;
    char *pch;

    emirler->Sembol = malloc((emirler->satir_sayisi -2) * sizeof(char *));
    
    /*Sembol*/
    for(index = 0; index < emirler->satir_sayisi -2; index++){

        tirnak_sayisi=0;
        bas_tirnak=0;
        son_tirnak=0;   
        pch = strchr(emirler->List[index+1],'\"');
        while(tirnak_sayisi != 8){
            tirnak_sayisi++;
            if(tirnak_sayisi == 7) bas_tirnak = pch-emirler->List[index+1];
            if(tirnak_sayisi == 8) son_tirnak = pch-emirler->List[index+1];
            pch = strchr(pch+1,'\"');
        }

        emirler->Sembol[index] = (char*)malloc((son_tirnak-bas_tirnak) * sizeof(char*));

        count=0;
        while(bas_tirnak != son_tirnak){
            if(emirler->List[index+1][bas_tirnak] != '\"'){
                emirler->Sembol[index][count] = emirler->List[index+1][bas_tirnak];      
                count++;
            }
            bas_tirnak++;
        }
        emirler->Sembol[index][count] = '\0';
 
  //      printf("Sembol :%s\n",emirler->Sembol[index]);
    }        
}

void Emirler_Parse_Islem(struct Emirler *emirler){
    int tirnak_sayisi=0;
    int bas_tirnak,son_tirnak;
    int index;
    int count=0;
    char *pch;
    
    emirler->Islem = malloc((emirler->satir_sayisi -2) * sizeof(char *));
    
    /*Islem*/
    for(index = 0; index < emirler->satir_sayisi -2; index++){

        tirnak_sayisi=0;
        bas_tirnak=0;
        son_tirnak=0;   
        pch = strchr(emirler->List[index+1],'\"');
        while(tirnak_sayisi != 12){
            tirnak_sayisi++;
            if(tirnak_sayisi == 11) bas_tirnak = pch-emirler->List[index+1];
            if(tirnak_sayisi == 12) son_tirnak = pch-emirler->List[index+1];
            pch = strchr(pch+1,'\"');
        }

        emirler->Islem[index] = (char*)malloc((son_tirnak-bas_tirnak) * sizeof(char*));

        count=0;
        while(bas_tirnak != son_tirnak){
            /*ignore edilenler*/
            if(
                emirler->List[index+1][bas_tirnak] != '\"' &&
                emirler->List[index+1][bas_tirnak] != ' '  &&
                emirler->List[index+1][bas_tirnak] != ','  &&
                emirler->List[index+1][bas_tirnak] != ':'
              ){
                
                emirler->Islem[index][count] = emirler->List[index+1][bas_tirnak];      
                count++;
            }
            bas_tirnak++;
        }
        emirler->Islem[index][count] = '\0';
 
 //       printf("Islem :%s\n",emirler->Islem[index]);
    }         
};

void Emirler_Parse_Adet(struct Emirler *emirler){
    int tirnak_sayisi=0;
    int bas_tirnak,ters_s_parantez;
    int index;
    int count=0;
    char *pch;
    char *pch2;
    emirler->Adet = malloc((emirler->satir_sayisi -2) * sizeof(char *));
    
    /*Adet -> 12.tırnak ve } arasında*/
    for(index = 0; index < emirler->satir_sayisi -2; index++){
        
        tirnak_sayisi=0;
        bas_tirnak=0;
        ters_s_parantez =0;
        pch = strchr(emirler->List[index+1],'\"');
        while(tirnak_sayisi != 14){
            tirnak_sayisi++; 
            if(tirnak_sayisi == 14) bas_tirnak = pch-emirler->List[index+1];
            pch = strchr(pch+1,'\"');
        }

        pch2 = strchr(emirler->List[index+1],'}');
        ters_s_parantez = pch2-emirler->List[index+1];
        
        emirler->Adet[index] = (char*)malloc((ters_s_parantez-bas_tirnak) * sizeof(char*));

        count=0;
        while(bas_tirnak != ters_s_parantez){
            /*ignore edilenler*/
            if(
                emirler->List[index+1][bas_tirnak] != '\"'  &&
                emirler->List[index+1][bas_tirnak] != ' '  &&
                emirler->List[index+1][bas_tirnak] != ','  &&
                emirler->List[index+1][bas_tirnak] != ':'
              ){
                
                emirler->Adet[index][count] = emirler->List[index+1][bas_tirnak];      
                count++;
            }
            bas_tirnak++;
        }
        emirler->Adet[index][count] = '\0';
 
 //       printf("Adet :%s\n",emirler->Adet[index]);
    }            
}