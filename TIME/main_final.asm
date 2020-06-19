.data
	#Bien tam
	tmp_str:
		.space 1024
	# ==============================================#
	#	MESSENGER: DU LIEU INPUT	   	#
	# ==============================================#
	TIME: #bien luu chuoi ngay thang nam
		.space 1024 
	TIME_2: 
		.space 1024 
	inputString: #bien luu chuoi nhap vao
		.space 1024

	inputMsg_day: 
		.asciiz "Nhap ngay DAY: "
	inputMsg_month: 
		.asciiz "Nhap thang MONTH: "
	inputMsg_year: 
		.asciiz "Nhap nam YEAR: "
	inputMsg_Invalid:
		.asciiz "Du lieu khong hop le. Moi nhap lai.\n"
	inputMsg_time2:
		.asciiz "Nhap chuoi TIME_2:\n"
		
	# ==============================================#
	# 	MESSENGER: MENU LUA CHON		#	
	# ==============================================#
	separateMsg:
		.asciiz "\n--------------------------------------------------\n"
	optionsMenu:
		.asciiz "----Ban hay chon 1 trong cac thao tac duoi day----\n"
	option1Msg:
		.asciiz "1. Xuat chuoi TIME theo dinh dang DD/MM/YYYY\n"
	option2Msg:
		.asciiz "2. Xuat chuoi TIME thanh mot trong cac dinh dang sau\n   A. MM/DD/YYYY\n   B. Month DD, YYYY\n   C. DD Month, YYYY\n"

		type_of_option2:
			.asciiz "Chon dinh dang (A, B, C): "
		convert_illegal_Msg:
			.asciiz "Lua chon khong hop le (khong phai A, B hay C).\n"
		# luu chuoi moi theo cac dinh dang
		tmp_1: 
			.space 1024
		tmp_2: 
			.space 1024

	option3Msg:
		.asciiz "3. Cho biet ngay vua nhap la thu may trong tuan:\n"
	option4Msg:
		.asciiz "4. Kiem tra nam trong chuoi TIME co phai la nam nhuan khong\n"

		is_LeapYear:
			.asciiz "La nam nhuan.\n"
		is_not_LeapYear:
			.asciiz "Khong la nam nhuan.\n"

	option5Msg:
		.asciiz "5. Cho biet khoang thoi gian giua chuoi TIME_1 va TIME_2\n"
	option6Msg:
		.asciiz "6. Cho biet 2 nam nhuan gan nhat voi nam trong chuoi TIME\n"

	# ==============================================#
	# 		MESSAGE RESULT			#
	# ==============================================#
	selectOptionMsg:
		.asciiz "Lua chon: "
	resultMsg: 	
		.asciiz "Ket qua: "
	invalidOptionMsg:
		.asciiz "Lua chon khong hop le. Moi chon lai.\n"
	DoUWantToContinueMsg:
		.asciiz "\nTiep tuc chuong trinh? (1: Co/ 0: Khong)\nLua chon: "

	# ==============================================#
	# 		CONSTANCT: TEN THANG		#
	# ==============================================#
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


	# ==============================================#
	# 		CONSTANCT: TEN THU		#
	# ==============================================#
	chu_nhat:
		.asciiz "Sunday"
	t_2:
		.asciiz "Monday"
	t_3:
		.asciiz "Tuesday"
	t_4:
		.asciiz "Wednesday"
	t_5:
		.asciiz "Thusday"
	t_6:
		.asciiz "Friday"
	t_7:
		.asciiz "Saturday"
	

	#______DU LIEU OUTPUT______
	# ==============================================#
	# 		MESSENGER: OUTPUT		#
	# ==============================================#
	outputMsg_CloserLeapYear:
		.asciiz "Hai nam nhuan (>= 1900) gan nhat la: "
	outputMsg_CloserLeapYear_and:
		.asciiz " and "
	outputMsg_GetDistanceTime:
		.asciiz "Khoang cach giua 2 khoang thoi gian (nam): "
	
.text:
# ==============================================#
#	GUI: MENU & NHAP DU LIEU		#
# ==============================================#
main:	
	la $a0, TIME      		# load address of TIME into $a0
	la $a1, inputString 		# load address of inputString  into $a1
	jal inputData 			#ham nhap du lieu v0: TIME, 
	slti $t1, $v1, 4
	beq $t1, 1, read_input_again 	#neu v1 = 4 thi hop le, nguoc lai k thoa 1 trong 1 dk => k hop le
	add $s0, $v0, $0 		#s0 luu dia chi TIME
	j printMenu
	
read_input_again: 			#yeu cau nhap lai du lieu
	la $a0, inputMsg_Invalid
	addi $v0, $0, 4  	
	syscall
	j main 		 		

printMenu:
	# xuat ra man hinh cac lua chon:
	addi $v0, $0, 4	

	la $a0, optionsMenu	
	syscall
	la $a0, option1Msg	
	syscall
	la $a0, option2Msg
	syscall
	la $a0, option3Msg
	syscall
	la $a0, option4Msg
	syscall
	la $a0, option5Msg
	syscall
	la $a0, option6Msg	
	syscall
	la $a0, separateMsg
	syscall
	j chooseSelectionMenu

