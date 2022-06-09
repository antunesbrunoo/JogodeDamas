#ifndef PECAS_H
#define PECAS_H
#include <QLabel>
#include "pecasgeral.h"

class Pecas : public QLabel
{
    Q_OBJECT
    int Linha = 0;
    int Coluna = 0;
    bool cor;
public:
    Pecas(QWidget *parent, int x, int y);
    Pecas(QWidget *parent, int x, int y, bool Cor);
    ~Pecas();
    bool getCor();
    void setColuna(int n);
    void setLinha(int n);
    int getColuna();
    int getLinha();

    void paintEvent(QPaintEvent* e);

    void mousePressEvent(QMouseEvent* event);


signals:
    mover(bool lado);

};

#endif // PECAS_H
