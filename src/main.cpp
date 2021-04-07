/* sims.cpp - Vehicle Movement Simulation
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


#include"vehicle.h"
#include"graph.h"
#include<vector>
#include<algorithm>
#include<ctime>
#include<random>
#include<cmath>
#include<stack>
#include<map>
#include<iostream>
using std::vector;

std::mt19937 gen(time(0)), gen2(time(0));
std::uniform_real_distribution<> dis(0.00, 100.00);
std::vector<std::pair<int,int> > arriving_times;
int rand_x(int, int);
double fun_S(double);
double move_pend(int, double, double);
using std::cin;
using std::cout;
using std::endl;

struct SIM_vehicle_component // a combination of vehicle and additional fields
{
	Vehicle vehicle;
	//int tag_clear; // a field used for identifying whether the vehicle entered a new dot
	int nearest_bypass; // a field used for bypassing-blocking process
	int original_index; // a value storaging the old index of sorted vehicles
	int current_road; // a field indicating the road the vehicle is currently on
	int arrival_time;
	double finished_percent;
	int id;
	std::stack<int>presets;
	int moves(double val)
	{
		finished_percent += val;
		return finished_percent >= 100.00;
	}
	int bypass_success_judge(SIM_vehicle_component tar)
	{
		int val_subject = (this->vehicle).skill_power;
		int val_passive = (tar.vehicle).obstruct_power;
		double possibility = fun_S((val_subject - val_passive) / 60.00) * 100.00;
		if(dis(gen) <= possibility) return 1;
		else return 0;
	}
};
SIM_vehicle_component SIM_vehicle_convert(Vehicle, int);

struct SIM_query // used as simulation's parameter
{
	vector <Vehicle> vehicle_list;
	Graph G;
}query;

bool SIM_vehicle_cmp(SIM_vehicle_component a, SIM_vehicle_component b) // used for bypassing-blocking process
{
	return a.finished_percent < b.finished_percent;
}

void init();

vector <SIM_vehicle_component> vehicle_onroad, vehicle_ondot, vehicle_enterdot, vehicle_tmplist;
vector <Edge> tmpEdges;

int simulation()
{
	int current_time=0;
	int is_end=0;
	
	while(!vehicle_onroad.empty()) vehicle_onroad.pop_back();
	while(!vehicle_ondot.empty()) vehicle_ondot.pop_back();
	while(!vehicle_enterdot.empty()) vehicle_enterdot.pop_back();
	/* vehicle list vehicle_onroad, vehicle_ondot, vehicle_enterdot
		clear list1,2,4 */
	
	for(int i = 0; i < query.vehicle_list.size(); ++i)
		vehicle_ondot.push_back(SIM_vehicle_convert(query.vehicle_list[i], i));
	/* for each vehicle
		 add to list2 */
	init();
	while(!is_end)
	{
		/*
		{
			cout<<"Time tick "<<current_time<<":\n";
			cout<<"onroad :";
			for(int i = 0; i < vehicle_onroad.size(); ++i)
			{
				cout<<"("<<vehicle_onroad[i].id<<", "<<vehicle_onroad[i].current_road<<", "
					<<vehicle_onroad[i].vehicle.current_point<<", "
					<<vehicle_onroad[i].finished_percent<<") ";
			}
			cout<<endl;
			cout<<"ondot :";
			for(int i = 0; i < vehicle_ondot.size(); ++i)
			{
				cout<<"("<<vehicle_ondot[i].id<<", "<<vehicle_ondot[i].current_road<<", "
					<<vehicle_ondot[i].vehicle.current_point<<", "
					<<vehicle_ondot[i].finished_percent<<") ";
			}
			cout<<endl;
			cout<<"enterdot :";
			for(int i = 0; i < vehicle_enterdot.size(); ++i)
			{
				cout<<"("<<vehicle_enterdot[i].id<<", "<<vehicle_enterdot[i].current_road<<", "
					<<vehicle_enterdot[i].vehicle.current_point<<", "
					<<vehicle_enterdot[i].finished_percent<<") ";
			}
			cout<<endl;
		}
		*/
		
		if(vehicle_onroad.size() > 0)
		{
			random_shuffle(vehicle_onroad.begin(), vehicle_onroad.end());
		}
		for(unsigned int i = 0; i < vehicle_onroad.size(); ++i)
			vehicle_onroad[i].original_index = i;
		
		for(unsigned int i = 0; i < vehicle_onroad.size(); ++i)
		{
			vehicle_tmplist.clear();
			int index;
			int tmp_flag = -1;
			double movement;
			
			for(unsigned int j = 0; j < vehicle_onroad.size(); ++j)
			{
				if(vehicle_onroad[i].current_road == vehicle_onroad[j].current_road)
					vehicle_tmplist.push_back(vehicle_onroad[j]);
				if(j == i)index = vehicle_tmplist.size() - 1;
			}
			sort(vehicle_tmplist.begin(),vehicle_tmplist.end(),SIM_vehicle_cmp);
			movement = move_pend(vehicle_onroad[i].vehicle.motor_power, 
						query.G.get_edg_by_id(vehicle_onroad[i].current_road).quality,
						query.G.get_edg_by_id(vehicle_onroad[i].current_road).len)
						/ query.G.get_edg_by_id(vehicle_onroad[i].current_road).len;
			
			for(unsigned int j = index + 1; j < vehicle_tmplist.size(); ++j)
			{
				int j2 = vehicle_tmplist[j].original_index;
				if(vehicle_onroad[j2].finished_percent < 100.00 && 
				vehicle_onroad[i].finished_percent + movement > vehicle_onroad[j2].finished_percent)
				{
					if( (!vehicle_onroad[i].bypass_success_judge(vehicle_onroad[j2])) || 
						vehicle_onroad[i].nearest_bypass == j2)
					{
						movement = move_pend(vehicle_onroad[i].vehicle.motor_power, 
									query.G.get_edg_by_id(vehicle_onroad[i].current_road).quality, 
									query.G.get_edg_by_id(vehicle_onroad[i].current_road).len * vehicle_onroad[j2].finished_percent)
									/ query.G.get_edg_by_id(vehicle_onroad[i].current_road).len;
						vehicle_onroad[i].moves(movement);
						goto out;
					}
				}
			}
			if(tmp_flag == -1)
			{
				tmp_flag = vehicle_onroad[i].moves(movement);
				if(tmp_flag == 1)
				{
					for(unsigned int j = index + 1; j < vehicle_tmplist.size(); ++j)
						vehicle_onroad[vehicle_tmplist[j].original_index].nearest_bypass = -1;
					
					vehicle_onroad[i].vehicle.current_point = query.G.get_edg_by_id(vehicle_onroad[i].current_road).t;
					vehicle_enterdot.push_back(vehicle_onroad[i]);
					vehicle_onroad.erase(vehicle_onroad.begin() + i);
					--i;
					for(unsigned int j = 0; j < vehicle_onroad.size(); ++j)
						vehicle_onroad[j].original_index = j;
					goto out;
				}
			}
			for(unsigned int j = index + 1; j < vehicle_tmplist.size(); ++j)
			{
				int old_index = vehicle_tmplist[j].original_index;
				vehicle_onroad[old_index].nearest_bypass = i;
			}
			out:;
		}
		/* for each vehicle in list1
			// random move
			// if enterdot
				// add to list4, remove from list1
			// else if intersect
				// pend movement success
				// tag bypassed vehicles by number
			// else
				// adjust vehicle
				*/
		
		
		for(unsigned int i = 0; i < vehicle_enterdot.size(); ++i)
		{
			if(vehicle_enterdot[i].vehicle.current_point ==
				vehicle_enterdot[i].vehicle.end_point)
			{
				arriving_times.push_back(std::make_pair(vehicle_enterdot[i].vehicle.start_time, current_time));
			}
			else
			{
				vehicle_enterdot[i].arrival_time = current_time;
				vehicle_ondot.push_back(vehicle_enterdot[i]);
			}
			vehicle_enterdot.erase(vehicle_enterdot.begin() + i);
			--i;
		}
		for(unsigned int i = 0; i < vehicle_ondot.size(); ++i)
		{
			//cout<<dis(gen)<<" "<<vehicle_ondot[i].arrival_time<<" "<<vehicle_ondot[i].vehicle.start_time<<" "<<current_time<<" ***"<<endl;
			if(dis(gen) <= 100.00 * fun_S(current_time - vehicle_ondot[i].arrival_time) &&
				vehicle_ondot[i].vehicle.start_time <= current_time)
			{
				vehicle_ondot[i].finished_percent = 0.00;
				int nxt = vehicle_ondot[i].presets.top();
				vehicle_ondot[i].presets.pop();
				int cur = vehicle_ondot[i].vehicle.current_point;
				int res = 0;
				for(unsigned int j = 0; j < tmpEdges.size(); ++j)
				{
					if(tmpEdges[j].s == cur && tmpEdges[j].t == nxt)
						res = j;
				}
				vehicle_ondot[i].current_road = res;
				vehicle_onroad.push_back(vehicle_ondot[i]);
				vehicle_ondot.erase(vehicle_ondot.begin() + i);
				--i;
			}
		}
		// for each vehicle in list4
			// if vehicle finished
				// note, delete
			//else
				// add to list2
		// for each vehicle in list2
			// if continue
				// add to list1
		++current_time;
		if(vehicle_onroad.size() == 0 && vehicle_ondot.size() == 0)is_end = 1;
		// if all lists are empty
			// set end to 1
	}
	return current_time;
}

