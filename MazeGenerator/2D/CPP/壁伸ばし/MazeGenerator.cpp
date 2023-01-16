#include <iostream>
#include <vector>
#include <random>
#include <set>

using namespace std;

enum class KIND{PATH, WALL}; //セルの種類
enum class DIR{F,B,L,R}; //forward, back, left, right

using Maze = vector<vector<KIND>>;

struct CORD{
    int x,y;
    bool operator<(const CORD& cord)const {return x*10000+y<cord.x*10000+cord.y;};
}; //座標

CORD act[] = {{-2,0},{2,0},{0,-2},{0,2}}; //動くときは2セルずつ動く

Maze generateMaze(int size_x, int size_y){
    if(size_x%2==0 || size_y%2==0||size_x<5||size_y<5){
        cout<<"invalid size input"<<endl;
    }
    //初期化
    Maze maze(size_x, vector<KIND>(size_y, KIND::PATH)); //迷路本体
    vector<CORD> wallStock; //wallStock[i]はi番目のセルに到達するまでに通った道のり
    set<CORD> isCurrentWall; //現在拡張中の壁
    set<CORD> startCord;//スタート座標の候補
    random_device seed;
    mt19937 gen(seed());
    for(int x=0; x<size_x; x++) maze[x][0] = maze[x][size_y-1] = KIND::WALL; //外側を壁で囲う
    for(int y=0; y<size_y; y++) maze[0][y] = maze[size_x-1][y] = KIND::WALL;
    for(int x=2; x<size_x-1; x+=2) for(int y=2; y<size_y-1; y+=2) { //スタート座標候補を初期化
        CORD cord = {x,y}; 
        startCord.insert(cord);
    }

    while(startCord.size() != 0){
        //ループごとの初期化
        wallStock.clear();
        isCurrentWall.clear();
        auto ite = startCord.begin();
        uniform_int_distribution<> startCordRand(0,startCord.size()-1);
        advance(ite, startCordRand(gen));
        CORD now = *ite;
        maze[now.x][now.y] = KIND::WALL;
        while(1){
            wallStock.push_back(now);
            isCurrentWall.insert(now);
            if(startCord.find(now)!=startCord.end()) startCord.erase(now);
            uniform_int_distribution<> dirRand(0, sizeof(DIR)-1);
            DIR dir = (DIR)dirRand(gen);
            if(dir == DIR::F){
                CORD new_cord = {now.x+act[(int)DIR::F].x, now.y+act[(int)DIR::F].y};
                if(isCurrentWall.find(new_cord)!=isCurrentWall.end()) dir = DIR::B; //進む先が伸ばしている壁だった時->方向を変える
                else {
                    if(maze[new_cord.x][new_cord.y] == KIND::WALL) {//伸ばしていない壁に当たった場合接続してループを終了
                        maze[now.x+act[(int)DIR::F].x/2][now.y+act[(int)DIR::F].y/2] = KIND::WALL;
                        break;
                    }
                    maze[now.x+act[(int)DIR::F].x/2][now.y+act[(int)DIR::F].y/2] = maze[new_cord.x][new_cord.y] = KIND::WALL; //壁を伸ばす
                    now = new_cord;
                }
            }
            if(dir == DIR::B){
                CORD new_cord = {now.x+act[(int)DIR::B].x, now.y+act[(int)DIR::B].y};
                if(isCurrentWall.find(new_cord)!=isCurrentWall.end()) dir = DIR::L; //進む先が伸ばしている壁だった時->方向を変える 
                else {
                    if(maze[new_cord.x][new_cord.y] == KIND::WALL) {//伸ばしていない壁に当たった場合接続してループを終了
                        maze[now.x+act[(int)DIR::B].x/2][now.y+act[(int)DIR::B].y/2] = KIND::WALL;
                        break;
                    }
                    maze[now.x+act[(int)DIR::B].x/2][now.y+act[(int)DIR::B].y/2] = maze[new_cord.x][new_cord.y] = KIND::WALL; //壁を伸ばす
                    now = new_cord;
                }
            }
            if(dir == DIR::L){
                CORD new_cord = {now.x+act[(int)DIR::L].x, now.y+act[(int)DIR::L].y};
                if(isCurrentWall.find(new_cord)!=isCurrentWall.end()) dir = DIR::R; //進む先が伸ばしている壁だった時->方向を変える
                else {
                    if(maze[new_cord.x][new_cord.y] == KIND::WALL) {//伸ばしていない壁に当たった場合接続してループを終了
                        maze[now.x+act[(int)DIR::L].x/2][now.y+act[(int)DIR::L].y/2] = KIND::WALL;
                        break;
                    }
                    maze[now.x+act[(int)DIR::L].x/2][now.y+act[(int)DIR::L].y/2] = maze[new_cord.x][new_cord.y] = KIND::WALL; //壁を伸ばす
                    now = new_cord;
                }
            }
            if(dir == DIR::R){
                CORD new_cord = {now.x+act[(int)DIR::R].x, now.y+act[(int)DIR::R].y};
                if(isCurrentWall.find(new_cord)!=isCurrentWall.end()){ //進む先が伸ばしている壁だった時->方向を変えない
                    if(wallStock.size()<=2) break; //もう戻れないとき
                    else {
                        wallStock.pop_back();
                        wallStock.pop_back();
                        now = wallStock.back(); //ひとつ前に戻る
                    }
                }
                else {
                    if(maze[new_cord.x][new_cord.y] == KIND::WALL) {//伸ばしていない壁に当たった場合接続してループを終了
                        maze[now.x+act[(int)DIR::R].x/2][now.y+act[(int)DIR::R].y/2] = KIND::WALL;
                        break;
                    }
                    maze[now.x+act[(int)DIR::R].x/2][now.y+act[(int)DIR::R].y/2] = maze[new_cord.x][new_cord.y] = KIND::WALL; //壁を伸ばす
                    now = new_cord;
                }
            }
        }
    }

    return maze;
}

int main(int argc, char* args[]){
    Maze maze = generateMaze(atoi(args[1]), atoi(args[2]));
    for(int i=0; i<atoi(args[1]); i++){
        for(int j=0; j<atoi(args[2]); j++)
            cout<<(maze[i][j]==KIND::WALL?"# ":"  ");
        cout<<endl;
    }
}