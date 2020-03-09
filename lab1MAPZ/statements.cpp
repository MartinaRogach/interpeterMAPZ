#include "statements.h"

QTreeWidgetItem* VarDecl::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    QTreeWidgetItem* ident = new QTreeWidgetItem();
    item->setText(0,"VarDecl");
    ident->setText(0,id);
    item->addChild(ident);
    return item;
}


QTreeWidgetItem* VarAssign::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,"=");
    item->addChild(var->print());
    item->addChild(rval->print());
    return item;
}

QTreeWidgetItem* Variable::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,id);
    return item;
}

QTreeWidgetItem* VarInit::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,"VarInit");
    item->addChild(decl->print());
    item->addChild(assign->print());
    return item;
}

QTreeWidgetItem* BinOp::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,op);
    item->addChild(left->print());
    item->addChild(right->print());
    return item;
}

QTreeWidgetItem* IfStmt::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,"ifstmt");
    item->addChild(expr->print());
    item->addChild(body->print());
    return item;
}

QTreeWidgetItem* Body::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,"Body");
    for(int i = 0; i < subtree.size();i++)
    {
        item->addChild(subtree[i]->print());
    }
    return item;
}

QTreeWidgetItem* ForStmt::print() {
    QTreeWidgetItem* item = new QTreeWidgetItem();
    item->setText(0,"ForStmt");
    item->addChild(init->print());
    item->addChild(test->print());
    item->addChild(update->print());
    item->addChild(stmts->print());

    return item;
}
