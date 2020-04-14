all: Parser Scanner YourCode 
	gcc BabyC.tab.o lex.yy.o driver.o your_code.o SymbolTable.o bucket.o -o bcc -lm

YourCode: bucket.o SymbolTable.o your_code.o driver.o 

Scanner: BabyC.lex 
	flex BabyC.lex
	gcc -c lex.yy.c

Parser: BabyC.y  
	bison -d BabyC.y
	gcc -c BabyC.tab.c

%.o: %.c 
	gcc -c $<

