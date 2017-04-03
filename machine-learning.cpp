
#include <iostream>
#include <fstream>
#include<string>
#include <iomanip>
#include<conio.h>
#define alpha 7.2                                      //alpha is used to control learning rate of machine.
#define iteration 30                                   //to control nuber of iterations for training.
#define noofinputs 897                                 //number of datset used for training.
void machine1();                                       
void machine2();
void machine3();
using namespace std;

//in this program i have consider an architecture of neuron with 9,9,4 (input,ouput,hidden) layer neurons.
//I have consider the example of neuclear reactor which have 9 sensors and the machine have to take the 
//The values of 9 sensors simultaneously and give suggestion to the control man to RISE,HOLD,STOP,LOWER.
//So the input is 9 sensor values and output is RISE,HOLD,STOP AND WAIT so while training we use iput vectors
//i.e for RISE:1000 HOLD:0100 STOP:0010 LOWER:0001 .


class ineuron
//use to create input neurons
{
public:
	float input;
	float output;
	float weight[9][9];
	friend class hneuron;
};

class hneuron
//use to create hidden layer neurons
{
public:
	float input;
	float output;
	float weight[9][4];
	float t;
	float bais;
	float bweight;
	float activation;
	float sigmoidal(float);
	friend class oneuron;

};
class oneuron
//use to create ouput layer neurons
{
public:
	float input;
	float output;
	float weight;
	float bais;
	float activation;
	float e;
	float bweight;
	float sigmoidal(float);
	friend class network;
	

};

class network
//use to create network of architecture 9 input ,9 hidden and 4  output neurons.
{
public:
	ineuron inrn[9];
	hneuron hnrn[9];
	oneuron onrn[4];
	

};

float hneuron::sigmoidal(float activation)
{
	float bais=1,bweight=0.1;
	bais=bais*bweight;
	float value=activation+bais;
	float sig=1/(1+exp(- value));
//	cout<<"sig"<<sig<<endl;
	value=sig+bais;
	
	return value;
}

float oneuron::sigmoidal(float activation)
{
	float bais=1,bweight=0.1;
	bais=bais*bweight;
	float value=activation+bais;
	float sig=1/(1+exp(- value));
//	cout<<endl<<"osig"<<sig;
	value=sig+bais;
    return value;
	
	
	
}
int main()
{
//cout<<"hi";
//ineuron weigh;
machine2();
machine1();
machine3();
return 0;
}


