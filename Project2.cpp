#include<iostream>
#include<fstream>
using namespace std;
class Job
{
	int ApplNo,post,points,total;
	char name[30];
	public:
		void intro()
		{
			cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
			cout<<"\n\t\t\t\t\t\t    JOB APPLICATION MANAGEMENT SYSTEM"<<endl;
			cout<<endl<<endl;
			cout<<"\t\t\t\t\t\t           Project by Team DEJ"<<endl<<endl;
			cout<<"\t\t\t\t\t\t        1914014 - Druvi Tendulkar"<<endl<<"\t\t\t\t\t\t        1914015 - Enid Fernandes"<<endl<<"\t\t\t\t\t\t        1914018 - Jaysel Silveira"<<endl;
			cout<<endl<<endl<<endl<<endl<<endl<<endl;
			cout<<"\n\t\t\t\t\t\t      Press Enter key to continue."<<endl;
			cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
			cin.get();
		}
	   int getApplNo()
	   {
		    return ApplNo;
	   }
	   void modName(int a,char *n)
       {
		   ApplNo=a;
		   strcpy(name,n);
	   }
	   void modAppNum(int a,int n)
       {
		   ApplNo=a;
		   ApplNo=n;
	   }
	void read();
	void write();
	void modify();
	void Delete(int);
};

void Job::read()
{
	total=0;
	cout<<endl<<"READING THE DETAILS OF THE APPLICANT... "<<endl<<endl;
	cout<<"Enter the Applicant Number. ";
	cin>>ApplNo;
	cin.ignore();
	cout<<endl<<"Enter the name of the applicant. ";
	cin.getline(name,30);
	cout<<endl<<"Criteria Number 1: Academic Score"<<endl;
	cout<<"Criteria Number 2: Communication Skills"<<endl;
	cout<<"Criteria Number 3: Presentation Skills"<<endl;
	for(int i=0;i<3;i++)
	{
			cout<<"Enter the points (out of 100) of the applicant for Criteria No."<<i+1<<": ";
			cin>>points;
			total=total+points;
	}
	cout<<endl<<"Post Number 1: Mechanical Engineer"<<endl;
	cout<<"Post Number 2: Computer Engineer"<<endl;
	cout<<"Post Number 3: Electronics Engineer"<<endl;
	cout<<"Post Number 4: Civil Engineer"<<endl;
	cout<<"Enter the number of the post (1-4) the applicant is applying for. ";
	cin>>post;
}
void Job::write()
{
	cout<<"Applicant Number = "<<ApplNo<<endl;
	cout<<"Name = "<<name<<endl;
    cout<<"Total Points = "<<total<<endl;
    cout<<"Post Number = "<<post<<endl<<endl;
}
void Job::modify()
{
	int toMod,counter=0,found=0,newAN;
	char opt,newN[30];
	fstream f;
	Job j;
	f.open("JobApplicants.dat",ios::in|ios::out|ios::binary|ios::ate);
	cout<<endl<<"Enter the Applicant Number of the Applicant whose details you want to modify. ";
	cin>>toMod;
	cout<<endl;
	f.seekg(0,ios::beg);
	while(f.read((char*)&j,sizeof(j)))
		{
			counter++;
			if(j.getApplNo()==toMod)
			{
				found=1;
				cout<<"Data before updation: "<<endl;
				j.write();
				break;
			}
		}
		if(f.eof())
			f.clear();
		if(found==0)
		{
			cout<<"Invalid Applicant Number. "<<endl;
			f.close();
		}
		else
		{
			cout<<endl<<"To modify the Applicant Number of the Applicant, press 'A' or 'a'."<<endl;
			cout<<"To modify the name of the Applicant, press 'N' or 'n'."<<endl;
			cin>>opt;
			if(opt=='N'||opt=='n')
			{
				cout<<"Applicant Number found at location "<<counter<<endl;
				cout<<endl<<"Enter the name you would like to update with. ";
				cin.ignore();
				cin.getline(newN,30);
				j.modName(toMod,newN);
				f.seekp((counter-1)*sizeof(j),ios::beg);
				f.write((char*)&j,sizeof(j));
				cout<<endl<<"Viewing the updated data:"<<endl;
	    		j.write();
	    		f.close();
			}
			else if(opt=='A'||opt=='a')
			{
				cout<<endl<<"Applicant Number found at location "<<counter<<endl;
				cout<<endl<<"Enter the Applicant Number you would like to update with. ";
				cin>>newAN;
				j.modAppNum(toMod,newAN);
				f.seekp((counter-1)*sizeof(j),ios::beg);
				f.write((char*)&j,sizeof(j));
				cout<<endl<<"Viewing the updated data:"<<endl;
	    		j.write();
	    		f.close();
			}
			else
			{
				cout<<"Invalid key pressed. "<<endl;
				f.close();
			}
		}	
}
void Job::Delete(int del)
{
	int found=0;
	Job j;
	ifstream iF;
	ofstream oF;
	iF.open("JobApplicants.dat",ios::in|ios::out|ios::binary|ios::ate);
	iF.seekg(0,ios::beg);
	while(iF.read((char*)&j,sizeof(j)))
	{
		if(j.getApplNo()==del)
		{
			found=1;
			break;
		}
	}
	if(iF.eof())
		iF.clear();
	if(found==0)
	{
		cout<<"Invalid Applicant Number. "<<endl;
		iF.close();
	}
	else
	{
		oF.open("Temp.dat",ios::in|ios::out|ios::binary|ios::app);
		iF.seekg(0,ios::beg);
		while(iF.read((char*)&j,sizeof(j)))
		{
			if(j.getApplNo()!=del)
			{
				oF.write((char*)&j,sizeof(j));
			}
		}
		iF.close();
		oF.close();
		remove("JobApplicants.dat");
		rename("Temp.dat","JobApplicants.dat");
		cout<<endl<<"Application Deleted."<<endl;
	}
}

