#include<iostream>
#include<vector>
#include<string.h>
#include<cstdio>
#include<ctime>
#include<cstdlib>
#include<string>
#include<map>
#include<set>
#include<list>
#include<queue>
#include<math.h>
#include<algorithm>
#include<cstdlib>
#include<stack>
#include<cctype>
#include<sstream>
#define INF 0x7777777f
#define sys std::ios::sync_with_stdio(false)
#define LL long long
#define Uint unsigned int
using namespace std;
struct TreapNode{
	TreapNode *left,*right;
	int val,fix;
	TreapNode(){
		left = right = NULL;
	}
};
void RotateL(TreapNode* &a){
	TreapNode* b = a->right;
	a->right = b->left;
	b->left = a;
	a = b;
}
void RotateR(TreapNode* &a){
	TreapNode* b = a->left;
	a->left = b->right;
	b->right = a;
	a = b;
}
TreapNode* search(TreapNode* a,int value){
	if(!a)return NULL;
	int val = a->val;
	if(value == val)return a;
	else if(value < val)return search(a->left,value);
	else return search(a->right,value);
}
void travel(TreapNode* a){
	if(!a)return;
	travel(a->left);
	printf("%d ",a->val);
	travel(a->right);
}
void TreapInsert(TreapNode* &p,int value){
	if(!p){
		p = new TreapNode();
		p->val = value;
		p->fix = rand();
	}else if(value <= p->val){
		TreapInsert(p->left,value);
		if(p->left->fix < p->fix)RotateR(p);
	}else{
		TreapInsert(p->right,value);
		if(p->right->fix < p->fix)RotateL(p);
	}
}
void TreapDelete(TreapNode* &p,int value){
	if(!p){cout << "Warning!No such value in Treap..." << endl;return; }
	if(value == p->val){
		if(!p->right || !p->left){
			TreapNode* t = p;
			if(!p->right)p = p->left;
			else p = p->right;
			delete t;
		}else{
			if(p->left->fix < p->right->fix){
				RotateR(p);TreapDelete(p->right,value);
			}else{
				RotateL(p);TreapDelete(p->left,value);
			}
		}
	}
	else if(value < p->val)TreapDelete(p->left,value);
	else TreapDelete(p->right,value);
}

int main(){
	int a,b,c;cin >> a >> b >>c;
	TreapNode* root = NULL;
	printf("Insert %d times.\n",a);
	srand((int)time(0));
	while(a--){
		int m;cin >> m;
		TreapInsert(root,m);
		printf("%d Inserted.\n",m);
	}
	printf("search %d times.\n",b);
	while(b--){
		int m;cin >> m;
		TreapNode* p = search(root,m);
		if(p)printf("%d Found.\n",p->val);
		else printf("No result!No such value in Treap!\n");
	}
	printf("travel Treap...\n");
	travel(root);cout << endl;
	printf("Delete %d times.\n",c);
	while(c--){
		int m;cin >> m;
		printf("Trying to delete %d in Treap...\n",m);
		TreapDelete(root,m);
	}
	printf("Now the Treap become:\n");
	travel(root);cout << endl;
	return 0;
}




