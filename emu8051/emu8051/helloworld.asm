CLR A
MOV A, #'H'
ACALL print
MOV A, #'E'
ACALL print
MOV A, #'L'
ACALL print
MOV A, #'L'
ACALL print
MOV A, #'O'
ACALL print
MOV A, #' '
ACALL print
MOV A, #'W'
ACALL print
MOV A, #'o'
ACALL print
MOV A, #'R'
ACALL print
MOV A, #'L'
ACALL print
MOV A, #'D'
ACALL print
MOV A, #'!'
ACALL print
JZ end

print:
	MOV P0, A
	MOV P1, #'c'
	MOV P1, 0h
	CLR A
	RET

end: