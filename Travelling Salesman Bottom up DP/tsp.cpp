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
	// cout << "OLD : ";
	// for(int i = 0 ; i < _set.size() ; i++)
	// 	cout << _set[i] << " ";
	// cout << endl;
	// cout << "NEW : "; 
	// for(int i = 0 ; i < v.size() ; i++)
	// 	cout << v[i] << " ";
	// cout << endl << endl;
	return v;
}

int main(){
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


	cout << "Enter adjacency matrix" << endl;
	int adj[n_cities][n_cities];
	for(int i = 0 ; i < n_cities ; i++){
		for(int j = 0 ; j < n_cities ; j++){
			cin >> adj[i][j];
		}
	}

	int start = 0;
	map< pair < vector<int> , int>, pair <int, int> > calculatedCost;

	for(int i = 0 ; i < sets.size() ; i++){
		std::vector<int> _cities; //calculate for these cities 0 -> [1, {2, 3}] => 1 is in the _cities
		_cities = citiesNotInSet(sets[i], n_cities);
		
		if(!(_cities.size()))
			_cities.push_back(0);

		for(int j = 0 ; j < _cities.size() ; j++){
			if(!(sets[i].size())){
				calculatedCost[make_pair(sets[i], _cities[j])] = make_pair(adj[start][_cities[j]], start);
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

					int current_cost = calculatedCost[temp].first + adj[sets[i][k]][_cities[j]];
					if(min_cost > current_cost){
						min_cost = current_cost;
						parent = sets[i][k];
					}
				}
				cout << "Cost [" << _cities[j] << ", { ";
				for(int k = 0 ; k < sets[i].size() ; k++){
					cout << sets[i][k] << " ";
				}
				cout << "}] = " << min_cost << ", Parent :: " << calculatedCost[make_pair(sets[i], _cities[j])].second << endl;

				calculatedCost[make_pair(sets[i], _cities[j])] = make_pair(min_cost, parent);
			}
		}
	}


	std::vector<int> v;
	v = citiesNotInSet(v, n_cities);

	int parent = calculatedCost[make_pair(v, 0)].second;
	// cout << calculatedCost[make_pair(v, 0)].first << " " << parent << endl;

	stack <int> s;
	for(int i = 0 ; i < n_cities ; i++){
		s.push(parent);
		//cout << parent << " ";
		if(find(v.begin(), v.end(), parent) != v.end())
			v.erase(find(v.begin(), v.end(), parent));
		parent = calculatedCost[make_pair(v, parent)].second;
	}

	while(!s.empty()){
		cout << s.top() << " -> ";
		s.pop();  
	}
	cout << 0 << endl;
	return 0;
}		



/*

4
0 1 15 6
2 0 7 3
9 6 0 12
10 4 8 0

*/