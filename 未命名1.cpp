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
int n,m,f[3*N],x,y,flag,op,ans;
int Find(int x){
	if(f[x]==x)return x;
	return f[x]=Find(f[x]);
}
void U(int x,int y){
	int xx=Find(x),yy=Find(y);
	f[xx]=f[yy];
}
void init(){
	rep(i,1,3*n)f[i]=i;//1~n其本身 n+1~2n其猎物 2n+1~3n其天敌 
	flag=0;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,m);
	init();
	while(m--){
		read(op,x,y);
		if(x>n or y>n)ans++;
		else if(op==1){
			if(Find(x+n)==Find(y) or Find(x+2*n)==Find(y))ans++;
			else U(x,y),U(x+n,y+n),U(x+2*n,y+2*n);
		}
		else if(op==2){
			if(Find(x)==Find(y) or Find(x+2*n)==Find(y))ans++;
			else U(x+n,y),U(x,y+2*n),U(x+2*n,y+n);
		} 
	}
	write(ans);
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}

