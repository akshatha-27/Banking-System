/* Project by Akshatha */
#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<dos.h>
#include<ctype.h>
#include<graphics.h>
struct account
{
  int acno;
  char n[30], p[30], type[3];
  struct date od;
  float bal;
};
  struct trans
 {
   int tacno;
   struct date td;
   char tt;
   char desc[30];
   float tamt;
 };
  void main()
{
  int gd,gm,ch,colr=1,colm=150,row=180;
  gd=DETECT;
  do
  {
  initgraph(&gd,&gm,"..\\bgi");
  while(!kbhit())
  {
    setcolor(12);
    line(100,50,500,50); //up
    line(100,430,500,430); //down
    line(100,50,20,150); //side up L
    line(20,330,100,430); //side down L
    line(20,150,20,330); //left middle
    line(500,50,580,150); //side up R
    line(580,330,500,430); //side down R
    line(580,150,580,330); //right middle
      /* outer line */
    setcolor(10);
    line(95,30,505,30); //up
    line(95,450,505,450); //down
    line(95,30,0,150);  //side up L
    line(0,330,95,450); //side down L
    line(0,150,0,330); //left middle
    line(505,30,600,150); //side up R
    line(600,330,505,450); //side down R
    line(600,150,600,330); //right middle
    setcolor(colr);
    circle(colm,40,9);
    circle(colm,440,9);
    circle(10,row,9);
    circle(590,row,9);
    setfillstyle(SOLID_FILL,colr);
    floodfill(colm,40,colr);
    floodfill(colm,440,colr);
    floodfill(10,row,colr);
    floodfill(590,row,colr);
    delay(5);
    colr++;
    if(colr>15)
    colr=1;
    colm+=30;
    if(colm>=480)
    colm=150;
    row+=30;
    if(row>=330)
    row=180;
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,4);
    setcolor(3);
    outtextxy(200,50,"Namma Bank");
    settextstyle(TRIPLEX_FONT,HORIZ_DIR,1);
    setcolor(14);
    outtextxy(150,120,"1.Opening an Account");
    outtextxy(150,150,"2.Deposit or Withdrawal");
    outtextxy(150,180,"3.Query");
    outtextxy(150,210,"4.Edit");
    outtextxy(150,240,"5.Transaction Report");
    outtextxy(150,270,"6.Customer Balance Report");
    outtextxy(150,300,"7.Exit");
    setcolor(5);
    outtextxy(150,345,"Your Choice : ");
  }
    gotoxy(36,23);
    scanf("%d",&ch);
    closegraph();
     switch(ch)
     {
       case 1:
	{
	 struct account a;
	 FILE *fp;
	 char w;
	 fp=fopen("accounts.dat","ab");
	 do
	 {
	   clrscr();
	   gotoxy(30,3); printf("Namma Bank Ltd");
	   gotoxy(30,4); printf("--------------");
	   gotoxy(20,5); printf("Account number       : ");
	   scanf("%d",&a.acno); fflush(stdin);
	   gotoxy(20,7); printf("Customer name        : ");
	   gets(a.n); fflush(stdin);
	   gotoxy(20,9); printf("Customer place       : ");
	   gets(a.p); fflush(stdin);
	   strcpy(a.type,"SB");
	   getdate(&a.od);
	   a.bal=0;
	   gotoxy(20,11);
	   printf("Account type         : %s",a.type);
	   gotoxy(20,13);
	   printf("Account opening date : %02d-%02d-%4d",a.od.da_day, a.od.da_mon, a.od.da_year);
	   gotoxy(20,15);
	   printf("Account balance    Rs.%.2f",a.bal);
	   fwrite(&a,sizeof(a),1,fp);
	   gotoxy(25,24);
	   printf("Any more y/n ? ");
	   scanf("%c",&w);
	 }while(w=='y' || w=='Y');
	  fclose(fp);
	}
	 break;
       case 2:
       {
	struct account a;
	struct trans t;
	FILE *fp1,*fp2;
	int x,flag,rs=sizeof(a),pos;
	char w;
	do
	{
	  clrscr();
	  gotoxy(20,5); printf("Enter account number   : ");
	  scanf("%d",&x); fflush(stdin);
	  flag=0;
	  fp1=fopen("accounts.dat", "rb+");
	  fread(&a,sizeof(a),1,fp1);
	  while(!feof(fp1))
	  {
	  if(x==a.acno)
	  {
	   gotoxy(20,6); printf("Account number         : %d",a.acno);
	   gotoxy(20,7); printf("Customer name          : %s",a.n);
	   gotoxy(20,8); printf("Customer place         : %s",a.p);
	   gotoxy(20,9); printf("Account type           : %s", a.type);
	   gotoxy(20,10); printf("Account opening date   : %02d-%02d-%4d",a.od.da_day, a.od.da_mon, a.od.da_year);
	   gotoxy(20,11); printf("Account balance        : %.2f",a.bal);
	   flag=1;
	   /*Entering Transaction*/
	   t.tacno=x;
	   getdate(&t.td);
	   gotoxy(20,13); printf("Transaction a/c number : %d",t.tacno);
	   gotoxy(20,14); printf("Transaction date       : %02d-%02d-%4d",t.td.da_day, t.td.da_mon, t.td.da_year);
	   one:
	   gotoxy(20,15); printf("Transaction type D/W   :  ");
	   scanf("%c",&t.tt); fflush(stdin);
	   t.tt=toupper(t.tt); fflush(stdin);
	   if(t.tt!= 'D' && t.tt != 'W')
	   {
	     gotoxy(20,22); printf("Error.. Type D or W only");
	     gotoxy(20,15); clreol();
	     goto one;
	   }
	   else
	   {
	     gotoxy(20,22); clreol();
	   }
	   two:
	   gotoxy(20,16); printf("Description            :  ");
	   gets(t.desc);
	   three:
	   gotoxy(20,17); printf("Transaction amount     :  ");
	   scanf("%f",&t.tamt); fflush(stdin);
	   if(t.tamt < 0)
	   {
	    gotoxy(20,22); printf("Error type 0 or more");
	    gotoxy(20,17); clreol();
	    goto three;
	   }
	   else if(t.tamt > a.bal && t.tt=='W')
	   {
	    gotoxy(20,22); printf("Error..Insufficient balance");
	    gotoxy(20,17); clreol();
	    goto three;
	   }
	   else
	   {
	    gotoxy(20,22); clreol();
	   }
	    fp2=fopen("trans.dat","ab");
	    fwrite(&t,sizeof(t),1,fp2);
	    fclose(fp2);
	    /* Account Updation */
	    pos=ftell(fp1);
	    fseek(fp1,pos-rs,SEEK_SET);
	    if(t.tt=='D')
	    a.bal+=t.tamt;
	    else
	    a.bal-=t.tamt;
	    fwrite(&a,sizeof(a),1,fp1);
	    break;
	  }
	   fread(&a,sizeof(a),1,fp1);
	 }
	  if(flag==0)
	  {
	    gotoxy(20,22); printf("Given account not in our bank");
	  }
	    fcloseall();
	    gotoxy(20,24); printf("Any more y/n ? ");
	    scanf("%c",&w);
	}while(w=='y' || w=='Y');
       }
	break;
       case 3:
       {
	struct account a;
	FILE *fp;
	char w;
	int flag,x;
	do
	{
	  clrscr();
	  gotoxy(20,5);
	  printf("Enter account number : ");
	  scanf("%d",&x); fflush(stdin);
	  flag=0;
	  fp=fopen("accounts.dat","rb");
	  fread(&a,sizeof(a),1,fp);
	  while(!feof(fp))
	  {
	   if(x==a.acno)
	   {
	    gotoxy(20,7); printf("Account Number       : %d",a.acno);
	    gotoxy(20,8); printf("Customer Name        : %s",a.n);
	    gotoxy(20,9); printf("Customer Place       : %s",a.p);
	    gotoxy(20,10); printf("Account Type         : %s",a.type);
	    gotoxy(20,11); printf("A/c Opening Date     : %02d-%02d-%4d",a.od.da_day,a.od.da_mon,a.od.da_year);
	    gotoxy(20,12); printf("Account Balance      : %.2f",a.bal);
	    flag=1;
	    break;
	   }
	    fread(&a,sizeof(a),1,fp);
	  }
	  if(!flag)
	  {
	   gotoxy(20,22); printf("Error...This A/c is not in our bank");
	  }
	   fclose(fp);
	   gotoxy(20,24); printf("Any more y/n ? ");
	   scanf("%c",&w);
	}while(w=='y' || w=='Y');
       }
	break;
       case 4:
	{
	 struct account a;
	 FILE *fp;
	 long int pos;
	 int x,flag,ch;
	 char w;
	 do
	 {
	   clrscr();
	   gotoxy(20,3); printf("Enter account number to edit : ");
	   scanf("%d",&x); fflush(stdin);
	   flag=0;
	   fp=fopen("accounts.dat","rb+");
	   fread(&a,sizeof(a),1,fp);
	   while(!feof(fp))
	   {
	    if(x==a.acno)
	    {
	     gotoxy(20,5); printf("Account Number      : %d",a.acno);
	     gotoxy(20,6); printf("Customer Name       : %s",a.n);
	     gotoxy(20,7); printf("Customer Place      : %s",a.p);
	     gotoxy(20,8); printf("Account Type        : %s",a.type);
	     gotoxy(20,9); printf("A/c Opening Date    : %02d-%02d-%4d",a.od.da_day,a.od.da_mon,a.od.da_year);
	     gotoxy(20,10); printf("Account Balance     : %.2f",a.bal);
	     flag=1;
	     pos=ftell(fp);
	     fseek(fp,pos-sizeof(a),SEEK_SET);
	     gotoxy(20,12); printf("1.Name    2.Place    3.Both  : ");
	     scanf("%d",&ch);  fflush(stdin);
	     switch(ch)
	     {
	      case 1:
	       gotoxy(20,14); printf("Enter new name : ");
	       gets(a.n);
	       break;
	      case 2:
	       gotoxy(20,14); printf("Enter new place : ");
	       gets(a.p);
	       break;
	      case 3:
	       gotoxy(20,14); printf("Enter a new name : ");
	       gets(a.n);
	       gotoxy(20,15); printf("Enter a new place : ");
	       gets(a.p);
	       break;
	     }
	      fwrite(&a,sizeof(a),1,fp);
	      break;
	    }
	     fread(&a,sizeof(a),1,fp);
	   }
	    if(!flag)
	    {
	      gotoxy(20,22);
	      printf("Account not found");
	    }
	     fclose(fp);
	     gotoxy(20,22); printf("Any more y/n ? ");
	     scanf("%c",&w);
	 }while(w=='y' || w=='Y');
	}
	 break ;
       case 5:
	{
	 struct account a;
	 struct trans t;
	 FILE *fp1,*fp2;
	 int x,flag;
	 char w;
	 do
	 {
	   clrscr();
	   gotoxy(20,3); printf("Enter account number : ");
	   scanf("%d",&x); fflush(stdin);
	   flag=0;
	   fp1=fopen("trans.dat","rb");
	   fp2=fopen("accounts.dat","rb");
	   fread(&t,sizeof(t),1,fp1);
	   fread(&a,sizeof(a),1,fp2);
	   printf("\n-------------------------------------------------------------------------------");
	   printf("\nTransaction   Transaction   Description    Withdrawals    Deposits      Balance");
	   printf("\n   Date          Type");
	   printf("\n-------------------------------------------------------------------------------");
	   a.bal=0;
	   while(!feof(fp1))
	   {
	     if(x==t.tacno)
	     {
	       printf("\n%02d-%02d-%4d       %c        %9s",t.td.da_day,t.td.da_mon,t.td.da_year,t.tt,t.desc);
	       if(t.tt=='D')
	       {
		 printf("%31.2f",t.tamt);
		 printf("%13.2f",a.bal+=t.tamt);
	       }
	       else
	       {
		 printf("%17.2f",t.tamt);
		 printf("%27.2f",a.bal-=t.tamt);
	       }
		 flag=1;
	     }
		fread(&t,sizeof(t),1,fp1);
	   }
	    if(!flag)
	    {
	      gotoxy(20,22);
	      printf("Account not found");
	    }
	    fclose(fp1);
	    gotoxy(20,25); printf("Any more y/n? ");
	    scanf("%c",&w);
	 }while(w=='y' || w=='Y');
	}
	break;
       case 6:
	{
	 struct account a;
	 FILE *fp;
	 int c=0;
	 float t=0;
	 clrscr();
	 printf("\t\t\t\tNamma Bank Ltd");
	 printf("\n\t\t\t\t--------------");
	 printf("\nAccount	  Customer	Customer	Account	       Opening	      Account ");
	 printf("\nNumber 	   Name		Place		Type           Date           Balance ");
	 printf("\n--------------------------------------------------------------------------------");
	 fp=fopen("accounts.dat","rb");
	 fread(&a,sizeof(a),1,fp);
	 while(!feof(fp))
	 {
	   c++;
	   t+=a.bal;
	   printf("\n%3d      %-15s %-15s  %-5s       %02d-%02d-%4d    %10.2f",a.acno,a.n,a.p,a.type,a.od.da_day,a.od.da_mon,a.od.da_year,a.bal);
	   fread(&a,sizeof(a),1,fp);
	 }
	  printf("\n--------------------------------------------------------------------------------");
	  printf("\nTotal number of accounts : %d",c);
	  printf("\nTotal account balance    : %.2f",t);
	  getch();
	}
	break;
     }
  }while(ch!=7);
}
