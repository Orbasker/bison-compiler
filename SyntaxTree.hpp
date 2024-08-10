#ifndef SYNTAX_TREE_HPP
#define SYNTAX_TREE_HPP

#include <string>
#include <list>
#include <set>
#include <algorithm>
#include <iterator>

class SyntaxTree
{
public:
    virtual std::string toString() = 0;
    virtual ~SyntaxTree() {}
};

// Define the rest of your SyntaxTree classes here

class Expression : public SyntaxTree
{
public:
    std::string toString();
    Expression(SyntaxTree *, int, SyntaxTree *);
    Expression(int, SyntaxTree *);
    Expression(int, SyntaxTree *, int);

private:
    SyntaxTree *left;
    int op;
    SyntaxTree *right;
};

class SizeExpression : public SyntaxTree
{
public:
    SizeExpression(SyntaxTree *variable);
    std::string toString();

private:
    SyntaxTree *variable;
};

class Block : public SyntaxTree
{
public:
    std::string toString();
    Block();
    void add(SyntaxTree *);

private:
    std::list<SyntaxTree *> stmtList;
};

class Assignment : public SyntaxTree
{
public:
    std::string toString();
    Assignment(SyntaxTree *, SyntaxTree *);

private:
    SyntaxTree *left;
    SyntaxTree *right;
};

class Declaration : public SyntaxTree
{
public:
    std::string toString();
    Declaration(int, SyntaxTree *);

private:
    SyntaxTree *varList;
    int type;
};

class Variable : public SyntaxTree
{
public:
    std::string toString();
    std::string varName;
    Variable(std::string);
};

class VariableList : public SyntaxTree
{
public:
    std::string toString();
    VariableList(SyntaxTree *);
    void add(SyntaxTree *);
    std::list<SyntaxTree *> get();

private:
    std::list<SyntaxTree *> varList;
};

class Constant : public SyntaxTree
{
public:
    std::string toString();
    Constant(int);

private:
    int value;
};

class Set : public SyntaxTree
{
public:
    std::string toString();
    Set();
    std::list<SyntaxTree *> intList;
};

class Collection : public SyntaxTree
{
public:
    std::string toString();
    Collection();
    std::list<SyntaxTree *> strList;
};

class If : public SyntaxTree
{
public:
    If(SyntaxTree *cond, SyntaxTree *block, SyntaxTree *elseBlock);
    std::string toString();

private:
    SyntaxTree *cond;
    SyntaxTree *block;
    SyntaxTree *elseBlock;
};

class While : public SyntaxTree
{
public:
    std::string toString();
    While(SyntaxTree *, SyntaxTree *);

private:
    SyntaxTree *cond;
    SyntaxTree *block;
};

class Condition : public SyntaxTree
{
public:
    std::string toString();
    Condition(SyntaxTree *var, SyntaxTree *collection);

private:
    SyntaxTree *var;
    SyntaxTree *collection;
};

class For : public SyntaxTree
{
public:
    std::string toString();
    For(SyntaxTree *cond, SyntaxTree *block);

private:
    SyntaxTree *cond;
    SyntaxTree *block;
};

class Input : public SyntaxTree
{
public:
    Input(SyntaxTree *l);
    std::string toString();
    void add(SyntaxTree *exp);

private:
    std::list<SyntaxTree *> expList;
};

class Print : public SyntaxTree
{
public:
    Print(SyntaxTree *l);
    std::string toString();
    void add(SyntaxTree *exp);

private:
    std::list<SyntaxTree *> expList;
};

class strings : public SyntaxTree
{
public:
    strings();
    void add(SyntaxTree *);
    std::string toString();

private:
    std::list<SyntaxTree *> strList;
};

#endif // SYNTAX_TREE_HPP
