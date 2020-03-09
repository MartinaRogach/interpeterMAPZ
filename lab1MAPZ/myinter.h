#ifndef MYINTER_H
#define MYINTER_H
#include <QString>
#include <QList>

using namespace std;
enum TokenType {
    KEYWORD,
    CONST,
    VARIABLE,
    OPERATOR,
    UNAROPERATOR,
    BRAKETS,
    SEPARATOR,
    LITERAL
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
    QList<Token> variableList;
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
