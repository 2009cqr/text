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
int vis[N],dis[N],n,a[1010][1010];
int prime(int root){
	int ans=0;
	memset(dis,INF,sizeof dis);
	dis[root]=0;
	rep(i,1,n){
		int u,minn=INF;
		rep(j,1,n){
			if(!vis[j] and dis[j]<minn){
				minn=dis[j];
				u=j;
			}
		}
		vis[u]=1;
		ans+=minn;
		rep(v,1,n){
			if(!vis[v])dis[v]=min(dis[v],a[u][v]);
		}
	}
	return ans;
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n);
	rep(i,1,n){
		rep(j,1,n)read(a[i][j]);
	}
	write(prime(1));
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}

