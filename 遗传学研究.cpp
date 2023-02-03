#include<bits/stdc++.h>
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
struct nood{
	int to,nex,w;
}edge[N>>1];
int head[N],cnt,tot,root[N],ans[N],p[N],n,t,maxn=1e9;
void add(int a,int b,int x){
	edge[cnt].to=b;
	edge[cnt].w=x;
	edge[cnt].nex=head[a];
	head[a]=cnt++; 
}
void init(){
	cnt=0;
	memset(head,-1,sizeof head);
}
struct Tree{
	int lson,rson,val;
}tree[N*40];
void pushup(int k){
	tree[k].val=tree[tree[k].lson].val+tree[tree[k].rson].val;
}
void update(int &k,int l,int r,int q,int x){
	if(!k)k=++tot;
	if(l==r){
		tree[k].val+=x;
		return;
	}
	int mid=(l+r)>>1;
	if(q<=mid)update(tree[k].lson,l,mid,q,x);
	else update(tree[k].rson,mid+1,r,q,x);
	pushup(k);
}
int Merge(int x,int y,int l,int r){
	if(!x||!y)return x+y;
	if(l==r){
		tree[x].val+=tree[y].val;
		return x;
	}
	int mid=(l+r)>>1;
	tree[x].lson=Merge(tree[x].lson,tree[y].lson,l,mid);
	tree[x].rson=Merge(tree[x].rson,tree[y].rson,mid+1,r);
	pushup(x);
	return x;
}
int query(int k,int l,int r,int x,int y){
	if(x<=l and y>=r)return tree[k].val;
	int mid=(l+r)>>1,sum=0;
	if(x<=mid)sum+=query(tree[k].lson,l,mid,x,y);
	if(y>mid)sum+=query(tree[k].rson,mid+1,r,x,y);
	return sum; 
}
void DFS(int u){
	for(int i=head[u];~i;i=edge[i].nex){
		int v=edge[i].to;
		DFS(v);
		root[u]=Merge(root[u],root[v],1,maxn);
	}
	ans[u]=query(root[u],1,maxn,p[u],maxn)-1;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);
	init();
	rep(i,1,n){
		read(p[i]);
		update(root[i],1,maxn,p[i],1);
	}
	rep(i,2,n){
		read(t);
		add(t,i,1);
	}
	DFS(1);
	rep(i,1,n){
		write(ans[i]);
		LF;
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
//线段树的分裂与合并应用 