chooseSelectionMenu:	
	la $a0, selectOptionMsg 
	syscall
	
	addi $v0, $0, 8	
	la $a0, inputString	
	addi $a1, $0, 1024 	
	syscall

	jal isValidNumber
	beq $v0, 0, invalidOption
	jal toInt			#v0 = toInt(a0)
	#kiem tra lua chon co nam trong khoang tu 1->6 hay khong? 
	
	slti $t0, $v0, 1		#t0 = (v0 < 1)
	beq $t0, 1, invalidOption 	#v0 < 1 =>invalid
	
	slti $t0, $v0, 7
	beq $t0, 0, invalidOption	#t0 = 0 => !(v0 < 7) => v0 > 6
	add $a0, $v0, $0
	j solveWithOption

invalidOption:
	addi $v0, $0, 4 		#syscall print = 4
	la $a0, invalidOptionMsg	
	syscall
	j chooseSelectionMenu

solveWithOption:
	beq $a0, 1, solve_option1
	beq $a0, 2, solve_option2
	beq $a0, 3, solve_option3
	beq $a0, 4, solve_option4
	beq $a0, 5, solve_option5
	beq $a0, 6, solve_option6
	j endProgram
	
continueMenu:
	la $a0, DoUWantToContinueMsg
	addi $v0, $0, 4
	syscall
	
	la $a0, inputString
	addi $a1, $0, 1024 	
	addi $v0, $0, 8
	syscall
	
	jal isValidNumber
	beq $v0, 0, invalidContinueOption
	jal toInt
	beq $v0, 0, endProgram		#ko tiep tuc -> thoat ctrinh
	beq $v0, 1, continueProgram	#tiep tuc
	j invalidContinueOption


invalidContinueOption:
	addi $v0, $0, 4
	la $a0, invalidOptionMsg
	syscall
	j continueMenu

continueProgram:
	la $a0, separateMsg
	addi $v0, $0, 4
	syscall
	j main

endProgram: 
	addi $v0, $0, 10
	syscall

solve_option1:
	#Gui thong diep ket qua
	addi $v0, $0, 4
	la $a0, resultMsg	
	syscall
	
	add $a0, $s0, $0	#$s0 hien tai luu TIME
	addi $v0, $0, 4
	syscall
	j continueMenu


solve_option2:
	# lua chon dinh dang can xu ly (A,B hay C)
	addi $v0, $0, 4 # in chuoi lua chon
	la $a0, type_of_option2
	syscall

	addi $v0, $0, 8 
	la $a0, inputString	# doc chuoi ($a0 = type (A, B hay C))
	addi $a1, $0, 1024 
	syscall

	# chuyen dinh dang
	add $a1, $0, $a0	#luu lua chon vao $a1
	add $a0, $0, $s0 	# $s0: TIME
	jal Convert

	beq $v1, 0, continueMenu 	#lua chon ko hop le -> ko chuyen doi dc

	# in ra dinh dang da duoc chuyen doi
	addi $v0, $0, 4
	la $a0, resultMsg	
	syscall
	
	add $a0, $0, $s0
	addi $v0, $0, 4
	syscall
	j continueMenu

solve_option3:
	add $a0, $s0, $0
	jal Weekday
	
	#in thu cua ngay vua nhap
	add $t0, $0, $v0
	addi $v0, $0, 4
	la $a0, resultMsg	
	syscall
	
	add $a0, $0, $t0
	addi $v0, $0, 4 
	syscall
	j continueMenu

solve_option4:
	add $a0, $s0, $0
	jal LeapYear
	bne $v0, $0, solve_4_LeapYear	#la nam nhuan
	
	la $a0, resultMsg
	addi $v0, $0, 4 
	syscall				#xuat thong diep
	la $a0, is_not_LeapYear
	addi $v0, $0, 4 		#la nam k nhuan
	syscall				#xuat thong diep
	j continueMenu

	solve_4_LeapYear:
		la $a0, resultMsg
		addi $v0, $0, 4	
		syscall
	
		la $a0, is_LeapYear
		addi $v0, $0, 4
		syscall
		j continueMenu

solve_option5:
#s1 luu chuoi TIME_2
	la $a0, inputMsg_time2
	addi $v0, $0, 4
	syscall

	la $a0, TIME_2
	la $a1, inputString
	jal inputData

	slti $t0, $v1, 4
	beq $t0, 1, input_again2 	#neu v1 < 4 -> ko hop le
	
	add $s1, $v0, $0 		#s1 luu TIME_2
	
	la $a0, resultMsg
	addi $v0, $0, 4
	syscall
	la $a0, outputMsg_GetDistanceTime
	addi $v0, $0, 4
	syscall


	add $a0, $0, $s0
	add $a1, $0, $s1
	jal GetTime
	add $a0, $0, $v0	# Lay khoang cach luu vao $a0
	addi $v0, $0, 1	# syscall print int
	syscall

	j continueMenu
	
	input_again2: 
		la $a0, inputMsg_Invalid
		addi $v0, $0, 4  	
		syscall
		j solve_option5
		
