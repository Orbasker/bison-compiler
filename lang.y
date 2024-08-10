%{
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <set>
#include <algorithm>
#include "lang.tab.h"
#include "SyntaxTree.hpp"

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
char* declarations;
char* statements;


extern FILE *yyin;
extern int yylex();
extern int yylineno;
extern int yydebug;

int isSetOrCollection(const char* var);
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


// declarations:
//     /* empty */ { declarations = strdup(""); }
//     | declarations declaration { 
//         char* temp; 
//         asprintf(&temp, "%s%s", declarations, $2); 
//         free(declarations); 
//         free($2); 
//         declarations = temp; 
//     }
//     ;

declaration:
    INT identifiers SEMICOLON { asprintf(&$$, "int %s;\n", $2); free($2); }
    | STR identifiers SEMICOLON { asprintf(&$$, "std::string %s;\n", $2); free($2); }
    | SET identifiers SEMICOLON { asprintf(&$$, "std::set<int> %s;\n", $2); free($2); }
    | COLLECTION identifiers SEMICOLON { asprintf(&$$, "std::set<std::string> %s;\n", $2); free($2); }
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
        char* temp;
        asprintf(&temp, "CPP_%s", $1);
        free($1);
        $$ = temp;
     }
    ;

statements:
    /* empty */ { statements = strdup(""); }
    | statements statement { 
        char* temp; 
        asprintf(&temp, "%s%s", statements, $2); 
        free(statements); 
        free($2); 
        statements = temp; 
    }
    ;

