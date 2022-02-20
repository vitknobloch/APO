/* template for own QtMips program development */

#define zero    $0
#define AT      $1
#define v0      $2
#define v1      $3
#define a0      $4
#define a1      $5
#define a2      $6
#define a3      $7

#define t0      $8
#define t1      $9
#define t2      $10
#define t3      $11
#define t4      $12
#define t5      $13
#define t6      $14
#define t7      $15
#define t8      $24
#define t9      $25
#define k0      $26
#define k1      $27

#define s0      $16
#define s1      $17
#define s2      $18
#define s3      $19
#define s4      $20
#define s5      $21
#define s6      $22
#define s7      $23

#define gp      $28
#define sp      $29
#define fp      $30
#define ra      $31

.globl _start
.globl __start
.set noat
.set noreorder
.ent _start

.text

__start:
_start:
	addi    a0, zero, 10

	// load the word from absolute address
	lw     $2, 0x2000($0)
	// store the word to absolute address
	sw     $2, 0x2004($0)

	/* space for your code */

loop:	break
        beq     zero, zero, loop
	nop

.end _start
