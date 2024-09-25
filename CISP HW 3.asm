.MODEL SMALL
.STACK 100h
.DATA
    promptName      DB 'Enter student name (max 20 chars): $'
    promptDegree    DB 'Enter degree name (max 20 chars): $'
    promptCreditsTaken DB 'Enter number of credits taken: $'
    promptTotalCredits DB 'Enter total credits required: $'
    outputCreditsNeeded DB 'Credits needed to graduate: $'
    
    nameBuffer      DB 20, 0
    degreeBuffer    DB 20, 0
    creditsTaken    DB ? 
    totalCredits    DB ?
    creditsNeeded    DB ? 

.CODE
MAIN PROC
    MOV AX, @DATA
    MOV DS, AX

    LEA DX, promptName
    MOV AH, 09h
    INT 21h

    LEA DX, nameBuffer
    MOV AH, 0Ah 
    INT 21h

    LEA DX, promptDegree
    MOV AH, 09h
    INT 21h

    LEA DX, degreeBuffer
    MOV AH, 0Ah
    INT 21h

    LEA DX, promptCreditsTaken
    MOV AH, 09h
    INT 21h

    MOV AH, 01h
    INT 21h
    SUB AL, '0'
    MOV creditsTaken, AL

    LEA DX, promptTotalCredits
    MOV AH, 09h
    INT 21h

    MOV AH, 01h
    INT 21h
    SUB AL, '0'
    MOV totalCredits, AL

    MOV AL, totalCredits
    SUB AL, creditsTaken
    MOV creditsNeeded, AL 

    MOV AX, 0600h 
    INT 10h


    LEA DX, outputCreditsNeeded
    MOV AH, 09h
    INT 21h

    MOV AL, creditsNeeded
    CMP AL, 0
    JL HandleNegativeCredits

    CALL PrintNumber
    JMP ProgramExit

HandleNegativeCredits:
    MOV DL, '-'
    MOV AH, 02h
    INT 21h
    MOV AL, creditsNeeded 
    NEG AL
    CALL PrintNumber

ProgramExit:
    MOV AX, 4C00h
    INT 21h

PrintNumber PROC
    CMP AL, 0
    JE PrintZero

    ADD AL, '0'
    MOV DL, AL 
    MOV AH, 02h 
    INT 21h
    RET

PrintZero:
    MOV DL, '0'
    MOV AH, 02h
    INT 21h
    RET

PrintNumber ENDP

MAIN ENDP
END MAIN
