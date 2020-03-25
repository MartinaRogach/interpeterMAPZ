#include "parser.h"
#include <iostream>
using namespace std;

QList<Node*> Parser::createTree(bool isBody) {
    QList<Node*> tree;
    tree.clear();
    cout << "create tree";
    while(pointer < tokenstream.size()) {
        if(isBody && tokenstream[pointer].data == "}" || tokenstream[pointer].data == "}") {
            return tree;
        } else if (tokenstream[pointer].data == "var" && tokenstream[pointer + 2].data == "=") {
            tree.push_back(parseInit());
        } else if (tokenstream[pointer].data == "var") {
            tree.push_back(parseVarDecl());
            pointer++;
        } else if(tokenstream[pointer].type == TokenType::VARIABLE && tokenstream[pointer + 1].data == "=") {
                tree.push_back(parseVariable());
        } else if(tokenstream[pointer].data == "if") {
            tree.push_back(parseIf());
        }
        else if(tokenstream[pointer].data == "cycle") {
            tree.push_back(parseCycle());
        }
        else if (tokenstream[pointer].data == "print") {
            tree.push_back(parsePrint());
        }
        if(pointer < tokenstream.size() && (tokenstream[pointer].data != ";" && tokenstream[pointer].data != "}")) {
            Exception exception("Missing ';' after " + tokenstream[pointer - 1].data);
            exception.raise();
        }
        pointer++;
    }
    if(isBody) {
        Exception exception("Missing '}' after " + tokenstream[pointer-1].data);
        exception.raise();
    }
    return tree;
}

VarDecl* Parser::parseVarDecl() {
    VarDecl* node = new VarDecl();
    pointer++;
    node->id = tokenstream[pointer].data;
    return node;
}

VarInit *Parser::parseInit() {
    VarInit* node = new VarInit();
    node->decl = parseVarDecl();
    node->assign = parseVariable();
    return node;
}

VarAssign* Parser::parseVariable() {
    cout << "parse var assigh";
    VarAssign* node = new VarAssign();
    node->var = new Variable(tokenstream[pointer].data);
    pointer++;
    if(pointer < tokenstream.size() && tokenstream[pointer].data == "=") {
        pointer++;
        node->rval = parseExpression();
        return node;
    }
    Exception exception("Missing '=' after " + tokenstream[pointer-1].data);
    exception.raise();
}

Expression *Parser::parseExpression() {
    cout << "parse expression";
    Expression* expr;
    if(pointer + 1 < tokenstream.size() && tokenstream[pointer+1].type == TokenType::OPERATOR) {
        expr = parseBinaryOperation();
    } else if (tokenstream[pointer].type == TokenType::LITERAL) {
        expr = new Literal(tokenstream[pointer].data);
        pointer++;
    } else if (tokenstream[pointer].type == TokenType::REGEX) {
        expr = new Regex(tokenstream[pointer].data);
        pointer++;
    } else if(pointer < tokenstream.size() && tokenstream[pointer].type == TokenType::VARIABLE) {
        expr = new Variable(tokenstream[pointer].data);
        pointer++;
    }
    else {
        Exception exception("Expression is wrong");
        exception.raise();
    }
    return expr;
}


BinaryOperation *Parser::parseBinaryOperation() {
    BinaryOperation *node = new BinaryOperation();
    Token old = tokenstream.takeAt(pointer + 1);
    node->left = parseExpression();
    node->right = parseExpression();
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
    return node;
}

If *Parser::parseIf() {
    If* node = new If();
    pointer++;
    node->check = parseExpression();
    node->body = parseBody();
    return node;
}

Print *Parser::parsePrint() {
    Print *node = new Print();
    pointer++;
    node->value = parseExpression();
    return node;
}

Cycle *Parser::parseCycle() {
    Cycle* node = new Cycle();
    pointer++;
    if(pointer < tokenstream.size() && tokenstream[pointer].type == TokenType::VARIABLE) node->check = parseExpression();
    else {
        Exception exception("Missing assign after " + tokenstream[pointer-1].data);
        exception.raise();
    }
    node->body = parseBody();
    return node;
}


void Parser::printTree(QList<Node*> tree,QTreeWidget *trwdg) {
    trwdg->clear();
    while(!tree.isEmpty()) {
        trwdg->addTopLevelItem(tree.first()->print());
        tree.pop_front();
    }
}
