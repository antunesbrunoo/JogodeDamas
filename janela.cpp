#include <fstream>
#include <QPainter>
#include "janela.h"
#include "pecas.h"
#include "pecasdama.h"

int Janela :: vezAtual = 0;

Janela::Janela(QWidget *parent)
    : QMainWindow{parent}
{
    this ->setGeometry(100, 100, 800, 720);
    this ->setWindowTitle("Jogo de Damas");

    salvar = new QPushButton("Salvar", this);
    salvar->setGeometry(690, 20, 90, 40);

    carregar = new QPushButton("Continuar", this);
    carregar->setGeometry(690, 80, 90, 40);

    connect(salvar, SIGNAL(clicked(bool)),
            this, SLOT(salvarArquivo()));

    connect(carregar, SIGNAL(clicked(bool)),
            this, SLOT(abrirArquivo()));

    int auxLinha = 20, auxColuna = 0;
    for(int i = 1; i < 9; i++){
       if(!(i%2) == 0){
           auxLinha = 100;
       }else{
           auxLinha = 20;
       }
       for(int j = 1; j < 5; j++){
           int x, y;
           if((i%2) != 0){
               x=(j*2);
               y=(i);
           }else if (i%2 == 0){
               x=(j*2-1);
               y=(i);
           }
           Pecas* p = new Pecas(this, x, y);
           if(i > 0 && i < 4){
               p->setGeometry(auxLinha,auxColuna,80,80);
               connect(p, SIGNAL(mover(bool)), this, SLOT(moverPeca(bool)));
               pecasTotal.push_back(p);
            }else if(i > 5 && i < 9){
               p->setGeometry(auxLinha,auxColuna,80,80);
               connect(p, SIGNAL(mover(bool)), this, SLOT(moverPeca(bool)));
               pecasTotal.push_back(p);
           }else{
               delete p;
           }
           auxLinha += 160;

       }
       auxColuna+=80;
    }
}

Janela* Janela::getInstancia(){
    if(instancia == nullptr)
        instancia = new Janela();
    return instancia;
}

Janela* Janela::instancia = nullptr;

void Janela::paintEvent(QPaintEvent *Tabuleiro){
    QPainter tabuleiro(this);
    tabuleiro.drawRect(QRect(20, 0 , 640, 640));

    QPainter q(this);
    if(this->vezAtual%2==0){
         q.setBrush((Qt::red));
        q.drawRect(QRect(690, 140, 90, 40));

    }else if(this->vezAtual%2!=0){
        q.setBrush((Qt::blue));
        q.drawRect(QRect(690, 140, 90, 40));
    }
    this->update();

    int auxLinha = 20, auxColuna = 0;
    for(int i = 0; i < 8; i++){
        if(i%2 == 0){
            auxLinha = 100;
        }else{
            auxLinha = 20;
        }
        for(int j = 0; j < 4; j++){
                QPainter QuadradoBlack(this);
                QuadradoBlack.setBrush((Qt::black));
                QuadradoBlack.drawRect(QRect(auxLinha, auxColuna , 80, 80));
                auxLinha += 160;
        }
        auxColuna += 80;
     }
}


void Janela::salvarArquivo(){
    std::fstream f("JogoSalvo.txt", std::fstream::out);
    int V = 0, A = 0;
    for(unsigned int i = 0; i < pecasTotal.size(); i++){
        if(pecasTotal.at(i)->getCor() == true){
            V++;
        }else if(pecasTotal.at(i)->getCor() == false && pecasTotal.at(i)->getColuna() != 10){
            A++;
        }
    }
    f << V << "\n";
    for(int i = 0; i < V ; i++){
        f << pecasTotal.at(i)->getLinha() << " " << pecasTotal.at(i)->getColuna() << "\n" ;
    }
    f << A << "\n";
    for(int i = V; i < V+A ; i++){
        f << pecasTotal.at(i)->getLinha() << " " << pecasTotal.at(i)->getColuna() << "\n" ;
    }
    f.close();
}

