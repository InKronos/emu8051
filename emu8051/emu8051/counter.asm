CLA A
MOV A5h, #1
NOP
loop:
    ACALL print
	MOV A, A5
	SUBB A, #10
	JZ end
	INC A5h
    SJMP loop

print:
	MOV A, A5h
	MOV P0, A
	MOV P1, #'d'
	MOV P1, 0h
	CLR A
	RET

end: