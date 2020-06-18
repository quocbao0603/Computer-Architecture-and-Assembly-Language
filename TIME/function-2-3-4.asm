.data
	m_1:
		.asciiz "January"
	m_2:
		.asciiz "February"
	m_3:
		.asciiz "March"
	m_4:
		.asciiz "April"
	m_5:
		.asciiz "May"
	m_6:
		.asciiz "June"
	m_7:
		.asciiz "July"
	m_8:
		.asciiz "August"
	m_9:
		.asciiz "September"
	m_10:
		.asciiz "October"
	m_11:
		.asciiz "November"
	m_12:
		.asciiz "December"
	
	tmp_str:
		.space 1024
	date_1:
		.space 1024
	date_2:
		.space 1024
	
.text	
main:
	la $a0, date_1
	addi $a1, $0, 1024
	addi $v0, $0, 8
	syscall
	jal isValid
	j Out
	
	


#Parameter:
#a0 (int): day
#a1 (int): month
#a2 (int): year
#a3 (char*): DD/MM/YYYY
#Get time string from 3 int parameters.	
#Return: 	$v0: current address of TIME string.
#		If this string is UNVALID, return $v0 = 0.
Date:
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	la $a3, date_1
	
	addi $t0, $0, 10 #Asign t0 = 10
	addi $t3, $0, 47 #Get the '/' char.
	
	#Get DAY and assign to a3.
	div $a0, $t0 # 
	mflo $t1 #Get the first digit of DAY.
	mfhi $t2 #Get the second digit of DAY.
	addi $t1, $t1, 48 #Convert int to char.
	addi $t2, $t2, 48 #Convert int to char.
	sb $t1, 0($a3) #Assign 1st char to a3.
	sb $t2, 1($a3) #Assign 2nd char to a3.
	sb $t3, 2($a3) #Assign 3rd char ("/") to a3.
	
	#-------------------------------
	#Get MONTH and assign to a3.
	div $a1, $t0 # 
	mflo $t1 #Get the first digit of MONTH.
	mfhi $t2 #Get the second digit of MONTH.
	addi $t1, $t1, 48 #Convert int to char.
	addi $t2, $t2, 48 #Convert int to char.
	sb $t1, 3($a3) #Assign 4th char to a3.
	sb $t2, 4($a3) #Assign 5th char to a3.
	sb $t3, 5($a3) #Assign 6th char ("/") to a3.
	
	#-------------------------------
	#Get YEAR and assign to a3.
	#Get last digit.
	div $a2, $t0
	mflo $a2
	mfhi $t1
	addi $t1, $t1, 48 #Convert int to char.
	sb $t1, 9($a3)
	
	#Get 3rd digit.
	div $a2, $t0
	mflo $a2
	mfhi $t1
	addi $t1, $t1, 48 #Convert int to char.
	sb $t1, 8($a3)
	
	#Get 2nd digit.
	div $a2, $t0
	mflo $a2
	mfhi $t1
	addi $t1, $t1, 48 #Convert int to char.
	sb $t1, 7($a3)
	
	#Get 1st digit.
	div $a2, $t0
	mfhi $t1
	addi $t1, $t1, 48 #Convert int to char.
	sb $t1, 6($a3)
	
	sb $0, 10($a3)	#Assign end of string ("/0").
	
	add $a0, $a3, $0
	jal isValid
	lw $a0, 4($sp)
	lw $ra, 0($sp)
	addi $sp, $sp, 8
	beq $v0, $0, Date_Invalid
	add $v0, $0, $a3
	jr $ra
	Date_Invalid:
		add $v0, $0, $0
		jr $ra

