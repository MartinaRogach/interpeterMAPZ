#include "statements.h"
#include <QDebug>

QTreeWidgetItem* VarDecl::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    QTreeWidgetItem* ident = new QTreeWidgetItem();
    item->setText(0,"VarDeclaration");
    ident->setText(0,id);
    item->addChild(ident);
    return item;
}

QString VarDecl::evaluate(QMap<QString, QString> &table) {
    if(!table.contains(id)) {
        table.insert(id,"");
        return "";
    }
    Exception exp("Variable is already declared!");
    exp.raise();
}

QTreeWidgetItem* VarAssign::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,"=");
    item->addChild(var->print());
    item->addChild(rval->print());
    return item;
}

QString VarAssign::evaluate(QMap<QString, QString>& table) {
    QString id = var->id;
    if (table.contains(id)) {
        QString value = rval->evaluate(table);
        table.insert(id, value);
        return "";
    }
    Exception exp("Variable " + id + " is not declared!");
    exp.raise();
}

QTreeWidgetItem* VarInit::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,"VarInit");
    item->addChild(decl->print());
    item->addChild(assign->print());
    return item;
}

QString VarInit::evaluate(QMap<QString, QString> &table) {
    decl->evaluate(table);
    assign->evaluate(table);
    return "";
}

QTreeWidgetItem* Variable::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,id);
    return item;
}

QString Variable::evaluate(QMap<QString, QString>& table) {
    if (table.contains(id)) {
        return table[id];
    }
    Exception exception("Variable is not declared");
    exception.raise();
}

QTreeWidgetItem* Literal::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, value);
    return item;
}

QString Literal::evaluate(QMap<QString, QString>& table) {
    return value;
}

QTreeWidgetItem* Regex::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0, value);
    return item;
}

QString Regex::evaluate(QMap<QString, QString>& table) {
    return value;
}

QTreeWidgetItem* BinaryOperation::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,op);
    item->addChild(left->print());
    item->addChild(right->print());
    return item;
}

QString BinaryOperation::evaluate(QMap<QString, QString>& table) {
    QString left = this->left->evaluate(table);
    QString right = this->right->evaluate(table);
    if (op == "has") {
        Regex reg(right);
        reg.replace();
        QRegularExpression regular(reg.value);
        QRegularExpressionMatch match = regular.match(left);
        bool hasMatch = match.hasMatch();
        if (hasMatch) {
            return "1";
        } else {
            return "0";
        }
    } else if (op == "capture") {
        Regex reg(right);
        reg.replace();
        QRegularExpression regular(reg.value);
        QRegularExpressionMatch match = regular.match(left);
        bool hasMatch = match.hasMatch();
        if (hasMatch) {
            return match.captured(0);
        } else {
            return "";
        }
    } else if (op == "remove") {
        int index = left.indexOf(right);
        left.replace(index, right.size(), "");
        return left;
    }
    return "";
}

QTreeWidgetItem* If::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,"if");
    item->addChild(check->print());
    item->addChild(body->print());
    return item;
}

QString If::evaluate(QMap<QString, QString> &table) {
    if(check->evaluate(table).toInt()){
        body->evaluate(table);
    }
    return "";
}

QTreeWidgetItem* Print::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,"print");
    item->addChild(value->print());
    return item;
}

QString Print::evaluate(QMap<QString, QString>& table) {
    QString id = "print";
    QString value = this->value->evaluate(table);
    table.insert(id, value);
    return "";
}

QTreeWidgetItem* Body::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,"body");
    for(int i = 0; i < subtree.size();i++) {
        item->addChild(subtree[i]->print());
    }
    return item;
}

QString Body::evaluate(QMap<QString, QString> &table) {
    while(!subtree.isEmpty()) {
        subtree.takeFirst()->evaluate(table);
    }
    return "";
}

QTreeWidgetItem* Cycle::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,"cycle");
    item->addChild(check->print());
    item->addChild(body->print());
    return item;
}

QString Cycle::evaluate(QMap<QString, QString> &table) {
    while(check->evaluate(table).toInt()){
        Body tmp = *body;
        body->evaluate(table);
        *body = tmp;
    }
    return "";
}
