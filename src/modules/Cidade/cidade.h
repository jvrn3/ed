#ifndef CIDADE_H

#define CIDADE_H
#include "../Quadra/quadra.h"
#include "../Hidrante/hidrante.h"
#include "../Semaforo/semaforo.h"
#include "../Torre/torre.h"
#include "../Lista/linked_list.h"
#include "../Rect/rect.h"
#include "../Circle/circle.h"
#include "../Geometry/geometry.h"
#include "../Tree/kdtree.h"
#include "../Comercio/comercio.h"
#include "../Hash/hash_table.h"
#include "../Pessoa/pessoa.h"
#include "../Morador/morador.h"

/* Representação de Siguel, cidade com diversos equipamentos, pessoas etc 
 * Este arquivo contém funções que manipulam a cidade
 *
 * */



typedef struct cidade{
  Lista lista_quadra;
  Lista lista_semaforo;
  Lista lista_hidrante;
  Lista lista_torre;

  KdTree arvore_quadra;
  KdTree arvore_semaforo;
  KdTree arvore_hidrante;
  KdTree arvore_torre;

  Hash comercio;
  Hash pessoas;
  Hash moradores;
  Hash tipo_comercio;
  Hash cep_quadra;

  Lista mor;
  Lista est;


}Cidade;

Cidade createCity();
Address changeAddress(Address a, char *cep, char face, int num, char *comp);
Ponto city_get_ponto(Cidade c, Address a);
Pessoa searchPessoa(Hash h, char *key);
Comercio searchComercioTipo(Hash h, char *key);
Morador searchMorador(Hash h, char *key);
Comercio searchComercio(Hash h, char *key);
Quadra searchQuadra(Hash h, char *key);
int _compareCepMorador(void *hd, void *k);
int _compareCepEstblcmto(void *h, void *k);
int _compareCodtEstblc(void *h, void *k);
void _hashSearchEstblcInRect(Cidade c, Rect r, FILE *fTxt);
void _hashSearchQuadraInRect(Cidade c, Rect r, FILE *fp);
void _hashSearchTipoInRect(Cidade c, Rect r, char *key, FILE *fTxt);
KdTree insert_quadra(Cidade c, Quadra q, float point[2]);
KdTree insert_hidrante(Cidade c, Hidrante h, float point[]);
KdTree insert_semaforo(Cidade c, Semaforo s, float point[]);
KdTree insert_torre(Cidade c, Torre t, float point[]);
KdTree remove_quadra(KdTree t,  Quadra q, float point[]);
Hidrante remove_hidrante(KdTree t, Hidrante h, float point[]);
Torre remove_torre(KdTree t, Torre to, float point[]);
Semaforo remove_semaforo(KdTree t, Semaforo s, float point[]);
Quadra search_cep(char *cep, KdTree kd);
Semaforo search_id_sem(char *id, KdTree kd);
Hidrante search_id_hi(char *id, KdTree kd);
Torre search_id_to(char *id, KdTree kd);
Torre search_id_toxy(float x, float y, Torre c);
KdTree  deleteQuadraInRect(Rect r,KdTree k, FILE *fp);
KdTree deleteSemaforoInRect(Rect r, KdTree k, FILE *fTxt);
KdTree deleteHidranteInRect(Rect r, KdTree k, FILE *fTxt);
KdTree deleteTorreInRect(Rect r, KdTree k, FILE *fTx);
KdTree deleteQuadraInCircle(Circle c, KdTree k, FILE *fTxt) ;
KdTree deleteSemaforoInCircle(Circle c, KdTree k, FILE *fTxt);
void searchQuadraInRect(Rect r, KdTree k, FILE *fTxt);
void searchQuadraInCircle(Circle c, KdTree k, FILE *fTxt);
void searchHidranteInRect(Rect r, KdTree k, FILE *fTxt);
void searchHidranteInCircle(Circle c, KdTree k, FILE *fTxt);
void searchSemaforoInRect(Rect r, KdTree k, FILE *fTxt);
void searchSemaforoInCircle(Circle c, KdTree k, FILE *fTxt);
void searchTorreInRect(Rect r, KdTree k, FILE *fTxt);
void searchTorreInCircle(Circle c, KdTree k, FILE *fTxt);
KdTree deleteHidranteInCircle(Circle c, KdTree k, FILE *fTxt);
KdTree deleteTorreInCircle(Circle c, KdTree k, FILE *fTxt);
void free_cidade(Cidade c);
void traverseTreeQuadra(KdTree kd, void (*func)(FILE *, void *), FILE *f);
void traverseTreeHidrante(KdTree kd, void (*func)(FILE *, void *), FILE *f);
void traverseTreeTorre(KdTree kd, void (*func)(FILE *, void *), FILE *f);
void traverseTreeSemaforo(KdTree kd, void (*func)(FILE *, void *), FILE *f);

float nn_aux(float a[], KdTree k, float *best);
float nn(KdTree k, float a[]);
float closest_aux(KdTree k, float *minor);
float closest_kd(KdTree k);
int pointt(KdTree k, float dist, FILE *fSvg, FILE *fTxt);
void point_aux(FILE *fSvg, FILE *fTxt, StTorre *a, StTorre *b, float dist);
#endif

