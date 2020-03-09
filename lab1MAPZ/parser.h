#ifndef PARSER_H
#define PARSER_H
#include "statements.h"
#include "myinter.h"
#include "exception.h"

class Parser {
public:
    QList<Token> tokenstream;
    int pointer = 0;
    QList<Token> variableList;
    void addVariableToList();
    QList<Node*> createTree(bool isBody);
    VarDecl* parseVarDecl();
    VarAssign* parseVarAssign();
    QString parseId();
    VarInit* parseInit();
    Expression* parseExpr();
    Constant *parseConst();
    BinOp* parseBinOp();
    Body* parseBody();
    IfStmt* parseIf();
//    ForStmt* parseFor();
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
