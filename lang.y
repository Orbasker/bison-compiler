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
char* declarations;
char* statementsL;


extern FILE *yyin;
extern int yylex();
extern int yylineno;
extern int yydebug;

int isSetOrCollection(const char* var);
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
    statements 
    ;

declaration:
    INT identifiers SEMICOLON { 
        DEBUG_PRINT("Outputting int declaration");
        DEBUG_PRINT("Identifiers from assign: %s", $2);
        asprintf(&$$, "int %s", $2); 
        char* temp = strtok($2, ",");
        while (temp != NULL) {
            putsym(temp, INT);  // Add to symbol table
            temp = strtok(NULL, ",");
        }
        free($2); 
    }
    | STR identifiers SEMICOLON { 
        asprintf(&$$, "std::string %s;\n", $2); 
        char* temp = strtok($2, ",");
        while (temp != NULL) {
            putsym(temp, STR);  // Add to symbol table
            temp = strtok(NULL, ",");
        }
        free($2); 
    }
    | SET identifiers SEMICOLON { 
        asprintf(&$$, "std::set<int> %s;\n", $2); 
        char* temp = strtok($2, ",");
        while (temp != NULL) {
            putsym(temp, SET);  // Add to symbol table
            temp = strtok(NULL, ",");
        }
        free($2); 
    }
    | COLLECTION identifiers SEMICOLON { 
        DEBUG_PRINT("Outputting collection declaration for the following identifiers: %s", $2);
        asprintf(&$$, "std::set<std::string> %s;\n", $2); 
        char* temp = strtok($2, ",");
        while (temp != NULL) {
            putsym(temp, COLLECTION);  // Add to symbol table
            temp = strtok(NULL, ",");
        }
        free($2); 
    }
    ;


