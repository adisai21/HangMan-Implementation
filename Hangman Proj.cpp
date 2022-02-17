#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<time.h>
#include<cstdlib>
using namespace std;
void printmessage(string message, bool printtop=true , bool printbottom=true)    //this is for writing borders for message  ,printtop=true means we want top border for my message
{
	if(printtop)
	{
		cout<<"+---------------------------------+"<<endl;
		cout<<"|";
	}
	else{
		cout<<"|";
	}
	bool front=true;
	for(int i=message.length();i<33;i++)    //33 is maximum number to be displayed , by this way we r displaying the message in the centre of the screen
	{
		if(front)
		{
			message=" "+message;
		}
		else
		{                                     //BY doing this we r making the message to be in centre 
			message=message+" ";
		}
		front=!front;
	}
	cout<<message;                 //typecasting it so that we can display it as string
	if(printbottom)
	{
		cout<<"|"<<endl;
		cout<<"+---------------------------------+"<<endl;
	}
	else{
		cout<<"|"<<endl; 
	}
}
void DrawHangman(int guesscount=0)          //here we put all the boolean variables as false because we dont want any border for any of these
{
	if(guesscount>=1)
	   printmessage("|",false,false);        //here if the user guess it wrong then the hangman will be printed 
	else
		printmessage("",false,false);
	if(guesscount>=2)
	   printmessage("|",false,false);
	else
		printmessage("",false,false);
	if(guesscount>=3)
	   printmessage("o",false,false);
	else
		printmessage("",false,false);
	if(guesscount==4)
	   printmessage("/",false,false);
	if(guesscount==5)
	   printmessage("/|",false,false);
	if(guesscount>=6)
	   printmessage("/|\\",false,false);      //here only the first three will be considered as last one is terminating character
	else
	   printmessage(" ",false,false);
	if(guesscount>=7)
	   printmessage("|",false,false);
	else
		printmessage(" ",false,false);
	if(guesscount==8)
	   printmessage("/",false,false);
	if(guesscount>=9)
	   printmessage("/ \\",false,false);
	else
	   printmessage(" ",false,false);
}
void PrintLetters(string input , char from , char to)                          //prints all the letters, these 2 characters are ranges of letters we will be displaying
{
	string s;
	for(char i=from; i<=to; i++)
	{
	  if(input.find(i)==string::npos)                                            //when we dont find the character 
	  {
	  	s+=i;
	  	s+=" ";
	  }
	  else{
	  	s+=" ";
	  }
	}
	printmessage(s, false, false);
}
void printavailableletters(string taken)
{
	printmessage("Available Letters");
	PrintLetters(taken, 'a', 'm');
	PrintLetters(taken, 'n', 'z');
}
bool printwordcheckwin(string word, string guessed)
{
	bool won=true;
	string s;
	for(int i=0;i<word.length();i++)
	{
		if(guessed.find(word[i])==string::npos)                //word is actual word to be guessed
		{
			won=false;
			s+="_";
		}
		else
		{
			s+=word[i];
			s+=" ";
		}
	}
	printmessage(s, false);
	return won;
}
string loadrandom (string path)
{
	int linecount=0;
	string word;
	vector <string> v;
	ifstream reader(path.c_str());
	if(reader.is_open())                               //check if the file is open
	{
		while(std::getline(reader,word))              //read the word from the file line by line
		   v.push_back(word);
		int randline=rand() % v.size();                 //%v.size to randomise on the size of the vector
		word=v.at(randline);                         //choosing the word from the vector of strings
	    reader.close();	
	}
	return word;
}
int triesleft(string word, string guessed)
{
	int error=0;
	for(int i=0;i<guessed.length();i++)
	{
		if(word.find(guessed[i])==string::npos)
		{
			error++;
		}
	}
	return error;
}
int main()
{
	srand(time(0));
	string guesses;
	string wordtoguess;
	wordtoguess = loadrandom("hangman.txt");
	int tries=0;
	bool win=false;
	do{
		system("cls");
		printmessage(" HANGMAN ");
		DrawHangman(tries);
		printavailableletters(guesses);
		printmessage(" Guess the Word ");
		printwordcheckwin(wordtoguess,guesses);
		
		if(win)
		break;
		
		char x;
		cout<<">";cin>>x;
		if(guesses.find(x)==string::npos)
		guesses+=x;
		
		tries=triesleft(wordtoguess, guesses);
	}while(tries<10);
	getchar();
	return 0;
}
