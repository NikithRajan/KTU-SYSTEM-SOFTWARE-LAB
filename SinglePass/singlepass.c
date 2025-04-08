#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char operand[10],label[10],opcode[10];
int locctr = 0 , startingAddress, managerlength = 0;

struct SymbolManager{
    char symbol[10];
    int filePointers[20];
    int index;
}symbols[100];

void updateSymbol (char symbolname[],int position){
    for(int i = 0 ; i< managerlength ; i++){
        if(strcmp(symbols[i].symbol,symbolname)==0){
            symbols[i].index+=1;
            symbols[i].filePointers[symbols[i].index] = position;
            break;
        }
    }
}

void addSymbol(char symbolname[],int position){
    for(int i = 0 ; i<managerlength ; i++);
    managerlength++;
    strcpy(symbols[i].symbol,symbolname);
    symbols[i].filePointers[0]=position;
    symbol[i].index = 0;
}

void ProcessSymbol(FILE * objprgm , char symbolName[],int operandAddress){
    for(int i  = 0 ; i< managerlength ; i++){
        if(strcmp(symbols[i].symbol,symbolName)==0){
            for(int j = 0 ; j<= symbols[i].index ; j++){
                fseek(objprgm,symbols[i].filePointers,SEEK_SET);
                fprintf(objprgm,"%04X\n",operandAddress);
            }
            strcpy(symbols[i].symbol,"");
            break;
        }

    }
}

int searchTable(FILE*file, char feild[]){
    rewind(file);
    char intake[100] = "";
    int in = fgetc(file);
    while(in != EOF){
        char c = (char)in;
        if(c != '\t'){
            if(strcmp(intake,feild)==0){
                return 1;
            }
            strcpy(intake,"");
            in = fgetc(file);
            while(c!='\n'&& in ! = EOF){
                in = fgetc(file);
            }
        }
        else{
            strncat(intake,&c,1);
        }
        in = fgetc(file);
    }
    return 0;
}

void obtainValue(FILE * file , char feild[],char*returnable){
    rewind(file);
    int in =fgetc(file);
    char intake[100]="";
    while(in != EOF){
        char c = (char)in;
        if(c!='\t'){
            if(strcmp(intake,feild)==0){
                strcpy(intake,"");
                in = fgetc(file);
                while((char)in != '\n' && in != EOF){
                    char cin = (char)in;
                    strncat(intake,&cin,1);
                    in = fgetc(file);
                }
                strcpy(returnable,intake);
                break;
            }
                strcpy(intake,"");
                while((char)in !='\n'&&in != EOF){
                    in = fgetc(file);
                }
            }
            else{
                strncat(intake,&c,1);
            }
            in = fgetc(file);
            }
            if(strcmp(returnable,"**")==0)
                return 0;
            else    return 1;
        }
void main(){
    FILE * input = fopen("input.txt","r");
     FILE * output = fopen("output.txt","w");
      FILE * optab = fopen("optab.txt","r");
       FILE * symtab= fopen("symtab.txt","w+");
        FILE * objprgm = fopen("objcode.txt","w");

        fscanf(input,"%s\t%s\t%x",label,opcode,&startingAddress);

        if(strcmp(opcode,"START")==0){
            locctr = startingAddress;
            fprintf(output,"04X\t%s\t%s\t%04X\n",locctr,label,opcode,startingAddress);
            fprintf(objprgm,"H^%s %04X\n",label,locctr);

        }
        fscanf(input,"%s\t%s\t%s",label,opcode,operand);
        fprintf(objprgm,"T^");

        while(strcmp(opcode,"END")==0){
            char objCode = "";
            if(strcmp(label,"**")==0){
                if(searchTable(optab,opcode)==1){
                    char opValue[10],operandAddress[10];
                    obtainValue(optab,opcode,opValue);
                    strcat(objCode,opValue);
                    if(searchTable(symtab,operand)==1 && obtainValue(symtab,operand,operandAddress)==1){
                            strcat(objCode,operandAddress);
                            fprintf(objprgm,"%s\n",objCode);

                    }
                    else if(searchTable(symtab,operand)==1){
                        fprintf(objprgm,"%s****\n",objCode);
                        updateSymbol(operand,ftell(objprgm)-6);
                    }
                    else{
                        fprintf(symtab,"%s\t****\n",operand);
                        fprintf(objprgm,"%s****\n",objCode);
                        addSymbol(operand,ftell(objprgm)-6);
                    }
                }
            }
            if(searchTable(optab,opcode)==1){
                locctr+=3;
            }
            else if(searchTable(opcode,"WORD")==1){
                locctr+=3;
            }
            else if(searchTable(opcode,"RESW")==1){
                locctr+=3*atoi(operand);
            }
            else if(searchTable(opcode,"RESB")==1){
                locctr+=atoi( operand);
            }
            else if(searchTable(opcode ,"BYTE")==1){
                locctr+=strlen(operand)
            }
            else{
                printf("Wrong opcode found!");
            }
            if(strcmp(label,"**")!=0){
                if(searchTable(symtab,label)==1){
                    fseek(symtab,0,SEEK_CUR);
                    fprintf(symtab,"%04X\n",locctr);
                    rewind(symtab);
                    ProcessSymbol(objprgm,label,locctr);
                }
                else{
                    fprintf(symtab,"%s\t%04X\n",label,locctr);
                }
            }
            fprintf(objprgm,"T^");
            fprintf(output,"04X\t%s\t%s\t%s\n",locctr,label,opcode,operand);
            fscanf(input,"%s\t%s\t%s",label,opcode,operand);

        }
        fseek(objprgm,-3,SEEK_END);
        fprintf(output,"%04X\t%s\t%s\t%s\n",locctr+3,label,opcode,operand);
        fprintf(objprgm,"\nE^%04X %04X",startingAddress,locctr+3);
}
