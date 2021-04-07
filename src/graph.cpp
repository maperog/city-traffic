#include"graph.h"
#if false
Graph::Graph(int n){
    for(int i=0;i<n;i++)v.push_back(Vertex());
    for(int i=0;i<n;i++)eindex.push_back(std::vector<int>());
    for(int i=0;i<n;i++){
		std::vector<int>ve,ve2;
		for(int j=1;j<=n;j++){
			ve.push_back(0x3fffffff);
		    ve2.push_back(-1);
        }
        floyd_dist.push_back(ve);
		floyd_next.push_back(ve2);
    }
}
void Graph::set_vertex(int p,Vertex data){
    assert(0<=p&&p<=n);
    v[p]=data;
}
void Graph::finish_edg(){
	int m=e.size();

	//Calculate shortest path
	for(int i=0;i<m;i++){
		int x,y;
		x=e[i].s;y=e[i].t;
		if(e[i].len<floyd_dist[x][y]){
			floyd_dist[x][y]=e[i].len;
			floyd_next[x][y]=y;
		}
	}
	for(int k=0;k<n;k++)for(int i=0;i<n;i++){
		if(floyd_dist[i][k]<0x3fffffff){ //a hack that could be of some use
			for(int j=0;j<n;j++){
				if(floyd_dist[i][j]>floyd_dist[i][k]+floyd_dist[k][j]){
				floyd_dist[i][j]=floyd_dist[i][k]+floyd_dist[k][j];
				floyd_next[i][j]=floyd_next[i][k];
				}
			}
		}
	}
}
const std::vector<int>&Graph::list_edg(int s){
    assert(0<=s&&s<=n);
    return eindex[s];
}
EdgeMeta Graph::get_edg_by_id(int id){
	return e[id];
}
int Graph::get_path(int s,int t){
	return floyd_next[s][t];
}
std::pair<int,int>Graph::get_coord(int p){
	return std::make_pair(v[p].x,v[p].y);
}
#endif
