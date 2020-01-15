#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "header.h"

using namespace std;

int main() {

	ifstream stream;
	string fileName;

	cout << "Please enter a file name." << endl;
	cin >> fileName;

	while(stream.fail()) { //if stream fails ask for appropriate name
		
		cout << "Unable to open file " << fileName << endl;
		cout << "Please enter a different file name." << endl;
		cin >> fileName;     
	}   stream.open(fileName.c_str()); 

	cout << "Successfully opened file " << fileName << endl << endl;
	cout << "######## TOPOLOGY ########" << endl << endl;

	string house, neighbor, line;
	linkedList GOT;

	while(getline(stream,line)) {

		istringstream iss(line);
		iss >> house >> neighbor; //taking house and neigbor names as string w/ iss

		cout << "Processing " << house << ", " << neighbor << endl;

		if(GOT.nnExists(house,neighbor) && GOT.nnExists(neighbor,house))
			cout << "Redundant information! An entry with " << house << " and " << neighbor <<" is already processed." << endl << endl;

		else 
		    cout << "Topology information successfully added." << endl << endl;

		if(!GOT.hnExists(house)) //there is no house name
			GOT.addHouseNode(house);
		
	    if(!GOT.hnExists(neighbor)) //there is no neighbor name
			GOT.addHouseNode(neighbor);

		if(!GOT.nnExists(house,neighbor)) //there is house name but not neighbor
			GOT.addNeighborNode(house,neighbor);
		
		if(GOT.nnExists(house,neighbor)) //there is house name and neighbor name, it makes neigbor and house neighbors as well.
			GOT.addNeighborNode(neighbor,house);

	}    cout << endl << "######## MAP ########" << endl << endl ;

	GOT.printAll(); //print function of map
	stream.close();

	int action = 0;
	while(action != 3) { //this will make the game continue until user enters 3 

		cout << endl << endl << "Please select an option [1-2-3]." << endl << "1. Annexation! War for the iron throne continues..." << endl ;
		cout << "2. Tyrion must travel, do a path check for the famous imp." << endl << "3. Exit" << endl ;
		cin >> action;


		if(action == 1) { //if user enters 1 the game will continue with this part

			cout << "Please enter two houses first the annexer and the annexed. (ex: Tyrell Stark)." << endl;
			string attack,winner,loser;
			cin.ignore();

			getline(cin,attack,'\n');
			istringstream vs(attack);
			vs >> winner >> loser; //taking conquerer and conquered name as string w/ iss

			if(!GOT.hnExists(winner)) //if first input doesnt exist
				cout << winner << " does not exist!" << endl << "Update failed." << endl ;

			else if(!GOT.hnExists(loser)) // if second input doesnt exist
				cout << loser << " does not exist!" << endl << "Update failed." << endl ; 

			else if(winner == loser) //if inputs are the same
				cout << "A House cannot conquer itself!" << endl << "Update failed." << endl;

			else if(!GOT.nnExists(winner,loser)) //if inputs are not neighbor
				cout << "A house can only conquer a neighboring house! " << loser << " is not a neighbor of " << winner << "." << endl << "Update failed." << endl;

			else if(GOT.nnExists(winner,loser)) { //if inputs are available for conquering

				GOT.conquerIt(winner,loser); //this function transfers the neighbors of loser to the winner
				GOT.deleteLoser(loser); //this function deletes the loser house 
				GOT.neighborDeleter(winner,loser); //this function deletes loser from the other neighbors lists
				cout << winner << " conquered " << loser << "!" << endl;
				cout << "######## MAP ########" << endl;
				GOT.printAll();
			}
		}

		else if(action == 2) { //if user enters 2 the game will continue with this part

			cout << "Please enter a path. (ex: Tyrell Martell Tully)" << endl;
			string path, prevHouse, nextHouse, next; 
			cin.ignore();

			getline(cin,path,'\n');
			istringstream control(path) ;
			control >> prevHouse >> nextHouse; //taking house names as string to create path w/ iss
			
			bool check = true;
			bool test = true;
			
			if(prevHouse == nextHouse) // if house names are same
				cout << "You are already in " << prevHouse << endl;

			if(!GOT.hnExists(prevHouse)) { //if input is not propriet
				cout << prevHouse << " does not exist in the map." << endl;
				test = false;
				check = false;
			}
			else if(!GOT.hnExists(nextHouse)) {
				cout << nextHouse << " does not exist in the map." << endl;
				test = false;
				check = false;
			}
			
			if(GOT.nnExists(prevHouse,nextHouse) && test) //if inputs are neighbor
				cout << "Path found between " << prevHouse << " and " << nextHouse << endl;
			
			else if(!GOT.nnExists(prevHouse,nextHouse) && test && prevHouse != nextHouse) { //if inputs are not neighbor
				cout << prevHouse << " is not a neighbor of " << nextHouse << endl;
				check = false;
			}

			while (control >> next) { 

				prevHouse = nextHouse;
			    nextHouse = next;
				
				if(!GOT.hnExists(nextHouse)) {
				cout << nextHouse << " does not exist in the map." << endl;
				test = false;
				}

				else if(!GOT.hnExists(prevHouse)) {
					cout << prevHouse << " does not exist in the map." << endl;
					test = false;
				}
				
				if (GOT.nnExists(nextHouse,prevHouse)) 
					cout << "Path found between " << nextHouse << " and " << prevHouse << endl;
				
				else if(!GOT.nnExists(nextHouse,prevHouse) && nextHouse != prevHouse && test) {
					cout << nextHouse << " is not a neighbor of " << prevHouse << endl;
					check = false; 
				}
			}	
			if(nextHouse == prevHouse)
				check = true;

			if(check && test)
				cout << "Path search succeeded." << endl;
			else if(!check || !test)
				cout << "Path search failed!" << endl;
		}

		else if(action > 3 || action < 0) // if input is not 1,2 or 3
			cout << "Invalid option please select from the menu." << endl;
	}
	//if user enters 3
	GOT.deleteAll();
	cout << "List deleted and program ended." << endl;


	cin.get();
	cin.ignore();
	
	return 0;
} 
