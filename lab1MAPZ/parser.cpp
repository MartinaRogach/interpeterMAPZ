#include "parser.h"
#include <iostream>
using namespace std;

QList<Node*> Parser::createTree(bool isBody) {
    QList<Node*> tree;
    tree.clear();
    cout << "create tree";
    while(pointer < tokenstream.size()) {
        if(isBody && tokenstream[pointer].data == "}") {
            return tree;
        } else if(tokenstream[pointer].type == TokenType::KEYWORD && tokenstream[pointer].data == "var") {
//            if(ifPresentinVariableList(tokenstream[pointer])) {
//                tree.push_back(parseVarAssign());
//            } else {
                tree.push_back(parseInit());
//            }
            cout << "variable token";

        }
//        } else if(tokenstream[pointer].data == "if") {
//            tree.push_back(parseIf());
//        }
////        else if(tokenstream[pointer].data == "cycle") {
////            tree.push_back(parseFor());
////        }
//        if(pointer < tokenstream.size() && tokenstream[pointer].data != ";") {
//            Exception exception("Missing ';' after " + tokenstream[pointer - 1].data);
//            exception.raise();
//        }
        pointer++;
    }
    if(isBody ) {
        Exception exception("Missing '}' after " + tokenstream[pointer-1].data);
        exception.raise();
    }
    return tree;
}

VarDecl* Parser::parseVarDecl() {
    VarDecl* node = new VarDecl();
    pointer++;
    if(pointer < tokenstream.size() && tokenstream[pointer].type == TokenType::VARIABLE) {
        node->id = parseId();
        return node;
    }
    Exception exception("Missing ID after " + tokenstream[pointer-1].data);
    exception.raise();
}

QString Parser::parseId() {
    QString val = tokenstream[pointer].data;
    pointer++;
    return val;
}

VarInit *Parser::parseInit() {
    VarInit* init = new VarInit();
    init->decl = parseVarDecl();
//    pointer--;
//    init->assign = parseVarAssign();
//    return init;
}

VarAssign* Parser::parseVarAssign() {
    cout << "parse var assigh";
    VarAssign* node = new VarAssign();
    node->var = new Variable(tokenstream[pointer].data);
    pointer++;
    return node;
//    if(pointer < tokenstream.size() && tokenstream[pointer].data == "=") {
//        pointer++;
//        node->rval = parseExpr();
//        return node;
//    }
    Exception exception("Missing '=' after " + tokenstream[pointer-1].data);
    exception.raise();
}

Expression *Parser::parseExpr() {
    cout << "parse expression";
    Expression* expr;
    if(pointer + 1 < tokenstream.size() && tokenstream[pointer+1].type == TokenType::OPERATOR) expr = parseBinOp();
    else if(pointer < tokenstream.size() && tokenstream[pointer].type == TokenType::VARIABLE) {
        expr = new Variable(tokenstream[pointer].data);
        pointer++;
    }
    else if(pointer < tokenstream.size() && tokenstream[pointer].type == TokenType::LITERAL) expr = parseConst();
    else {
        Exception exception("Expression is wrong");
        exception.raise();
    }
    return expr;
}

Constant *Parser::parseConst() {
    QRegExp re("\d");
    Constant *constant;
    constant = new Constant(tokenstream[pointer].data);
    pointer++;
    return constant;
}


BinOp *Parser::parseBinOp() {
    BinOp *node = new BinOp();
    Token old = tokenstream.takeAt(pointer + 1);
    node->left = parseExpr();
    node->right = parseExpr();
    node->op = old.data;
    pointer--;
    tokenstream.insert(pointer, old);
    pointer += 2;
    return node;
}

Body *Parser::parseBody() {
    if(pointer >= tokenstream.size() || tokenstream[pointer].data != '{') {
        Exception exception("Missing '{' after " + tokenstream[pointer-1].data);
        exception.raise();
    }
    pointer++;
    Body* node = new Body();
    node->subtree = createTree(true);
    pointer++;
    return node;
}

IfStmt *Parser::parseIf() {
    IfStmt* node = new IfStmt();
    pointer++;
    node->expr = parseExpr();
    node->body = parseBody();
    pointer++;
    return node;
}

//ForStmt *Parser::parseFor() {
//    ForStmt* node = new ForStmt();
//    pointer++;
//    if(pointer < tokenstream.size() && tokenstream[pointer].tag == Tag::TYPE) node->init = parseInit();
//    else if(pointer < tokenstream.size() && tokenstream[pointer].tag == Tag::IDENTIFIER) node->init = parseVarAssign();
//    else {
//        Exception exception("Missing Init or Assign after " + tokenstream[pointer-1].data);
//        exception.raise();
//    }
//    node->test = parseExpr();
//    node->update = parseExpr();
//    node->stmts = parseBody();
//    return node;
//}


void Parser::printTree(QList<Node*> tree,QTreeWidget *trwdg) {
    trwdg->clear();
    while(!tree.isEmpty()) {
        trwdg->addTopLevelItem(tree.first()->print());
        tree.pop_front();
    }
}
