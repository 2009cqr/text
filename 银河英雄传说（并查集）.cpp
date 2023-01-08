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
int n,m,f[N],dis[N],num[N],x,y; 
char op[10];
int Find(int x){
	if(f[x]==x)return x;
	int root=Find(f[x]);
	dis[x]+=dis[f[x]];
	return f[x]=root;
}
void U(int x,int y){
	int xx=Find(x),yy=Find(y);
	if(xx!=yy){
		f[xx]=f[yy];
		dis[xx]=num[yy];
		num[yy]+=num[xx];
	}
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	scanf("%d",&m);
	rep(i,1,30000){
		f[i]=i;
		num[i]=1;
	}
	while(m--){
		scanf("%s%d%d",&op,&x,&y);
		if(op[0]=='C'){
			int t1=Find(x),t2=Find(y);
			if(t1==t2)write(max(0,abs(dis[x]-dis[y])-1));
			else write(-1);
			LF;
		}
		else U(x,y);
	}
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}
