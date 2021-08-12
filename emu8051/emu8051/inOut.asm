CLR A
get:
    MOV A, P2
    JZ get
    ACALL print
    SJMP get

print:
	MOV P0, A
	MOV P1, #'c'
	MOV P1, 0h
    MOV P2, 0h
	CLR A
	RET
