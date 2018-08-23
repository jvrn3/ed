#include "cidade.h"
#include <string.h>

Cidade createCity(){
	Cidade city;

	city.lista_quadra = createList();
	city.lista_hidrante = createList();
	city.lista_semaforo = createList();
	city.lista_torre = createList();


	city.arvore_quadra = NULL;
	city.arvore_semaforo = NULL;
	city.arvore_hidrante = NULL;
	city.arvore_torre = NULL;

	return city;
}

KdTree insert_quadra(Cidade c, Quadra q, float point[2]){
	/* insert(c.lista_quadra, q, 0); */
	return kd_insert(c.arvore_quadra, q, point);
}
KdTree insert_hidrante(Cidade c, Hidrante h, float point[]){
	/* insert(c.lista_hidrante, h, 0); */
	return kd_insert(c.arvore_hidrante, h, point);
}
KdTree insert_torre(Cidade c, Torre t, float point[]){
	/* insert(c.lista_torre, t, 0); */
	return kd_insert(c.arvore_torre, t, point);
}
KdTree insert_semaforo(Cidade c, Semaforo s, float point[]){
	/* insert(c.lista_semaforo, s, 0); */
	return kd_insert(c.arvore_semaforo, s, point);
}
//could return the cep position and then use get function to access it
Quadra search_cep(char *cep, Cidade c){
	Node *n;
	StQuadra *sq;
	for(n = getFirst(c.lista_quadra); n != NULL; n = n->next){
		sq = (StQuadra *) n->data;
		if(strcmp(sq->cep, cep) == 0){
			return sq;
		}
	}
	return NULL;
	/* Lista ss = c.lista_quadra; */
	/* int n = length(ss)-1; */
	/* for(int i = 0; i < n; i++){ */
	/* 	StQuadra *sq = (StQuadra *) get(ss, 0); */
	/* 	if(strcmp(sq->cep, cep) == 0){ */
	/* 		return sq; */
	/* 	} */
  /*  */
	/* 	ss = pop(ss); */
	/* } */
	/* return NULL; */
}
Semaforo search_id_sem(char *id, Cidade c){
	Node *n; 
	StSemaforo *ss;
	for(n = getFirst(c.lista_semaforo); n != NULL; n = n->next){
		ss = (StSemaforo *) n->data;
		if(strcmp(ss->id, id) == 0){
			return ss;
		}
	}
	return NULL;
	/* Lista s = c.lista_semaforo; */
	/* int n = length(s) -1; */
	/* for(int i = 0; i < n; i++){ */
	/* 	StSemaforo *ss = (StSemaforo *) get(s, 0); */
	/* 	if(strcmp(ss->id, id) == 0){ */
	/* 		return ss; */
	/* } */
	/* 	s = pop(s); */
  /*  */
	/* } */
  /*  */
	/* return NULL; */
}
Torre search_id_toxy(float x, float y, Torre t){
	Node *n;
	StTorre *st;
	for(n = getFirst(t); n != NULL; n = n->next){
		st = (StTorre *) n->data;
		if((x - st->x) < 0.1 && (y - st->y) < 0.1){
			return st;
		}

	}
	return NULL;
}
Hidrante search_id_hi(char *id, Cidade c){
	Node *n;
	StHidrante *sh;
	for(n = getFirst(c.lista_hidrante); n != NULL; n = n->next){
		sh = (StHidrante *) n->data;
		if(strcmp(sh->id, id) == 0){
			return sh;
		}
	}
	return NULL;
	/* Lista s = c.lista_hidrante; */
	/* int n = length(s) -1; */
	/* for(int i = 0; i < n; i ++){ */
	/* 	StHidrante *sh = (StHidrante *) get(s, 0); */
	/* 	if(strcmp(sh->id, id) == 0) */
	/* 		return sh; */
	/* 	s = pop(s); */
	/* } */
	/* return NULL; */
}
Torre search_id_to(char *id, Cidade c){
	Node *n;
	StTorre *st;
	for(n = getFirst(c.lista_torre); n != NULL; n = n->next){
		st = (StTorre *) n->data;
		if(strcmp(st->id, id) == 0){
			return st;
		}
	}
	return NULL;
	/* Lista s = c.lista_torre; */
	/* int n = length(s) -1; */
	/* for(int i =0; i < n; i++){ */
	/* 	StTorre *st = (StTorre *) get(s, 0); */
	/* 	if(strcmp(st->id, id) == 0) */
	/* 		return st; */
	/* 	s = pop(s); */
	/* } */
	/* return NULL; */
}
KdTree remove_quadra(KdTree t, Quadra q, float point[]){
	return delete_kd_node(t, q, point, 0);
}
KdTree remove_hidrante(KdTree t, Hidrante h, float point[]){
	return delete_kd_node(t, h, point, 0);
}
KdTree remove_semaforo(KdTree t, Semaforo s, float point[]){
	return delete_kd_node(t, s, point, 0);
}
KdTree remove_torre(KdTree t, Torre to, float point[]){
	return delete_kd_node(t, to, point, 0);
}
KdTree deleteQuadraInRect(Rect r, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StQuadra *sq;
	Rect r2;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteQuadraInRect(r, kd->left, fTxt);
	kd->right = deleteQuadraInRect(r, kd->right, fTxt);
	sq = (StQuadra *) kd->data;
	r2 = createRect("", "", sq->larg, sq->alt, sq->x, sq->y); 
	if(isRectInsideRect(r2, r)){
		fprintf(fTxt, "CEP REMOVIDO %s\n", sq->cep);
		kd = remove_quadra(kd, kd->data, kd->point);
	}
	free(r2);
	r2 = NULL;
	
	/* float point[] = {sq->x, sq->y}; */
	return kd;
	
	/* 		fprintf(fTxt, "Quadra Cep=%s Fill=%s Stroke=%s X=%lf Y=%lf W=%lf H=%lf\n", */
	/* 				sq->cep, */
	/* 				sq->fill, */
	/* 				sq->strk,  */
	/* 				sq->x, */
	/* 				sq->y, */
	/* 				sq->larg, */
	/* 				sq->alt); */
	/* 	} */
    /*  */
	/* } */
}
KdTree deleteQuadraInCircle(Circle c, KdTree k, FILE *fTxt ){
	if(k == NULL)
		return NULL;
	/* Node *n; */ 
	StQuadra *sq;
	Rect r;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteQuadraInCircle(c, kd->right, fTxt);
	kd->right = deleteQuadraInCircle(c, kd->left, fTxt);
	sq = (StQuadra *) kd->data;
	r = createRect("", "", sq->larg, sq->alt, sq->x, sq->y); 
	if(isRectInsideCircle(c, r)){
		fprintf(fTxt, "CEP REMOVIDO %s\n", sq->cep);

		kd = remove_quadra(kd, kd->data, kd->point);
	}
	free(r);
	r = NULL;
	return kd;

	/* 				fprintf(fTxt, "Quadra Cep=%s Fill=%s Stroke=%s X=%lf Y=%lf W=%lf H=%lf\n", */
	/* 						sq->cep, */
	/* 						sq->fill, */
	/* 						sq->strk,  */
	/* 						sq->x, */
	/* 						sq->y, */
	/* 						sq->larg, */
	/* 						sq->alt); */

}
KdTree deleteSemaforoInRect(Rect r, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StSemaforo *ss;
	Rect r2;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteSemaforoInRect(r, kd->left, fTxt);
	kd->right= deleteSemaforoInRect(r, kd->right, fTxt);
	ss = (StSemaforo *) kd->data;
	r2 = createRect(ss->strk, ss->fill, 5, 15, ss->x, ss->y);
	if(isRectInsideRect(r2, r)){
		fprintf(fTxt, "dle s %s\n", ss->id);
		kd = remove_semaforo(kd, kd->data, kd->point);
	}
	free(r2);
	r2 = NULL;
	return kd;
}
	/* 	else{ */
	/* 		fprintf(fTxt, "Semaforo ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", */
	/* 				ss->id, */
	/* 				ss->fill, */
	/* 				ss->strk,  */
	/* 				ss->x, */
	/* 				ss->y); */
	/* 	} */
	/* } */

