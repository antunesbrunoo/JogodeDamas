#ifndef PECASDAMA_H
#define PECASDAMA_H

#include <QObject>
#include <QLabel>
#include "pecasgeral.h"

class pecasDama : public QLabel
{
    Q_OBJECT
    int Linha;
    int Coluna;
    bool cor;
public:
    pecasDama(QWidget *parent, bool Cor);
    bool getCor();
    int getColuna();
    int getLinha();

    void paintEvent(QPaintEvent* e);
signals:

};

#endif // PECASDAMA_H
