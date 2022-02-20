// bubble-sort.S file template, rename and implement the algorithm
// Test algorithm in qtmips_gui program
// Select the CPU core configuration with delay-slot
// This setups requires (for simplicity) one NOP instruction after
// each branch and jump instruction (more during lecture about pipelining)
// The code will be compiled and tested by external mips-elf-gcc
// compiler by teachers, you can try make in addition, but testing
// by internal assembler should be enough

// copy directory with the project to your repository to
// the directory work/bubble-sort
// critical is location of the file work/bubble-sort/bubble-sort.S
// which is checked by the scripts

// Directives to make interesting windows visible
#pragma qtmips show registers
#pragma qtmips show memory

.set noreorder
.set noat

.globl    array_size
.globl    array_start

.text
.globl _start
.ent _start

_start:

	la   $a0, array_start
	la   $a1, array_size
	lw   $a1, 0($a1) // number of elements in the array

loop:	
	addi $a2, $a1, -1 //set iner-loop decrementor
	addi $v1, $0, 1 //set sorted flag
	addi $a3, $a0, 0 //set current lower element pointer
	lw $s0, 0($a3) //load first element
	
bubble:
	lw $s1, 4($a3) //load next element

	slt $v0, $s0, $s1 //compare
	beq $v0, $0, else
	nop
	//lowval less than highval
	sw $s0, 0($a3)
	addi $s0, $s1, 0
	j increment
	nop

else:
	//lowval greater than highval
	sw $s1, 0($a3)
	addi $v1, $0, 0 //set sorted flag to false	

increment:
	//increment inner loop
	addi $a3, $a3, 4 //increment current element pointer
	addi $a2, $a2, -1 //decrement decrementor
	bgtz $a2, bubble
	nop
	
	//increment outer loop
	sw $s0, 0($a3) //save largest value to last index
	addi $a1, $a1, -1 //decrement outer decrementor
	bne $0, $v1, end_loop //break cycle if array is already sorted
	nop
	bgtz $a1, loop
	nop

//Final infinite loop
end_loop:
	cache 9, 0($0)  // flush cache memory
	break           // stop the simulator
	j end_loop
	nop

.end _start

.data
// .align    2 // not supported by QtMips yet

array_size:
.word	15
array_start:
.word	5, 3, 4, 1, 15, 8, 9, 2, 10, 6, 11, 1, 6, 9, 12

// Specify location to show in memory window
#pragma qtmips focus memory array_size