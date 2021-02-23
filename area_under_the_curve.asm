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

	li	$v0,5		# CODE FOR READING INTEGER
	syscall

	mtc1 $zero, $f20         # f20 will store the value of area and area can be a float so using a f register
	move	$s0,$v0		# a4 stores n ie the number of coordinates

	li	$v0,4		# Code for syscall: print_string
	la	$a0, newline	# new line
	syscall

	li	$v0,4
	la	$a0,msg2
	syscall

	li	$v0,5		# CODE FOR READING INTEGER
	syscall
	move	$s7,$v0		# a2 stores x coordiante

	li	$v0,4		# Code for syscall: print_string
	la	$a0, newline	# new line
	syscall

	li	$v0,4
	la	$a0,msg3
	syscall
	li	$v0,5		# CODE FOR READING INTEGER
	syscall
	move	$s6,$v0        # a3 stores y coordinate

	li	$v0,4		# Code for syscall: print_string
	la	$a0, newline	# new line
	syscall

	li	$t1,1
	li	$t9,1

loop:
	beq	$t1,$s0,exit     # if the value of t1==s0 then jump to exit
	add	$t1,$t1,$t9	# t1 = t1+1
	li	$v0,4
	la	$a0,msg2
	syscall

	li	$v0,5		# CODE FOR READING INTEGER
	syscall
	move	$s2,$v0		# t2 stores x coordiante

	li	$v0,4
	la	$a0,msg3
	syscall
	li	$v0,5		# CODE FOR READING INTEGER
	syscall
	move	$s3,$v0      # t3 stores y coordinate
	
	#mov.s $f12, $f20
	#li	$v0,2     # code used to print float
	#syscall
	sub	$s7,$s2,$s7
	slt	$t6,$s6,0
	beq	$t6,1,case1
	beq	$t6,0,if
case1:	
	slt	$t6,$s3,0
	beq	$t6,1,case2
	abs	$s6,$s6
	add	$t5,$s6,$s3
	mul	$t6,$s3,$s3
	mul	$t4,$s6,$s6
	li	$a0,2
	mul	$t5,$t5,$a0
	mul	$t4,$t4,$s7
	mul	$t6,$t6,$s7
	mtc1	$t4,$f4
	cvt.s.w $f4, $f4
	mtc1	$t6,$f6
	cvt.s.w $f6, $f6
	mtc1	$t5,$f5
	cvt.s.w $f5, $f5
	div.s	$f6,$f6,$f5
	div.s	$f4,$f4,$f5
	
	add.s	$f20,$f20,$f6
	add.s	$f20,$f20,$f4
	move	$s7,$s2		#
	move	$s6,$s3		#
	#li	$v0,4
	#la	$a0,msgcase1
	#syscall
	#mov.s $f12, $f20
	#li	$v0,2     # code used to print float
	#syscall
	j	loop		#
	
case2:
	sgt	$t4,$s6,$s3     # if s6 >s3
	li	$t6,1
	mtc1 $t6 $f3
	cvt.s.w $f3, $f3
	beq	$t4,0,else1	#  if a3 > t3 then move to else
	mul	$t5,$s7,$s6	#	find the area of lower square
	li	$t6,1
	mtc1 $t6 $f3
	cvt.s.w $f3, $f3
	mtc1	$t5,$f2		#   put the value of t5 in float regester f2
	cvt.s.w $f2, $f2
	div.s $f2 $f2 $f3
	abs.s	$f2,$f2
	add.s	$f20,$f20,$f2	#
	sub	$s6,$s3,$s6	#   find the area of the triangle the is formed on the top
	mul	$t5,$s7,$s6	#	find the area of the triangle the is formed on the top
	li	$t6,2		#
	mtc1	$t5,$f2		#
	cvt.s.w $f2, $f2
	mtc1	$t6,$f3		#
	cvt.s.w $f3, $f3
	div.s	$f2,$f2,$f3	# find the area of the triangle the is formed on the top
	abs.s	$f2,$f2
	add.s	$f20,$f20,$f2	# add the area of triangle
	move	$s7,$s2		#
	move	$s6,$s3		#
	#li	$v0,4
	#la	$a0,msgcase2
	#syscall
  	#mov.s $f12, $f20
	#li	$v0,2     # code used to print float
	#syscall
	j	loop		#

