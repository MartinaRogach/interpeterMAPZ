#ifndef STATEMENTS_H
#define STATEMENTS_H_H
#include <QTreeWidget>
#include "exception.h"

class Node {
public:
    virtual QTreeWidgetItem* print() = 0;
    virtual QString evaluate(QMap<QString, QString>& table) = 0;
    virtual ~Node(){}
};

class Expression: public Node {
public:
    QTreeWidgetItem * print(){}
    QString evaluate(QMap<QString, QString>& table){}
    ~Expression(){}
};

class Statement: public Node {
public:
    QTreeWidgetItem* print(){}
    QString evaluate(QMap<QString, QString>& table){}
    ~Statement(){}
};

class Variable: public Expression {
public:
    QString id;
    QTreeWidgetItem* print();
    QString evaluate(QMap<QString, QString>& table);
    Variable(QString ident):id{ident}{}
    Variable(){}
    ~Variable(){}
};

class Literal: public Expression {
public:
    QString value;
    QTreeWidgetItem* print();
    QString evaluate(QMap<QString, QString>& table);
    Literal(QString ident):value{ident}{}
    Literal(){}
    ~Literal(){}
};

class VarDecl:public Node {
public:
    QTreeWidgetItem* print();
    QString id;
    QString evaluate(QMap<QString, QString>& table);
    VarDecl(QString ID):id{ID}{}
    VarDecl(){}
    ~VarDecl(){}
};

class VarAssign: public Statement {
public:
    Variable* var;
    Expression* rval;
    QTreeWidgetItem *print();
    QString evaluate(QMap<QString, QString>& table);
    VarAssign(Variable* Var, Expression* Rval):var{Var},rval{Rval}{}
    VarAssign(){}
    ~VarAssign(){}
};

class VarInit:public Node {
public:
    VarDecl* decl;
    VarAssign* assign;
    QTreeWidgetItem * print();
    QString evaluate(QMap<QString, QString>& table);
    VarInit(VarDecl* Decl, VarAssign* Assign):decl{Decl},assign{Assign}{}
    VarInit(){}
    ~VarInit(){}
};

class Body: public Node {
public:
    QList<Node*> subtree;
    QTreeWidgetItem* print();
    QString evaluate(QMap<QString, QString>& table);
    ~Body(){}
};

class BinaryOperation: public Expression {
public:
    Expression* left;
    QString op;
    Expression* right;
    QTreeWidgetItem * print();
    QString evaluate(QMap<QString, QString>& table);
    BinaryOperation(Expression* Left, QString Op, Expression* Right):left{Left},op{Op},right{Right}{}
    BinaryOperation(){}
    ~BinaryOperation(){}
};

class If: public Statement {
public:
    Expression* check;
    Body* body;
    QTreeWidgetItem * print();
    QString evaluate(QMap<QString, QString>& table);
    If(Expression* expression,Body* Body):check{expression},body{Body}{}
    If(){}
    ~If(){}
};

class Cycle: public Statement {
public:
    Expression* check;
    Body* body;
    QTreeWidgetItem * print();
    QString evaluate(QMap<QString, QString>& table);
    Cycle(){}
    ~Cycle(){}
};

class Print: public Statement {
public:
    Expression* value;
    QTreeWidgetItem * print();
    QString evaluate(QMap<QString, QString>& table);
    Print(){}
    ~Print(){}
};

class Regex: public Expression {
public:
    QString value;
    Regex(QString value) {
        this->value = value;
    }
    QTreeWidgetItem* print();
    QString evaluate(QMap<QString, QString>& table);

    void replace() {
        if (value.contains("-")) {
            value.insert(0,"[");
            value.append("]");
        } else if (value.contains("(")) {
            int index1 = value.indexOf("(");
            int index2 = value.indexOf(")");
            value.replace(index1, 1, "{");
            value.replace(index2, 1, "}");
        } else if (value.contains(" ")) {
            int index1 = value.indexOf(" ");
            value.replace(index1, 2, "\\s");
        } else if (value.contains("*")) {
            value.replace(0, 1, ".");
        }
    }
};


#endif // STATEMENTS_H
