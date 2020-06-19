# $a0 is TIME's address pointer
# 10/10/2020 --> Year is 2020
Year:
	# Saving address $ra to stack
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	# Year is in TIME[6:9]
	addi $a1, $0, 6
	addi $a2, $0, 9
	jal strToNum
	# $v0 is year's number and this is a result for Year function
	
	# Restoring stack
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
	
# $a0 is TIME's address pointer
# 10/10/2020 --> 0 because 2020 is not a leap year
LeapYear:
	jal Year
	# Now, $v0 is year number
	# year is a Leap Year when year % 400 = 0 or (year % 4 == 0 && year % 100 != 0)
	addi $t0, $0, 400
	div $v0, $t0
	mfhi $t1 # $t1 = $v0 % 400
	beq $t1, $0, return_Leap_Year # t1 == 0 if v0 % 400 == 0
	
	addi $t0, $0, 4
	div $v0, $t0
	mfhi $t1 # t1 = v0 % 4
	bne $t1, $0, return_Not_Leap_Year # if year % 4 != 0 then (year % 4 == 0 && year % 100 != 0) == false
	
	addi $t0, $0, 100
	div $v0, $t0
	mfhi $t1 # t1 = v0 % 100
	
	beq $t1, $0, return_Not_Leap_Year  # if v0 % 100 == 0 then false because we had year % 4 == 0 but year % 100 == 0
	j return_Leap_Year 
	
	return_Leap_Year:
	addi $v0, $0, 1
	jr $ra	
	
	return_Not_Leap_Year
	addi $v0, $0, 0
	jr $ra
	
# $a0 is TIME's address pointer
# return char* is one element of {"Mon", "Tues", "Wed", "Thurs", "Fri", "Sat", "Sun"}
Weekday:
	# Saving to stack
	addi $sp, $sp -24
	sw $ra, 20($sp) # saving $ra
	sw $a0, 16($sp) # address of TIME's pointer
	sw $a1, 12($sp) # day
	sw $a2, 8($sp) # month
	sw $a3, 4($sp) # year
	sw $s0, 0($sp) # result for this day
	
	# get day and assign to a1
	lw $a0, 16($sp)
	jal Day
	add $a1, $0, $v0 # assign day to a1
	
	# get month and assign to a2
	lw $a0, 16($sp)
	jal Month
	add $a2, $0, $v0 # assign month to a2 
	
	# get year and assign to a3
	lw $a0, 16($sp)
	jal Year
	add $a3, $0, $v0 # assign Year to a3
	
	# check condition
	# if month < 3 then month += 12, year -= 1
	addi $t3, $0, 3 # t3 = 3
	slt $t4, $a2, $t3
	beq $t4, $0, Days_Of_The_Week # neu month >= 3
	# else if (month < 3)
	addi $a3, $a3, -1
	addi $a2, $a2, 12
	j Days_Of_The_Week
	
	Days_Of_The_Week: # days_of_the_week = (days + 2 * month + 3 * (month + 1) div 5 + year + (year div 4)) % 7
	add $s0, $0, $a1 # assign result to a1 (result = days)
	addi $t4, $0, 2 # t4 = 2
	
	mult $a2, $t4
	mflo $a1 # a1 = a2 * t4 = month * 2
	add $s0, $s0, $a1 # result = result + 2 * month
	
	addi $a2, $a2, +1 # month = month + 1
	addi $t4, $0, 3 # $t4 = 3
	mult $a2, $t4
	mflo $a2 # a2 = 3 * (month + 1)
	addi $t4, $t4, 5
	
	div $a2, $t4 # 3 * (month + 1) div 5
	mflo $a2 # a2 = 3 * (month + 1) div 5
	add $s0, $s0, $a2 # result = result + 3 * (month + 1) div 5
	
	add $s0, $s0, $a3 %# result = result + year
	
	addi $t4, $0, 4 # t4 = 4
	div $a3, $t4
	mflo $a3 # $a3 = year div 4
	
	add $s0, $s0, $a3 # result = result + (year div 4)
	
	addi $t4, $0, 7 # t4 = 7
	div $s0, $t4
	mfhi $s0 # s0 = s0 mod 7
	
	# Case of
	beq $s0, 0, Sun
	beq $s0, 1, Mon
	beq $s0, 2, Tue
	beq $s0, 3, Wed
	beq $s0, 4, Thu
	beq $s0, 5, Fri
	j Sat
	
	Sun:
		la $v0, chu_nhat
		j restore_and_exit_WeekDay
	Mon:
		la $v0, t_2
		j restore_and_exit_WeekDay
	Tue:
		la $v0, t_3
		j restore_and_exit_WeekDay
	Wed:
		la $v0, t_4
		j restore_and_exit_WeekDay
	Thu:
		la $v0, t_5
		j restore_and_exit_WeekDay
	Fri:
		la $v0, t_6
		j restore_and_exit_WeekDay
	Sat:
		la $v0, t_7
		j restore_and_exit_WeekDay
	
	restore_and_exit_WeekDay:
		lw $ra, 20($sp)
		lw $a0, 16($sp)
		lw $a1, 12($sp)
		lw $a2, 8($sp) 
		lw $a3, 4($sp) 
		lw $s0, 0($sp) 
		addi $sp, $sp +24
		jr $ra
	
	
	

# --------------------------------------- Utils function -----------------------------------------------
# $a0 is address of char's pointer
# $a1 is start index
# $a2 is end index
strToNum:
	# assign $v0 is zero
	add $v0, $0, $0
	add $t0, $a0, $a1 # starting index
	add $t1, $a0, $a2 # end index
	addi $t1, $t1, 1 # end index + 1
	strToNum_loop: # loop to get digit
		slt $t2, $t0, $t1 # if $t0 < $t1 ? 1 : 0
		beq $t2, $0, strToNum_exit # if $t0 >= $t1 then exit
		# else 
		# $v0 = $v0 * 10
		addi $t3, $0, 10
		mult $v0, $t3
		mflo $v0 # get 32-bit lowest # v0 = v0 * 10
		
		lb $t3, 0($t0) # load 1 bytes char
		addi $t3, $t3, -48 # convert to int
		add $v0, $v0, $t3 # $v0 = $v0 + $t3
		
		add $t0, $t0, +1 # increase iterator variable
		
		j strToNum_loop # continuing loop
	strToNum_exit:
	jr $ra
	
		
	
	