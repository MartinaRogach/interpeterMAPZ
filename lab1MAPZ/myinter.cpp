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
    this->tokens.append(Token(QString(";"), TokenType::SEPARATORS));
}



QList<Token> LexAnalysis::splitByToken(){
   int position = 0;
    QString word;
    QList<Token> tokens;

    while(position<text.length())
    {
        word = "";
        if(text[position].isSpace())
        {
            position++;
        }

        if(text[position] == )








        if(text[position].isLetter())
        {
            while(text[position].isLetterOrNumber())
            {
                word.append(text[position]);
                position++;
            }
            tokens.append(Token(word, TokenType::VARIABLE));
            continue;
        }
        if(text[position].isDigit())
        {
            while(text[position].isDigit())
            {
                word.append(text[position]);
                position++;
            }
            tokens.append(Token(word,Tag::LITERAL));
            continue;
        }
        if(text[position] == "\"")
        {
            do
            {
                word.append(text[position]);
                position++;
            }while(text[position] != "\"" && position<text.length());
            word.append("\"");
            tokens.append(Token(word,Tag::LITERAL));
            position++;
            continue;
        }
        if(text[position] == ";" || text[position] == "{" || text[position] == "}" )
        {
            word.append(text[position]);
            position++;
            tokens.append(Token(word,Tag::SEPARATORS));
            continue;
        }
        if(text[position] == "#")
        {
            while(text[position] != "\n" && position<text.length())
            {
                word.append(text[position]);
                position++;
            }
            tokens.append(Token(word,Tag::COMMENTS));
            continue;
        }
        if(text[position] == "=" || text[position] == ">" || text[position] == "<")
        {
            if(text[position] == "=" && text[position+1] == "=")
            {
                tokens.append(Token("==",Tag::OPERATOR));
            }
            else
            {
                word.append(text[position]);
                tokens.append(Token(word,Tag::OPERATOR));
            }
            position++;
            continue;
        }
        else
        {
            //add exeption
            position++;
        }
    }
*/
    return tokens;

}
