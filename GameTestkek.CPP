#include<iostream.h>
#include<dos.h>
#include<iomanip.h>
#include<conio.h>
#include<graphics.h>
#include<fstream.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<process.h>
fstream fin,fout;
class game
{
char gn[20],gen[20],age[20];
int gc,r;
public:
void fdelete();
float co;
int ram,gr;
char pro[10],sz[10],os[10];
void input()
{
clrscr();
cout<<"\nEnter Serial No: ";
cin>>gc;
cout<<"\nEnter Game Name: ";
gets(gn);
cout<<"\nEnter Genre: ";
gets(gen);
cout<<"\nEnter Minimum Age Requirement: ";
gets(age);
cout<<"\nEnter RAM(in Gigabytes): ";
cin>>ram;
cout<<"\nEnter Processor(No of cores): ";
gets(pro);
cout<<"\nEnter OS: ";
gets(os);
cout<<"\nEnter Graphics Req(Size of GDDR5 RAM): ";
cin>>gr;
cout<<"\nEnter Usage Space(In Gigabytes): ";
gets(sz);
cout<<"\nEnter The Cost Of Game(INR): ";
cin>>co;
cout<<"\nEnter Rating out of 5: ";
cin>>r;
}
void output();
void mod(int a,char b[],char c[],int d,char e[]);
char* getn()
{
return gn;
}
}G;
void game::output()
{
cout<<endl<<gc;
cout<<". ";
cout<<gn<<endl;
int p=0;
p=strlen(gn);
for(int i=0;i<p+3;i++)
cout<<"-";
cout<<endl<<"Genre:"<<gen;
cout<<"\nCost:"<<co;
cout<<"\n\nSpecifications\n--------------"<<endl<<"RAM Required:"<<ram<<" GB"<<endl<<"No Of Cores(CPU):"<<pro<<" Cores"<<endl<<"Operating System:"<<os<<" and above"<<endl<<"Size of GPU:"<<gr<<" GB"<<endl<<"HDD Usage:"<<sz<<" GB"<<endl<<"Rating:";
if(r==1)
cout<<"*";
if(r==2)
cout<<"* *";
if(r==3)
cout<<"* * *";
if(r==4)
cout<<"* * * *";
if(r==5)
cout<<"* * * * *";
}
void fcreate()
{
clrscr();
fout.open("game.dat",ios::binary|ios::out|ios::app);
char ch='y';
do
{
G.input();
fout.write((char*)&G,sizeof(G));
cout<<"\nDo you wish to add more records(y/n):";
ch=getch();
}while((ch=='y')||(ch=='Y'));
fout.close();
}
void fdisp()
{
char p='y';
clrscr();
fin.open("game.dat",ios::binary|ios::in|ios::app);
fin.seekg(0);
do
{
fin.read((char*)&G,sizeof(G));
if(fin.eof())
{
cout<<"\nEnd Of File";
break;
}
clrscr();
G.output();
cout<<"\n Do you want to view more(y/n)?";
p=getch();
}while((!fin.eof())&&((p=='Y')||(p=='y')));
fin.close();
getch();
}
void fsearch()
{
clrscr();
fin.open("game.dat",ios::binary|ios::in|ios::beg|ios::app);
char ch[20];
int f=0;
cout<<"\nEnter Game to be searched:";
gets(ch);
while(!fin.eof())
{
fin.read((char*)&G,sizeof(G));
if(fin.eof())
break;
if(!strcmpi(G.getn(),ch))
{
G.output();
f=1;
break;
}
}
if(f==0)
cout<<"\nRecord not found!";
fin.close();
}
void fmodify()
{
clrscr();
fin.open("game.dat",ios::binary|ios::in|ios::out);
char ch[20],b[10],c[10],e[10];
int f=0,a,d,p;
cout<<"\nEnter name of game to be modified:";
gets(ch);
fin.seekg(0);
while(!fin.eof())
{
p=fin.tellg();
fin.read((char*)&G,sizeof(G));
if(fin.eof())
break;
if(!strcmpi(G.getn(),ch))
{
f++;
G.output();
cout<<"\nEnter new value for RAM , To keep existing value press '-1': ";
cin>>a;
cout<<"\nEnter new value for CPU , To keep existing value press '.': ";
gets(b);
cout<<"\nEnter new value for OS  , To keep existing value press '.': ";
gets(c);
cout<<"\nEnter new value for GPU , To keep existing value press '-1': ";
cin>>d;
cout<<"\nEnter new value for HDD requirement , To keep existing value press '.': ";
gets(e);
G.mod(a,b,c,d,e);
fin.seekp(p);
fin.write((char*)&G,sizeof(G));
break;
}
}
fin.close();
if(f==0)
cout<<"\nRecord not found!";
getch();
}
void game::mod(int a,char b[],char c[],int d,char e[])
{
if(a!=-1)
G.ram=a;
if(strcmp(b,"."))
strcpy(G.pro,b);
if(strcmp(c,"."))
strcpy(G.os,c);
if(d!=-1)
G.gr=d;
if(strcmpi(e,"."))
strcpy(G.sz,e);
}
void game::fdelete()
{
clrscr();
fin.open("game.dat",ios::binary|ios::in|ios::app);
fout.open("temp.dat",ios::binary|ios::out|ios::app);
int f=0;
char ch[20];
cout<<"\nEnter the game to be deleted:";
gets(ch);
fin.seekg(0);
while(!fin.eof())
{
fin.read((char*)&G,sizeof(G));
if(fin.eof())
break;
if(!strcmpi(G.getn(),ch))
{
f=1;
cout<<"\nRecord to be deleted: ";
G.output();
}
else
fout.write((char*)&G,sizeof(G));
}
fin.close();
fout.close();
if(f==0)
{
cout<<endl<<"Record not found!";
getch();
}
else
{
cout<<"\nRecord deleted";
getch();
}
remove("game.dat");
rename("temp.dat","game.dat");
}
void com()
{
clrscr();
char ch[20];
int ram,gr;
fin.open("game.dat",ios::binary|ios::in);
cout<<"\n Enter the game to be checked for compatibility:";
gets(ch);
cout<<"\nEnter your RAM size(GB): ";
cin>>ram;
cout<<"\nEnter your GPU size(GB): ";
cin>>gr;
while(!fin.eof())
{
fin.read((char*)&G,sizeof(G));
if(fin.eof())
{
cout<<"Record not found!";
getch();
break;
}
if(!strcmpi(G.getn(),ch))
{
if(ram>=G.ram&&gr>=G.gr)
cout<<"\nYour computer is compatible for the game.";
else
cout<<"\nYour computer is incompatible for the game.";
}
}
fin.close();
}
void logo()
{
int gdriver=DETECT,gmode;
initgraph(&gdriver,&gmode,"C:/TURBOC3/BGI");
rectangle(250,30,387,48);
rectangle(275,143,398,160);
rectangle(275,175,398,192);
}
void exit()
{
clrscr();
int driver,mode;
driver=DETECT;
initgraph(&driver,&mode,"C:/TURBOC3/BGI");
settextstyle(0,0,3);
outtextxy(215,150,"EXITING...");
for(int r=0;r<638;r++)
{
setlinestyle(3,1,5);
setcolor(LIGHTRED);
line(0,400,r,400);
line(0,403,r,403);
line(0,406,r,406);
line(0,409,r,409);
delay(5);
}
exit(0);
}
void main()
{
clrscr();
int driver,mode;
driver=DETECT;
initgraph(&driver,&mode,"C:/TURBOC3/BGI");
char u[20],p[20];
logo();
gotoxy(34,3);
cout<<"Gamelist Login";
gotoxy(25,10);
cout<<"Username:";
gotoxy(25,12);
cout<<"Password:";
gotoxy(36,10);
cout<<"G";
delay(150);
cout<<"R";
delay(150);
cout<<"O";
delay(150);
cout<<"U";
delay(150);
cout<<"P";
delay(150);
cout<<"1";
delay(150);
cout<<"G";
delay(150);
cout<<"M";
delay(150);
cout<<"L";
delay(150);
cout<<"S";
delay(150);
cout<<"T";
delay(900);
gotoxy(36,12);
for(int a=0;a<14;a++)
{
cout<<"*";
delay(150);
}
delay(450);
gotoxy(36,15);
cout<<"LOGIN SUCCESS!!!";
delay(1500);
cleardevice();
settextstyle(0,0,3);
outtextxy(45,150,"Please wait, Redirecting");
for(int r=0;r<638;r++)
{
setlinestyle(1,1,3);
setcolor(YELLOW);
line(0,400,r,400);
line(0,403,r,403);
line(0,406,r,406);
line(0,409,r,409);
delay(5);
}
cleardevice();
closegraph();
initgraph(&driver,&mode,"C:/TC/BGI");
setbkcolor(15);
setcolor(GREEN);
settextstyle(0,0,8);
outtextxy(155,100,"Coded");
outtextxy(250,250,"by");
delay(4500);
closegraph();
initgraph(&driver,&mode,"C:/TC/BGI");
setbkcolor(0);
setcolor(LIGHTRED);
settextstyle(1,0,5);
delay(1200);
outtextxy(150,60,"Abhijith Ashokan");
delay(1200);
setcolor(WHITE);
outtextxy(220,160,"Abit V Abi");
delay(1200);
setcolor(GREEN);
outtextxy(225,260,"Akhil P V");
delay(1200);
setcolor(BLUE);
outtextxy(160,360,"Kevin Kuruvilla");
delay(3000);
textbackground(0);
gotoxy(20,5);
cleardevice();
setbkcolor(WHITE);
setcolor(BLUE);
settextstyle(0,0,4);
outtextxy(215,150,"LOADING");
for(int k=0;k<638;k++)
{
setlinestyle(3,1,3);
setcolor(GREEN);
line(0,400,k,400);
line(0,403,k,403);
line(0,406,k,406);
line(0,409,k,409);
delay(8);
}
closegraph();
initgraph(&driver,&mode,"C:/TC/BGI");
setbkcolor(4);
settextstyle(0,0,9);
outtextxy(120,150,"GAME");
outtextxy(270,300,"LIST");
delay(4500);
closegraph();
textbackground(1);
textcolor(12);
char ch='y',x;
do
{
clrscr();
cout<<"\n\n\t\t\t   Welcome to The Game List";
cout<<"\n\t\t\t   ------------------------";
cout<<"\n\n\t\t\t  1. Add Records  ";
cout<<"\n\n\t\t\t  2. Display Records";
cout<<"\n\n\t\t\t  3. Search Records";
cout<<"\n\n\t\t\t  4. Modify Records";
cout<<"\n\n\t\t\t  5. Delete Records";
cout<<"\n\n\t\t\t  6. Check Compatibility";
cout<<"\n\n\t\t\t  7. Exit";
cout<<"\n\n\n\t\t     Press any key to continue!";
x=getch();
switch(x)
{
case '1':fcreate();
break;
case '2':fdisp();
break;
case '3':fsearch();
break;
case '4':fmodify();
break;
case '5':G.fdelete();
break;
case '6':com();
break;
case '7':exit();
}
if(x!='7')
{
cout<<"\nDo you wish to go back to Menu?(y/n):";
ch=getch();
if((ch=='n')||(ch=='N'))
exit();
}
}while((ch=='y')||(ch=='Y'));
}





