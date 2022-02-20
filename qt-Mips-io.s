// Directives to make interresting windows visible
#pragma qtmips show registers
#pragma qtmips show memory

.globl _start
.set noat
.set noreorder

.text

_start:
la $1, 0xffffc110

addi $2, $0, 0
//red
addi $2, $2, 255
sll $2, $2, 8
//green
addi $2, $2, 15
sll $2, $2, 8
//blue
addi $2, $2, 123

sw $2, 0($1)

loop:
	break
	j loop

.data
.org	0x2000


// Specify location to show in memory window
#pragma qtmips focus memory src_val