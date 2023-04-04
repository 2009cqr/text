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
	int key,val;//关键值与随机数
	int cnt,Size; //当前值出现了几次，树的大小 
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
void zig(int &p){//右旋 
	int q=L(p);
	L(p)=R(q);
	R(q)=p;
	p=q;
	pushup(R(p));
	pushup(p);
}
void zag(int &p){//左旋 
	int q=R(p);
	R(p)=L(q);
	L(q)=p;
	p=q;
	pushup(L(p));
	pushup(p);
}
void build(){//两个哨兵（因为有左右旋） 
	make_node(-INF);
	make_node(INF);
	root=1;
	R(1)=2;
	pushup(2);
	if(V(1)<V(2))zag(root);//防止随机值出问题 
}
void Insert(int &p,int key){//插入一个权值为key的点 
	if(!p)p=make_node(key);
	else if(K(p)==key)C(p)++;
	else if(K(p)>key){
		Insert(L(p),key);
		if(V(L(p))>V(p))zig(p);//回溯维护堆 
	}
	else{
		Insert(R(p),key);
		if(V(R(p))>V(p))zag(p);//回溯维护堆 
	}
	pushup(p);
}
void Remove(int &p,int key){//删除 
	if(!p)return;
	if(K(p)==key){//找到要删除的点 
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
		else p=0;//叶子节点 
	}
	else if(K(p)>key)Remove(L(p),key);
	else Remove(R(p),key);
	pushup(p);
}
int get_rank_by_key(int p,int key){//根据数值查排名 
	if(!p)return -1;
	if(K(p)==key)return S(L(p))+1;
	if(K(p)>key)return get_rank_by_key(L(p),key);
	return S(L(p))+C(p)+get_rank_by_key(R(p),key);
}
int get_key_by_rank(int p,int rnk){//根据排名查数值
	if(!p)return -1;
	if(S(L(p))>=rnk)return get_key_by_rank(L(p),rnk);
	if(S(L(p))+C(p)>=rnk)return K(p);
	return get_key_by_rank(R(p),rnk-S(L(p))-C(p));
}
int get_prev(int p,int key){//查询严格小于key的最大数 
	if(!p)return -INF;
	if(K(p)>=key)return get_prev(L(p),key);
	return max(K(p),get_prev(R(p),key)); //小了后找最大的 
}
int get_next(int p,int key){//查询严格大于key的最小数 
	if(!p)return INF;
	if(K(p)<=key)return get_next(R(p),key);
	return min(K(p),get_next(L(p),key)); //大了后找最小的 
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
	 	else if(op==3)printf("%d\n",get_rank_by_key(root,x)-1);//-1是因为去掉一个极小哨兵 
	 	else if(op==4)printf("%d\n",get_key_by_rank(root,x+1));//+1是因为去掉一个极小哨兵 
	 	else if(op==5)printf("%d\n",get_prev(root,x));
	 	else if(op==6)printf("%d\n",get_next(root,x));
	 }
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
/*
插入 x 数
删除 x 数(若有多个相同的数，因只删除一个)
查询 x 数的排名(排名定义为比当前数小的数的个数 +1 )
查询排名为 x 的数
求 x 的前驱(前驱定义为小于 x，且最大的数)
求 x 的后继(后继定义为大于 x，且最小的数)
*/
