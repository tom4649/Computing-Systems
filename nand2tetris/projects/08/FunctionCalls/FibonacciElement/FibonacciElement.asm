@256
D=A
@SP
M=D
@777
D=A
@SP
M=M+1
A=M-1
M=D
@LCL
D=M
@SP
M=M+1
A=M-1
M=D
@ARG
D=M
@SP
M=M+1
A=M-1
M=D
@THIS
D=M
@SP
M=M+1
A=M-1
M=D
@THAT
D=M
@SP
M=M+1
A=M-1
M=D
@SP
D=M
@0
D=D-A
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Sys.init
0;JMP
//first step
//funcMain.fibonacci
(Main.fibonacci)
//pushargument
@0
D=A
@ARG
A=D+M
D=M
@SP
M=M+1
A=M-1
M=D
//pushconstant
@2
D=A
@SP
M=M+1
A=M-1
M=D
//arithmeticlt
@SP
A=M-1
D=M
A=A-1
D=M-D
@SP
M=M-1
@Main.fibonacci$True0
D;JLT
@Main.fibonacci$False0
0;JEQ
(Main.fibonacci$True0)
@SP
A=M-1
M=-1
@Main.fibonacci$l0
0;JEQ
(Main.fibonacci$False0)
@SP
A=M-1
M=0
@Main.fibonacci$l0
0;JEQ
(Main.fibonacci$l0)
//if
@SP
AM=M-1
D=M
@Main.fibonacci$IF_TRUE
D;JNE
//goto
@Main.fibonacci$IF_FALSE
0;JEQ
(Main.fibonacci$IF_TRUE)
//pushargument
@0        
D=A
@ARG
A=D+M
D=M
@SP
M=M+1
A=M-1
M=D
//return
@LCL
D=M
@R13
M=D
@5
A=D-A
D=M
@R14
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
@ARG
D=M
@SP
M=D+1
@R13
AM=M-1
D=M
@THAT
M=D
@R13
AM=M-1
D=M
@THIS
M=D
@R13
AM=M-1
D=M
@ARG
M=D
@R13
AM=M-1
D=M
@LCL
M=D
@R14
A=M
0;JMP
(Main.fibonacci$IF_FALSE)
//pushargument
@0
D=A
@ARG
A=D+M
D=M
@SP
M=M+1
A=M-1
M=D
//pushconstant
@2
D=A
@SP
M=M+1
A=M-1
M=D
//arithmeticsub
@SP
A=M-1
D=M
A=A-1
D=M-D
@SP
M=M-1
@SP
A=M-1
M=D
//callMain.fibonacci Main.fibonacci
@Main.fibonacci$0
D=A
@SP
M=M+1
A=M-1
M=D
@LCL
D=M
@SP
M=M+1
A=M-1
M=D
@ARG
D=M
@SP
M=M+1
A=M-1
M=D
@THIS
D=M
@SP
M=M+1
A=M-1
M=D
@THAT
D=M
@SP
M=M+1
A=M-1
M=D
@SP
D=M
@1  
D=D-A
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(Main.fibonacci$0)
//pushargument
@0
D=A
@ARG
A=D+M
D=M
@SP
M=M+1
A=M-1
M=D
//pushconstant
@1
D=A
@SP
M=M+1
A=M-1
M=D
//arithmeticsub
@SP
A=M-1
D=M
A=A-1
D=M-D
@SP
M=M-1
@SP
A=M-1
M=D
//callMain.fibonacci Main.fibonacci
@Main.fibonacci$1
D=A
@SP
M=M+1
A=M-1
M=D
@LCL
D=M
@SP
M=M+1
A=M-1
M=D
@ARG
D=M
@SP
M=M+1
A=M-1
M=D
@THIS
D=M
@SP
M=M+1
A=M-1
M=D
@THAT
D=M
@SP
M=M+1
A=M-1
M=D
@SP
D=M
@1  
D=D-A
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(Main.fibonacci$1)
//arithmeticadd
@SP
A=M-1
D=M
A=A-1
D=D+M
@SP
M=M-1
@SP
A=M-1
M=D
//return
@LCL
D=M
@R13
M=D
@5
A=D-A
D=M
@R14
M=D
@SP
M=M-1
A=M
D=M
@ARG
A=M
M=D
@ARG
D=M
@SP
M=D+1
@R13
AM=M-1
D=M
@THAT
M=D
@R13
AM=M-1
D=M
@THIS
M=D
@R13
AM=M-1
D=M
@ARG
M=D
@R13
AM=M-1
D=M
@LCL
M=D
@R14
A=M
0;JMP
//funcSys.init
(Sys.init)
//pushconstant
@4
D=A
@SP
M=M+1
A=M-1
M=D
//callSys.init Main.fibonacci
@Sys.init$0
D=A
@SP
M=M+1
A=M-1
M=D
@LCL
D=M
@SP
M=M+1
A=M-1
M=D
@ARG
D=M
@SP
M=M+1
A=M-1
M=D
@THIS
D=M
@SP
M=M+1
A=M-1
M=D
@THAT
D=M
@SP
M=M+1
A=M-1
M=D
@SP
D=M
@1   
D=D-A
@5
D=D-A
@ARG
M=D
@SP
D=M
@LCL
M=D
@Main.fibonacci
0;JMP
(Sys.init$0)
(Sys.init$WHILE)
//goto
@Sys.init$WHILE              
0;JEQ
