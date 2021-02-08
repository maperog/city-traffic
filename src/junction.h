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

#include "vehicle.h" 

#ifndef ROAD_H_INCLUDED
#define ROAD_H_INCLUDED

const int j_tpps = 100; // Time particles per second // 这就是各自为政的代价
const int j_pass_rate = j_tpps; // j_pass_rate / motor_power = Time for a vehicle to pass the junction

// Traffic light types
const char j_solid = 1; // General
const char j_back = 2; // Turn Back
const char j_left = 3; // Turn left
const char j_forward = 4; // Go straight
const char j_right = 5; // Turn right
const char j_walk = 6; // Pedestrian

// Traffic light color
const char j_red = 1;
const char j_green = 2;
const char j_yellow = 3;

struct JDemand{ // A vehicle in a junction
    Vehicle*v;
    int port;
};

struct JLightStatus{ // Traffic light status
    char color; // Color
    int countdown; // Countdown(in time particle) 
    // -1 = No countdown
    // Countdown should always be set to non-(-1) except
    // in manual control,
    // even when it's not shown. See countdown_vis

    bool countdown_vis; // Whether countdown is visible
};

class Junction{ // Base Junction, TODO
    std::string name;
};

#endif


