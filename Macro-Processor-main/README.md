# Macro-Processor
## Created By: Divya Dayashankar Jaiswal
#### LANGUAGE USED : C
#### ALGORITHM DEVELOPED : TWO-PASS (ALGORITHM - 1); MDI (ALGORITHM - 2); STACK (ALGORITHM - 3)
#### PERCENTAGE OF SOFTWARE DEVELOPED : 100%

### algo1: It consists of pass-1 and pass-2 algorithm (pass-1 processing macro definition; pass-2 processing macro calls and expansion)
Each of these pass-1 and pass-2 algorithm makes a line-by-line scan over its input.
* **Pass-1-MACRO DEFINATION**: The algorithm for pass-1 tests each input line. If it is a Macro, the entire macro defination is saved in the next available location in the Macro Defination Table (MDT). The line of the defination is the macro name line. The name is entered into the Macro Name Table (MNT), along with the pointer to the first-location of the MDT entry of the defination. When the END is encountered, all of the macro definations have beenn processed so control transfers to pass 2 in order to process macro calls.
* **Pass-2-MACRO CALLS & EXPANSION**: The algorithm for pass-2 tests the operation mnemonic of each input line to see if it is a name in the MNT. When a call is found, the call processor sets a pointer, the Macro Defination Table Pointer (MDTP), to the corresponding macro defination stored in the MDT. The initial value of the MDTP is obtained from "MDT index" field of the MNT entry. The macro expander prepares the Argument List Array (ALA) consistinig of a table of dummy argument indices and corresponding arguments to the call. Reading proceeds from MDT, as each successive line is read, the values from ALA is substituted for dummy argument indices in the macro defination. Reading of the MEND line in the MDT terminates expansion of the macro, and scanning continues from the input file. When the END is encountered, the algorithm terminates.

### algo2: It consists of Algorithm 2---Simple one-pass macro processor
These is a simpler solution that has advantage of reducing all macro processing to a single pass. Here, macro defination must be processed before calls because macros must be defined to the processor before it can expand calls to them. There are two additional variable introduce in this design: a Macro Defination Input (MDI) Indicator and a Macro Defination Level Counter (MDLC). The MDI and MDLC are switches (counters) used to keep track of macro calls and macro definations. The MDI indicator has the value "ON" during expansion of a macro call and the value "OFF" at all other times. The Macro Defination Level Counter is incremented by 1 when a MACRO is encountered and decremented by 1 when a MEND occurs. Also, since it is a possible to be performing the "macro defination pass" simultaneously with the "macro expansion pass", as it is the case when expanding a macro defination with an inner macro defination, there must be two separate ALAs, one ALA is used for macro defination while other is employed for macro call expansion. 

### algo3: It consists of Algorithm 3---One-pass macro processor capable of handling macro calls within macro definitions
To handle macro calls within macros, the macro processor must be able to work recursively i.e. to process one macro before it is finished with another, then to continue with the previous, or 'outer' one. Recursive procedures usually operate by means of a stack. A Stack Pointer (SP) indicates the position or frame at the 'top' of the stack. 
This algorithm handles the macro calls within macro definations as well as macro definations within macro definiations. Heres, pointer MDTP and the ALA associated with each call belong in the stack. The switch MDI must also be saved. The SP, which indicates the beginning of the current stack frame, serve in the place MDI- in each succeeding frame. Also, previous value of SP is saved to prevent it from lost. Ignoring the actual method of data representation, we consider the stack to be an array of pointers and character strings.

#### Advantages of the Algorithm 3
* Works for nth - Level Nested Macro Call and Definition.
* Uses 2-D array for Argument and Line Numbers (such as argument - 'ARGU1', line number - 95)
* It recognize difference between Upper Case and Lower Case.
* It has all the functionality of Algorithm 1 and 2 of Macro Processor.
* It is Backward referencing software.    
