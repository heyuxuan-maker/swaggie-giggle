#include <stdlib.h>  
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <windows.h>
#define TRUE 1
#define FALSE 0
#define MAXIMUS 16
int Cx,Cy;
void runpcgame();
void runmangame();
struct players_list
{	
	char name[11];
	int score;
}players[100],temp;
struct position 
{
	int x;
	int y;
	int score;
};
struct position positions[50];
int position_order;
int count;
char chess_board[16][16],cp;
void startgame()
{
	int i;
	printf("\t\t****************************\n");
	printf("\t\t*       ������             *\n");
	printf("\t\t* ģʽ1:�˻�ģʽ           *\n");
	printf("\t\t* ģʽ2:����ģʽ           *\n");
	printf("\t\t* ģʽ0:�˳���Ϸ           *\n");
	printf("\t\t****************************\n");
	printf("\t\t*ʹ�÷��������������ƶ�����*\n");
	printf("\t\t*ʹ�ÿո�������            *\n");
	printf("\t\t*��Ϸ�пɰ���ESC�˳���Ϸ   *\n");
	printf("\t\t****************************\n");
	printf("������ѡ�");
	while(1)
	{
		scanf("%d",&i);
		getchar();
		if(i==1)
			runpcgame();
		else if(i==2)
			runmangame();
		else if(i==0)
			exit(0);
		else
		{
			printf("�������ܼ�������,������ѡ��ģʽ:");
			continue;
		}
	}
}
void scorelist(int scores,char cp)//�������а� 
{
	system("cls");
	int score[100],j=0;
	static int ii=0;
	char ch;
	if(cp=='*')
		printf("�ڷ�ʤ������������������(����quit��������)��\n");
	else
		printf("�׷�ʤ������������������(����quit��������)��\n"); 
	scanf("%s",players[ii].name);
	getchar();
	if(strcmp(players[ii].name,"quit")==0)
		exit(0);
	else
	{	players[ii].score=scores;
		printf("  \t\t�������а�\n");
		printf("����\t\t�ǳ�\t\t����\n");
		for(j=0;j<=ii;j++)
		{
			int k;
			for(k=j+1;k<=ii;k++)
			{
				if(players[j].score<players[k].score)
				{
					temp=players[j];
					players[j]=players[k];
					players[k]=temp;
				}
			}
		}
	}
	for(j=0;j<=ii;j++)
	{
		printf("%d\t\t%s",j+1,players[j].name);
		switch(strlen(players[j].name))
		{
			case 1:{printf("%17d\n",players[j].score);break;}
			case 2:{printf("%16d\n",players[j].score);break;}
			case 3:{printf("%15d\n",players[j].score);break;}
			case 4:{printf("%14d\n",players[j].score);break;}
			case 5:{printf("%13d\n",players[j].score);break;}
			case 6:{printf("%12d\n",players[j].score);break;}
			case 7:{printf("%11d\n",players[j].score);break;}
			case 8:{printf("%10d\n",players[j].score);break;}
			case 9:{printf("%9d\n",players[j].score);break;}
			case 10:{printf("%8d\n",players[j].score);break;}
			default:break;
		}
	}
	ii++;
	count=0;
	printf("\n");
	while(1)
	{
		printf("�Ƿ�����������Ϸ��Y/N\n");
		scanf("%c",&ch);
		getchar();
		if(ch=='N')
			exit(0);
		else if(ch=='Y')
			startgame();
		else
			continue;
	}
}
void initialize_board(void)//��ʼ������ 
{
	count=0;
	int i, j;
	for (i = 0;i<16;i++) 
		for (j = 0;j<16;j++)
			chess_board[i][j]= ' ';
	Cx=17;
	Cy=16;
	cp='*';
}
void initial_positions(void)//��ʼ�����̵÷� 
{
	positions[0].x = positions[0].y = positions[0].score = 0;
	for (position_order = 1;position_order < 50;position_order++) 
		positions[position_order] = positions[0];
	position_order = 0;
}
void print_board()//ÿ����������ӡ������ 
{
	int i, j;
	for (i = 0;i < 33;i++) 
	{ 
		for (j = 0;j < 33;j++) 
		{
			if (i == 0 && j == 0) /*The first row*/
				printf("��  ");
			else if (i == 0 && j==32) 
				printf("��");
			else if (i == 0 && j % 2 == 0) 
				printf("��  ");
			if (i == 32 && j == 0)/*The last row*/
				printf("��  ");
			else if (i == 32 && j == 32)
				printf("��");
			else if (i == 32 && j % 2 == 0)
				printf("��  ");
			if (i != 0 && i != 32) /*The other rows*/
			{
				if (i % 2 == 0) 
				{
					if (j == 0) 
						printf("��  ");
					else if (j == 32) 
						printf("��");
					else if (j % 2 == 0) 
						printf("��  ");
				}
				else if(j % 2 == 0)
				{
					if(i==Cx&&j==Cy)
						printf("  X");
					else 
						printf("  %c", chess_board[(i - 1) / 2][(j+1)/2]);
				}
			}
		}
		putchar('\n');
	}
	if(cp=='*')
		printf("���ڷ����ӣ�");
	else
		printf("���׷����ӣ�");
}
int is_full()//�ж������Ƿ����� 
{
	int i, j;
	for (i = 0;i < 16;i++)
		for (j = 0;j < 16;j++)
			if (chess_board[i][j] == ' ')
				return FALSE;
	return TRUE;
}
void is_win(int x, int y, char cp)//�˻��ж�ʤ�� 
{
	int i, num=0;
	char var;
	for (i = 0;chess_board[y][x + i]==cp;i++,num++);
	for (i = -1;chess_board[y][x + i]==cp;i--,num++);
	if (num >= 5) 
	{
		system("cls");
		print_board();
		printf("%c win!", cp);
		if(cp=='*')
			scorelist(count/2+1,cp);
		else
		{
			system("pause");
			system("cls"); 
			printf("���Ƿ��뿪ʼ�µ���Ϸ��Y/N\n");
			while(1)
			{
				var=getch();
				if(var=='Y')  startgame();
				else if(var=='N')  exit(0);
				else  continue;
			}
		}
	}
	else 
		num = 0; 
	for (i = 0;chess_board[y + i][x] == cp;i++, num++);
	for (i = -1;chess_board[y + i][x] == cp;i--, num++);
	if (num >= 5)
	{
		system("cls");
		print_board();
		printf("%c win!", cp);
		if(cp=='*')
			scorelist(count/2+1,cp);
		else
		{
			system("pause");
			system("cls"); 
			printf("���Ƿ��뿪ʼ�µ���Ϸ��Y/N\n");
			while(1)
			{
				var=getch();
				if(var=='Y')  startgame();
				else if(var=='N')  exit(0);
				else  continue;
			}
		}
	}
	else 
		num = 0;
	for (i = 0;chess_board[y + i][x + i] == cp;i++, num++);
	for (i = -1;chess_board[y + i][x + i] == cp;i--, num++);
	if (num >= 5) 
	{
		system("cls");
		print_board();
		printf("%c win!", cp);
		if(cp=='*')
			scorelist(count/2+1,cp);
		else
		{
			system("pause");
			system("cls"); 
			printf("���Ƿ��뿪ʼ�µ���Ϸ��Y/N\n");
			while(1)
			{
				var=getch();
				if(var=='Y')  startgame();
				else if(var=='N')  exit(0);
				else  continue;
			}
		}
	}
	else
		num = 0;
	for (i = 0;chess_board[y + i][x - i] == cp;i++, num++);
	for (i = -1;chess_board[y + i][x - i] == cp;i--, num++);
	if (num >= 5)
	{
		system("cls");
		print_board();
		printf("%c win!", cp);
		if(cp=='*')
			scorelist(count/2+1,cp);
		else
		{
			system("pause");
			system("cls"); 
			printf("���Ƿ��뿪ʼ�µ���Ϸ��Y/N\n");
			while(1)
			{
				var=getch();
				if(var=='Y')  startgame();
				else if(var=='N')  exit(0);
				else  continue;
			}
		}
	}
	else
		num = 0;
}
void is_winman(int a, int b, char cp)//�����ж�ʤ�� 
{
	int w=1,x=1,y=1,z=1,i;//�ۼƲ�ͬ������������ͬ������Ŀ
	for(i=1;i<5;i++)
	{	
		if(b+i<MAXIMUS&&chess_board[a][b+i]==cp)
			w++;
		else
			break;
	}//���¼���  
	for(i=1;i<5;i++)
	{	
		if(b-i>0&&chess_board[a][b-i]==cp)
			w++;
		else 
			break;
	}//���ϼ���  
	if(w>=5)
	{
		printf("%c��ʤ����",cp); 
		system("pause");
		system("cls");
		print_board();
		if(cp=='*')
			scorelist(256-(count+1)/2,cp);
		else
			scorelist(256-(count-1)/2,'O');
	}
	for(i=1;i<5;i++)
	{
		if(a+i<MAXIMUS&&chess_board[a+i][b]==cp)
			x++;
		else 
			break;
	}//���Ҽ���  
	for(i=1;i<5;i++)
	{
		if(a-i>0&&chess_board[a-i][b]==cp)
			x++;
		else 
			break;}//��������  
	if(x>=5)
	{
		printf("%c��ʤ����",cp); 
		system("pause");
		system("cls");
		print_board();
		if(cp=='*')
			scorelist(256-(count+1)/2,cp);
		else
			scorelist(256-(count-1)/2,'O');
	}
	for(i=1;i<5;i++)
	{	
		if(a+i<MAXIMUS&&b+i<MAXIMUS&&chess_board[a+i][b+i]==cp)
			y++;
		else 
			break;}//�����¼���  
	for(i=1;i<5;i++)
	{	
		if(a-i>0&&b-i>0&&chess_board[a-i][b-i]==cp)
			y++;
		else 
			break;}//�����ϼ���  
	if(y>=5)
	{
		printf("%c��ʤ����",cp); 
		system("pause");
		system("cls");
		print_board();
		if(cp=='*')
			scorelist(256-(count+1)/2,cp);
		else
			scorelist(256-(count-1)/2,'O');
	}
	for(i=1;i<5;i++)
	{	
		if(a+i<MAXIMUS&&b-i>0&&chess_board[a+i][b-i]==cp)
			z++;
		else
			break;}//�����ϼ���  
	for(i=1;i<5;i++)
	{	
		if(a-i>0&&b+i<MAXIMUS&&chess_board[a-i][b+i]==cp)
			z++;
		else 
			break;
	}//�����¼���  
	if(z>=5)
	{
		printf("%c��ʤ����",cp); 
		system("pause");
		system("cls");
		print_board();
		if(cp=='*')
			scorelist(256-(count+1)/2,cp);
		else
			scorelist(256-(count-1)/2,'O');
	}
}
void scan(void)//�˻��������� 
{
	int input;
	while(1)
	{
		input=getch();
		if(input==27)
			exit(0);
		else if(input==' ')
		{
			if (!(chess_board[(Cx-1)/2][Cy/2]==' '))
				continue;
			chess_board[(Cx-1)/2][Cy/2]='*';
			system("cls");
			print_board();
			count+=2;
			break;
		}
		else if(input==0xE0)//�������µ��Ƿ��������������������룬��һ��Ϊ0xE0��ʾ���µ��ǿ��Ƽ�  
		{   
			input=getch();//���õڶ���������Ϣ  
			switch(input)//�жϷ������������ƶ�����λ��  
			{   
				case 0x4B:Cy-=2;break; 
				case 0x48:Cx-=2;break; 
				case 0x4D:Cy+=2;break; 
				case 0x50:Cx+=2;break; 
			}
			if(Cx<1)
				Cx=31;//��������λ��Խ�����ƶ����Բ�  
			if(Cy<0)
				Cy=30;
			if(Cx>31) 
				Cx=1;  
			if(Cy>30)
				Cy=0;
			system("cls");
			print_board();
		}
		else
			continue;
	}
	is_win(Cy/2,(Cx-1)/2,'*');	
}
void reverse(char row[],int len)//����һ�����Ӿ��жԳ��ԣ���x=3,x=4��״̬�ɷ�ת����Ϊx=0,x=1��״̬
{
	char temp;
	int i,j;
	for (i = 0, j = len - 1;i <= j;i++, j--)
	{
		temp = row[i];
		row[i] = row[j];
		row[j] = temp;
	}
}
int score(char row[], int x)//'O'�������壬'*'�������壬��ִ�ڣ�����ִ��
{                                           //ÿ��if��֧����ע�ͣ�'_'�����ո񣨼������Ӵ�����'O'Ϊ���壬'*'Ϊ����
	if (x > 2) 
	{                        //'?'��ʾ�ѿɸ��֣���λ��״̬���ػ�ȡ
		reverse(row,5);
		x = 4 - x;                  //�����ŵ�return�����صı��ǶԸ�λ�õ�����
	}
	switch (x) 
	{
	case 0:
	{
		if (row[1]=='O'&&(row[2]=='O'||row[2]==' ') && (row[3] == 'O' || row[3] == ' ') && (row[4] == 'O' || row[4] == ' ')) 
		{
			if (row[x + 2]==' ')//_O_??
				return(15);
			else if (row[x + 3] == ' ') //_OO_?
				return(50);
			else if (row[x + 4] == ' ')//_OOO_
				return(90);
			else 	//_OOOO
				return(1000);
		}
		else if (row[1] == '*' && (row[2] == '*' || row[2] == ' ') && (row[3] == '*' || row[3] == ' ') && (row[4] == '*' || row[4] == ' ')) 
		{
			if (row[x + 2] == ' ')//_*_??
				return(5);
			else if (row[x + 3] == ' ') 	//_**_?
				return(30);
			else if (row[x + 4] == ' ') //_***_
				return(70);
			else //_****
				return(500);
		}
	};break;
	case 1:
	{
		if ((row[0] == 'O' || row[0] == ' ') && (row[2] == 'O' || row[2] == ' ') && (row[3] == 'O' || row[3] == ' ') && (row[4] == 'O' || row[4] == ' ')) 
		{
			if (row[0] == 'O')
			{
				if (row[2] == ' ')	//O_ _??
					return(15);
				else if (row[3] == ' ')//O_O_??
					return(50);
				else if (row[4] == ' ')	//O_OO_
					return(90);
				else //O_OOO
					return(1000);
			}
			else if (row[2] == ' ') //_ _ _??
				return(0);
			else if (row[3] == ' ')	//_ _O_?
				return(15);
			else if (row[4] == ' ')	//_ _OO_
				return(50);
			else //_ _OOO
				return(80);
		}
		else if ((row[0] == '*' || row[0] == ' ') && (row[2] == '*' || row[2] == ' ') && (row[3] == '*' || row[3] == ' ') && (row[4] == '*' || row[4] == ' ')) 
		{
			if (row[0] == '*') 
			{
				if (row[2] == ' ') 	//*_ _??
					return(5);
				else if (row[3] == ' ') //*_*_?
					return(30);
				else if (row[4] == ' ')//*_**_
					return(70);
				else //*_***
					return(500);
			}
			else if (row[2] == ' ') //_ _ _??
				return(0);
			else if (row[3] == ' ') //_ _*_?
				return(5);
			else if (row[4] == ' ')//_ _**_
				return(30);
			else//_ _***
				return(60);
		}
	};break;
	case 2: 
	{
		if ((row[0] == 'O' || row[0] == ' ') && (row[1] == 'O' || row[2] == ' ') && (row[3] == 'O' || row[3] == ' ') && (row[4] == 'O' || row[4] == ' ')) 
		{
			if (row[1] == 'O') 
			{
				if (row[3] == 'O') 
				{
					if (row[0] == 'O') 
					{
						if (row[4] == 'O') //OO_OO
							return(1000);
						else 
							return(90);		//OO_O_
					}
					else 
					{
						if (row[4] == 'O') //_O_OO
							return(90);
						else //_O_O_
							return(50);
					}
				}
				else 
				{
					if (row[0] == 'O')	//OO_ _?
						return(40);
					else //_O_ _?
						return(15);
				}
			}
			else 
			{
				if (row[3] == 'O') 
				{
					if(row[4] == 'O')//_ _ _OO
						return(40);
					else//_ _ _O_
						return(15);
				}
			}
		}
		else if ((row[0] == '*' || row[0] == ' ') && (row[1] == '*' || row[2] == ' ') && (row[3] == '*' || row[3] == ' ') && (row[4] == '*' || row[4] == ' ')) 
		{
			if (row[1] == '*') 
			{
				if (row[3] == '*') 
				{
					if (row[0] == '*')
					 {
						if (row[4] == '*') //**_**
							return(500);
						else//**_*_
							return(70);
					 }
					else 
					{
						if (row[4] == '*')//_*_**
							return(70);
						else//_*_*_
							return(30);
					}
				}
				else
				{
					if (row[0] == '*') //**_ _ _
						return(20);
					else //_*_ _?
						return(5);
				}
			}
			else 
			{
				if (row[3] == '*') 
				{		//_ _ _**
					if (row[4] == '*')
						return(20);
					else //_ _ _*_
						return(5);
				}
			}
		}
	};break;
	}
	return(0);
} 
int sense_row(int x, int y)//������ȡ,������һ��ʾ���У�x��y��������λ���ǵ�����O
{                                  //[OOOOO]OOOO,O[OOOOO]OOO��OO[OOOOO]OO......�����������ν�ȡ�����෽������

	int sum = 0, i, j;
	char row[5];
	for (i = x - 4;i <= x;i++) 
	{
		if (!(i >= 0 && i + 4 <= 15))
			continue;
		else 
		{
			for (j = 0;j < 5;j++) 
				row[j] = chess_board[y][i + j];
			sum += score(row, x - i);
		}
	}
	return(sum);
}
int sense_col(int x, int y)
{
	int sum = 0, i, j;
	char row[5];
	for (i = y - 4;i <= y;i++) 
	{
		if (!(i >= 0 && i + 4 <= 15)) 
			continue;
		else
		{
			for (j = 0;j < 5;j++) 
				row[j] = chess_board[i + j][x];
			sum += score(row, y - i);
		}
	}
	return(sum);
}
int sense_right_bias(int x, int y)
{
	int sum = 0, i, j;
	char row[5];
	for (i = -4;i <= 0;i++) 
	{
		if (!(y + i >= 0 && x + i >= 0 && y + i + 4 <= 15 && x + i + 4 <= 15)) 
			continue;
		else
		{
			for (j = 0;j < 5;j++) 
				row[j] = chess_board[y + i + j][x + i + j];
			sum += score(row, -i);
		}
	}
	return(sum);
}
int sense_left_bias(int x, int y)
{
	int sum = 0, i, j;
	char row[5];
	for (i = -4;i <= 0;i++)
	{
		if (!(y - i <= 15 && x + i >= 0 && y - i - 4 >= 0 && x + i + 4 <= 15)) 
			continue;
		else
		{
			for (j = 0;j < 5;j++) 
				row[j] = chess_board[y - i - j][x + i + j];
			sum += score(row, -i);
		}
	}
	return(sum);
}
void sense(void)//���ĸ������ϵ������ۺϲ���¼
{
	int x, y, sum = 0;
	initial_positions();
	for (y = 0;y < 16;y++)
		for (x = 0;x < 16;x++) 
		{
			if (chess_board[y][x] != ' ') 
				continue;
			sum += sense_col(x, y);
			sum += sense_row(x, y);
			sum += sense_left_bias(x, y);
			sum += sense_right_bias(x, y);
			if (sum != 0) 
			{
				positions[position_order].score = sum;
				positions[position_order].x = x;
				positions[position_order].y = y;
				position_order++;
				sum = 0;
			}
		}
}
void think_act(void)
{
	int max=0,max_order,i;
	for (i=0;i<position_order;i++) 
		if (positions[i].score>max) 
		{
			max=positions[i].score;
			max_order=i;
		}
	chess_board[positions[max_order].y][positions[max_order].x]='O';
	is_win(positions[max_order].x,positions[max_order].y,'O');
}
void runpcgame()//�˻�ģʽ 
{
	initialize_board();
	print_board();
	while (!is_full())
	{
		scan();
		sense();
		think_act();
		system("cls");
		print_board();
	}
}
int main(void)
{
	startgame();
	return 0;
}
void runmangame()//����ģʽ 
{ 
	int input;//��������
	initialize_board();//��ʼ���Ծ�
	while(1)
	{
		system("cls");
		print_board();
		input=getch();
		if(input==27)
			exit(0);
		else if(input==' ')
		{
			if (!(chess_board[(Cx-1)/2][Cy/2]==' '))
				continue;
			chess_board[(Cx-1)/2][Cy/2]=cp;
			if(cp=='*')
				cp='O';
			else if(cp=='O')
				cp='*';
			system("cls");
			print_board();
			count++;
		}
		else if(input==0xE0)//�������µ��Ƿ��������������������룬��һ��Ϊ0xE0��ʾ���µ��ǿ��Ƽ�  
		{   
			input=getch();//���õڶ���������Ϣ  
			switch(input)//�жϷ������������ƶ�����λ��  
			{   
				case 0x4B:Cy-=2;break; 
				case 0x48:Cx-=2;break; 
				case 0x4D:Cy+=2;break; 
				case 0x50:Cx+=2;break; 
			}
			if(Cx<1)
				Cx=31;//��������λ��Խ�����ƶ����Բ�  
			if(Cy<0)
				Cy=30;
			if(Cx>31) 
				Cx=1;  
			if(Cy>30)
				Cy=0;
			system("cls");
			print_board();
		}
		is_winman((Cx-1)/2,Cy/2,cp);
	}
}
