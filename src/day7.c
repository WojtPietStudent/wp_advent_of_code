#include <stdio.h>
#include <stdlib.h>

#define MAX_NUM_LEN 64


unsigned int
my_pow(unsigned int num,int to)
{
	unsigned int total=1;
	for(int i=0;i<to;i++){
		total*=num;
	}
	total*=(to!=0);
	return total;
}

unsigned int
my_logi(unsigned int num,unsigned int pow)
{
	unsigned int total=pow,to=0;
	while(total<num){
		total*=pow;
		to++;
	}
	return to;
}

unsigned long
oper_loop(unsigned long *numbers,int lenght,unsigned long expected)
{
	unsigned long total=0,add_symbol=0;
	int test_reuse=0;
	for(int i=0;i<(1<<lenght);i++){
		unsigned long total_temp=numbers[0];
		for(int j=1;j<lenght;j++){
			test_reuse=((add_symbol & (1<<j-1))>0);
			total_temp+=numbers[j]*test_reuse;
			total_temp*=(numbers[j]*((add_symbol & (1<<j-1))==0))+test_reuse;
		}
		if(total_temp==expected){
			total=expected;
			break;
		}
		add_symbol++;
	}
	return total;
}

	
unsigned long
oper_loop_concat(unsigned long *numbers,int lenght,unsigned long expected)
{
	
	unsigned long total=0,add_symbol=0;
	int operator[MAX_NUM_LEN]={0};
	
	for(int i=0;i<my_pow(3,lenght);i++){
		
		unsigned long total_temp=numbers[0];
		int carry=0;
		
		for(int j=1;j<lenght;j++){

			operator[j-1]+=carry;
			carry=operator[j-1]==3;
			operator[j-1]%=3;
			
			total_temp*=	 (numbers[j]*(operator[j-1]==0))
					+((my_pow(10,(my_logi(numbers[j],10)+1)))*(operator[j-1]==2))
					+(operator[j-1]==1);
			
			total_temp+=numbers[j]*(operator[j-1]>0);
		}

		if(total_temp==expected){
			total=expected;
			break;
		}
		
		operator[0]++;
	}
	return total;
}


unsigned long
oper_all_loop(const char *numpath)
{
	FILE *operf=fopen(numpath,"r");
	char current_line[MAX_NUM_LEN*4],*point_line;
	unsigned long current_num[MAX_NUM_LEN],compare,current_size=0,add_all=0;
	int offset_cur=0,offset_change=0;
	while((point_line=fgets(current_line,MAX_NUM_LEN*4,operf))!=NULL){
		current_size=0;
		sscanf(point_line,"%lu%n:",&compare,&offset_cur);
		
		offset_cur+=1;
		while(sscanf(point_line+offset_cur," %lu%n",&current_num[current_size],&offset_change)>0){
			offset_cur+=offset_change;
			offset_cur++;
			current_size++;
		}
	
		add_all+=oper_loop(current_num,current_size,compare);
	}
	fclose(operf);
	return add_all;
}
unsigned long
oper_all_loop_cat(const char *numpath)
{
	FILE *operf=fopen(numpath,"r");
	char current_line[MAX_NUM_LEN*4],*point_line;
	unsigned long current_num[MAX_NUM_LEN],compare,current_size=0,add_all=0;
	int offset_cur=0,offset_change=0;
	while((point_line=fgets(current_line,MAX_NUM_LEN*4,operf))!=NULL){
		current_size=0;
		sscanf(point_line,"%lu%n:",&compare,&offset_cur);
		
		offset_cur+=1;
		while(sscanf(point_line+offset_cur," %lu%n",&current_num[current_size],&offset_change)>0){
			offset_cur+=offset_change;
			offset_cur++;
			current_size++;
		}
	
		add_all+=oper_loop_concat(current_num,current_size,compare);
	}
	fclose(operf);
	return add_all;
}
int
main()
{
	printf("p1 : %lu , p2 : %lu\n",oper_all_loop("../data/day7data.txt"),oper_all_loop_cat("../data/day7data.txt"));
	return 0;
}
