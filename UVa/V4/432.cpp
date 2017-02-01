#include<cstdio>
#include<algorithm>
using namespace std;

struct node {
	bool visit;
	int x,y;
	node *right;
	node *left;
	node *parent;
	node(int X,int Y){
		x = X;
		y = Y;
		visit = false;
		parent = left = right = NULL;
	}
};

node *tree;

void recurse_left(node *t,int x , int y , int B , int H , int p ){
	//printf("Rec Left (%d,%d)\n",x,y);
	if (p==0){ /* create triangle */
		t->left = new node(x-B/2,y-H);
		t->right = new node(x+B/2,y-H);
		//printf("Create Left (%d,%d)\n",x-B/2,y-H);
		//printf("Create Right (%d,%d)\n",x+B/2,y-H);
		t->left->parent = t;
		t->right->parent = t;
		return ;
	}
	t->left = new node(x - B/4, y - H/2);
	t->right = new node(x + B/4, y - H/2);
	recurse_left(t->left, x - B/4 , y - H/2 , B/2 , H/2 , p - 1 );
	recurse_left(t->right, x - B/4 , y - H/2 , B/2 , H/2 , 0 );
	t->right->parent = t;
	t->left->parent = t;
}

void recurse_right(node *t,int x , int y , int B , int H , int q ){
	//printf("Rec Right (%d,%d)\n",x,y);
	if (q==0){ /* create triangle */
		//printf("Create Left (%d,%d)\n",x-B/2,y-H);
		//printf("Create Right (%d,%d)\n",x+B/2,y-H);
		t->left = new node(x-B/2,y-H);
		t->right = new node(x+B/2,y-H);
		t->left->parent = t;
		t->right->parent = t;
		return ;
	}
	t->left = new node(x - B/4, y - H/2);
	t->right = new node(x + B/4, y - H/2);
	recurse_right(t->right, x + B/4 , y - H/2 , B/2 , H/2 , q-1 );
	recurse_right(t->left, x - B/4 , y - H/2 , B/2 , H/2 , 0 );
	t->right->parent = t;
	t->left->parent = t;
}

void create_tree(int p,int q,int x,int y){
	if (p==0 && q==0){
		tree = new node(x,y);
		tree->left = new node(x-1,y-1);
		tree->left->parent = tree;
		tree->right = new node(x+1,y-1);
		tree->right->parent = tree;
		return;
	}
	//printf("Raiz (%d,%d)\n",x,y);
	int m = max(p,q);
	tree = new node(x,y);
	int B = 2 * abs(x);
	int H = abs(y);
	tree->left = new node(x - B/4, y - H/2);
	tree->right = new node(x + B/4, y - H/2);
	recurse_left(tree->left, x - B/4 , y - H/2 , B/2 , H/2 , p - 1 );
	recurse_right(tree->right, x + B/4 , y - H/2 , B/2 , H/2 ,q - 1 );
	tree->left->parent = tree;
	tree->right->parent = tree;
}

void travel_tree(){
	node *act = tree;
	node *left;
	node *right;
	
	while (act != NULL){
		/* go to the lower left */
		left = act->left;
		while (left->left != NULL) left = left->left;
		printf("(%d,%d)(%d,%d)\n",act->x,act->y,left->x,left->y);
		right = left->parent->right;
		printf("(%d,%d)(%d,%d)\n",left->x,left->y,right->x,right->y);
		act->visit = true;
		left->visit = true;
		right->visit = true;
		/* go to the topmost unvisited triangle */
		act = right->parent;
		while (act!= NULL && act->visit) act = act->parent;
		if (act == NULL){
			printf("(%d,%d)(%d,%d)\n",right->x,right->y,tree->x,tree->y);
			break;
		}
		printf("(%d,%d)(%d,%d)\n",right->x,right->y,act->x,act->y);
		act->visit = true;
		printf("(%d,%d)(%d,%d)\n",act->x,act->y,act->parent->right->x,act->parent->right->y);
		act = act->parent->right;
 	}
}

void delete_tree(node *t){
	if (t!= NULL){
		delete_tree(t->left);
		delete_tree(t->right);
		delete t;
		t = NULL;
	}
}

int main(){

	int p,q,x,y;
	int runs;
	scanf("%d",&runs);
	while (runs--){
		scanf("%d %d %d %d",&p,&q,&x,&y);
		create_tree(p,q,x,y);
		travel_tree();
		putchar('\n');
		if (runs) delete_tree(tree);
	}
	return 0;
}