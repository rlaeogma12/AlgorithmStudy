/*
	Robot Cleaner Question :
	Samsung SW Test
	By Kim Dae Heum
	
	https://www.acmicpc.net/problem/14503
*/

#include <iostream>
enum direction{
	north = 0,
	east = 1,
	south = 2,
	west = 3,
	directionNum = 4
};

int directions[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};

using namespace std;

class map{
private:
	int N, M;	//row, col
public:
	bool **mapArray;
	bool **isCleaned;
	map(){
		mapArray = NULL;
		isCleaned = NULL;
	}
	~map(){
		if(mapArray && isCleaned){
			for(int i=0; i<N; i++){
				delete[] mapArray[i];
				delete[] isCleaned[i];
			}
			delete[] mapArray;
			delete[] isCleaned;
		}
	}
	
	void setSize(int row, int col){
		N = row, M = col;
		mapArray = new bool*[N];
		isCleaned = new bool*[N];
		for(int i=0; i<N; i++){
			mapArray[i] = new bool[M];
			isCleaned[i] = new bool[M];
		}
		
		//default setting.
		for(int i=0; i<N;i++){
			for(int j=0;j<M;j++){
				isCleaned[i][j] = false;
			}
		}
	}
	
	void setValue(int _row, int _col, int val){
		mapArray[_row][_col] = val;
	}
	
	void cleaning(int _row, int _col){
		isCleaned[_row][_col] = true;
	}
	
	bool isCleanedLoc(int _row, int _col){
		return isCleaned[_row][_col];
	}	
	
};

class robotCleaner{
private:
	int Startdirection;
	int startRow, startCol;	//current location
	int cleanedNum;
	map *area;
public:
	robotCleaner(){
		cleanedNum = 0;
	}
	~robotCleaner(){		
	}
	
	void setPosition(int _row, int _col, int _dir, map *_area){
		startRow = _row;
		startCol = _col;
		Startdirection = _dir;
		area = _area;
	}
	
	void clean(int _row, int _col){
		area->cleaning(_row, _col);
	}
	
	bool isCanGo(int row, int col){
		if(!(area->mapArray[row][col])){
			return true;
		}
		else{
			return false;
		}
	}
	
	int getBackdir(int dir){
		int backdir = dir+directionNum/2;
		
		if(backdir >= directionNum){
			backdir %= directionNum;
		}	
		return backdir;
	}
	
	void operation(int dir, int row, int col, int nonCleaned=0){
		
		//clean this pos. 1
		if(!(area->isCleanedLoc(row, col))){
			clean(row, col);
			cleanedNum++;	
		}
		
		int targetDir = dir-1;
		if(targetDir<0){
			targetDir += directionNum;
		}
		
		int targetRow = row + directions[targetDir][0];
		int targetCol = col + directions[targetDir][1];			
		
		//2
		if(nonCleaned != directionNum){
			//2-1
			if(!(area->isCleanedLoc(targetRow, targetCol)) && isCanGo(targetRow, targetCol)){
				operation(targetDir, targetRow, targetCol);
				return;
			}
			//2-2
			else{
				operation(targetDir, row, col, nonCleaned+1);
				return;			
			}			
		}
		else{
			int targetDir = getBackdir(dir);
			int targetRow = row + directions[targetDir][0];
			int targetCol = col + directions[targetDir][1];
			
			//2-3
			if(isCanGo(targetRow, targetCol)){
				operation(dir, targetRow, targetCol);
			}
			//2-4
			else{
				//END
				cout<<cleanedNum<<endl;
			}			
		}	
	}
	
	int getAnswer(){
		return cleanedNum;
	}
	
};

//global
robotCleaner Robot;
map Map;

void getInput(){
	int m, n;
	cin >> m >> n;
	Map.setSize(m, n);
	
	int row, col, dir;
	
	cin >> row >> col >> dir;
	Robot.setPosition(row, col, dir, &Map);

	bool buf;
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			cin >> buf;
			Map.setValue(i, j, buf);
		}
	}
	
	
	Robot.operation(dir, row, col);
}

int main(){
	getInput();
	return 0;
}
