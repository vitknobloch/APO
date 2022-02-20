// Directives to make interresting windows visible
#pragma qtmips show registers
#pragma qtmips show memory

.globl _start
.set noat
.set noreorder

.text

_start:
addi $t0, $0,7

outer:
addi $t0, $t0, -1
la $1, 0x33C
addi $t1, $0, 692
addi $t2, $0, 0

inner:
addi $t1, $t1, -1
add $s1, $1, $t2
lw $s0, 0($s1)
bne $t1, $0, inner
addi $t2, $t2, 4

bne $t0, $0, outer
nop

loop:
	break
	j loop

.data
.org	0x2000


// Specify location to show in memory window
#pragma qtmips focus memory 0x33C