#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char label[100],opcode[100],operand[100];
int startingaddress,locctr=0;
void searchTable(FILE*file , char field[]);
void main(){
        FILE * input = fopen("input.txt","r");
         FILE * output = fopen("intermediate.txt","w");
          FILE * symtab = fopen("symtab.txt","a+");
           FILE * optab = fopen("optab.txt","r");

        fscanf(input,"%s\t%s\t%s",label,opcode,operand);
        if(strcmp(opcode, "START")==0){
            startingaddress = atoi(operand);
            locctr = startingaddress;
            fprintf(output,%04x\t%s\t%s\t%04x\n,locctr,label,opcode,locctr);
            fscanf(input,"%s\t%s\t%s",label,opcode,operand);
        }
        while(strcmp(opcode,"END")!=0){
            if(strcmp(label,"")!=0){
                if(searchTable(symtab,label) == 0 && strcmp(label,"**")!=0){
                    fprintf(symtab,"%s\t%04x\n",label,locctr);
                }
                else if(searchTable(symtab,label)==1){
                    printf("Duplicate label found");

                }
                if(searchTable(optab,opcode)==1){
                    locctr+=3;
                }
                else if(strcmp(opcode,"WORD")==0){
                    locctr+=3
                }
                else if(strcmp(opcode,"RESW")==0){
                    locctr+=3*atoi(operand);
                }
                 else if(strcmp(opcode,"RESB")==0){
                    locctr+=atoi(operand);
                }
                 else if(strcmp(opcode,"BYTE")==0){
                    locctr+=strlen(operand);
                }
                else{
                    printf("Invalid opcode found!");
                }
            }
                fprintf(output,"%04x\t%s\t%s\t%s\n",locctr,label,opcode,operand);
                fscanf(input ,"%s\t%s\t%s",label,opcode,operand);


        }
         fprintf(output,"%04x\t%s\t%s\t%s\n",locctr-startingaddress,label,opcode,operand);
    }
int searchTable(FILE * file , char field[]){
    rewind(file);
    int in = fgetc(file);
    char intake[100] = "";
    while (in != EOF){
        char c = (char) in;
        if(c == '\t'){
            if(strcmp(intake,field)== 0){
                return 1;
            }
            strcpy(intake,"");
            while((char)in ! = '\n' && in ! = EOF){
                in = fgetc(file);
            }
        }
        else
            strncat(intake,&c,1);
            in = fgetc(file);
    }
    return 0;
}
