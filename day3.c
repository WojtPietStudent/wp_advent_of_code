#include <stdio.h>
#include <stdlib.h>

	
int
part1d3()
{
	FILE *mulf=fopen("day3data.txt","r");
	
	int muld=0,num1l=0,num2l=0,totres=0;
	char num1[16],num2[16],opch,cmps[]="mul(,)";

	while((opch=fgetc(mulf))!=EOF){
		if(muld==4){
			if(opch>='0'&&opch<='9'){
				num1[num1l]=opch;
				num1l++;
				continue;
			}else if(opch==',' && num1l!=0){
				num1[num1l]='\b';
				muld++;
				continue;
			}
		}else if(muld==5){
			if(opch>='0'&&opch<='9'){
				num2[num2l]=opch;
				num2l++;
				continue;
			}else if(opch==')' && num2l!=0){
				num2[num2l]='\b';
				totres+=atoi(num1)*atoi(num2);
			}	
		}else if(opch==cmps[muld]){
			muld++;
			continue;
		}
		num1l=0;
		num2l=0;
		muld=0;	
	}
	fclose(mulf);
	return totres;
}


int
part2d3()
{
	FILE *mulf=fopen("day3data.txt","r");
	
	int muld=0,
	    num1l=0,num2l=0,totres=0,
	    numdo=0,numdont=0,enable=1;
	char num1[16],num2[16],opch,
	     cmps[]="mul(,)",
	     cdo[]="do()",
	     cdont[]="don't()";

	while((opch=fgetc(mulf))!=EOF){
		if(opch==cdo[numdo]||opch==cdont[numdont]){
			enable+=((numdo==3) && enable==0);
			enable-=((numdont==6) && enable==1);
			numdo+=cdo[numdo]==opch;
			numdont+=cdont[numdont]==opch;
			continue;
		}
		numdo=0;
		numdont=0;
		if(enable==1){
			if(muld==4){
				if(opch>='0'&&opch<='9'){
					num1[num1l]=opch;
					num1l++;
					continue;
				}else if(opch==',' && num1l!=0){
					num1[num1l]='\b';
					muld++;
					continue;
				}
			}else if(muld==5){
				if(opch>='0'&&opch<='9'){
					num2[num2l]=opch;
					num2l++;
					continue;
				}else if(opch==')' && num2l!=0){
					num2[num2l]='\b';
					totres+=atoi(num1)*atoi(num2);
				}	
			}else if(opch==cmps[muld]){
				muld++;
				continue;
			}
		}
		num1l=0;
		num2l=0;
		muld=0;	
	}
	fclose(mulf);
	return totres;
}


int
main()
{
	printf("%d\n",part1d3());
	printf("%d\n",part2d3());
	return 0;
}
