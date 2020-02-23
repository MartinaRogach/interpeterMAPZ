#ifndef MYINTER_H
#define MYINTER_H
#include <QString>
#include <QVector>
#include <QList>
#include <QMap>

enum tokenType {
    CONST,
    VARIABLE,
    CONDITIONAL,
    CYCLE,
    FUNCTION,
    OPERATOR,
    BRAKETS,
    SEPARATORS
};


class Token {
public:
    QString data;
    tokenType type;
    Token(QString DATA, tokenType TYPE) {
        data = DATA;
        type = TYPE;
    }
};


class LexAnalysis {
public:
    QList<Token> tokens;
    LexAnalysis(QString code) {
        tokens = lexicalAnalysis(code);
    }
private:
    QList<Token> lexicalAnalysis(QString code);
};


#endif // MYINTER_H
