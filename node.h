/*
	Program: Library for the management of a queue of nodes
	Antonio Diaz Flores
	A01329256
	Oscar Barbosa Aquino
	A01329173
	Date: 16/11/18
*/

#include "queue.h"

/*
	Function that sorts a queue by the nombre field in the nodes
*/
void sortByName(struct Queue **pth){
	int  l = 0;
	while((*pth)->next){
		l++;
		(*pth) = (*pth)->next;
	}
	for (int i = 0; i < l; ++i){
		if(strcmp2( (*pth)->node->nombre , (*pth)->previous->node->nombre )<0)
			swap(pth);
		(*pth) = (*pth)->previous;
	}
}

/*
	Function that sorts a queue by the cantidad field in the nodes
*/
void sortByCompra(struct Queue **pth){
	int  l = 0;
	while((*pth)->next){
		l++;
		(*pth) = (*pth)->next;
	}
	for (int i = 0; i < l; ++i){
		if((*pth)->node->cantidad < (*pth)->previous->node->cantidad)
			swap(pth);
		(*pth) = (*pth)->previous;
	}
}

/*
	Function that sorts a queue by the ventas field in the nodes
*/
void sortByVenta(struct Queue **pth){
	int  l = 0;
	while((*pth)->next){
		l++;
		(*pth) = (*pth)->next;
	}
	for (int i = 0; i < l; ++i){
		if((*pth)->node->precioVenta < (*pth)->previous->node->precioVenta)
			swap(pth);
		(*pth) = (*pth)->previous;
	}
}

/*
	Function that pushes a node to the queue and then sorts it by name field
*/
void pushName(struct Queue **pth,struct node* data){
	push(pth,data);
	sortByName(pth);
}

/*
	Function that pushes a node to the queue and then sorts it by cantidad field
*/
void pushCompra(struct Queue **pth,struct node* data){
	push(pth,data);
	sortByCompra(pth);
}

/*
	Function that pushes a node to the queue and then sorts it by venta field
*/
void pushVenta(struct Queue **pth,struct node* data){
	push(pth,data);
	sortByVenta(pth);
}

/*
	Function for cleaning a string from \n chars
*/
void clean(char **key){
	int l = 0;
	while(*(*key) != '\0'){
		if (*(*key) == '\n'){
			*(*key) = '\0';
			l--;
		}
		l++;
		(*key)++;
	}
	while(l>-1){
		(*key)--;
		l--;
	}
}

/*
	Function for searching specific nodes in the tree by id and then returns them
*/
struct node* search(struct node *ptr,char* key){
	if(strcmp2(ptr->key,key) != 0){
		if (strcmp2( ptr->key, key)<0){
			if(ptr->right){
				return search(ptr->right,key);
			}
			else{
				return NULL;
			}
		}
		else{
			if(ptr->left){
				return search(ptr->left,key);
			}
			else{
				return NULL;
			}
		}
	}
	else{
		return ptr;
	}
}

/*
	Function that returns a double pointer to char with the information of a node
*/
char** getInfo(struct node* node){
	char** array = (char**)malloc(5*sizeof(char*));
	*(array+0) = NULL;
	*(array+1) = NULL;
	*(array+2) = NULL;
	*(array+3) = NULL;
	*(array+4) = NULL;

	char* copyNombre = (char*)(malloc(sizeof(char)*1024));
	char* copyVenta = (char*)(malloc(sizeof(char)*1024));
	char* copyCompra = (char*)(malloc(sizeof(char)*1024));
	char* copyKey = (char*)(malloc(sizeof(char)*1024));

	strcpy(copyNombre , node->nombre);
	strcpy(copyVenta , node->venta);
	strcpy(copyCompra , node->cant);
	strcpy(copyKey , node->key);

	*array = copyKey;
	*(array+1) = copyNombre;
	*(array+2) = copyCompra;
	*(array+3) = copyVenta;
	return array;
}

/*
	Function that returns a double pointer to char with the information of a node for saving
*/
char** getInfo2(struct node* node){
	char** array = (char**)malloc(5*sizeof(char*));
	*(array+0) = NULL;
	*(array+1) = NULL;
	*(array+2) = NULL;
	*(array+3) = NULL;
	*(array+4) = NULL;

	char* copyNombre = (char*)(malloc(sizeof(char)*1024));
	char* copyVenta = (char*)(malloc(sizeof(char)*1024));
	char* copyCompra = (char*)(malloc(sizeof(char)*1024));
	char* copyKey = (char*)(malloc(sizeof(char)*1024));
	char* strEnabled = (char*)(malloc(sizeof(char)*1024));

	strcpy(copyNombre , node->nombre);
	strcpy(copyVenta , node->venta);
	strcpy(copyCompra , node->cant);
	strcpy(copyKey , node->key);
	strcpy(strEnabled , node->enabled);

	*array = copyKey;
	*(array+1) = copyNombre;
	*(array+2) = copyCompra;
	*(array+3) = copyVenta;
	*(array+4) = strEnabled;
	return array;
}