void machine1()
{
	ifstream myFile;
	ifstream myFile1;
	 myFile.open("C:/Users/hp/Documents/c++ code/input"); //use to give input of 9 sensors.
	 myFile1.open("C:/Users/hp/Documents/c++ code/M1");   //use to give ouput suggestions for machine1.
	float inputall[897][9] ;
	float outputall[897][4] ;
	for(int i=0;i<897;i++)
	{
		for(int j=0;j<9;j++)
		{

		myFile >> inputall[i][j] ;
		if(j<4)
		{
			myFile1 >> outputall[i][j] ;
			//cout<<outputall[i][j];
		}

		}

	}



network net;
float input[897][9];
float desired[897][4];
for(int k=0;k<iteration;k++)
{
//float input[9]={0.0381,0.0041,2.08882535996619,8.84513726839206,10.378674036586,0.033891963449393,1.6001,1.2001,0.14775844802405};

for(int io=0;io<noofinputs;io++)
{
	for(int j=0;j<9;j++)
		{
			input[io][j]=inputall[io][j];
			cout<<input[io][j]<<endl;
		}
	for(int j=0;j<4;j++)
		{
			desired[io][j]=outputall[io][j];
			cout<<desired[io][j]<<endl;
		}
			


if(k==0)
{
for(int i=0;i<9;i++)
{
	for(int j=0;j<9;j++)
	
	{
	
		net.inrn[i].weight[i][j]=0.1;

	
	}
		
 }
}


	for(int i=0;i<9;i++)
{
	net.inrn[i].output=input[io][i];
}
	

float activation=0;
 for(int j=0;j<9;j++)
{
	activation=0;
	for(int i =0;i<9;i++)
	{
	
		activation=activation+net.inrn[i].output*net.inrn[i].weight[i][j];
	}
	net.hnrn[j].activation=activation;
  net.hnrn[j].output=net.hnrn[j].sigmoidal(activation);
  
    
}

if(io==0)
{
for(int i=0;i<9;i++)
{
	for(int j=0;j<4;j++)
	
	{
	
		net.hnrn[i].weight[i][j]=0.1;
		
	
	}
}
}
for(int j=0;j<4;j++)
{
	activation=0;
	for(int i =0;i<9;i++)
	
	{
	
		activation=activation+net.hnrn[i].output*net.hnrn[i].weight[i][j];
	}
	net.onrn[j].activation=activation;
  net.onrn[j].output=net.onrn[j].sigmoidal(activation);
  cout<<endl<<"output"<< net.onrn[j].output;
    
}

for(int i=0;i<4;i++)
{
	//float tt = desired[io][i]-net.onrn[i].output;
	//net.onrn[i].e= tt * tt;
   net.onrn[i].e=desired[io][i]-net.onrn[i].output;
//	net.onrn[i].e=(desired[i]-net.onrn[i].output)*net.onrn[i].output*(1-net.onrn[i].output);
		
	cout<<endl<<"error"<<net.onrn[i].e;
	
/*else 
	{
		cout<<endl<<"No. Of iterations:"<<k;
		break;
	}
*/
}
for(int i=0;i<9;i++)
{
	float r=0,y,yi;
	for(int j=0;j<4;j++)
	
	{
	
	 y=net.hnrn[i].output;
	 yi=1-y;
		 r=r+net.hnrn[i].weight[i][j]*net.onrn[j].e;
		net.hnrn[i].t=y*yi*r;
	
	}
}

for(int i=0;i<4;i++)
{
	net.onrn[i].bweight=net.onrn[i].bweight+alpha*net.onrn[i].bais*net.onrn[i].e;
}

for(int i=0;i<9;i++)
{
	
	for(int j=0;j<4;j++)
	
	{
		net.hnrn[i].weight[i][j]=net.hnrn[i].weight[i][j]+alpha*net.hnrn[i].output*net.onrn[j].e;
	}
}

for(int i=0;i<9;i++)
{
	net.hnrn[i].bweight=net.hnrn[i].bweight+alpha*net.hnrn[i].bais*net.hnrn[i].t;
}



for(int i=0;i<9;i++)
{
	
	for(int j=0;j<9;j++)
	{
		
		net.inrn[i].weight[i][j]=net.inrn[i].weight[i][j]+alpha*net.inrn[i].output*net.hnrn[j].t;
    }
}

}


    myFile.close();
	myFile1.close();
}

float input1[9]={0.1071,	0.0811,	9.921392031	,1.22602817	,10.92835431,	1.504245634	,2.4001	,1.8001,0.887812187};
float activation=0;
	for(int i=0;i<9;i++)
{
	net.inrn[i].output=input1[i];
}
 for(int j=0;j<9;j++)
{
	activation=0;
	for(int i =0;i<9;i++)
	{
	
		activation=activation+net.inrn[i].output*net.inrn[i].weight[i][j];
	}
	net.hnrn[j].activation=activation;
  net.hnrn[j].output=net.hnrn[j].sigmoidal(activation);
  
    
}
for(int j=0;j<4;j++)
{
	activation=0;
	for(int i =0;i<9;i++)
	
	{
	
		activation=activation+net.hnrn[i].output*net.hnrn[i].weight[i][j];
	}
	 net.onrn[j].activation=activation;
  net.onrn[j].output=net.onrn[j].sigmoidal(activation);
  cout<<endl<<"output"<< net.onrn[j].output;
    
}
}


