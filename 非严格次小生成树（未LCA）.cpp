#include<bits/stdc++.h>
using namespace std;
#define LF putchar('\n')
#define SP putchar(' ')
#define rep(i,a,b) for(register int i=(a);i<=(b);++i)
#define repp(i,a,b) for(register int i=(a);i>=(b);i--)
#define pair<int,int> pill
#define mem(t, v) memset((t),v,sizeof(t))
#define fir first
#define sec second
#define mk make_pair
#define INF 0x3f3f3f3f
#define LINF 0x3f3f3f3f3f3f3f3f
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
const ll MOD=1e9+7,N=1e6+10;
int n,m,f[N],Max_dis[1010][1010],cnt,head[2*N];
ll sum,ans=LINF;
struct Node{
	int x,y,w,flag;
}node[N];
struct G{
	int firs,nex,w;
}edge[2*N];
void add(int a,int b,int w){
	edge[cnt].firs=b;
	edge[cnt].w=w;
	edge[cnt].nex=head[a];
	head[a]=cnt++;
}
bool cmp(Node a,Node b){
	return a.w<b.w;
}
int Find(int x){
	if(x==f[x])return x;
	return f[x]=Find(f[x]);
}
void init(){
	rep(i,1,n)f[i]=i;
	memset(head,-1,sizeof head);
}
void kruskal(){
	init();
	sort(node+1,node+1+m,cmp);
	rep(i,1,m){
		int xx=Find(node[i].x),yy=Find(node[i].y);
		if(xx!=yy){
			f[xx]=yy;
			sum+=node[i].w;
			node[i].flag=1;
			add(node[i].x,node[i].y,node[i].w);
			add(node[i].y,node[i].x,node[i].w);
		}
	}
}
void DFS(int s,int u,int father,int maxx){
	Max_dis[s][u]=maxx;
	for(int i=head[u];~i;i=edge[i].nex){
		int v=edge[i].firs;
		if(v!=father){
			if(edge[i].w>maxx)DFS(s,v,u,edge[i].w);
			else DFS(s,v,u,maxx);
		}
	}
} 
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,m);
	rep(i,1,m)read(node[i].x,node[i].y,node[i].w);
	kruskal();
	rep(i,1,n)DFS(i,i,-1,-INF);
	rep(i,1,m){
		if(node[i].flag==0)ans=min(ans,sum-Max_dis[node[i].x][node[i].y]+node[i].w);
	}
	write(ans);
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
