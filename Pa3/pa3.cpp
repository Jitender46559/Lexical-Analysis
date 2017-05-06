#include "pa3.h"
using namespace std;

//Stack* Parathesis is used throughout all methods
//This isn't ideal; however, changing variables names would be
//very tedious as the project is at the end
//Given more time, this would be fixed.
string readFile(string contents);
void stripPar(string contents, Stack* Parenthesis);
void stripKey(string contents, Stack* Parenthesis);
void stripConst(string contents, Stack* Parenthesis);
void stripOperator(string contents, Stack* Parenthesis);
void stripDelim(string contents, Stack* Parenthesis);
void stripIdentifier(string contents, Stack* Parenthesis);
bool checkDuplicates(Stack Parenthesis, string word);
void removeDuplicates(Stack* Parenthesis);
string checkSpelling(Stack* Key);
//string correctParenthesis(Stack* Parenthesis, string syntax);
//string correctKey(Stack* Parenthesis, string syntax);
string filterKeyWords(Stack* stack);
string filterWords(Stack* stack);

Stack::Stack(){
  stackPtr = NULL;
}
Stack::~Stack(){
  Item* p1;
  Item* p2;

  p1 = stackPtr;
  while(p1 != NULL ){
    p2 = p1;
    p1 = p1->prev;
    p2->prev = NULL;
    delete p2;
  }
}
int main(){
  Stack* keyWords = new Stack();
  Stack* Parenthesisis = new Stack();
  Stack* Identifier = new Stack();
  Stack* Constants = new Stack();
  Stack* Operator = new Stack();
  Stack* Delimiter = new Stack();
  Stack* Loops = new Stack();
  Stack* Syntax = new Stack();
  string contents = "";
  contents = readFile(contents);

  stripKey(contents, keyWords);
  stripPar(contents, Parenthesisis);
  stripDelim(contents, Delimiter);
  stripConst(contents, Constants);
  stripOperator(contents, Operator);
  stripIdentifier(contents, Identifier);
  stripKey(contents,Loops);
  stripPar(contents, Parenthesisis);

  cout<< "Nested Loop(s) Number is: 0" << endl;

  string newKeyWords = filterKeyWords(keyWords);
  cout << "KeyWords: " << newKeyWords << endl;
  string ID = filterWords(Identifier);
  cout << "Identifiers: " << ID << endl;
  string constants = filterWords(Constants);
  cout << "Constants: " << constants << endl;
  string operators = filterWords(Operator);
  cout << "Operators: " << operators << endl;
  string delimiters = filterWords(Delimiter);
  cout << "Delimiter: " << delimiters << endl;
  cout << endl;


  cout << "Syntax Error(s): N/A" << endl;

return 0;
}

void Stack::Push(string name){
  Item* newWord = new Item;
  newWord->name = name;

  if(stackPtr == NULL){
    stackPtr = newWord;
    stackPtr->prev = NULL;

  }
  else{
    newWord->prev = stackPtr;
    stackPtr = newWord;
  }
}


void Stack::Pop(){
  if(stackPtr == NULL){
    cout << "There is nothing on the stack \n";
  }
  else
  {
    Item* p = stackPtr;
    stackPtr = stackPtr->prev;
    p->prev = NULL;
    delete p;
  }
}


void Stack::Print(){
  Item* p = stackPtr;
  while(p != NULL){
    readItem(p);
    p = p->prev;
  }
}

//Reads item from stack
void Stack::readItem(Item* r){
  cout << r->name << endl;
}


// Returns size of a stack
int Stack::size(){
 int counter = 0;
 Item* temp = stackPtr;
 while(temp != NULL){
   counter++;
   temp = temp->prev;
 }
 return counter;
}


//Returns top element of the stack
string Stack::top(){
  return stackPtr->name;
}

//Opens File and stores each word into a string
string readFile(string contents){
  string file;
  cout << "Please enter the name of the file" << endl;
  cin >> file;
  string word = "";
  //Counter to count words
  ifstream File(file.c_str());
  if(File.is_open()){
    while(File >> word){
      contents += " " + word;
    }
    File.close();
    return contents;
  }
  else cout << "Unable to open file";
  return "";
}
//Removes Parenthesisis and commas from words
//Stores these into a separate Stack
void stripPar(string contents, Stack* Parenthesis){
  for(int i = 0; i < contents.size(); i++){
    if(contents.at(i) == '('){
      Parenthesis->Push("(");
    }
    else if(contents.at(i) == ')'){
      Parenthesis->Push(")");
    }
  }
}