solve_option6:
	la $a0, resultMsg
	addi $v0, $0, 4	
	syscall
	la $a0, outputMsg_CloserLeapYear
	addi $v0, $0, 4		# syscall print string
	syscall

	add $a0, $0, $s0	# get TIME
	jal Leap_Year_Closer
	add $a0, $0, $v0	# get nam nhuan 1
	addi $v0, $0, 1 	# syscall print int
	syscall

	la $a0, outputMsg_CloserLeapYear_and
	addi $v0, $0, 4 #syscall print string
	syscall

	add $a0, $0, $v1	# get nam nhuan 2
	addi $v0, $0, 1		# syscall print int
	syscall

	j continueMenu
# ==============================================#
#Ham nhap du lieu				#
#INPUT: 					#
#OUTPUT: v0: (dia chi) chuoi TIME		#
#	 v1 = 4: hop le; < 4: ko hop le		#
# ==============================================#
inputData: 
	addi $sp, $sp, -28
	sw $ra, 24($sp)
	sw $a0, 20($sp)
	sw $a1, 16($sp)

	add $v1, $0, $0	

	# ============================================
	#Nhap ngay
	la $a0, inputMsg_day	#xuat msg ra man hinh
	addi $v0, $0, 4	
	syscall
	lw $a0, 16($sp)		#a0 = inputString
	addi $a1, $0, 1024	
	addi $v0, $0, 8		#syscall 8: readstring
	syscall			
	jal isValidNumber	
	add $v1, $v1, $v0 	
	lw $a0, 16($sp)		
	jal toInt		#chuyen ngay sang int
	sw $v0, 12($sp)		#luu ngay vao stack

	# ============================================
	#Nhap thang
	la $a0, inputMsg_month
	addi $v0, $0, 4	
	syscall
	lw $a0, 16($sp)		
	addi $a1, $0, 1024 	
	addi $v0, $0, 8	
	syscall
	jal isValidNumber 	
	add $v1, $v1, $v0	
	lw $a0, 16($sp)		
	jal toInt		#chuyen thang sang int
	sw $v0, 8($sp) 		#luu thang vao stack

	# ============================================
	#Nhap nam
	la $a0, inputMsg_year
	addi $v0, $0, 4	
	syscall
	lw $a0, 16($sp) 	
	addi $a1, $0, 1024 	
	addi $v0, $0, 8 	
	syscall
	jal isValidNumber 	
	add $v1, $v1, $v0	
	lw $a0, 16($sp) 	
	jal toInt		#chuyen nam sang int
	sw $v0, 4($sp) 		#luu nam vao stack
	
	#neu hop le v1 = 3 < 4
	#syntax ko hop le -> return
	slti $t0, $v1, 4	#t0 = (v1 < 4)
	beq $t0, 0, inputDate_return

	#syntax hop le -> chuyen sang dang chuan DD/MM/YYYY
	lw $t0, 12($sp)		#ngay
	lw $t1, 8($sp)		#thang
	lw $t2, 4($sp) 		#nam
	lw $t3, 20($sp) 	#TIME

	add $a0, $t0, $0
	add $a1, $t1, $0
	add $a2, $t2, $0
	add $a3, $t3, $0

	sw $v1, 0($sp)
	jal ConvertToTIME
	
	lw $t0, 0($sp)
	add $v1, $v1, $t0
	j inputDate_return

inputDate_return:
	lw $ra, 24($sp)
	addi $sp, $sp, 28
	jr $ra

