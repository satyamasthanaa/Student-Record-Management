#include<fstream>
#include<stdio.h>
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<iomanip>
#include<ctype.h>
using namespace std;
int no;

class record
{
	public:	char age[5];
			char standard[5];
			char rollno[20];
			char name[10];
			char busno[5];
		  	char ind[5];
			char mentor[10];
			char parentno[10];
}
rec[100],found[100];

char st_no[20],rt_name[20];
void sortrecord()
{
	int i,j;
	record temp;
	for(int i=0;i<no-1;i++)
		for(int j=0;j<no-i-1;j++)
			if(strcmp(rec[j].name,rec[j+1].name)>0)
			{
				temp=rec[j];
				rec[j]=rec[j+1];
				rec[j+1]=temp;
			}
}


void retrieve_record(char*index)
{
	fstream file;
	int i=0;
	char age[5],standard[5],rollno[20],name[20],busno[5],mentor[10],parentno[10],ind[5];
	file.open("record.txt",ios::in);
	for(i=0;i<no;i++)
	{
		file.getline(ind,5,'|');
		file.getline(name,20,'|');
		file.getline(rollno,20,'|');
		file.getline(age,5,'|');
		file.getline(standard,5,'|');
		file.getline(busno,5,'|');
		file.getline(mentor,10,'|');
		file.getline(parentno,10,'\n');
		if(strcmp(index,ind)==0)
		{cout<<"\t************************************************************\n\n";
			cout<<"student details:\n";
			cout<<"\n\nrollno\tname\t\tage\tstandard\tbusno\tmentor\tparentno\n";
			cout<<rollno<<"\t"<<name<<"\t\t";
			cout<<age<<"\t"<<standard<<"\t\t"<<busno<<"\t"<<mentor<<"\t"<<parentno<<"\n";

		}
	
	}
	file.close();
}
void retrieve_details()
{
	fstream file;
	char age[5];
	char standard[5];
	char rollno[20],name[20];
	char busno[5],mentor[10],parentno[10];
	char ind[5];
	char chrollno[20],index[20][20];
	file.open("secindex.txt",ios::in);
	int k=0;
	for(int i=0;i<no;i++)
	{
		file.getline(name,20,'|');
		file.getline(rollno,20,'|');
		file.getline(ind,4,'\n');
		if(strcmp(name,rt_name)==0)
		{
			strcpy(found[k].name,name);
			strcpy(found[k].rollno,rollno);
			strcpy(index[k],ind);
			k++;
		}
	}
	file.close();
	if(k==1)
	{
		retrieve_record(index[0]);
		return;
	}
	else
	{
		cout<<"choose the candidates rollno\n";
		for(int i=0;i<k;i++)
			cout<<"rollno:"<<found[i].rollno<<"\t name:"<<found[i].name<<endl;
	}
	cin>>chrollno;
	for(int i=0;i<k;i++)
	{
		if(strcmp(chrollno,found[i].rollno)==0)
		{
			retrieve_record(index[i]);
			return;
		}
	}
	cout<<"invalid entry\n";
	return;
}

void delete_record(char *indx)
{
	int i;
	fstream file1,file2;
	char age[5];
	char standard[5];
	char rollno[20],name[20];
	char busno[5],mentor[10],parentno[10];
	char ind[5];
	char index[20][20];
	file2.open("record.txt",ios::in);
	for(i=0;i<no;i++)
	{
		file2.getline(ind,4,'|');
		file2.getline(name,20,'|');
		file2.getline(rollno,20,'|');
		file2.getline(age,5,'|');
		file2.getline(standard,5,'|');
        file2.getline(busno,5,'|');
	file2.getline(mentor,10,'|');
	file2.getline(parentno,10,'\n');
		strcpy(index[i],ind);
		strcpy(rec[i].rollno,rollno);
		strcpy(rec[i].name,name);
		strcpy(rec[i].age,age);
		strcpy(rec[i].standard,standard);
		strcpy(rec[i].busno,busno);
		strcpy(rec[i].mentor,mentor);
		strcpy(rec[i].parentno,parentno);
    }
	int flag=-1;
	for(i=0;i<no;i++)
	{
		if(strcmp(index[i],indx)==0)
		{
			flag=i;
		}
	}
	if(flag==-1)
	{
		cout<<"error....!\n";
		return;
	}
	for(i=flag;i<no;i++)
	{
		rec[i]=rec[i+1];
	}
	no--;
	cout<<"\n record deleted\n";
	file2.close();
	file1.open("secindex.txt",ios::out);
	file2.open("record.txt",ios::out);
	for(i=0;i<no;i++)
	{
		file1<<rec[i].name<<"|"<<rec[i].rollno<<"|"<<i<<"\n";
		file2<<i<<"|"<<rec[i].name<<"|"<<rec[i].rollno<<"|"<<rec[i].age<<"|"<<rec[i].standard<<"|"<<rec[i].busno<<"|"<<rec[i].mentor<<"|"<<rec[i].parentno<<"\n";
	}
	file1.close();
	file2.close();
}

