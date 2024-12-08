#include <stdio.h>
#include <stdlib.h>

int 
compint(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int 
main(int argc,char *argv[])
{
	FILE *advr;
	advr=fopen("../data/day1data.txt","r");
	int list1[1024],list2[1024],ll=0,lista,listb;
	while(fscanf(advr,"%d %d\n",&list1[ll],&list2[ll])>0){
		ll++;	
	}
	qsort(list1,ll,sizeof(list1[0]),compint);
	qsort(list2,ll,sizeof(list2[0]),compint);
	for(int i=0;i<ll;i++){
		int occucnt=0;
		lista+=abs(list1[i]-list2[i]);
		
		for(int j=0;j<ll;j++){
			occucnt+=list1[i]==list2[j];
		}	
		listb+=occucnt*list1[i];
	}
	fclose(advr);
	printf("p1:%d , p2:%d\n",lista,listb);
	return 0;
}
