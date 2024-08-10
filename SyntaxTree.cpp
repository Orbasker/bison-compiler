#include "SyntaxTree.hpp"

#define INT_T 1
#define STR_T 2
#define SET_T 3
#define COLLECTION_T 4

#define UNUSED(x) (void)(x)

Expression::Expression(SyntaxTree *l, int o, SyntaxTree *r)
    : left(l), op(o), right(r) {}
Expression::Expression(int o, SyntaxTree *operand)
    : left(operand), op(o) {}
Expression::Expression(int o1, SyntaxTree *operand, int o2)
    : left(operand), op('(')
{
    UNUSED(o1);
    UNUSED(o2);
}

Block::Block() {}

Assignment::Assignment(SyntaxTree *l, SyntaxTree *r) : left(l), right(r) {}

Declaration::Declaration(int typ, SyntaxTree *list) : varList(list), type(typ) {}

Variable::Variable(std::string name) : varName(name) {}

VariableList::VariableList(SyntaxTree *initial)
{
    varList.push_back(initial);
}

Constant::Constant(int val) : value(val) {}

Set::Set() {}

Collection::Collection() {}

While::While(SyntaxTree *c, SyntaxTree *b) : cond(c), block(b) {}

std::string Expression::toString()
{
    std::string leftSide = left->toString();
    std::string rightSide;
    if (op != 'N' && op != '(')
        rightSide = right->toString();

    switch (op)
    {
    case '+':
        return leftSide + " + " + rightSide;
    case '-':
        return leftSide + " - " + rightSide;
    case '*':
        return leftSide + " * " + rightSide;
    case '/':
        return leftSide + " / " + rightSide;
    case 'G':
        return leftSide + " >= " + rightSide;
    case 'L':
        return leftSide + " <= " + rightSide;
    case '=':
        return leftSide + " == " + rightSide;
    case '!':
        return leftSide + " != " + rightSide;
    case '<':
        return leftSide + " < " + rightSide;
    case '>':
        return leftSide + " > " + rightSide;
    case '&':
        return leftSide + " & " + rightSide;
    case '(':
        return "( " + leftSide + " )";
    case 'N':
        return "-" + leftSide;
    }

    return "??";
}

std::string Block::toString()
{
    std::string result = "{\n";
    for (SyntaxTree *el : stmtList)
    {
        result += el->toString() + ";\n";
    }
    result += "}";
    return result;
}

void Block::add(SyntaxTree *el)
{
    stmtList.push_back(el);
}

std::string Assignment::toString()
{
    return left->toString() + " = " + right->toString();
}

std::string Declaration::toString()
{
    std::string typeStr;

    switch (type)
    {
    case INT_T:
        typeStr = "int";
        break;
    case STR_T:
        typeStr = "std::string";
        break;
    case SET_T:
        typeStr = "Set";
        break;
    case COLLECTION_T:
        typeStr = "Collection";
        break;
    default:
        typeStr = "unknown";
        break;
    }

    std::string result = typeStr + " " + varList->toString();
    return result;
}

std::string Variable::toString()
{
    return varName;
}

std::string VariableList::toString()
{
    std::string result;
    bool first = true;
    for (SyntaxTree *el : varList)
    {
        if (!first)
        {
            result += ",";
        }
        result += el->toString();
        first = false;
    }
    return result;
}

std::list<SyntaxTree *> VariableList::get()
{
    return varList;
}

void VariableList::add(SyntaxTree *el)
{
    varList.push_back(el);
}

std::string Constant::toString()
{
    return std::to_string(value);
}

std::string Set::toString()
{
    std::string result = "{";
    if (intList.size() > 0)
    {
        SyntaxTree *first = intList.front();
        intList.pop_front();
        result += first->toString();
        for (SyntaxTree *i : intList)
        {
            result += "," + i->toString();
        }
    }
    result += "}";
    return result;
}

std::string Collection::toString()
{
    std::string result = "Collection{";
    if (strList.size() > 0)
    {
        SyntaxTree *first = strList.front();
        strList.pop_front();
        result += "\"" + first->toString() + "\"";
        for (SyntaxTree *i : strList)
        {
            result += ",\"" + i->toString() + "\"";
        }
    }
    result += "}";
    return result;
}

std::string While::toString()
{
    return "while( " + cond->toString() + " )" + block->toString();
}

If::If(SyntaxTree *cond, SyntaxTree *block, SyntaxTree *elseBlock = nullptr)
    : cond(cond), block(block), elseBlock(elseBlock) {}

std::string If::toString()
{
    std::string result = "if (" + cond->toString() + ") " + block->toString() + ";\n";
    if (elseBlock != nullptr)
    {
        result += "else " + elseBlock->toString();
    }
    return result;
}

Print::Print(SyntaxTree *l)
{
    expList.push_back(l);
}

void Print::add(SyntaxTree *exp)
{
    expList.push_back(exp);
}

std::string Print::toString()
{
    std::string result = "std::cout << ";
    bool first = true;

    for (SyntaxTree *exp : expList)
    {
        if (first)
        {
            // The first expression is a string
            result += "\"" + exp->toString() + "\" << \" \" << ";
            first = false;
        }
        else
        {
            // Subsequent expressions are variables
            result += "(" + exp->toString() + ") << \" \" << ";
        }
    }

    result += "std::endl";
    return result;
}

For::For(SyntaxTree *c, SyntaxTree *b) : cond(c), block(b) {}

std::string For::toString()
{
    return "for(const auto& " + cond->toString() + ") " + block->toString();
}

Condition::Condition(SyntaxTree *v, SyntaxTree *c) : var(v), collection(c) {}

std::string Condition::toString()
{
    return var->toString() + " : " + collection->toString();
}

Input::Input(SyntaxTree *l)
{
    expList.push_back(l);
}

void Input::add(SyntaxTree *exp)
{
    expList.push_back(exp);
}

std::string Input::toString()
{
    std::string result;
    bool first = true;

    for (SyntaxTree *exp : expList)
    {
        if (first)
        {
            // The first expression is a string
            result += "std::cout << \"" + exp->toString() + "\" << std::endl;\n";
            first = false;
        }
        else
        {
            // Subsequent expressions are variables
            result += "std::cin >> " + exp->toString();
        }
    }

    return result;
}

SizeExpression::SizeExpression(SyntaxTree *var) : variable(var) {}

std::string SizeExpression::toString()
{
    return variable->toString() + ".size()";
}

strings::strings() {}

void strings::add(SyntaxTree *el)
{
    strList.push_back(el);
}

std::string strings::toString()
{
    std::string result;
    bool first = true;
    for (SyntaxTree *el : strList)
    {
        if (!first)
        {
            result += ",";
        }
        result += "\"" + el->toString() + "\"";
        first = false;
    }
    return result;
}