void machine2()
{
	ifstream myFile;
	ifstream myFile1;
	 myFile.open("C:/Users/hp/Documents/c++ code/input");
	 myFile1.open("C:/Users/hp/Documents/c++ code/M2");
	float inputall[897][9] ;
	float outputall[897][4] ;
	for(int i=0;i<897;i++)
	{
		for(int j=0;j<9;j++)
		{

		myFile >> inputall[i][j] ;
		if(j<4)
		{
			myFile1 >> outputall[i][j] ;
			//cout<<outputall[i][j];
		}

		}

	}



network net;
float input[897][9];
float desired[897][4];
for(int k=0;k<iteration;k++)
{
//float input[9]={0.0381,0.0041,2.08882535996619,8.84513726839206,10.378674036586,0.033891963449393,1.6001,1.2001,0.14775844802405};
for(int io=0;io<noofinputs;io++)
{
	for(int j=0;j<9;j++)
		{
			input[io][j]=inputall[io][j];
			cout<<input[io][j]<<endl;
		}
	for(int j=0;j<4;j++)
		{
			desired[io][j]=outputall[io][j];
			cout<<desired[io][j]<<endl;
		}
			


if(k==0)
{
for(int i=0;i<9;i++)
{
	for(int j=0;j<9;j++)
	
	{
	
		net.inrn[i].weight[i][j]=0.1;

	
	}
		
 }
}


	for(int i=0;i<9;i++)
{
	net.inrn[i].output=input[io][i];
}
	

float activation=0;
 for(int j=0;j<9;j++)
{
	activation=0;
	for(int i =0;i<9;i++)
	{
	
		activation=activation+net.inrn[i].output*net.inrn[i].weight[i][j];
	}
	net.hnrn[j].activation=activation;
  net.hnrn[j].output=net.hnrn[j].sigmoidal(activation);
  
    
}

if(io==0)
{
for(int i=0;i<9;i++)
{
	for(int j=0;j<4;j++)
	
	{
	
		net.hnrn[i].weight[i][j]=0.1;
		
	
	}
}
}
for(int j=0;j<4;j++)
{
	activation=0;
	for(int i =0;i<9;i++)
	
	{
	
		activation=activation+net.hnrn[i].output*net.hnrn[i].weight[i][j];
	}
	net.onrn[j].activation=activation;
  net.onrn[j].output=net.onrn[j].sigmoidal(activation);
  cout<<endl<<"output"<< net.onrn[j].output;
    
}

for(int i=0;i<4;i++)
{
	//float tt = desired[io][i]-net.onrn[i].output;
   net.onrn[i].e=desired[io][i]-net.onrn[i].output;
   //net.onrn[i].e=tt * tt;
//	net.onrn[i].e=(desired[i]-net.onrn[i].output)*net.onrn[i].output*(1-net.onrn[i].output);
		
	cout<<endl<<"error"<<net.onrn[i].e;
	
/*else 
	{
		cout<<endl<<"No. Of iterations:"<<k;
		break;
	}
*/
}
for(int i=0;i<9;i++)
{
	float r=0,y,yi;
	for(int j=0;j<4;j++)
	
	{
	
	 y=net.hnrn[i].output;
	 yi=1-y;
		 r=r+net.hnrn[i].weight[i][j]*net.onrn[j].e;
		net.hnrn[i].t=y*yi*r;
	
	}
}

for(int i=0;i<4;i++)
{
	net.onrn[i].bweight=net.onrn[i].bweight+alpha*net.onrn[i].bais*net.onrn[i].e;
}

for(int i=0;i<9;i++)
{
	
	for(int j=0;j<4;j++)
	
	{
		net.hnrn[i].weight[i][j]=net.hnrn[i].weight[i][j]+alpha*net.hnrn[i].output*net.onrn[j].e;
	}
}

for(int i=0;i<9;i++)
{
	net.hnrn[i].bweight=net.hnrn[i].bweight+alpha*net.hnrn[i].bais*net.hnrn[i].t;
}



for(int i=0;i<9;i++)
{
	
	for(int j=0;j<9;j++)
	{
		
		net.inrn[i].weight[i][j]=net.inrn[i].weight[i][j]+alpha*net.inrn[i].output*net.hnrn[j].t;
    }
}

}


    myFile.close();
	myFile1.close();
}

float input1[9]={0.1071,	0.0811,	9.921392031	,1.22602817	,10.92835431,	1.504245634	,2.4001	,1.8001,0.887812187};
float activation=0;
	for(int i=0;i<9;i++)
{
	net.inrn[i].output=input1[i];
}
 for(int j=0;j<9;j++)
{
	activation=0;
	for(int i =0;i<9;i++)
	{
	
		activation=activation+net.inrn[i].output*net.inrn[i].weight[i][j];
	}
	net.hnrn[j].activation=activation;
  net.hnrn[j].output=net.hnrn[j].sigmoidal(activation);
  
    
}
for(int j=0;j<4;j++)
{
	activation=0;
	for(int i =0;i<9;i++)
	
	{
	
		activation=activation+net.hnrn[i].output*net.hnrn[i].weight[i][j];
	}
	 net.onrn[j].activation=activation;
  net.onrn[j].output=net.onrn[j].sigmoidal(activation);
  cout<<endl<<"output"<< net.onrn[j].output;
    
}
}


