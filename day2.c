#include <stdio.h>
#include <stdlib.h>


void 
ogcode()
{
	FILE *advr;
	advr=fopen("day2data.txt","r");
	if(advr==NULL){return;}
	char *ina,bufv[1024];
	int inde=0,last=0,now=0,tot=0,inne=0,totin=0,ilo=0,dilf=0;

	while((ina=fgets(bufv,1024,advr))!=NULL){
		
		sscanf(ina,"%d%n",&last,&inne);
		totin+=inne;
		inne=0;
		
		sscanf(ina+totin,"%d%n",&now,&inne);
		totin+=inne;
		inne=0;
		
		if(now==last){goto Floo;}
		
		inde=1+(-2*((now-last)<0));
		dilf=(now-last)*inde;
		
		if(dilf>3||dilf<1){goto Floo;}
		
		last=now;
		
		while(sscanf(ina+totin,"%d%n",&now,&inne)>0){
			dilf=(now-last)*inde;
			if(dilf>3||dilf<1){goto Floo;}
			totin+=inne;
			inne=0;
			last=now;
		}
		
		tot++;
		Floo:
			dilf=0;inde=0;last=0;now=0;inne=0;totin=0;
			ilo++;
	}
	fclose(advr);
	printf("p1:%d\n",tot);
}



int reactorbrute(int *ina,int sina,int called);

int 
reactco(int *ina,int sina,int called)
{
	if(called!=1){
		int inaa[64];
		for(int j=0;j<sina;j++){
			int adder=0;
			for(int k=0;k<sina-1;k++){
				if(k==j){adder=1;}
				inaa[k]=ina[k+adder];
			}
			adder=0;
			if(reactorbrute(inaa,sina-1,1)==1){
				return 1;
			}}}
		return 0;
}

int 
reactorbrute(int *ina,int sina,int called)
{
	int inde=0,dilf=0;	
	if(ina[0]==ina[1]){
		return reactco(ina,sina,called);
	}
	inde=1+(-2*((ina[1]-ina[0])<0));
	dilf=(ina[1]-ina[0])*inde;
	if(dilf>3||dilf<1){
		return reactco(ina,sina,called);		
	}
	for(int i=1;i<sina-1;i++){
		if(ina[i]==ina[i+1]){
			return reactco(ina,sina,called);
		}
		dilf=(ina[i+1]-ina[i])*inde;
		if(dilf>3||dilf<1){
			return reactco(ina,sina,called);
		}
	}
	return 1;
}
	
int 
main(int argc,char *argv[])
{
	FILE *advr;
	advr=fopen("day2data.txt","r");
	if(advr==NULL){return 1;}
	char *ina,bufv[1024];
	int now[64],tot=0,inne=0,totin=0,crl1=0,crl2=0;

	while((ina=fgets(bufv,1024,advr))!=NULL){
		totin=0;
		inne=0;	
		tot=0;
		while(sscanf(ina+totin,"%d%n",&now[tot],&inne)>0){
			totin+=inne;
			inne=0;
			tot++;
		}
		if(tot==0){continue;}
		crl1+=(reactorbrute(now,tot,1)!=0);
		crl2+=(reactorbrute(now,tot,0)!=0);
		
	}
	fclose(advr);
	printf("p1:%d p2:%d\n",crl1,crl2);
	return 0;
}
