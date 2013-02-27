DEF

def nonInstruction() {
	[-] > -------- <
}

def adjust() {
	> [ <+>- ] <
	[ > + > + > + > ]
}

def plus() {
	> + <
}

def read() {
	> + < 
}

def sub() {
	> + < 
}

def print() {
	> + < 
}

def backward() {
	> + <
}

def forward() {
	> + <
}

def beginLoop() {
	> + <
}

def endLoop() {
	> + <
}

def __sub_6x7() {
	>+++ +++ [ >++++ +++ [ <<- >>- ] <- ] <
}

def __sub_4x3plus2() {
	-- >++++ [ >+++ [ <<- >>- ] <- ] <
}

def __sub_6x5plus1() {
	+ >+++ +++ [ >+++ ++ [ <<- >>- ] <- ] <	
}

def MapCode() {
	__sub_6x7()
	- 
	[
		-
		[  
			-
			[
				-
				[
					__sub_4x3plus2()
					[
						--
						[
							__sub_6x5plus1()
							[
								--
								[
									nonInstruction()
								]
								endLoop()
							]
							beginLoop()
						]
						forward()
					]
					backward()
				]
				print()
			]
			sub()
		]
		read()
	]
	plus()

	adjust()

}

def IsHalt() {
	>+++ +++ [ >+++ ++ [ <<- >>- ] <- ] <--- 
}

def BeforeMapCode() {
	>+++ +++ [ >+++ ++ [ <<+ >>- ] <- ] <+++
}

def __________________________________________________________________________() {}

def Ready() {
	<[<]
}

def Init_ProgramCounter_afterReady() {
	>>[-]<<
}

def Initial() {
	Ready()
	Init_ProgramCounter_afterReady()
	<<
}

def nextProgramCounter() {
	>>>>[-]<<<<+
}

def fetchCode() {
	>>>>[>>>>] <
}



def Into_DataSection() {
	[>] 
	>>[>>]
}

def exit_DataSection() {
	<<[<<]
	<[<]
}

def do_plus() {
	Into_DataSection()
		>+.<
	exit_DataSection()
}


def do_read() {
	Into_DataSection()
		>,.<
	exit_DataSection()
}

def do_sub() {
	Into_DataSection()
		>-.<
	exit_DataSection()
}

def do_print() {
	Into_DataSection()
		>.<
	exit_DataSection()
}

def do_backward() {
	Into_DataSection()
		<<[-]
	exit_DataSection()
}

def do_forward() {
	Into_DataSection()
		+
	exit_DataSection()
}

def do_beginLoop() {
	Into_DataSection()
		
	exit_DataSection()
}

def do_endLoop() {
	Into_DataSection()
		
	exit_DataSection()
}

def SaveCode_inS_byT_onT_STCF() {
	<[-]<[-]>>
	[<+<+>>-] <[>+<-]
}

def RestoreCode() {
	[-]
	<<[>>+<<-]
	>>>
}

def __IsThatWhatWeWant_() {
	>+<[ >- <[<+>-] ]
	<[>+<-]>
}

def ________tmp() {

}

def Interprete() {
	fetchCode()
	[
		SaveCode_inS_byT_onT_STCF() 
		>

		-
		__IsThatWhatWeWant_()
		> [ -> do_plus() <++++++++> ]
		<

		-
		__IsThatWhatWeWant_()
		> [ -> do_read() <++++++++> ]
		<

		-
		__IsThatWhatWeWant_()
		> [ -> do_sub() <++++++++> ]
		<

		-
		__IsThatWhatWeWant_()
		> [ -> do_print() <++++++++> ]
		<

		-
		__IsThatWhatWeWant_()
		> [ -> do_backward() <++++++++> ]
		<

		-
		__IsThatWhatWeWant_()
		> [ -> do_forward() <++++++++> ]
		<
		
		-
		__IsThatWhatWeWant_()
		> [ -> do_beginLoop() <++++++++> ]
		<

		-
		__IsThatWhatWeWant_()
		> [ -> do_endLoop() <++++++++> ]
		<

		>
		nextProgramCounter()
		
		<<[-]>
		RestoreCode()

		fetchCode()
	]
	
}

def test_Interprete() {
	>>>>
	+>>+>+>
	<<<<
	<<<
	Interprete()
}

def main() {
	>>>> , IsHalt() [ BeforeMapCode() MapCode() , IsHalt() ]
	Initial()
	Interprete()
}

END
MAIN

main()
