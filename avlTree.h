/*
	Program: Library for the management of an AVL Tree
	Antonio Diaz Flores
	A01329256
	Oscar Barbosa Aquino
	A01329173
	Date: 16/11/18
*/

#include "node.h"

/*
	Function that returns the greater from two integers
*/
int maximo(int a, int b){
	return a>b ? a:b;
}

/*
	Function that returns the height from a node
*/
int altura(struct node* node){
	if (node)
		return node->altura;
	return 0;
}

/*
	Function that returns the differencein heights from the children of a node
*/
int offSetFromRoot(struct node* node){
	if(node)
		return altura(node->right) - altura(node->left);
	return 0;
}

/*
	Function that creates a new node
*/
struct node* createRoot(char** array){
	struct node* temp = (struct node *)malloc(sizeof(struct node));
	
	char *Copykey = (char*)(malloc(sizeof(char)*1024));
	char *Copynombre = (char*)(malloc(sizeof(char)*1024));
	char *Copycompra = (char*)(malloc(sizeof(char)*1024));
	char *Copyventa = (char*)(malloc(sizeof(char)*1024));
	char *en = (char*)(malloc(sizeof(char)*1024));
	
	strcpy(Copykey, (*array));
	strcpy(Copynombre,*(array+1));
	strcpy(Copycompra,*(array+2));
	strcpy(Copyventa,*(array+3));
	strcpy(en,*(array+4));

	temp->key =Copykey;
	temp->nombre = Copynombre;
	temp->cant = Copycompra;
	temp->venta = Copyventa;
	
	temp->cantidad = atof(Copycompra);
	temp->precioVenta = atof(Copyventa);
	

	temp->left = NULL;
	temp->right = NULL;
	temp->altura = 1;
	temp->enabled = en;
	printf("enabled = %s\n",temp->enabled );
	return temp;
}

/*
	Function that rotates the tree in a right right case
*/
void case1(struct node** ptx){
	struct node *x = (*ptx);
	struct node *y = x->right;
	struct node *b = y->left;

	y->left = x;
	x->right = b;

	x->altura = 1 + maximo(altura(x->left),altura(x->right));
	y->altura = 1 + maximo(altura(y->left),altura(y->right));

	*ptx = y;
}

/*
	Function that rotates the tree in a right left case
*/
void case2(struct node** ptx){
	struct node *x = (*ptx);
	struct node *z = x->right;
	struct node *y = z->left;
	struct node *b = y->left;
	struct node *c = y->right;

	y->left = x;
	y->right = z;
	x->right = b;
	z->left = c;

	x->altura = 1 + maximo(altura(x->left),altura(x->right));
	z->altura = 1 + maximo(altura(z->left),altura(z->right));
	y->altura = 1 + maximo(altura(y->left),altura(y->right));

	*ptx = y;

}

/*
	Function that rotates the tree in a left left case
*/
void case3(struct node** ptx){
	struct node *z = (*ptx);
	struct node *y = z->left;
	struct node *c = y->right;

	y->right = z;
	z->left = c;

	z->altura = 1 + maximo(altura(z->left),altura(z->right));
	y->altura = 1 + maximo(altura(y->left),altura(y->right));

	*ptx = y;
}

/*
	Function that rotates the tree in a left right case
*/
void case4(struct node** ptx){
	struct node *z = (*ptx);
	struct node *x = z->left;
	struct node *y = x->right;
	struct node *b = y->left;
	struct node *c = y->right;

	y->left = x;
	y->right = z;
	x->right = b;
	z->left = c;

	z->altura = 1 + maximo(altura(z->left),altura(z->right));
	x->altura = 1 + maximo(altura(x->left),altura(x->right));
	y->altura = 1 + maximo(altura(y->left),altura(y->right));

	*ptx = y;
}

