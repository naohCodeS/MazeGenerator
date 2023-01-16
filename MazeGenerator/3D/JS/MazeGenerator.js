const KIND = {
    PATH:0, WALL:1
};
const DIR = {
    F:0,B:1,L:2,R:3,U:4,D:5,SIZE:6
};
class CORD{
    constructor(x,y,z){
        this.x = x;
        this.y = y;
        this.z = z;
    }
    lt(cord){
        return this.x*1000000+this.y*1000+this.z<cord.x*1000000+cord.y*1000+cord.z;
    }
    add(cord){
        return new CORD(this.x+cord.x,this.y+cord.y,this.z+cord.z);
    }
    div(div){
        return new CORD(this.x/div,this.y/div,this.z/div);
    }
}

const act = [new CORD(-2,0,0),new CORD(2,0,0),new CORD(0,-2,0),new CORD(0,2,0),new CORD(0,0,-2),new CORD(0,0,2)];
function canMoveTo(maze, now, dir, size_x, size_y, size_z){
    let moved = now.add(act[dir]);
    if(moved.x < 0 || moved.x >= size_x || moved.y < 0 || moved.y >= size_y || moved.z < 0 || moved.z >= size_z) return false;
    return maze[moved.x][moved.y][moved.z] === KIND.WALL;
}
function cantMove(maze, now, size_x, size_y, size_z){
    return !canMoveTo(maze, now, DIR.F, size_x, size_y, size_z) &&
        !canMoveTo(maze, now, DIR.B, size_x, size_y, size_z) &&
        !canMoveTo(maze, now, DIR.L, size_x, size_y, size_z) &&
        !canMoveTo(maze, now, DIR.R, size_x, size_y, size_z) &&
        !canMoveTo(maze, now, DIR.U, size_x, size_y, size_z) &&
        !canMoveTo(maze, now, DIR.D, size_x, size_y, size_z);
}
function moveTo(maze, now, dir){
    let moved;
    moved = [now.add(act[dir].div(2)), now.add(act[dir])];
    maze[moved[0].x][moved[0].y][moved[0].z] = maze[moved[1].x][moved[1].y][moved[1].z] = KIND.PATH;
    now = moved[1];
    return now;
}

function generate(size_x, size_y, size_z){
    if(size_x%2===0 || size_y%2===0|| size_z%2===0 || size_x<5 || size_y<5 || size_z < 5 ){
        console.log("error");
    }

    let maze = [];
    for(let i=0; i<size_x; i++){
        maze[i] = [];
        for(let j=0; j<size_y; j++){
            maze[i][j] = [];
            for(let k=0; k<size_z; k++) maze[i][j][k] = KIND.WALL;
        }
    }
    const startCord = new Set();
    startCord.add(new CORD(1,1,1));
    let dir;
    let now;
    while (startCord.size !== 0) {
        now = [...startCord][Math.floor(Math.random() * (startCord.size))];
        if (cantMove(maze, now, size_x, size_y, size_z)) {
            startCord.delete(now);
            continue;
        }
        maze[now.x][now.y][now.z] = KIND.PATH;
        while (1) {
            if (cantMove(maze, now, size_x, size_y, size_z)) break;
            if (!startCord.has(now)) startCord.add(now);
            dir = Math.floor(Math.random() * (DIR.SIZE));
            if (!canMoveTo(maze, now, dir, size_x, size_y, size_z)) dir = (dir + 1) % (DIR.SIZE);
            else now = moveTo(maze, now, dir);
        }
    }
    return maze;
}

console.log(generate(5,5,5));