Convert:
	
	#Get type
	addi $t0, $0, 67
	beq $a1, $t0, Convert_C #Jump to convert C if type == 'C'
	addi $t0, $0, 66
	beq $a1, $t0, Convert_B #Jump to convert_B if type == 'B'
	j Convert_A #Jump to convert_A
	
	Convert_A:
		lb $t0, 0($a0) #Get 1st char.
		lb $t1, 1($a0) #Get 2nd char.
		lb $t2, 3($a0) #Get 3rd char.
		lb $t3, 4($a0) #Get 4th char.
		
		#Swap DAY and MONTH
		sb $t2, 0($a0)
		sb $t3, 1($a0)
		sb $t0, 3($a0)
		sb $t1, 4($a0)
		
		j convert_out
	
	Convert_B:
		addi $sp, $sp ,-28
		sw $ra, 0($sp)
		sw $a0, 4($sp)
		sw $a1, 8($sp)
		sw $a2, 12($sp)
		sw $a3, 16($sp)
		
		lb $t0, 3($a0) #Get month
		lb $t1, 4($a0) #.........
		addi $t0, $t0, -48 #Char to int
		addi $t1, $t1, -48 #Char to int
		addi $t2, $2, 10 #Assign 10 to t4
		mult $t0, $t2
		mflo $t0
		add $t0, $t0, $t1 #Get the MONTH (int).
		add $a0, $t0, $0
		jal MonthName
		sw $v0, 20($sp) #Save month to stack.
		la $t0, tmp_str #Load tmp string to t0
		
		#Space character.
		addi $t1, $0, 32 
		sb $t1, 0($t0)
		
		#Get day char and assign to t0.
		lw $a0, 4($sp)
		lb $t1, 0($a0) 
		sb $t1, 1($t0)
		lb $t1, 1($a0)
		sb $t1, 2($t0)
		
		# Assing "," to $t0
		addi $t1, $0, 44 
		sb $t1, 3($t0) 
		
		#Space character.
		addi $t1, $0, 32 
		sb $t1, 4($t0)
		
		#Get YEAR and assign to t0.
		lb $t1, 6($a0) 
		sb $t1, 5($t0)
		lb $t1, 7($a0)
		sb $t1, 6($t0)
		lb $t1, 8($a0)
		sb $t1, 7($t0)
		lb $t1, 9($a0)
		sb $t1, 8($t0)
		
		sw $t0, 24($sp)
		
		#-----------
		#Assign MONTH to Sa0.
		lw $a1, 20($sp)
		addi $a2, $0, 0
		addi $a3, $0, 10
		jal copy
		
		#Assign DAY, YEAR to Sa0.
		lw $a1, 24($sp)
		addi $a2, $0, 0
		addi $a3, $0, 8
		jal join
		lw $ra, 0($sp)
		lw $a0, 4($sp)
		lw $a1, 8($sp)
		lw $a2, 12($sp)
		lw $a3, 16($sp)
		addi $sp, $sp, 28
		
		j convert_out
	
	Convert_C:
		addi $sp, $sp ,-28
		sw $ra, 0($sp)
		sw $a0, 4($sp)
		sw $a1, 8($sp)
		sw $a2, 12($sp)
		sw $a3, 16($sp)
		
		lb $t0, 3($a0) #Get month
		lb $t1, 4($a0) #.........
		addi $t0, $t0, -48 #Char to int
		addi $t1, $t1, -48 #Char to int
		addi $t2, $2, 10 #Assign 10 to t4
		mult $t0, $t2
		mflo $t0
		add $t0, $t0, $t1 #Get the MONTH (int).
		add $a0, $t0, $0
		jal MonthName
		sw $v0, 20($sp) #Save month to stack.
		la $t0, tmp_str #Load tmp string to t0
		
		#Get day char and assign to t0.
		lw $a0, 4($sp)
		lb $t1, 0($a0) 
		sb $t1, 0($t0)
		lb $t1, 1($a0)
		sb $t1, 1($t0)
		
		#Space character.
		addi $t1, $0, 32 
		sb $t1, 2($t0)
		
		# Assing "," to $t0
		addi $t1, $0, 44 
		sb $t1, 3($t0) 
		
		#Space character.
		addi $t1, $0, 32 
		sb $t1, 4($t0)
		
		#Get YEAR and assign to t0.
		lb $t1, 6($a0) 
		sb $t1, 5($t0)
		lb $t1, 7($a0)
		sb $t1, 6($t0)
		lb $t1, 8($a0)
		sb $t1, 7($t0)
		lb $t1, 9($a0)
		sb $t1, 8($t0)
		
		sw $t0, 24($sp)
		
		#-----------
		#Assign MONTH to Sa0.
		lw $a1, 24($sp)
		addi $a2, $0, 0
		addi $a3, $0, 2
		jal copy
		
		#Assign DAY, YEAR to Sa0.
		lw $a1, 20($sp)
		addi $a2, $0, 0
		addi $a3, $0, 10
		jal join
		
		lw $a1, 24($sp)
		addi $a2, $0, 3
		addi $a3, $0, 8
		jal join
		
		lw $ra, 0($sp)
		lw $a0, 4($sp)
		lw $a1, 8($sp)
		lw $a2, 12($sp)
		lw $a3, 16($sp)
		addi $sp, $sp, 28
		
		j convert_out
	convert_out:
		jr $ra		
		
		
		