#===============================================================#
#		SOLVE OPTION 1					#
#Ham tra ve chuoi ngay thang nam dang chuan DD/MM/YYYY		#
#INPUT: a0,a1,a2: ngay thang nam (int)				#
#	a3: TIME						#
#	a0,a1,a2,a3 co the bi doi trong ham nay			#
#OUTPUT: v0 = TIME dang chuan DD/MM/YYYY			#
#	 v1: tinh hop le (1: hop le, 0: ko hop le)		#
#===============================================================#
ConvertToTIME:
	addi $sp, $sp, -4
	sw $ra, 0($sp)

	jal isValidDate
	add $v1, $v0, $0
	beq $v1, 0, ConvertToTIME_return	#v1 = 0 -> ngay ko hop le -> return
	
	#Ngay hop le -> chuyen sang dang chuan DD/MM/YYYY
	addi $t0, $0, 47		#t0 = 47 = '/'

	#a0 -> DD
	addi $t1, $0, 10		#t1 = 10
	div $a0, $t1			
	mflo $t2			#t2 => 		DAY / 10
	mfhi $a0			#a0 = a0 % 10=> DAY % 10
	
	#to char
	addi $t2, $t2, 48		
	addi $a0, $a0, 48		
	
	sb $t2, 0($a3)			#TIME[0] = DAY / 10
	sb $a0, 1($a3)			#TIME[1] = DAY % 10
	sb $t0, 2($a3)			#TIME[2] = '/'

	#a1 -> MM
	addi $t1, $0, 10		#t1 = 10
	div $a1, $t1
	mflo $t2			#t2 =>		MONTH / 10
	mfhi $a1			#a1 = a1 % 10=> MONTH % 10
	
	#to char
	addi $t2, $t2, 48		
	addi $a1, $a1, 48
			
	sb $t2, 3($a3)			#TIME[3] = MONTH / 10
	sb $a1, 4($a3)			#TIME[4] = MONTH % 10
	sb $t0, 5($a3)			#TIME[5] = '/'

	#a2 -> YYYY
	addi $t1, $0, 1000
	div $a2, $t1
	mflo $t2			#t2 = YEAR / 1000
	mfhi $a2			#a2 = a2 % 1000 => YEAR = YEAR % 1000
	addi $t2, $t2, 48		#to char
	sb $t2, 6($a3)			#TIME[6] 

	addi $t1, $0, 100
	div $a2, $t1
	mflo $t2			#t2 = YEAR / 100
	mfhi $a2			#a2 = a2 % 100  => YEAR = YEAR % 100
	addi $t2, $t2, 48		#to char
	sb $t2, 7($a3)			#TIME[7]

	addi $t1, $0, 10
	div $a2, $t1
	mflo $t2			#t2 = YEAR / 10
	mfhi $a2			#a2 = a2 % 10 => YEAR = YEAR % 10
	addi $t2, $t2, 48		#to char
	addi $a2, $a2, 48		#to char
	sb $t2, 8($a3)			#TIME[8] 
	sb $a2, 9($a3)			#TIME[9]
	sb $0, 10($a3)			#TIME[10] = '\0'
	
	ConvertToTIME_return:
		add $v0, $0, $a3	#v0 luu dia chi TIME
		lw $ra, 0($sp)
		addi $sp, $sp, 4
		jr $ra




	
#Ham kiem tra cua syntax
#INPUT: a0: string, ko bi thay doi gia tri trong ham nay
#OUTPUT: v0 = 1 => hop le: gom cac chu so tu 0-9
isValidNumber:
	add $t0, $0, $a0 				#t0 = i
	add $v0, $0, 1					#v0 = 1 => mac dinh la hop le
	
	isValidNumber_loop:
		lb $t1, 0($t0)				#t1 = p[i]
		
		addi $t2, $0, 0				#t2 = '\0'
		beq $t1, $t2, toInt_return		#p[i] = '\0' -> break
		addi $t2, $0, 10 			#t2 = 10 => '\n'	
		beq $t1, $t2, isValidNumber_return 	#p[i] = '\n' -> break
		
		
		slti $t3, $t1, 48			#if t1 = '0' (48 = '0')
		bne $t3, $0, isValidNumber_return_false	#p[i] < '0' -> return false
		slti $t3, $t1, 58			#t3 = (t1 < 58) 58 > 57 = '9'
		beq $t3, $0, isValidNumber_return_false	#t3 = 0 => p[i] > '9' -> return false
		
		addi $t0, $t0, 1			#i++
		j isValidNumber_loop
	
	isValidNumber_return_false:
		add $v0, $0, $0				# $v0 = 0, khong hop le
		j isValidNumber_return
	
	isValidNumber_return:
		jr $ra

	
#Ham String to Num
#INPUT: a0 (hop le, k bi doi trong ham nay)
#OUTPUT: v0 = int(a0)
toInt:
	add $v0, $0, $0			#v0 = res		
	add $t0, $0, $a0		#t0 = i	
toInt_loop:
	lb $t1, 0($t0)			#t1 = p[i]
	
	addi $t2, $0, 0			#t2 = '\0'
	beq $t1, $t2, toInt_return	#p[i] = '\0' -> return	
	
	addi $t2, $0, 10		#t2 = '\n'
	beq $t1, $t2, toInt_return	#p[i] = '\n' -> return
	
	
	#res = res*10 + int(p[i])
	mult $v0, $t2
	mflo $v0			#res = res * 10
	addi $t1, $t1, -48		#p[i] to int
	add $v0, $v0, $t1		#res += p[i]
	
	add $t0, $t0, 1			#i++
	j toInt_loop
	
toInt_return:
	jr $ra


Month: # MM trong chuoi TIME -> (int)MM
	# Saving address $ra to stack
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	# Month is in TIME[3:4]
	addi $a1, $0, 3
	addi $a2, $0, 4
	jal strToNum
	# $v0 is Month's number and this is a result for Month function
	
	# Restoring stack
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra
#Ham tinh khoang cach nam giua 2 chuoi TIME
#INPUT: a0: TIME_1, a1:TIME_2 and a0 > a1
#OUPUT: v0 (int): distance_year
SubYear:
	# save into stack
	addi $sp, $sp, -36
	sw $ra, 32($sp)
	sw $a0, 28($sp)
	sw $a1, 24($sp)

	# save TIME_1
	jal Year
	sw $v0, 20($sp)		# save Year(TIME_1)
	jal Month
	sw $v0, 16($sp)		# save Month(TIME_1)
	jal Day
	sw $v0, 12($sp)		# save Day(TIME_1)

	# save TIME_2
	lw $a0, 24($sp)		# get TIME_2
	jal Year
	sw $v0, 8($sp)		# save Year(TIME_2)
	jal Month
	sw $v0, 4($sp)		# save Month(TIME_2)
	jal Day
	sw $v0, 0($sp)		# save Day(TIME_2)

	add $v0, $0, $0 # v0 = 0

	lw $t0, 20($sp) # t0 = Year(TIME_1)
	lw $t1, 8($sp)  # t1 = Year(TIME_2)
	beq $t0, $t1, SubYear_return # if Year(TIME_1) == Year(TIME_2) goto SubYear_return

	add $v0, $v0, $t0 # v0 = t0
	sub $v0, $v0, $t1 # v0 = t0 - t1