void Janela::abrirArquivo(){
   for(int i = pecasTotal.size()-1; i >= 0; i--){
        delete(pecasTotal[i]);
    }
    pecasTotal.clear();
    std::fstream f("JogoSalvo.txt", std::fstream::in);
    std::string PecasV;

    while(!f.eof()){
            if(!f.eof()){
                std::getline(f, PecasV);
                int V = std::stoi(PecasV);
                for(int i = 0; i < V; i++){
                    std::string aux, aux2;
                        if (std::getline(f,aux,' '))
                        {
                            std::getline(f,aux2);
                            int Converte1 = std::stoi(aux2);
                            int Converte2 = std::stoi(aux);
                            Pecas* p = new Pecas(this,Converte1, Converte2, true);
                            p->setGeometry(((Converte1-1)*80)+20,((Converte2-2)*80)+80,80,80);
                            connect(p, SIGNAL(mover(bool)), this, SLOT(moverPeca(bool)));
                            pecasTotal.push_back(p);
                            this->update();
                            p->show();

                        }
                }

                std::string PecasA;
                std::getline(f, PecasA);
                int A = std::stoi(PecasA);
                for(int i=V; i < A+V; i++){
                    std::string aux, aux2;
                        if (std::getline(f,aux,' '))
                        {
                            std::getline(f,aux2);
                            int Converte1 = std::stoi(aux2);
                            int Converte2 = std::stoi(aux);
                            Pecas* p = new Pecas(this,Converte1, Converte2, false);
                            p->setGeometry(((Converte1-1)*80)+20,((Converte2-2)*80)+80,80,80);
                            connect(p, SIGNAL(mover(bool)), this, SLOT(moverPeca(bool)));
                            pecasTotal.push_back(p);
                            this->update();
                            p->show();
                        }
                }
            }
            break;
    }
    f.close();
}

