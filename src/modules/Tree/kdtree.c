#include "kdtree.h"

KdTree newKdTree(void *data, float point[]){
    KdTree kd = malloc(sizeof(KdNode));
    KdNode *n = (KdNode *) kd;
    n->data = data;
    n->left = NULL;
    n->right = NULL;
    copyPoint(n->point, point);
    return kd;
}
void copyPoint(float p[], float p2[]){
   for(int i = 0; i < 2;i++){
      p[i] = p2[i];
   }
}

KdTree kd_insert_aux(KdTree t, void *data, float point[2], int cd){
    KdNode *n = (KdNode *) t;

    if(n == NULL){
       return newKdTree(data, point);
    }

    if(point[cd] < n->point[cd]){
       n->left = kd_insert_aux(n->left, data, point, (cd + 1) % 2);
    }
    else{
       n->right = kd_insert_aux(n->right, data, point, (cd + 1) % 2);
    }
    return n;
}
KdTree kd_insert(KdTree kd, void *data, float point[2]){
   return kd_insert_aux(kd, data, point, 0);
}
/* float min(float a, float b){ */
/*     if(a < b) */
/* 	return a; */
/*     else */
/* 	return b; */
/*  */
/* } */


KdTree minData(void *a,  void *b, void *c, int dim){
   KdNode *kMin = (KdNode *) a;
   KdNode *kb = (KdNode *) b;
   KdNode *kc = (KdNode *) c;

   if(kb->point[dim] < kMin->point[dim]){
      kMin = kb;
   }
   if(kc->point[dim] < kMin->point[dim]){
      kMin = kc;
   }
   return kMin;
}

KdTree find_min_rec(KdTree kd, int d, int depth){
   KdNode *n = (KdNode *)  kd; 
   if(n == NULL)
      return NULL;
      
   int cd = d % 2;
   if(cd == d){
      if(n->left == NULL )
	 return n;
      else return find_min_rec(n->left, d, depth+1);
   }
   else{
      return minData(n,
	    find_min_rec(n->left, d, depth+1),
	    find_min_rec(n->right, d, depth+1), d);
   }
}
KdTree find_min(KdTree kd, int d){
   return find_min_rec(kd, d, 0);

}
int are_same(float pointA[], float pointB[]){
  for(int i = 0; i < 2; i++){
     if(pointA[i] != pointB[i])
	return 0;
  }
  return 1;
}

KdTree delete_kd_node(KdTree kd, void *data, float point[], int depth){
   if(kd == NULL){
      return NULL;
   }
   KdNode *n = (KdNode *) kd;
   int cd = depth % 2;
   if(are_same(n->point, point)){
      if(n->right != NULL){
	 KdNode *min = (KdNode *) find_min(n->right, cd);

	 n->data = min->data;
	 copyPoint(n->point, min->point);
	 n->right = (KdNode *) delete_kd_node(n->right, min->data, min->point, depth+1);
      }
      else if(n->left != NULL){
	 KdNode *min = (KdNode *) find_min(n->left, cd);
	 n->data = min->data;
	 copyPoint(n->point, min->point);
	 n->right = (KdNode *) delete_kd_node(n->left, min->data, min->point, depth+1);
	 n->left = NULL;
      }
      else{
	 n = NULL;
	 return NULL;
      }
      return n;
   }
   else{
      if(point[cd] < n->point[cd]){
	 n->left = (KdNode *) delete_kd_node(n->left, data, point, depth+1);
      }
      else{
	 n->right = (KdNode *) delete_kd_node(n->right, data, point, depth+1);
      }
   }
   return n;
}
void printInOrder(KdTree t, void (*displayFn)(void *)){
    KdNode *n = (KdNode *) t;
    if(n == NULL){
	printf("NULL\n");
	return;
    }

    if(n->left != NULL)
	printInOrder(n->left, displayFn);
    displayFn(n->data);
    if(n->right != NULL)
	printInOrder(n->right, displayFn);
}

void destroyTree(KdTree k){
   KdNode *kd = (KdNode *) k;
   free(kd->data);
   if(kd->left != NULL)
      destroyTree(kd->left);
   if(kd->right != NULL)
      destroyTree(kd->right);

   free(kd);

}
