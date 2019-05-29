/*
 * Deliver the egg: This is a board game. It uses dice to determine how many steps you can move. What's different
 * 		from other board game is two players are moving the same object, the egg. And each player can have 3 chances
 * 		to go back in order to prevent the other to get the destination.
 * 	Basic rules: 2 players take turns to roll the dice, each player must move exactly the same step as the number
 * 		on dice. If the egg stop at the destination, then that player wins. If the egg reach the destination, but
 * 		there are steps left, then go that amount of steps backward. The strategy is to go back. Each player
 * 		has three times to go back, in order to prevent your opponent from being able to win. If the current position
 * 		number is less than the number on dice and the player decide to go backward. Then the egg will just remain at the same place.
 */

#include <iostream>
#include <string>
#include <time.h>
#include <vector>
using namespace std;
void show(vector <string> map, int position);
void clear(vector <string> map);

int main(void){
	srand((unsigned)time(NULL));
	int p1back;//the chance for each player to go back is 3
	int p2back;
	int d1;
	int d2;//the point on the dice
	char direction;//go forward or backward
	int mode;//the number of game mode
	int destination;//how large the map is
	char go;//the command to roll the dice
	bool p1win,p2win;//the winning condition of each player
	char cont;//whether the players want to have a new game after they finish one game

	while(cont != 'n'){
		p1back = 3;//the chance for each player to go back is 3
		p2back = 3;
		vector <string> map;//the string vector to show where the egg is
		p1win,p2win = false;//the winning condition of each player are false at the beginning
		cout << "Welcome to Deliver The Egg!\n";
		cout << "Choose game mode: 1:quick match. 2:standard match.";
		while(!(cin >> mode) || (mode != 1 && mode != 2)){
		cout << "Wrong input, please enter 1 or 2 for game mode.\n";
			cin.clear();
			while(cin.get() != '\n'){};
		}
		if(mode == 1){//quick match has a smaller map
			cout << "This is quick mode, the egg is only 10 steps to the destination, be careful.\n";
			for(int i = 0; i < 10; i ++){//set up the map with size 10
				map.push_back("_ ");
			}
			destination = 10;
		}else{//standard mode
			cout << "This is standard mode, the egg is 15 steps away. Think farther.";
			for(int i = 0; i < 15; i ++){//set up a map with size 15
				map.push_back("_ ");
			}
			destination = 15;
		}
		int position = 1;//the egg's initial position
		show(map,position);//show where the egg is
		while(p1win != true && p2win != true){//a loop until one player wins
			cout << "Now is player 1's turn, please roll the dice. (enter g)";
			while(!(cin >> go) || (go != 'g')){
				cout << "Wrong input, enter g to roll the dice.\n";
			}
			d1 = rand() % 6 + 1;//generate a random number from 1 to 6
			cout << "You got number " << d1 << endl;
			cout << "Go forward(f) or go back(b)? You have " << p1back << " chance(s) to go back.";
			while(!(cin >> direction) || (direction != 'f' && direction != 'b')){//input validation
				cout << "Wrong input, please enter f for go forward and b for backward.\n";
				while(cin.get() != '\n'){};
			}
			if(direction == 'f'){//if the player choose to go forward
				if((position + d1) > destination){//if you go beyond the map, the overflowing step will be go backwards
					position = destination - (position + d1 - destination);
				}else if((position + d1) == destination){//if you just get the destination then you win
					p1win = true;
					break;//terminate the current game
				}else{//else just add the number to position
					position += d1;
					cout << "You move " << d1 << " steps forward.\n";
				}
			}else{//if the player choose to go backwards
				if(p1back <= 0){//if the player has no chance to go back, also automatically go forward
					cout << "You have no chance to back, go forward.\n";
					if((position + d1) > destination){//and check the forward conditions
						position = destination - (position + d1 - destination);
					}else if((position + d1) == destination){
						p1win = true;
						break;
					}else
						position += d1;
						cout << "You move " << d1 << " steps forward.\n";
				}else if((position - d1) <= 0){//if the egg will go before the initial position, just stand still and lose 1 chance to go back
					cout << "There's no way for you to go back, you did nothing.\n";
					p1back --;
				}else{
					cout << "You move " << d1 << " steps backward.\n";
					position -= d1;
					p1back --;
				}

			}
			show(map,position);//after player 1 's operation, show the egg's position
			cout << "Now is player 2's turn, please roll the dice. (enter g)";
			while(!(cin >> go) || (go != 'g')){
				cout << "Wrong input, enter g to roll the dice.\n";
			}
			d2 = rand() % 6 + 1;
			cout << "You got number " << d2 << endl;
			cout << "Go forward(f) or go back(b)? You have " << p2back << " chance(s) to go back.";
			while(!(cin >> direction) || (direction != 'f' && direction != 'b')){
				cout << "Wrong input, please enter f for go forward and b for backward.\n";
				while(cin.get() != '\n'){};
			}
			if(direction == 'f'){
				if((position + d2) > destination){
					position = destination - (position + d2 - destination);
				}else if((position + d2) == destination){
					p2win = true;
					break;
				}else{
					position += d2;
					cout << "You move " << d1 << " steps forward.\n";
				}
			}else{
				if(p2back <= 0){
					cout << "You have no chance to back, go forward.\n";
					if((position + d2) > destination){
						position = destination - (position + d2 - destination);
					}else if((position + d2) == destination){
						p2win = true;
						break;
					}else{
						position += d2;
						cout << "You move " << d2 << " steps forward.\n";
					}
				}else if((position - d2) <= 0){
					cout << "There's no way for you to go back, you did nothing.\n";
					p2back --;
			}else{
				position -= d2;
				p2back --;
				cout << "You move " << d2 << " steps backward.\n";
			}
		}
			show(map,position);
		}
		if(p1win == true){//if player 1 wins
			cout << "Player 1 deliver the egg to the destination successfully, congratulations!\n";
		}else{//if player 2 wins
			cout << "Player 2 deliver the egg to the destination successfully, congratulations!\n";
		}
		clear(map);//after each round of game, set the map back to null

		cout << "Do you want to continue playing? (y for yes, n for no)";
		while(!(cin >> cont) || (cont != 'n' && cont != 'y')){
			cout << "Wrong input, just y for yes and n for no.\n";
		}
	}
	cout << "Bye, see you next time!\n";
	return 0;
}

void show(vector <string> map, int position){
	cout << "Now the egg is at position " << position << endl;
	for(int i = 0; i < map.size(); i ++){
		if(i == position -1){
			cout << "O ";//if the block is position, print the egg(i use just letter O to represent)
		}else//otherwise, print the map
		cout << map[i];
	}
	cout << endl;
}

void clear(vector <string> map){
	while(!map.empty()){//set the map back to null
		map.pop_back();
	}
}


