#include<bits/stdc++.h>

typedef long long ll;
typedef std::pair<int,int> pii;

#define For(i,a) for(int i=0;i<(int)a;i++)
#define pb push_back



using namespace std;


//Define our chocolate bar

const int W = 5;
const int L = 12;
const int T = 6;
const pii bad_tr[] = {{11,4},{2,4},{10,2}};

//Find our bad peaces
bool is_bad(int x,int y){
	for(int i=0;i<3;i++){
		if(x==bad_tr[i].first && y==bad_tr[i].second) return 1;
	}
	return 0;
}

//Print our board
int board[L][W];
void print(){

	cout<<"---------------------\n";
	for(int i=0;i<L;i++){
		for(int j=0;j<W;j++){
			if(board[i][j]==0){
				if(is_bad(i,j)) cout<<"@";
				else cout<<"0";
			}
			else{
				cout<<" ";

							}
		}
		cout<<endl;
	}
	cout<<"---------------------\n";

}

//Our Valid Movements
bool is_valid_move(const int a[L][W],int x,int y){
	for(int i=x;i>=0;i--){
		for(int j=y;j>=0;j--){
			if(a[i][j]==0) return 1;
		}
	}
	return 0;
}

//User & AI Make Moves
int make_move(int a[L][W],int x,int y,int turn){
	if(!is_valid_move(a,x,y)) return 0;
	for(int i=0;i<=x;i++){
		for(int j=0;j<=y;j++){
			if(a[i][j]==0) a[i][j] = turn;
		}
	}
	return 1;
}

//Shows all the Possible Moves
vector<pii> get_moves(int a[L][W]){
	vector<pii> tmp;
	for(int i=0;i<L;i++){
		for(int j=0;j<W;j++){
			if(is_valid_move(a,i,j))
				tmp.pb({i,j});
		}
	}
	return tmp;
}

//When our Game is finished?
bool is_finished(const int a[L][W]){
	for(int i=0;i<L;i++){
		for(int j=0;j<W;j++){
			if(a[i][j]==0) return 0;
		}
	}
	return 1;
}

//Counts the number of eaten peaces
pii count(const int a[L][W]){
	int eat_num = 0;
	int bad_num = 0;
	for(int i=0;i<L;i++){
		for(int j=0;j<W;j++){
			if(a[i][j]==2){
				if(is_bad(i,j)) bad_num++;
				else eat_num++;
			}
		}
	}
	return {eat_num,bad_num};
}

//Copies the Chocolate Bar
void copy(int a[L][W],int b[L][W]){
	for(int i=0;i<L;i++){
		for(int j=0;j<W;j++){
			b[i][j] = a[i][j];
		}
	}
}

pii make_max(int a[L][W],int times=T);
pii make_min(int a[L][W],int times=T);

// All the options whit the most right peaces and less bad peaces
// uses Min_Max foe Min peaces
pii make_max(int a[L][W],int times){
	if(is_finished(a) || times==0){
		return count(a);
	}
	pii best = {1e8,1e8};
	int b[L][W];
	auto moves = get_moves(a);
	for(pii x:moves){
		copy(a,b);
		make_move(b,x.first,x.second,2);
		pii tmp = make_min(b,times-1);
		if(tmp.second<best.second){
			best = tmp;
		}
		else if(tmp.second==best.second && tmp.first>best.first){
			best = tmp;
		}
	}
	return best;
}

pii make_min(int a[L][W],int times){
	if(is_finished(a) || times==0){
		return count(a);
	}
	pii best = {-1,-1};
	int b[L][W];
	auto moves = get_moves(a);
	for(pii x:moves){
		copy(a,b);
		make_move(b,x.first,x.second,1);
		pii tmp = make_max(b,times-1);
		if(tmp.second>best.second){
			best = tmp;
		}
		else if(tmp.second==best.second && tmp.first<best.first){
			best = tmp;
		}
	}
	return best;
}

pii ai(int a[L][W],int times=T){
	if(is_finished(a) || times==0){
		return count(a);
	}
	pii best = {1e8,1e8};
	pii best_move;
	int b[L][W];
	auto moves = get_moves(a);
	for(pii x:moves){
		copy(a,b);
		make_move(b,x.first,x.second,2);
		pii tmp = make_min(b,times-1);
		if(tmp.second<best.second){
			best = tmp;
			best_move = x;
		}
		else if(tmp.second==best.second){
			best = tmp;
			best_move = x;
		}
	}
	return best_move;
}

pii get_move_from_user(int a[L][W]){
	print();
	cout<<"Enter Your move (first row then column): ";
	int x,y;


	cin>>x>>y;
	while(!is_valid_move(a,x-1,y-1)){
		cout<<"You Enter wrong move.Try again: ";
		cin>>x>>y;
	}
	return pii{x-1,y-1};
}
int main(){

	int turn = 1;
	while(!is_finished(board)){
		if(turn==1){
			pii user_move = get_move_from_user(board);
			make_move(board,user_move.first,user_move.second,turn);
			print();
		}
		else{
			pii ai_move = ai(board);
			make_move(board,ai_move.first,ai_move.second,turn);
			//print();
		}
		turn = 3-turn;
	}
	pii res = count(board);
	cout<<"I ate "<<res.second<<" bad chocolate but you ate "<<3-res.second<<endl;
	system("pause");
	return 0;
}

