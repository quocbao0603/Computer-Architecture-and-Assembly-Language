
.data
	# _____DU LIEU INPUT_____
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
		

	# _____MENU LUA CHON_____	
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
		convert_invalid_Msg:
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


	#______RESULT_______
	selectOptionMsg:
		.asciiz "Lua chon: "
	resultMsg: 	
		.asciiz "Ket qua: "
	invalidOptionMsg:
		.asciiz "Lua chon khong hop le. Moi chon lai.\n"
	DoUWantToContinueMsg:
		.asciiz "\nTiep tuc chuong trinh? (1: Co/ 0: Khong)\nLua chon: "


	# _____TEN THANG_____
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


	# _____TEN THU_____
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
	outputMsg_CloserLeapYear:
		.asciiz "Hai nam nhuan (>= 1900) gan nhat la: "
	outputMsg_CloserLeapYear_and:
		.asciiz " and "
	outputMsg_GetTime:
		.asciiz "Khoang cach giua 2 khoang thoi gian (nam): "
	
.text:
#__________MENU & NHAP DU LIEU____________
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
	#beq $a0, 2, solve_option2
	#beq $a0, 3, solve_option3
	#beq $a0, 4, solve_option4
	#beq $a0, 5, solve_option5
	#beq $a0, 6, solve_option6
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
	addi $v0, $0, 4
	la $a0, resultMsg
	syscall
	
	add $a0, $s0, $0	#$s0 hi?n t?i ?ang l?u TIME
	addi $v0, $0, 4
	syscall
	j continueMenu

#_________________Doan nay chua xu li(chi copy paste test thu)______________#
#___________________________________________________________________________#
#___________________________________________________________________________#
solve_option2:
	# lua chon dinh dang can xu ly (A,B hay C)
	addi $v0, $0, 4 # in chuoi lua chon
	la $a0, type_of_option2
	syscall

	addi $v0, $0, 8 
	la $a0, inputString	# doc chuoi ($a0 = type (A, B hay C))
	addi $a1, $0, 1024 
	syscall

	
	# chuyen con tro xuong dong moi de in ket qua
#	addi $a0, $0, 10 # (int)10 = (char)\n (ASCII)
#	addi $v0, $0, 11 # in ra ky tu
#	syscall

	# chuyen dinh dang
	add $a1, $0, $a0	#luu lua chon vao $a1
	add $a0, $0, $s0 	# $s0: TIME
	#jal Convert

	beq $v1, 0, continueMenu 	#lua chon ko hop le -> ko chuyen doi dc

	# in ra dinh dang da duoc chuyen doi
	add $a0, $0, $s0
	addi $v0, $0, 4
	syscall
	j continueMenu

solve_option3:
	add $a0, $s0, $0
	#jal WeekDay
	add $a0, $0, $v0
	addi $v0, $0, 4 # in chuoi option 3
	syscall
	j continueMenu

solve_option4:
	add $a0, $s0, $0
	#jal LeapYear
	bne $v0, $0, solve_4_LeapYear
	la $a0, is_not_LeapYear
	addi $v0, $0, 4 # in ra chuoi ket qua
	syscall
	j continueMenu

	solve_4_LeapYear:
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
	
	la $a0, outputMsg_GetTime
	addi $v0, $0, 4
	syscall

	#xu ly.....
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
	#xu ly...
	la $a0, outputMsg_CloserLeapYear
	addi $v0, $0, 4	# syscall print string
	syscall

	add $a0, $0, $s0	# get TIME
	#jal LeapYearCloser
	#jal Year
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
#_________________Doan nay chua xu li(chi copy paste test thu)______________#
#___________________________________________________________________________#
#___________________________________________________________________________#


#Ham nhap du lieu
#INPUT: 
#OUTPUT: v0: (dia chi) chuoi TIME
#	 v1 = 4: hop le; < 4: ko hop le
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

#===========================================================#
#		SOLVE OPTION 1
#Ham tra ve chuoi ngay thang nam dang chuan DD/MM/YYYY
#INPUT: a0,a1,a2: ngay thang nam (int), a3: TIME
#	a0,a1,a2,a3 co the bi doi trong ham nay
#OUTPUT: v0 = TIME dang chuan DD/MM/YYYY
#	 v1: tinh hop le (1: hop le, 0: ko hop le)
#===========================================================#
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


#_________________Doan nay chua xu li(chi copy paste test thu)______________#
#___________________________________________________________________________#
#___________________________________________________________________________#


#______________SOLVE OPTION 5______________________
#Ham cho biet thoi gian  giua chuoi TIME_1 va TIME_2
#INPUT: a0, a1: 2 chuoi thoi gian can tinh khoang cach TIME_1, TIME_2
#OUTPUT: v0 (int) = khoang cach thoi gian (nam)
GetTime:
	# save into stack
	addi $sp, $sp, -12
	
	sw $ra, 8($sp)
	sw $a0, 4($sp)
	sw $a1, 0($sp)

	jal CompareTime

	# TIME_1 == TIME_2 => distance_year = 0
	beq $v0, $0, GetTime_return

	# TIME_1 > TIME_2 => v0 == 1
	slt $t0, $v0, $0 # v0 < 0
	bne $t0, $0, GetTime_skip # if true goto GetTime_skip

	jal SubYear
	j GetTime_return

GetTime_skip:
	# TIME_1 < TIME_2 => v0 == -1
	lw $a0, 0($sp)
	lw $a1, 4($sp)

	jal SubYear

GetTime_return:
	lw $ra, 8($sp)
	lw $a0, 4($sp)
	lw $a1, 0($sp)
	addi $sp, $sp, 12
	
	jr $ra