SubYear_Compare_month:
	lw $t0, 16($sp) # t0 = Month(TIME_1)
	lw $t1, 4($sp)  # t1 = Month(TIME_2)

	beq $t0, $t1, SubYear_day #if Month(TIME_1) == Month(TIME_2) goto SubYear_day
	
	slt $t3, $t1, $t0 # t1 < t0
	bne $t3, $0, SubYear_return #if Month(TIME_2) < Month(TIME_1) goto SubYear_return
	
	j SubYear_skip #if Month(TIME_1) < Month(TIME_2) goto SubYear_skip
SubYear_day:
	lw $t0, 12($sp) # t0 = Day(TIME_1)
	lw $t1, 0($sp)  # t1 = Day(TIME_2)

	beq $t0, $t1, SubYear_return #if Day(TIME_1) == Day(TIME_2) goto SubYear_return
	
	slt $t3, $t1, $t0 # t1 < t0
	bne $t3, $0, SubYear_return #if Day(TIME_2) < Day(TIME_1) goto SubYear_return
	
	#else Day(TIME_1) < Day(TIME_2)
SubYear_skip:
	addi $v0, $v0, -1
SubYear_return:
	# restore from stack
	lw $ra, 32($sp)
	lw $a0, 28($sp)
	lw $a1, 24($sp)
	addi $sp, $sp, 36

	jr $ra
#===============================================================#
#Ham ktra tinh hop le cua ngay					#		
#INPUT: a0, a1, a2 > 0: ngay thang nam dang int 		#
#	ko bi thay doi gia tri trong ham			#
#OUTPUT: v0 = 1: hop le/ = 0: ko hop le				#
#===============================================================#
isValidDate:
	addi $sp, $sp, -8
	sw $ra, 4($sp)
	
	add $v0, $0, $0			#mac dinh ko hop le
	#Thang > 12 || == 0 -> ko hop le
	slti $t0, $a1, 13		#t0 = (a1 < 13)
	beq $t0, 0, isValidDate_return 	#t0 = 0 -> a1 >= 13 -> return 
	beq $a1, 0, isValidDate_return	#a1 = 0 -> return

	#Ngay == 0 -> ko hop le
	beq $a0, 0, isValidDate_return

	#Nam < 1900 -> ko hop le
	slti $t0, $a2, 1900
	bne $t0, $0, isValidDate_return  

	#Nam > 9999 -> ko hop le
	slti $t0, $a2, 10000
	beq $t0, 0, isValidDate_return

	#Ktra ngay trong thang
	# - thang 1,3,5,7,8,10,12: ngay <= 31
	beq $a1, 1, checkLessThan31
	beq $a1, 3, checkLessThan31	
	beq $a1, 5, checkLessThan31
	beq $a1, 7, checkLessThan31	
	beq $a1, 8, checkLessThan31
	beq $a1, 10, checkLessThan31
	beq $a1, 12, checkLessThan31	

	# - thang 4,6,9,11: ngay <= 30
	beq $a1, 4, checkLessThan30
	beq $a1, 6, checkLessThan30
	beq $a1, 9, checkLessThan30
	beq $a1, 11, checkLessThan30

	# - thang 2
	beq $a1, 2, checkFebruary

	checkLessThan31:
		slti $t0, $a0, 32 		#t0 = (a0<32)
		beq $t0, 1, isValidDate_true	#t0=1 -> a0 <= 31
		j isValidDate_return

	checkLessThan30:
		slti $t0, $a0, 31 		#t0 = (a0<31)
		beq $t0, 1, isValidDate_true	#t0=1 -> a0 <= 30
		j isValidDate_return
	
	checkFebruary:
		beq $a0, 29, isLeapYear

		slti $t0, $a0, 30			
		beq $t0, 1, isValidDate_true	
		j isValidDate_return
	
	isLeapYear:
		sw $a0, 0($sp)
		add $a0, $0, $a2

		jal OnlyYear_LeapYear
		lw $a0, 0($sp)
		bne $v0, $0, isValidDate_true #if a0 is leap year goto isValidDate_true
		j isValidDate_return
	
	isValidDate_true:
		addi $v0, $0, 1

	isValidDate_return:
		lw $ra, 4($sp)
		addi $sp, $sp, 8
		jr $ra
		
