/** EL2208 Praktikum Pemecahan Masalah dengan C 2021/2022
 *  Modul            : 7 - Stack & Queue
 *  Hari dan Tanggal : Jumat, 26 April 2024
 *  Nama (NIM)       : Naufal Afiq Muzaffar (13222025)
 *  Asisten (NIM)    : Muhammad Rafli (18321012)
 *  Nama File        : main.c
 *  Deskripsi        : Menentukan output berupa nilai terbesar selanjutnya dari masing-masing Data dari input yang diberikan
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    int Data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* head;
} Stack;

void push(Stack* stack, int new_Data) {
    Node* new_node = (Node*) malloc(sizeof(Node));
    new_node->Data = new_Data;
    new_node->next = stack->head;
    stack->head = new_node;
}

int pop(Stack* stack) {
    int ret_val = 0;
    Node* temp = stack->head;

    if (temp != NULL) {
        ret_val = temp->Data;
        stack->head = temp->next;
        free(temp);
    }
    return(ret_val);
}

Stack* stackInverse(Stack* stack, int PanjangData){
    Stack* temp = (Stack*) malloc(sizeof(Stack));
    temp->head = NULL;

    for (int i = 0; i < PanjangData; i++) {
        push(temp,pop(stack));
    }
    return temp;
}

void toStack(Stack* stack, int number, int PanjangData){
    for (int i = 0; i < PanjangData; i++, number /= 10 ) {
        push(stack, number % 10);
    }
}

void PrintData(Stack* stack, int JumlahData){
    for ( int i = 0; i < JumlahData; i++){
        int Data = pop(stack);
        if(i != (JumlahData-1)){
            printf(" %d ->", Data);
        }
        else{
            printf(" %d\n", Data);
        }
    }
}

int main(){

    char RiwayatGrafik[8];
    int Data,PanjangData=0;
    int DataTerbesar, HariTerbesar=0;
    int NextDay;
    int kondisi = 0;
    int hari =0;

    Stack* StackData = (Stack*) malloc(sizeof(Stack));
    Stack* StackResult = (Stack*) malloc(sizeof(Stack));
    Stack* StackDay = (Stack*) malloc(sizeof(Stack));
    StackData->head = NULL;
    StackDay->head = NULL;
    StackResult->head = NULL;

    printf("Input Data >> ");
    scanf("%s", RiwayatGrafik);

    PanjangData = strlen(RiwayatGrafik);
    Data = atoi(RiwayatGrafik);

    for (int i = 0; i < PanjangData; i++){
        hari = i+1;
        toStack(StackData,Data, PanjangData);

        for (int j = 0; j < hari; j++){
            DataTerbesar = pop(StackData);
        }
        while (kondisi == 0){
            NextDay = pop(StackData);
            hari = hari + 1;
            if (NextDay > DataTerbesar){
                push(StackResult,NextDay);
                if (hari>HariTerbesar){
                    HariTerbesar = hari;
                    push(StackDay, hari);
                }
                DataTerbesar = NextDay;
                kondisi = 1;
            }
            if (NextDay == 0){
                push(StackResult,0);
                kondisi=1;
            }
        }
        hari = 0;
        kondisi =0;
    }
    
    printf("DATA   :");
    toStack(StackData,Data, PanjangData);
    PrintData(StackData,PanjangData);

    printf("RESULT :");
    StackResult = stackInverse(StackResult,PanjangData);
    PrintData(StackResult,PanjangData);

    printf("SELL   :");
    StackDay = stackInverse(StackDay,PanjangData);
    for ( int i = 0; i < PanjangData; i++){
        Data = pop(StackDay);
        if(Data !=0){
            printf(" Day%d", Data);
        }
    }
}
