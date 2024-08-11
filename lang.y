%{
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include "lang.tab.h"

using namespace std;

typedef struct symrec {
    char *name;
    int type;
    struct symrec *next;
} symrec;

symrec *sym_table = NULL;

symrec *putsym(const char *, int);
symrec *getsym(const char *);

void yyerror(const char *s) {
    extern int yylineno;
    fprintf(stderr, "Error: %s at line %d\n", s, yylineno);
}

FILE *outfile;
FILE *debugfile;

extern FILE *yyin;
extern int yylex();
extern int yylineno;
extern int yydebug;

int isSetOrCollection(const char* var);

char* indent_string(const char* str, int indent_level) {
    char* result = strdup("");
    char* line = strtok(strdup(str), "\n");
    while (line != NULL) {
        char* temp;
        asprintf(&temp, "%s%*s%s\n", result, indent_level * 4, "", line);
        free(result);
        result = temp;
        line = strtok(NULL, "\n");
    }
    return result;
}

#define DEBUG_PRINT(msg, ...) fprintf(debugfile, "DEBUG: " msg "\n", ##__VA_ARGS__)
%}

%union {
    int ival;
    char* sval;
}

%token <ival> NUMBER
%token <sval> STRING_LITERAL IDENTIFIER
%token INT STR SET COLLECTION INPUT OUTPUT IF ELSE WHILE FOR
%token EQ NEQ LE GE LT GT ASSIGN PLUS MINUS MUL DIV INTERSECT UNION
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON COMMA COLON LBRACKET RBRACKET 

%type <sval> expression condition identifier identifiers set_literal col_literal
%type <sval> declaration statements statement
%type <sval> string_list number_list

%right ASSIGN
%left PLUS MINUS
%left MUL DIV
%left INTERSECT UNION
%left EQ NEQ LE GE LT GT
%left SEMICOLON

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%debug

%%

program:
    statements { 
        DEBUG_PRINT("Finished parsing statements");
        fprintf(outfile, "%s", $1);
    }
    ;

declaration:
    INT identifiers SEMICOLON { 
        DEBUG_PRINT("Parsed INT declaration: CPP_%s", $2);
        fprintf(outfile, "    int %s;\n", $2);
        free($2);  // Free after use
    }
    | STR identifiers SEMICOLON { 
        DEBUG_PRINT("Parsed STR declaration: CPP_%s", $2);
        fprintf(outfile, "    std::string %s;\n", $2);
        free($2);  // Free after use
    }
    | SET identifiers SEMICOLON { 
        DEBUG_PRINT("Parsed SET declaration: CPP_%s", $2);
        fprintf(outfile, "    std::set<int> %s;\n", $2);
        free($2);  // Free after use
    }
    | COLLECTION identifiers SEMICOLON { 
        DEBUG_PRINT("Parsed COLLECTION declaration: CPP_%s", $2);
        fprintf(outfile, "    std::set<std::string> %s;\n", $2);
        free($2);  // Free after use
    }
    ;





identifiers:
    identifier { 
        DEBUG_PRINT("Parsed single identifier: %s", $1);
        $$ = $1;  // Ownership is transferred, no need to free here
    }
    | identifiers COMMA identifier { 
        DEBUG_PRINT("Parsed multiple identifiers: %s, %s", $1, $3);
        char* temp; 
        asprintf(&temp, "%s, %s", $1, $3); 
        free($1);  // Free previous concatenated string
        free($3);  // Free the current identifier string
        $$ = temp; // Transfer ownership of the concatenated result
    }
    ;



identifier:
    IDENTIFIER { 
        DEBUG_PRINT("Parsed identifier: %s", $1);
        if (strcmp($1, "class") == 0) {
            $$ = strdup("CPP_class");
        } else {
            char* temp;
            asprintf(&temp, "CPP_%s", $1);
            free($1);
            $$ = temp;
        }
    }
    ;

statements:
    /* empty */ { 
        $$ = strdup(""); 
    }
    | statements statement {
        asprintf(&$$, "%s%s", $1, $2);  // Don't free $1 or $2 for testing
    }
    ;


