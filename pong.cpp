#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cmath>
#include<Windows.h>

using namespace std;


class test
{
	private:
			int getvy(int y)
			{
				int a=0, l=1, j=1;
				if(dir[0]<0)l=-1;
				for(int i=0;i<abs(dir[0]);i++)
				{
					if(y+a==1||y+a==31)
					{
						l=-l;
						j=-j;
					}
					a+=l;
				}
				dir[0]*=j;
				return a;
			}
			
			int getvx(int x, int y)//dir0|+/-|
			{
				int a=0, l=abs(dir[1])/dir[1];
				for(int i=0;i<abs(dir[1]);i++)
				{
					if(tab[y][x+a-1]==219||tab[y][x+a+1]==219)
					{
						dir[1]=-dir[1];
						l=-l;
					}
					a+=l;
					if(a+x==0||a+x==90)break;
				}
				return a;
			}
			
	
	public:
		int tab[33][91],dir[2]={-2, -3}, wynik[2]={};
		
		void init()
		{
			
			for(int i=0;i<33;i++)
			{
				for(int j=0;j<91;j++)tab[i][j]=0;
			}
			
			tab[16][45] = 254;
			for(int i=0;i<91;i++)
			{
				tab[0][i]=240;
				tab[32][i]=240;
			}
			for(int i=15;i<=17;i++)
			{
				tab[i][1]=219;
				tab[i][89]=219;
			}
		}
		
		bool move()
		{			
			for(int i=0;i<33;i++)
			{
				for(int j=0;j<91;j++)
				{
					if(tab[i][j]==254)
					{
						tab[i][j]=0;
						int y=i+getvy(i);
						int x=j+getvx(j, y);
						tab[y][x]=254;						
						if(x==0||x==90)//0, w tym wypadku, bedzie rowne 1
						{
							if(x==0)wynik[0]++;
							else wynik[1]++;
							dir[1]=-dir[1];
							if(!(rand()%10))dir[0]++;
							if(!(rand()%10))dir[0]--;
							if(rand()%10==0||rand()%10==1)dir[0]=-dir[0];
							if(!(rand()%10))dir[1]++;
							if(!(rand()%10))dir[1]--;
							return true;
						}
						return false;
					}
				}
			}
		}
		
		void move_en()
		{
			int pos=1, a, s=3;
			for(;pos<30;pos++)
			{
				if(tab[pos][89]==219) break;
			}
			if(GetKeyState(VK_UP) & 0x8000 && pos>1)
			{
				a=-1;
				for(int i=0;i<s;i++)
				{
					if(pos-i==1)
					{
						s=i;
						break;
					}
				}
			}
			else if(GetKeyState(VK_DOWN) & 0x8000 && pos+2<31)
			{
				a=1;
				pos+=2;
				for(int i=0;i<s;i++)
				{
					if(pos+i==31)
					{
						s=i;
						break;
					}
				}
			}
			else return;
			
			for(int i=pos;i!=pos-3*a;i+=-a)
			{
				tab[i+a*s][89]=219;
				tab[i][89]=0;
			}
		}
		
		
		void move_pl()
		{
			int pos=1, a, s=3;
			for(;pos<30;pos++)
			{
				if(tab[pos][1]==219) break;
			}
			if(GetKeyState('W') & 0x8000 && pos>1)
			{
				a=-1;
				for(int i=0;i<s;i++)
				{
					if(pos-i==1)
					{
						s=i;
						break;
					}
				}
			}
			else if(GetKeyState('S') & 0x8000 && pos+2<31)
			{
				a=1;
				pos+=2;
				for(int i=0;i<s;i++)
				{
					if(pos+i==31)
					{
						s=i;
						break;
					}
				}
			}
			else return;
			
			for(int i=pos;i!=pos-3*a;i+=-a)
			{
				tab[i+a*s][1]=219;
				tab[i][1]=0;
			}
		}
		
		void show()
		{
			system("cls");
			for(int i=0;i<33;i++)
			{
				for(int j=0;j<91;j++)
				{
					if(tab[i][j]==0) cout<<" ";
					else cout<<char(tab[i][j]);
				}
				cout<<endl;
			}
			cout<<"wynik -  "<<wynik[0]<<":"<<wynik[1];
		}
		
};


int main()
{

	test t;
	t.init();
	
	_sleep(3000);
	
	while(1)
	{
		t.show();
		_sleep(300);
		t.move_pl();
		t.move_en();
		if(t.move()) t.init();

	}
	
	return 0;
}
