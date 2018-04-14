/*
	Get out of Company Question :
	Samsung SW Test
	By Kim Dae Heum
	
	https://www.acmicpc.net/problem/14501
	0/1 knapsack / backtracking or branch bound. NP-HARD
*/

#include <iostream>
#include <algorithm>

using namespace std;

class counsil{
private:
	int N;
	int *timeArr, *priceArr;
	bool *visited;
	int maxPrice;
	
public:
	counsil(int _N){
		maxPrice = 0;
		N = _N;
		timeArr = new int[N], priceArr = new int[N];	
		visited = new bool[N];
		
		for(int i=0; i<N; i++){
			visited[i] = false;
		}
	}
	~counsil(){
		if(timeArr){
			delete[] timeArr;
			delete[] priceArr;
			delete[] visited;
		}
	}
	
	void setTimeArr(int _row, int val){
		timeArr[_row] = val;
	}
	
	void setPriceArr(int _row, int val){
		priceArr[_row] = val;
	}
		
	void doSangDam(int time = 0, int cost = 0){
		if(time == N){
			maxPrice = max(maxPrice, cost);
			return;
		}
		
		if(time + timeArr[time] <= N) doSangDam(time+timeArr[time], cost+priceArr[time]);
		if(time + 1 <= N) doSangDam(time+1, cost);		
	}
	
	int getResult(){
		return maxPrice;
	}
	
	
};

void getInput(){
	int size, buf1, buf2;
	cin >> size;
	counsil BackJoonCS(size);
	
	for(int i=0; i<size; i++){
		cin >> buf1 >> buf2;
		BackJoonCS.setTimeArr(i, buf1);
		BackJoonCS.setPriceArr(i, buf2);
	}
	
	BackJoonCS.doSangDam();
	cout << BackJoonCS.getResult();	
}


int main(){
	getInput();
	return 0;
}
