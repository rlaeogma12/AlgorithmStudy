/*
	Slope Question :
	Samsung SW Test
	Gear Question
	By Kim Dae Heum
	
	https://www.acmicpc.net/problem/14890
*/

#include <iostream>

using namespace std;

class tile{
public:
	int height;
	bool isWidthSlope, isHeightSlope;
	bool isWidthStart, isHeightStart;
	
	//constructor
	tile(){
		isWidthSlope = false;
		isHeightSlope = false;
		isWidthStart = false;
		isHeightStart = false;
		height = 0;
	}
};

class map{
public:
	//Variables
	tile **mapArray;
	int N, L;
	bool isFromStart;
	
	//--Functions---
	
	//constructor & destructor
	map(){
		mapArray = NULL;
		N = 0;
		L = 0;
		isFromStart = true;
	}
	~map(){
		for(int i=0; i<N; i++){
			delete[] mapArray[i];
		}
		delete[] mapArray;
	}
	
	//set the Map Array
	void setMapArray(int nValue, int lValue, int **givenArr){
		N = nValue;
		L = lValue;
		mapArray = new tile*[N];
		for(int i=0;i<N;i++){
			mapArray[i] = new tile[N];
		}
		
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				mapArray[i][j].height = givenArr[i][j];
			}
		}
	}
	
	/*
	//show.
	void showMapArray(){
		cout<<"--- Array ---"<<endl;
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				cout << mapArray[i][j].height;
				
				if(mapArray[i][j].isHeightStart){
					cout << "[";
				}				
				cout << mapArray[i][j].isHeightSlope;
				if(mapArray[i][j].isHeightStart){
					cout << "]";
				}
				
				if(mapArray[i][j].isWidthStart){
					cout << "["; 
				}							
				cout << mapArray[i][j].isWidthSlope;	

				if(mapArray[i][j].isWidthStart){
					cout << "]";
				}		
				
				cout<<"\t";				
				
			}
			cout<<endl;
		}	
		cout<<"-------------"<<endl;	
	}
	*/	
	
	//is all same in a row for L.
	bool isSameInRow(int row, int col){
		bool result = true;
		for(int i=0; i<L-1; i++){
			if(mapArray[row+i][col].height != mapArray[row+i+1][col].height){
				result = false;
			}
		}
		
		bool isVaildWall = false;
		
		if(result){
			
			//if the front of my in-a-row height is not as different as only 1. (check my before)
			if(row>0 && mapArray[row-1][col].height == mapArray[row][col].height + 1){
				isVaildWall = true;
				isFromStart = true;
			}
			
			//check my after.			
			if(row + L < N && mapArray[row+L][col].height == mapArray[row][col].height + 1){
				if(isVaildWall == true){
					isVaildWall = false;
				}
				else{
					isVaildWall = true;
				}				
				isFromStart = false;
			}
		}
		
		if(result && isVaildWall){
			return true;
		}
		else{
			return false;
		}
	}
	
	//is all same in a col for L.
	bool isSameInCol(int row, int col){
		bool result = true;
		for(int i=0; i<L-1; i++){
			if(mapArray[row][col+i].height != mapArray[row][col+i+1].height){
				result = false;
			}
		}	
		
		bool isVaildWall = false;
		
		if(result){
			
			//if the front of my in-a-col height is not as different as only 1. (check my before)
			if(col>0 && mapArray[row][col-1].height == mapArray[row][col].height + 1){
				isVaildWall = true;
				isFromStart = true;
			}
			
			//check my after.			
			if(col + L < N && mapArray[row][col+L].height == mapArray[row][col].height + 1){
				if(isVaildWall == true){
					isVaildWall = false;
				}
				else{
					isVaildWall = true;
				}
				
				isFromStart = false;
			}
		}
		
		if(result && isVaildWall){
			return true;
		}
		else{
			return false;
		}
	}
	
	//setting slope which profits conditions.
	void setSlope(){		
		int iter;
		
		//ROW
		for(int i=0; i<N; i++){
			iter = 0;
			while(iter + L <= N){
				if(isSameInRow(iter, i)){
					if(isFromStart){
						mapArray[iter][i].isHeightStart = true;
					}
					else{
						mapArray[iter+L-1][i].isHeightStart = true;
					}
					
					//set ROW Slope
					for(int j=0; j<L; j++){
						mapArray[iter+j][i].isHeightSlope = true;
					}
					
					iter += L-1;
				}	
				iter++;				
			}			
		}
		
		//COL
		for(int i=0; i<N; i++){
			iter = 0;
			while(iter + L <= N){
				if(isSameInCol(i, iter)){		
					if(isFromStart){
						mapArray[i][iter].isWidthStart = true;
					}
					else{
						mapArray[i][iter+L-1].isWidthStart = true;
					}							
					
					//set COL Slope
					for(int j=0; j<L; j++){
						mapArray[i][iter+j].isWidthSlope = true;
					}
					iter += L-1;
				}	
				iter++;				
			}			
		}		
		//end of for loop
	}

	
	//count available Road
	int countVaildRoad(){
		int answer = 0;
				
		int iter;
		bool isVaildRoad;
		
		//See Row Road 		
		//Start From first row
		for(int i=0; i<N; i++){
			isVaildRoad = true;
			iter = 0;
			while(iter < N-1){
				//if the next road has different height
				if(mapArray[iter][i].height > mapArray[iter+1][i].height){
					//if the next hasn't slope.
					if(mapArray[iter+1][i].isHeightStart == false){
						isVaildRoad = false;
						break;
					}
				}
				else if(mapArray[iter][i].height < mapArray[iter+1][i].height){
					if(mapArray[iter][i].isHeightStart == false){
						isVaildRoad = false;
						break;
					}
				}
				
				iter++;
			}					
			
			if(isVaildRoad){
				answer++;
			}			
		}		
		
		
		//See Col Road		
		for(int i=0; i<N; i++){
			isVaildRoad = true;
			iter = 0;
			while(iter < N-1){
				//if the next road has different height
				if(mapArray[i][iter].height > mapArray[i][iter+1].height){
					//if the next hasn't slope.
					if(mapArray[i][iter+1].isWidthStart == false){
						isVaildRoad = false;
						break;
					}
				}
				else if(mapArray[i][iter].height < mapArray[i][iter+1].height){
					//if the next hasn't slope.
					if(mapArray[i][iter].isWidthStart == false){
						isVaildRoad = false;
						break;
					}
				}				
				iter++;
			}					
			
			if(isVaildRoad){
				answer++;
			}			
		}		
		
		
		return answer;
	}	
	
};


//Global Variables
int Count = 0;
map Map;

//get Input!
void getInput(){
	//N : Map Width/Height , L : Slope Width.
	int N, L;
	
	cin >> N >> L;
	
	int **buf = new int*[N];
	for(int i=0; i<N; i++){
		buf[i] = new int[N];
	}
	
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			cin >> buf[i][j];
		}
	}
	
	Map.setMapArray(N, L, buf);
	Map.setSlope();
	//Map.showMapArray();
	Count = Map.countVaildRoad();
	
	for(int i=0; i<N; i++){
		delete[] buf[i];
	}
	delete[] buf;
}

//main
int main(){
	getInput();
	cout << Count << endl;
	return 0;
}