void delete_index(char*nam)
{
	fstream file;
	char age[5],standard[5],rollno[20],name[20],busno[5],ind[5],mentor[10],parentno[10];
	char chrollno[20],index[20][20];
	int i,k=0;
	file.open("secindex.txt",ios::in);
	for(i=0;i<no;i++)
	{
		file.getline(name,20,'|');
		file.getline(rollno,20,'|');
		file.getline(ind,4,'\n');
		if(strcmp(nam,name)==0)
		{
			strcpy(found[k].name,name);
			strcpy(found[k].rollno,rollno);
			strcpy(index[k],ind);
			k++;
		}
	}
	file.close();
	if(k==1)
	{
		delete_record(index[0]);
		return;
	}
	else
	{
		cout<<"Choose the candidate rollno\n";
		for(i=0;i<k;i++)
			cout<<"rollno: "<<found[i].rollno<<"\tName: "<<found[i].name<<endl;
	}
	cin>>chrollno;
	for(i=0;i<k;i++)
	{
		if(strcmp(chrollno,found[i].rollno)==0)
		{
			delete_record(index[i]);
			return;
		}
	}
	cout<<"Inavalid Entry\n";
	return;
}

void login()
{
	
	char pass[10];
	char user[]="SK";
	char us[10];
	char p[]="1234";
	int att=0;
	cout<<"\t************************************************************\n\n";
	cout<<"\t.........................LOGIN PAGE...........................\n\n";
	cout<<"\t************************************************************\n\n";
	
	label :cout<<"\n username:\n";
	cin>>us;

	if(strcmp(us,user)!=0)
	{cout<<"\n invalid username\n";
	exit(0);
	}		
	else{
		cout<<"password:\n";
		cin>>pass;
			if(strcmp(pass,p)==0)
			{  return;
			}
			else
			{
			cout<<"wrong password\n";
			exit(0);
			}
	
	}


}
int main()
{
	login();
	
	
	fstream file1,file2;
        file1.open("secindex.txt",ios::out);
	file2.open("record.txt",ios::out);
	file1.close();
	file2.close();
	char rt_rollno[5],st_name[15],st_rollno[5];
	char age[5],standard[5],name[20],busno[5],ind[5],mentor[10],parentno[10];
	int i,z,j,n,flag,flag1,choice;
	cout<<"\n\t-->> Welcome to Student database monitoring system <<-- 	\n";
		cout<<"\t************************************************************\n\n";
	for(;;)
	{cout<<"\n\t************************************************************\n\n";
		cout<<"\nChoose the option:\n1:Add \n2:Search \n3:Delete \n4:Display \n5:Exit\n";
		cin>>choice;
		//int k;
		switch(choice)
		{
			
                   case 1: {
				file1.open("secindex.txt",ios::out|ios::app);
				file2.open("record.txt",ios::out|ios::app);
				
				cout<<"Enter the no. of students:\n";
					cin>>z;
					
                    n=no;
					for(j=0;j<z;j++)
					{
					    i=n+j;
						cout<<"Enter the name:";
						cin>>rec[i].name;
						cout<<"rollno:";
						cin>>rec[i].rollno;
						cout<<"age:";
						cin>>rec[i].age;
						cout<<"standard:";
						cin>>rec[i].standard;
						cout<<"busno:";
						cin>>rec[i].busno;
						cout<<"mentor name:";
						cin>>rec[i].mentor;
						cout<<"parent's number:";
						cin>>rec[i].parentno;
			file1<<rec[i].name<<"|"<<rec[i].rollno<<"|"<<i<<"\n";
       					file2<<no++<<"|"<<rec[i].name<<"|"<<rec[i].rollno<<"|"<<rec[i].age<<"|"<<rec[i].standard<<"|"<<rec[i].busno<<"|"<<rec[i].mentor<<"|"<<rec[i].parentno<<"\n";
						}

					sortrecord();
					
					file1.close();
					file2.close();
					break;
}

			case 2:	{cout<<"Enter the name of the record to be searched:\n";
					cin>>st_name;
					file1.open("secindex.txt",ios::in);
					if(!file1)
					{
						cout<<"File creation error\n";
						exit(0);
					}
					flag1=0;
					for(i=0;i<no;i++)
					{
						file1.getline(rt_name,20,'|');
						file1.getline(st_rollno,20,'|');
						file1.getline(st_no,4,'\n');
						if(strcmp(st_name,rt_name)==0)
						{
							retrieve_details();
							flag1=1;
							break;
						}
					}
					if(!flag1)
						cout<<"Record search failed\n";
					file1.close();
					break;}

			case 3:	{cout<<"Enter the name of the record to be deleted:\n";
					cin>>st_name;
					file1.open("secindex.txt",ios::in);
					if(!file1)
					{
						cout<<"File creation error\n";
						exit(0);
					}
					flag=0;
					for(i=0;i<no;i++)
					{
						file1.getline(rt_name,20,'|');
						file1.getline(st_rollno,20,'|');
						file1.getline(ind,4,'\n');
						if(strcmp(st_name,rt_name)==0)
						{
							delete_index(rt_name);
							flag=1;
							break;
						}
					}
					if(!flag)
						cout<<"Deletion failed\n";
					file1.close();
					break;}

			case 4:	{cout<<"\t************************************************************\n\n";
cout<<"rollno\tNAME\tage\tstandard\tbusno\tmentor\tparentno\n";
								for(i=0;i<no;i++)
					{
                        
			cout<<rec[i].rollno<<"\t"<<rec[i].name<<"\t"<<rec[i].age<<"\t"<<rec[i].standard<<"\t\t"<<rec	[i].busno<<"\t"<<rec[i].mentor<<"\t"<<rec[i].parentno<<"\n";
}
					break;}
			
			case 5: {exit(0);
					break;}
		}
	}
	
}