#Get string type of month.
MonthName:
	beq $a0, 1, MN_1
	beq $a0, 2, MN_2
	beq $a0, 3, MN_3
	beq $a0, 4, MN_4
	beq $a0, 5, MN_5
	beq $a0, 6, MN_6
	beq $a0, 7, MN_7
	beq $a0, 8, MN_8
	beq $a0, 9, MN_9
	beq $a0, 10, MN_10
	beq $a0, 11, MN_11
	beq $a0, 12, MN_12
	
	MN_1:
		la $v0, m_1
		jr $ra
	MN_2:
		la $v0, m_2
		jr $ra
	MN_3:
		la $v0, m_3
		jr $ra
	MN_4:
		la $v0, m_4
		jr $ra
	MN_5:
		la $v0, m_5
		jr $ra
	MN_6:
		la $v0, m_6
		jr $ra
	MN_7:
		la $v0, m_7
		jr $ra
	MN_8:
		la $v0, m_8
		jr $ra
	MN_9:
		la $v0, m_9
		jr $ra
	MN_10:
		la $v0, m_10
		jr $ra
	MN_11:
		la $v0, m_11
		jr $ra
	MN_12:
		la $v0, m_12
		jr $ra
		
#Copy string from $a1 to $a0
#$a2: start position of $a1
#$a3: end position of $a1
copy:
	addi $t0, $0, 0 #i
	addi $t1, $a2, 0 #j
	copy_loop:
		add $t2, $a1, $t1 #Get address of a1[j]
		lb $t3, 0($t2) #Get a1[j]
		add $t2, $a0, $t0 #Get address of a0[i]
		sb $t3, 0($t2) #Assign a0[i] = a1[j]
		beq $t3, $0, copy_exit #Exit if a1[j] == '\0'
		beq $a3, $t1, copy_assign_eos #Exit if j = $a3
		addi $t0, $t0, 1 #i = i+1
		addi $t1, $t1, 1 #j = j+1
		j copy_loop
	copy_assign_eos: #Assign '\0' to the end of string $a0.
		addi $t0, $t0, 1 #i = i+1
		add $t1, $a0, $t0
		sb $0, 0($t1)
	copy_exit:
		jr $ra

