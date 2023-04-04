#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <deque>
#include <map>
#include <iomanip>
#include <iostream>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;
#define LF putchar('\n')
#define SP putchar(' ')
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define repp(i,a,b) for(register int i=(a);i>=(b);i--)
#define pill pair<int,int>
#define mem(t, v) memset((t),v,sizeof(t))
#define fir first
#define sec second
#define mk make_pair
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
#define lc root<<1
#define rc root<<1|1
typedef long long ll;
typedef unsigned long long ull;
template<typename T>
void read(T &x) {x=0;char ch=getchar();ll f=1;while(!isdigit(ch)){if(ch=='-')f*=-1;ch=getchar();}while(isdigit(ch)){x=(x<<3)+(x<<1)+(ch^48);ch=getchar();}x*=f;}
template<typename T, typename... Args>
void read(T &first, Args& ... args) {read(first);read(args...);}
template<typename T>
void write(T arg) {T x=arg;if(x<0) {putchar('-');x=-x;}if(x>9) {write(x/10);}putchar(x%10+'0');}
template<typename T, typename ... Ts>
void write(T arg, Ts ... args) {write(arg);if(sizeof...(args)!=0) {putchar(' ');write(args ...);}}
const ll MOD=1e9+7,N=1e5+10;
int n,root,tot;
struct node{
	int lson,rson;
	int key,val;//�ؼ�ֵ�������
	int cnt,Size; //��ǰֵ�����˼��Σ����Ĵ�С 
	#define L(p) (tree[p].lson)
	#define R(p) (tree[p].rson)
	#define K(p) (tree[p].key)
	#define V(p) (tree[p].val)
	#define C(p) (tree[p].cnt)
	#define S(p) (tree[p].Size)
}tree[N];
void pushup(int p){
	S(p)=S(L(p))+S(R(p))+C(p);
}
int make_node(int key){
	K(++tot)=key;
	C(tot)=S(tot)=1;
	V(tot)=rand();
	return tot;
}
void zig(int &p){//���� 
	int q=L(p);
	L(p)=R(q);
	R(q)=p;
	p=q;
	pushup(R(p));
	pushup(p);
}
void zag(int &p){//���� 
	int q=R(p);
	R(p)=L(q);
	L(q)=p;
	p=q;
	pushup(L(p));
	pushup(p);
}
void build(){//�����ڱ�����Ϊ���������� 
	make_node(-INF);
	make_node(INF);
	root=1;
	R(1)=2;
	pushup(2);
	if(V(1)<V(2))zag(root);//��ֹ���ֵ������ 
}
void Insert(int &p,int key){//����һ��ȨֵΪkey�ĵ� 
	if(!p)p=make_node(key);
	else if(K(p)==key)C(p)++;
	else if(K(p)>key){
		Insert(L(p),key);
		if(V(L(p))>V(p))zig(p);//����ά���� 
	}
	else{
		Insert(R(p),key);
		if(V(R(p))>V(p))zag(p);//����ά���� 
	}
	pushup(p);
}
void Remove(int &p,int key){//ɾ�� 
	if(!p)return;
	if(K(p)==key){//�ҵ�Ҫɾ���ĵ� 
		if(C(p)>1)C(p)--;
		else if(L(p) or R(p)){
			if(!R(p) or V(L(p))>V(R(p))){
				zig(p);
				Remove(R(p),key);
			}
			else{
				zag(p);
				Remove(L(p),key);
			}
		}
		else p=0;//Ҷ�ӽڵ� 
	}
	else if(K(p)>key)Remove(L(p),key);
	else Remove(R(p),key);
	pushup(p);
}
int get_rank_by_key(int p,int key){//������ֵ������ 
	if(!p)return -1;
	if(K(p)==key)return S(L(p))+1;
	if(K(p)>key)return get_rank_by_key(L(p),key);
	return S(L(p))+C(p)+get_rank_by_key(R(p),key);
}
int get_key_by_rank(int p,int rnk){//������������ֵ
	if(!p)return -1;
	if(S(L(p))>=rnk)return get_key_by_rank(L(p),rnk);
	if(S(L(p))+C(p)>=rnk)return K(p);
	return get_key_by_rank(R(p),rnk-S(L(p))-C(p));
}
int get_prev(int p,int key){//��ѯ�ϸ�С��key������� 
	if(!p)return -INF;
	if(K(p)>=key)return get_prev(L(p),key);
	return max(K(p),get_prev(R(p),key)); //С�˺������� 
}
int get_next(int p,int key){//��ѯ�ϸ����key����С�� 
	if(!p)return INF;
	if(K(p)<=key)return get_next(R(p),key);
	return min(K(p),get_next(L(p),key)); //���˺�����С�� 
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	build();
	 scanf("%d",&n);
	 while(n--){
	 	int op,x;
	 	scanf("%d%d",&op,&x);
	 	if(op==1)Insert(root,x);
	 	else if(op==2)Remove(root,x);
	 	else if(op==3)printf("%d\n",get_rank_by_key(root,x)-1);//-1����Ϊȥ��һ����С�ڱ� 
	 	else if(op==4)printf("%d\n",get_key_by_rank(root,x+1));//+1����Ϊȥ��һ����С�ڱ� 
	 	else if(op==5)printf("%d\n",get_prev(root,x));
	 	else if(op==6)printf("%d\n",get_next(root,x));
	 }
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
/*
���� x ��
ɾ�� x ��(���ж����ͬ��������ֻɾ��һ��)
��ѯ x ��������(��������Ϊ�ȵ�ǰ��С�����ĸ��� +1 )
��ѯ����Ϊ x ����
�� x ��ǰ��(ǰ������ΪС�� x����������)
�� x �ĺ��(��̶���Ϊ���� x������С����)
*/
