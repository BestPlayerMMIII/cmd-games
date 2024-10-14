#include<iostream>
#include<string>
#include<vector>
#include<conio.h>
#include<fstream>
#include<ctime>
#include<cstdlib>

using namespace std;


class Hangman
{
private:
	vector<string> vocabulary;
	bool GameOver;
	string toFind;
	vector<bool> toFind_found;
	int errors;
	bool tried[26];	 //{/*A*/false,/*B*/false,/*C*/false,/*D*/false,/*E*/false,			// tried[n] when n is
					 ///*F*/false,/*G*/false,/*H*/false,/*I*/false,/*J*/false,			// (char*maiusc*-65)
					 ///*K*/false,/*L*/false,/*M*/false,/*N*/false,/*O*/false,
					 ///*P*/false,/*Q*/false,/*R*/false,/*S*/false,/*T*/false,
					 ///*U*/false,/*V*/false,/*W*/false,/*X*/false,/*Y*/false,/*Z*/false}
	
public:
	
	Hangman(){
		for(int i=0; i<26; i++){
			this->tried[i] = false;
		}
		this->initVoc();
		this->GameOver = this->selectWord();
		this->errors = 0;
	}
	
	bool selectWord()
	{
		int r, s = this->vocabulary.size();
		if(s==0) return true;
		r = rand()%s;
		this->toFind = this->vocabulary.at(r);
		for(int i=0; i<this->toFind.length(); i++){
			this->toFind_found.push_back(!isalpha(this->toFind.at(i)));
		} this->toFind_found.at(0) = true;
		return false;
	}
	
	void initVoc()
	{
		ifstream f;
		char ch;
		string s("");
		f.open("vocabulary.txt");
		if(!f.is_open()) return;
		while(true){
			f.get(ch);
			if(f.eof()) break;
			if((ch==';')||(ch=='\n')){
				if(s.length()>0)
					this->vocabulary.push_back(s);
				s = "";
			} else {
				if(islower(ch))
					ch-=32;
				s.append(1,ch);
			}
		}
		if(s.length()>0) this->vocabulary.push_back(s);
		f.close();
	}
	
	void view_man(int errs)
	{
	system("CLS");
	cout<<"    ________"<<endl;
	cout<<"    |  "; if(errs>0) cout<<"     O     "; cout<<endl;
	cout<<"    |  "; if(errs>2) cout<<"  ---"; else cout<<"     "; if(errs>1) cout<<"|"; if(errs>3) cout<<"---  "; cout<<endl;
	cout<<"    |  "; if(errs>4) cout<<"    /"; if(errs>5) cout<<" \\    "; cout<<endl;
	cout<<"    |  "; if(errs>4) cout<<"   / "; if(errs>5) cout<<"  \\    "; cout<<endl;
	cout<<"    |  "<<endl;
	cout<<"  __|__"<<endl;
	}
	
	void showWord()
	{
		cout<<"\n ";
		for(int i=0; i<this->toFind.length(); i++){
			if(this->toFind_found.at(i))
				cout<<this->toFind.at(i)<<" ";
			else
				cout<<"_ ";
		}
		cout<<endl;
	}
	
	void showTried()
	{
		cout<<"\n  LETTERS TRIED:\n ";
		for(int i=0; i<26; i++){
			if(this->tried[i])
				cout<<char(i+65)<<"; ";
		}
		cout<<"\b\b \n - - - - -\n";
	}
	
	void updateFound(char ch)
	{
		int i, l=this->toFind.length();
		bool error = true;
		for(i=0; i<l; i++){
			if(this->toFind.at(i)==ch){
				this->toFind_found.at(i) = true;
				error = false;
			}
		}
		if(error)
			this->errors+=1;
	}
	
	void showScreen()
	{
		this->view_man(this->errors);
		this->showWord();
		this->showTried();
	}
	
	void makeTry()
	{
		this->showScreen();
		cout<<"\n >>  ";
		char ch = 13, ltr;
		bool force = true;
		do{
			ltr = ch;
			ch = getch();
			if((ch==13)&&(!force))
				break;
			cout<<"\b ";
			if(isalpha(ch)){
				force = false;
				if(islower(ch))
					ch-=32;
				cout<<"\b"<<ch;
			} else force=true;
		}while(true);
		if(this->tried[ltr-65]) return;
		this->tried[ltr-65] = true;
		this->updateFound(ltr);
	}
	
	bool hasWon()
	{
		int i, s=this->toFind_found.size();
		for(i=0; i<s; i++){
			if(!this->toFind_found.at(i))
				return false;
		}
		return true;
	}
	
	void play()
	{
		/*for(int i=0; i<this->vocabulary.size(); i++){
			cout<<this->vocabulary.at(i)<<endl;
		}
		return;*/
		if(this->GameOver&&(this->errors<6)){
			cout<<"Creare un file 'vocabulary.txt' e immettere parole separate da ';' o da '\\n'";
			return;
		}
		while(true){
			this->GameOver = (this->errors>5);
			if(this->GameOver) break;
			this->makeTry();
			if(this->hasWon()) break;
		}
		this->showScreen();
		cout<<"\n";
	}
	
	string get_word(){ return this->toFind; }
	bool isGameOver(){ return this->GameOver; }
	
};

int main()
{
	srand(time(NULL));
	Hangman game;
	game.play();
	if(game.isGameOver())
		cout<<"\n GAME OVER!\n\nThe hidden word was... "<<game.get_word()<<" !\n";
	else
		cout<<"\n EXACTLY! You survived!\n";
	system("PAUSE");
	return 0;
}
