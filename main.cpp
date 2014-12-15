#include <stdlib.h>
#include <iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
using namespace std;

#define BEAMSIZE 1024

class MainData
{
	public:
	int antennanum;
	int stationnum;
	vector <vector<int> > antenna;
	vector <vector<int> > station;	 
	//vector<bool> isantenna;	
};

/*
class Result
{
	public:
	vector<int> union_result;
	vector<int> intersect_result;
	void add_new (int new_antenna);

//	vector<int> station_result;
	int station_result;

//	vector<int> antenna_result;
};
*/


class Result
{
	public:		
	int size;
	vector<int> station_status;
	void add_new (int new_antenna);
	Result(){
		size=0;
	}
};


/****************Greedy 1 data structure********************/
class antenna_density
{
	public:
	int id;
	double density;
};

struct antenna_density_operator 
{
	bool operator () (antenna_density a, antenna_density b) {
		return a.density < b.density;	
	}
}operator_object;

/*********************************************/

/*****************Greedy 3 data structure********************/
// the state include the result status and the antennas which have been included
struct state {
	Result result;
	vector<int> antenna_state;

};


// compare which state is better
struct state_operator {
	bool operator () (state a, state b) {
		return a.result.size > b.result.size;
	}

} state_operator_object;


// compare the size 
struct antenna_operator {
	bool operator () (vector<int> a, vector<int> b) {
		return a.size() > b.size();
	}
} antenna_operator_object;


/************************************************************/






void input_from_file(MainData &data);
MainData data;
int main(){
	input_from_file(data);

//	Result result;
	//exit(1);
	//cout<<"aa"<<data.stationnum<<endl;
	
//	result.station_status.resize(data.stationnum,0);
//	result.add_new(0);
//	result.add_new(1);
//	result.add_new(2);
//	result.add_new(3);
//	for(int i=0 ; i < data.stationnum ; i++){
//		cout<<result
//	}
	
//	cout << "size: " << result.size << endl;
//	cout << "intersect size: " << result.intersect_result.size() << endl;




/*	for(int i=0; i<data.station.size();i++){
		cout<<data.station[i].size()<<endl;
	}
*/	



/*********************Greedy 1 algorithm****************************/
/*
	vector<antenna_density> density (data.antennanum);
	for(int i=0; i<data.antennanum ; i++){
		int sum = 0;
		for (int j = 0; j < data.antenna[i].size(); j++) {
			sum += data.station[data.antenna[i][j]].size();
		}
		antenna_density temp;
		temp.id = i;
		temp.density = (double)sum / (double)data.antenna[i].size();
		density[i] = temp;
	//	cout<<sum<<endl;
	}

	sort(density.begin(), density.end(), operator_object);
//	for (int i = 0; i < density.size(); i++){
//		cout << density[i].id << ":" << density[i].density << endl;	
//	}	
	
	int start = 0;	
	while (start < data.antenna.size()) {
		Result temp = result;
		temp.add_new(density[start].id);
		if (temp.station_result.size() < result.station_result.size()) {
			break;
		}
		temp.antenna_result.push_back(density[start].id);
		result = temp;
		start++;
	}

	for (int i = 0; i < result.antenna_result.size(); i++) {
		cout << result.antenna_result[i] << endl;	
	}

	cout << "Total station: " << result.station_result.size() << endl;
*/
/***************************************************************/


/*********************Greedy 2 algorithm****************************/
/*
	int initial=0;
	result.add_new(initial);	
	data.antenna[initial].clear();	

	int Start=0;
	while(Start<data.antenna.size()){
		Result local_result=result;
		int solution=-1;
		int maxlength=result.station_result.size();
		int templength=0;
		for(int i=0; i<data.antenna.size();i++){
			local_result.add_new(i);
			templength=local_result.station_result.size();
			if(templength > maxlength){
				solution=i;
				maxlength=templength;
			}
			local_result = result;
		}
		cout<<"station: "<<solution<<endl;
		cout<<"size: "<<result.station_result.size()<<endl;
		if(solution == -1)
			break;
		else{
			result.add_new(solution);
			result.antenna_result.push_back(solution);
			data.antenna[solution].clear();
			Start++;
		}
	}

	for (int i = 0; i < result.antenna_result.size(); i++) {
		cout << result.antenna_result[i] << endl;	
	}
	cout << "Total station: " << result.station_result.size() << endl;
	
	*/
/***************************************************************/


/*****************************Beam search*****************************/

	// record the current sub solution, if the solution becomes bigger than the decided size n, find the best solution of n, sort	
	// consider n = 16 first


	// first sort antenna
	sort(data.antenna.begin(), data.antenna.end(), antenna_operator_object);
/*	for (int i = 0; i < data.antenna.size(); i++) {
		cout << "size " << data.antenna[i].size() << endl;
	} 
*/	
/*
	vector<antenna_density> density (data.antennanum);
	for(int i=0; i<data.antennanum ; i++){
		int sum = 0;
		for (int j = 0; j < data.antenna[i].size(); j++) {
			sum += data.station[data.antenna[i][j]].size();
		}
		antenna_density temp;
		temp.id = i;
		temp.density = (double)sum / (double)data.antenna[i].size();
		density[i] = temp;
	//	cout<<sum<<endl;
	}
	sort(density.begin(), density.end(), operator_object);
*/	
	
	vector<state> state_set(BEAMSIZE * 2);
	// initialize
	for (int i = 0; i < BEAMSIZE * 2; i++) {
		state_set[i].result.station_status.resize(data.stationnum,0);
	}
	
	
	// first handle the first one
//	state_set[1].result.add_new(density[0].id);	
	state_set[1].result.add_new(0);
	for (int i = 1; i < 10; i++) {
		// if no more antenna
		if (i == data.antennanum) 
			break;
			
		int base = 1 << i;
		for (int j = base; j < 2 * base; j++) {
			state_set[j] = state_set[j - base];
//			state_set[j].result.add_new(density[i].id);
			state_set[j].result.add_new(i);
		}
	}
	
	// if the size is not bigger than 4
	if (data.antennanum < 5) {
		int sol_size = 1 << data.antennanum;
		sort(state_set.begin(), state_set.begin() + sol_size, state_operator_object);
		cout << state_set[0].result.size << endl;
	}
	
	for (int i = 10; i < data.antennanum; i++) {
		// try to copy first 16 to last 16 and then add the current antenna
		for (int j = 0; j < BEAMSIZE; j++) {
			state_set[j+BEAMSIZE] = state_set[j];
//			state_set[j+BEAMSIZE].result.add_new(density[i].id);
			state_set[j].result.add_new(i);
		}
		
		// sort the current state_set
		sort(state_set.begin(), state_set.end(), state_operator_object);

		/***************************************************************
		**********if include randomization, put here *******************
		*****************************************************************/
//		int gap = 0;
		for (int i = 0; i < 1024; i=i+16) {
			
			state_set[i] = state_set[i+BEAMSIZE];
//			gap = gap + 32;
		}
		
//		cout << "current sort: " ;
//		for (int j = 0; j < BEAMSIZE * 2; j++) {
//			cout << state_set[j].result.size << "->";
//		}
//		cout << endl; 
		
	}
	
	cout << state_set[0].result.size << endl;
	
	
	
	
	return 0;		
}




