int head[N],cnt;
struct nood{
	int nex,to,w;
}edge[M];
void add(int x,int y,int l){
	edge[cnt].nex=head[x];
	edge[cnt].to=y;
	edge[cnt].w=l;
	head[x]=++cnt;
}
void init(){
	memset(head,-1,sizeof head);
}
for(int i=heaad[u];~i;i=edge[i].nex){
	int v=edge[i].to,w=edge[i].w;
}