int main()
{
	Job j;
	fstream f;
	int ch,del;
	char cont;
	j.intro();
	do
	{
		cout<<endl<<"Select your Option (1-4): "<<endl;;
	    cout<<"1: Reading an Applicant."<<endl;
	    cout<<"2: Displaying the List of Applicants."<<endl;
	    cout<<"3: Modifying the details."<<endl;
	    cout<<"4: Deleting an Application."<<endl;
	    
	    cin>>ch;
	    switch(ch)
	    {
	    	case 1:f.open("JobApplicants.dat",ios::out|ios::binary|ios::app);
         	f.clear();
			j.read();				
	        f.write((char*)&j,sizeof(j));
	        f.close();
		    break;
		    
	    	case 2:f.open("JobApplicants.dat",ios::in|ios::binary|ios::ate);
	    	cout<<endl<<"PRINTING THE DETAILS OF ALL THE APPLICANTS... "<<endl<<endl;
	    	f.clear();
			f.seekg(0,ios::beg);
	        while(f.read((char*)&j,sizeof(j)))
	        {
				j.write();
			}
			if(f.eof())
				f.clear();
			f.close();
			break;
			
			case 3:cout<<endl<<"MODIFYING THE DETAILS OF AN APPLICANT..."<<endl<<endl;
			j.modify();
			break;
			
			case 4:cout<<endl<<"DELETING AN APPLICATION..."<<endl<<endl;
			cout<<"Enter the Applicant Number of the application you want to delete. "<<endl;
			cin>>del;
			j.Delete(del);
			break;
			
			default:cout<<endl<<"Invalid Input."<<endl;
			break;
	    }
	    cout<<endl<<"Do you want to continue? \nIf yes, press 'Y' or 'y'. \nIf no, press 'N' or 'n'."<<endl;
	    cin>>cont;
	}while(cont=='Y'||cont=='y');
	cout<<endl<<"Thanks for using JOB APPLICATION MANAGEMENT SYSTEM..."<<endl;
}
