#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString a= ui->textEdit->toPlainText();
    LexAnalysis lx(a);
    QList<Token> ourTokens = lx.splitByToken();
    for(int i = 0; i< ourTokens.size();++i){
        ui->listWidget->addItem(QString(ourTokens[i].data + " "+ QString::number(ourTokens[i].type)));
                //setText(QString(ourTokens[i].data + " "+ ourTokens[i].type));
    }

}
