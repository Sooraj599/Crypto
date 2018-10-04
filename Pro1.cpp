#include <iostream>
#define max 15
using namespace std;
//Defining global variables
int n=23;
int front=-1,rear=-1,lastuser=0;
double genesis;
double endb;

//Defining the User Class
class user{
public :
double balance;
int id;
char password[20];
user() {
balance = 5;
}
};
user db[50];
//The block structure for BlockChain

struct block{
int from;
int to;
int amount;
double hash;
double hashkey;
double prev;
struct block *prevPtr;
};
struct block *firstBlock,*newPtr,*lastBlock;
block transactions[max];
//Hash Function
double hashfunc(int from, int to, int amt){
int number;
number = ((from*to) * (n*n*n) + amt);
return number;
}
//Decrypting the hash using a key
double getKey(int a){
int temp;
for (int i=1;i<a;i++){
temp = a/i;
if (temp%10==0){

return i;
break;
}
}
}
//Some useful functions
int isEqual(char a1[], char a2[]) {
int res = 1;
if (a1[0]=='\0' || a2[0]=='\0'){res=0;}
else{
for (int i = 0 ; a1[i]!= '\0' ; i++) {
if (a1[i]!=a2[i]) {
res = 0;
break;
}
}}
return res;
}
void copy(char a1[],char a2[]){
for (int i=0 ;a1[i]!='\0';i++){
a2[i] = a1[i];
}
}

//Queue functions
void enqueue(block b){
if ((front==0 && rear==max-1) || (front==rear+1)) {
cout<<"Too many transactions!";
return;
}
if (front==-1) {
front = 0;
rear=0;
}
else {
if (rear==max-1) {rear=0;}
else {rear++;}
}
transactions[rear]=b;
}
block dequeue(){
block temp;
if (front==rear) {
temp = transactions[front];
front = -1;
rear = -1;
}
else {
if (front == max-1) {

temp = transactions[front];
front = 0;
}
else {
temp = transactions[front];
front++;
}
}
return temp;
}
//Mining the blockchain
void mine(int id) {
if (front==-1) {cout<<"No pending transactions!";}
else{
block curBlock;
curBlock = dequeue();

if (db[curBlock.to].id=='\0' || db[curBlock.from].balance-
curBlock.amount<0 || curBlock.from == curBlock.to ) {

cout << "You have detected an invalid transaction!";}
else {
double curHash = curBlock.hash;
int k = getKey(curBlock.hash);
curBlock.hashkey = k;
db[curBlock.from].balance -= curBlock.amount;
db[curBlock.to].balance += curBlock.amount;

newPtr = new block;
*newPtr = curBlock;
if (firstBlock==NULL && lastBlock==NULL){
firstBlock=newPtr;
lastBlock=newPtr;
endb=curHash;
genesis=curHash;
}
else {
curBlock.prevPtr=lastBlock;
lastBlock=newPtr;
curBlock.prev=endb;
endb=curBlock.hash;
}
cout << "\nYou have authenticated a transaction. You have successfully earned 0.25 LTC"<<endl;
}}
n++;
db[id].balance += 0.25;
}

void sendCoin(int from,int to,int amount) {
if (to>lastuser) {cout<<"User does not exist!";}
else{
block newBlock;

newBlock.from=from;
newBlock.to=to;
newBlock.amount=amount;
newBlock.hash = hashfunc(from,to,amount);
enqueue(newBlock);
cout << "Your transaction has successfully been enqueued!";
}
}
//Main Driver function
int main(){
int a1,cur,a2;
char curPass[20];
while(1){
cout << "\n*******WELCOME TO LitCoin*******" <<
endl;
cout << "1. Login\n2.Sign Up\n";
cin >> a1;
switch(a1) {
case 1 :
cout << "Enter your wallet ID :";
cin >> cur;
cout << "Enter your password: ";
cin >> curPass;

if (isEqual(db[cur].password,curPass)) {
int check = 0;
while(1) {
cout << "\n*******************************"
<< endl;
cout << "What would you like to do next? Choose an option:"<<endl;
cout << "1.Send LitCoin\n2.Mine a block\n3.Show balance\n4.Log Out" << endl;
cin >> a2 ;
switch (a2) {
case 1:
int sendto,xamount;
cout << "Enter the walletID of the user you want to send it to :"<<endl;
cin >> sendto;
cout << "Enter the amount of LitCoin you wish to transfer :";
cin>> xamount;
sendCoin(cur,sendto,xamount);
break;
case 2 :
mine(cur);break;
case 3 :

cout << "Your current unmined balance is : " <<
db[cur].balance << "LTC" <<endl;
break;
case 4:
check =1 ;
break;

}
if (check==1) {
break;
}
}
}
else {
cout << "Wrong username or Password!";
}
break;
case 2 :
char newPass[20];
lastuser++;
db[lastuser].id = lastuser;
cout<<"Hello, thank you for signing up! Your WalletID is "<<db[lastuser].id<<endl;

cout << "Enter a desired password: "<< endl;
cin>> newPass;
copy(newPass,db[lastuser].password);
cout << "You have successfully registered for LitCoin."<<endl;
cout<< "Your current balance is "<<db[lastuser].balance;
break;
default : cout << "Please enter a valid option!"<<endl;
break;
}
}
}