#===============================================================#
# Ham kiem tra nam nhuan					#
#INPUT: a0: year						#
#OUTPUT: 1: leap year, 0: not leap year				#	
#===============================================================#
OnlyYear_LeapYear:
	#save into stack
	addi $sp, $sp, -8
	sw $t1, 4($sp)
	sw $t2, 0($sp)
	
	addi $t1, $0, 400 # t1 = 400
	div $a0, $t1
	mfhi $t2 				# t2 = year % 400
	beq $t2, $0, OnlyYear_True	# if year % 400 == 0

	addi $t1, $0, 4 # t1 = 4
	div $a0, $t1
	mfhi $t2 				# t2 = year % 4
	bne $t2, $0, OnlyYear_False # if year % 4 != 0

	addi $t1, $0, 100 # t1 = 100
	div $a0, $t1
	mfhi $t2 				# t2 = year % 100
	beq $t2, $0, OnlyYear_False # if year % 4 == 0 and year % 100 == 0
OnlyYear_True:
	addi $v0, $0, 1		
	j OnlyYear_return
OnlyYear_False:
	add $v0, $0, $0
OnlyYear_return:
	lw $t1, 4($sp)
	lw $t2, 0($sp)

	addi $sp, $sp, 8

	jr $ra
#===============================================================#
#			Khoa's code				#
#===============================================================#
#Ham chuyen doi tu dang chuan DD/MM/YYYY sang cac dang khac	#
#INPUT: a1: TYPE(char)						#
#	a0: TIME => bi thay doi trong ham nay			#
#A: MM/DD/YYYY							#
#B: Month DD, YYYY						#
#C: DD Month, YYYY						#
#===============================================================#
Convert:
	#Get type
	lb $t1, 0($a1)
	addi $t0, $0, 67
	beq $t1, $t0, Convert_C #Jump to convert C if type == 'C'
	addi $t0, $0, 66
	beq $t1, $t0, Convert_B #Jump to convert_B if type == 'B'
	addi $t0, $0, 65
	beq $t1, $t0, Convert_A #Jump to convert_B if type == 'B'
	
	j Convert_illegal	#Truong hop lua chon k phai A, B, C
	
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
		
		j Convert_out
	
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
		
		j Convert_out
	
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
		
		j Convert_out
		
	Convert_illegal:
		addi $v1, $0, 0 		#lua chon ko hop le
		addi $v0, $0, 4			
		la $a0, convert_illegal_Msg
		syscall
		j Convert_out	
	
	Convert_out:
		jr $ra		
		
		
		
		
#Get string typec1 of month.
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
#===============================================================#
#Copy string from $a1 to $a0					#
#$a2: start position of $a1					#
#$a3: end position of $a1					#
#===============================================================#
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
#===============================================================#
#Join string $a1 to $a0:					#
#$a2: start position of $a1					#
#$a3: end position of $a1					#
#===============================================================#
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

Day:
	# Saving address $ra to stack
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	# Day is in TIME[0:1]
	addi $a1, $0, 0
	addi $a2, $0, 1
	jal strToNum
	# $v0 is Day's number and this is a result for Day function
	
	# Restoring stack
	lw $ra, 0($sp)
	addi $sp, $sp, 4
	jr $ra

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

# $a0 is TIME's address pointer
# return char* is one element of {"Mon", "Tues", "Wed", "Thurs", "Fri", "Sat", "Sun"}
Weekday:
	# Saving to stack
	addi $sp, $sp -20
	sw $ra, 16($sp) # saving $ra
	sw $a0, 12($sp) # address of TIME's pointer
	
	
	
	
	
	# get day and assign to a1
	lw $a0, 12($sp)
	jal Day
	add $a1, $0, $v0 # assign day to a1
	sw $a1, 8($sp) # day
	
	# get month and assign to a2
	lw $a0, 12($sp)
	jal Month
	add $a2, $0,$v0 # assign month to a2 
	sw $a2, 4($sp) # month
	
	# get year and assign to a3
	lw $a0, 12($sp)
	jal Year
	add $a3, $0, $v0 # assign Year to a3
	sw $a3, 0($sp) # year
	
	lw $a1, 8($sp)
	lw $a2, 4($sp)
	lw $a3, 0($sp)
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
	addi $t4, $0, 5 # $t4 = 5
	
	div $a2, $t4 # 3 * (month + 1) div 5
	mflo $a2 # a2 = 3 * (month + 1) div 5
	add $s0, $s0, $a2 # result = result + 3 * (month + 1) div 5
	
	add $s0, $s0, $a3 # result = result + year
	
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
		lw $ra, 16($sp)
		lw $a0, 12($sp)
		lw $a1, 8($sp)
		lw $a2, 4($sp) 
		lw $a3, 0($sp) 
		addi $sp, $sp, +20
		jr $ra

