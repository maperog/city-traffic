#include "junction.h"

void Junction::setup(int n){
    this->n = n;
    this->pins=std::vector<std::deque<JDemand> >();
    this->ports=std::vector<std::deque<JDemand> >();
    for(int i=0;i<n;i++){
        pins.push_back(std::deque<JDemand>());
        ports.push_back(std::deque<JDemand>());
    }
    this->lights=std::vector<std::map<char, JLightStatus> >();
    this->setup_tl();
}
void Junction::setup_tl(){
    // Nothing to do in the base class
}
void Junction::safety_check(){
    // We've no time to work on this
}
char get_next_color(char c){return c^3;}
void Junction::add_time(int t){
    while(t>0){
        int ct=get_critical(t);
        int mt=(t>ct?ct:t);
	    this->pass_vehicles(mt);
	    for(int i=0;i<this->n;i++){
            for(
              std::map<char, JLightStatus>::iterator j=lights[i].begin();
              j!=lights[i].end();
              j++){
                if(j->second.countdown>=0)
                j->second.countdown-=mt;
                if(j->second.countdown==0){
                    this->toggle_light(i,j->first,0);
                    on_switch();
                    safety_check();
                }
            }
    	}
    	t-=mt;
    }
}
void Junction::toggle_light(int p,int type,int t){
    if(t){this->lights[p][type].countdown=t;}
    else{
        this->lights[p][type].color=get_next_color(this->lights[p][type].color);
        this->lights[p][type].countdown=-1;
    }
}
bool Junction::acceptp(int s,int t){
    // Trivial for base class
    return true;
}
void Junction::pass_vehicles(int t){
    for(int i=0;i<=this->n;i++){
        
    }
}