/*
	Function that returns a double pointer to char with the information of a node from an existing double pointer
*/
char** desplegarInfo(struct node* node,char** array){
	
	char* copyNombre = (char*)(malloc(sizeof(char)*1024));
	char* copyVenta = (char*)(malloc(sizeof(char)*1024));
	char* copyCompra = (char*)(malloc(sizeof(char)*1024));
	char* copyKey = (char*)(malloc(sizeof(char)*1024));

	strcpy(copyNombre , node->nombre);
	strcpy(copyVenta , node->venta);
	strcpy(copyCompra , node->cant);
	strcpy(copyKey , node->key);

	*array = copyKey;
	*(array+1) = copyNombre;
	*(array+2) = copyCompra;
	*(array+3) = copyVenta;
	return array;
}

struct node* keyDelete = NULL;

/* 
	Function that returns the information of a node that's going to be erased
*/
char** deleteData(struct node** ptr,char* key){
	char** array = (char**)malloc(5*sizeof(char*));
	*(array+0) = NULL;
	*(array+1) = NULL;
	*(array+2) = NULL;
	*(array+3) = NULL;
	*(array+4) = NULL;
	if(*ptr){
		struct node* ptn = search(*ptr,key);
		
		if (ptn && strcmp(ptn->enabled,"1")==0){
			keyDelete = search(*ptr,key);
			*(array+4) = (char*)ptr;
			return desplegarInfo(ptn,array);
		}
		else
			return array;
	}
	else{
		return array;
	}
}

/*
	Function to delete the data that was shown previously
*/
void deleteDis(){
	if(keyDelete)
		keyDelete->enabled = "0";
	keyDelete = NULL;
}

struct node* keyEdit = NULL;

/*
	Function that returns the information of a node that's going to be edited
*/
char** modifyId(struct node** ptr,char* key){
	char** array = (char**)malloc(5*sizeof(char*));
	*(array+0) = NULL;
	*(array+1) = NULL;
	*(array+2) = NULL;
	*(array+3) = NULL;
	*(array+4) = NULL;
	if(*ptr){
		struct node* ptn = search(*ptr,key);
		
		if (ptn && strcmp(ptn->enabled,"1")==0){
			keyEdit = search(*ptr,key);
			*(array+4) = (char*)ptr;
			return desplegarInfo(ptn,array);
		}
		else
			return array;
	}
	else{
		return array;
	}
}

/*
	Function to edit the data that was shown previously
*/
void editDis(char** array){
	if (keyEdit){
		char *Copykey = (char*)(malloc(sizeof(char)*1024));
		char *Copynombre = (char*)(malloc(sizeof(char)*1024));
		char *Copycompra = (char*)(malloc(sizeof(char)*1024));
		char *Copyventa = (char*)(malloc(sizeof(char)*1024));
		
		strcpy(Copykey, (*array));
		strcpy(Copynombre,*(array+1));
		strcpy(Copycompra,*(array+2));
		strcpy(Copyventa,*(array+3));

		keyEdit->key =Copykey;
		keyEdit->nombre = Copynombre;
		keyEdit->cant = Copycompra;
		keyEdit->venta = Copyventa;
		keyEdit->cantidad = atof(Copycompra);
		keyEdit->precioVenta = atof(Copyventa);
	}
	keyDelete = NULL;
}

struct node* keyId = NULL;

/*
	Function that returns the information of a node that's going to be recovered
*/
char** recoverId(struct node** ptr,char* key){
	char** array = (char**)malloc(5*sizeof(char*));
	*(array+0) = NULL;
	*(array+1) = NULL;
	*(array+2) = NULL;
	*(array+3) = NULL;
	*(array+4) = NULL;
	if(*ptr){
		struct node* ptn = search(*ptr,key);
		
		if (ptn && strcmp(ptn->enabled,"0")==0){
			keyId = search(*ptr,key);
			*(array+4) = (char*)ptr;
			return desplegarInfo(ptn,array);
		}
		else
			return array;
	}
	else{
		return array;
	}
}

/*
	Function to recover the data that was shown previously
*/
void recoverDis(){
	if(keyId){
		keyId->enabled = "1";
	}
	keyId = NULL;
}

/*
	Function that searches for an element in the queue by partial match
*/
struct node* searchQueue(struct Queue *queue,char* key){
	while(queue){
		struct node* tmp = pop(&queue);
		if (strcmp2(tmp->key,key)==0 || strcmp2(tmp->nombre,key)==0 || strcmp2(tmp->venta,key)==0 || strcmp2(tmp->cant,key)==0)
			return tmp;
	}
	return NULL;
}
