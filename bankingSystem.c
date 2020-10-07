/* Simple banking management project in C */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

void newAccount();
void writeFile();
void viewAccount();
void output();
//void searchQuestion();
void searchNumber();
void searchName();
void deposit();
void withdraw();
void listAccounts();
void search();
void delete_customer();
void empty_db();
void transaction();

struct date
{
	int day;
	int month;
	int year;
};

struct accountInformation{
	char acc_num[20];
	char f_name[20];
	char l_name[20];
	char city[20];
	char street[20];
	char mobile_num[20];
	//char acc_type;
	float balance;
	struct date registerDate;
}customer;

int t1,s1,ts;

int main(void)
{
	while(1)
	{
		int mainLoop;
		char opt;
		system("clear");
		printf("\n\n\n\t\t\t----------------------------");
		printf	("\n\t\t\t BANK MANAGEMENT SYSTEM ");
		printf("\n\t\t\t----------------------------");
		printf("\n\t\t\t 1. New account.");
		printf("\n\t\t\t 2. Search account.");
		printf("\n\t\t\t 3. List accounts.");
		printf("\n\t\t\t 4. Transaction");
		printf("\n\t\t\t 5. Delete account.");
		printf("\n\t\t\t 6. Erase database.");
		printf("\n\t\t\t 0. EXIT");
		printf("\n\t\t\t----------------------------");
		printf("\n\t\t\t Enter your choice. ");
		scanf("%d", &mainLoop);
		switch(mainLoop)
		{
			case 1:
				newAccount();
				writeFile();
				break;
						
			case 2:
				search();
				break;
			case 3:
				listAccounts();
				break;				
			case 4:
				transaction();
				break;
			case 5:
				delete_customer();
				break;
			case 6:
				empty_db();
				break;

			case 0:
				system("clear");
				printf("\n\n\t\t\t-------------------------------");
				printf("\n\t\t\t| PROJECT BY NENAD KUZIC 2020 |");
				printf("\n\t\t\t| C FILES HANDLING I/O        |");
				printf("\n\t\t\t-------------------------------\n\n");
				exit(1);
			default:
				system("clear");
				printf("\n\t\t\t Enter valid option - 1/2/3/4/5/6/0");
				break;
		}
	}
}
void empty_db(void){
	system("clear");
	remove("bank_system.dat");
	FILE *erase;
	char ch;
	erase = fopen("bank_system.dat","wb");
	printf("\nDATABASE ERASED!\n");
	fclose(erase);
	exit:
	printf("Press ENTER to go back to menu...");
	ch=fgetc(stdin);
	if(getchar()==0x0A) // Use of enter
		main();
	else goto exit;
}

void newAccount(void)
{
	/* Create new file.dat for writing, and check if file exists, */
	FILE *fp;
        int fp_check;
	const char *file = "bank_system.dat";

	/* Checking if file exists */
	fp=fopen(file,"rb");
	if(fp==NULL) fp_check=0;
	else { fp_check=1; fclose(fp); }

	/* Open file  */
	if(fp_check==1) fp=fopen(file,"rb");
	else(fp=fopen(file,"wb"));
	
	/* Add new account */
	fseek(fp,0,SEEK_END);
	t1=ftell(fp);
	s1=sizeof(customer);
	ts=t1/s1;
	fseek(fp,(ts-1)*s1,SEEK_SET);
	fread(&customer,sizeof(customer),1,fp);
	system("clear");
	printf("\n\n\n----------------------------");
	printf("\n  Creating new account.");
	printf("\n----------------------------\n");
	fclose(fp);
	printf("Account number:		 \n");	scanf("%s", customer.acc_num);
	printf("First name:	 	 \n"); 	scanf("%s", customer.f_name);
	printf("Last name: 		 \n");	scanf("%s", customer.l_name);
	printf("City:			 \n");	scanf("%s", customer.city);
	printf("Street:			 \n");	scanf("%s", customer.street);
	printf("Mobile number: 		 \n");	scanf("%s", customer.mobile_num);
	printf("Balance:		 \n");	scanf("%f", &customer.balance);
	printf("Register date(dd/nn/yyy):\n");	scanf("%d/%d/%d", 
							&customer.registerDate.day,
							&customer.registerDate.month,
							&customer.registerDate.year);
	return;
}