/* 	fprintf(fTxt, "Semaforo ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", */
		/* 			ss->id, */
		/* 			ss->fill, */
		/* 			ss->strk,  */
		/* 			ss->x, */
		/* 			ss->y); */
		/* } */
KdTree deleteSemaforoInCircle(Circle c, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StSemaforo *ss;
	Rect r;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteSemaforoInCircle(c, kd->left, fTxt);
	kd->right = deleteSemaforoInCircle(c, kd->right, fTxt);
	ss = (StSemaforo *) kd->data;
	r = createRect(ss->strk, ss->fill, 5, 15, ss->x, ss->y);
	if(isRectInsideCircle(c,r)){
		kd = remove_semaforo(kd, kd->data, kd->point);
		fprintf(fTxt, "Dle s %s\n", ss->id);
		
	}
	free(r);
	r = NULL;
	return kd;
}

/* fprintf(fTxt, "Hidrante ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n",  */
/* 		sh->id, */
/* 		sh->fill, */
/* 		sh->strk, */
/* 		sh->x, */
/* 		sh->y */
/* 	   ); */
KdTree deleteHidranteInRect(Rect r, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StHidrante *sh;
	Circle c;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteHidranteInRect(r, kd->left, fTxt);
	kd->right = deleteHidranteInRect(r, kd->right, fTxt);
	sh = (StHidrante *) kd->data;
	c = createCircle(sh->strk, sh->fill, 10,sh->x, sh->y );
	if(isCircleInsideRect(c, r)){
		fprintf(fTxt, "dle h %s\n", sh->id);
		kd = remove_hidrante(kd, kd->data, kd->point);
	}
	free(c);
	c = NULL;
	return kd;
}
		/* fprintf(fTxt, "Hidrante ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n",  */
						/* 		sh->id, */
						/* 		sh->fill, */
						/* 		sh->strk, */
						/* 		sh->x, */
						/* 		sh->y */
						/* 		); */

