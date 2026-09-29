#----------------------------------------
# Compilation :
#	as -o hello_32.o hello_32.s
#	ld -o hello_32 hello_32.o
#----------------------------------------
                    .data
msg :               .asciz "Hello, World !\n"
len = 15

fic :               .asciz "fic.txt"
                    .bss
                    .text
                    .global _start

_start :
        #             movl $4,%eax
        #             movl $1,%ebx
        #             movl $msg,%ecx
        #             movl $len,%edx
        #             int  $0x80           # appel système

                    #open fic.txt
                     movl $5,%eax
                     movl $fic,%ebx
                     movl $577,%ecx
                     movl $0644,%edx
                     int  $0x80           # appel système

                    #write msg in file
                     movl %eax,%ebx
                     movl $4,%eax
                     movl $msg,%ecx
                     movl $len,%edx
                     int  $0x80           # appel système

                    #close
                     movl $6,%eax
                     movl $0,%ebx
                     int $0x80

exit :
                     movl $1,%eax
                     movl $0,%ebx
                     int  $0x80
