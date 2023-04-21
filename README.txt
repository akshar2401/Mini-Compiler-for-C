When you run the makefile, the following warning is generated:
"BabyC.y:78.16: warning: empty rule for typed nonterminal, and no action"
This warning is generated becausse there's no action for Declaration List
But the code still works (bcc is still created). This warning can be ignored

How to run:
1) run "make" command in the terminal
2) Then run  "bcc <filename>.bc" or "./bcc <filename>.bc" 

Symbol Table constraints:
1) The initial size of the Symbol table is 1229. As more symbols are added in the table, 
the loadfactor will increase, and the table will be resized after loadfactor becomes more than 0.75
2) The new size will be the first prime number after the current size of the table * 2


Output
1) The program will still print the statements
2) The generated code is directed to file created based on test file.Look for files with name created using format: test<testnumber>.iloc

Changes:
Added null check for Ast root in GenerateILocCode() in your_code.c
