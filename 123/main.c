#include <stdio.h>
#include <stdlib.h>

#define LEN 8



int PW[] = {1, 5 ,2 ,0 ,3 ,7 ,4 , 6 };

int PO[] = {3, 0, 2, 4, 6, 1, 7 , 5 };

int krzyz[] = { 4, 5, 6, 7, 0, 1, 2, 3};

int p10[] = {2, 4, 1, 6, 3, 9, 0, 8, 7, 5 };

int SL1[] = { 1 , 2 , 3 , 4 , 0} ;

int SL2[] = { 2 , 3 , 4 , 0 , 1};

int p10_w8[] = { 5 , 2 , 6 , 3 , 7 , 4 , 9 , 8 };

int p4_w8[] = { 3 , 0 , 1 , 2 , 1 , 2 , 3 , 0 };

int p4[]= { 1 , 3 , 2 , 0};

int SBox1[4][4]={ {1, 0, 3, 2},
                {3, 2, 1, 0},
                {0, 2 ,1 ,3},
                {3, 1 ,3 ,2}  };

int SBox2[4][4]={ {0, 1, 2, 3},
                {2, 0, 1, 3},
                {3, 0, 1, 0},
                {2, 1, 0, 3}  };

int klucz_pocz[] = { 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1};

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
        drugi_out[i-(dl/2)]=in[i];
       }
    }
}

void cat(int * k0, int * k1, int * out , int dl){ //zakładając że k1 i k0 ma równe długości
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
        return in[1]+in[0]*2;
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

void sbox(int * in, int sbox[][4], int * out ){
    int ad[] = {in[0],in[3]};
    int bc[] = {in [1], in[2]};
    int r, c, x;

    r=todec(ad);
    c=todec(bc);
    x=sbox[r][c];

    printf("\n Kolumna: %i Wiersz: %i X:%i",c,r,x);


    out[1]=x%2;
    x=x/2;
    out[0]=x%2;

    }

 void szyfrowanie(int * in, int * klucz, int * out){
    int k0[4];
    int k1[4];
    int k1_kopia[4];
    int k1_buf[8];
    int k1_buf2[4];
    int pierwsze_bity[4];
    int drugie_bity[4];
    int buf[8];
    int out1[4];
    split(in,k0,k1,8);


    int i;
    for(i=0;i<4;i++){
        k1_kopia[i]=k1[i];
    }

    printf("\n drugie pol: ");

    for(i=0;i<4;i++){
        printf("%i",k1[i]);
    }


    permutacja(k1,k1_buf,p4_w8,8);

    printf("\n p4_w8: ");

    for(i=0;i<LEN;i++){
        printf("%i",k1_buf[i]);
    }

    xor(klucz,k1_buf,buf,8);

    printf("\n Xor: ");

    for(i=0;i<LEN;i++){
        printf("%i",buf[i]);
    }

    split(buf,pierwsze_bity,drugie_bity,8);
    int s1[2];
    int s2[2];

    printf("\n Pierwsze bity: ");

    for(i=0;i<4;i++){
        printf("%i",pierwsze_bity[i]);
    }

    printf("\n Drugie bity: ");

    for(i=0;i<4;i++){
        printf("%i",drugie_bity[i]);
    }

    sbox(pierwsze_bity,SBox1,s1);
    sbox(drugie_bity,SBox2,s2);



    cat(s1,s2,k1,4);

    printf("\n Po Sboxach: ");

    for(i=0;i<4;i++){
        printf("%i",k1[i]);
    }

    permutacja(k1,k1_buf2,p4,4);

    xor(k0,k1_buf2,out1,4);

    cat(out1,k1_kopia,out,8);

 }

int main()
{
    int tekst[LEN];
    char buf[LEN];
    int arek[LEN];

    scanf("%s",buf);
    int i;
    for(i=0;i<LEN;i++){  //Wpisz klucz do tablicy, jeśli jest więcej niż 6 to ignoruj jeśli mniej to wpisz 0

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

    printf("\n wynik permutacji : ");

    int wynik[LEN];

    permutacja(tekst,wynik,PW,LEN); //PW

    for(i=0;i<LEN;i++){
        printf("%i",wynik[i]);
    }

     printf("\n Klucz 1 rundy: ");

    int pierwszej_rundy[LEN];
    int drugiej_rundy[LEN];

    generuj_klucze(pierwszej_rundy,drugiej_rundy); //generowanie kluczy

    for(i=0;i<LEN;i++){
        printf("%i",pierwszej_rundy[i]);
    }

      printf("\n  Klucz 2 rundy:");

    for(i=0;i<LEN;i++){
        printf("%i",drugiej_rundy[i]);
    }

    int zaszyfrowany[8];

    szyfrowanie(wynik,pierwszej_rundy,zaszyfrowany); //szyfrowanie pierwszej rundy

    printf("\n Zaszyfrowany tekst po 1 rundzie: ");

    for(i=0;i<LEN;i++){
        printf("%i",zaszyfrowany[i]);
    }

    permutacja(zaszyfrowany,wynik,krzyz,8); //krzyzowanie

    printf("\n Po krzyzowaniu: ");

    for(i=0;i<LEN;i++){
        printf("%i",wynik[i]);
    }

    szyfrowanie(wynik,drugiej_rundy,zaszyfrowany); //szyfrowanie drugiej rundy

    printf("\n Zaszyfrowany tekst po 1 rundzie: ");

    for(i=0;i<LEN;i++){
        printf("%i",zaszyfrowany[i]);
    }

    permutacja(zaszyfrowany,wynik,PO,8); // PO

    printf("\n Zaszyfrowany tekst: ");

    for(i=0;i<LEN;i++){
        printf("%i",wynik[i]);
    }

    permutacja(wynik,arek,PW,LEN);

    printf("\n Po PW: ");

    for(i=0;i<LEN;i++){
        printf("%i",arek[i]);
    }


    szyfrowanie(arek,drugiej_rundy,zaszyfrowany); //szyfrowanie drugiej rundy

    printf("\n Zaszyfrowany tekst po 2 rundzie: ");

    for(i=0;i<LEN;i++){
        printf("%i",zaszyfrowany[i]);
    }

    permutacja(zaszyfrowany,wynik,krzyz,8); //krzyzowanie

    printf("\n Po krzyzowaniu: ");

    for(i=0;i<LEN;i++){
        printf("%i",wynik[i]);
    }

    szyfrowanie(wynik,pierwszej_rundy,zaszyfrowany); //szyfrowanie pierwszej rundy

    printf("\n Zaszyfrowany tekst po 1 rundzie: ");

    for(i=0;i<LEN;i++){
        printf("%i",zaszyfrowany[i]);
    }

    permutacja(zaszyfrowany,wynik,PO,8); //PO

    printf("\n Odszyfrowany tekst: ");

    for(i=0;i<LEN;i++){
        printf("%i",wynik[i]);
    }

    return 0;

}
