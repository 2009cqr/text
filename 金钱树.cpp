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
ll head[N],cnt,c[N],root,n,m,a[N],tot,l[N],r[N],op,x,y,k;
struct Node{
	int to,nex;
}edge[N*2];
void add(ll a,ll b){
	edge[cnt].to=b;
	edge[cnt].nex=head[a];
	head[a]=cnt++;
}
ll lowbit(ll x){return x&(-x);}
void addition(ll x,ll k){
	for(ll i=x;i<=n;i+=lowbit(i))c[i]+=k;
}
ll getsum(int x){
	ll sum=0;
	for(ll i=x;i;i-=lowbit(i))sum+=c[i];
	return sum;
}
void DFS(ll u,ll father){
	l[u]=++tot;
	addition(tot,a[u]);
	for(int i=head[u];~i;i=edge[i].nex){
		int v=edge[i].to;
		if(v!=father)DFS(v,u);
	}
	r[u]=tot;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	memset(head,-1,sizeof head);
	read(n,m,root);
	rep(i,1,n)read(a[i]);
	rep(i,1,n-1){
		read(x,y);
		add(x,y),add(y,x);
	}
	DFS(root,0);
	while(m--){
		read(op);
		if(op==1){
			read(x,k);
			addition(l[x],k);
		}
		else{
			read(x);
			write(getsum(r[x])-getsum(l[x]-1));
			LF;
		}
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}

