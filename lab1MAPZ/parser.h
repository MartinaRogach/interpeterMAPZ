#ifndef PARSER_H
#define PARSER_H
#include "interpreter.h"
#include "myinter.h"

class Parser {
public:
    QList<Token> tokenstream;
    int pointer = 0;
    QList<Token> variableList;
    void addVariableToList();
    QList<Node*> createTree(bool isBody);
    VarAssign* parseVariable();
    VarDecl* parseVarDecl();
    VarInit* parseInit();
    Expression* parseExpression();
    BinaryOperation* parseBinaryOperation();
    Body* parseBody();
    If* parseIf();
    Cycle* parseCycle();
    Print* parsePrint();
    void printTree(QList<Node*> tree,QTreeWidget *trwdg);
    Parser(QList<Token> tokens) {
        tokenstream = tokens;
    }

    bool ifPresentinVariableList(Token token) {
        for (int i = 0; i < variableList.count(); ++i) {
            if (token.data == variableList[i].data) {
                return true;
            }
        }
        return false;
    }
};


#endif // PARSER_H