statement:
    declaration { 
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
        // else if (strstr($3, "-") != NULL && strstr($3, "&") != NULL) {
        //     // Case: Difference and intersection together
        //     char* leftSide = strtok($3, "-");
        //     char* rightSide = strtok(NULL, "-");
        //     asprintf(&$$, "std::cout << %s << (%s - intersection(%s, %s)) << std::endl;\n", $2, leftSide, rightSide, rightSide);
        // }
        // else if (strstr($3, "-") != NULL) {
        //     // Case: Set difference
        //     char* leftSide = strtok($3, "-");
        //     char* rightSide = strtok(NULL, "-");
        //     asprintf(&$$, "std::cout << %s << (%s - %s) << std::endl;\n", $2, leftSide, rightSide);
        // }
        else if (strstr($3, "+") != NULL) {
            // Generate code to compute the union of sets using union_sets function
            asprintf(&$$, "std::cout << %s << union_sets%s, %s << std::endl;\n", $2, strtok($3, "+"), strtok(NULL, "+"));
        }
        else {
            asprintf(&$$, "std::cout << %s << %s << std::endl;\n", $2, $3);
        }
        free($2); 
        free($3); 
    }
    | IF LPAREN condition RPAREN statement %prec LOWER_THAN_ELSE {
        asprintf(&$$, "if (%s) {\n%s}\n", $3, $5);
        free($3);
        free($5);
    }
    | IF LPAREN condition RPAREN statement ELSE statement {
        asprintf(&$$, "if (%s) {\n%s} else {\n%s}\n", $3, $5, $7);
        free($3);
        free($5);
        free($7);
    }
    | IF LPAREN condition RPAREN LBRACE statements RBRACE {
        asprintf(&$$, "if (%s) {\n%s}\n", $3, $6);
        free($3);
        free($6);
    }
    | IF LPAREN condition RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE {
        asprintf(&$$, "if (%s) {\n%s} else {\n%s}\n", $3, $6, $10);
        free($3);
        free($6);
        free($10);
    }
    | IF LPAREN condition RPAREN LBRACE statements RBRACE ELSE statement {
        asprintf(&$$, "if (%s) {\n%s} else {\n%s}\n", $3, $6, $9);
        free($3);
        free($6);
        free($9);
    }
    // | IF LPAREN condition RPAREN statement { 
    //     asprintf(&$$, "if (%s) %s", $3, $5); 
    //     free($3); 
    //     free($5); 
    // }
    // | IF LPAREN condition RPAREN statement ELSE statement { 
    //     asprintf(&$$, "if (%s) %s else %s", $3, $5, $7); 
    //     free($3); 
    //     free($5); 
    //     free($7); 
    // }
    
    // | IF LPAREN condition RPAREN LBRACE statements RBRACE { 
    //     asprintf(&$$, "if (%s) {\n%s}\n", $3, $6); 
    //     free($3); 
    //     free($6);
    // }
    // | IF LPAREN condition RPAREN LBRACE statements RBRACE ELSE LBRACE statements RBRACE { 
    //     asprintf(&$$, "if (%s) {\n%s} else {\n%s}\n", $3, $6, $10); 
    //     free($3); 
    //     free($6); 
    //     free($10);
    // }
    | WHILE condition LBRACE statements RBRACE { 
        asprintf(&$$, "while (%s) {\n%s}\n", $2, $4); 
        free($2); 
        free($4); 
    }
    | FOR identifier COLON identifier LBRACE statements RBRACE { 
        asprintf(&$$, "for (const auto& %s : %s) {\n%s}\n", $2, $4, $6); 
        free($2); 
        free($4); 
        free($6); 
    }
    | identifier ASSIGN expression SEMICOLON { 
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
            // Case 4: Simple assignment
            asprintf(&$$, "%s = %s;\n", $1, $3); 
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
    | identifier { $$ = $1; }
    | identifier ASSIGN expression { 
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
        if (strstr($1, "{") != NULL || strstr($3, "{") != NULL) {
            asprintf(&$$, "%s + %s", $1, $3);
        } 
        else if (strstr($3, "{") != NULL) {
            asprintf(&$$, "%s.insert(%s)", $1, $3);
        }
        else {
            asprintf(&$$, "(%s + %s)", $1, $3);
        }
        free($1);
        free($3);
    }
    | expression MINUS expression { 
         char* temp; 
        asprintf(&temp, "intersection(%s, %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | expression MUL expression { 
        char* temp; 
        asprintf(&temp, "(%s * %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | expression DIV expression { 
        char* temp; 
        asprintf(&temp, "(%s / %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | expression INTERSECT expression { 
        char* temp; 
        asprintf(&temp, "intersection(%s, %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | expression UNION expression { 
        char* temp; 
        asprintf(&temp, "union_sets(%s, %s)", $1, $3); 
        free($1); 
        free($3); 
        $$ = temp; 
    }
    | LPAREN expression RPAREN { 
        char* temp; 
        asprintf(&temp, "(%s)", $2); 
        free($2); 
        $$ = temp; 
    }
    ;

condition:
    expression EQ expression { 
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
    // | expression {
    //     char* temp; 
    //     asprintf(&temp, "(%s)", $1);
    //     free($1);
    //     $$ = temp;
    // }
    // | LPAREN expression RPAREN {
    //     char* temp;
    //     asprintf(&temp, "%s", $2);  // Just pass through the expression
    //     free($2);
    //     $$ = temp;
    // }
    // | LPAREN identifier RPAREN {
    //     $$ = strdup($2);  // Handle a single identifier as a condition
    // }
    
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
    symrec* symbol = getsym(var);
    if (symbol) {
        return (symbol->type == SET || symbol->type == COLLECTION);
    }
    return 0;
}

int main(int argc, char **argv) {
    yydebug = 1;  // Enable debug output
    declarations = strdup("");
    statements = strdup("");

    outfile = fopen("output.cpp", "w");
    if (!outfile) {
        fprintf(stderr, "Error opening output file\n");
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
    fprintf(outfile, "%s", statements);

    // Output the closing brace for main function
    fprintf(outfile, "    return 0;\n}\n");

    fclose(outfile);
    free(declarations);
    free(statements);
    return 0;
}
