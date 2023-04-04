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
	int ch[2],fa,val,size,cnt;//左右节点，父节点，权值，大小，重复 
}tree[N];
void pushup(int p){
	tree[p].size=tree[tree[p].ch[0]].size+tree[tree[p].ch[1]].size+tree[p].cnt; 
}
void rotate(int x){//子树上旋一步
	 int y=tree[x].fa,z=tree[y].fa,k=tree[y].ch[1]==x;
	 tree[z].ch[tree[z].ch[1]==y]=x;
	 tree[x].fa=z;
	 tree[y].ch[k]=tree[x].ch[k^1];
	 tree[tree[x].ch[k^1]].fa=y;
	 tree[x].ch[k^1]=y;
	 tree[y].fa=x;
	 pushup(x),pushup(y);
}
//在每个操作完成后进行spaly，以保证此树的平衡 
void splay(int x,int k){//x旋转到k下（k=0时转到根节点） 
	while(tree[x].fa!=k){
		int y=tree[x].fa,z=tree[y].fa;
		if(k!=z){
			if((tree[y].ch[1]==x)^(tree[z].ch[1]==y))//Z型
				rotate(x);
			else rotate(y); 
		} 
		rotate(x);
	}
	if(k==0)root=x;
}
void Inster(int x){//插入x 
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
int getv(int v){//查找权值为v的节点的编号
	int u=root,res;
	while(u){
		if(tree[u].val>=v)res=u,u=tree[u].ch[0];//（v可能不存在，故res记录近似值） 
		else u=tree[u].ch[1];
	}
	return res;
}
int Next(int x,int f){//f=1查找后继,f=0查找前驱 
	int p=getv(x);
	splay(p,0);
	int u=root;
	if((tree[u].val>x and f)or(tree[u].val<x and !f))return u;
	u=tree[u].ch[f];
	while(tree[u].ch[f^1])u=tree[u].ch[f^1];
	return u;
}
void Delete(int x){
	int last=Next(x,0),next=Next(x,1);//查找前驱与后继
	splay(last,0);
	splay(next,last);
	int del=tree[next].ch[0];//此时x为后继的唯一子节点，且为左子节点 
	if(tree[del].cnt>1){
		tree[del].cnt--;
		splay(del,0);
	}
	else tree[next].ch[0]=0;
}
int K_th(int x){//查找从小到大第x个数的编号 
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
		else if(opt==4)write(tree[K_th(x+1)].val);//+1是因为哨兵 
		else if(opt==5)write(tree[Next(x,0)].val);
		else if(opt==6)write(tree[Next(x,1)].val);
		if(opt>=3)LF;
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
输入格式
*/ 