# $a0 is year number
# return 0 or 1
LeapYearNumber:
	# save to stack
	addi $sp, $sp, -8
	sw $t0, 0($sp)
	sw $t1, 4($sp)
	
	# year is a Leap Year when year % 400 = 0 or (year % 4 == 0 && year % 100 != 0)
	addi $t0, $0, 400
	div $a0, $t0
	mfhi $t1 # $t1 = $a0 % 400
	beq $t1, $0, return_Leap_Year # t1 == 0 if a0 % 400 == 0
	
	addi $t0, $0, 4
	div $a0, $t0
	mfhi $t1 # t1 = a0 % 4
	bne $t1, $0, return_Not_Leap_Year # if year % 4 != 0 then (year % 4 == 0 && year % 100 != 0) == false
	
	addi $t0, $0, 100
	div $a0, $t0
	mfhi $t1 # t1 = a0 % 100
	
	beq $t1, $0, return_Not_Leap_Year  # if v0 % 100 == 0 then false because we had year % 4 == 0 but year % 100 == 0
	j return_Leap_Year 
	
	return_Leap_Year:
	addi $v0, $0, 1
	j return_all
	
	return_Not_Leap_Year:
	addi $v0, $0, 0
	j return_all
	
	return_all:
	lw $t0, 0($sp)
	lw $t1, 4($sp)
	addi $sp, $sp, +8	
	jr $ra

# $a0 is TIME's address pointer
# 10/10/2020 --> 0 because 2020 is not a leap year
LeapYear:
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	jal Year
	# Now, $v0 is year number
	add $a0, $0, $v0
	jal LeapYearNumber
	
	# restore and return
	lw $ra, 0($sp)
	addi $sp, $sp, +4
	jr $ra

#a0 is year
# return 1900 <= year <= 9999
isValidYear:
	slti $t0, $a0, 10000
	beq $t0, $0, return_false_ValidYear
	
	addi $t1, $0, 1899
	slt $t0, $t1, $a0 
	beq $t0, $0, return_false_ValidYear
	
	return_true_ValidYear:
	addi $v0, $0, 1
	jr $ra
	return_false_ValidYear:
	addi $v0, $0, 0
	jr $ra
	 
# $a0 is value
# $a1 is +1 or -1
# return leap year
NextLeapYear:
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $t0, 4($sp)
	sw $t1, 8($sp)
	
	add $t0, $0, $a0
	add $t1, $0, $a1
	add $t0, $t0, $a1
	while_loop:
		add $a0, $0, $t0
		jal LeapYearNumber
		beq $v0, 1, return_NextLeapYear
		
		add $t0, $t0, $t1
		j while_loop
	return_NextLeapYear:
	add $v0, $0, $t0
	
	lw $ra, 0($sp)
	lw $t0, 4($sp)
	lw $t1, 8($sp)
	addi $sp, $sp, +12	
	jr $ra
		

# a0 is char* TIME
# return: v0: leap year 1, v1: leap year 2
Leap_Year_Closer:
	addi $sp, $sp, -8
	sw $a0, 0($sp)
	sw $ra, 4($sp)
	jal Year
	lw $a0, 0($sp)
	lw $ra, 4($sp)
	addi $sp, $sp, +8
	#t0 is leap year < current_year, t1 is leap year > current_year
	addi $sp, $sp, -4
	sw $ra, 0($sp)
	
	add $t0, $0, $v0
	add $t1, $0, $v0
	
	add $a0, $0, $t0
	addi $a1, $0, -1
	jal NextLeapYear
	add $t0, $0, $v0 
	
	add $a0, $0, $t1
	addi $a1, $0, +1
	jal NextLeapYear
	add $t1, $0, $v0
	# we had $t0 < current_year < $t1
	# if $t0 is not valid
	# if $t0 < 1900 then false
	slti $t2, $t0, 1900
	beq $t2, 1, return_nxt_nxt
	
	# if $t1 > 9999 then false
	addi $t3, $0, 9999
	slt $t2, $t3, $t1
	beq $t2, 1, return_pst_pst
	
	return_pst_nxt:
		j return_all_closer
	return_nxt_nxt:
		add $a0, $0, $t1
		addi $a1, $0, +1
		jal NextLeapYear
		add $t0, $0, $v0
		j return_all_closer
	return_pst_pst:
		add $a0, $0, $t0
		addi $a1, $0, -1
		jal NextLeapYear
		add $t1, $0, $v0
		j return_all_closer
	return_all_closer:
		lw $ra, 0($sp)
		addi $sp, $sp, +4
		add $v0, $0, $t0
		add $v1, $0, $t1
		jr $ra


GetTime:
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $s0,4($sp)
	sw $s1, 8($sp)
	addi $a0, $s0, 0
	addi $a1, $s1, 0
	jal CompareDate
	beq $v0, $0, GetDistance_Zero
	lw $a1, 8($sp)
	lw $a0, 4($sp)
	addi $t0, $0, 1
	beq $v0, $t0, GetDistance_JumptoYear
	addi $t0, $s2, 0
	addi $s2, $s3, 0
	addi $s3, $t0, 0
	j GetDistance_JumptoYear
	GetDistance_JumptoYear:
		jal GetDistance_Year
		j GetDistance_Out
	GetDistance_Zero:
		addi $v0, $0, 0
	GetDistance_Out:
		lw $ra, 0($sp)
		lw $a0, 4($sp)
		lw $a1, 8($sp)
		addi $sp, $sp, 8
		
		jr $ra
