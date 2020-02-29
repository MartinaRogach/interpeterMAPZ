#ifndef MYINTER_H
#define MYINTER_H
#include <QString>
#include <QVector>
#include <QList>
#include <QMap>
#include <iostream>
using namespace std;
enum TokenType {
    KEYWORD,
    CONST,
    VARIABLE,
   //CONDITIONAL,
   //CYCLE,
   //FUNCTION,
    OPERATOR,
    BRAKETS,
    SEPARATORS,
    LITERALS
};
//var myVar = "hello people";


class Token {
public:
    QString data;
    TokenType type;
    Token(QString DATA, TokenType TYPE) {
        data = DATA;
        type = TYPE;
    }
};


class LexAnalysis {
public:
    QString text;
    QList<Token> tokens;

    LexAnalysis(QString code) {
        text = code;
       lexicalAnalysis();
    }
    QList<Token> splitByToken();

private:
    QList<Token> getTokensByType(TokenType type);
    void lexicalAnalysis();


};


#endif // MYINTER_H