else1:	mul	$t5,$s7,$s3	#
	mtc1	$t5,$f2		#
	cvt.s.w $f2, $f2
	abs.s	$f2,$f2
	add.s	$f20,$f20,$f2	#
	sub	$s6,$s6,$s3	#
	mul	$t5,$s7,$s6	#
	li	$t6,2		#
	mtc1	$t5,$f2		#
	cvt.s.w $f2, $f2
	mtc1	$t6,$f3		#
	cvt.s.w $f3, $f3
	div.s	$f2,$f2,$f3	#
	abs.s	$f2,$f2
	add.s	$f20,$f20,$f2	#
	move	$s7,$s2		#
	move	$s6,$s3		#
	#li	$v0,4
	#la	$a0,msgelse1
	#syscall
	#mov.s $f12, $f20
	#li	$v0,2     # code used to print float
	#syscall
	j	loop		#

if2:
	
	abs	$s3,$s3
	add	$t5,$s6,$s3
	mul	$t6,$s3,$s3
	mul	$t4,$s6,$s6
	li	$a0,2
	mul	$t5,$t5,$a0
	mul	$t4,$t4,$s7
	mul	$t6,$t6,$s7
	mtc1	$t4,$f4
	cvt.s.w $f4, $f4
	mtc1	$t6,$f6
	cvt.s.w $f6, $f6
	mtc1	$t5,$f5
	cvt.s.w $f5, $f5
	div.s	$f6,$f6,$f5
	div.s	$f4,$f4,$f5
	add.s	$f20,$f20,$f6
	add.s	$f20,$f20,$f4
	neg		$s3,$s3
	move	$s7,$s2		#
	move	$s6,$s3		#
	#li	$v0,1
	#add $a0, $s7, $zero
	#syscall
	#li	$v0,1
	#add $a0, $s6, $zero
	#syscall
	#li	$v0,4
	#la	$a0,msgif2
	#syscall
	#mov.s $f12, $f20
	#li	$v0,2     # code used to print float
	#syscall
	j	loop



if:
	slt	$t4,$s6,$s3     # if s6 <t3
	sgt	$t6,$s3,0
	beq	$t6,0,if2
	beq	$t4,0,else	#  if a3 > t3 then move to else
	mul	$t5,$s7,$s6	#	find the area of lower square
	li	$t6,1
	mtc1 $t6 $f3
	cvt.s.w $f3, $f3
	mtc1	$t5,$f2		#   put the value of t5 in float regester f2
	cvt.s.w $f2, $f2
	div.s $f2 $f2 $f3
	add.s	$f20,$f20,$f2	#
	sub	$s6,$s3,$s6	#   find the area of the triangle the is formed on the top
	mul	$t5,$s7,$s6	#	find the area of the triangle the is formed on the top
	li	$t6,2		#
	mtc1	$t5,$f2		#
	cvt.s.w $f2, $f2
	mtc1	$t6,$f3		#
	cvt.s.w $f3, $f3
	div.s	$f2,$f2,$f3	# find the area of the triangle the is formed on the top
	add.s	$f20,$f20,$f2	# add the area of triangle
	move	$s7,$s2		#
	move	$s6,$s3		#
	#li	$v0,4
	#la	$a0,msgif
	#syscall
	#mov.s $f12, $f20
	#li	$v0,2     # code used to print float
	#syscall
	j	loop		#

else:	mul	$t5,$s7,$s3	#
	mtc1	$t5,$f2		#
	cvt.s.w $f2, $f2
	add.s	$f20,$f20,$f2	#
	sub	$s6,$s6,$s3	#
	mul	$t5,$s7,$s6	#
	li	$t6,2		#
	mtc1	$t5,$f2		#
	cvt.s.w $f2, $f2
	mtc1	$t6,$f3		#
	cvt.s.w $f3, $f3
	div.s	$f2,$f2,$f3	#
	add.s	$f20,$f20,$f2	#
	move	$s7,$s2		#
	move	$s6,$s3		#
	#li	$v0,4
	#la	$a0,msgelse
	#syscall
	#mov.s $f12, $f20
	#li	$v0,2     # code used to print float
	#syscall
	j	loop		#




exit:
	mov.s $f12, $f20
	li	$v0,2     # code used to print float
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
msg:	.asciiz	"Enter the value of n!\n"
msg2:   .asciiz "Enter the coordinate X  \n"
msg3:   .asciiz "Enter the coordinate Y \n"
newline: .asciiz "\n"
#msgif:	.asciiz	"if\n"
#msgif2:	.asciiz	"if2 \n"
#msgelse:	.asciiz	"else\n"
#msgelse1:	.asciiz	"else1\n"
#msgcase2:	.asciiz	"case2\n"
#msgcase1:	.asciiz	"case1\n"
