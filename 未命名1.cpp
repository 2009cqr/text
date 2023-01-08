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
int n,m,maxx,minn=INF,a[N],sum,pow9[10]={0,9,81,729,6561,59049,531441,4782969,43046721,387420489};
int mod_10(int x){
	return (x%10+10)%10;
} 
void dfs(int k,int pos,int v){
	if(v>=minn&&v*pow9[m-k]<=maxx)return;
	sum=0;
	if(k==m){
		rep(i,pos,n)sum+=a[i];
		maxx=max(maxx,v*mod_10(sum));
		minn=min(minn,v*mod_10(sum));
		return;
	} 
	rep(i,pos,n-m+k){
		sum+=a[i];
		dfs(k+1,i+1,v*mod_10(sum));
	}
	
}
signed main(){
//	freopen(".in","r",stdin);
//	freopen(".out","w",stdout);
	read(n,m);
	rep(i,1,n){
		read(a[i]);
		a[i+n]=a[i];
	}
	rep(i,1,n){
		dfs(1,1,1);
		rep(j,1,2*n)a[j]=a[j+1];
	}
	write(minn);
	LF;
	write(maxx);
//	fclose(stdin);
//	fclose(stdout);
	return 0;
}

