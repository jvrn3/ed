#include "modules/String/mystr.h"
#include "modules/Circle/circle.h"
#include "modules/Rect/rect.h"
#include "modules/Svg/svg.h"
#include "modules/Geometry/geometry.h"
#include "modules/Cidade/cidade.h"
#include "modules/Sort/sort.h"
#include "palmeiras.h"

int
main(int argc, char *argv[]){
	int id, id2, i;

	char border[MAXSIZE];
	char inside[MAXSIZE];
	char suffix[MAXSIZE];
	char line[1000];
	char cep[MAXSIZE];
	char fill_q[MAXSIZE], strk_q[MAXSIZE];
	char fill_h[MAXSIZE], strk_h[MAXSIZE];
	char fill_t[MAXSIZE], strk_t[MAXSIZE];
	char fill_s[MAXSIZE], strk_s[MAXSIZE];
	char tmp_strk[MAXSIZE], tmp_fill[MAXSIZE];
	char id_equipamentos[MAXSIZE];
	Lista listC = createList();
	Lista listR = createList();
	Lista linha = createList();
	Lista linha2 = createList();
	Lista l;

	Cidade city = createCity();

	Circle c;
	Rect rect;
	Torre t;


	char *path, *dir, *leitura, *nomeTxt, *nomeSvg, *nomePath, *qry ;
	char *qry_name;

	double *array_torre_x;
	double r, x, y, w, h;
	int n;

	FILE *fWrite, *fRead, *fTxt, *fDraw, *fQry, *fSvgQry;



	leitura = path = dir = qry = NULL;
	printaPalmeiras1();

	i = 1;
	while(i < argc){
		if(strcmp("-e", argv[i]) == 0){
			i++;
			path = aloca_tamanho(path, strlen(argv[i]));
			strcpy(path,arruma_path(argv[i]));
			printf("PATH=%s\n", path);
		}
		if(strcmp("-f", argv[i]) == 0){
			i++;
			leitura = aloca_tamanho(leitura, strlen(argv[i]));
			strcpy(leitura, argv[i]);
		}
		if(strcmp("-o", argv[i]) == 0){
			i++;
			dir = aloca_tamanho(dir, strlen(argv[i]));
			strcpy(dir, argv[i]);
			dir = arruma_path(dir);

			printf("%s\n", dir);
		}
		if(strcmp("-q", argv[i]) == 0){
			i++;
			qry = aloca_tamanho(qry, strlen(argv[i]));
			strcpy(qry, argv[i]);

		
		}
		i++;
	}
	if(path==NULL){
		path = aloca_tamanho(path, 3);
		strcpy(path, "./");
	}
	if(leitura == NULL || dir == NULL){
		fprintf(stderr, "siguel usage: siguel [-e path -q file.qry] -f arq.geo -o dir");
		exit(-1);
	}
	

	leitura[strlen(leitura) -4] = 0;

	nomeTxt = criaString(dir, leitura, ".txt");
	nomeSvg = criaString(dir, leitura, ".svg");

	nomePath = criaString(path, leitura, ".geo");
	printf("NOME LEITURA=%s\n", nomePath);

	fRead = fopen(nomePath, "r");
	printf("NOME ESCRITA=%s\n", nomeTxt);

	fTxt  = fopen(nomeTxt, "w");
	if(fTxt == NULL){
		fprintf(stderr, "cant open file ");
		exit(-1);
	}

	fDraw = fopen(nomeSvg, "w");
	if(fDraw == NULL){
		fprintf(stderr, "cant open file");
		exit(-1);
	}
	fprintf(fDraw,"<svg>\n");

	if(fRead == NULL){
		fprintf(stderr, "Can't find file to read\nCheck if it exists\n");
		exit(-1);
	}
	//read .geo file
	while(!feof(fRead)){
		fgets(line, 1000, fRead);

		switch(line[0]){
			case 'c':
				if(line[1] == 'q')
					sscanf(line, "cq %s %s", strk_q, fill_q);
				else if(line[1] == 'h')
					sscanf(line, "ch %s %s", strk_h, fill_h);
				else if(line[1] == 't')
					sscanf(line, "ct %s %s", strk_t, fill_t);

				else if(line[1] == 's')
					sscanf(line, "cs %s %s", strk_s, fill_s);
				else{
					sscanf(line, "c %d %s %s %lf %lf %lf", &id, border, inside, &r, &x, &y);
					c = createCircle(border, inside, r, x, y);
					listC = insert(listC, c, id);

				}

				break;
				
			case 'r':
				sscanf(line, "r %d %s %s %lf %lf %lf %lf", &id, border, inside, &w, &h, &x, &y);
				rect = createRect(border, inside, w, h, x, y);

				listR = insert(listR, rect, id);
				

				break;

			case 'd':
				sscanf(line, "d %d %d", &id, &id2);
				fputs(line, fTxt);
				if ((linha = search_id(listC, id, 1)) != NULL){
					if((linha2 = search_id(listC, id2, 1)) != NULL)
						fprintf(fTxt, "%.2f\n",distanceCC(linha, linha2));
					else
						fprintf(fTxt, "%.2f\n",distanceCR(search_id(listC, id, 1), search_id(listR, id2,1)));
				}
				if ((linha = search_id(listR, id,1 )) != NULL){
					printf("a");
					if((linha2 = search_id(listC, id2, 1)) != NULL)
						fprintf(fTxt, "%.2f\n",distanceCR(linha2, linha));
					else
						fprintf(fTxt, "%.2f\n",distanceRR(linha, search_id(listR, id2, 1)));
				}
				break;

			case 'o':
				sscanf(line, "o %d %d", &id, &id2);
				fputs(line, fTxt);
				if ((linha = search_id(listC, id, 1)) != NULL){
					if((linha2 = search_id(listC, id2, 1)) != NULL){

						if(overlayCC(linha, linha2)){
							fprintf(fTxt, "SIM\n");
							drawOverlapCC(fDraw, linha, linha2);
						}
						else
							fprintf(fTxt, "NAO\n");
					}
					else{
						linha2 = search_id(listR, id2, 1);

						if(overlayCR(linha, linha2)){
							fprintf(fTxt, "SIM\n");
							drawOverlapCR(fDraw, linha, linha2);
						}
						else
							fprintf(fTxt, "NAO\n");
					}
				}
				//actually i have no idea what it is 28/06/2018
				else if((linha = search_id(listR, id, 1)) != NULL){
					if((linha2 = search_id(listC, id2, 1)) != NULL){
						if(overlayCR(linha2, linha)){
							fprintf(fTxt, "SIM\n");
							drawOverlapCR(fDraw, linha2, linha);
						}
						else
							fprintf(fTxt, "NAO\n");
					}
					else{
						linha2= search_id(listR, id2,1 );
						if(overlayRR(linha, linha2)){
							fprintf(fTxt, "SIM\n");
							drawOverlapRR(fDraw, linha, linha2);
						}
						else
							fprintf(fTxt, "NAO\n");
					}
				}
				break;
			case 'i':
				sscanf(line, "i %d %lf %lf ",&id, &x, &y);
				fprintf(fTxt, "i %d %.2f %.2f\n", id, x, y); 
				if ((linha = search_id(listC, id, 1))){
					if(isInsideC(linha, x, y))

						fprintf(fTxt, "SIM\n");
					else
						fprintf(fTxt, "NAO\n");
				}
				if ((linha = search_id(listR, id, 1))){
					if(isInsideR(linha, x, y))
						fprintf(fTxt, "SIM\n");
					else
						fprintf(fTxt, "NAO\n");
				}
				break;

				case 'h':
				sscanf(line, "h %s %lf %lf",id_equipamentos, &x, &y);
				Hidrante hid= createHidrante(fill_h, strk_h, id_equipamentos, x, y);
				city = insert_hidrante(city, hid);
				drawHidrante(fDraw, hid);

				break;

				//ler quadra
				case 'q':
				sscanf(line, "q %s %lf %lf %lf %lf", cep,&x, &y, &w,&h);
				Quadra q = createQuadra(fill_q, strk_q, cep, x, y, w, h);
				
				city = insert_quadra(city, q);
				
				drawQuadra(fDraw, q);


				break;

				case 's':
				sscanf(line, "s %s %lf %lf", id_equipamentos, &x, &y);
				Semaforo sem = createSemaforo(fill_s, strk_s, id_equipamentos, x, y);
				city = insert_semaforo(city, sem);

				drawSemaforo(fDraw, sem);


				break;
				case 't':
				sscanf(line, "t %s %lf %lf", id_equipamentos, &x, &y);
				t = createTorre(fill_t, strk_t, id_equipamentos, x, y);
				city = insert_torre(city, t);
				drawTorre(fDraw, t);

				break;

			case 'a':
				sscanf(line, "a %d %s", &id, suffix);
				leitura = criaString(leitura, "-", suffix);
				leitura = criaString(dir, leitura, ".svg");
				printf("end: %s", path);
				fWrite = fopen(criaString(dir, criaString(leitura, "-", suffix), ".svg"), "w");

				if(fWrite == NULL)
					fprintf(stderr, "cant open file");
				fprintf(fWrite, "<svg>\n");


				display(listC, fWrite, drawCircle);

				display(listR, fWrite, drawRect);

				if((linha = search_id(listC, id, 0)) != NULL){

					manipulate(linha, listC, fWrite, drawLineCToC);
					manipulate(linha, listR, fWrite, drawLineCToR);
				}
				else if((linha = search_id(listR, id, 0)) != NULL){
					manipulate(linha, listC, fWrite, drawLineRToC);
					manipulate(linha, listR, fWrite, drawLineRToR);

				}
				fprintf(fWrite, "</svg>");

				fclose(fWrite);
				break;
			default:
				break;
		}

	}
	//parsing and handling .qry files
	if(qry != NULL){
		qry[strlen(qry) -4] = 0;

		fQry = fopen(criaString(path, qry, ".qry"), "r");
		if(!fQry){
			fprintf(stdout, "Cant open file");
			exit(-1);
		}
	
		while(!feof(fQry)){
			fgets(line, 1000, fQry);

			//dq command ~ done?
			if(strncmp(line, "dq", 2) == 0){


				sscanf(line, "dq %lf %lf %lf %lf", &x, &y, &w, &h);

				rect = createRect("", "", w, h, x, y);

				l = city.lista_quadra;
				n = length(l) -1;
				for(int i =0 ; i < n; i++){
					StQuadra * sq =   (StQuadra *)get(l, 0);
					Rect rr = createRect("", "", sq->larg, sq->alt, sq->x, sq->y);
					if(isRectInsideRect(rr, rect)){
						fprintf(fTxt, "CEP REMOVIDO: %s\n", sq->cep);

						city.lista_quadra = del(city.lista_quadra, sq);
					}
					l = pop(l);
					free(rr);
					rr = NULL;
				}
			}
			//done?
			else if(strncmp(line, "q?", 2) == 0){
				sscanf(line, "q? %lf %lf %lf %lf", &x, &y, &w, &h);
				rect = createRect("", "", w, h, x, y);
				l = city.lista_quadra;
				n = length(l) - 1;
				for(int i = 0; i < n; i++){
					StQuadra *sq = (StQuadra *)get(l, 0);
					Rect rr =createRect(sq->strk, sq->fill, sq->larg, sq->alt, sq->x, sq->y);
					if(isRectInsideRect(rr, rect)){
						fprintf(fTxt, "Quadra Cep=%s Fill=%s Stroke=%s X=%lf Y=%lf W=%lf H=%lf\n",
								sq->cep,
								sq->fill,
								sq->strk, 
								sq->x,
								sq->y,
								sq->larg,
								sq->alt);
					}
					l = pop(l);
					free(rr);
					rr = NULL;
				}

				l = city.lista_semaforo;
				n = length(l) -1;
				for(int i = 0; i < n;  i++){
						StSemaforo *ss = (StSemaforo *) get(l, 0);
						Rect rr = createRect(ss->strk, ss->fill, 5, 15, ss->x, ss->y);
					if(isRectInsideRect(rr, rect)){
						fprintf(fTxt, "Semaforo ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n",
								ss->id,
								ss->fill,
								ss->strk, 
								ss->x,
								ss->y);
					}
					l = pop(l);
					free(rr);
					rr = NULL;
				}
				l = city.lista_hidrante;
				n = length(l) -1;
				for(int i = 0; i <  n ; i++){
					StHidrante *sh = (StHidrante *) get(l, 0);
					c = createCircle(sh->strk, sh->fill, 10,sh->x, sh->y );
					if(isCircleInsideRect(c, rect)){
						fprintf(fTxt, "Hidrante ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", 
								sh->id,
								sh->fill,
								sh->strk,
								sh->x,
								sh->y
								);
					}
					l = pop(l);
					free(c);
					c = NULL;
				}
				l = city.lista_torre;
				n = length(l) -1;
				for(int i = 0; i < n; i++){
					StTorre *st = (StTorre *) get(l, 0);
					c = createCircle(st->strk, st->fill, 10, st->x, st->y);
					if(isCircleInsideRect(c, rect)){
						fprintf(fTxt, "Torre ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", 
								st->id,
								st->fill,
								st->strk,
								st->x,
								st->y
								);
					}
					l = pop(l);
					free(c);
					c = NULL;
				}
						//precisa fazer o retangulo pontilhado
			}
			//done?
			else if(strncmp(line, "Q?", 2) == 0){
				sscanf(line, "Q? %lf %lf %lf", &r, &x, &y);
				c = createCircle("", "", r, x, y);

				for(int i = 0; i < length(city.lista_quadra) -1; i++){
					StQuadra *sq = (StQuadra *)get(city.lista_quadra, i);
					if(isRectInsideCircle(c, createRect(sq->strk, sq->fill, sq->larg, sq->alt, sq->x, sq->y))){
						fprintf(fTxt, "Quadra Cep=%s Fill=%s Stroke=%s X=%lf Y=%lf W=%lf H=%lf\n",
								sq->cep,
								sq->fill,
								sq->strk, 
								sq->x,
								sq->y,
								sq->larg,
								sq->alt);
					}
				}
				for(int i = 0; i < length(city.lista_semaforo) - 1; i++){
						StSemaforo *ss = (StSemaforo *) get(city.lista_semaforo, i);
						rect =  createRect(ss->strk, ss->fill, 5, 15, ss->x, ss->y);
					if(isRectInsideCircle(c, rect)){
						fprintf(fTxt, "Semaforo ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n",
								ss->id,
								ss->fill,
								ss->strk, 
								ss->x,
								ss->y);
					}
					free(rect);
				}
				for(int i = 0; i < length(city.lista_hidrante) - 1; i++){
					StHidrante *sh = (StHidrante *) get(city.lista_hidrante, i);
					if(isCircleInsideCircle(createCircle(sh->strk, sh->fill, 10,sh->x, sh->y), c)){
						fprintf(fTxt, "Hidrante ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", 
								sh->id,
								sh->fill,
								sh->strk,
								sh->x,
								sh->y
								);
					}
				}
				
				for(int i = 0; i < length(city.lista_torre) - 1; i++){
					StTorre *st = (StTorre *) get(city.lista_torre, i);
					if(isCircleInsideCircle(createCircle(st->strk, st->fill, 10, st->x, st->y), c)){
						fprintf(fTxt, "Torre ID=%s Fill=%s Stroke=%s X=%lf Y=%lf\n", 
								st->id,
								st->fill,
								st->strk,
								st->x,
								st->y
								);
					}
				}
			}
			//Dq  undone
			else if(strncmp(line, "Dq", 2) == 0){

				sscanf(line, "Dq %lf %lf %lf", &r, &x, &y);

				c = createCircle("", "", r, x, y);
				// go through the entire list and remove the ones that overlap
				//
				 l = city.lista_quadra;
				 n = length(l)-1;
				 for(int i = 0; i < n; i++){

					StQuadra *sq = (StQuadra *) get(l, 0);
					rect = createRect(sq->strk, sq->fill, sq->larg, sq->alt, sq->x, sq->y);

					if(isRectInsideCircle(c, rect)){
						fprintf(fTxt, "Dq %s\n", sq->cep);
						city.lista_quadra = del(city.lista_quadra, sq);
					}
						l = pop(l);
						free(rect);
						rect = NULL;
					}

				}
				else if(strncmp(line, "dle", 3)==0){
					sscanf(line, "dle %*[srh] %lf %lf %lf %lf ",&x, &y, &w, &h);

					rect = createRect("", "", w, h, x, y);
					drawRect(fDraw, rect);
					if(line[4] == 'r' || line[5] == 'r' || line[6] == 'r'){

						l = city.lista_torre;
						n = length(l) -1;
						for(int i = 0; i < n; i++){
							StTorre *st = (StTorre *) get(l, 0);
							c = createCircle(st->strk, st->fill, 10, st->x, st->y);
							if(isCircleInsideRect(c, rect)){
								fprintf(fTxt, "dle t %s\n", st->id);
								city.lista_torre = del(city.lista_torre, st);
							}
							l = pop(l);
							free(c);
							c = NULL;
						}
					}

					if(line[4] == 'h' || line[5] == 'h' || line[6] == 'h'){
						//remove h
						l = city.lista_hidrante;
						n = length(l) -1;

						 for(int i = 0; i < n; i++){
							StHidrante *sh = (StHidrante *) get(l, 0);
							c = createCircle(sh->strk, sh->fill, 10, sh->x, sh->y);

							if(isCircleInsideRect(c, rect)){
								fprintf(fTxt, "dle h %s\n", sh->id);
								city.lista_hidrante = del(city.lista_hidrante, sh);
							}
							l = pop(l);
							free(c);
							c = NULL;

						}
					}
					if(line[4] == 's' || line[5] == 's' || line[6] == 's'){
						//remove r
						l = city.lista_semaforo;
						n = length(l) -1;
						 for(int i = 0; i < n; i++){
							StSemaforo *ss = (StSemaforo *) get(l, 0);
							//memory leak
							Rect rect_aux = createRect(ss->strk, ss->fill, 5, 15, ss->x, ss->y);
							if(isRectInsideRect(rect_aux, rect)){
								fprintf(fTxt, "dle s %s\n", ss->id);
								city.lista_semaforo = del(city.lista_semaforo, ss);
							}
							l = pop(l);
							free(rect_aux);
							rect_aux = NULL;
						}
					}
				}
				else if(strncmp(line, "Dle", 3) == 0){
					sscanf(line, "Dle %*[rsh] %lf %lf %lf", &x, &y, &r );
					c = createCircle("", "", r, x, y);


					if(line[4] == 'h' || line[5] == 'h' || line[6] == 'h'){
						l = city.lista_hidrante;
						n = length(l) -1;
						for(int i = 0; i < n; i++){
							StHidrante *sh =(StHidrante *) get(l, 0);
							Circle circ = createCircle(sh->strk, sh->fill, 10, sh->x, sh->y);
							if(isCircleInsideCircle(circ, c)){
								fprintf(fTxt, "Dle %s\n", sh->id);
								city.lista_hidrante = del(city.lista_hidrante, sh);
							}
							l = pop(l);
							free(circ);
							circ = NULL;
						}
					}
					if(line[4] == 'r' || line[5] == 'r' || line[6] == 'r'){
						l = city.lista_torre;
						n = length(l) -1 ;
						for(int i = 0; i < n; i++){
							StTorre *st = (StTorre *) get(l, 0);
							Circle circ = createCircle(st->strk, st->fill, 10, st->x, st->y);
							if(isCircleInsideCircle(circ, c)){
								fprintf(fTxt, "Dle r %s\n", st->id);
								city.lista_torre = del(city.lista_torre, st);
							}
							l = pop(l);
							free(circ);
							circ=  NULL;
						}
					}
					if(line[4] == 's' || line[5] == 's' || line[6] == 's'){
						l = city.lista_semaforo;
						n = length(l) -1;
						for(int i = 0; i < n; i++){
							StSemaforo *ss = (StSemaforo *) get(l, 0);
							//memory leak
							rect = createRect(ss->strk, ss->fill, 5, 15, ss->x, ss->y);
							if(isRectInsideCircle(c, rect)){
								fprintf(fTxt, "Dle s %s\n", ss->id);
								city.lista_semaforo = del(city.lista_semaforo, ss);
							}
							l = pop(l);
							free(rect);
							rect = NULL;
					}
				}
			}
			else if(strncmp(line, "cc", 2) == 0){
				//that's really a bad code, need to change how to access in the future

				sscanf(line, "cc %s %s %s", cep, tmp_strk, tmp_fill);
				StQuadra *sq;
				StTorre *st;
				StHidrante *sh;
				StSemaforo *ss;
				
				if((sq = (StQuadra *) search_cep(cep, city) )!= NULL){
					strcpy(sq->fill, tmp_fill);
					strcpy(sq->strk, tmp_strk);
				}

				else if((ss = (StSemaforo *) search_id_sem(cep, city)) != NULL){
					strcpy(ss->fill, tmp_fill);
					strcpy(ss->strk, tmp_strk);
				}
				else if((st = (StTorre *) search_id_to(cep, city) )!= NULL){
					strcpy(st->fill, tmp_fill);
					strcpy(st->strk, tmp_strk);

				}
				else if((sh = (StHidrante *) search_id_hi(cep, city)) != NULL){
					strcpy(sh->fill, tmp_fill);
					strcpy(sh->strk, tmp_strk);
				}
			}
			else if(strncmp(line, "crd?", 4) == 0){
				
				sscanf(line, "crd? %s", cep);
				StQuadra *sq;
				StTorre *st;
				StHidrante *sh;
				StSemaforo *ss;
			printf("buscando\n");
				if((sq = (StQuadra *) search_cep(cep, city) )!= NULL)
					fprintf(fTxt, "%lf %lf %lf %lf QUADRA\n", sq->x, sq->y, sq->larg, sq->alt);
				else if((ss = (StSemaforo *) search_id_sem(cep, city)) != NULL)
					fprintf(fTxt, "%lf %lf SEMAFORO\n", ss->x, ss->y);
				else if((st = (StTorre *) search_id_to(cep, city) )!= NULL)
					fprintf(fTxt, "%lf %lf TORRE\n", st->x, st->y);
				else if((sh = (StHidrante *) search_id_hi(cep, city)) != NULL)
					fprintf(fTxt, "%lf %lf HIDRANTE\n", sh->x, sh->y);
			}
			/* closest pair */
			else if(strncmp(line, "crb?", 4) == 0){
				n = length(city.lista_torre);
				l = city.lista_torre;
				/* array_torre_x = malloc(sizeof(double) * n); */

			}
		}
		if(has_slash(qry))
			qry_name = get_last_slash(qry);
		else
			qry_name = qry;

		qry_name = criaString(dir, criaString(leitura, "-", qry_name), ".svg");
		fSvgQry = fopen(qry_name, "w");
		if(!fSvgQry){
			fprintf(stderr, "bugou ao criar file");
			exit(-1);
		}
		/*
		 * create new svg file after manipulating [deleting etc] the old list
		 *
		 */
		fprintf(fSvgQry, "<svg>\n");

		//it's time to print

		l = city.lista_quadra;
		n = length(city.lista_quadra) -1;
		for(int i = 0; i < n; i++){
			StQuadra *sq = (StQuadra *) get(l, 0);
			drawQuadra(fSvgQry, sq);
			l= pop(l);
		}
		
		l = city.lista_hidrante;
		n = length(city.lista_hidrante) -1;
		for(int i =0; i < n; i++){
			StHidrante *sh = (StHidrante *) get(l, 0);
			drawHidrante(fSvgQry, sh);
			l = pop(l);
		}
		l = city.lista_semaforo;
		n = length(city.lista_semaforo) -1;
		for(int i =0; i < n; i++){
			StSemaforo *ss = (StSemaforo *) get(l, 0);
			drawSemaforo(fSvgQry, ss);
			l = pop(l);
		}
		l = city.lista_torre;
		n = length(city.lista_torre) -1;
		for(int i = 0; i < n; i++){
			StTorre *st = (StTorre *) get(l,0);
			/* Torre t = createTorre(st->fill, st->strk, st->id, st->x, st->y); */
			drawTorre(fSvgQry, st);
			l	= pop(l);
		}

		free(qry_name);
		fprintf(fSvgQry, "\n</svg>\n");
		fclose(fSvgQry);
	}
	//t2 stuff
	l = listR;
	n = length(listR) -1;
	for(int i =0; i < n; i++){
		StRect *sr = (StRect *) get(l, 0);
		drawRect(fDraw, sr);
		l = pop(l);
	}

	l = listC;
	n = length(listC) -1;
	for(int i =0; i < n; i++){
		StCircle *sc = (StCircle *) get(l, 0);
		drawCircle(fDraw, sc);
		l = pop(l);
	}
	fprintf(fDraw, "</svg>");

	//is there more allocated variables? 
	free(path);
	free(dir);
	free(leitura);
	free(nomeSvg);
	free(nomeTxt);
	free(nomePath);


	fclose(fRead);
	fclose(fTxt);
	fclose(fDraw);

	//destroying lists
	destroy(city.lista_semaforo);
	destroy(city.lista_quadra);
	destroy(city.lista_hidrante);
	destroy(city.lista_torre);
	destroy(listC);
	destroy(listR);
	/* destroy(linha2); */
	/* destroy(linha); */
	return 0;
}
