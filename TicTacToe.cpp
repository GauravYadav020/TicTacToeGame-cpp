#include<bits/stdc++.h>

using namespace std;


void printboard();
void playermove();
void aimove();
void cornerChoice(bool);
void checkForWin();
void end();


//The 'pairs' list is used to check and see if anyone has won the game.
int pairs[8][3] = {
	{0, 3, 6},
	{1, 4, 7},
	{2, 5, 8},
	{0, 1, 2},
	{3, 4, 5},
	{6, 7, 8},
	{0, 4, 8},
	{2, 4, 6}
};

//'Corners' is used for the AI to let it pick random corners.
int corners[4] = {0, 2, 6, 8};

string board = "______   ";

//'Turn' keeps track of whose turn it is. During the game it is either "AI" or "PLAYER".
string turn = "PLAYER";

//'Aiturn' lets the AI know how many turns it has taken.
int aiturn = 0;
		

int main() {
	//cout << "MAIN\n\n";
	printboard();
	
	return 0;
}


//Just prints the board and starts the next turn
void printboard() {
	//cout << "printboard\n\n";
	cout << board[0] << "|" << board[1] << "|" << board[2] << endl;
	cout << board[3] << "|" << board[4] << "|" << board[5] << endl;
	cout << board[6] << "|" << board[7] << "|" << board[8] << endl;
	cout << endl << "Turn: " << turn << endl;
	
	if(turn == "O")
		playermove();
	else if(turn == "AI"){
		aiturn++;
		aimove();
	}
	else if(turn == "PLAYER")
		playermove();
}

//Prompts the player to move
//Also checks the input is legit or not
void playermove() {
	//cout << "playermove\n\n";
	int choice;
	cout << "Enter a number 0-8: ";
	cin >> choice;
	
	if(choice > 8 && choice < 0){
		cout << "Enter a number between 0 and 8." << endl;
		playermove();
	}
	else if(board[choice] == 'X' || board[choice] == 'O'){
		cout << "That place is already taken." << endl;
		playermove();
	}
	else
		board[choice] = 'O';
	
	turn = "AI";
	checkForWin();
}


void cornerChoice(bool alreadyMoved) {
	//cout << "cornerChoice\n\n";
	vector<int> goodChoices;
	int j = 0;
	
	srand(time(0));
	
	
	if(!alreadyMoved){
		for(int i = 0; i < 4; i++){
			if(board[corners[i]] == ' ' || board[corners[i]] == '_')
				goodChoices.push_back(corners[i]);
				j++;
		}
		//int temp = rand();
		board[goodChoices[rand() % goodChoices.size()]] = 'X';
		//cout << board[temp % goodChoices.size()] << ", " << temp % goodChoices.size() << endl;
	}
}


void aimove() {
	//cout << "aimove\n\n";
	bool alreadyMoved = false;
	int completes[8][3] = {
		{0, 3, 6},
		{1, 4, 7},
		{2, 5, 8},
		{0, 1, 2},
		{3, 4, 5},
		{6, 7, 8},
		{0, 4, 8},
		{2, 4, 6}
	};
	
	if(aiturn == 1){
		if(board[4] != 'O'){
			board[4] = 'X';
			alreadyMoved = true;
		}
		else{
			cornerChoice(alreadyMoved);
			alreadyMoved = true;
		}
	}
	else{
		//Offensive playing technique
		for(int i = 0; i < 8; i++){
			if(board[completes[i][0]] == 'X' && board[completes[i][1]] == 'X' && board[completes[i][2]] != 'O'){
				board[completes[i][2]] = 'X';
				alreadyMoved = true;
			}
			else if(board[completes[i][1]] == 'X' && board[completes[i][2]] == 'X' && board[completes[i][0]] != 'O'){
				board[completes[i][0]] = 'X';
				alreadyMoved = true;
			}
			else if(board[completes[i][0]] == 'X' && board[completes[i][2]] == 'X' && board[completes[i][1]] != 'O'){
				board[completes[i][1]] = 'X';
				alreadyMoved = true;
			}
		}
		
		//Defensive playing technique
		for(int i = 0; i < 8; i++){
			if(board[completes[i][0]] == 'O' && board[completes[i][1]] == 'O' && board[completes[i][2]] != 'O'){
				board[completes[i][2]] = 'X';
				alreadyMoved = true;
			}
			else if(board[completes[i][1]] == 'O' && board[completes[i][2]] == 'O' && board[completes[i][0]] != 'O'){
				board[completes[i][0]] = 'X';
				alreadyMoved = true;
			}
			else if(board[completes[i][0]] == 'O' && board[completes[i][2]] == 'O' && board[completes[i][1]] != 'O'){
				board[completes[i][1]] = 'X';
				alreadyMoved = true;
			}
		}
	}
	
	if(!alreadyMoved){
		if(aiturn == 2 && board[4] == 'O')
			cornerChoice(alreadyMoved);
		else{
			int sides[4] = {1, 3, 5, 7};
			int humanSides = 0;
			for(int i = 0; i < 4; i++)
				if(board[sides[i]] == 'O')
					humanSides++;
			
			if(humanSides >= 1)
				cornerChoice(alreadyMoved);
			else{
				srand(time(0));
								
				vector<int> goodChoices;
				for(int i = 0; i < 4; i++)
					if(board[sides[i]] == ' ' || board[sides[i]] == '_')
						goodChoices.push_back(sides[i]);
				if(goodChoices.empty())
					cornerChoice(alreadyMoved);
				else
					board[goodChoices[rand() % goodChoices.size()]] = 'X';
			}
		}
	}
	
	turn = "PLAYER";
	checkForWin();
}

void checkForWin() {
	//cout << "checkforwin\n\n";
	for(int i = 0; i < 8; i++){
		char zero = board[pairs[i][0]];
		char one = board[pairs[i][1]];
		char two = board[pairs[i][2]];
		
		if(zero == one && one == two){
			if(zero == 'X'){
				cout << "AI WINS" << endl;
				end();
			}
			else if(zero == 'O'){
				cout << "You won, did you cheat or what?" << endl;
				end();
			}
		}
		else{
			int filledSpaces = 0;
			for(int i = 0; i < 8; i++){
				if(board[i] != ' ' && board[i] != '_')
					filledSpaces++;
				if(filledSpaces == 8){
					cout << "A draw! You will never win!" << endl;
					end();
				}
			}
		}
	}
	printboard();
}

void end() {
    cout << "Here is the final board." << endl;
    cout << board[0] << "|" << board[1] << "|" << board[2] << endl;
    cout << board[3] << "|" << board[4] << "|" << board[5] << endl;
    cout << board[6] << "|" << board[7] << "|" << board[8] << endl;
    exit(0);
}

