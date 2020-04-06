#include<iostream>
#include<fstream>
#include<cstring>
using namespace std;

void pass1();
void writemnt(string line, int &mntc, int &mdtc);
void writemdt(string line, int &mdtc);
void writeout(string line);
void pass2();
void mdt(int x, char ala2[]);
int mnt(string line1, string line);
int main()
{
	remove("mdt.txt");
	remove("mnt.txt");
	remove("output.txt");
	remove("output1.txt");
	pass1();
	pass2();
 	return 0;
}
void pass1()
{
	int mntc=0, mdtc=1, ala[30], i, a=0, k;
	ifstream fin;
	string line;
	fin.open("input.txt", ios::in);
	do
	{
		a=0;
		getline(fin,line);
		if(line=="MACRO")
		{
			getline(fin,line);
			writemnt(line, mntc, mdtc);
			writemdt(line, mdtc);
			for(i=0;line[i]!=' ';i++);
			for(int j=i;line[j]!='\0';j++)
			{
				if(line[j]!='&' &&line[j]!=',' &&line[j]!=' ')
				{
					ala[a]=line[j];
					a++;
				}
			}
			do
			{
				getline(fin, line);
				for(k=0;line[k]!=' ';k++);
				for(int j=k;line[j]!='\0';j++)
				{
					for(int l=0;l<a;l++)
					{
						if(ala[l]==line[j])
						{
							line[j-1]='#';
							char v=l;
							line[j]=l+'0';
							break;
						}
					}
				}
				writemdt(line, mdtc);
			}while(line!="MEND");
		}
		else
		{
			writeout(line);
		}
	}while(!fin.eof());
	fin.close();
}
void writemnt(string line, int &mntc, int &mdtc)
{
	mntc++;
	ofstream fout;
	fout.open("mnt.txt", ios::out|ios::app);
	fout<<mntc<<" ";
	fout<<line<<" ";
	fout<<mdtc<<endl;
	fout.close();
}
void writemdt(string line, int &mdtc)
{
	ofstream fout;
	fout.open("mdt.txt", ios::out|ios::app);
	fout<<mdtc<<" ";
	fout<<line<<endl;
	fout.close();
	mdtc++;
}
void writeout(string line)
{
	ofstream fout;
	fout.open("output.txt", ios::out|ios::app);
	fout<<line<<endl;
	fout.close();
}
void pass2()
{
	string line="", line1="";
	char temp[300];
	int i, j, k, flag=1;
	ifstream fin;
	fin.open("output.txt", ios::in);
	ofstream fout;
	while(!fin.eof())
	{
		getline(fin, line);
		int a=0;
		for(j=0;line[j]!=' ' && line[j]!='\0';j++)
		{
			temp[a++]=line[j];
		}
		temp[a]='\0';
		line1=temp;
		flag=mnt(line1, line);
		if(flag==0)
		{
			fout.open("output1.txt", ios::out|ios::app);
			fout<<line<<endl;
			fout.close();
		}
	}	
	fin.close();
}
int mnt(string line1, string line)
{
	int x=0, a=0, flag=1, i, k, j;
	char ala2[100], temp[300];
	string line2="", line3="";
	ifstream fmnt;
	fmnt.open("mnt.txt", ios::in);
	while(!fmnt.eof())
	{
		getline(fmnt, line2);
		for(j=0;line2[j]!=' ';j++);
		j++;
		a=0;
		while(line2[j]!=' ')
		{
			temp[a++]=line2[j];
			j++;
		}
		temp[a]='\0';
		line3=temp;
		x=0;
		j++;
		if(line3==line1)
		{
			flag=1;
			int b=0;
			for(k=j;line2[k]!=' ';k++);
			k++;
			while(line2[k]!='\0')
			{
				x=x*10+(line2[k]-'0');
				k++;
			}  
			for(i=0;line[i]!=' ';i++);
			i++;
			a=0;
			for(j=i;line[j]!='\0';j++)
			{
				if(line[j]!=',' && line[j]!=' ')
				ala2[a++]=line[j];
			}	
			mdt(x, ala2);
			break;
		}
		else
		{
			flag=0;
		}
	}
	fmnt.close();
	return flag;
}
void mdt(int x, char ala2[])
{
	string line4="";
	ifstream fmdt;
	char temp[300];
	int y=0, a, flag=1, i, j, k;
	fmdt.open("mdt.txt", ios::in);
	ofstream fout;
	fout.open("output1.txt", ios::out|ios::app);
	while(!fmdt.eof())
	{
		y=0;
		getline(fmdt, line4);
		for(i=0;line4[i]!=' ';i++)
		{
			y=y*10+(line4[i]-'0');
		}
		if(x==y)
		{
			while(line4!="MEND")
			{
				getline(fmdt, line4);
				a=0;
				for(i=0;line4[i]!=' ';i++);
				i++;
				for(j=i;line4[j]!=' ' && line4[j]!='\0';j++)
				{
					temp[a++]=line4[j];
				}
				temp[a]='\0';
				if(strcmp(temp, "MEND")==0)
				{
					flag=0;
					break;
				}
				temp[a++]=' ';
				j++;
				for(k=j;line4[k]!='\0';k++)
				{
					if(line4[k]=='#')
					{
						int u=line4[k+1]-'0';
						temp[a++]=ala2[u];
						k++;
					}
					else
					{
						temp[a++]=line4[k];	
					}	
				}
				temp[a]='\0';
				line4=temp;				
				fout<<line4<<endl;
			}
			if(flag==0)
			{
				break;
			}
		}
	}
	fmdt.close();
	fout.close();
}

