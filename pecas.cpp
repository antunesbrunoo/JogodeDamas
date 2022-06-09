#include <QPainter>
#include <QPen>
#include <QMouseEvent>
#include <QMessageBox>
#include "pecas.h"


Pecas::Pecas(QWidget *parent, int x, int y)
    : QLabel{parent}
{
    Coluna = x;
    Linha = y;
    if (Linha < 4){
        cor = true;
    }else{
        cor = false;
    }
}
Pecas::Pecas(QWidget *parent, int x, int y, bool Cor)
    : QLabel{parent}
{
    Coluna = x;
    Linha = y;
    this->cor= Cor;
}

Pecas::~Pecas(){}
bool Pecas::getCor(){
    return cor;
}
void Pecas:: setColuna(int n){
    Coluna = n;
}
void Pecas:: setLinha(int n){
    Linha = n;
}
int Pecas:: getColuna(){
    return Coluna;
}
int Pecas:: getLinha(){
    return Linha;
}

void Pecas:: paintEvent(QPaintEvent* e){
    QPainter p(this);
    QPen pen;
    pen.setColor(Qt::black);
    p.setPen(pen);
    p.drawRect(0,0,width()-1, height()-1);
    if(getCor()== true){
        p.setBrush(Qt::red);
    }else{
        p.setBrush(Qt::blue);
    }
    p.drawEllipse(10,10,60,60);
}

void Pecas::mousePressEvent(QMouseEvent* event){
    try{
        if(event->button() == Qt::LeftButton) {
            emit mover(true);
        }
        else if(event->button() == Qt::RightButton) {
            emit mover(false);
        }
    }
    catch(int e){
        QMessageBox::about(this, "Erro", "Movimento Indevido");
    }
}
