/*
o CS 280-102, SPRING 2015
o Ernesto Martinez
o Program #2
*/

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "p2lex.h"
using namespace std;


int main(int argc, char*argv[]) {

	char line[1000];
	string lexeme;
	vector<Token> list;
	vector<string> identifiers;
	map<Token,int> reference;

	Token endToke(DONE), myToke;
	int i = 0, idCompare = 0;
	istream *br;
	ifstream inStream(argv[1]);
	br = &inStream;

	Token id(ID), integer(INT), string(STRING), plus(PLUS), minus(MINUS), star(STAR), slash(SLASH), set(SET), print(PRINT), sc(SC), done(DONE);

	reference[id, integer, string, plus, minus, star, slash, set, print, sc, done] = 0;

	if(argc < 2) //checks for argument count < 2
	{
		while( cin.good() ) {
			cin.get(line, 999);
		}
	}
	if(argc > 2) //checks for argument count > 2
	{
		cout << "Too many arguments" << endl;
		return 0;
	}
	if(inStream.is_open()) //validates file name
	{
	}
	else
	{
		cout << "File not found" << endl;
		return 0;
	}
	inStream.seekg(0, ios::end); // checks for empty file
	if (inStream.tellg() < 1)
	{
		return 0;
	}
	inStream.seekg(0);

	do	//call for getToken function
	{
		myToke = getToken(br, lexeme);
		list.push_back(myToke);
		if(!lexeme.empty() && lexeme != "set" && lexeme != "print") //if identifier is not keyword, add to "identifiers"
		{
			if(identifiers.size() == 0)
				identifiers.push_back(lexeme);
			else
			{
				for(i = 0; i < identifiers.size(); i++)
				{
					if(lexeme.compare(identifiers[i]) == 0)
						idCompare++;
				}
				if(idCompare == 0)
				{
					identifiers.push_back(lexeme);
				}
				idCompare = 0;
			}
		}
		lexeme.clear(); //clears string after it comes back from function
	}while(myToke != endToke);

	for(i = 0; i < identifiers.size()-1; i++) //arranges identifiers alphabetically
	{
		for(int j = i; j < identifiers.size(); j++)
		{
			if(identifiers[i] > identifiers[j])
			{
				swap(identifiers[i], identifiers[j]);
			}
		}
	}


	for(i = 0; i < list.size(); i++) //counts number of instances of each token
	{
		if(list[i] == 0)
			reference[id]++;
		if(list[i] == 1)
			reference[integer]++;
		if(list[i] == 2)
			reference[string]++;
		if(list[i] == 3)
			reference[plus]++;
		if(list[i] == 4)
			reference[minus]++;
		if(list[i] == 5)
			reference[star]++;
		if(list[i] == 6)
			reference[slash]++;
		if(list[i] == 7)
			reference[set]++;
		if(list[i] == 8)
			reference[print]++;
		if(list[i] == 9)
			reference[sc]++;
	}

	if(reference[id] != 0) //print scheme
		cout << "Identifier:" << reference[id] << endl;
	if(reference[integer] != 0)
		cout << "Integer constant:" << reference[integer] << endl;
	if(reference[string] != 0)
		cout << "Quoted string:" << reference[string] << endl;
	if(reference[plus] != 0)
		cout << "+ operator:" << reference[plus] << endl;
	if(reference[minus] != 0)
		cout << "- operator:" << reference[minus] << endl;
	if(reference[star] != 0)
		cout << "* operator:" << reference[star] << endl;
	if(reference[slash] != 0)
		cout << "/ operator:" << reference[slash] << endl;
	if(reference[set] != 0)
		cout << "set keyword:" << reference[set] << endl;
	if(reference[print] != 0)
		cout << "print keyword:" << reference[print] << endl;
	if(reference[sc] != 0)
		cout << "semicolon:" << reference[sc] << endl;
	if(!identifiers.empty())
	{
		cout << endl << "List of identifiers: " << identifiers[0];
		for(i = 1; i < identifiers.size(); i++)
		{
			cout << ", " << identifiers[i];
		}
	}
	cout << endl; //adds blank line at end of print

	return 0;
}

