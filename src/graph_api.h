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

#include "road.h" // Highly WIP, caution!

void set_nm(int n,int m); // n vertices and m edges
void set_tl_type(int v,int x); // for vertex v set traffic light type to x
void add_tl_offset(int v,int t); // add offset to the traffic light
int add_edg(int s,int t,Road meta); //add undirected edge between s and t with road data meta, returns edge id
int fix_id(int id); //get the canonical edge id