statement:
    declaration
    | expression SEMICOLON { 
        DEBUG_PRINT("Parsed expression statement");
        fprintf(outfile, "    %s;\n", $1); 
        free($1);  // Free the expression string
    }
    | INPUT STRING_LITERAL identifier SEMICOLON { 
        DEBUG_PRINT("Parsed INPUT statement");
        fprintf(outfile, "    std::cout << %s;\n    std::cin >> %s;\n", $2, $3); 
        free($2);  // Free the input string
        free($3);  // Free the identifier
    }
    | OUTPUT STRING_LITERAL expression SEMICOLON { 
        DEBUG_PRINT("Parsed OUTPUT statement");
        fprintf(outfile, "    std::cout << %s << %s << std::endl;\n", $2, $3);
        free($2);  // Free the output string
        free($3);  // Free the expression string
    }
    | IF LPAREN condition RPAREN statement %prec LOWER_THAN_ELSE {
        DEBUG_PRINT("Parsed IF statement");
        fprintf(outfile, "    if (%s) {\n    %s    }\n", $3, $5);
        free($3);  // Free the condition
        free($5);  // Free the inner statement
    }
    | IF LPAREN condition RPAREN statement ELSE statement {
        DEBUG_PRINT("Parsed IF-ELSE statement");
        fprintf(outfile, "    if (%s) {\n    %s    } else {\n    %s    }\n", $3, $5, $7);
        free($3);  // Free the condition
        free($5);  // Free the if-statement
        free($7);  // Free the else-statement
    }
    | WHILE LPAREN condition RPAREN LBRACE statements RBRACE { 
        DEBUG_PRINT("Parsed WHILE statement");
        fprintf(outfile, "    while (%s) {\n%s    }\n", $3, $6); 
        free($3);  // Free the condition
        free($6);  // Free the statements inside the loop
    }
    | FOR LPAREN identifier COLON identifier RPAREN LBRACE statements RBRACE { 
        DEBUG_PRINT("Statements: %s", $8);
        DEBUG_PRINT("Parsed FOR statement: for (%s : %s)", $3, $5);
        fprintf(outfile, "    for (const auto& %s : %s) {\n", $3, $5); 
        fprintf(outfile, "%s", $8);  // Output the statements correctly
        fprintf(outfile, "    }\n");
        free($3);  // Free the first identifier
        free($5);  // Free the second identifier
        free($8);  // Free the inner statements
    }
    | identifier ASSIGN expression SEMICOLON { 
        DEBUG_PRINT("Parsed assignment: %s = %s", $1, $3);
        fprintf(outfile, "    %s = %s;\n", $1, $3);
        free($1);  // Free the identifier
        free($3);  // Free the expression
    }
    | identifier ASSIGN col_literal SEMICOLON {
        DEBUG_PRINT("Parsed assignment of collection: %s = %s", $1, $3);
        fprintf(outfile, "    CPP_%s = %s;\n", $1, $3);  // Use CPP_ prefix here
        free($1);  // Free identifier string
        free($3);  // Free collection literal
    }
    | identifier ASSIGN set_literal SEMICOLON {
        DEBUG_PRINT("Parsed assignment of set: %s = %s", $1, $3);
        fprintf(outfile, "    CPP_%s = %s;\n", $1, $3);  // Use CPP_ prefix here
        free($1);  // Free identifier string
        free($3);  // Free set literal
    }
    ;

