#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QMessageBox>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_pushButton_clicked() {

    ui->treeWidget->clear();
    ui->listWidget->clear();
    try {
        QString a= ui->textEdit->toPlainText();
        LexAnalysis lx(a);
        QList<Token> ourTokens = lx.splitByToken();
        for(int i = 0; i< ourTokens.size();++i){
            QString text = "";
            if (ourTokens[i].type == TokenType::SEPARATOR) text = "SEPARATOR";
            else if (ourTokens[i].type == TokenType::KEYWORD) text = "KEYWORD";
            else if (ourTokens[i].type == TokenType::LITERAL) text = "LITERAL";
            else if (ourTokens[i].type == TokenType::OPERATOR) text = "OPERATOR";
            else if (ourTokens[i].type == TokenType::VARIABLE) text = "VARIABLE";
            else if (ourTokens[i].type == TokenType::BRACKETS) text = "BRACKETS";
            else if (ourTokens[i].type == TokenType::REGEX) text = "REGEX";
            ui->listWidget->addItem(QString(ourTokens[i].data + " " + text));
        }
        QList<Token> variableList = lx.variableList;
        Parser parser(ourTokens);
        parser.variableList = variableList;
        QList<Node*> tree = parser.createTree(false);
        parser.printTree(tree,ui->treeWidget);

        Interpreter inter(tree);
        inter.evaluate();

        ui->tableWidget->setRowCount(inter.symboltable.size());
        for (int i = 0; i < inter.symboltable.size(); ++i) {
            for (int j = 0; j < 3; ++j) {
                ui->tableWidget->setItem(i,j,new QTableWidgetItem(""));
            }
        }
        QList<QString> keys = inter.symboltable.keys();
        for (int i = 0; i < inter.symboltable.size(); ++i) {
            ui->tableWidget->item(i,0)->setText(keys[i]);
            ui->tableWidget->item(i,1)->setText(inter.symboltable[keys[i]]);
        }
    } catch (Exception &tokenexcept) {
        QMessageBox box;
        box.setText(tokenexcept.What());
        box.exec();
    }
}
