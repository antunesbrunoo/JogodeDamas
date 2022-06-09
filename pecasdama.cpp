#include "pecasdama.h"
#include "pecasGeral.h"
#include <QPainter>
#include <QPen>

pecasDama::pecasDama(QWidget *parent, bool Cor)
    :QLabel{parent}
{
    this->cor=Cor;
}

bool pecasDama::getCor(){
    return this->cor;
}
int pecasDama::getColuna(){
    return this->Coluna;
}
int pecasDama::getLinha(){
    return this->Linha;
}

void pecasDama:: paintEvent(QPaintEvent* e){
    QPainter p(this);
    QPen pen;
    pen.setColor(Qt::black);
    p.setPen(pen);
    p.drawRect(0,0,width()-1, height()-1);
    if(getCor()== true){
        p.setBrush(Qt::green);
    }else{
        p.setBrush(Qt::yellow);
    }
    p.drawEllipse(10,10,60,60);
}
