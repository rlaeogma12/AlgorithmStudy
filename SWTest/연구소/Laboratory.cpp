/*
	Laboratory Question :
	Samsung SW Test
	By Kim Dae Heum
	
	https://www.acmicpc.net/problem/14502
	이렇게 푸는게 아닌것 같다.. 풀긴 풀었는데.. 
*/
#include <iostream>

using namespace std;

enum setting{
	space = 0,
	wall = 1,
	virus = 2,
	maxWall = 3
};

int dir[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

class lab{
private:
public:
	int N, M;
	int **mapArray;
	int **tmpArray;
	bool **visited;	//flag
	bool **virusVisited;	//virus flag
	int maxValue;
	
	lab(int _N, int _M){
		maxValue = 0;		
		N = _N, M = _M;
		mapArray = new int*[N];
		tmpArray = new int*[N];
		visited = new bool*[N];
		virusVisited = new bool*[N];
		for(int i=0; i<N; i++){
			mapArray[i] = new int[M];
			tmpArray[i] = new int[M];
			visited[i] = new bool[M];
			virusVisited[i] = new bool[M];
		}		
		
		//set default values
		for(int i=0;i<N;i++){
			for(int j=0;j<M;j++){
				visited[i][j] = false;
				virusVisited[i][j] = false;
			}
		}
	}
	~lab(){
		if(mapArray && visited){
			for(int i=0; i<N; i++){
				delete[] mapArray[i];
				delete[] tmpArray[i];
				delete[] visited[i];
				delete[] virusVisited[i];
			}
			delete[] mapArray;
			delete[] tmpArray;
			delete[] visited;
			delete[] virusVisited;
		}
	}
	
	void setArrayValue(int row, int col, int val){
		mapArray[row][col] = val;
	}
	
	void show(){
		cout<<"safe zone : ";
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				if(mapArray[i][j] == wall){
					cout<<"["<<i<<" "<<j<<"] ";
				}
			}
		}
		cout<<endl;		
	}
	
	void setTmpArray(){
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				tmpArray[i][j] = mapArray[i][j];
			}
		}
	}

	bool isCanGo(int row, int col){
		if(row>=0 && row <N){
			if(col>=0 && col <M){
				if(tmpArray[row][col] == space){
					return true;	
				}				
			}
		}
		return false;
	}
		
	void spreading(int row, int col){
		virusVisited[row][col] = true;
		
		for(int i=0; i<4; i++){
			int tRow = row + dir[i][0];
			int tCol = col + dir[i][1];
			
			if(isCanGo(tRow, tCol)){
				tmpArray[tRow][tCol] = virus;
				spreading(tRow, tCol);	
			}
		}
		
	}

	void setVirusVisited(){
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				virusVisited[i][j] = false;
			}
		}
	}
		
	void spreadVirus(){
		setVirusVisited();
		setTmpArray();
		
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				if(mapArray[i][j] == virus && !virusVisited[i][j]){
					spreading(i, j);
				}
			}
		}
	}	
	void setSafeZone(){		
		spreadVirus();
		
		int safeZoneNum = 0;
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				if(tmpArray[i][j] == space){
					safeZoneNum++;
				}
			}
		}
		
		if(safeZoneNum > maxValue){
			maxValue = safeZoneNum;
		}
	}
	
	bool isEmpty(int row, int col){
		if(mapArray[row][col] == space){
			return true;
		}
		else{
			return false;	
		}
	}
	
	//defense virus! ! !
	void operation(int current = 0, int wallNum = 0){	
		int row, col;
	
		if(wallNum == maxWall){
			setSafeZone();
		}
		else{
			for(int i=current; i<N*M; i++){
				row = i/M;
				col = i - row*M;
				if(!visited[row][col] && isEmpty(row, col)){
					visited[row][col] = true;
					mapArray[row][col] = wall;
					operation(i, wallNum+1);	
				}				
			}		
		}
		row = current/M;
		col = current - row*M;
		
		visited[row][col] = false;
		mapArray[row][col] = space;
	}
};

void getInput(){	
	int N, M, buf;
	cin >> N >> M;
	
	lab Lab(N, M);	//the only Object
	
	for(int i=0; i<N; i++){
		for(int j=0; j<M; j++){
			cin >> buf;
			Lab.setArrayValue(i, j, buf);
		}
	}
	
	Lab.operation();
	cout << Lab.maxValue <<endl;
}


int main(){
	getInput();
	return 0;
}
