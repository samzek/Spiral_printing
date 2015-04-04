#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum direction {UP,DOWN,LEFT,RIGHT,NONE} direction;
typedef struct matr_t{
	char num;
	direction dir;
	short ctrl;  
}Matr;

void fill_in_matr(Matr *matr,char *line,int row,int col)
{
	int i,j;
	int k=4;
	for(i=0;i <row;i++){
		for(j=0;j<col;j++){
			matr[j+i*col].num = line[k];
			matr[j+i*col].dir = NONE;
			matr[j+i*col].ctrl = 0;
			k+=2;
		}	
	}

};
void next(direction dir,int *i,int *j)
{
	switch(dir){
		case UP:
			*i-=1;
			break;
		case DOWN: 
			*i+=1;
			break;
		case RIGHT:
			*j+=1;
			break;
		case LEFT:
			*j-=1;
			break;
		case NONE:
			break;
	}
};
direction change_dir(Matr *matr,int i,int j,int m,int n)
{	
	direction dir;
	//Look UP
	if((i-1)!=-1 && matr[j+(i-1)*m].ctrl!=1){
		dir = UP;
	}
	//look DOWN
	else if ((i+1) != n && matr[j+(i+1)*m].ctrl != 1){
		dir = DOWN;}
	//look RIGHT
	else if ((j+1) != m && matr[(j+1)+i*m].ctrl != 1){
		dir = RIGHT;}
	//look LEFT
	else if ((j-1) != -1 && matr[(j-1)+i*m].ctrl != 1){
		dir = LEFT;}
	else{
		dir = NONE;
	}
	return dir;	
};
void print_spiral(Matr *matr,int n,int m)
{
	int c=1,i=0,j=0,i1,j1;
	printf("%c ",matr[j+i*m].num);
	matr[j+i*m].dir=RIGHT;
	matr[j+i*m].ctrl = 1;
	j++;
	Matr *current = &matr[j+i*m];
	direction past = matr[j-1+i*m].dir;
	while(c < n*m){
		printf("%c ",current->num);
		current->ctrl = 1;
		current->dir = past;
		i1=i;
		j1=j;
		next(current->dir,&i1,&j1);
		if(i1 == n || i1 == -1 || j1 == m || j1 == -1 || 
			matr[j1+i1*m].ctrl == 1){
			current->dir = change_dir(matr,i,j,m,n);
			next(current->dir,&i,&j);
			past = current->dir;
			current = &matr[j+i*m];
		}
		else{
			i=i1;j=j1;
			past = current->dir;			
			current = &matr[j+i*m];
		}
		c++;
	}
	printf("\n");	

}
int main(int argc,char **argv){
    FILE *file = fopen(argv[1], "r");
    char line[1024];
    int n,m,i;
    Matr *matr;
    int *el;
    while (fgets(line,1024, file)) {			
		n=atoi(&line[0]);
		m=atoi(&line[2]);
		matr = (Matr *) malloc(n*m*sizeof(Matr));	
		fill_in_matr(matr,line,n,m);
		print_spiral(matr,n,m);
    }
    return 0;

}
