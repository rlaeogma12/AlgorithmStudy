/*
	insert operation Question :
	Samsung SW Test
	By Kim Dae Heum
	
	https://www.acmicpc.net/problem/14888
*/

#include <iostream>

enum operations{
	opNumber = 4,
	add = 1,
	sub = 2,
	mul = 3,
	divide = 4
};	

using namespace std;

class operation{
private:
	int maxValue, minValue;
	int opNum[opNumber];
	int *opArray, *numArray;
	bool *opVisited;
	
	int N;
	
public:
	operation(){
		maxValue = -1000000000;
		minValue = 1000000000;
		opArray = NULL, numArray= NULL, opVisited= NULL;
	}
	~operation(){
		if(opArray && numArray && opVisited){
			delete[] opArray;
			delete[] numArray;
			delete[] opVisited;
		}
	}
	
	void setOpNum(int row, int eachOpNum){
		opNum[row] = eachOpNum;
	}
	
	void setSize(int _N){
		N = _N;
		numArray = new int[N];
		opArray = new int[N-1];
		opVisited = new bool[N-1];
		
		for(int i=0; i<N-1; i++){
			opVisited[i] = false;
		}
	}
	
	void setEachNumArrayValue(int row, int value){
		numArray[row] = value;
	}
	
	int getMin(){
		return minValue;
	}
	
	int getMax(){
		return maxValue;
	}
	
	void calculateOp(){
		int ans = numArray[0];
		for(int i=1; i<N; i++){
			switch(opArray[i-1]){
				case add:{
					ans += numArray[i];
					break;
				}
				case sub:{
					ans -= numArray[i];
					break;
				}
				case mul:{
					ans *= numArray[i];
					break;
				}
				case divide:{
					ans /= numArray[i];
					break;
				}
			}
		}
		
		if(maxValue < ans){
			maxValue = ans;
		}
		if(minValue > ans){
			minValue = ans;
		}
	}
	
	void getAnswer(int op = 0, int iter = 0, int curNum = 0){
		if(op == opNumber){
			calculateOp();
		}
		else{
			if(opNum[op] == curNum){
				getAnswer(op+1, iter, 0);
			}
			else{
				for(int j=0; j<N-1; j++){
					if(!opVisited[j]){
						opVisited[j] = true;
						opArray[j] = op+1;
						getAnswer(op, j, curNum+1);
					}
				}					
			}
		}
		opVisited[iter] = false;		
	}
	
};

void getInput(){	
	operation makeOp;
	int size, buf;
	cin >> size;	
	makeOp.setSize(size);
	for(int i=0; i<size; i++){
		cin >> buf;
		makeOp.setEachNumArrayValue(i, buf);
	}
	
	for(int i=0;i<opNumber;i++){
		cin >> buf;
		makeOp.setOpNum(i, buf);
	}
	
	makeOp.getAnswer();
	
	cout << makeOp.getMax() << endl;
	cout << makeOp.getMin() << endl;
	
	
}

int main(){
	getInput();
	return 0;
}