SIM_vehicle_component SIM_vehicle_convert(Vehicle vehicle,int x)
{
	SIM_vehicle_component res;
	res.vehicle = vehicle;
	res.original_index = -1;
	res.nearest_bypass = -1;
	res.arrival_time = 0;
	res.current_road = -1;
	res.id = x;
	return res;
}

int rand_x(int minimum = 0, int maximum = 127)
{
	srand(clock());
	int res, div, delta;
	do
	{
		res = rand();
		delta = maximum - minimum + 1;
		div = RAND_MAX - (RAND_MAX % delta);
	}
	while(res >= div);
	return res % delta;
}

double fun_S(double x)
{
	return (exp(x))/(exp(x)+exp(-x));
}

double move_pend(int power, double roadbuff, double maxlimit)
{
	//an 1 power moves on a 1.0 roadbuff road should have the max probability to move 1 unit length on the road
	double valA = 0.00, valB = 0.00, mu = 0, sigma = 0;
	valA = 0.7 * pow(power, 0.8) + 0.3 * sin(power + 3.6) + 0.559903995;
	valB = 1.5 * log(roadbuff + 1);
	mu = valA * valB * maxlimit / 100.00;
	sigma = std::min(mu / 3.0, fun_S(roadbuff * (-0.25)));
	std::normal_distribution<> valR{mu, sigma};
	return std::max(0.00, valR(gen2));
}