KdTree deleteHidranteInCircle(Circle c, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StHidrante *sh;
	Circle c2;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteHidranteInCircle(c, kd->left, fTxt);
	kd->right = deleteHidranteInCircle(c, kd->right, fTxt);
	sh = (StHidrante *) kd->data;
	c2 = createCircle(sh->strk, sh->fill, 10,sh->x, sh->y );
	if(isCircleInsideCircle(c2, c)){
		fprintf(fTxt, "Dle h %s\n", sh->id);
		kd =remove_hidrante(kd, kd->data, kd->point);
	}
	free(c2);
	c2 = NULL;
	return kd;
}
/* fprintf(fTxt, "Torre ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n",  */
/* 								st->id, */
/* 								st->fill, */
/* 								st->strk, */
/* 								st->x, */
/* 								st->y */
/* 								); */

KdTree deleteTorreInRect(Rect r, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StTorre *st;
	Circle c;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteTorreInRect(r, kd->left, fTxt);
	kd->right = deleteTorreInRect(r, kd->right, fTxt);
	st = (StTorre *) kd->data;
	c = createCircle(st->strk, st->fill, 10, st->x, st->y);
	if(isCircleInsideRect(c, r)){
		fprintf(fTxt, "dle t %s\n", st->id);
		kd = remove_torre(kd, kd->data, kd->point);
	}
	free(c);
	c = NULL;
	return kd;
}

/* fprintf(fTxt, "Torre ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n",  */
/* 		st->id, */
/* 		st->fill, */
/* 		st->strk, */
/* 		st->x, */
/* 		st->y */
/* 	   ); */
KdTree deleteTorreInCircle(Circle c, KdTree k, FILE *fTxt){
	if(k == NULL)
		return NULL;
	StTorre *st;
	Circle c2;
	KdNode *kd = (KdNode *) k;
	kd->left = deleteTorreInCircle(c, kd->left, fTxt);
	kd->right = deleteTorreInCircle(c, kd->right, fTxt);
	st = (StTorre *) kd->data;
	c2 = createCircle(st->strk, st->fill, 10, st->x, st->y);
	if(isCircleInsideCircle(c2, c)){
		fprintf(fTxt, "Dle t %s\n", st->id);
		kd = remove_torre(kd, kd->data, kd->point);
	}

	free(c2);
	c2 = NULL;
	return kd;
}
void free_cidade(Cidade c){
	destroy(c.lista_hidrante);
	destroy(c.lista_quadra);
	destroy(c.lista_semaforo);
	destroy(c.lista_torre);
	destroyTree(c.arvore_quadra);
	destroyTree(c.arvore_hidrante);
	destroyTree(c.arvore_torre);
	destroyTree(c.arvore_semaforo);
	
}

void traverseTreeQuadra(KdTree kd, void (*func)(FILE *, void *), FILE *f){
	if(kd == NULL)
		return;

	KdNode *knode = (KdNode *)kd;
	StQuadra *sq = (StQuadra *) knode->data;
	func(f, sq);
	if(knode->left != NULL)
		traverseTreeQuadra(knode->left, func, f);
	if(knode->right != NULL )
		traverseTreeQuadra(knode->right, func, f);

}
void traverseTreeSemaforo(KdTree kd, void (*func)(FILE *, void *), FILE *f){
	KdNode *knode = (KdNode *)kd;
	if(knode != NULL){
		StSemaforo *sq = (StSemaforo *) knode->data;
		if(sq != NULL)
			func(f, sq);

		if(knode->left != NULL)
			traverseTreeSemaforo(knode->left, func, f);
		if(knode->right != NULL )
			traverseTreeSemaforo(knode->right, func, f);
	}

}
void traverseTreeTorre(KdTree kd, void (*func)(FILE *, void *), FILE *f){
	KdNode *knode = (KdNode *)kd;
	if(knode != NULL){
		StTorre *sq = (StTorre *) knode->data;
		if(sq != NULL)
			func(f, sq);

		if(knode->left != NULL)
			traverseTreeTorre(knode->left, func, f);
		if(knode->right != NULL )
			traverseTreeTorre(knode->right, func, f);
	}

}
void traverseTreeHidrante(KdTree kd, void (*func)(FILE *, void *), FILE *f){
	KdNode *knode = (KdNode *)kd;
	if(knode != NULL){
		StHidrante *sq = (StHidrante *) knode->data;
		if(sq != NULL)
			func(f, sq);

		if(knode->left != NULL)
			traverseTreeHidrante(knode->left, func, f);
		if(knode->right != NULL )
			traverseTreeHidrante(knode->right, func, f);
	}

}
