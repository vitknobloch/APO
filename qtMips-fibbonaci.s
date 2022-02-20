// Directives to make interresting windows visible
#pragma qtmips show registers
#pragma qtmips show memory

.globl _start
.set noat
.set noreorder
.ent _start

.text

_start:
	//store address in $1
	la $1, pole
	addi $6, $0, 40

big_loop:
	//set sorted flag
	addi $2, $0, 0

	addi $6, $6, -4

	add $5, $1, $6
	
	addi $3, $1, 0
	//load first member to $s0
	lw $s0, 0($1)
	
for:
	//add increment to adress
	lw $s1, 4($3)
	slt $4, $s1, $s0

	beq $4, $0, else
	nop
	//if second is smaller than first
	sw $s1, 0($3)
	addi $2, $0, 1
	j increment
	nop

else:	//if first is smaller
	sw $s0, 0($3)
	add $s0, $s1, $0

increment:
	addi $3, $3, 4
	bne $3, $5, for
	nop
	//end cycle write last number
	sw $s0, 0($3)

	bne $2, $0, big_loop
	nop


.end  _start
.data
pole: .word 11, 10, 7, 15, 9, 1, 6, 4, 14, 12
.org	0x2000



// Specify location to show in memory window
#pragma qtmips focus memory src_val