expression:
    NUMBER { 
        DEBUG_PRINT("Parsed NUMBER: %d", $1);
        asprintf(&$$, "%d", $1); 
    }
    | STRING_LITERAL { 
        DEBUG_PRINT("Parsed STRING_LITERAL: %s", $1);
        $$ = $1; 
    }
    | set_literal { 
        DEBUG_PRINT("Parsed set_literal");
        $$ = $1; 
    }
    | col_literal { 
        DEBUG_PRINT("Parsed col_literal");
        $$ = $1; 
    }
    | identifier { 
        DEBUG_PRINT("Parsed identifier in expression: %s", $1);
        $$ = $1; 
    }
    | expression PLUS expression {
        DEBUG_PRINT("Parsed addition");
        asprintf(&$$, "(%s + %s)", $1, $3);
        free($1);
        free($3);
    }
    | expression MINUS expression { 
        DEBUG_PRINT("Parsed subtraction");
        asprintf(&$$, "(%s - %s)", $1, $3); 
        free($1); 
        free($3); 
    }
    | expression MUL expression { 
        DEBUG_PRINT("Parsed multiplication");
        asprintf(&$$, "(%s * %s)", $1, $3); 
        free($1); 
        free($3); 
    }
    | expression DIV expression { 
        DEBUG_PRINT("Parsed division");
        asprintf(&$$, "(%s / %s)", $1, $3); 
        free($1); 
        free($3); 
    }
    | expression INTERSECT expression { 
        DEBUG_PRINT("Parsed intersection");
        asprintf(&$$, "intersection(%s, %s)", $1, $3); 
        free($1); 
        free($3); 
    }
    | expression UNION expression { 
        DEBUG_PRINT("Parsed union");
        asprintf(&$$, "union_sets(%s, %s)", $1, $3); 
        free($1); 
        free($3); 
    }
    | LPAREN expression RPAREN { 
        DEBUG_PRINT("Parsed parenthesized expression");
        asprintf(&$$, "(%s)", $2); 
        free($2); 
    }
    ;

condition:
    expression { 
        DEBUG_PRINT("Parsed condition (single expression)");
        $$ = $1; 
    }
    | expression EQ expression { 
        DEBUG_PRINT("Parsed equality condition");
        asprintf(&$$, "(%s == %s)", $1, $3); 
        free($1); 
        free($3); 
    }
    | expression NEQ expression { 
        DEBUG_PRINT("Parsed inequality condition");
        asprintf(&$$, "(%s != %s)", $1, $3); 
        free($1); 
        free($3); 
    }
    | expression LT expression { 
        DEBUG_PRINT("Parsed less than condition");
        asprintf(&$$, "(%s < %s)", $1, $3); 
        free($1); 
        free($3); 
    }
    | expression LE expression { 
        DEBUG_PRINT("Parsed less than or equal condition");
        asprintf(&$$, "(%s <= %s)", $1, $3); 
        free($1); 
        free($3); 
    }
    | expression GT expression { 
        DEBUG_PRINT("Parsed greater than condition");
        asprintf(&$$, "(%s > %s)", $1, $3); 
        free($1); 
        free($3); 
    }
    | expression GE expression { 
        DEBUG_PRINT("Parsed greater than or equal condition");
        asprintf(&$$, "(%s >= %s)", $1, $3); 
        free($1); 
        free($3); 
    }
    ;

set_literal:
    LBRACKET number_list RBRACKET { 
        DEBUG_PRINT("Parsed set literal");
        asprintf(&$$, "{%s}", $2); 
        free($2); 
    }
    ;

number_list:
    NUMBER { 
        DEBUG_PRINT("Parsed single number in list: %d", $1);
        asprintf(&$$, "%d", $1); 
    }
    | number_list COMMA NUMBER {
        DEBUG_PRINT("Parsed multiple numbers in list");
        asprintf(&$$, "%s, %d", $1, $3);
        free($1);
    }
    | /* empty */ { 
        DEBUG_PRINT("Parsed empty number list");
        $$ = strdup(""); 
    }
    ;

col_literal:
    LBRACE string_list RBRACE { 
        DEBUG_PRINT("Parsed collection literal: %s", $2);
        asprintf(&$$, "{%s}", $2); 
        free($2); 
    }
    | LBRACE RBRACE { 
        DEBUG_PRINT("Parsed empty collection literal");
        $$ = strdup("{}"); 
    }
    ;


string_list:
    STRING_LITERAL {
        DEBUG_PRINT("Parsed single string in list: %s", $1);
        $$ = $1;  // $1 is passed on, no need to free it here
    }
    | string_list COMMA STRING_LITERAL {
        DEBUG_PRINT("Parsed multiple strings in list: %s, %s", $1, $3);
        char* temp;
        asprintf(&temp, "%s, %s", $1, $3);
        free($1);  // Free the previous string list
        free($3);  // Free the current string
        $$ = temp; // Store the concatenated result
    }
    ;



%%

