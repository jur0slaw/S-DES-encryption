#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LEN 8



int PW[] = {1, 5 ,2 ,0 ,3 ,7 ,4 , 6 };

int PO[] = {3, 0, 2, 4, 6, 1, 7 , 5 };

int krzyz[] = { 4, 5, 6, 7, 0, 1, 2, 3};

int p10[] = {2, 4, 1, 6, 3, 9, 0, 8, 7, 5 };

int SL1[] = { 1 , 2 , 3 , 4 , 0} ;

int SL2[] = { 2 , 3 , 4 , 0 , 1};

int p10_w8[] = { 5 , 2 , 6 , 3 , 7 , 4 , 9 , 8 };

int SBox1[4][4]={ {1, 0, 3, 2},
                {3, 2, 1, 0},
                {0, 2 ,1 ,3},
                {3, 1 ,3 ,2}  };

int SBox2[4][4]={ {0, 1, 2, 3},
                {3, 2, 1, 0},
                {0, 2 ,1 ,3},
                {3, 1 ,3 ,2}  };

int klucz_pocz[] = { 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1};

void permutacja(int * tekst, int * wynik, int * wzor ,  int dl){

    int i;
    for(i=0;i<dl;i++){
        wynik[i]=tekst[wzor[i]];
    }

}

void split(int * in, int * pierwszy_out, int * drugi_out, int dl){
    int i;
    for(i=0;i<dl;i++){
       if(i<dl/2){
        pierwszy_out[i]=in[i];
       }
       else{
        drugi_out[i]=in[i];
       }
    }
}

void cat(int * k0, int * k1, int * out , int dl){ //zak³adaj¹c ¿e k1 i k0 ma równe d³ugoœci
    int i;
    for(i=0;i<dl;i++){
        if(i<dl/2){
        out[i]=k0[i];
        }else{
            out[i]=k1[i-(dl/2)];
        }
    }
}

 void xor(int * pierwszy_in,int * drugi_in, int * out, int dl ){
    int i;
    for(i=0;i<dl;i++){
        out[i]=(pierwszy_in[i]+drugi_in[i])%2;
    }

 }

 int todec(int * in){
        return in[0]+in[1]*2;
 }

 void generuj_klucze(int * pierwszej_rundy, int * drugiej_rundy){

        int buf[10];
        int k0[5];
        int k1[5];
        int buf_k0[5];
        int buf_k1[5];
        permutacja(klucz_pocz,buf,p10,10);
        split(buf,k0,k1,10);
        permutacja(k0,buf_k0,SL1,5);
        permutacja(k1,buf_k1,SL1,5);
        cat(buf_k0,buf_k1,buf,10);
        permutacja(buf,pierwszej_rundy,p10_w8,8);
        permutacja(buf_k0,k0,SL2,5);
        permutacja(buf_k1,k1,SL2,5);
        cat(k0,k1,buf,10);
        permutacja(buf,drugiej_rundy,p10_w8,8);



 }

int main()
{
    int tekst[LEN];
    char buf[LEN];

    scanf("%s",buf);
    int i;
    for(i=0;i<LEN;i++){  //Wpisz klucz do tablicy, jeœli jest wiêcej ni¿ 6 to ignoruj jeœli mniej to wpisz 0

        if(buf[i]==49){
            tekst[i]=1;
        }
        else{
            tekst[i]=0;
        }


    }

    for(i=0;i<LEN;i++){          //Sprawdzanie
        printf("%i",tekst[i]);
    }

    printf("\n");

    int wynik[LEN];

    permutacja(tekst,wynik,PW,LEN); //PW

    for(i=0;i<LEN;i++){
        printf("%i",wynik[i]);
    }

     printf("\n");

    int pierwszej_rundy[LEN];
    int drugiej_rundy[LEN];

    generuj_klucze(pierwszej_rundy,drugiej_rundy);

    for(i=0;i<LEN;i++){
        printf("%i",pierwszej_rundy[i]);
    }

      printf("\n");

    for(i=0;i<LEN;i++){
        printf("%i",drugiej_rundy[i]);
    }

    return 0;

}