#Ham so sanh chuoi TIME
#INPUT: a0, a1: 2 chuoi thoi gian can tinh khoang cach TIME_1, TIME_2
#OUTPUT: v0 = 1: TIME_1 > TIME_2, v0 = 0: TIME_1 = TIME_2, v0 = -1: TIME_1 < TIME_2
CompareTime:
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

Compare_year:
	lw $t0, 20($sp) # t0 = Year(TIME_1)
	lw $t1, 8($sp)  # t1 = Year(TIME_2)
	
        beq $t0, $t1, Compare_month

	slt $t3, $t0, $t1 # t0 < t1
	bne $t3, $0, Compare_Smaller #if Year(TIME_1) < Year(TIME_2) goto Compare_Smaller
	
	j Compare_Bigger #if Year(TIME_1) != Year(TIME_2) goto Compare_Bigger
Compare_month:
	lw $t0, 16($sp) # t0 = Month(TIME_1)
	lw $t1, 4($sp)  # t1 = Month(TIME_2)
	
	beq $t0, $t1, Compare_day

	slt $t3, $t0, $t1 # t0 < t1
	bne $t3, $0, Compare_Smaller #if Month(TIME_1) < Month(TIME_2) goto Compare_Smaller
	
	j Compare_Bigger #if Month(TIME_1) != Month(TIME_2) goto Compare_Bigger
Compare_day:
	lw $t0, 12($sp) # t0 = Day(TIME_1)
	lw $t1, 0($sp)  # t1 = Day(TIME_2)
	
	beq $t0, $t1, Compare_Equal

	slt $t3, $t0, $t1 # t0 < t1
	bne $t3, $0, Compare_Smaller #if Day(TIME_1) < Day(TIME_2) goto Compare_Smaller
	
	j Compare_Bigger #if Day(TIME_1) != Day(TIME_2) goto Compare_Bigger
Compare_Smaller:
	addi $v0, $0, -1 # v0 = -1
	j CompareTime_return
Compare_Bigger:
	addi $v0, $0, 1 # v0 = 1
	j CompareTime_return
Compare_Equal:
	add $v0, $0, $0
CompareTime_return:
	# restore from stack
	lw $ra, 32($sp)
	lw $a0, 28($sp)
	lw $a1, 24($sp)
	addi $sp, $sp, 36

	jr $ra


# $a0: luu chuoi TIME
# $v0: tra ve ket qua kieu int tuong ung cho tung ham (Day, Month, Year)
Day: # DD trong chuoi TIME -> (int)DD
	# luu vao stack
	# $t0 ~ TIME[0], $t1 ~ TIME[1]
	addi 	$sp, $sp, -8
	sw	$ra, 4($sp)
	sw	$a0, 0($sp)

	# xu ly hang chuc cua ngay
	lb	$t0, 0($a0)
	addi	$t0, $t0, -48 # chuyen tu char sang int (ASCII)
	
	li	$t1, 10
	mult	$t0, $t1
	mflo	$t0
	
	# xu ly hang don vi cua ngay 
	lb	$t1, 1($a0)
	addi	$t1, $t1, -48
	add	$t0, $t0, $t1

	add 	$v0, $0, $t0

	# khoi phuc lai stack
	lw	$ra, 4($sp)
	lw	$a0, 0($sp)
	addi 	$sp, $sp, 8
	
	jr	$ra

Month: # MM trong chuoi TIME -> (int)MM
	# luu vao stack
	# $t0 ~ TIME[3], $t1 ~ TIME[4]
	addi 	$sp, $sp, -8
	sw	$ra, 4($sp)
	sw	$a0, 0($sp)

	# xu ly hang chuc cua thang
	lb	$t0, 3($a0)
	addi	$t0, $t0, -48
	
	li	$t1, 10
	mult	$t0, $t1
	mflo	$t0
	
	# xu ly hang don vi cua thang
	lb 	$t1, 4($a0)
	addi	$t1, $t1, -48
	add	$t0, $t0, $t1

	add 	$v0, $0, $t0

	# khoi phuc lai stack
	lw	$ra, 4($sp)
	lw	$a0, 0($sp)
	addi 	$sp, $sp, 8
	
	jr	$ra

Year:
	# luu vao stack
	addi $sp, $sp, -12
	sw $ra, 8($sp)
	sw $a0, 4($sp)

	# xu ly hang nghin va tram cua nam
	la	$a0, 6($a0) # nam trong chuoi TIME bat dau tu TIME[6]
	jal	Day
	
	li	$t1, 100
	mult	$v0, $t1
	mflo	$t0
	sw 	$t0, 0($sp)

	# xu ly hang chuc va don vi cua nam
	lw 	$a0, 4($sp)
	la	$a0, 8($a0)
	jal	Day

	# luu ket qua vao $v0
	lw	$t0, 0($sp)
	add 	$v0, $v0, $t0

	# khoi phuc stack
	lw	$ra, 8($sp)
	lw	$a0, 4($sp)
	addi 	$sp, $sp, 12
	
	jr	$ra

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

#Ham ktra tinh hop le cua ngay-----------------------------------------------------
#INPUT: a0, a1, a2 > 0: ngay thang nam dang int 
#	ko bi thay doi gia tri trong ham
#OUTPUT: v0 = 1: hop le/ = 0: ko hop le
#Ham ktra tinh hop le cua ngay-----------------------------------------------------
#INPUT: a0, a1, a2 > 0: ngay thang nam dang int 
#	ko bi thay doi gia tri trong ham
#OUTPUT: v0 = 1: hop le/ = 0: ko hop le
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
		

# Ham kiem tra nam nhuan
#INPUT: a0: year
#OUTPUT: 1: leap year, 0: not leap year
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
#_________________Doan nay chua xu li(chi copy paste test thu)______________#
#___________________________________________________________________________#
#___________________________________________________________________________#
