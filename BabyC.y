%{
	#include <stdio.h>
	#include "compiler.h"

// The parser needs to call the scanner to get the next token 
	extern int yylex();

// The error function 
	extern int yyerror(const char *);

// The ASTNode root
    extern ASTNode* gASTRoot;
%}

//Put any initialization code here 
%initial-action 
{

}

%token LE "<="
%token GE ">="
%token EQ "=="
%token NE "!="
%token OR "||"
%token AND "&&"
%token MAIN "main"
%token INT "int"
%token IF "if"
%token ELSE "else"
%token WHILE "while"

//Define the types for the grammar attributes ($$, $1, $2, ...) 
%union 
{
	struct ASTNode* node; // Most $$ values will be ASTNodes 
	int num; // Integer numbers
	char* string; // Strings for identifiers 
}

//Specify the type for each token. Only needed for IDENT and NUM, because they are the only ones that have actual regexp rules
%token <string> IDENT
%token <num> NUM
//Specify the type for each non-terminal in the grammar. Here are some samples:
%type <node> Expr
%type <node> Term
 
%type <num>  LogicalOp
%type <node> Factor
%type <node> Goal
%type <node> Assignment
%type <node> LHS
%type <node> Declaration
%type <node> Statement
%type <node> DeclarationList
%type <node> StatementList
%type <node> Compare
%type <node> Condition
%type <node> LogicalFactor
%type <node> LogicalTerm
%type <node> If
%type <node> While
// Add the rest of the types for the grammar's symbols



%%

// Write the grammar for BabyC, and write an embedded action for each production. Here are some samples for you:
Goal: MAIN '(' ')' '{' DeclarationList StatementList'}'	{gASTRoot=$6;}
;
Assignment: LHS '=' Expr';' {$$ = CreateAssignmentNode($1, $3);}
;
LHS: IDENT {$$ = CreateLHSNode($1);}
;
Declaration: INT IDENT';' {addDeclaration($2);}
;
DeclarationList: | Declaration DeclarationList
;
Statement: Assignment {$$=$1;}
		   | If {$$ = $1;}
		   | While {$$ = $1;}
;
StatementList:  {$$=NULL;}
				| Statement StatementList {$$ = CreateStatementListNode($1, $2);}
;
LogicalOp: EQ    {$$ = EQUAL_OP}
		   | NE  {$$ = NOTEQUAL_OP}
		   | '>' {$$ = GT_OP}
		   | '<'	  {$$ = LT_OP}
		   | LE	  {$$ = LTE_OP}
		   | GE	  {$$ = GTE_OP}
;
Compare: Expr LogicalOp Expr {$$ = CreateCompareNode($1, $2, $3);}
;
Condition: Condition OR LogicalTerm {$$ = CreateLogicalNode($1, OR_OP, $3);}
		   | LogicalTerm {$$ = $1;}
;
LogicalTerm: LogicalTerm AND LogicalFactor  {$$ = CreateLogicalNode($1, AND_OP, $3);}
			| LogicalFactor {$$ = $1;}
;
LogicalFactor: Compare {$$ = $1;}
;
If: IF '('Condition')' '{'StatementList'}'	 {$$ = CreateIFNode($3, $6);}
	| IF '('Condition')' '{'StatementList'}' ELSE '{'StatementList'}' {$$ = CreateIfElseNode($3, $6, $10);}
While: WHILE '('Condition')' '{' StatementList '}' {$$ = CreateWhileNode($3, $6);}
Expr: Term    {$$ = $1;}
	| Expr '+' Term {$$ = CreateArithmeticOpNode($1, $3, ADD_OP);}
	| Expr '-' Term {$$ = CreateArithmeticOpNode($1, $3, SUB_OP);}
;
Term: Factor  {$$ = $1;}
	| Term '*' Factor {$$ = CreateArithmeticOpNode($1, $3, MULT_OP);}
	| Term '/' Factor {$$ = CreateArithmeticOpNode($1, $3, DIV_OP);}
;
Factor: IDENT 		{$$ = CreateIdentNode($1);printf("Creating IDENT node for %s\n", $1);}
	| NUM 		{$$ = CreateNumNode($1); printf("Creating NUM node for %d\n", $1);}
	| '('Expr')'	{$$ = $2; printf("Creating Expression node in parentheses\n");}
;



%%
