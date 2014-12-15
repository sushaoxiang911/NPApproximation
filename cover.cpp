#include <stdlib.h>
#include <iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<climits>
#include<math.h>
#include<ctime>
using namespace std;



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

class 






class Result
{
	public:		
	int size;
	vector<int> station_status;
	vector<bool> antenna_visited;
	void add_new (int new_antenna);
	void delete_old(int old_antenna);
	Result(int stationnum, int antennanum){
		size=0;
		station_status.resize(stationnum,0);
		antenna_visited.resize(antennanum,1);
	}
};

/****************simulate anealing data structure***********/
class SimulateAnealing
{
	public:
    double temperature = 10000.0;
    double cooling_rate = 0.9999;
   //double cooling_rate = 0.0000000000000000001;
    double absolute_temperature = 8000;
	//0.00001
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
		return a.density > b.density;	
	}
}operator_object;

/*********************************************/



/******************** GA ****************************/
void generate_random_result (Result &result);
void recombination_mutation (Result &result1, Result &result2, vector<Result> &generation, int index);
/***************************************************/


void input_from_file(MainData &data);


MainData data;

int main(){
	input_from_file(data);
	srand(time(0));




//int sumsum = 0;
//for(int nn = 0; nn < 100; nn++) {


	clock_t c_start = clock();



	Result result(data.stationnum, data.antennanum);
	vector<int> antenna_selected;

	//exit(1);
	//cout<<"aa"<<data.stationnum<<endl;
	

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
	for(int i=0; i<data.antennanum;i++){
			result.add_new(i);
	}	
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
	int size=0;	
	while (start < data.antenna.size()) {
		result.delete_old(density[start].id);
		if (result.size < size) {
			result.add_new(density[start].id);
			break;
		}
		antenna_selected.push_back(density[start].id);
		size = result.size;
		start++;
		cout<<"aa: "<<size;
	}
	cout<< antenna_selected.size();
	for(int i = 0; i < antenna_selected.size(); i++) {
		cout<<" " << antenna_selected[i];	
	}
	cout<<endl;
	cout<<"size: "<<result.size << endl;
*/
/***************************************************************/

/*********************Greedy 1&2  algorithm****************************/
/*
	vector<bool> antenna_visited(data.antennanum,1);
	//vector<int> deleted_antenna;
	
	for(int i=0; i<data.antennanum;i++){
			result.add_new(i);
	}
	
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
	int size=result.size;	
	while (start < data.antenna.size()) {
		result.delete_old(density[start].id);
		antenna_visited[density[start].id]=0;
		if (result.size < size) {
			antenna_visited[density[start].id]=1;
			result.add_new(density[start].id);		
			break;
		}
		//antenna_selected.push_back(density[start].id);
		//deleted_antenna.push_back(density[start].id);		
		size = result.size;
		start++;
		//cout<<"aa: "<<size;
	}
	cout<<result.size<<endl;
	
	
	int Start=0;
	while(1){
		int solution=-1;
		int maxstation=result.size;
		int tempstation=0;
		//cout<<"aa"<<endl;
		for(int i=0; i<data.antennanum;i++){
			if(antenna_visited[i]){
				result.delete_old(i);
				tempstation = result.size;
				result.add_new(i);
			} else {
				result.add_new(i);
				tempstation = result.size;
				result.delete_old(i);
			}
			if(tempstation > maxstation){
				solution=i;
				maxstation=tempstation;
			}
		}
		//cout<<"station: "<<solution<<'\n';
		//cout<<"size: "<<result.station_result.size<<endl;
		if(solution == -1){			
			break;
		}
		else{
			if (antenna_visited[solution]) {
				result.delete_old(solution);
				antenna_visited[solution] = 0;			
			} else {
				result.add_new(solution);
				//antenna_selected.push_back(solution);
				antenna_visited[solution]=1;
			} 			
			Start++;
		}
	}
	cout<< antenna_selected.size();
	for(int i = 0; i < antenna_selected.size(); i++) {
		cout<<" " << antenna_selected[i];	
	}
	cout<<endl;
	cout<<result.size << endl;
*/
/***************************************************************/

/*********************Greedy 1&2 & SA algorithm****************************/
	SimulateAnealing sa;
	Result maxresult(data.stationnum, data.antennanum);
//	srand(time(0));
	//vector<int> deleted_antenna;
	
	for(int i=0; i<data.antennanum;i++){
			result.add_new(i);
	}
	
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
	int size=result.size;	
	while (start < data.antenna.size()) {
		result.delete_old(density[start].id);
		result.antenna_visited[density[start].id]=0;
		if (result.size < size) {
			result.antenna_visited[density[start].id]=1;
			result.add_new(density[start].id);		
			break;
		}
		//antenna_selected.push_back(density[start].id);
		//deleted_antenna.push_back(density[start].id);		
		size = result.size;
		start++;
		//cout<<"aa: "<<size;
	}
	//cout<<result.size<<endl;
	
	for(int i=0;i<data.antennanum;i++){
		maxresult.antenna_visited[i]=0;
	}
	int start2 = data.antennanum-1;	
	int size2=maxresult.size;	
	while (start2 >= 0) {
		maxresult.add_new(density[start2].id);
		maxresult.antenna_visited[density[start2].id]=1;
		if (maxresult.size < size2) {
			maxresult.antenna_visited[density[start2].id]=0;
			maxresult.delete_old(density[start2].id);		
			break;
		}
		//antenna_selected.push_back(density[start].id);
		//deleted_antenna.push_back(density[start].id);		
		size2 = maxresult.size;
		start2--;
		//cout<<"aa: "<<size;
	}	
	cout<<"result: "<<result.size<<endl;
	cout<<"maxresult: "<<maxresult.size<<endl;

	if(result.size < maxresult.size)
		result = maxresult;


	
	int Start=0;
	while(1){
	
	
	
	
		clock_t c_end = clock();
		if (1000.0 * (c_end - c_start) > 8000.0)
			break;
	
	
	
	
	
	
	
		int solution=-1;
		int maxstation=result.size;
		int tempstation=0;
		//cout<<"aa"<<endl;
		for(int i=0; i<data.antennanum;i++){
			if(result.antenna_visited[i]){
				result.delete_old(i);
				tempstation = result.size;
				result.add_new(i);
			} else {
				result.add_new(i);
				tempstation = result.size;
				result.delete_old(i);
			}
			if(tempstation > maxstation){
				solution=i;
				maxstation=tempstation;
			}
		}
		//cout<<"station: "<<solution<<'\n';
		//cout<<"size: "<<result.station_result.size<<endl;
	
			
		if(solution == -1){	
			if(result.size > maxresult.size)
				maxresult = result;
			if(sa.temperature * sa.cooling_rate > sa.absolute_temperature)
			{
			//cout<<"SA"<<endl;
			int index = 0;
			int select[(int)data.antennanum/50];
			for(int i=0 ; i<data.antennanum/50; i++){


//		 		select[i]= rand() % data.antennanum;

				while(index < data.antennanum) {
					if (result.antenna_visited[density[index].id]) {
						select[i] = density[index].id;					
					}
					index++;				
				}
				if (index == data.antennanum) {
					select[i]= rand() % data.antennanum;
				}



				if(result.antenna_visited[select[i]]==1){
					result.antenna_visited[select[i]]=0;
					result.delete_old(select[i]);
				}
				else{
					result.add_new(select[i]);
					result.antenna_visited[select[i]]=1;
				}
			//int station_count=result.size;
				if(result.size < tempstation)
				{
					if(exp((tempstation-result.size) / sa.temperature ) > static_cast <float> (rand()) / static_cast <float> (RAND_MAX)){
							
					}
					else{
						if(result.antenna_visited[select[i]]==1){
							result.delete_old(select[i]);
							result.antenna_visited[select[i]]=0;
						}	
						else{
							result.add_new(select[i]);
							result.antenna_visited[select[i]]=1;
						}
					}
				}
			}
			//break;
		}
		else
			break;
		}
		
		else{
			if (result.antenna_visited[solution]) {
				result.delete_old(solution);
				result.antenna_visited[solution] = 0;			
			} else {
				result.add_new(solution);
				//antenna_selected.push_back(solution);
				result.antenna_visited[solution]=1;
			} 			
			//Start++;
		}
 		sa.temperature *= sa.cooling_rate;
		//cout<<sa.temperature<<endl;
		//cout<<"result"<<result.size<<endl;
	}
	
	//cout << "maxresult " << maxresult.size << endl;

/*

	int antenna_select_num=0;
	for(int i = 0; i < maxresult.antenna_visited.size(); i++) {
		if(maxresult.antenna_visited[i]==1)
			antenna_select_num++;
	}
	cout<< antenna_select_num<<" ";
	
	for(int i = 0; i < maxresult.antenna_visited.size(); i++) {
		if(maxresult.antenna_visited[i]==1)
			cout<<i<<" ";
	}
	cout<<endl;
*/



	cout<<maxresult.size<<endl;









//sumsum+=maxresult.size;
//}
//cout << "average: " << (double)sumsum/100 << endl;




/****************************** GA ******************************************/

	Result temp(data.stationnum, data.antennanum);
	
	for(int i=0; i<data.antennanum;i++){
			temp.add_new(i);
	}
	// initial the generation set
	vector <Result> generation(1000, temp);
	
	// random generate and calculate the sum
	int adaptive_sum = 0;
	for (int i = 0; i < 1000; i++) {
		generate_random_result(generation[i]);
		adaptive_sum += generation[i].size;
	}
	
	// how many generations?
	while(1) {
	
		// the weight 
		vector<double> adaptive_weight (1000, 0.0);
		for (int i = 0; i < 1000; i++) {
			if (i == 0) {
				adaptive_weight[i] = (double)generation[i].size/(double)adaptive_sum;
			} else if (i == 999) {
				adaptive_weitht[i] = 1.0;
			}else {
				adaptive_weight[i] = (double)generation[i].size/(double)adaptive_sum + adaptive_weight[i-1];
			}
		}
	
		// select
		vector <Result> temp_generation(1000);
		for (int i = 0; i < 1000; i++) {
			// generate a random number
			double random_num = (double)rand()/(double)RAND_MAX;
			// find the select one CAN BE DONE BY BINARY SEARCH
			if (random_num < adaptive_weight[0]) {
				temp_generation[i] = generation[0];	
			}
			for (int j = 1; j < 1000; j++) {
				if (random_num < adaptive_weight[j] && random_num > adaptive_weight[j-1]) {
					temp_generation[i] = generation[j];
					break;
				}
			}
		}
		
		// recombination
		for (int i = 0; i < 500; i++) {
			int random_parent1 = rand() % temp_generation.size();
			Result parent1 = temp_generation[random_parent1];
			temp_generation.erase(temp_generation.begin() + random_parent1);
			int random_parent2 = rand() % temp_generation.size();
			Result parent2 = temp_generation[random_parent2];
			
			recombination_mutation (parent1, parent2, generation, i);
		}
		
		
	}
	
	
	
	// after the last one, find the best answer
	int max_size_index = 0;
	int max_size = 0;
	for (int i = 0; i < generation.size(); i++) {
		if (generation[i].size > max_size) {
			max_size_index = i;
			max_size = generation[i].size;
		}
	}
	








	/*
	for(int i = 0; i < antenna_selected.size(); i++) {
		cout<<" " << antenna_selected[i];	
	}
	cout<<endl;
	cout<<result.size << endl;
	*/
/***************************************************************/

/*********************Greedy 2 algorithm****************************/
/*
	//int initial=0;
	//result.add_new(initial);	
	//antenna_selected.push_back(initial);
	//data.antenna[initial].clear();	
	int Start=0;
	while(Start<data.antennanum){
		int solution=-1;
		int maxstation=result.size;
		int tempstation=0;
		//cout<<"aa"<<endl;
		for(int i=0; i<data.antennanum;i++){
			result.add_new(i);
			tempstation = result.size;
			if(tempstation > maxstation){
				solution=i;
				maxstation=tempstation;
			}
			result.delete_old(i);
		}
		//cout<<"station: "<<solution<<'\n';
		//cout<<"size: "<<result.station_result.size<<endl;
		if(solution == -1)
			break;
		else{
			result.add_new(solution);
			antenna_selected.push_back(solution);
			data.antenna[solution].clear();
			Start++;
		}
	}
	cout<< antenna_selected.size();
	for(int i = 0; i < antenna_selected.size(); i++) {
		cout<<" " << antenna_selected[i];	
	}
	cout<<endl;
	cout<<result.size << endl;
*/
/***************************************************************/

/*********************Greedy 2.1 algorithm****************************/
/*
	//int initial=0;
	//result.add_new(initial);	
	//antenna_selected.push_back(initial);
	//data.antenna[initial].clear();	
	vector<bool> antenna_visited(data.antennanum,0);
	int Start=0;
	while(1){
		int solution=-1;
		int maxstation=result.size;
		int tempstation=0;
		//cout<<"aa"<<endl;
		for(int i=0; i<data.antennanum;i++){
			if(antenna_visited[i]){
				result.delete_old(i);
				tempstation = result.size;
				result.add_new(i);
			} else {
				result.add_new(i);
				tempstation = result.size;
				result.delete_old(i);
			}
			if(tempstation > maxstation){
				solution=i;
				maxstation=tempstation;
			}
		}
		//cout<<"station: "<<solution<<'\n';
		//cout<<"size: "<<result.station_result.size<<endl;
		if(solution == -1)
			break;
		else{
			if (antenna_visited[solution]) {
				result.delete_old(solution);
				antenna_visited[solution] = 0;			
			} else {
				result.add_new(solution);
				//antenna_selected.push_back(solution);
				antenna_visited[solution]=1;
			} 			
			Start++;
		}
	}
	cout<< antenna_selected.size();
	for(int i = 0; i < antenna_selected.size(); i++) {
		cout<<" " << antenna_selected[i];	
	}
	cout<<endl;
	cout<<result.size << endl;
*/
/***************************************************************/





/*********************Greedy 3 algorithm****************************/
/*
	vector<bool> antenna_visited(data.antennanum,1);
	for(int i=0; i<data.antennanum;i++){
			result.add_new(i);
	}	
	int Start=0;
	while(Start<data.antenna.size()){
		int solution=-1;
		int maxstation=result.size;
		int tempstation=0;
		//cout<<"aa"<<endl;
		for(int i=0; i<data.antennanum;i++){
			if(antenna_visited[i]==1){
				result.delete_old(i);
				tempstation = result.size;
				if(tempstation > maxstation){
					solution=i;
					maxstation=tempstation;
				}
				result.add_new(i);
			}		
		}
		//cout<<"station: "<<solution<<'\n';
		//cout<<"size: "<<result.station_result.size<<endl;
		if(solution == -1)
			break;
		else{
			result.delete_old(solution);
			//antenna_selected.push_back(solution);
			antenna_visited[solution]=0;
			//data.antenna[solution].clear();
			Start++;
		}
	}
	cout<< antenna_selected.size();
	for(int i = 0; i < antenna_selected.size(); i++) {
		cout<<" " << antenna_selected[i];	
	}
	cout<<endl;
	cout<<result.size << endl;
*/
/***************************************************************/

/*********************Greedy 2&3 algorithm****************************/
/*
	vector<bool> antenna_visited(data.antennanum,1);
	for(int i=0; i<data.antennanum;i++){
			result.add_new(i);
	}	
	int start=0;
	while(start<data.antenna.size()){
		int solution=-1;
		int maxstation=result.size;
		int tempstation=0;
		//cout<<"aa"<<endl;
		for(int i=0; i<data.antennanum;i++){
			if(antenna_visited[i]==1){
				result.delete_old(i);
				tempstation = result.size;
				if(tempstation > maxstation){
					solution=i;
					maxstation=tempstation;
				}
				result.add_new(i);
			}		
		}
		//cout<<"station: "<<solution<<'\n';
		//cout<<"size: "<<result.station_result.size<<endl;
		if(solution == -1)
			break;
		else{
			result.delete_old(solution);
			//antenna_selected.push_back(solution);
			antenna_visited[solution]=0;
			//data.antenna[solution].clear();
			start++;
		}
	}
	cout<< antenna_selected.size();
	for(int i = 0; i < antenna_selected.size(); i++) {
		cout<<" " << antenna_selected[i];	
	}
	cout<<endl;
	cout<<result.size << endl;
	cout<<"****"<<endl;

	int Start=0;
	while(1){
		int solution=-1;
		int maxstation=result.size;
		int tempstation=0;
		//cout<<"aa"<<endl;
		for(int i=0; i<data.antennanum;i++){
			if(antenna_visited[i]){
				result.delete_old(i);
				tempstation = result.size;
				result.add_new(i);
			} else {
				result.add_new(i);
				tempstation = result.size;
				result.delete_old(i);
			}
			if(tempstation > maxstation){
				solution=i;
				maxstation=tempstation;
			}
		}
		//cout<<"station: "<<solution<<'\n';
		//cout<<"size: "<<result.station_result.size<<endl;
		if(solution == -1){			
			break;
		}
		else{
			if (antenna_visited[solution]) {
				result.delete_old(solution);
				antenna_visited[solution] = 0;			
			} else {
				result.add_new(solution);
				//antenna_selected.push_back(solution);
				antenna_visited[solution]=1;
			} 			
			Start++;
		}
	}
	cout<< antenna_selected.size();
	for(int i = 0; i < antenna_selected.size(); i++) {
		cout<<" " << antenna_selected[i];	
	}
	cout<<endl;
	cout<<result.size << endl;

*/

	return 0;		
}

