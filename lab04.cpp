/* Name: Seth John
   Pawprint: scjc68
   ECE 3220 Lab 4
   Date: 03/05/2018
   Monday Lab Section Part 2*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

using namespace std;

void error(void);
int* readfile(int numfile);
void offset_go(int* array, double offset,char* newfile1);
void scale_go(int* array, double scale,char* newfile1);
void save_stat(double average,int max, char* filename);
void save_cent(double average, int* array,char* newfile1);
void save_norm(int* array,int maxval, char* newfile1);
void copy(int* array,char* newfile1);
double avg_go(int* array);
int max_go(int* array);
int maxval_go(int numfile);

int* readfile(int numfile) //takes in data from file
{
	int i=1;
	char* filename=(char*)malloc(sizeof(char)*16);
	sprintf(filename,"Raw_data_%02d.txt",numfile); //sets correct file name from raw files given based on numfile
	
	FILE* fileptr=fopen(filename,"r");
	if(fileptr==NULL) //checks for opened file
	{
		cout << "Your file is not opened." << endl;
	}
	
	int length_file=0;
	int maxval=0;
	fscanf(fileptr,"%d %d",&length_file,&maxval); //takes in the length_file and max value
	
	int* array=(int*)malloc(sizeof(int)*(length_file+1));
	*array=length_file; 	//length_file is set as the first value in the array
	for(i=1;i<=length_file;i++) //this loop puts all other values in the array
	{
		fscanf(fileptr,"%d",(array+i));
	}
	fclose(fileptr); //used to close file
	return array;
}

void offset_go(int* array, double offset, char* newfile1)
{
	int i=1;
	int length_file=*array;
	FILE* fileptr=fopen(newfile1,"w");
	
	if(fileptr==NULL)
	{ 
		cout << "Your file is not opened." << endl;
	}
	fprintf(fileptr,"%d %.4f\n",length_file,offset); //length_file and offset value will be in first line of file 
	for(i=1;i<=length_file;i++)  //prints to file using +
	{
		fprintf(fileptr,"%.4f\n",(double)(*(array+i)+offset));
	}
	fclose(fileptr); 
}

void scale_go(int* array, double scale,char* newfile1)
{
	int i=1;
	int length_file=*array;
	FILE* fileptr=fopen(newfile1,"w");
	
	if(fileptr==NULL)
	{
		cout << "Your file is not opened." << endl;
	}
	fprintf(fileptr,"%d %.4f\n",length_file,scale); 
	for(i=1;i<=length_file;i++) //prints to file using *
	{ 
		fprintf(fileptr,"%.4f\n",(double)(*(array+i)*scale));
	}
	fclose(fileptr);
}

void copy(int* array, char* newfile1)
{
	int i=1;
	char* filename=(char*)malloc(sizeof(char)*40);
	
	sprintf(filename,"%s.txt",newfile1);
	FILE* fileptr=fopen(filename,"w");
	for(i=1; i<=*array;i++) //copies input file data to output file data
	{ 
		fprintf(fileptr,"%d\n",*(array+i));
	}
	fclose(fileptr);
	free(filename);
}

void save_stat(double average, int max, char* filename)
{
	FILE* fileptr=fopen(filename,"w");
	fprintf(fileptr,"%.4f %d",average,max); //prints info to stats file
	fclose(fileptr);
}

void save_cent(double average, int* array, char* newfile1)
{
	int i=1;
	int length_file=*array;
	FILE* fileptr=fopen(newfile1,"w");
	
	for(i=1;i<=length_file;i++) //new average will be 0 after centering data
	{ 
		fprintf(fileptr,"%.4f\n",(double)*(array+i)-average); //prints info to center file
	}
	fclose(fileptr);
}

void save_norm(int* array,int maxval,char* newfile1) //checks values between -1 and 1
{
	int i=1;
	int length_file=*array;
	FILE* fileptr=fopen(newfile1,"w");
	
	for(i=1;i<=length_file;i++)
	{
		fprintf(fileptr,"%.4f\n",(double)*(array+i)/(double)maxval); //prints info to normal file
	}
	fclose(fileptr);
}

double avg_go(int* array)
{
	int i=1;
	int length_file=*array;
	double overall_total=0;
	double average=0;
	
	for(i=1;i<=length_file;i++) //all values in array are added
	{ 
		overall_total=overall_total+*(array+i);
	}
	average=overall_total/(double)length_file; //average function
	return average;
}

int max_go(int* array)
{
	int i=1;
	int length_file=*array;
	int max=*(array+1);
	
	for(i=1;i<=length_file;i++) //checks each value against the before value
	{
		if(*(array+i)>max)
		{
			max=*(array+i);
		}
	}
	return max;
}

int maxval_go(int numfile) //takes first line of the file for maxval
{ 
	char* filename=(char*)malloc(sizeof(char)*16);
	sprintf(filename,"Raw_data_%02d.txt",numfile);
	FILE* fileptr=fopen(filename,"r");
	if(fileptr==NULL)
	{
		cout << "Your file is not opened." << endl;
	}
	
	int length_file=0;
	int maxval=0;
	fscanf(fileptr,"%d %d",&length_file,&maxval);
	return maxval;
}

void error(void) //notices error and prints program menu usage
{
	cout << " This is how you should run the program in any order after './a.out' with some or all of the arguments: " << endl;
	cout << " Use './a.out -h' for help \nOR\n ./a.out -n 'file number' -o 'int value' -s 'double value' -r 'Output file name' -S -N -C" << endl;
}

int main(int argc, char* argv[]){
	
	int i = 1;
	int numfile = 0;
	double offset = 0;
	double scale = 0;
	int genflag = 0;
	int statflag = 0;
	int centflag = 0;
	int normflag = 0;
	char* newfile1 = (char*)malloc(sizeof(char)*32);
	char* newfile2 = (char*)malloc(sizeof(char)*32);
	int* array;
	double average=0;
	int max=0;
	int maxval=0;
	double avg_new=0;
	
	for(i=1;i<argc;i++) //loops through whole command line while checking for errors
	{
		if((argv[i][0]=='-')&&(argv[i][1]=='n')) //numfile argument
		{
			i++;
			if(argv[i]==NULL)
			{
				error();
				return 0;
			}
			numfile=atoi(argv[i]); //uses atoi to convert numfile string to int
			if(numfile==0||numfile>20) //incorrect numfile check
			{
				error();
				return 0;
			}
		}
		else if((argv[i][0]=='-')&&(argv[i][1]=='o')) //offset argument 
		{
			i++;
			if(argv[i] == NULL)
			{
				error();
				return 0;
			}
			offset = strtod(argv[i],argv); //strtod used to convert string to double
			if(offset == 0)
			{
				error();
				return 0;
			}
		}
		else if((argv[i][0]=='-')&&(argv[i][1]=='s')) //scale argument
		{
			i++;
			if(argv[i] == NULL)
			{
				error();
				return 0;
			}
			scale=strtod(argv[i],argv);
			if(scale == 0)
			{
				error();
				return 0;
			}
		}
		else if((argv[i][0]=='-')&&(argv[i][1]=='r')) //new name for output file
		{
			i++;
			if(argv[i] == NULL) //incorrect argument check
			{
				error();
				return 0;
			}
			strcpy(newfile2,argv[i]); //sets flag and copies new file data into variable 
			genflag = 1;
		}
		else if((argv[i][0]=='-')&&(argv[i][1]=='h')) //prints program menu usage
		{
			cout << " This is how you should run the program in any order after './a.out' with some or all of the arguments: " << endl;
			cout << " Use './a.out -h' for help \nOR\n ./a.out -n 'file number' -o 'int value' -s 'double value' -r 'Output file name' -S -N -C" << endl;
			return 0;
		}
		else if((argv[i][0]=='-')&&(argv[i][1]=='S')) //stat flag is set
		{
			statflag = 1;
		}
		else if((argv[i][0]=='-')&&(argv[i][1]=='C')) //cent flag is set
		{
			centflag = 1;
		}
		else if((argv[i][0]=='-')&&(argv[i][1]=='N')) //norm flag is set
		{
			normflag = 1;
		}
		else //prints error message for anything else 
		{
			error();
			return 0;
		}
	}
	
	array=readfile(numfile); //uses input file to read in signal

	if(offset!=0) //offset is set from output file 
	{
		sprintf(newfile1,"Offset_data_%02d.txt",numfile);
		offset_go(array,offset,newfile1); 
	}
	if(scale!=0) //scale is set from output file
	{
		sprintf(newfile1,"Scaled_data_%02d.txt",numfile);
		scale_go(array,scale,newfile1);
	}
	if(genflag==1) //-r command that copies the original input into an output file 
	{
		copy(array,newfile2);
	}
	if(statflag==1) //statistics conditions 
	{
		sprintf(newfile1,"Stats_data_%02d.txt",numfile);
		max=max_go(array); 
		average=avg_go(array); 
		save_stat(average,max,newfile1);
	}
	if(centflag==1) //center conditions 
	{
		sprintf(newfile1,"Center_data_%02d.txt",numfile);
		avg_new = avg_go(array); 
		save_cent(avg_new,array,newfile1);
	}
	if(normflag == 1) //normal conditions
	{
		sprintf(newfile1,"Normal_data_%02d.txt",numfile);
		maxval = maxval_go(numfile); 
		save_norm(array,maxval,newfile1);
	}
	
	free(array); //frees up all memory allocated
	free(newfile1);
	free(newfile2);
	return 0;
}
