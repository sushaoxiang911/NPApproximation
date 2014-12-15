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


class Result
{
	public:		
	int size;
	vector<int> station_status;
	vector<bool> antenna_visited;
	void add_new (int new_antenna);
	void delete_old(int old_antenna);

	Result(){}
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
    double absolute_temperature = 0.00001;
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


void input_from_file(MainData &data);


MainData data;

int main(){
	input_from_file(data);
	srand(time(0));




//int sumsum = 0;
//for(int nn = 0; nn < 100; nn++) {


	clock_t c_start = clock();
	cout<<"initial: "<<c_start<<endl;


	Result result(data.stationnum, data.antennanum);
	vector<int> antenna_selected;

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
		if ((double)(clock() - c_start)/CLOCKS_PER_SEC > 60.0)
			break;
		int solution=-1;
		int maxstation=result.size;
		int tempstation=0;
		//cout<<"aa"<<endl;
//		vector<int> increase;
		for(int i=0; i<data.antennanum;i++){
			if(result.antenna_visited[i]){
//				cout << result.size << endl;
				result.delete_old(i);
				tempstation = result.size;
				result.add_new(i);
//				cout << result.size << endl;
			} else {
//				cout << result.size << endl;
				result.add_new(i);
				tempstation = result.size;
				result.delete_old(i);
//				cout << result.size << endl;
			}
			if(tempstation > maxstation){
				solution=i;
				maxstation=tempstation;
			}
//			if (tempstation > result.size) {
//				increase.push_back(tempstation);
//			}
		}
		
		
		
		
		
		//cout<<"station: "<<solution<<'\n';
		//cout<<"size: "<<result.station_result.size<<endl;
		if(solution == -1){	
			if(result.size > maxresult.size){
				maxresult = result;
//				cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!:               "<<maxresult.size<<endl;
			}
			if(sa.temperature * sa.cooling_rate > sa.absolute_temperature)
			{
				int index = 0;
				int select[(int)data.antennanum/50];
				for(int i=0 ; i<data.antennanum/50; i++){
//			 		select[i]= rand() % data.antennanum;
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
		/*			if(result.size < tempstation)
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
			*/	}
				//break;
			} else
				break;
		}
		else{
			if (result.antenna_visited[solution]) {
//				cout << "status: " << result.antenna_visited[solution] << endl;
//				cout<< "delete: " << solution << endl;
				result.delete_old(solution);
				result.antenna_visited[solution] = 0;			
			} else {
//				cout << "status: " << result.antenna_visited[solution] << endl;
//				cout << "add: " << solution << endl;
				result.add_new(solution);
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