int n, V, E;
void input()
{
	// n V E
	// n vehicles:
	// each vehicle: motor_power skill_power obstruct_power start_time s t
	// V vertexies
	// id from 1 to V
	// E roads
	// each road: s t quality length (as directed edges)
	cin>>n>>V>>E;
	Vehicle tmp;
	Edge tmpE;
	for(int i = 1; i <= n; ++i)
	{
		int a, b, c, d, e, f;
		cin>>a>>b>>c>>d>>e>>f;
		tmp.motor_power = a;
		tmp.skill_power = b;
		tmp.obstruct_power = c;
		tmp.start_time = d;
		tmp.start_point = e;
		tmp.end_point = f;
		tmp.current_point = e;
		query.vehicle_list.push_back(tmp);
	}
	for(int i = 1; i <= E; ++i)
	{
		int a, b;
		double c, d;
		cin>>a>>b>>c>>d;
		tmpE.s = a;
		tmpE.t = b;
		tmpE.quality = c;
		tmpE.len = d;
		query.G.add_edg(tmpE);
		tmpEdges.push_back(tmpE);
	}
}

double floyd[55][55];
int f_from[55][55];
void init()
{
	for(int i = 1; i <= V; ++i)
		for(int j = 1; j <= V; ++j)
		{
			floyd[i][j] = 1e60;
			f_from[i][j] = -1;
		}
	for(int i = 1; i <= V; ++i)
	{
		floyd[i][i] = 0;
		f_from[i][i] = i;
	}
	
	for(int a = 0; a < n; ++a)
	{
		for(int i = 0; i < E; ++i)
		{
			int a, b;
			Edge tmpE = query.G.get_edg_by_id(i);
			a = tmpE.s;
			b = tmpE.t;
			double c = move_pend(vehicle_ondot[a].vehicle.motor_power, tmpE.quality, tmpE.len);
			floyd[a][b] = c;
			f_from[a][b] = a;
		}
		for(int i = 1; i <= V; ++i)
		{
			for(int j = 1; j <= V; ++j)
			{
				if(i == j)continue;
				for(int k = 1; k <= V; ++k)
				{
					if(floyd[i][j] > floyd[i][k] + floyd[k][j])
					{
						floyd[i][j] = floyd[i][k] + floyd[k][j];
						f_from[i][j] = k;
					}
				}
			}
		}
		/*
		for(int i = 1; i <= V; ++i,cout<<endl)
			for(int j = 1; j <= V; ++j)
				cout<<floyd[i][j]<<" ";
		cout<<endl;
		for(int i = 1; i <= V; ++i,cout<<endl)
			for(int j = 1; j <= V; ++j)
				cout<<f_from[i][j]<<" ";
		*/
		int now = vehicle_ondot[a].vehicle.end_point, s = vehicle_ondot[a].vehicle.start_point;
		while(now != s)
		{
			//cout<<now<<" "<<s<<endl;
			vehicle_ondot[a].presets.push(now);
			now = f_from[s][now];
			
		}
	}
}

int main()
{
	srand(time(0));
	cout<<dis(gen)<<endl;
	input();
	int res = simulation();
	cout<<res<<endl;
	for(int i = 0; i < n ; ++i)
	{
		cout<<arriving_times[i].first<<" "<<arriving_times[i].second<<endl;
	}
	return 0;
}

/*
2 2 1
1500 5 3 3 1 2
500 3 300 2 1 2
1 2 3 10
*/
