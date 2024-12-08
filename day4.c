#include <stdio.h>
#include <stdlib.h>

int
main()
{
	FILE *xmasf=fopen("day4data.txt","r");
	if(xmasf==NULL){
		perror("xmasf:");
		return 1;
	}

	int sizey=0,sizex=0,bootx=0,totx=0,tota=0;
	char searchme[140][140],getme;
	int taballx[140*140],sita=0,
	    taballa[140*140],sia=0;
	while((getme=fgetc(xmasf))!=EOF){
		if(getme=='X'){
			taballx[sita]=140*(sizey)+bootx;
			sita++;
		}else if(getme=='A'){
			taballa[sia]=140*(sizey)+bootx;
			sia++;
		}

		if(getme=='\n'){
			if(sizex==0){
				sizex=bootx;
			}
			sizey++;
			bootx=0;

		}else if(sizex==0){
			bootx++;
			searchme[0][bootx-1]=getme;
		}else{
			searchme[sizey][bootx]=getme;
			bootx++;
		}
	}

	for(int k=0;k<sita;k++){
		int i=taballx[k]/140,j=taballx[k]%140;
			totx+=(j<=136 && searchme[i][j+1]=='M' && searchme[i][j+2]=='A' && searchme[i][j+3]=='S');
			totx+=(j>=3 && searchme[i][j-1]=='M' && searchme[i][j-2]=='A' && searchme[i][j-3]=='S');
			totx+=(i<=136 && searchme[i+1][j]=='M' && searchme[i+2][j]=='A' && searchme[i+3][j]=='S');
			totx+=(i>=3 && searchme[i-1][j]=='M' && searchme[i-2][j]=='A' && searchme[i-3][j]=='S');
			totx+=(i<=136 && j<=136 && searchme[i+1][j+1]=='M' && searchme[i+2][j+2]=='A' && searchme[i+3][j+3]=='S');
			totx+=(i>=3 && j>=3 && searchme[i-1][j-1]=='M' && searchme[i-2][j-2]=='A' && searchme[i-3][j-3]=='S');
			totx+=(i<=136 && j>=3 && searchme[i+1][j-1]=='M' && searchme[i+2][j-2]=='A' && searchme[i+3][j-3]=='S');
			totx+=(i>=3 && j<=136 && searchme[i-1][j+1]=='M' && searchme[i-2][j+2]=='A' && searchme[i-3][j+3]=='S');
	}
	for(int i=0;i<sia;i++){
		int y=taballa[i]/140,x=taballa[i]%140;
		tota+=	((y >= 1 && y <= 138 && x >= 1 && x <= 138) &&
			(((searchme[y+1][x+1]=='M'&&searchme[y-1][x-1]=='S')||(searchme[y+1][x+1]=='S' && searchme[y-1][x-1]=='M')) &&
			((searchme[y+1][x-1]=='M'&&searchme[y-1][x+1]=='S')||(searchme[y+1][x-1]=='S' && searchme[y-1][x+1]=='M'))));
	}	

	printf("p1: %d p2: %d\n",totx,tota);
	fclose(xmasf);
	return 0;
}
