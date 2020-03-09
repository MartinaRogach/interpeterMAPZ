#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <QException>

class Exception: public QException {
private:
    QString Msg;
public:
    void raise() const override { throw *this; }
    Exception* clone() const override {return new Exception(*this);}
    Exception(QString msg):Msg{ msg }{}
    QString What(){ return Msg; }
};

#endif // EXCEPTION_H
