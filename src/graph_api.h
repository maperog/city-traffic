/* graph_api.h - Abstract graph-building API
 *
 * Copyright 2021 "Maperog" and contributors
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>
 */
#include<vector>
#include<utility>

#ifndef GRAPH_API_H_INCLUDED
#define GRAPH_API_H_INCLUDED
struct Vertex{ // Add vertex metadata here
    int junction_type;
};
struct EdgeMeta{ // Add edge data here
    int s; // Starting Point
    int t; // Finishing point
    int len; //length
    int quality; // a factor determining vehicle speed
    int ord1; // The order of the edge on the vertex s
    // Since the junction requires the pins and ports to
    // be given in the correct order, the backend should
    // sort the edges according to ord1 and ord2.
    // For the same order value, the edge first added goes
    // first (Use std::stable_sort)

    int ord2; // The order of the edge on the vertex t
};
bool edge_cmp1(Edge x,Edge y){return x.ord1<y.ord1;}
bool edge_cmp2(Edge x,Edge y){return x.ord2<y.ord2;}

void set_nm(int n,int m); // n vertices and m edges
void setup_vertex(Vertex mt); // Set up a vertex with vertex metadata my
int add_edg(Edge mt); //add undirected edge between s and t with edge metadata mt, returns edge id
//int fix_id(int id); //get the canonical edge id
Edge get_edg_by_id(int id); // Get edge data by ID
const std::vector<int>&list_edg(int s); // List edges by starting point
const int*c_list_edg(int s){ // List edges by starting point (C-style array) Terminating with -1
    std::vector<int> v=list_edg(s);
    int *arr=new int[v.size()+1];
    std::copy(v.begin(),v.end(),arr);
    arr[v.size()]=-1;
    return arr;
}

// For GUI
int get_canvas_x();
int get_canvas_y(); // Canvas size
std::pair<int,int>recommend_coord(int p); // return recommended coordinate of point p
long long int c_recommend_coord(int p){
    std::pair<int,int>r=recommend_coord(p);
    return (r.first<<32)&r.second;
}
#endif
