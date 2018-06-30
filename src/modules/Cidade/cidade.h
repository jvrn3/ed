#ifndef CIDADE_H
#define CIDADE_H
#include "../Quadra/quadra.h"
#include "../Hidrante/hidrante.h"
#include "../Semaforo/semaforo.h"
#include "../Torre/torre.h"
#include "../Lista/static_ist.h"

typedef struct cidade{
  Lista lista_quadra;
  Lista lista_semaforo;
  Lista lista_hidrante;
  Lista lista_torre;

}Cidade;

Cidade createCity();
Cidade insert_quadra(Cidade c, Quadra q);
Cidade insert_hidrante(Cidade c, Hidrante h);
Cidade insert_semaforo(Cidade c, Semaforo s);
Cidade insert_torre(Cidade c, Torre t);
void remove_quadra(Cidade c, Quadra q);
Hidrante remove_hidrante(Cidade c, Hidrante h);
Torre remove_torre(Cidade c, Torre t);
Semaforo remove_semaforo(Cidade c, Semaforo s);
Quadra search_cep(char *cep, Cidade c);
Semaforo search_id_sem(char *id, Cidade c);
Hidrante search_id_hi(char *id, Cidade c);
Torre search_id_to(char *id, Cidade c);
#endif

