/* junction.h - Junction
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

#include <utility>
#include <string>
#include <vector>
#include <queue>

#include "vehicle.h" 

#ifndef ROAD_H_INCLUDED
#define ROAD_H_INCLUDED

const int j_tpps = 100; // Time particles per second // 这就是各自为政的代价
const int j_pass_rate = j_tpps; // j_pass_rate / motor_power = Time for a vehicle to pass the junction

// Traffic light types
const char j_solid = 1; // General
const char j_back = 2; // Turn Back (Unused)
const char j_left = 3; // Turn left
const char j_forward = 4; // Go straight
const char j_right = 5; // Turn right
const char j_walk = 6; // Pedestrian (Unused)
const char j_gate = 7; // Cross or down arrow, used in toll gates (Unused)
// j_gate probably has no practical use, but keeping it 2**n does seem nice

// Traffic light color
const char j_black = 0; // Disabled(Unused)
const char j_red = 1;
const char j_green = 2;
const char j_yellow = 3; // (Unused)

struct JDemand{ // A vehicle in a junction
    Vehicle*v;
    int port;
};

struct JLightStatus{ // Traffic light status
    char color; // Color
    int countdown; // Countdown(in time particle) 
    // -1 = No countdown
    // Countdown should always be set to non-(-1)
    // s long as it's scheduled to change
    // No matter if the countdown is displayed

    bool safety; // safety override, enforcing red light.
};

class Junction{ // Base Junction, TODO
protected:
    int n; // Number of pins/ports
    std::vector<std::queue<JDemand> > pins, ports; // Queues of pin/port
    std::vector<std::map<char, JLightStatus> > lights; // Lights (Assuming that for each pin all lights are of distinct types)

    // Get the new state of a traffic light after time t
    JLightStatus light_addtime(JLightStatus x, int t);
    virtual int get_critical(int maxt); // Get the critical time to interrupt simulation, usually when the countdown is over, within timespan maxt.
    virtual void setup_tl(); //set up traffic lights

    // Check whether the vehicles would run into each other in the current configuration
    // and set up safety overrides to avoid collision.
    virtual void safety_check(); 
public:
    void toggle_light(int t); // Toggle the light after t of countdown (Immediately if t=0)
    void addtime(int t); // Shift the Junction by time t
    void setup(int n); //Set up pins and ports and traffic lights
    Junction():n(0),pins(),ports(),lights(){}
    Junction(int n):n(n),pins(),ports(),lights(){
        setup(n);
    }
};

#endif


