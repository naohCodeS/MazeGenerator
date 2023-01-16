#include <iostream>
#include <vector>
#include <random>
#include <set>

using namespace std;

enum class KIND{PATH, WALL}; //セルの種類
enum class DIR{F,B,L,R,MAX_DIR}; //forward, back, left, right

using Maze = vector<vector<KIND>>;

struct CORD{
    int x,y;
    bool operator<(const CORD& cord)const {return x*10000+y<cord.x*10000+cord.y;};
    CORD operator+(const CORD& cord) {return {x+cord.x,y+cord.y};}
    CORD operator/(const int div) {return {x/div,y/div};}
}; //座標

CORD act[] = {{-2,0},{2,0},{0,-2},{0,2}}; //動くときは2セルずつ動く

bool canMoveTo(Maze maze, CORD now, DIR dir, int size_x, int size_y){ //dir方向に動けるかどうかを判定する
    CORD moved = now + act[(int)dir];
    if(moved.x < 0 || moved.x >= size_x || moved.y < 0 || moved.y >= size_y) return false;
    if(maze[moved.x][moved.y] == KIND::WALL) return true;
    else return false;
}

bool cantMove(Maze maze, CORD now, int size_x, int size_y){ //どこにも動けない状態かどうかを判定する
    return !canMoveTo(maze, now, DIR::F, size_x, size_y) &&
           !canMoveTo(maze, now, DIR::B, size_x, size_y) &&
           !canMoveTo(maze, now, DIR::L, size_x, size_y) &&
           !canMoveTo(maze, now, DIR::R, size_x, size_y);
}

void moveTo(Maze& maze, CORD *now, DIR dir){//dir方向に動く, maze,nowの書き換えも実行
    CORD moved[2] = {*now+act[(int)dir]/2, *now+act[(int)dir]};
    maze[moved[0].x][moved[0].y] = maze[moved[1].x][moved[1].y] = KIND::PATH;
    *now = moved[1];
}

Maze generateMaze(int size_x, int size_y){
    if(size_x%2==0 || size_y%2==0||size_x<5||size_y<5){
        cout<<"invalid size input"<<endl;
    }
    //初期化
    Maze maze(size_x, vector<KIND>(size_y, KIND::WALL)); //迷路本体
    set<CORD> startCord;//スタート座標の候補
    random_device seed;
    mt19937 gen(seed());
    startCord.insert({1,1});//スタート座標候補を初期化

    while(startCord.size() != 0){  
        //スタート位置の決定
        auto ite = startCord.begin();
        uniform_int_distribution<> startCordRand(0,startCord.size()-1);
        advance(ite, startCordRand(gen));
        CORD now = *ite;

        if(cantMove(maze, now, size_x, size_y)){//動けない場合そのセルをスタート座標候補から除外し、新たにスタートする
            startCord.erase(now);
            continue;
        }
        maze[now.x][now.y] = KIND::PATH;
        while(1){
            if(cantMove(maze, now, size_x, size_y)) break;
            if(startCord.find(now)==startCord.end()) startCord.insert(now);
            uniform_int_distribution<> dirRand(0, (int)DIR::MAX_DIR-1);
            DIR dir = (DIR)dirRand(gen);
            if(!canMoveTo(maze, now, dir, size_x, size_y)) dir = (DIR)(((int)dir+1)%(int)DIR::MAX_DIR);
            else moveTo(maze, &now, dir);
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
