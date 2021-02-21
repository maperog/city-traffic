#include "junction.h"

// Junction
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
void Junction::on_switch(){
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
int Junction::get_critical(int maxt){
    for(int i=0;i<this->n;i++){
        for(
          std::map<char, JLightStatus>::iterator j=lights[i].begin();
          j!=lights[i].end();
          j++){
            if(j->second.countdown>=0){
                maxt = (maxt<=j->second.countdown)?maxt:j->second.countdown;
            }
        }
    }
    return maxt;
}
void Junction::pass_vehicles(int t){
    for(int i=0;i<this->n;i++){
        int curt=t;
        while(curt>=0){
            std::deque<JDemand> buf;
            while(pins[i].size()){
                JDemand x=pins[i].front();
                pins[i].pop_front();
                if(acceptp(i,x.port)&&j_pass_rate<curt*x.v->motor_power){
                    ports[x.port].push_back(x);
                    curt-=j_pass_rate/x.v->motor_power;
                    break;
                }else{
                    buf.push_back(x);
                }
                if(buf.size()>=5)break;
            }
            while(buf.size()){
                pins[i].push_front(buf.front());
                buf.pop_front();
            }
        }
    }
}
void Junction::push_vehicle(Vehicle*v,int pin,int target){
    assert(pin>=0);assert(pin<this->n);
    assert(target>=0);assert(target<this->n);
    pins[pin].push_back(JDemand(v,target));
}
Vehicle* Junction::pop_vehicle(int port){
    assert(port>=0);assert(port<this->n);
    if(!ports[port].size())return((Vehicle*)0);
    JDemand x=ports[port].front();
    ports[port].pop_front();
    return x.v;
}
char Junction::get_light_color(int p,int type){
    return lights[p][type].safety?j_red:lights[p][type].color;
}


// SimpleJunction
void SimpleJunction::setup_tl(){
    for(int i=0;i<n;i++){
        lights[i][j_solid]=JLightStatus(i%2?j_green:j_red,30*j_tpps);
    }
}
bool SimpleJunction::acceptp(int s,int t){
    return lights[s][j_solid].color==j_green||t==(s+1)%n;
}
void SimpleJunction::on_switch(){
    for(int i=0;i<n;i++){
        if(lights[i][j_solid].countdown==-1){
            lights[i][j_solid].countdown=30*j_tpps;
        }
    }
}