identifiers:
    identifier { 
        char* temp;
        asprintf(&temp, "%s", $1);
        free($1);
        $$ = temp;

     }
    | identifiers COMMA identifier { 
        char* temp; 
        asprintf(&temp, "%s,%s", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    ;

identifier:
    IDENTIFIER { 
        DEBUG_PRINT("identifier from identifier: %s", $1);
        char* temp;
        asprintf(&temp, "CPP_%s", $1);
        free($1);
        $$ = temp;
        DEBUG_PRINT("identifier from identifier: %s", $$);
        DEBUG_PRINT("current statement in identifier: %s", statementsL);
     }
    ;

statements:
    /* empty */ { $$ = strdup(""); }
    | statements statement {
        DEBUG_PRINT("Before concatenation: %s", statementsL);
        
        // Accumulate the statements
        char* temp;
        asprintf(&temp, "%s%s", statementsL, $2);
        
        DEBUG_PRINT("After concatenation: %s", temp);
        
        // Update statementsL to accumulate the generated code
        free(statementsL);
        statementsL = temp;
        
        // Pass along the accumulated statements
        $$ = strdup(statementsL);
        
        free($2);  // Free the current statement since it's already added to statementsL
    }
    ;


statement:
    LBRACE statements RBRACE {  
        char* temp;
        asprintf(&temp, "%s", $2);
        free($2);
        $$ = temp;
    }
    | declaration { 
        asprintf(&$$, "%s;\n", $1); 
        free($1);
    } 
    | expression SEMICOLON { 
        asprintf(&$$, "%s;\n", $1); 
        free($1); 
    }
    | INPUT STRING_LITERAL identifier SEMICOLON { 
        asprintf(&$$, "std::cout << %s;\nstd::cin >> %s;\n", $2, $3); 
        free($2); 
        free($3); 
    }
    | OUTPUT STRING_LITERAL SEMICOLON { 
        DEBUG_PRINT("Output string literal: %s", $2);
        asprintf(&$$, "std::cout << %s << std::endl;\n", $2); 
        free($2); 
    }
    | OUTPUT identifier SEMICOLON {
        DEBUG_PRINT("Output identifier: %s", $2);
        int res = isSetOrCollection($2);
        DEBUG_PRINT("isSetOrCollection: %d", res);
        if (res) {
            DEBUG_PRINT("Outputting set or collection");
            asprintf(&$$, "for (const auto& element : %s) {\n"
                        "    std::cout << \" \" << element;\n"
                        "}\n"
                        "std::cout << std::endl;\n", $2);
        } else {
            DEBUG_PRINT("Outputting simple identifier");
            asprintf(&$$, "std::cout << %s << std::endl;\n", $2);
        }
        free($2);
    }
    | OUTPUT STRING_LITERAL expression SEMICOLON { 
        if (isSetOrCollection($3)) {
            asprintf(&$$, "std::cout << %s;\n"
                         "for (const auto& element : %s) {\n"
                         "    std::cout << \" \" << element;\n"
                         "}\n"
                         "std::cout << std::endl;\n", $2, $3);
        }
        else if (strchr($3,MINUS) != NULL)
        {
            char* leftSide = strtok($3, "-");
            char* rightSide = strtok(NULL, "-");
            asprintf(&$$, "std::cout << %s << (%s - intersection(%s, %s)) << std::endl;\n", $2, leftSide, rightSide, rightSide);
        }
        else if (strstr($3, "+") != NULL) {
            // Generate code to compute the union of sets using union_sets function
            asprintf(&$$, "std::cout << %s << union_sets%s, %s << std::endl;\n", $2, strtok($3, "+"), strtok(NULL, "+"));
        }
        else {
            asprintf(&$$, "std::cout << %s << %s << std::endl;\n", $2, $3);
        }
        DEBUG_PRINT("Output string_lteral,expression: %s %s", $2, $3);
        free($2); 
        free($3); 
    }
    | IF LPAREN identifier RPAREN statement %prec LOWER_THAN_ELSE {
        DEBUG_PRINT("Outputting if statement with single statement");
        asprintf(&$$, "if (&%s) {\n%s}\n", $3, $5);
        free($3);
        free($5);
    }
    | IF LPAREN condition RPAREN statement %prec LOWER_THAN_ELSE {
        DEBUG_PRINT("Outputting if statement with single statement");
        asprintf(&$$, "if (%s) {\n%s}\n", $3, $5);
        free($3);
        free($5);
    }
    | IF LPAREN condition RPAREN statement ELSE statement {
        DEBUG_PRINT("Outputting if statement with else statement");
        asprintf(&$$, "if (%s) {\n%s} else {\n%s}\n", $3, $5, $7);
        free($3);
        free($5);
        free($7);
    }
    | IF LPAREN condition RPAREN LBRACE statements RBRACE {
        DEBUG_PRINT("Outputting if statement with multiple statements");
        DEBUG_PRINT("Condition: %s", $3);
        // DEBUG_PRINT("Statements: %s", $$);
        DEBUG_PRINT("Statements from statment: %s", $6);

        char* if_block;
        asprintf(&if_block, "if (%s) {\n%s}\n", $3, $6);

        // Check if_block content
        DEBUG_PRINT("Generated if block: %s", if_block);

        $$ = if_block;

        free($3);
        // free($6);
    }



    | IF LPAREN condition RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE {
        DEBUG_PRINT("Outputting if statement with else block");
        asprintf(&$$, "if (%s) {\n%s} else {\n%s}\n", $3, $6, $10);
        free($3);
        free($6);
        free($10);
    }
    | IF LPAREN condition RPAREN LBRACE statements RBRACE ELSE statement {
        DEBUG_PRINT("Outputting if statement with else statement");
        asprintf(&$$, "if (%s) {\n%s} else {\n%s}\n", $3, $6, $9);
        free($3);
        free($6);
        free($9);
    }
    | WHILE condition LBRACE statements RBRACE { 
        asprintf(&$$, "while (%s) {\n%s}\n", $2, $4); 
        free($2); 
        free($4); 
    }
    | FOR LPAREN identifier COLON identifier RPAREN statement {
        DEBUG_PRINT("Parsing for loop");
        DEBUG_PRINT("Iterator: %s", $3);
        DEBUG_PRINT("Set/Collection: %s", $5);
        DEBUG_PRINT("Body: %s", $7);
        
        char* for_block;
        asprintf(&for_block, "for (const auto& %s : %s) {\n%s}\n", $3, $5, $7);
        
        DEBUG_PRINT("Generated for block: %s", for_block);
        
        $$ = for_block;
        
        free($3);
        free($5);
        free($7);
    }
    | FOR LPAREN NUMBER COLON NUMBER RPAREN statement {
        DEBUG_PRINT("Parsing for loop with number range");
        DEBUG_PRINT("Start: %d", $3);
        DEBUG_PRINT("End: %d", $5);
        DEBUG_PRINT("Body: %s", $7);
        
        char* for_block;
        asprintf(&for_block, "for (int CPP_i = %d; CPP_i <= %d; CPP_i++) {\n%s}\n", $3, $5, $7);
        
        DEBUG_PRINT("Generated for block: %s", for_block);
        
        $$ = for_block;
        
        // Only free the statement, not the integer values
        free($7);
    }
    | FOR LPAREN NUMBER COLON identifier RPAREN LBRACE statements RBRACE {
        DEBUG_PRINT("Parsing for loop with number range and identifier");
        DEBUG_PRINT("Start: %d", $3);
        DEBUG_PRINT("End: %s", $5);
        DEBUG_PRINT("Body: %s", $8);
        
        char* for_block;
        asprintf(&for_block, "for (int CPP_i = %d; CPP_i <= %s; CPP_i++) {\n%s}\n", $3, $5, $8);
        
        DEBUG_PRINT("Generated for block: %s", for_block);
        
        $$ = for_block;
        
        free($5);
        free($8);
    }
    | identifier ASSIGN expression SEMICOLON { 
        DEBUG_PRINT("Outputting assignment statement with expression from statement");
        if (strstr($3, "+") != NULL && strstr($3, "{") != NULL) {
            // Case 1: Adding multiple elements to a collection
            char *plus = strchr($3, '+');
            *plus = '\0';
            char *rightSide = plus + 1;
            while (*rightSide == ' ') rightSide++; // Skip spaces
            asprintf(&$$, "%s.insert(%s);\n", $1, rightSide);
        } else if (strstr($3, "+") != NULL && strchr($3, '"') != NULL) {
            // Case 2: Adding a single string element to a collection
            char *plus = strchr($3, '+');
            *plus = '\0';
            char *rightSide = plus + 1;
            while (*rightSide == ' ') rightSide++; // Skip spaces
            asprintf(&$$, "%s.insert(%s;\n", $1, rightSide);
        } else if (strchr($3, '{') != NULL) {
            // Case 3: Direct assignment of a set/collection
            asprintf(&$$, "%s.insert(%s);\n", $1, $3);
        } else {
            if (isSetOrCollection($1)) {
                DEBUG_PRINT("Outputting set or collection range insertion");
// Case 5: Inserting a range of elements from one set/collection to another
                DEBUG_PRINT("Assign identifier: %s", $1);
                DEBUG_PRINT("Expression: %s", $3);
                
                 // Generate the nested insertion statement
                asprintf(&$$, "%s.insert(%s.begin(), %s.end());\n",
                        $1, $1, $1, $3);

                DEBUG_PRINT("Generated nested insertion: %s", $$);

            } else {
                DEBUG_PRINT("Outputting simple assignment");
                // Case 4: Simple assignment
                asprintf(&$$, "%s = %s;\n", $1, $3); 
            }
            // Case 4: Simple assignment
        }
        free($1);
        free($3);
    }
    

    ;

expression:
    NUMBER { asprintf(&$$, "%d", $1); }
    | STRING_LITERAL { $$ = strdup($1); }
    | set_literal { $$ = $1; }
    | col_literal { $$ = $1; }
    | identifier { 
        DEBUG_PRINT("identifier from expression: %s", $1);
        DEBUG_PRINT("statement from expression at the moment: %s", statementsL);
        char* temp;
        asprintf(&temp, "%s", $1);
        free($1);
        $$ = temp; 
        DEBUG_PRINT("statement from expression at the moment: %s", statementsL);
        }
    | identifier ASSIGN expression { 
        DEBUG_PRINT("Outputting assignment statement with expression from expression");
        if (strstr($3, "+") != NULL && strstr($3, "{") != NULL) {
            char *leftSide = strdup($3);
            char *plus = strchr(leftSide, '+');
            *plus = '\0';
            char *rightSide = plus + 1;
            while (*rightSide == ' ') rightSide++; // Skip spaces
            asprintf(&$$, "%s.insert(%s.begin(), %s.end())", $1, rightSide, rightSide);
            free(leftSide);
        } else if (strstr($3, "{") != NULL) {
            asprintf(&$$, "%s.insert(%s.begin(), %s.end())", $1, $3, $3);
        } else {
            asprintf(&$$, "%s = %s", $1, $3); 
        }
        free($1); 
        free($3); 
    }
    | expression PLUS expression {
        DEBUG_PRINT("Outputting addition expression");
        if (strstr($1, "{") != NULL || strstr($3, "{") != NULL) {
            asprintf(&$$, "%s + %s", $1, $3);
        } 
        else if (isSetOrCollection($1) && isSetOrCollection($3)) {
            asprintf(&$$, "union_sets(%s, %s)", $1, $3);
        }
        else {
            asprintf(&$$, "(%s + %s)", $1, $3);
        }
        free($1);
        free($3);
    }
    | expression MINUS expression { 
        DEBUG_PRINT("Outputting subtraction expression");
         char* temp; 
        asprintf(&temp, "intersection(%s, %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | expression MUL expression { 
        DEBUG_PRINT("Outputting multiplication expression");
        char* temp; 
        asprintf(&temp, "(%s * %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | expression DIV expression { 
        DEBUG_PRINT("Outputting division expression");
        char* temp; 
        asprintf(&temp, "(%s / %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | expression INTERSECT expression { 
        DEBUG_PRINT("Outputting intersection expression");
        char* temp; 
        asprintf(&temp, "intersection(%s, %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | expression UNION expression { 
        DEBUG_PRINT("Outputting union expression");
        char* temp; 
        asprintf(&temp, "union_sets(%s, %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | LPAREN expression RPAREN { 
        DEBUG_PRINT("Outputting expression in parentheses");
        char* temp; 
        asprintf(&temp, "(%s)", $2); 
        free($2); 
        $$ = temp; 
    }
    ;

condition:
    identifier {
        char* temp;
        asprintf(&temp, "&%s", $1);
        free($1);
        $$ = temp;
    }
    | expression EQ expression { 
        DEBUG_PRINT("Outputting equality condition");
        char* temp; 
        asprintf(&temp, "(%s == %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | expression NEQ expression { 
        char* temp; 
        asprintf(&temp, "(%s != %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | expression LT expression { 
        char* temp; 
        asprintf(&temp, "(%s < %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | expression LE expression { 
        char* temp; 
        asprintf(&temp, "(%s <= %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | expression GT expression { 
        char* temp; 
        asprintf(&temp, "(%s > %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | expression GE expression { 
        char* temp; 
        asprintf(&temp, "(%s >= %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    ;

set_literal:
    LBRACKET number_list RBRACKET { 
        asprintf(&$$, "{%s}", $2); 
        free($2); 
    }
    ;

number_list:
    NUMBER { asprintf(&$$, "%d", $1); }
    | number_list COMMA NUMBER {
        char* temp;
        asprintf(&temp, "%s, %d", $1, $3);
        free($1);
        $$ = temp;
    }
    | /* empty */ { $$ = strdup(""); }
    ;

col_literal:
    LBRACE string_list RBRACE { 
        asprintf(&$$, "{%s}", $2); 
        free($2); 
    }
    | LBRACE RBRACE { $$ = strdup("{}"); }
    ;

string_list:
    STRING_LITERAL {
        asprintf(&$$, "%s", $1);
        free($1);
    }
    | string_list COMMA STRING_LITERAL {
        char* temp;
        asprintf(&temp, "%s, %s", $1, $3);
        free($1);
        free($3);
        $$ = temp;
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
    DEBUG_PRINT("Checking if %s is a set or collection", var);
    symrec* symbol = getsym(var);
    // DEBUG_PRINT("Symbol type: %d", symbol->type);
    if (symbol) {
        DEBUG_PRINT("Symbol type: %d", symbol->type);
        return (symbol->type == SET || symbol->type == COLLECTION);
    }
    return 0;
}

int main(int argc, char **argv) {
    yydebug = 1;  // Enable debug output
    declarations = strdup("");
    statementsL = strdup("");

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
    fprintf(outfile, "%s", statementsL);

    // Output the closing brace for main function
    fprintf(outfile, "    return 0;\n}\n");

    fclose(outfile);
    fclose(debugfile);
    free(declarations);
    free(statementsL);
    return 0;
}
