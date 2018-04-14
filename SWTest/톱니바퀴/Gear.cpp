/*
	Gear Question :
	Samsung SW Test
	Gear Question
	By Kim Dae Heum
	
	https://www.acmicpc.net/problem/14891
*/
#include <iostream>

#define gearEdgeNumber	8
#define gearNumber	4

enum way{
	CLOCKWISE = 1,
	NON_CLOCKWISE = -1
};

enum polar{
	N_Polar = 0,
	S_Polar = 1
};



using namespace std;

class gear{
public:
	int status[gearEdgeNumber];
	
	//set Status from input strings.
	void setStatus(char *inputString){
		for(int i=0; i<gearEdgeNumber; i++){
			status[i] = (int)(inputString[i] - '0');
		}
	}
	
	//rotate to Left
	void rotate(int way){		
		//switch Start
		switch(way){
			case CLOCKWISE:{
				int tmp = status[gearEdgeNumber-1];
				
				for(int i=gearEdgeNumber-1; i>0; i--){
					status[i] = status[i-1];					
				}
				status[0] = tmp;				
				
				break;
			}
			case NON_CLOCKWISE:{
				int tmp = status[0];
				for(int i=0; i<gearEdgeNumber-1; i++){
					status[i] = status[i+1];
				}
				status[gearEdgeNumber-1] = tmp;
				
				break;
			}
		}
		//switch End
	}
	
	void showStatus(){
		cout << "See Diff" << endl;
		for(int i=0;i<gearEdgeNumber;i++){
			cout << status[i];
		}
		cout << endl;
	}
	
};

class handleGear{
	//Gear Numbers
public:
	int Score;
	gear Gear[gearNumber];
	
	//constructor
	handleGear(){
		Score = 0;
	}
	
	//rotate all gear
	void rotateObjGear(int objNum, int rotateWay){
		
		int tmpNum = objNum;
		int tmpRotateState = rotateWay;
			
		//see my Left Gears
		while(tmpNum > 0){
			//IF Left GearEdge is not same with my GearEdge and not visited.
			if(Gear[tmpNum].status[gearEdgeNumber - gearEdgeNumber/4] != Gear[tmpNum-1].status[gearEdgeNumber/4]){
				tmpRotateState = tmpRotateState == CLOCKWISE? NON_CLOCKWISE : CLOCKWISE;
				Gear[tmpNum-1].rotate(tmpRotateState);
				tmpNum--;		
			}
			else{
				break;
			}			
		}
		
		tmpNum = objNum;
		tmpRotateState = rotateWay;
		
		//see my Right Gears
		while(tmpNum < gearNumber - 1){
			//IF Right GearEdge is not same with my GearEdge and not visited.
			if(Gear[tmpNum].status[gearEdgeNumber/4] != Gear[tmpNum+1].status[gearEdgeNumber - gearEdgeNumber/4]){
				tmpRotateState = tmpRotateState == CLOCKWISE? NON_CLOCKWISE : CLOCKWISE;
				Gear[tmpNum+1].rotate(tmpRotateState);
				tmpNum++;	
			}
			else{
				break;
			}					
		}		
		//rotate my own Gears
		Gear[objNum].rotate(rotateWay);		
	}
	
	int multiple(int obj, int times){
		int ans = 1;
		for(int i=0; i<times; i++){
			ans *= obj;
		}
		return ans;
	}
	
	void summaryScore(){
		Score = 0;
		for(int i=0; i<gearNumber; i++){
			if(Gear[i].status[0] == S_Polar){
				Score += multiple(2, i);
			}
		}
	}	
};

//get Input!
void getInput(){
	
	handleGear HandleGear;
	
	char buff[gearEdgeNumber];
	
	for(int i=0; i<gearNumber; i++){
		cin >> buff;
		HandleGear.Gear[i].setStatus(buff);
	}		
	
	int K;	//rotate number
	cin >> K;
	
	int varBuf[2];
	
	for(int i=0; i<K; i++){
		cin >> varBuf[0] >> varBuf[1];
		HandleGear.rotateObjGear(varBuf[0]-1, varBuf[1]);
	}
	
	HandleGear.summaryScore();	
	cout << HandleGear.Score;
}

//main
int main(){
	getInput();	
	return 0;
}
