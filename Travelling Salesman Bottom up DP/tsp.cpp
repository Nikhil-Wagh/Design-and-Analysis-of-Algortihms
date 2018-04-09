#include "bits/stdc++.h"
using namespace std;
int compareSets(std::vector<int> a, std::vector<int> b){
	return a.size() < b.size();
}

std::vector<int> citiesNotInSet(std::vector<int> _set, int n){
	std::vector<int> v;
	for(int i = 1 ; i < n ; i++){ // Because 0 is the starting state
		if(find(_set.begin(), _set.end(), i) == _set.end()){
			v.push_back(i);
		}
	}
	return v;
}


int main(){
	// cout << "Traveling Salesman Problem" << endl;
	int n_cities;
	cout << "Enter number of cities :: ";
	cin >> n_cities;

	//Generating sets 
	std::vector< std::vector<int> > sets;

	int n_sets = pow(2, n_cities - 1);
	for(int i = 0 ; i < n_sets ; i++){
		std::vector<int> _set;
		for(int j = 0 ; j < n_cities ; j++){
			if(i & (1 << j)){
				_set.push_back(j + 1);
			}
		}
		sets.push_back(_set);
	}

	sort(sets.begin(), sets.end(), compareSets);
	// Uncomment following to see sets
	// cout << "Sets" << endl;
	// for(int i = 0 ; i < sets.size() ; i++){
	// 	cout << sets[i].size() <<  " :: ";
	// 	for(int j = 0 ; j < sets[i].size() ; j++){
	// 		cout << sets[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }

	int e;
	while(true){
		cout << "Enter the number of edges :: ";
		cin >> e; 
		if(e > 0)
			break;
		cout << "Incorrect Input" << endl;
	}

	cout << "Enter the edges with thier weights. ( should be > 0)" << endl;
	int adj[n_cities + 1][n_cities + 1];
	for(int i = 0 ; i < n_cities ; i++){
		for(int j = 0 ; j < n_cities ; j++)
			adj[i][j] = INT_MAX;
	}
	//input
	for(int i = 0 ; i < e ; i++){
		int x, y, z;
		cin >> x >> y >> z;
		x--;y--;

		if(adj[x][y] != INT_MAX){
			cout << "Edge already present." << endl; i--; 
		}
		else if (x == y){
			cout << "Cannot contain self loop" << endl; i--;
		}
		else if((x < 0) || (x > n_cities) || (y < 0) || (y > n_cities)){
			cout << "Incorrect vertices" << endl; i--; 
		}
		else if (z <= 0){
			cout << "Weight Incorrect" << endl; i--; 
		}
		else
		{
			adj[x][y] = z;
		}
	}

	cout << endl;

	int start = 0, si = -1;
	map< pair < vector<int> , int>, pair <int, int> > calculatedCost;

	for(int i = 0 ; i < sets.size() ; i++){
		std::vector<int> _cities; //calculate for these cities 0 -> [1, {2, 3}] => 1 is in the _cities
		_cities = citiesNotInSet(sets[i], n_cities);
		
		if(!(_cities.size()))
			_cities.push_back(start);

		if(sets[i].size()!=si){
			si=sets[i].size();
			cout << endl << "|S| :: " << sets[i].size() << endl;
		}

		for(int j = 0 ; j < _cities.size() ; j++){
			if(!(sets[i].size())){
				cout << "Cost [" << _cities[j] + 1 << ", { } ] = ";
				if(adj[_cities[j]][start] != INT_MAX){
					pair <vector <int>, int > v;
					v = make_pair(sets[i], _cities[j]);
					calculatedCost[v] = make_pair(adj[_cities[j]][start], start);
					cout << calculatedCost[v].first << ", Parent :: " << start + 1 << endl;
				}
				else{
					cout << "No Path, Parent :: -1" << endl;
				}
			}
			else{
				int min_cost = INT_MAX, parent = -1;
				for(int k = 0 ; k < sets[i].size() ; k++){
					std::vector<int> v;
					v = sets[i];

					// cout << "City number :: " << _cities[j] << " Set::" << endl;
					// for(int x = 0 ; x < v.size() ; x++)
					// 	cout << v[x] << " ";
					// cout << endl;

					v.erase(v.begin() + k);

					pair < vector<int>, int > temp;
					temp = make_pair(v, sets[i][k]);

					if(adj[_cities[j]][sets[i][k]] != INT_MAX && calculatedCost.count(temp)){
						int current_cost = calculatedCost[temp].first + adj[_cities[j]][sets[i][k]];
						if(min_cost > current_cost){
							min_cost = current_cost;
							parent = sets[i][k];
						}
					}
				}
				cout << "Cost [" << _cities[j] + 1 << ", { ";
				for(int k = 0 ; k < sets[i].size() ; k++){
					cout << sets[i][k] + 1 << " ";
				}
				cout << "}] = ";
				if(min_cost != INT_MAX){
					pair <vector<int>, int > v;
					v = make_pair(sets[i], _cities[j]);
					calculatedCost[v] = make_pair(min_cost, parent);
					cout << calculatedCost[v].first << ", Parent :: " << calculatedCost[v].second + 1 << endl;	
				}
				else{
					cout << "No Path, Parent :: -1" << endl;
				}
			}
		}
	}
	cout << endl;

	std::vector<int> v;
	v = citiesNotInSet(v, n_cities);

	if(calculatedCost.count(make_pair(v, start))){
		int parent = calculatedCost[make_pair(v, start)].second;
		cout << "MIN COST :: " << calculatedCost[make_pair(v, start)].first << endl;
		cout << start + 1;
		while(true){
			cout << " -> " << parent + 1;
			if(v.size())
				v.erase(find(v.begin(), v.end(), parent));
			if(parent == start)
				break;
			parent = calculatedCost[make_pair(v, parent)].second;
		}
		cout << endl;
	}
	else{
		cout << "No Path Possible" << endl;
	}
	return 0;
}		



/*

4
0 1 15 6
2 0 7 3
9 6 0 12
10 4 8 0


4
12
1 2 1
1 3 15
1 4 6
2 1 2
2 3 7
2 4 3
3 1 9
3 2 6
3 4 12
4 1 10 
4 2 4
4 3 8

1 2 4 3 1

*/