void writeFile(void)
{
	FILE *fp;
	fp=fopen("bank_system.dat","ab");
	fwrite(&customer,sizeof(customer),1,fp);
	fclose(fp);
	return;
}

void listAccounts(void)
{
	char ch;
	int i=0;
	system("clear");
	printf("\n\n\n----------------------------");
	printf("\n\tAccounts list.");
	printf("\n----------------------------");
	FILE *view;
	view=fopen("bank_system.dat","rb");
	if(view==0) exit(0);
	while(fread(&customer,sizeof(customer),1,view)==1)
	{
		output();
		i++;
	}
	fclose(view);
	printf("Total %d accounts.\n", i);
	menu_option:
	printf("Press ENTER to go back to menu...");
	ch=fgetc(stdin);
	if(getchar()==0x0A) // Use of enter
		main();
	else goto menu_option;
}

void search(void)
{
	char ch;
	system("clear");
	printf("\n\n\n----------------------------");
	printf("\n\tSearch account.");
	printf("\n----------------------------");
	printf("\n 1) Account number");
	printf("\n 2) Customer name");
	printf("\n 3) Back to menu"); 
	printf("\n----------------------------");
	printf("\n Enter your choice. ");
	scanf("%s", &ch);
	if(ch=='1')searchNumber();
	else if(ch=='2')searchName();
	else if(ch=='3') main();
	else { printf("\nIncorrect entry!\n"); search(); }
}

void searchNumber(void)
{
	system("clear");
	char acc_num[20], ch;
	FILE *fp;
	bool b;
	fp = fopen("bank_system.dat","rb");		
	if(fp==0) exit(0);
	printf("\nEnter account number: ");
	scanf("%s", acc_num);
	while(fread(&customer,sizeof(customer),1,fp)==1)
	{
		if(strcmp(customer.acc_num,acc_num)==0)
		{
		      	output();
			fclose(fp);
	       		b = false;
		}
	}
	fclose(fp);
	if(b==true) printf("\nAccount number %s was not found.\n", acc_num);
		
	option_invalid:
	printf("Search again?(y/n)");
	scanf(" %c",&ch);	
	if(ch=='y') searchNumber();
	if(ch=='n') main();
	else { printf("Incorrect entry!\n"); goto option_invalid; }
}
	
void searchName(void)
{
	system("clear");
	char f_name[20], ch;
	FILE *fp;
	bool b;
      	fp = fopen("bank_system.dat","rb");		
	if(fp==0) exit(0);
	printf("\nEnter customer name: ");
	scanf("%s",f_name);
	while(fread(&customer,sizeof(customer),1,fp)==1)
	{
		if(strcmp(f_name,customer.f_name)==0) 
		{
		       	output();
			fclose(fp);
			b = false;				
		}   
	}
	fclose(fp);
	if(b==true) printf("\nCustomer %s was not found.\n", f_name);			
	
	option_invalid:
	printf("Search again? (y/n) ");
	scanf(" %c", &ch);
	if(ch=='y') searchName();
	else if(ch=='n') main();
	else { printf("Incorrect entry!\n"); goto option_invalid; }
}

void output(void)
{
	printf("\n\n 	Account number:		%s\n",customer.acc_num);
	printf("	First name:		%s\n",customer.f_name);
	printf("	Last name:		%s\n",customer.l_name);
	printf("	City:			%s\n",customer.city);
	printf("	Street:			%s\n",customer.street);
	printf("	Mobile number:		%s\n",customer.mobile_num);
	printf("	Balance:		%.2f\n",customer.balance);
	printf("	Register date:		%d/%d/%d\n\n",
						customer.registerDate.day,
						customer.registerDate.month,
						customer.registerDate.year);
	return;
}