/*
	Function for inserting a new key to the tree
*/
int insert(struct node** ptr, char** array, char *key){
	if (*ptr == NULL){
		*ptr =  createRoot(array);
		return 1;
	}
	else if(strcmp2(key,(*ptr)->key)!=0){
		int x = 1;
		if (strcmp2(key,(*ptr)->key)<0)
			x = insert(&(*ptr)->left,array,key);
		else if(strcmp2(key,(*ptr)->key)>0)
			x = insert(&(*ptr)->right,array,key);

		(*ptr)->altura = maximo(altura((*ptr)->left),altura( (*ptr)->right)) + 1;

		int dif = offSetFromRoot(*ptr);


		if(dif > 1 && strcmp2((*ptr)->right->key,key)<=-1)
			case1(ptr);
		if(dif > 1 && strcmp2((*ptr)->right->key,key)>=1)
			case2(ptr);
		if(dif < -1 && strcmp2((*ptr)->left->key,key)>=1)
			case3(ptr);
		if(dif < -1 && strcmp2((*ptr)->left->key,key)<=-1)
			case4(ptr);
		return x;
	}
	else{
		return 0;
	}
}

/*
	Function that returns the size of a tree
*/
int sizeOfTree(struct node* root, int x){
	if(root){
		if(strcmp(root->enabled,"1")==0)
			return x++;
		sizeOfTree(root->left,x);
		sizeOfTree(root->right,x);
	}
}

/*
	Function that returns a triple pointer to char with the information of the nodes in a Queue
*/
char*** sendGet(struct Queue** queue){
	char *** array = (char***)(malloc(sizeof(char**)*(sizeOfQueue(*queue)+1)));
	int  l =0;
	while(*queue){
		*(array+l) = getInfo(get(queue));
		l++;
	}
	*(array+l) = NULL;
	return array;
}

/*
	Function that returns a triple pointer to char with the information of the nodes in a Queue
*/
char*** sendPop(struct Queue** queue){
	char *** array = (char***)(malloc(sizeof(char**)*(sizeOfQueue(*queue)+1)));
	int  l =0;
	while(*queue){
		*(array+l) = getInfo(pop(queue));
		l++;
	}
	*(array+l) = NULL;
	return array;
}

/*
	Function that fills the queue with the nodes in the tree
*/
void fillQueue(struct Queue** queue,struct node* root){
	if (root){
		if(strcmp(root->enabled,"1")==0)
			push(queue,root);
		fillQueue(queue,root->left);
		fillQueue(queue,root->right);
	}
}

/*
	Function that fills the queue with the nodes in the tree in order by Id
*/
void fillQueueId(struct node* root, struct Queue** queue){
	if(root){
		fillQueueId(root->left,queue);
		if(strcmp(root->enabled,"1")==0)
			push(queue,root);
		fillQueueId(root->right,queue);
	}
}

/*
	Function that fills the queue with the nodes in the tree in order by Id
*/
void fillQueueName(struct node* root,struct Queue** queue){
	if (root){
		fillQueueName(root->left,queue);
		if(strcmp(root->enabled,"1")==0)
			pushName(queue,root);
		fillQueueName(root->right,queue);
	}
}

/*
	Function that fills the queue with the nodes in the tree in order by compra
*/
void fillQueueCompra(struct node* root,struct Queue** queue){
	if (root){
		fillQueueCompra(root->left,queue);
		if(strcmp(root->enabled,"1")==0)
			pushCompra(queue,root);
		fillQueueCompra(root->right,queue);
	}
}

/*
	Function that fills the queue with the nodes in the tree in order by venta
*/
void fillQueueVenta(struct node* root,struct Queue** queue){
	if (root){
		fillQueueVenta(root->left,queue);
		if(strcmp(root->enabled,"1")==0)
			pushVenta(queue,root);
		fillQueueVenta(root->right,queue);
	}
}

/*
	Function that fills the queue according to the selection of the user
*/
char*** reporteSwitch(struct node* root,int selec){
	struct Queue *queue = NULL;
	switch(selec){
		case 1:
			fillQueueId(root,&queue);
			if (queue)
			return sendGet(&queue);
			break;
		case 2:
			fillQueueId(root,&queue);
			if (queue)
			return sendPop(&queue);
			break;
		case 3:
			fillQueueName(root,&queue);
			if (queue)
			return sendGet(&queue);
			break;
		case 4:
			fillQueueName(root,&queue);
			if (queue)
			return sendPop(&queue);
			break;
		case 5:
			fillQueueCompra(root,&queue);
			if (queue)
			return sendGet(&queue);
			break;
		case 6:
			fillQueueCompra(root,&queue);
			if (queue)
			return sendPop(&queue);
			break;
		case 7:
			fillQueueVenta(root,&queue);
			if (queue)
			return sendGet(&queue);
			break;
		case 8:
			fillQueueVenta(root,&queue);
			if (queue)
			return sendPop(&queue);
			break;
	}
	return NULL;
}

