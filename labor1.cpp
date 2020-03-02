#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <time.h>

using namespace std;

int n=0;
#define OK 100
#define ERROR 0

ofstream file;
clock_t st, fs;

void bektrek(int *tomb);
int bektrek_keres(int *tomb, int poz);
int bektrek_mvr(int *tomb, int poz);
int bektrek_forw(int *tomb, int poz);
void kiirtomb(int *tomb);
int *h;

int main()
{
    cout << "Mekkora legyen a tabla merete: ";
    cin >> n;
    h= new int[n+1];
    int *tomb = new int[n];
    
    for(int i=0; i<=n;++i)
        h[i]=1;
        
    bektrek(tomb);
    fflush(stdin);
    system("pause");
	return 0;
}

void bektrek(int *tomb)
{
    int s=0;
    file.open("ki.txt");
	while(1)
	{
		cout << endl << "1:  backtarcking" << endl;
		cout << "2: backtarcking + MVR" << endl;
		cout << "3: backtarcking + MVR + Forward checking" << endl;
		cout << "4: kilepes "<<endl;
		cout << endl << "Kerem a kivant modszert:";
		cin >> s;
		st = clock();
		switch(s)
		{
			case 1:
				bektrek_keres(tomb,0);
				break;
			case 2:
				bektrek_mvr(tomb,0);
				break;
			case 3:
				bektrek_forw(tomb,0);
				break;
			case 4:
				break;
		}
		if(s == 4)
			break;
	}
		cout << "Backtreking vege";
		file.close();
}

int bektrek_forw(int *tomb, int poz)
{
    
    //  leallasi feltetel
    if ( poz == n)
        {
               kiirtomb(tomb);
                return OK;
        }
        //  sorra kiprobaljuk a lehetseges ertekeket
    for(int ert=1; ert<=n; ++ert)
    {
        if(h[(ert+poz+1)%n]==1)
        {
                h[ert]=0;
                tomb[poz]=(ert+poz+1)%n;
               
                //  megnezuk, hogy konszitens-e
                int res=0;
                if (poz==0)
                {
                      res = bektrek_forw(tomb,poz+1);
                }
                else
                {
                      bool oke=true;
                      for (int i=0;i<poz;++i)
                      {
                          if (tomb[i]==tomb[poz])
                          {
                             oke=false;
                             break;
                          }
                          if (abs(tomb[poz]-tomb[i])==poz-i )
                          {
                          oke=false;
                          break;
                          }
                      }
                      if (oke==true) 
                      { 
                           res = bektrek_forw(tomb,poz+1); 
                      } 
                }
               
                if (res == OK)
                return OK;
                h[ert]=1;
          }
      }
 
    tomb[poz]=-1;
    return ERROR;
}

int bektrek_mvr(int *tomb, int poz)
{
   
    //  leallasi feltetel
    if ( poz == n)
    {
        kiirtomb(tomb);
        return OK;
    }
    //  sorra kiprobaljuk a lehetseges ertekeket
    for(int ert=1; ert<=n; ++ert)
    {
        tomb[poz]=(ert+poz+1)%n;
   
        // megnezuk, hogy konszitens-e
        int res=0;
        if (poz==0)
        {
                res = bektrek_mvr(tomb,poz+1);
        }
        else
        {
                bool oke=true;
                for (int i=0;i<poz;++i)
                {
                      if (tomb[i]==tomb[poz])
                      {
                             oke=false;
                             break;
                      }
                      if (abs(tomb[poz]-tomb[i])==poz-i )
                      {
                             oke=false;
                             break;
                      }
                }
                if (oke==true) 
                { 
                       res = bektrek_mvr(tomb,poz+1); 
                } 
        }
        
        if (res == OK)
                return OK;
    }
    
    tomb[poz]=-1;
    return ERROR;
}

int bektrek_keres(int *tomb, int poz)
{
  
    //  leallasi feltetel
    if ( poz == n)
    {
        kiirtomb(tomb);
        return OK;
    }
    // sorra kiprobaljuk a lehetseges ertekeket
    
    for(int ert=1; ert<=n; ++ert)
    {
        tomb[poz]=ert;
        //  megnezi, hogy konszitens-e
        int res=0;
        if (poz==0)
        {
                res= bektrek_keres(tomb,poz+1);
        }
        else
        {
                bool oke=true;
                for (int i=0;i<poz;++i)
                {
                if (tomb[i]==tomb[poz])
                {
                      oke=false;
                      break;
                }
                if (abs(tomb[poz]-tomb[i])==poz-i )
                {
                oke=false;
                break;
                }
        }
        if (oke==true) 
        { 
                res = bektrek_keres(tomb,poz+1); 
        } 
    }
    
    if (res == OK)
    return OK;
}

tomb[poz]=-1;
return ERROR;
}

void kiirtomb(int *tomb)
{ 
fs = clock();
printf("%lf  az eltelt ido ",(double)(fs-st)/CLOCKS_PER_SEC);
    for (int i=0;i<n;++i)
    {
        for (int j=0;j<n;++j)
        { 
                if (tomb[i] == j+1)
                file << "1";
                else
                file << "*";
        }
        file << endl;
    }
file << endl;
}
