# Marisa的missing列表
sims.h （目前）缺失接口列表：



1. 获取某个 ```vehicle``` 对象所在的 ```road``` 对象的编号
(wycero注:不予实现,这是魔理沙她自己的事)
2. 获取某个 ```vehicle``` 对象的行进能力(Vehicle::motor_power)
3. 获取某个 ```vehicle``` 对象在对应道路上的行进程度
(wycero:不予实现,理由同1)
4. 获取某个 ```vehicle``` 对象的规划行进路线(Graph::get_path)
5. 获取某个 ```vehicle``` 对象的突破能力(Vehicle::skill_power)
6. 获取某个 ```vehicle``` 对象的阻碍通行能力(Vehicle::obstruct_power)
7. 获取某个 ```road``` 对象的可通行程度(Graph::get_edge_by_id, EdgeMeta::quality)
8. 命令某个 ```vehicle``` 进入某条道路(Graph::conduct)
9. 待定



理论上一个 ```graph``` 对象至少由一些 ```road``` 对象和 ```vertex``` 对象构成
