#----------------------------------------
# Compilation :
#	as -o hello_32.o hello_32.s
#	ld -o hello_32 hello_32.o
#----------------------------------------
                    .data
msg :               .asciz "Hello, World !\n"
len = 15
                    .bss
                    .text
                    .global _start

_start :
                     movl $4,%eax
                     movl $1,%ebx
                     movl $msg,%ecx
                     movl $len,%edx
                     int  $0x80           # appel système

exit :
                     movl $1,%eax
                     movl $0,%ebx
                     int  $0x80