void input_from_file(MainData &data)
{
  	ifstream myfile ("test4.dat");
  	if (myfile.is_open()){
		myfile>>data.antennanum>>data.stationnum;
		data.antenna.resize(data.antennanum);
		data.station.resize(data.stationnum);
		string line;
		getline(myfile,line);
    	//while ( getline (myfile,line) )
		for(int i=0; i<data.antennanum;i++){
			getline (myfile,line);
			//cout<<line<<"\n";
			string temp;
			stringstream ss;
			ss<<line;
			ss>>temp;
			while(ss>>temp){			
				int tempp=atoi(temp.c_str());
				data.antenna[i].push_back(tempp);
				data.station[tempp].push_back(i);
			}
	    }	
    	myfile.close();
  	}
}


void Result::add_new(int new_antenna) {
	for(int i=0; i< data.antenna[new_antenna].size();i++){
		station_status[data.antenna[new_antenna][i]]++;
		if(station_status[data.antenna[new_antenna][i]]==1)
			size++;
		if(station_status[data.antenna[new_antenna][i]]==2)
			size--;
	}
}




/*
void Result::add_new(int new_antenna) {
	
	// the current antenna 
	vector<int> current_antenna = data.antenna[new_antenna];


	

	// union_old intersects with new antenna
	vector<int> intersect_temp(current_antenna.size());
	vector<int> :: iterator it = set_intersection(union_result.begin(), union_result.end(), current_antenna.begin(), current_antenna.end(), intersect_temp.begin());
	intersect_temp.resize(it - intersect_temp.begin());

	// intersect_old union with the previous result
//	vector<int> intersect_new(intersect_result.size() + intersect_temp.size());
	intersect_result.resize(intersect_result.size() + intersect_temp.size());
	
	it = set_union(intersect_result.begin(), intersect_result.end(), intersect_temp.begin(), intersect_temp.end(), intersect_result.begin());
	intersect_result.resize(it - intersect_result.begin());


	// union_old union with new antenna
//	vector<int> union_new(union_result.size() + current_antenna.size());
	union_result.resize(union_result.size() + current_antenna.size());
	it = set_union(union_result.begin(), union_result.end(), current_antenna.begin(), current_antenna.end(), union_result.begin());
	union_result.resize(it - union_result.begin());

	//refresh
//	union_result = union_new;
//	intersect_result = intersect_new;
	
	// refresh final result
//	station_result.clear();
//	station_result.resize(union_new.size());
//	it = set_difference(union_result.begin(), union_result.end(), intersect_result.begin(), intersect_result.end(), station_result.begin());
//	station_result.resize(it - station_result.begin());
	station_result = union_result.size() - intersect_result.size();
}	
*/

