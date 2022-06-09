#ifndef PECASGERAL_H
#define PECASGERAL_H

#include <QLabel>

class pecasGeral : public QLabel
{
    Q_OBJECT
public:

    virtual bool getCor()=0;
    virtual int getColuna()=0;
    virtual int getLinha()=0;

signals:

};

#endif // PECASGERAL_H