GetDistance_Year:
	addi $sp, $sp, -16
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	sw $a1, 8($sp)
	
	#Lay ra 2 nam
	add $t3, $0, $0
	sw $t3, 12($sp)
	beq $s2, $s3, GetDistance_Year_Return
	
	#Tinh khoang cach hai nam
	addi $s2, $s2, -1
	sub $t2, $s2, $s3
	sw $t2, 12($sp)
	
	#Lay ra 2 thang
	lw $a0, 4($sp)
	jal Month
	add $s2, $v0, $0
	lw $a0, 8($sp)
	jal Month
	add $s3, $v0, $0
	
	slt $t2, $s2, $s3
	lw $t3, 12($sp) #Lay khoang cach so nam trong stack
	add $t3, $t3, $t2 #Cong 1 neu thang cua nam 1 < thang cua nam 2
	sw $t3, 12($sp)
	bne $t2, $0, GetDistance_Year_Return #Return neu MONTH1 < MONTH2
	slt $t2, $s3, $s2
	bne $t2, $0, GetDistance_Year_Return #Return neu MONTH2 < MONTH1
	
	#Neu hai thang bang nhau, so sanh ngay
	lw $a0, 4($sp)
	jal Day
	add $s2, $v0, $0
	lw $a0, 8($sp)
	jal Day
	add $s3, $v0, $0
	
	#Neu 2 ngay do la ngay 29/2
	lw $a0, 4($sp)
	jal Month
	add $t0, $v0, $0
	addi $t3, $0, 2
	bne $t0, $t3, GetDistance_Year_Not292
	
	lw $a0, 8($sp)
	jal Month
	add $t1, $v0, $0
	addi $t3, $0, 2
	bne $t1, $t3, GetDistance_Year_Not292
	
	#Chuyen ngay 29/2 -> 28/2
	addi $t3, $0, 28
	slt $t2, $t3, $s2
	sub $s2, $s2, $t2
	
	addi $t3, $0, 28
	slt $t2, $t3, $s3
	sub $s3, $s3, $t2
	
	GetDistance_Year_Not292:
	slt $t2, $s2, $s3
	lw $t3, 12($sp)
	add $t3, $t3, $t2
	sw $t3, 12($sp)
	
	bne $t2, $0, GetDistance_Year_Return #Return neu DAY1 < DAY2
	
	slt $t2, $s3, $s2
	bne $t2, $0, GetDistance_Year_Return #Return neu DAY2 < DAY1
	lw $t3, 12($sp)
	addi $t3, $t3, 1
	sw $t3, 12($sp)
	GetDistance_Year_Return:
		lw $v0, 12($sp)
		lw $ra, 0($sp)
		lw $a0, 4($sp)
		lw $a1, 8($sp)
		addi $sp, $sp, 16
		jr $ra
	
		
		
CompareDate:
	addi $sp, $sp, -12
	sw $ra, 0($sp)
	sw $a0, 4($sp)
	sw $a1, 8($sp)
	jal Year
	add $s2, $v0, $0
	lw $a0, 8($sp)
	jal Year
	add $s3, $v0, $0
	add $a0, $s2, $0
	add $a1, $s3, $0
	jal CompareInt
	addi $t0, $0, 1
	beq $v0, $t0, Compare_Bigger
	addi $t0, $0, -1
	beq $v0, $t0, Compare_Smaller
	
	
	lw $a0, 4($sp)
	jal Month
	add $s2, $v0, $0
	lw $a0, 8($sp)
	jal Month
	add $s3, $v0, $0
	add $a0, $s2, $0
	add $a1, $s3, $0
	jal CompareInt
	addi $t0, $0, 1
	beq $v0, $t0, Compare_Bigger
	addi $t0, $0, -1
	beq $v0, $t0, Compare_Smaller
	
	lw $a0, 4($sp)
	jal Day
	add $s2, $v0, $0
	lw $a0, 8($sp)
	jal Day
	add $s3, $v0, $0
	add $a0, $s2, $0
	add $a1, $s3, $0
	jal CompareInt
	addi $t0, $0, 1
	beq $v0, $t0, Compare_Bigger
	addi $t0, $0, -1
	beq $v0, $t0, Compare_Smaller
	j Compare_Equal
	Compare_Bigger:
		addi $v0, $0, 1
		j Compare_out
	Compare_Smaller:
		addi $v0, $0, -1
		j Compare_out
	Compare_Equal:
		addi $v0, $0, 0
		j Compare_out
	Compare_out:
		lw $a0, 4($sp)
		lw $a1, 8($sp)
		lw $ra, 0($sp)
		addi $sp, $sp, 12
		jr $ra
	
CompareInt:
	slt $t0, $a0, $a1
	bne $t0, $0, CompareInt_Smaller
	slt $t0, $a1, $a0
	bne $t0, $0, CompareInt_Bigger
	j CompareInt_Equal
	CompareInt_Smaller:
		addi $v0, $0, -1
		jr $ra
	CompareInt_Bigger:
		addi $v0, $0, 1
		jr $ra
	CompareInt_Equal:
		addi $v0, $0, 0
		jr $ra