#Join string $a1 to $a0:
#$a2: start position of $a1
#$a3: end position of $a1
join:
	addi $t0, $0, 0 #Iterative var for a0 (i).
	addi $t1, $a2, 0 #Iterative var for a1 (j).
	join_loop_a0:
		add $t2, $a0, $t0 #Get address of a0[i]
		lb $t3, 0($t2) #Get a0[i]
		beq $t3, $0, join_loop_a1 #If a0[i] == '\0'
		addi $t0, $t0, 1 #i = i + 1
		j join_loop_a0 #Loop
	join_loop_a1:
		add $t3, $a1, $t1 #Get address of a1[j]
		lb $t4, 0($t3) #Get a1[j]
		add $t2, $a0, $t0 #Get address of a0[i]
		sb $t4, 0($t2) #a0[i] = a1[i]
		beq $t4, $0, join_out #If a[1] == '\0'
		beq $a3, $t1, join_assign_eos #If j == a3
		addi $t0, $t0, 1 #i = i+1
		addi $t1, $t1, 1 #j = j+1
		j join_loop_a1
	join_assign_eos:#Assign '\0' to the end of string $a0.
		addi $t0, $t0, 1 #i = i+1
		add $t1, $a0, $t0
		sb $0, 0($t1)
	join_out:
		jr $ra

#Check the validation of date was inputted.
#Parameter:	$a0: DATE
#Return: 	0: invalid
#		1: valid
	
isValid:
	addi $sp, $sp, -8
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	
	#Get DAY
	jal Day
	add $t0, $v0, $0
	
	#Get MONTH
	#jal Month
	add $t1, $v0, $0
	
	#Get YEAR
	#jal Year
	add $t2, $v0, $0
	
	addi $t4, $0, 1900
	#If YEAR < 1900
	slt $t5, $t2, $t4
	bne $t5, $0, isValid_inValid
	
	#Get is LeapYEAR
	#jal LeapYear
	add $t3, $v0, $0
	
	#If MONTH = {1,3,5,7,8,10,12}
	addi $t4, $0, 1
	beq $t1, $t4, isValid_31
	addi $t4, $0, 3
	beq $t1, $t4, isValid_31
	addi $t4, $0, 5
	beq $t1, $t4, isValid_31
	addi $t4, $0, 7
	beq $t1, $t4, isValid_31
	addi $t4, $0, 8
	beq $t1, $t4, isValid_31
	addi $t4, $0, 10
	beq $t1, $t4, isValid_31
	addi $t4, $0, 12
	beq $t1, $t4, isValid_31
	
	#If MONTH = 2
	addi $t4, $0, 2
	beq $t1, $t4, isValid_Feb
	
	#If MONTH = {4,6,9,11}
	addi $t4, $0, 4
	beq $t1, $t4, isValid_30
	addi $t4, $0, 6
	beq $t1, $t4, isValid_30
	addi $t4, $0, 9
	beq $t1, $t4, isValid_30
	addi $t4, $0, 11
	beq $t1, $t4, isValid_30
	
	isValid_31:
		addi $t4, $0, 31
		#If DAY > 31
		slt $t5, $t4, $t0
		bne $t5, $0, isValid_inValid
		j isValid_Valid
	isValid_30:
		addi $t4, $0, 30
		#If DAY > 30
		slt $t5, $t4, $s0
		bne $t5, $0, isValid_inValid
		j isValid_Valid
	isValid_Feb:
		addi $t4, $t3, 28
		#If DAY > 28 or 29(NON-LEAP YEAR or LEAP YEAR)
		slt $t5, $t4, $s0
		bne $t5, $0, isValid_inValid
		j isValid_Valid
	isValid_inValid:
		addi $v0, $0, 0
		j isValid_out
	isValid_Valid:
		addi $v0, $0, 1
		j isValid_out
	isValid_out:
		lw $ra, 0($sp)
		lw $a0, 4($sp)
		addi $sp, $sp, 8
		jr $ra
		
Day:
	lb $t0, 0($a0)
	lb $t1, 1($a0)
	addi $t0, $t0, -48
	addi $t1, $t1, -48
	addi $t2, $0, 10
	mult $t0, $t2
	addi $v0, $0, 0
	mflo $v0
	add $v0, $v0, $t1
	jr $ra
	 
	
Out:
	addi $v0, $0, 10
	syscall
	
