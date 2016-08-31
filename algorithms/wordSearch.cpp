#include <iostream>
#include <fstream>
#include <unordered_map>
#include <map>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

struct wordCount{
	string word;
	int count;
	map<int, bool> docs;

	void printDocs(){
		for(map<int, bool>::iterator i = docs.begin(); i != docs.end(); i++){
			if(i->second == true) cout << i->first << " ";
		}cout <<  endl;
	}

	bool operator<(const wordCount& a) const{
		if(count == a.count) return this->word < a.word;
		return count > a.count;
	}

	void printNot(string word2);
	void printUnion(string word2);
	void printIntersection(string word2);
};

unordered_map<string, wordCount*> words;

void addWord(string word, string fileName){
	size_t l = fileName.find("/");
	size_t r = fileName.find(".txt");
	int file = atoi((fileName.substr(l+1,r-l-1)).c_str());
	if(words[word] == NULL){
		words[word] = new wordCount;
		words[word]->word = word;
		words[word]->count = 1;
		words[word]->docs[file] = true;
	}
	else{
		words[word]->count++;
		words[word]->docs[file] = true;
	}
}

bool compare(const wordCount* a, const wordCount* b){
	return *a < *b;
}

void wordCount::printUnion(string word2){
	map<int, bool> docs;
	for(map<int, bool>::iterator i = (this->docs).begin(); i != (this->docs).end(); i++){
		docs[i->first] = i->second;
	}
	for(map<int, bool>::iterator i = (words[word2]->docs).begin(); i != (words[word2]->docs).end(); i++){
		docs[i->first] = docs[i->first] || i->second;
	}
	for(map<int, bool>::iterator i = docs.begin(); i != docs.end(); i++){
		if(i->second == true) cout << i->first << " ";
	}cout <<  endl;
}

void wordCount::printIntersection(string word2){
	map<int, bool> docs;
	for(map<int, bool>::iterator i = (this->docs).begin(); i != (this->docs).end(); i++){
		docs[i->first] = i->second;
	}	
	for(map<int, bool>::iterator i = (words[word2]->docs).begin(); i != (words[word2]->docs).end(); i++){
		if(docs[i->first] && i->second) cout << i->first << " ";
	}cout << endl;
}

void wordCount::printNot(string word2){
	map<int, bool> docs;
	for(map<int, bool>::iterator i = (this->docs).begin(); i != (this->docs).end(); i++){
		docs[i->first] = i->second;
	}
	for(map<int, bool>::iterator i = (words[word2]->docs).begin(); i != (words[word2]->docs).end(); i++){
		if(docs[i->first] == true && i->second == true) docs[i->first] = false;
	}
	for(map<int, bool>::iterator i = docs.begin(); i != docs.end(); i++){
		if(i->second == true) cout << i->first << " ";
	}cout <<  endl;
}

int main(){
	int k,q,m; cin >> k >> q >> m;

	for(int i=0; i!=k; i++){
		string file; cin >> file;
		ifstream fin; fin.open(file);

		string word;
		while(fin >> word){
			addWord(word, file);
		}
		char temp; cin >> temp;
	}

	vector<wordCount*> counts;
	for(unordered_map<string, wordCount*>::iterator i = words.begin(); i != words.end(); ++i){
		counts.push_back(i->second);
	}
	sort(counts.begin(), counts.end(), compare);

	for(size_t i = 0; i != m; i++) cout << counts[i]->count << " " << counts[i]->word << endl;
	cout << "$\n";
	for(int i=0; i!=q; i++){
		string word1, query, word2;
		cin >> word1 >> query;
		if(query == "ONLY"){
			if(words[word1] == NULL) continue;
			words[word1]->printDocs();
			cout << "$\n";
		}
		else if(query == "OR"){
			if(words[word1] == NULL) continue;
			cin >> word2;
			if(words[word2] == NULL) continue;
			words[word1]->printUnion(word2);
			cout << "$\n";
		}
		else if(query == "AND"){
			if(words[word1] == NULL) continue;
			cin >> word2;
			if(words[word2] == NULL) continue;
			words[word1]->printIntersection(word2);
			cout << "$\n";
		}
		else if(query == "EXCEPT"){
			if(words[word1] == NULL) continue;
			cin >> word2;
			if(words[word2] == NULL) continue;
			words[word1]->printNot(word2);
			cout << "$\n";
		}
	}
}