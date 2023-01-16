#include <iostream>
#include <vector>
#include <random>
#include <set>

using namespace std;

enum class KIND{PATH, WALL}; //セルの種類
enum class DIR{F,B,L,R,U,D,SIZE}; //forward, back, left, right

using Maze = vector<vector<vector<KIND>>>;

struct CORD{
    int x,y,z;
    bool operator<(const CORD& cord)const {return x*1000000+y*1000+z<cord.x*1000000+cord.y*1000+cord.z;};
    CORD operator+(const CORD& cord) {return {x+cord.x,y+cord.y,z+cord.z};}
    CORD operator/(const int div) {return {x/div,y/div,z/div};}
}; //座標

CORD act[] = {{-2,0,0},{2,0,0},{0,-2,0},{0,2,0},{0,0,-2},{0,0,2}}; //動くときは2セルずつ動く

bool canMoveTo(Maze maze, CORD now, DIR dir, int size_x, int size_y, int size_z){ //dir方向に動けるかどうかを判定する
    CORD moved = now + act[(int)dir];
    if(moved.x < 0 || moved.x >= size_x || moved.y < 0 || moved.y >= size_y || moved.z < 0 || moved.z >= size_z) return false;
    if(maze[moved.x][moved.y][moved.z] == KIND::WALL) return true;
    else return false;
}

bool cantMove(Maze maze, CORD now, int size_x, int size_y, int size_z){ //どこにも動けない状態かどうかを判定する
    return !canMoveTo(maze, now, DIR::F, size_x, size_y, size_z) &&
           !canMoveTo(maze, now, DIR::B, size_x, size_y, size_z) &&
           !canMoveTo(maze, now, DIR::L, size_x, size_y, size_z) &&
           !canMoveTo(maze, now, DIR::R, size_x, size_y, size_z) &&
           !canMoveTo(maze, now, DIR::U, size_x, size_y, size_z) &&
           !canMoveTo(maze, now, DIR::D, size_x, size_y, size_z);
}

void moveTo(Maze& maze, CORD *now, DIR dir){//dir方向に動く, maze,nowの書き換えも実行
    CORD moved[2] = {*now+act[(int)dir]/2, *now+act[(int)dir]};
    maze[moved[0].x][moved[0].y][moved[0].z] = maze[moved[1].x][moved[1].y][moved[1].z] = KIND::PATH;
    *now = moved[1];
}

Maze generateMaze(int size_x, int size_y, int size_z){
    if(size_x%2==0 || size_y%2==0|| size_z%2==0 || size_x<5 || size_y<5 || size_z < 5 ){
        cout<<"invalid size input (each side must be odd with at least )"<<endl;
    }
    //初期化
    Maze maze(size_x, vector<vector<KIND>>(size_y, vector<KIND>(size_z, KIND::WALL))); //迷路本体
    set<CORD> startCord;//スタート座標の候補
    random_device seed;
    mt19937 gen(seed());
    startCord.insert({1,1,1});//スタート座標候補を初期化

    while(startCord.size() != 0){
        auto ite = startCord.begin();//スタート位置の決定
        uniform_int_distribution<> startCordRand(0,startCord.size()-1);
        advance(ite, startCordRand(gen));
        CORD now = *ite;

        if(cantMove(maze, now, size_x, size_y, size_z)){//動けない場合そのセルをスタート座標候補から除外し、新たにスタートする
            startCord.erase(now);
            continue;
        }
        maze[now.x][now.y][now.z] = KIND::PATH;
        while(1){
            if(cantMove(maze, now, size_x, size_y, size_z)) break;
            if(startCord.find(now)==startCord.end()) startCord.insert(now);
            uniform_int_distribution<> dirRand(0, (int)DIR::SIZE-1);
            DIR dir = (DIR)dirRand(gen);
            if(!canMoveTo(maze, now, dir, size_x, size_y, size_z)) dir = (DIR)(((int)dir+1)%(int)DIR::SIZE);
            else moveTo(maze, &now, dir);
        }
    }
    return maze;
}

int main(int argc, char* args[]){
    Maze maze = generateMaze(atoi(args[1]), atoi(args[2]), atoi(args[3])); //３次元迷路の生成
    for(int i=0; i<atoi(args[1]); i++){
        cout<<"x = "<<i<<endl;
        for(int j=0; j<atoi(args[2]); j++){
            for(int k=0; k<atoi(args[3]); k++)
                cout<<(maze[i][j][k]==KIND::WALL?"# ":"  ");
            cout<<endl;
        }
        cout<<"--------------------------------"<<endl;
    }
}