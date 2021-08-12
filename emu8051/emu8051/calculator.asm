CLR A
MOV B5h, #3

get:
    MOV A, P2
    JZ get
    ACALL save
    MOV A, B5h
    JZ licz
    SJMP get

licz:
    MOV A, A6h
    SUBB A,  #+
    JZ dodaj
    MOV A, A6h
    SUBB A,  #-
    JZ odejmij
    MOV A, A6h
    SUBB A,  #*
    JZ pomuż
    MOV A, A6h
    SUBB A,  #/
    JZ dziel

dodaj:
    MOV A, A5h
    ADD A, A7h
    MOV A8h, A
    ACALL print
    JZ end

odejmij:
    MOV A, A5h
    SUBB A, A7h
    MOV A8h, A
    ACALL print
    JZ end

pomuż:
    MOV A, A5h
    MOV B, A7h
    MUL AB
    ACALL print
    JZ end

pomuż:
    MOV A, A5h
    MOV B, A7h
    MUL AB
    ACALL print
    JZ end

print:
    MOV
    MOV P0, A
	MOV P1, #'c'
	MOV P1, 0h
    MOV P2, 0h
	
	RET