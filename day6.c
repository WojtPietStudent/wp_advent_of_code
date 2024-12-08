#include <stdio.h>
#include <stdlib.h>

#define MAX_MAP_SIZE 256

enum cellState{
	Empty=0,
	Obstacle=1,
	Visited=2
};
enum patrolState{
	PatrolUp=1,
	PatrolRight=2,
	PatrolDown=3,
	PatrolLeft=4	
};

typedef struct{
	int cell_array[MAX_MAP_SIZE*MAX_MAP_SIZE],
	    line_len,line_num,col_patrol,row_patrol,patrol_state;
}patrolMap;

void
pmap_print(patrolMap *view)
{
	for(int i=0;i<view->line_num;i++){
		for(int j=0;j<view->line_len;j++){
			int out_view=view->cell_array[i*MAX_MAP_SIZE+j];
			if(view->col_patrol==j&&view->row_patrol==i){
				switch(view->patrol_state){
				case PatrolUp:
					printf("^");
					break;
				case PatrolDown:
					printf("v");
					break;
				case PatrolRight:
					printf(">");
					break;
				case PatrolLeft:
					printf("<");
					break;
				default:
					break;
				}		
			}else{
				switch(out_view){
				case Empty:
					printf(".");
					break;	
				case Obstacle:
					printf("#");
					break;
				case Visited:
					printf("X");
					break;
		
				default:
					break;
				}
			}
		}
		printf("\n");
		
	}
	printf("\n");
}


patrolMap*
pmap_load(const char file_open[],patrolMap *into)
{
	char current_line[MAX_MAP_SIZE],*point_line;
	int line_len=0,line_num=0;
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
			/*	is this faster????	*/
			int patrol=0
				+(PatrolUp)*(point_line[i]=='^')
				+(PatrolDown)*(point_line[i]=='v')
				+(PatrolLeft)*(point_line[i]=='<')
				+(PatrolRight)*(point_line[i]=='>');
			into->patrol_state+=patrol;
			if(patrol>0){
				into->col_patrol=i;
				into->row_patrol=line_num;
			}
			into->cell_array[line_num*MAX_MAP_SIZE+i]=	 
				 (Empty)*(point_line[i]=='.')
				+(Obstacle)*(point_line[i]=='#')
				+(Visited)*(patrol>0);
		}
		line_num++;
	}
	into->line_num=line_num;

	return into;
}



int
pmap_copy(patrolMap *in,patrolMap *copy)
{
	for( int i = 0 ; i < copy->line_num ; i++ ){
		for( int j = 0; j < copy->line_len ; j++ ){
			
			in->cell_array[ i * MAX_MAP_SIZE + j ] = copy->cell_array[ i * MAX_MAP_SIZE + j ];
		}
	}

	in->line_num = copy->line_num;
	in->line_len = copy->line_len;
	in->col_patrol = copy->col_patrol;
	in->row_patrol = copy->row_patrol;
	in->patrol_state = copy->patrol_state;

	return 0;
}



int
pmap_develop(patrolMap *out)
{
	//started with one selected rest is filled for next
	int next,total=1,
	    point_next_col= ( out->col_patrol + ( out->patrol_state == PatrolRight ) - ( out->patrol_state == PatrolLeft )),
	    point_next_row= ( out->row_patrol - ( out->patrol_state == PatrolUp ) + ( out->patrol_state == PatrolDown ));
	
	
	
	while(point_next_row >= 0 && point_next_row <= out->line_num && point_next_col >= 0 && point_next_col <= out->line_len){
		
		next=out->cell_array[ point_next_row * MAX_MAP_SIZE + point_next_col ];
		switch(next){
			
			case Empty:
				total++;
				out->cell_array[point_next_row*MAX_MAP_SIZE + point_next_col]=Visited;
			case Visited:
				out->row_patrol = point_next_row;
				out->col_patrol = point_next_col;
				break;
			case Obstacle:
				out->patrol_state = (out->patrol_state) % 4+1;
				break;
			default:
				return -total;
		}	
		point_next_row = ( out->row_patrol - ( out->patrol_state == PatrolUp ) + ( out->patrol_state == PatrolDown ));
		point_next_col = ( out->col_patrol + ( out->patrol_state == PatrolRight ) - ( out->patrol_state == PatrolLeft ));
	}
	return total;
}




