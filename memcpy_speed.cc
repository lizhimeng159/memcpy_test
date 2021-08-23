/*
-- Compilation and run:
g++ -O0 -std=c++11 -o memcpy_speed memcpy_speed.cc && ./memcpy_speed
*/
#include <iostream>
#include <string.h>
#include <time.h>
#include <iomanip>
using namespace std;

#define TYPE_NUM (11)
#define ITERATION_NUM (10)
#define KB (1024)
#define MB (1024*KB)
#define GB (1024*MB)

struct memcpy_type{
	int mt_size;
	char *src_mtp;
	char *des_mtp;
	double total_used_time;
	int iteration_num;
};

struct memcpy_type mt[TYPE_NUM];


void init_memcpy_buf(){

	mt[0].mt_size = 1*KB;	
	mt[1].mt_size = 4*KB;	
	mt[2].mt_size = 16*KB;	
	mt[3].mt_size = 128*KB;	
	mt[4].mt_size = 1*MB;	
	mt[5].mt_size = 2*MB;	
	mt[6].mt_size = 4*MB;	
	mt[7].mt_size = 8*MB;	
	mt[8].mt_size = 64*MB;	
	mt[9].mt_size = 256*MB;	
	mt[10].mt_size = 512*MB;	

	for(int i = 0; i < TYPE_NUM; i++){
		mt[i].src_mtp = new char[mt[i].mt_size];
		mt[i].des_mtp = new char[mt[i].mt_size];
		memset(mt[i].src_mtp,1,mt[i].mt_size);
	};
}

void test_memcpy(){

	struct timespec start_time, end_time;

	for(int i = 0; i < TYPE_NUM; i++){
		clock_gettime(CLOCK_MONOTONIC, &start_time);
        	memcpy(mt[i].des_mtp, mt[i].src_mtp, mt[i].mt_size);
        	clock_gettime(CLOCK_MONOTONIC, &end_time);
        	mt[i].total_used_time += (end_time.tv_sec - start_time.tv_sec)*1000.0 + \
                          (end_time.tv_nsec - start_time.tv_nsec)/1000000.0;

		mt[i].iteration_num++;
	};

}

void print_result(){

	for(int i = 0; i < TYPE_NUM; i++){
		cout<<setprecision(6)<<"memcpy size(kb):"<<std::left<<setw(10)
			<<mt[i].mt_size/1024<<"time used per copy(ms): " \
			<<setw(10)<<mt[i].total_used_time/mt[i].iteration_num<<"  "<< \
			"time used per 4kb(us):"<<setw(15) <<mt[i].total_used_time/mt[i].iteration_num*1000.0/(mt[i].mt_size/4.0/KB) \
		       	<< "memcpy speed(GB/s):" <<setw(20)<< \
			mt[i].mt_size/mt[i].total_used_time*mt[i].iteration_num/GB*1000 <<endl;
	};
}
	

int main(int argc,const char **argv){

	printf("start memcpy test \n");
	init_memcpy_buf();

	for(int i = 0; i < 10; i++){
		test_memcpy();
		printf("total iterations are 10, this iteration is %dth\n",i+1);
	};

	print_result();

	return 0;
}