/*
	Function that searches for a exact match of a node by id in the tree and return the information of the node
*/
char*** searchExactMatch(struct node *root, char* key){
	if(strcmp2(key,"")!=0){
		struct Queue *queue = NULL;
		struct node *temp = search(root,key);
		if(temp && strcmp(temp->enabled,"1")==0){
			push(&queue,temp);
			return sendPop(&queue);
		}
	}
	return NULL;
}

/*
	Function that fills a Queue with all lesser values of a node in the tree by an specific field
*/
void fillLesser(struct node *root,char* key,struct Queue** queue){
	if(root){
		fillLesser(root->left,key,queue);
		if(strcmp(root->enabled,"1")==0)
			if(strcmp2(root->key,key)<=0)
				push(queue,root);
		fillLesser(root->right,key,queue);
	}
}

/*
	Function that returns all lesser values of a node in the tree by an specific field with a triple pointer to char
*/
char*** searchLesser(struct node *root, char* key){
	if(strcmp2(key,"")!=0){
		struct Queue *queue = NULL;
		fillLesser(root,key,&queue);
		if(queue){
			return sendGet(&queue);
		}
	}
	return NULL;
}

/*
	Function that fills a Queue with all greater values of a node in the tree by an specific field
*/
void fillGreater(struct node *root,char* key,struct Queue** queue){
	if(root){
		fillGreater(root->left,key,queue);
		if(strcmp(root->enabled,"1")==0)
			if(strcmp2(root->key,key)>=0)
				push(queue,root);
		fillGreater(root->right,key,queue);
	}
}

/*
	Function that returns all greater values of a node in the tree by an specific field with a triple pointer to char
*/
char*** searchGreater(struct node *root, char* key){
	struct Queue *queue = NULL;
	fillGreater(root,key,&queue);
	if(queue){
		return sendGet(&queue);
	}
	return NULL;
}

/*
	Function that fills a Queue with all values of a node that are equal to an specific key
*/
void fillStr(struct node *root,char* key,struct Queue** queue){
	if(root){
		fillStr(root->left,key,queue);
		if(strcmp(root->enabled,"1")==0)
			if(strcmp2(root->nombre,key)==0 || strcmp2(root->venta,key)==0 || strcmp2(root->cant,key)==0)
				push(queue,root);
		fillStr(root->right,key,queue);
	}
}

/*
	Function that searches for a exact match of a node by a field in the tree
*/
char*** searchStr(struct node *root, char* key){
	struct Queue *queue = NULL;
	fillStr(root,key,&queue);
	if(queue){
		return sendGet(&queue);
	}
	return NULL;
}

/*
	Function that searches for a exact match of a node by a field in the tree
*/
void fillPartial(struct node *root,char* key,struct Queue** queue){
	if(root){
		fillPartial(root->left,key,queue);
		if(strcmp(root->enabled,"1")==0)
			if(strstr(root->nombre,key)!=NULL || strstr(root->venta,key)!=NULL || strstr(root->cant,key)!=NULL)
				push(queue,root);
		fillPartial(root->right,key,queue);
	}
}

/*
	Function that searches for a partial match of a node by a field in the tree
*/
char*** searchPartialMatch(struct node *root, char* key){
	struct Queue *queue = NULL;
	fillPartial(root,key,&queue);
	if(queue){
		return sendGet(&queue);
	}
	return NULL;
}

/*
	Function that returns a triple pointer to char with the all the nodes in the tree
*/
char*** guardarArbol(struct node* root){
	struct Queue* queue = NULL;
	int l = 0;

	char *** array = (char***)(malloc(sizeof(char**)*(sizeOfTree(root,0)+1)));

	if(root)
		push(&queue,root);
	else{
		free(array);
		return NULL;
	}
	
	while(queue){
		struct node* current = get(&queue);
		if(current->left)
			push(&queue,current->left);
		if(current->right)
			push(&queue,current->right);
		*(array+l) = getInfo2(current);
		l++;
	}
	*(array+l) = NULL;

	return array;
}