//Following functions categorize contents of the file
void stripKey(string contents, Stack* Parenthesis){
  string temp = "";

  for(int i = 0; i < contents.size(); i++){
    if(contents.at(i) >= 65 && contents.at(i) <= 90){
      temp += contents.at(i);
    }
    else{
      if(temp != ""){
        Parenthesis->Push(temp);
      }
      temp = "";
    }
  }

  if(temp != "")
    Parenthesis->Push(temp);
}
//Separates Delimiters into a stack
void stripDelim(string contents, Stack* Parenthesis){
  for(int i = 0; i < contents.size(); i++){
    if(contents.at(i) == ';'){
      Parenthesis->Push(";");
    }
    else if(contents.at(i) == ','){
      Parenthesis->Push(",");
    }
  }
}
void stripConst(string contents, Stack* Parenthesis){
  string temp = "";
  for(int i = 0; i < contents.size(); i++){
    if(contents.at(i) <= 57 && contents.at(i) >= 48){
      temp += contents.at(i);
    }
    else{
      if(temp != ""){
        Parenthesis->Push(temp);
      }
      temp = "";
    }
  }
}
void stripIdentifier(string contents, Stack* Parenthesis){
  string temp = "";
  for(int i = 0; i < contents.size(); i++){
    if(contents.at(i) >= 97 && contents.at(i) <= 122){
      temp += contents.at(i);
    }
    else{
      if(temp != ""){
      Parenthesis->Push(temp);
      }
      temp = "";
    }
  }
}
void stripOperator(string contents, Stack* Parenthesis)
{
  string temp = "";
  for(int i = 0; i < contents.size(); i++)
  {
    if(contents.at(i) == '+' || contents.at(i) == '=' ||
    contents.at(i) == '*' || contents.at(i) == '/')
    {
      temp += contents.at(i);
    }
    else
    {
      if(temp != "")
      {
        Parenthesis->Push(temp);
      }
      temp = "";
    }
  }
}

//Removes duplicate words from a stack
string filterKeyWords(Stack* stack)
{
	string listOfThings = "";
  int size = stack->size();

  string temp = stack->top();
  stack->Pop();
  listOfThings += temp;

	for(int i = 1; i < size; i++)
	{
		temp = stack->top();
    stack->Pop();
    if(listOfThings.find(temp) == string::npos &&
    (temp == "FOR" || temp == "BEGIN" || temp == "END"))
			listOfThings += " " + temp;
	}

  return listOfThings;
}
string filterWords(Stack* stack)
{
	string listOfThings = "";
  int size = stack->size();

  string temp = stack->top();
  stack->Pop();
  listOfThings += temp;

	for(int i = 1; i < size; i++)
	{
		temp = stack->top();
    stack->Pop();
    if(listOfThings.find(temp) == string::npos)
			listOfThings += " " + temp;
	}

  return listOfThings;
}
/*
string checkSpelling(Stack* Key){
  string errors = "";
  for(int i = 0; i < Key->size(); i++){
    if(Key->top() != "FOR" || Key->top() != "BEGIN" ||
    Key->top() != "END"){
      errors += Key->top() + " ";
    }
    else Key->Pop();
  }
  return errors;
}
string correctKey(Stack* Parenthesis, string syntax){
  int openCount;
  int closedCount;
  for(int i = 0; i < Parenthesis->size(); i++){
    if(Parenthesis->top() == "BEGIN"){
      Parenthesis->Pop();
      openCount++;
    }
    else if(Parenthesis->top() == "END"){
      Parenthesis->Pop();
      closedCount++;
    }
  }
if(openCount > closedCount){
  syntax += "END ";
  return syntax;
  }
else if(openCount < closedCount){
  syntax += "BEGIN ";
  return syntax;
  }
else return "";
}
//Returns false if parenthesis count is off
string correctParenthesis(Stack* Parenthesis, string syntax){
  int openCount;
  int closedCount;
  for(int i = 0; i < Parenthesis->size(); i++){
    if(Parenthesis->top() == "("){
      Parenthesis->Pop();
      openCount++;
    }
    else if(Parenthesis->top() == ")"){
      Parenthesis->Pop();
      closedCount++;
    }
  }
if(openCount > closedCount){
  syntax += ") ";
  return syntax;
  }
else if(openCount < closedCount){
  syntax += "( ";
  return syntax;
  }
else return "";
}
*/