void transaction(void)
{
	int opt;
	system("clear");
	printf("\n\n\n----------------------------");
	printf("\n\t\tTransaction menu");
	printf("\n----------------------------");
	printf("\n 1) Depostit");
	printf("\n 2) Withdraw");
	printf("\n 3) Back to menu"); 
	printf("\n----------------------------");
	printf("\n Enter your choice. ");
	scanf("%d", &opt);
	if(opt==1)deposit();
	else if(opt==2)withdraw();
	else if(opt==3) main();
	else { printf("\nIncorrect entry!\n"); transaction(); }
}

void deposit(void)
{
	system("clear");
	bool b;
	FILE *fp, *temp;
	char acc_num[20], ch;
	float money;		 // Amount of money to deposit
	temp=fopen("bank_temp.dat","wb");
	fp=fopen("bank_system.dat","rb");
	printf("Enter account number for transaction: ");
	scanf("%s",acc_num);
	while(fread(&customer,sizeof(customer),1,fp)==1)
	{

		if(strcmp(customer.acc_num,acc_num)==0)
		{ 
			printf("Curent balance: %.2f\n",customer.balance);
			printf("Amount to deposit: ");
			scanf("%f",&money);
			customer.balance=customer.balance+money;
			printf("\nTransaction completed.\n");
			printf("New balance: %.2f\n",customer.balance);
			b=false;
		}
		fwrite(&customer,sizeof(customer),1,temp);
	}
	
	fclose(fp);
	fclose(temp);
	remove("bank_system.dat");
	rename("bank_temp.dat","bank_system.dat");
	if(b==true) printf("\nAccount not found!\n");
		
	option_invalid:
	printf("New transaction?(y/n) ");
	scanf(" %c",&ch);
	if(ch=='y') deposit();
	else if(ch=='n') main();
	else { printf("Incorrect entry!\n"); goto option_invalid; }	
	
	return;
}

void withdraw(void)
{
	system("clear");
	bool b;
	FILE *fp, *temp;
	char acc_num[20], ch;
	float money;		// Amount of money to withdraw
	temp=fopen("bank_temp.dat","wb");
	fp=fopen("bank_system.dat","rb");
	printf("Enter account number for transaction: ");
	scanf("%s",acc_num);
	while(fread(&customer,sizeof(customer),1,fp)==1)
	{
		if(strcmp(customer.acc_num,acc_num)==0)
		{ 
			printf("Curent balance: %.2f\n",customer.balance);
			printf("Amount to withdraw: ");
			scanf("%f",&money);
			customer.balance=customer.balance-money;
			printf("\nTransaction completed.\n");
			printf("New balance: %.2f\n",customer.balance);
			b=false;
		}
		fwrite(&customer,sizeof(customer),1,temp);		
	}
	fclose(fp);
	fclose(temp);
	remove("bank_system.dat");
	rename("bank_temp.dat","bank_system.dat");
	if(b==true) printf("\nAccount not found!\n");
	
	option_invalid:
	printf("New transaction?(y/n) ");
	scanf(" %c",&ch);
	if(ch=='y') deposit();
	else if(ch=='n') main();
	else { printf("Incorrect entry!\n"); goto option_invalid; }

	return;
}

void delete_customer(void)
{
	system("clear");
	FILE *fp, *temp; 
	bool b;
	char acc_num[20];
	temp=fopen("bank_temp.dat","wb");
	fp=fopen("bank_system.dat","rb");	
	printf("Enter account number to delete: ");
       	scanf("%s",acc_num);	
	while(fread(&customer,sizeof(customer),1,fp)==1)
	{
		if(strcmp(customer.acc_num,acc_num)==0){ b = false; continue; }
		else fwrite(&customer,sizeof(customer),1,temp);
	}
	if(b==true){ printf("Account number %s not found",acc_num); return; }
	fclose(fp);
	fclose(temp);
	remove("bank_system.dat");
	rename("bank_temp.dat","bank_system.dat");
	printf("Record is deleted.");
	return;	
}





