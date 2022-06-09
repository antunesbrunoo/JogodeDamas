#ifndef JANELA_H
#define JANELA_H
#include <QPushButton>
#include <QMainWindow>
#include <vector>
#include "pecas.h"

class Janela : public QMainWindow
{
    Q_OBJECT
    QPushButton *salvar, *carregar;
    std::vector <Pecas*> pecasTotal;
    static Janela* instancia;
    static int vezAtual;
    explicit Janela(QWidget *parent = nullptr);

public:
    static Janela* getInstancia();
    virtual void paintEvent(QPaintEvent *Tabuleiro);

public slots:
    void salvarArquivo();
    void abrirArquivo();
    void moverPeca(bool direcao);

signals:
};

#endif // JANELA_H