symrec *putsym(const char *sym_name, int sym_type) {
    symrec *ptr = (symrec *)malloc(sizeof(symrec));
    ptr->name = (char *)malloc(strlen(sym_name) + 1);
    strcpy(ptr->name, sym_name);
    ptr->type = sym_type;
    ptr->next = sym_table;
    sym_table = ptr;
    return ptr;
}

symrec *getsym(const char *sym_name) {
    symrec *ptr;
    for (ptr = sym_table; ptr != NULL; ptr = ptr->next)
        if (strcmp(ptr->name, sym_name) == 0)
            return ptr;
    return NULL;
}

std::set<int> intersection(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

std::set<int> union_sets(const std::set<int>& a, const std::set<int>& b) {
    std::set<int> result = a;
    result.insert(b.begin(), b.end());
    return result;
}

std::set<std::string> intersection(const std::set<std::string>& a, const std::set<std::string>& b) {
    std::set<std::string> result;
    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));
    return result;
}

std::set<std::string> union_sets(const std::set<std::string>& a, const std::set<std::string>& b) {
    std::set<std::string> result = a;
    result.insert(b.begin(), b.end());
    return result;
}

int isSetOrCollection(const char* var) {
    symrec* symbol = getsym(var);
    if (symbol) {
        return (symbol->type == SET || symbol->type == COLLECTION);
    }
    return 0;
}

int main(int argc, char **argv) {
    yydebug = 1;  // Enable debug output

    outfile = fopen("output.cpp", "w");
    if (!outfile) {
        fprintf(stderr, "Error opening output file\n");
        return 1;
    }
    debugfile = fopen("debug.log", "w");
    if (!debugfile) {
        fprintf(stderr, "Error opening debug file\n");
        return 1;
    }

    ++argv, --argc;
    if (argc > 0)
        yyin = fopen(argv[0], "r");
    else
        yyin = stdin;

    // Output the header for C++ file
    fprintf(outfile, "#include <iostream>\n#include <set>\n#include <string>\n#include <algorithm>\n\n");

     // Output the intersection and union functions
    fprintf(outfile, "std::set<int> intersection(const std::set<int>& a, const std::set<int>& b) {\n");
    fprintf(outfile, "    std::set<int> result;\n");
    fprintf(outfile, "    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));\n");
    fprintf(outfile, "    return result;\n");
    fprintf(outfile, "}\n\n");

    fprintf(outfile, "std::set<int> union_sets(const std::set<int>& a, const std::set<int>& b) {\n");
    fprintf(outfile, "    std::set<int> result = a;\n");
    fprintf(outfile, "    result.insert(b.begin(), b.end());\n");
    fprintf(outfile, "    return result;\n");
    fprintf(outfile, "}\n\n");

    fprintf(outfile, "std::set<std::string> intersection(const std::set<std::string>& a, const std::set<std::string>& b) {\n");
    fprintf(outfile, "    std::set<std::string> result;\n");
    fprintf(outfile, "    std::set_intersection(a.begin(), a.end(), b.begin(), b.end(), std::inserter(result, result.begin()));\n");
    fprintf(outfile, "    return result;\n");
    fprintf(outfile, "}\n\n");

    fprintf(outfile, "std::set<std::string> union_sets(const std::set<std::string>& a, const std::set<std::string>& b) {\n");
    fprintf(outfile, "    std::set<std::string> result = a;\n");
    fprintf(outfile, "    result.insert(b.begin(), b.end());\n");
    fprintf(outfile, "    return result;\n");
    fprintf(outfile, "}\n\n");

    fprintf(outfile, "std::ostream& operator<<(std::ostream& os, const std::set<std::string>& set) { os << \"{\"; for (auto it = set.begin(); it != set.end(); ++it) { if (it != set.begin()) os << \", \"; os << *it; } os << \"}\"; return os; }\n");

    // Output the main function header
    fprintf(outfile, "int main() {\n");

    yyparse();

    // Output the generated code to the output file

    // Output the closing brace for main function
    fprintf(outfile, "    return 0;\n}\n");

    fclose(outfile);
    fclose(debugfile);
    // free(declarations);
    // free(statements);
    return 0;
}
