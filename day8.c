#include <stdio.h>
#include <stdlib.h>

#define MAX_MAP_SIZE 512


typedef struct{
	int vec_array[MAX_MAP_SIZE][3],
	    cell_array[MAX_MAP_SIZE*MAX_MAP_SIZE],
	    line_len,line_num,vec_num;
}towerLocs;

void
twloc_print(towerLocs *view)
{
	for(int i=0;i<view->line_num;i++){
		for(int j=0;j<view->line_len;j++){
			printf("%c",view->cell_array[i*MAX_MAP_SIZE+j]);			
		}
		printf("\n");
		
	}
	printf("\n");
}


towerLocs*
twloc_load(const char file_open[],towerLocs *into)
{
	char current_line[MAX_MAP_SIZE],*point_line;
	int line_len=0,line_num=0,vec_num=0;
	FILE *patrol_file=fopen(file_open,"r");
	if(patrol_file==NULL){return NULL;}
	
	while( (point_line=fgets(current_line,MAX_MAP_SIZE,patrol_file))!=NULL){
		if(line_len==0){
			while(point_line[line_len]!='\n'){
				line_len++;
			}
			into->line_len=line_len;
		}
		for(int i=0;i<line_len;i++){
			into->cell_array[line_num * MAX_MAP_SIZE + i] = current_line[i];
			if(current_line[i]!='.'){
				
				into->vec_array[vec_num][0]=i;
		       		into->vec_array[vec_num][1]=line_num;
				into->vec_array[vec_num][2]=current_line[i];
				vec_num++;		
			}	 
		}
		line_num++;
	}
	into->line_num=line_num;
	into->vec_num=vec_num;
	return into;
}

int
twloc_anode(towerLocs *calc)
{
	int total=0,tmp_col=0,tmp_row=0;
	for(int i=0;i<calc->vec_num;i++){
		for(int j=0;j<calc->vec_num;j++){
			tmp_row=(2*calc->vec_array[i][1]-calc->vec_array[j][1]);
			tmp_col=(2*calc->vec_array[i][0]-calc->vec_array[j][0]);
			if(	(tmp_row >= 0 && tmp_col >= 0 && tmp_row < calc->line_num && tmp_col < calc->line_len)
			     && calc->cell_array[tmp_row*MAX_MAP_SIZE+tmp_col]!='?'
			     && calc->vec_array[i][2]==calc->vec_array[j][2]
			     && (calc->vec_array[i][1]!=calc->vec_array[j][1] && calc->vec_array[i][0]!=calc->vec_array[j][0]) ){
				
				total++;
				calc->cell_array[tmp_row*MAX_MAP_SIZE+tmp_col]='?';
			}
		}
	}
	return total;
}

int
twloc_anode_harmonic(towerLocs *calc)
{
	int total=0,tmp_col=0,tmp_row=0,tmpd_col=0,tmpd_row=0,proc=1,
	    loccell_array[MAX_MAP_SIZE*MAX_MAP_SIZE];
	
	for(int i=0;i<calc->line_num;i++){
		for(int j=0;j<calc->line_len;j++){
			loccell_array[i*MAX_MAP_SIZE+j]=calc->cell_array[i*MAX_MAP_SIZE+j];			
		}
	}
	
	for(int i=0;i<calc->vec_num;i++){
		for(int j=0;j<calc->vec_num;j++){
			proc=0;
			
			tmpd_row=(calc->vec_array[i][1]-calc->vec_array[j][1]);
			tmpd_col=(calc->vec_array[i][0]-calc->vec_array[j][0]);
			
			tmp_row=calc->vec_array[i][1]+tmpd_row*proc;
			tmp_col=calc->vec_array[i][0]+tmpd_col*proc;
			
			while(tmp_row >= 0 && tmp_col >= 0 && tmp_row < calc->line_num && tmp_col < calc->line_len && 
			     ( tmpd_col != 0 && tmpd_row != 0 )	
			     ){
			
				if(loccell_array[tmp_row*MAX_MAP_SIZE+tmp_col]!='?' &&
				   calc->vec_array[i][2]==calc->vec_array[j][2]
				  ){
					
					total++;
					loccell_array[tmp_row*MAX_MAP_SIZE+tmp_col]='?';	
				}
				proc++;
				
				tmp_row=calc->vec_array[i][1]+tmpd_row*proc;
				tmp_col=calc->vec_array[i][0]+tmpd_col*proc;
			};
			
		}
	}
	return total;
}

int
main()
{
	towerLocs the_map,the_map2;
	twloc_load("day8data.txt",&the_map);
	twloc_load("day8data.txt",&the_map2);
	printf("p1 : %d , p2 : %d\n",twloc_anode(&the_map),twloc_anode_harmonic(&the_map2));
	return 0;
}
