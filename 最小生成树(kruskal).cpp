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
int n,m,f[N],ans,sum;
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
void kruskal(){
	sort(node+1,node+1+m,cmp);
	rep(i,1,m){
		int xx=Find(node[i].x),yy=Find(node[i].y);
		if(xx!=yy){
			f[xx]=f[yy];
			sum+=node[i].w;
			ans++;
			if(ans==n-1)return;
		}
	}
	sum=-1;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,m);
	rep(i,1,n)f[i]=i;//记得初始化，警钟长鸣
	rep(i,1,m)read(node[i].x,node[i].y,node[i].w);
	kruskal();
	if(sum==-1)printf("-1");
	else printf("%d",sum);
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
