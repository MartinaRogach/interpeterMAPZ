#ifndef STATEMENTS_H
#define STATEMENTS_H_H
#include <QTreeWidget>

class Node {
public:
    virtual QTreeWidgetItem* print() = 0;
    virtual ~Node(){}
};

class Expression: public Node {
public:
    QTreeWidgetItem * print(){}
    ~Expression(){}
};

class Statement: public Node {
public:
    QTreeWidgetItem* print(){}
    ~Statement(){}
};

class Body: public Node {
public:
    QList<Node*> subtree;
    QTreeWidgetItem* print();
    ~Body(){}
};

class Variable: public Expression {
public:
    QString id;
    QTreeWidgetItem* print();
    Variable(QString ident):id{ident}{}
    Variable(){}
    ~Variable(){}
};

class VarDecl: public Node {
public:
    QTreeWidgetItem* print();
    QString id;
    VarDecl(QString ID):id{ID}{}
    VarDecl(){}
    ~VarDecl(){}
};

class VarAssign: public Statement {
public:
    Variable* var;
    Expression* rval;
    QTreeWidgetItem *print();
    VarAssign(Variable* Var, Expression* Rval):var{Var},rval{Rval}{}
    VarAssign(){}
    ~VarAssign(){}
};

class VarInit: public Node {
public:
    VarDecl* decl;
    VarAssign* assign;
    QTreeWidgetItem * print();
    VarInit(VarDecl* Decl, VarAssign* Assign):decl{Decl},assign{Assign}{}
    VarInit(){}
    ~VarInit(){}
};

class BinOp: public Expression {
public:
    Expression* left;
    QString op;
    Expression* right;
    QTreeWidgetItem * print();
    BinOp(Expression* Left, QString Op, Expression* Right):left{Left},op{Op},right{Right}{}
    BinOp(){}
    ~BinOp(){}
};

class Constant: public Expression {
public:
    QString value;
    QTreeWidgetItem* print(){}
    Constant(QString val): value{val}{}
    ~Constant(){}
};

class IfStmt: public Statement {
public:
    Expression* expr;
    Body* body;
    QTreeWidgetItem * print();
    IfStmt(Expression* expression,Body* Body):expr{expression},body{Body}{}
    IfStmt(){}
    ~IfStmt(){}
};

class ForStmt: public Statement {
public:
    Node* init;
    Expression* test;
    Expression* update;
    Body* stmts;
    QTreeWidgetItem * print();
    ForStmt(){}
    ~ForStmt(){}
};

#endif // STATEMENTS_H
