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
int n,f[N],sum,num[N],t;
struct Node{
	int x,y,w;
}node[N];
bool cmp(Node a,Node b){
	return a.w<b.w;
}
int Find(int x){
	if(x==f[x])return x;
	return f[x]=Find(f[x]);
}
void U(int x,int y){
	int xx=Find(x),yy=Find(y);
	f[xx]=f[yy];
	num[yy]+=num[xx];
}
void init(){
	rep(i,1,n){
		f[i]=i;
		num[i]=1;
	}
	sum=0;
}
int kruskal(){
	sort(node+1,node+n,cmp);
	rep(i,1,n-1){
		int xx=Find(node[i].x),yy=Find(node[i].y);
		sum+=(num[xx]*num[yy]-1)*(node[i].w+1);
		U(node[i].x,node[i].y);
	}
	return sum;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(t);
	while(t--){
		read(n);
		init();
		rep(i,1,n-1)read(node[i].x,node[i].y,node[i].w);
		write(kruskal());
		LF;
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}

