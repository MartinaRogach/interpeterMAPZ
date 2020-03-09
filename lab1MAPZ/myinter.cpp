#include "myinter.h"

void LexAnalysis::lexicalAnalysis() {
    QVector<QString> keyword;
    keyword<<"if"<<"cycle"<<"var"<<"function";
    for(int i = 0; i<keyword.size();++i){
        this->tokens.append(Token(keyword[i],TokenType::KEYWORD ));
    }
    QVector<QString> operators;
    operators<<"+"<<"="<< "==";
    for(int i=0; i<operators.size();++i){
        this->tokens.append(Token(operators[i],TokenType::OPERATOR));
    }
    this->tokens.append(Token(QString(";"), TokenType::SEPARATOR));
}

QList<Token> LexAnalysis::splitByToken(){
    int position = 0;
    QString word;
    QList<Token> tokens;

    while(position<text.length()) {
        word = "";
        if(text[position].isSpace()) {
            position++;
        }

        if(text[position] ==";"){
            word=text[position];
            tokens.append(Token(word,TokenType::SEPARATOR));
            ++position;
            continue;
        }
        if(text[position]=="\"" ){
            word+=text[position];
            ++position;
            while(text[position]!="\""){
                word+=text[position];
                ++position;
            }
            word+=text[position];
            tokens.append(Token(word, TokenType::LITERAL));
            ++position;
            continue;
        }
        QList<Token> operators = getTokensByType(TokenType::OPERATOR);
        for(int i =0; i<operators.size();++i){
            for(int j=0; j<operators[i].data.size();++j){
                if(text[position] == operators[i].data[j]){
                    word += text[position];
                    ++position;
                }
            }
        }
        if(!word.isEmpty()){
            tokens.append(Token(word, TokenType::OPERATOR));
            continue;
        }
        QList<Token> keywords = getTokensByType(TokenType::KEYWORD);
        for(int i =0; i<keywords.size();++i){
            for(int j=0; j<keywords[i].data.size();++j){
                if(text[position] == keywords[i].data[j]){
                    word += text[position];
                    ++position;
                }
            }
        }
        if(!word.isEmpty()){
            tokens.append(Token(word, TokenType::KEYWORD));
            continue;
        }
        if(text[position].isLetter()) {
            while(text[position].isLetterOrNumber()) {
                word.append(text[position]);
                position++;
            }
            variableList.append(Token(word, TokenType::VARIABLE));
            tokens.append(Token(word, TokenType::VARIABLE));
            continue;
        }
    }
    return tokens;
}

QList<Token> LexAnalysis:: getTokensByType(TokenType type){
    QList<Token> tokensByType;
    for(int i = 0;i<this->tokens.size(); ++i){
        if(this->tokens[i].type == type){
            tokensByType.append(this->tokens[i]);
        }
    }
    return tokensByType;
}
