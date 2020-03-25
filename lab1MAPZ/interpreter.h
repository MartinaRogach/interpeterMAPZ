#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <QList>
#include <QMap>
#include "statements.h"

class Interpreter {
public:
    QList<Node*> tree;
    QMap<QString, QString> symboltable;
    void evaluate();
    Interpreter(QList<Node*> Tree):tree{Tree}{}
    ~Interpreter(){}
};

#endif // INTERPRETER_H
