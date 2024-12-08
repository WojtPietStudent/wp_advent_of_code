#include <stdio.h>
#include <stdlib.h>
int
day5part1()
{
	FILE *flops=fopen("day5data.txt","r");
	
	char anyline[512],*delimme;
	
	int ruleall[2048][2],rulesize=0,linesize=0,ifpo=0,opline[128],curol=0,offo=0,offto=0,total=0;
	
	while((delimme=fgets(anyline,512,flops))!=NULL){
		if(delimme[0]=='\n'){ifpo=1;continue;}
		if(ifpo==0){
			sscanf(delimme,"%d|%d\n",&ruleall[rulesize][0],&ruleall[rulesize][1]);
			rulesize++;
		}else{
			curol=0;
			offto=0;
			do{
				sscanf(&delimme[offto],"%d%n",&opline[curol],&offo);
				offto+=offo;
				curol++;
		
				if(delimme[offto]!='\n'){
				offto++;
				}

			}while(delimme[offto]!='\n');
				
			for(int i=0;i<curol;i++){
				for(int j=0;j<rulesize;j++){
					if(opline[i]==ruleall[j][0]){
						for(int k=i;k>=0;k--){
							if(opline[k]==ruleall[j][1]){goto enderl;}
						}
					}
				}
			}
			total+=opline[(curol-1)/2];
			enderl:
			continue;
		}
	}
	fclose(flops);
	return total;
}

	
int
day5part2()
{
	FILE *flops=fopen("day5data.txt","r");
	
	char anyline[512],*delimme;
	
	int ruleall[2048][2],rulesize=0,linesize=0,ifpo=0,opline[128],curol=0,offo=0,offto=0,total=0,addit=0;
	
	while((delimme=fgets(anyline,512,flops))!=NULL){
		if(delimme[0]=='\n'&&ifpo==0){ifpo=1;continue;}
		if(ifpo==0){
			sscanf(delimme,"%d|%d\n",&ruleall[rulesize][0],&ruleall[rulesize][1]);
			rulesize++;
		}else{
			curol=0;
			offto=0;
			do{
				sscanf(&delimme[offto],"%d%n",&opline[curol],&offo);
				offto+=offo;
				curol++;
				if(delimme[offto]!='\n'){
					offto++;}
			}while(delimme[offto]!='\n');
			addit=0;
			gohere:
			for(int i=0;i<curol;i++){
				for(int j=0;j<rulesize;j++){
					if(opline[i]==ruleall[j][0]){
						for(int k=i;k>=0;k--){
							if(opline[k]==ruleall[j][1]){
								addit=1;
								opline[i]=ruleall[j][1];
								opline[k]=ruleall[j][0];
								goto gohere;}}}}}
			if(addit==1){total+=opline[(curol-1)/2];}}}
	fclose(flops);
	return total;
}



int
main()
{
	printf("p1 : %d , p2 : %d\n",day5part1(),day5part2());	
	return 0;
}
