# All program code is placed after the
	# .text assembler directive
	.text

	# Declare main as a global function
	.globl	main
	
# The label 'main' represents the starting point
main:
	# Run the print_string syscall which has code 4
	li	$v0,4		# Code for syscall: print_string
	la	$a0, msg	# Pointer to string (load the address of msg)
	syscall
	li  $s2,48
	li $v0,8		# CODE FOR READING INTEGER
	la $a0, buffer  # load byte space into address
    	li $a1, 1002   # allot the byte space for string  
   	move $t0, $a0   # save string to t0
	syscall
	li $s0,0      #s0 will store the length of stack
	lb $t1,0($t0)
	lb  $t9, newline 
	beq $t9,$t1,null
	
loop:
	lb $t1,0($t0)
	
	addi $t0,$t0,1
	lb  $t9, newline
	beq $t9,$t1,exit
	li $t8,48
	slt $t9,$t1,$t8
	beq $t9,1,operator
	li $t8,58
	slt $t9,$t1,$t8
	beq $t9,1,operand

	j error

operand:
	
	subu $sp, $sp,4
	subu $t1,$t1,48
	#li	$v0,1		# Code for syscall: print_string
	#move	$a0, $t1	#t1 Pointer to string (load the address of msg)
	#syscall
	sw $t1,($sp)
	addi $s0,$s0,1
	j loop
operator: 
	
	#li $t8,2
	#slt $t9,$s0,$t8
	#beq $t9,1,error
	li $t9,42
	subu $s0,$s0,1
	beq $t1,$t9,multiply
	li $t9,43
	beq $t1,$t9,sum
	li $t9,45
	beq $t1,$t9,minus
	j error
minus:
	lw $t7, ($sp)
	addu $sp, $sp, 4
	lw $t6, ($sp)
	addu $sp, $sp, 4
	sub $t6,$t6,$t7
	subu $sp, $sp, 4
	sw $t6, ($sp)
	j loop
multiply:
	lw $t7, ($sp)
	addu $sp, $sp, 4
	lw $t6, ($sp)
	addu $sp, $sp, 4
	mul $t7,$t7,$t6
	subu $sp, $sp, 4
	sw $t7, ($sp)
	j loop
sum:
	#li	$v0,4		# Code for syscall: print_string
	#la	$a0, msg	# Pointer to string (load the address of msg)
	#syscall

	lw $t7, ($sp)
	addu $sp, $sp, 4
	lw $t6, ($sp)
	addu $sp, $sp, 4
	add $t7,$t7,$t6
	subu $sp, $sp, 4
	sw $t7, ($sp)
	j loop


error: 	li	$v0,4		# Code for syscall: print_string
	la	$a0, msg3	# Pointer to string (load the address of msg)
	syscall	
	li	$v0,10		# Code for syscall: exit
	syscall

null:  
	li	$v0,4		# Code for syscall: print_string
	la	$a0, msg2	# Pointer to string (load the address of msg)
	syscall	
	li	$v0,10		# Code for syscall: exit
	syscall
exit:   
	li $t8,1
	slt $t5,$s0,$t8
	beq $t5,1,error
	li $t8,1
	sgt $t5,$s0,$t8
	beq $t5,1,error
	
	lw $t7, ($sp)
	addu $sp, $sp, 4
	li $v0, 1
	move $a0,$t7
	syscall
	li	$v0,4		# Code for syscall: print_string
	la	$a0, newline	# Pointer to string (load the address)
	syscall	
	li	$v0,10		# Code for syscall: exit
	syscall
	li	$v0,10		# Code for syscall: exit
	syscall

	# All memory structures are placed after the
	# .data assembler directive
	.data

	# The .asciiz assembler directive creates
	# an ASCII string in memory terminated by
	# the null character. Note that strings are
	# surrounded by double-quotes
msg:	.asciiz	"Enter the string!\n"
msg2:   .asciiz "“Error empty string ...Please run again and enter a postfix expression  \n"
msg3:   .asciiz "“Invalid postfix expression...Please run again and enter a valid postfix expression\n"
buffer: .space 1002
newline: .asciiz "\n"
zero : .asciiz "0"
