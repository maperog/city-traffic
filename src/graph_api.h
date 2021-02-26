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

#ifndef GRAPH_API_H_INCLUDED
#define GRAPH_API_H_INCLUDED
struct VertexMeta{ // Add vertex metadata here
    int junction_type;
};
struct EdgeMeta{ // Add edge metadata here
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
bool edge_meta_cmp1(EdgeMeta x,EdgeMeta y){return x.ord1<y.ord1;}
bool edge_meta_cmp2(EdgeMeta x,EdgeMeta y){return x.ord2<y.ord2;}

void set_nm(int n,int m); // n vertices and m edges
void setup_vertex(VertexMeta mt); // Set up a vertex with vertex metadata my
int add_edg(int s,int t,EdgeMeta mt); //add undirected edge between s and t with edge metadata mt, returns edge id
//int fix_id(int id); //get the canonical edge id
#endif
