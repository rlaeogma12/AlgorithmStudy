/*
	Start & Link Question :
	Samsung SW Test
	Gear Question
	By Kim Dae Heum
	
	https://www.acmicpc.net/problem/14889
	스타트와 링크 
*/

#include <iostream>
#include <vector>

using namespace std;
//class for handling players.
class info{
private:	
	int N;	//player Number
	int **statArray;	//player data
	bool *joinedFlag;	//flag for check that a player already joined the team or not.
	//save team players.
	int *team_Start, *team_Link;
	//least diff value
	int leastDiff;
	
public:
	//constructor & destructor.크 
	info(){
		statArray = NULL;
		joinedFlag = NULL;
		team_Start = NULL;
		team_Link = NULL;
		
		N = 0;
		leastDiff = 10000000;	//big as much as possible.
	}
	~info(){
		if(statArray && joinedFlag && team_Start && team_Link){
			for(int i=0;i<N;i++){
				delete[] statArray[i];
			}
			delete[] statArray;
			delete[] joinedFlag;
			delete[] team_Start;
			delete[] team_Link;			
		}
	}
	
	void setPlayerNumber(int _N){
		N = _N;		
		statArray = new int*[N];
		joinedFlag = new bool[N];
		team_Start = new int[N/2];
		team_Link = new int[N/2];
		
		for(int i=0; i<N; i++){
			statArray[i] = new int[N];			
			//initiation.
			joinedFlag[i] = false;
		}
	}
	
	void setStatusData(int row, int col, int value){
		statArray[row][col] = value;
	}
	
	void showData(){
		for(int i=0;i<N;i++){
			for(int j=0;j<N;j++){
				cout << statArray[i][j];
			}
			cout<<endl;
		}
	}
	
	
	int getScore(int p1, int p2){
		return statArray[p1][p2];	
	}
	
	//divide Team!
	void divideTeam(){
		int ai = 0, bi = 0;
		
		for(int i=0; i<N; i++){
			if(joinedFlag[i]){
				team_Start[ai++] = i;
			}
			else{
				team_Link[bi++] = i;
			}
		}
		
		int teamStart_Score = 0, teamLink_Score = 0;
		
		//Add team Score
		for(int i=0;i<N/2;i++){
			for(int j=0;j<N/2;j++){
				if(i!=j){
					teamStart_Score += getScore(team_Start[i], team_Start[j]);
					teamLink_Score += getScore(team_Link[i], team_Link[j]);
				}
			}
		}
		
		int diff = teamStart_Score > teamLink_Score? teamStart_Score - teamLink_Score : teamLink_Score - teamStart_Score;		
		
		if(leastDiff > diff){
			leastDiff = diff;
		}					
	}
	
	void getLeastDiff(int player, int joinedNumber){
		//if player number of one side reached to N/2, divide Team!
		if(joinedNumber == N/2){
			divideTeam();
		}
		else{
			for(int i=player; i<N; i++){
				if(!joinedFlag[i]){
					joinedFlag[i] = true;
					getLeastDiff(i, joinedNumber+1);
				}
			}
		}
		joinedFlag[player] = false;		
	}
	
	int getResult(){
		return leastDiff;
	}
	
	
};

info PlayerInfo;

void getInput(){
	int size, buf;
	cin >> size;
	PlayerInfo.setPlayerNumber(size);
	
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			cin >> buf;
			PlayerInfo.setStatusData(i,j,buf);
		}
	}
	PlayerInfo.getLeastDiff(0, 0);
	
	cout << PlayerInfo.getResult() << endl;
}

int main(){
	getInput();
	return 0;
}
