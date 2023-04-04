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
const ll MOD=1e9+7,N=2e5+10;
int root,tot,n,opt,x;
struct node{
	int ch[2],fa,val,size,cnt;//���ҽڵ㣬���ڵ㣬Ȩֵ����С���ظ� 
}tree[N];
void pushup(int p){
	tree[p].size=tree[tree[p].ch[0]].size+tree[tree[p].ch[1]].size+tree[p].cnt; 
}
void rotate(int x){//��������һ��
	 int y=tree[x].fa,z=tree[y].fa,k=tree[y].ch[1]==x;
	 tree[z].ch[tree[z].ch[1]==y]=x;
	 tree[x].fa=z;
	 tree[y].ch[k]=tree[x].ch[k^1];
	 tree[tree[x].ch[k^1]].fa=y;
	 tree[x].ch[k^1]=y;
	 tree[y].fa=x;
	 pushup(x),pushup(y);
}
//��ÿ��������ɺ����spaly���Ա�֤������ƽ�� 
void splay(int x,int k){//x��ת��k�£�k=0ʱת�����ڵ㣩 
	while(tree[x].fa!=k){
		int y=tree[x].fa,z=tree[y].fa;
		if(k!=z){
			if((tree[y].ch[1]==x)^(tree[z].ch[1]==y))//Z��
				rotate(x);
			else rotate(y); 
		} 
		rotate(x);
	}
	if(k==0)root=x;
}
void Inster(int x){//����x 
	int u=root,fa=0;
	while(u and tree[u].val!=x){
		fa=u;
		u=tree[u].ch[x>tree[u].val];
	}
	if(u){
		tree[u].cnt++;
		pushup(u);
	}
	else{
		u=++tot;
		tree[fa].ch[x>tree[fa].val]=u;
		tree[tot].fa=fa;
		tree[tot].val=x;
		tree[tot].ch[0]=tree[tot].ch[1]=0;
		tree[tot].size=1;
		tree[tot].cnt=1;
	}
	splay(u,0);
}
int getv(int v){//����ȨֵΪv�Ľڵ�ı��
	int u=root,res;
	while(u){
		if(tree[u].val>=v)res=u,u=tree[u].ch[0];//��v���ܲ����ڣ���res��¼����ֵ�� 
		else u=tree[u].ch[1];
	}
	return res;
}
int Next(int x,int f){//f=1���Һ��,f=0����ǰ�� 
	int p=getv(x);
	splay(p,0);
	int u=root;
	if((tree[u].val>x and f)or(tree[u].val<x and !f))return u;
	u=tree[u].ch[f];
	while(tree[u].ch[f^1])u=tree[u].ch[f^1];
	return u;
}
void Delete(int x){
	int last=Next(x,0),next=Next(x,1);//����ǰ������
	splay(last,0);
	splay(next,last);
	int del=tree[next].ch[0];//��ʱxΪ��̵�Ψһ�ӽڵ㣬��Ϊ���ӽڵ� 
	if(tree[del].cnt>1){
		tree[del].cnt--;
		splay(del,0);
	}
	else tree[next].ch[0]=0;
}
int K_th(int x){//���Ҵ�С�����x�����ı�� 
	int u=root;
	if(tree[u].size<x)return false;
	while(u){
		if(x>tree[tree[u].ch[0]].size+tree[u].cnt){
			x-=tree[tree[u].ch[0]].size+tree[u].cnt;
			u=tree[u].ch[1];
		}
		else if(tree[tree[u].ch[0]].size>=x)u=tree[u].ch[0];
		else return u;
	}
	return -1;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	Inster(-INF);
	Inster(INF);
	read(n);
	while(n--){
		read(opt,x);
		if(opt==1)Inster(x);
		else if(opt==2)Delete(x);
		else if(opt==3){
			int p=getv(x);
			splay(p,0);
			write(tree[tree[root].ch[0]].size);
		}
		else if(opt==4)write(tree[K_th(x+1)].val);//+1����Ϊ�ڱ� 
		else if(opt==5)write(tree[Next(x,0)].val);
		else if(opt==6)write(tree[Next(x,1)].val);
		if(opt>=3)LF;
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
�����ʽ
*/ 