void machine3()
{
	ifstream myFile;
	ifstream myFile1;
	 myFile.open("C:/Users/hp/Documents/c++ code/input");
	 myFile1.open("C:/Users/hp/Documents/c++ code/M3");
	float inputall[897][9] ;
	float outputall[897][4] ;
	for(int i=0;i<897;i++)
	{
		for(int j=0;j<9;j++)
		{

		myFile >> inputall[i][j] ;
		if(j<4)
		{
			myFile1 >> outputall[i][j] ;
			//cout<<outputall[i][j];
		}

		}

	}



network net;
float input[897][9];
float desired[897][4];
for(int k=0;k<iteration;k++)
{
//float input[9]={0.0381,0.0041,2.08882535996619,8.84513726839206,10.378674036586,0.033891963449393,1.6001,1.2001,0.14775844802405};
for(int io=0;io<noofinputs;io++)
{
	for(int j=0;j<9;j++)
		{
			input[io][j]=inputall[io][j];
			cout<<input[io][j]<<endl;
		}
	for(int j=0;j<4;j++)
		{
			desired[io][j]=outputall[io][j];
			cout<<desired[io][j]<<endl;
		}
			


if(k==0)
{
for(int i=0;i<9;i++)
{
	for(int j=0;j<9;j++)
	
	{
	
		net.inrn[i].weight[i][j]=0.1;

	
	}
		
 }
}


	for(int i=0;i<9;i++)
{
	net.inrn[i].output=input[io][i];
}
	

float activation=0;
 for(int j=0;j<9;j++)
{
	activation=0;
	for(int i =0;i<9;i++)
	{
	
		activation=activation+net.inrn[i].output*net.inrn[i].weight[i][j];
	}
	net.hnrn[j].activation=activation;
  net.hnrn[j].output=net.hnrn[j].sigmoidal(activation);
  
    
}

if(io==0)
{
for(int i=0;i<9;i++)
{
	for(int j=0;j<4;j++)
	
	{
	
		net.hnrn[i].weight[i][j]=0.1;
		
	
	}
}
}
for(int j=0;j<4;j++)
{
	activation=0;
	for(int i =0;i<9;i++)
	
	{
	
		activation=activation+net.hnrn[i].output*net.hnrn[i].weight[i][j];
	}
	net.onrn[j].activation=activation;
  net.onrn[j].output=net.onrn[j].sigmoidal(activation);
  cout<<endl<<"output"<< net.onrn[j].output;
    
}

for(int i=0;i<4;i++)
{
   net.onrn[i].e=desired[io][i]-net.onrn[i].output;
   //float tt = desired[io][i]-net.onrn[i].output;
   //net.onrn[i].e=desired[io][i]-net.onrn[i].output;
   //net.onrn[i].e=tt * tt;
//	net.onrn[i].e=(desired[i]-net.onrn[i].output)*net.onrn[i].output*(1-net.onrn[i].output);
		
	cout<<endl<<"error"<<net.onrn[i].e;
	

}
for(int i=0;i<9;i++)
{
	float r=0,y,yi;
	for(int j=0;j<4;j++)
	
	{
	
	 y=net.hnrn[i].output;
	 yi=1-y;
		 r=r+net.hnrn[i].weight[i][j]*net.onrn[j].e;
		net.hnrn[i].t=y*yi*r;
		}
}
for(int i=0;i<4;i++)
{
	net.onrn[i].bweight=net.onrn[i].bweight+alpha*net.onrn[i].bais*net.onrn[i].e;
}
for(int i=0;i<9;i++)
{	
	for(int j=0;j<4;j++)
		{
		net.hnrn[i].weight[i][j]=net.hnrn[i].weight[i][j]+alpha*net.hnrn[i].output*net.onrn[j].e;
	}
}
for(int i=0;i<9;i++)
{
	net.hnrn[i].bweight=net.hnrn[i].bweight+alpha*net.hnrn[i].bais*net.hnrn[i].t;
}
for(int i=0;i<9;i++)
{	
	for(int j=0;j<9;j++)
	{		
		net.inrn[i].weight[i][j]=net.inrn[i].weight[i][j]+alpha*net.inrn[i].output*net.hnrn[j].t;
    }
}
}
    myFile.close();
	myFile1.close();
}
getch();
cout<<"********Data testing********";
float input1[9]={0.1071,	0.0811,	9.921392031	,1.22602817	,10.92835431,	1.504245634	,2.4001	,1.8001,0.887812187};
float activation=0;
	for(int i=0;i<9;i++)
{
	net.inrn[i].output=input1[i];
}
 for(int j=0;j<9;j++)
{
	activation=0;
	for(int i =0;i<9;i++)
	{
	
		activation=activation+net.inrn[i].output*net.inrn[i].weight[i][j];
	}
	net.hnrn[j].activation=activation;
  net.hnrn[j].output=net.hnrn[j].sigmoidal(activation); 
}
for(int j=0;j<4;j++)
{
	activation=0;
	for(int i =0;i<9;i++)
		{	
		activation=activation+net.hnrn[i].output*net.hnrn[i].weight[i][j];
	}
	 net.onrn[j].activation=activation;
  net.onrn[j].output=net.onrn[j].sigmoidal(activation);
  cout<<endl<<"output"<< net.onrn[j].output;   
}
}

