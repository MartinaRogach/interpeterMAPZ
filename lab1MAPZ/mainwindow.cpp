#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
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
        ui->listWidget->addItem(QString(ourTokens[i].data + " " + text));
    }
    QList<Token> variableList = lx.variableList;
    Parser parser(ourTokens);
    parser.variableList = variableList;
    cout << "main window";
    QList<Node*> tree = parser.createTree(false);
    parser.printTree(tree,ui->treeWidget);
}
