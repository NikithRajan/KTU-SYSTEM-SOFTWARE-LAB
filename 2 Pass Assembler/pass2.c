#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
char operand[10],opcode[10],label[10],locctr[10];
void searchTable(FILE*file , char field[]);
void obtainValue(FILE*file,char field[],char * remaining);
void main(){
    char startingAddress[10];
     FILE * input = fopen("intermediate.txt","r");
     FILE * output = fopen("output.txt","w");
     FILE * optab = fopen("optab.txt","r");
     FILE * objprgm = fopen("object.txt","w");
     FILE * symtab = fopen("symtab.txt","r");

     fscanf(input,"%s\t%s\t%s\t%s",locctr,label,opcode,operand);

     if(strcmp(opcode,"START")==0){
            fprintf(output,"%s\t%s\t%s\t%s\t%s\n",locctr,label,opcode,operand," ");
     }
    fprintf(objprgm,"H^%s %s\n",label,operand);
    strcpy(startingAddress,operand);
    fscanf(input,"%s\t%s\t%s\t%s",locctr,label,opcode,operand);

    fprintf(objprgm,"t^****^");
    int lengthLoc = ftell(objprgm)-5;
    int remaining = 25;

    while (strcmp(opcode,"END")!=0){
        char objCode[100] = "";
        char operandAddress[10];
        if(searchTable(optab,opcode)==1){
            if(searchTable(symtab,symbol)==1){
                obtainValue(symtab,operand,operandAddress);
            }
            else{
                strcpy(operandAddress,"0");
            }
        char opValue[10];
        obtainValue(optab,opcode,opvalue);
        strcat(objCode,opValue);
        strcat(objCode,operandAddress);
    }
    else if(strcmp(operand,"WORD")==0){
        strcat(objcode , "0000");
        strcat(objcode,operand);
    }
    else if (strcmp(operand,"BYTE")==0){
        strcat(objCode,"0000");
        char length[10];
        itoa(strlen(operand),length,10);
        strcat(objCode,length);
    }
    if(strlen(objCode)<remaining){
        fprintf(objprgm,"%s ",objCode);
        remaining-=strlen(objCode);
    }
    else{
        int currentPos = ftell(objprgm);
        fseek(objprgm,lengthLoc,SEEK_SET);
        int length = 25 - remaining;
        fprintf(objprgm,"%04X",length);
        fseek(objprgm,currentPos,SEEK_SET);
        remaining = 25;
        fprintf(objprgm,"\nT^****^%s",objCode);
        remaining-=strlen(objCode);
        lengthLoc=ftell(objprgm)-11;
    }
    fprintf(output,"%s\t%s\t%s\t%s\t%s",locctr,label,operand,opcode,objCode);
    fscanf(input, "%s\t%s\t%s\t%s",locctr,label,opcode,operand);
    }
    int currentPos = ftell(objprgm);
    fseek(objprgm,lengthLoc,SEEK_SET);
    int length = 25  -remaining;
    fprintf(objprgm,"%04X",length);
    fseek(objprgm,currentPos,SEEK_SET);
    fprintf(objprgm,"\nE^%s",startingAddress);

}

int searchTable(FILE*file , char field[]){
    rewind(file);
    int in = fgetc(file);
    char intake[100]="";
    while(in!=EOF){
        char c = (char)in;
        if(c=='\t'){
            if(strcmp(intake,field)==0){
                return 1;
            }
            strcpy(intake,"");
            while((char)in != '\n'&& in != EOF){
                in = fgetc(file);
            }
        }
        else{
            strncat(intake, &c , 1);
        }
        in = fgetc(file);
    }
    return 0;

}

int obtainValue(FILE * file ,char field[], char * returnable){
   `rewind(file);
    char intake[100] = "";
    int in = fgetc(file);
    while (in != EOF){
        char c = (char) in;
        if(c == '\t'){
            if(strcmp(intake,field)==0){
                strcpy(intake,"");
                in = fgetc(file);
                while((char)in != '\n' && in != EOF){
                    char cin = (char)in;
                    strncat(intake,&cin,1);
                    in = fgetc(file);
                }
                strcpy(returnable,intake);
            }
            strcpy(intake,"");
            while((char) in !='\n' && in ! = EOF)
                in = fgetc(file);
        }
        else{
            strncat(intake,&c,1);
        }
        in = fgetc(file);
    }
    return 0;
}
