#ifndef MYINTER_H
#define MYINTER_H
#include <QString>
#include <QVector>
#include <QList>
#include <QMap>

enum tokenType{
                CONST,
                VARIABLE,
                CONDITIONAL,
                CYCLE,
                FUNCTION,
                OPERATOR,
                BRAKETS,
                SEPARATORS
};


class Token{
public:
    Token(QString DATA,tokenType TYPE){data = DATA; type = TYPE;}
    QString data;
    tokenType type;
};


QList<Token> lexicalAnalysis(QString code){
    
    
}


#endif // MYINTER_H
