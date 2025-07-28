# project
Gigagenine 분할 예정 -> Game Scene, Scene Manager
오브젝트 추상클래스 + 템플릿 


Game Scene
Update
Render
std::vector<Map> maps;
std::shared_ptr<Player> player;
int palyersize = 64;
addMap
addObjectToCurrentMap
addPlayer
addPortal
GetMapIndexByName

Scene Manager
HasMaps
currentMap
ChangeMap
int currentMapIndex = 0;