void Janela::moverPeca(bool direcao) {
    bool vez;
    if(this->vezAtual%2==0){
         vez = true;

    }else{
        vez = false;
    }
    Pecas *aux;
    int K, I;
    bool podeComer = false;
    for(unsigned int i = 0; i < pecasTotal.size(); i++){
        if(pecasTotal.at(i) == sender()){
           aux = pecasTotal.at(i);
           K = i;
        }
    }

    if((direcao == true) && (aux->getCor() == true) && (vez==true)){
        char PecaAmiga = 'n';// nada, amiga, inimiga

        for(unsigned int i = 0; i < pecasTotal.size(); i++){
            if((aux->getLinha()+1 == pecasTotal.at(i)->getLinha()) && (aux->getColuna()-1 == pecasTotal.at(i)->getColuna())){
                if(aux->getCor() == pecasTotal.at(i)->getCor()){
                    PecaAmiga = 'a';
                } else if(aux->getCor() != pecasTotal.at(i)->getCor()){
                    for(unsigned int i = 0; i < pecasTotal.size(); i++){
                        if((aux->getLinha()+2 == pecasTotal.at(i)->getLinha()) && (aux->getColuna()-2 == pecasTotal.at(i)->getColuna())){
                            podeComer = false;
                            throw 1;
                        }else{
                            podeComer = true;
                        }
                    }
                    PecaAmiga = 'i';
                    I = i;
                }
            }
        }
        if(PecaAmiga == 'n'){
            if(pecasTotal.at(K)->getColuna()!=1 && pecasTotal.at(K)->getLinha()!=8){
                pecasTotal.at(K)->move(pecasTotal.at(K)->pos().x()-80, pecasTotal.at(K)->pos().y()+80);
                pecasTotal.at(K)->setColuna(pecasTotal.at(K)->getColuna()-1);
                pecasTotal.at(K)->setLinha(pecasTotal.at(K)->getLinha()+1);
                Janela:: vezAtual++;

            }
        }else if(PecaAmiga == 'a'){
            throw 1;
        }else if(PecaAmiga == 'i' && podeComer == true){
                if(pecasTotal.at(K)->getColuna()!=2 && pecasTotal.at(K)->getLinha()!=7){
                    pecasTotal.at(K)->move(pecasTotal.at(K)->pos().x()-160, pecasTotal.at(K)->pos().y()+160);
                    pecasTotal.at(K)->setColuna(pecasTotal.at(K)->getColuna()-2);
                    pecasTotal.at(K)->setLinha(pecasTotal.at(K)->getLinha()+2);
                    delete (pecasTotal[I]);
                    pecasTotal.erase(pecasTotal.begin()+I);
                    Janela:: vezAtual++;
                }

        }
        if (pecasTotal.at(K)->getLinha()==8){
            pecasDama *p =new pecasDama(this, true);
            p->setGeometry(((pecasTotal.at(K)->getColuna()-1)*80)+20,(pecasTotal.at(K)->getLinha()-1)*80,80,80);
            p->update();
            p->show();

        }

    }else if((direcao == false) && (aux->getCor()== true) && (vez==true)){
        char PecaAmiga = 'n';
        for(unsigned int i = 0; i < pecasTotal.size(); i++){
            if((aux->getLinha()+1 == pecasTotal.at(i)->getLinha()) && (aux->getColuna()+1 == pecasTotal.at(i)->getColuna())){
                if(aux->getCor() == pecasTotal.at(i)->getCor()){
                    PecaAmiga = 'a';
                } else if(aux->getCor() != pecasTotal.at(i)->getCor()){
                    for(unsigned int i = 0; i < pecasTotal.size(); i++){
                        if((aux->getLinha()+2 == pecasTotal.at(i)->getLinha()) && (aux->getColuna()+2 == pecasTotal.at(i)->getColuna())){
                            podeComer = false;
                            throw 1;
                        }else{
                            podeComer = true;
                        }
                    }
                    PecaAmiga = 'i';
                    I = i;
                }
            }
        }
        if(PecaAmiga == 'n'){
            if(pecasTotal.at(K)->getColuna()!=8 && pecasTotal.at(K)->getLinha()!=8){
                pecasTotal.at(K)->move(pecasTotal.at(K)->pos().x()+80, pecasTotal.at(K)->pos().y()+80);
                pecasTotal.at(K)->setColuna(pecasTotal.at(K)->getColuna()+1);
                pecasTotal.at(K)->setLinha(pecasTotal.at(K)->getLinha()+1);
                Janela:: vezAtual++;
            }
        }else if(PecaAmiga == 'a'){
            throw 1;
        }else if(PecaAmiga == 'i' && podeComer == true){
                if(pecasTotal.at(K)->getColuna()!=7 && pecasTotal.at(K)->getLinha()!=7){
                    pecasTotal.at(K)->move(pecasTotal.at(K)->pos().x()+160, pecasTotal.at(K)->pos().y()+160);
                    pecasTotal.at(K)->setColuna(pecasTotal.at(K)->getColuna()+2);
                    pecasTotal.at(K)->setLinha(pecasTotal.at(K)->getLinha()+2);
                    delete (pecasTotal[I]);
                    pecasTotal.erase(pecasTotal.begin()+I);
                    Janela:: vezAtual++;
                }

        }
        if (pecasTotal.at(K)->getLinha()==8){
            pecasDama *p =new pecasDama(this, true);
            p->setGeometry(((pecasTotal.at(K)->getColuna()-1)*80)+20,(pecasTotal.at(K)->getLinha()-1)*80,80,80);
            p->update();
            p->show();

        }

    }else if ((direcao == true) && (aux->getCor()== false) && (vez==false)){
        char PecaAmiga = 'n';
        for(unsigned int i = 0; i < pecasTotal.size(); i++){
            if((aux->getLinha()-1 == pecasTotal.at(i)->getLinha()) && (aux->getColuna()-1 == pecasTotal.at(i)->getColuna())){
                if(aux->getCor() == pecasTotal.at(i)->getCor()){
                    PecaAmiga = 'a';
                } else if(aux->getCor() != pecasTotal.at(i)->getCor()){
                    for(unsigned int i = 0; i < pecasTotal.size(); i++){
                        if((aux->getLinha()-2 == pecasTotal.at(i)->getLinha()) && (aux->getColuna()-2 == pecasTotal.at(i)->getColuna())){
                            podeComer = false;
                            throw 1;
                        }else{
                            podeComer = true;
                        }
                    }
                    PecaAmiga = 'i';
                    I = i;
                }
            }
        }
        if(PecaAmiga == 'n'){
            if(pecasTotal.at(K)->getColuna()!=1 && pecasTotal.at(K)->getLinha()!=1){
                pecasTotal.at(K)->move(pecasTotal.at(K)->pos().x()-80, pecasTotal.at(K)->pos().y()-80);
                pecasTotal.at(K)->setColuna(pecasTotal.at(K)->getColuna()-1);
                pecasTotal.at(K)->setLinha(pecasTotal.at(K)->getLinha()-1);
                Janela:: vezAtual++;
            }
        }else if(PecaAmiga == 'a'){
            throw 1;
        }else if(PecaAmiga == 'i' && podeComer == true){
                if(pecasTotal.at(K)->getColuna()!=2 && pecasTotal.at(K)->getLinha()!=2){
                    pecasTotal.at(K)->move(pecasTotal.at(K)->pos().x()-160, pecasTotal.at(K)->pos().y()-160);
                    pecasTotal.at(K)->setColuna(pecasTotal.at(K)->getColuna()-2);
                    pecasTotal.at(K)->setLinha(pecasTotal.at(K)->getLinha()-2);
                    delete (pecasTotal[I]);
                    pecasTotal.erase(pecasTotal.begin()+I);
                    Janela:: vezAtual++;
                }

        }
        if (pecasTotal.at(K)->getLinha()==1){
            pecasDama *p =new pecasDama(this, false);
            p->setGeometry(((pecasTotal.at(K)->getColuna()-1)*80)+20,(pecasTotal.at(K)->getLinha()-1)*80,80,80);
            p->update();
            p->show();

        }

    }else if ((direcao == false && aux->getCor()== false) && (vez==false)){
        char PecaAmiga = 'n';
        for(unsigned int i = 0; i < pecasTotal.size(); i++){
            if((aux->getLinha()-1 == pecasTotal.at(i)->getLinha()) && (aux->getColuna()+1 == pecasTotal.at(i)->getColuna())){
                if(aux->getCor() == pecasTotal.at(i)->getCor()){
                    PecaAmiga = 'a';
                } else if(aux->getCor() != pecasTotal.at(i)->getCor()){
                    for(unsigned int i = 0; i < pecasTotal.size(); i++){
                        if((aux->getLinha()-2 == pecasTotal.at(i)->getLinha()) && (aux->getColuna()+2 == pecasTotal.at(i)->getColuna())){
                            podeComer = false;
                            throw 1;
                        }else{
                            podeComer = true;
                        }
                    }
                    PecaAmiga = 'i';
                    I = i;
                }
            }
        }
        if(PecaAmiga == 'n'){
            if(pecasTotal.at(K)->getColuna()!=8 && pecasTotal.at(K)->getLinha()!=1){
                pecasTotal.at(K)->move(pecasTotal.at(K)->pos().x()+80, pecasTotal.at(K)->pos().y()-80);
                pecasTotal.at(K)->setColuna(pecasTotal.at(K)->getColuna()+1);
                pecasTotal.at(K)->setLinha(pecasTotal.at(K)->getLinha()-1);
                Janela:: vezAtual++;
            }
        }else if(PecaAmiga == 'a'){
            throw 1;
        }else if(PecaAmiga == 'i' && podeComer == true){
                if(pecasTotal.at(K)->getColuna()!=7 && pecasTotal.at(K)->getLinha()!=2){
                    pecasTotal.at(K)->move(pecasTotal.at(K)->pos().x()+160, pecasTotal.at(K)->pos().y()-160);
                    pecasTotal.at(K)->setColuna(pecasTotal.at(K)->getColuna()+2);
                    pecasTotal.at(K)->setLinha(pecasTotal.at(K)->getLinha()-2);
                    delete (pecasTotal[I]);
                    pecasTotal.erase(pecasTotal.begin()+I);
                    Janela:: vezAtual++;
                }
        }
        if (pecasTotal.at(K)->getLinha()==1){
            pecasDama *p =new pecasDama(this, false);
            p->setGeometry(((pecasTotal.at(K)->getColuna()-1)*80)+20,(pecasTotal.at(K)->getLinha()-1)*80,80,80);
            p->update();
            p->show();

        }
    }
}

