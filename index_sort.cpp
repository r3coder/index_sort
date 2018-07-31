#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <math.h>
#include <sys/time.h>
#include <iomanip>
#include <chrono>
constexpr int DATA_NUM = 1000000;
constexpr int TEST_NUM = 30;

void printTime(long time){
	std::cout <<(time)/1000000 << ".";
	std::cout << std::setw(6) << std::setfill('0') << (time)%1000000;
}

int index_sort_v(int* start, int* end){
	int* it = start;
	int len = 0;
	int max = *it; int min = *it;

	while(it!=end){
		if(*it>max){max = *it;}
		if(*it<min){min = *it;}
		it++;
		len++;
	}
	int div = (int)std::sqrt(DATA_NUM);
	std::vector<int> data[div];
	for(int i=0;i<div;i++){
		data[i].reserve(DATA_NUM);
	}
	it = start;
	while(it!=end){
		//std::cout << "it " << (*it) << "	 max-min " << (max-min+1) << "	 ans:" << ((float)*it/(max-min+1))*len << std::endl;
		float target = ((float)*it/(max-min+1));
		data[(int)(target*div)].push_back(*it);
		it++;
	}
	//std::cout << "put complete" << std::endl;
	it = start;
	for(int i=0;i<div;i++){
		std::sort(data[i].begin(),data[i].end());
		for(int j=0;j<data[i].size();j++){
			*it = data[i].at(j);
			it++;
			//std::cout<<data[i].at(j)<<"\t";
		}
		//std::cout<<std::endl;
	}
}
int index_sort(int* start, int* end){
	int* it = start;
	int len = 0;
	int max = *it; int min = *it;

	while(it!=end){
		if(*it>max){max = *it;}
		if(*it<min){min = *it;}
		it++;
		len++;
	}
	int data_new[len];
	bool valid[len];
	for(int i=0;i<len;i++){data_new[i] = 0; valid[len] = false;}
	it = start;
	while(it!=end){
	//std::cout << "it " << (*it) << "	 max-min " << (max-min+1) << "	 ans:" << ((float)*it/(max-min+1))*len << std::endl;
		int target = (int)(((float)*it/(max-min+1))*len);
		if(!valid[target]){
			data_new[target] = *it;
			valid[target] = true;
		}
		else{
			bool input = false;
			while (!input){
				//int td = data_new[target];
				if(data_new[target]<*it){
					target++;
					if(!valid[target]){
						data_new[target] = *it;
						valid[target] = true;
						input=true;
					}
				}
				else{
					data_new[target+1] = data_new[target];
					data_new[target] = *it;
					valid[target+1] = true;
					input = true;
				}
			}
		}
		it++;
	}
	it = start;
	int index = 0;
	while(it!=end){
		*it = data_new[index];it++;index++;
	}
}

bool comparator (int i,int j) { return (i<j); }
int main(){
	/*
	std::default_random_engine generator;
	std::uniform_int_distribution<int> distribution(1,DATA_NUM);*/
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

	long quick_total = 0;
	long quick_avg = 0;
	long index_total = 0;
	long index_avg = 0;
	int data_quick[DATA_NUM];
	int data_index[DATA_NUM];
	struct timeval t;
	for(int tst=0;tst<TEST_NUM;tst++){
		//set data to non-rep
		/*
		for (int i=0;i<DATA_NUM;i++){
			data_quick[i] = i;
		}
		shuffle (data_quick,data_quick+DATA_NUM, std::default_random_engine(seed));
		for (int i=0;i<DATA_NUM;i++){
			data_index[i] = data_quick[i];
		}*/

		for (int i=0;i<DATA_NUM;i++){
			data_index[i]=rand()%100000;
			data_quick[i]=data_index[i];
		}

		//for (int i=0;i<DATA_NUM;i++){std::cout << data_index[i] << "\t";}std::cout << std::endl;
	 
		//quicksort
		gettimeofday(&t,NULL);
		long t_start = (long)t.tv_sec*1000000+(long)t.tv_usec;
		std::sort(data_quick,data_quick+DATA_NUM,comparator);
		gettimeofday(&t,NULL);
		long t_end = (long)t.tv_sec*1000000+(long)t.tv_usec;
		quick_total = quick_total + t_end - t_start;
		std::cout << "Quicksort #" << tst+1 << ": ";
		printTime(t_end-t_start); std::cout << std::endl;
		
		//indexsort
		gettimeofday(&t,NULL);
		t_start = (long)t.tv_sec*1000000+(long)t.tv_usec;
		//index_sort(data_index,data_index+DATA_NUM);
		index_sort_v(data_index,data_index+DATA_NUM);
		gettimeofday(&t,NULL);
		t_end = (long)t.tv_sec*1000000+(long)t.tv_usec;
		index_total = index_total + t_end - t_start;
		std::cout << "Indexsort #" << tst+1 << ": ";
		printTime(t_end-t_start); std::cout << std::endl;

	
		bool validate = true;
		for (int i=0;i<DATA_NUM;i++){
			if(data_index[i]!=data_quick[i]){
				validate = false;
				std::cout << data_index[i] << "!=" << data_quick[i] << std::endl;
				std::cout << "Result ERROR" << std::endl;
				for (int i=0;i<DATA_NUM;i++){std::cout << data_quick[i] << "\t";}std::cout << std::endl;
				for (int i=0;i<DATA_NUM;i++){std::cout << data_index[i] << "\t";}std::cout << std::endl;
				break;
			}
		}
	}
	quick_avg = quick_total / TEST_NUM;
	index_avg = index_total / TEST_NUM;

	std::cout << "******************************"<<std::endl;
	std::cout << "Data Size : " << DATA_NUM << std::endl;
	std::cout << "quicksort:" << std::endl;
	std::cout << "total execution time : "<<(quick_total)/1000000 << ".";
	std::cout << std::setw(6) << std::setfill('0') << (quick_total)%1000000<<std::endl;
	std::cout << "average execution time : "<<(quick_avg)/1000000 << ".";
	std::cout << std::setw(6) << std::setfill('0') << (quick_avg)%1000000<<std::endl;
	std::cout << "******************************"<<std::endl;
	std::cout << "total execution time : "<<(index_total)/1000000 << ".";
	std::cout << std::setw(6) << std::setfill('0') << (index_total)%1000000<<std::endl;
	std::cout << "average execution time : "<<(index_avg)/1000000 << ".";
	std::cout << std::setw(6) << std::setfill('0') << (index_avg)%1000000<<std::endl;
	std::cout << "******************************"<<std::endl;
	return 0;
}