int
pmap_oneloop(patrolMap *out,int *patrol_memory)
{
	int 	next,
		point_next_col= ( out->col_patrol + ( out->patrol_state == PatrolRight ) - ( out->patrol_state == PatrolLeft )),
		point_next_row= ( out->row_patrol - ( out->patrol_state == PatrolUp ) + ( out->patrol_state == PatrolDown ));
	out->cell_array[ point_next_row * MAX_MAP_SIZE + point_next_col ]=Obstacle;
	
	while(point_next_row >= 0 && point_next_row <= out->line_num && point_next_col >= 0 && point_next_col <= out->line_len){
		next=out->cell_array[ point_next_row * MAX_MAP_SIZE + point_next_col ];
		switch(next){	
			case Empty:
				out->cell_array[point_next_row*MAX_MAP_SIZE + point_next_col]=Visited;
			case Visited:
				out->row_patrol = point_next_row;
				out->col_patrol = point_next_col;
				break;
			case Obstacle:
				
				if((patrol_memory[out->row_patrol * MAX_MAP_SIZE + out->col_patrol]&1<<out->patrol_state)>1){
						return 1;
				}
				patrol_memory[out->row_patrol * MAX_MAP_SIZE + out->col_patrol]+=
					 ((patrol_memory[out->row_patrol * MAX_MAP_SIZE + out->col_patrol]&1<<out->patrol_state)==0)
					*(1<<out->patrol_state);
								
				out->patrol_state = (out->patrol_state) % 4+1;
				break;
			default:
				return 0;
		}
		point_next_row = ( out->row_patrol - ( out->patrol_state == PatrolUp ) + ( out->patrol_state == PatrolDown ));
		point_next_col = ( out->col_patrol + ( out->patrol_state == PatrolRight ) - ( out->patrol_state == PatrolLeft ));
	}
	return 0;
}



int
pmap_block(patrolMap *out)
{
	patrolMap copy;
	int next,total=0,
	    point_next_col= ( out->col_patrol + ( out->patrol_state == PatrolRight ) - ( out->patrol_state == PatrolLeft )),
	    point_next_row= ( out->row_patrol - ( out->patrol_state == PatrolUp ) + ( out->patrol_state == PatrolDown )),
	    
	    patrol_memory[MAX_MAP_SIZE * MAX_MAP_SIZE]={0},
	    patrol_memory_modify[MAX_MAP_SIZE * MAX_MAP_SIZE]={0};
	
	
	while(point_next_row >= 0 && point_next_row <= out->line_num && point_next_col >= 0 && point_next_col <= out->line_len){

		next=out->cell_array[ point_next_row * MAX_MAP_SIZE + point_next_col ];
		
		switch(next){
			
			case Empty:
				out->cell_array[point_next_row*MAX_MAP_SIZE + point_next_col]=Visited;
				
				/*could cut back by saving changes in seperate struct instead of copy*/
				pmap_copy(&copy,out);

				for( int i = 0 ; i < out->line_num ; i++ ){
					for( int j = 0; j < out->line_len ; j++ ){	
						patrol_memory_modify[ i * MAX_MAP_SIZE + j ] = patrol_memory[ i * MAX_MAP_SIZE + j ];
					}
				}

				total+=pmap_oneloop(&copy,patrol_memory_modify);

			case Visited:
				
				out->row_patrol = point_next_row;
				out->col_patrol = point_next_col;

				break;
			case Obstacle:
					
				patrol_memory[out->row_patrol * MAX_MAP_SIZE + out->col_patrol]+=
					 ((patrol_memory[out->row_patrol * MAX_MAP_SIZE + out->col_patrol]&1<<out->patrol_state)==0)
					*(1<<out->patrol_state);
				
				out->patrol_state = (out->patrol_state) % 4+1;
				break;
			default:
				return 0;
		}
		point_next_row = ( out->row_patrol - ( out->patrol_state == PatrolUp ) + ( out->patrol_state == PatrolDown ));
		point_next_col = ( out->col_patrol + ( out->patrol_state == PatrolRight ) - ( out->patrol_state == PatrolLeft ));
	}
	return total;
}

int
main()
{
	patrolMap the_map,the_map2;
	pmap_load("day6data.txt",&the_map);
	printf("p1 : %d",pmap_develop(&the_map));
	pmap_load("day6data.txt",&the_map2);
	printf(" , p2 : %d\n",pmap_block(&the_map2));
	return 0;
}
