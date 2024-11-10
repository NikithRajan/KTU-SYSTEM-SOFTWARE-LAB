DATA SEGMENT
    MSG1 DB 10,13, "PALINDROME$"
    MSG2 DB 10,13, "ENTER A STRING:$"
    MSG3 DB 10,13, "IS A PALINDROME$"
    MSG4 DB 10,13, "IS NOT A PALINDROME$"
    STR1 DW dup(0)
DATA ENDS
ASSUME CS : CODE SEGEMENT DS : DATA SEGMENT
CODE SEGMENT
START:  
        MOV AX,DATA
        MOV DS,AX
        LEA DX,MSG1
        MOV AH,09H
        INT 21h
        LEA DX,MSG2
        MOV AH,09H
        INT 21h
        LEA DI,STR1
        LEA SI,STR1
        MOV AH,01H
NEXT:
        INT 21h
        CMP AL,0DH
        JE TERMINATE
        MOV [DI],AL
        INC DI
        JMP NEXT
TERMINATE :
        MOV AL,"$"
        MOV [DI],AL
CHECK:
        DEC DI
        MOV AL,[SI]
        CMP [DI],AL
        JN NOTPALINDROME 
        INC SI
        CMP SI,DI
        JL CHECK
NOTPALINDROME:
        LEA DX,MSG4
        MOV AH,09H
        INT 21h
        JMP XX
PALINDROME:
        LEA DX,MSG3
        MOV AH,09H
        INT 21h
        JMP XX
XX:
        MOV AHL, 4CH
        INT 21h
        HLT
CODE ENDS
ENS START
