.globl _start
.globl __start
.set noreorder
.ent _start

.text

.equ SERP_TX_ST_REG,        0xffffc008-0x100000000
.equ SERP_TX_ST_REG_READY_m,       0x1
.equ SERP_TX_ST_REG_IE_m,          0x2

.equ SERP_TX_DATA_REG,      0xffffc00c-0x100000000

.equ SPILED_REG_LED_LINE,   0xffffc104-0x100000000
.equ SPILED_REG_KNOBS_8BIT, 0xffffc124-0x100000000


__start:
_start:

loop:
	lw	$a0, SPILED_REG_KNOBS_8BIT($zero)
	sw	$a0, input($zero)
	jal	fibonacci
	nop
	sw	$v0, output($zero)
	sw	$v0, SPILED_REG_LED_LINE($zero)
	jal	serp_tx_hex
	addi	$a0, $v0, 0
	jal	serp_tx_byte
	addi	$a0, $zero, 0xa
	beq	$zero, $zero, loop
	nop

.end _start

.ent fibonacci
fibonacci:
	addi	$v0, $zero, 0
	addi	$v1, $zero, 1
L1:
	beq	$a0, $zero, L2
	addi	$a0, $a0, -1
	add	$t0, $v0, $v1
	addi	$v1, $v0, 0
	beq	$zero, $zero, L1
	addi	$v0, $t0, 0
L2:
	jr	$ra
.end fibonacci

.ent serp_tx_hex

serp_tx_hex:
	addi	$sp, $sp, -12
	sw	$ra, 0($sp)
	sw	$s0, 4($sp)
	sw	$s1, 8($sp)
	addi	$s0, $a0, 0
	addi	$s1, $0, 8
L3:	
	addi	$a0, $s0, 0
	srl	$a0, $a0, 28
	addi	$a0, $a0, 0x30
	sltiu	$t0, $a0, 0x3a
	bne	$t0, $zero, L4
	addi	$s1, $s1, -1
	addi	$a0, $a0, 0x41-0x3a
L4:
	jal	serp_tx_byte
	nop
	bne	$s1, $0, L3
	sll	$s0, $s0, 4
	lw	$ra, 0($sp)
	lw	$s0, 4($sp)
	lw	$s1, 8($sp)
	jr	$ra
	addi	$sp, $sp, 12

.end serp_tx_hex

.ent serp_tx_byte

serp_tx_byte:
	lw	$t0, SERP_TX_ST_REG($zero)
	andi	$t0, $t0, SERP_TX_ST_REG_READY_m
	beq	$t0, $zero, serp_tx_byte
	jr	$ra
	sw	$a0, SERP_TX_DATA_REG($zero)

.end serp_tx_byte

.org	0x2000
.data

input:	.word	5

output:	.word	0