/***************************************************************/






void input_from_file(MainData &data)
{
	cin>>data.antennanum>>data.stationnum;
	data.antenna.resize(data.antennanum);
	data.station.resize(data.stationnum);
	string line;
	getline(cin,line);
    //while ( getline (myfile,line) )
	for(int i=0; i<data.antennanum;i++){
		getline (cin,line);
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

void Result::delete_old(int old_antenna) {
	for(int i=0; i< data.antenna[old_antenna].size();i++){
		station_status[data.antenna[old_antenna][i]]--;
		if(station_status[data.antenna[old_antenna][i]]==1)
			size++;
		if(station_status[data.antenna[old_antenna][i]]==0)
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


void generate_random_result (Result &result) {
	for (int i = 0; i < data.antennanum; i++) {
		int random = rand() % 2
		if (random == 0) {
			result.delete_old(i);
			result.antenna_visited[i] = 0;
		}
	}

}

void recombination_mutation (Result &result1, Result &result2, vector<Result> &generation, int index) {
	int recombination_point = random() % data.antennanum;
	
	// recombination child 1
	for (int i = 0; i <= recombination_point; i++) {
		if (result1.antenna_visited[i] == 1 && generation[index].antenna_visited[i] == 0) {
			generation[index].add_new(i);
			generation[index].antenna_visited[i] = 1;
		}
		if (result1.antenna_visited[i] == 0 && generation[index].antenna_visited[i] == 1) {
			generation[index].delete_old(i);
			generation[index].antenna_visited[i] = 0;
		}
	}
	for (int i = recombination_point+1; i < data.antennanum; i++) {
		if (result2.antenna_visited[i] == 1 && generation[index].antenna_visited[i] == 0) {
			generation[index].add_new(i);
			generation[index].antenna_visited[i] = 1;
		}
		if (result2.antenna_visited[i] == 0 && generation[index].antenna_visited[i] == 1) {
			generation[index].delete_old(i);
			generation[index].antenna_visited[i] = 0;
		}
	}
	// child 2
	for (int i = 0; i <= recombination_point; i++) {
		if (result2.antenna_visited[i] == 1 && generation[index+1].antenna_visited[i] == 0) {
			generation[index+1].add_new(i);
			generation[index+1].antenna_visited[i] = 1;
		}
		if (result2.antenna_visited[i] == 0 && generation[index+1].antenna_visited[i] == 1) {
			generation[index+1].delete_old(i);
			generation[index+1].antenna_visited[i] = 0;
		}
	}
	for (int i = recombination_point+1; i < data.antennanum; i++) {
		if (result1.antenna_visited[i] == 1 && generation[index+1].antenna_visited[i] == 0) {
			generation[index+1].add_new(i);
			generation[index+1].antenna_visited[i] = 1;
		}
		if (result1.antenna_visited[i] == 0 && generation[index+1].antenna_visited[i] == 1) {
			generation[index+1].delete_old(i);
			generation[index+1].antenna_visited[i] = 0;
		}
	}
	
	
	// mutation 
	// how many times?
	for (int i = 0; i < 1; i++) {
		double mutation_point = rand() % data.antennanum;
		if (generation[index].antenna_visited[mutation_point] == 1) {
			generation[index].antenna_visited[mutation_point] = 0;
			generation[index].delete_old (mutation_point);
		} else {
			generation[index].antenna_visited[mutation_point] = 1;
			generation[index].add_new (mutation_point);
		}
		
		mutation_point = rand() % data.antennanum;
			if (generation[index+1].antenna_visited[mutation_point] == 1) {
			generation[index+1].antenna_visited[mutation_point] = 0;
			generation[index+1].delete_old (mutation_point);
		} else {
			generation[index+1].antenna_visited[mutation_point] = 1;
			generation[index+1].add_new (mutation_point);
		}
	}
	
}



