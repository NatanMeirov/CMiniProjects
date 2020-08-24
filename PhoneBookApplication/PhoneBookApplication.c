#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include "PhoneBookApplication.h"

void main()
{
	system("color 5f");
	start();
	return 0;
}

void back()
{
	start();
}

void start()
{
	menu();
}

void menu()
{
	system("cls");
	printf("\t\t**********WELCOME TO PHONEBOOK*************");
	printf("\n\n\t\t\t  MENU\t\t\n\n");
	printf("\t1.Add New   \t2.List   \t3.Exit  \n\t4.Modify \t5.Search\t6.Delete");

	switch (getch())
	{
	case '1':
		add_record();
		break;
	case '2':
		list_record();
		break;
	case '3':
		exit(0);
	case '4':
		modify_record();
		break;
	case '5':
		search_record();
		break;
	case '6':
		delete_record();
		break;
	default:
		system("cls");
		printf("\nEnter 1 to 6 only");
		printf("\nEnter any key...");
		getch();
		menu();
	}
}

void display_person_info(Person person)
{
	printf("\nFull Name: %s \nID: %s \nAddress: %s \nFather Name: %s \nMother Name: %s \nPhone Number: %s \nGender: %s \nE-mail: %s ", person.full_name, person.id, person.address, person.father_name, person.mother_name, person.phone_number, person.gender, person.email);
}

void ending_process()
{
	printf("\n\nEnter any key...");
	getch();
	system("cls");
	menu();
}

void add_record()
{
	system("cls");
	FILE* file;
	Person person;
	file = fopen("PhoneBookRecords.txt", "ab+");
	printf("\nEnter Full Name:");
	get_input(person.full_name);

	printf("\nEnter ID:");
	get_input(person.id);
	
	printf("\nEnter Address:");
	get_input(person.address);
	
	printf("\nEnter Father Name:");
	get_input(person.father_name);
	
	printf("\nEnter Mother Name:");
	get_input(person.mother_name);
	
	printf("\nEnter Phone Number:");
	get_input(person.phone_number);
	
	printf("\nEnter Gender:");
	get_input(person.gender);
	
	printf("\nEnter E-mail:");
	get_input(person.email);

	fwrite(&person, sizeof(person), 1, file);

	fflush(stdin);
	printf("\nRecord Saved!");
	fclose(file);
	
	ending_process();
}

void list_records()
{
	Person person;
	FILE* file;
	file = fopen("PhoneBookRecords.txt", "rb");
	
	if (!file)
	{
		printf("\nFile opening error...");
		exit(1);
	}

	while (fread(&person, sizeof(person), 1, file) == 1)
	{
		printf("\n\n\nYOUR RECORD IS\n\n");
		display_person_info(person);
		getch();
		system("cls");
	}

	fclose(file);
	
	ending_process();
}

void search_record()
{
	int found_name = 0;
	Person person;
	FILE* file;
	char name_to_search[50];

	file = fopen("PhoneBookRecords.txt", "rb");
	if (!file)
	{
		printf("\nFile opening error...");
		exit(1);
	}

	printf("\nEnter name of person to search in the record:\n");
	get_input(name_to_search);

	while (fread(&person, sizeof(person), 1, file) == 1)
	{
		if (strcmp(person.full_name, name_to_search) == 0)
		{
			printf("\n\t Detail Information About %s: ", person.full_name);
			display_person_info(person);
			found_name = 1;
		}
	}

	if (!found_name)
	{
		printf("\nName not found in records...");
	}

	fclose(file);

	ending_process();
}

void delete_record()
{
	Person person;
	FILE* file;
	FILE* temp_file;
	int found_name = 0;
	char name_to_delete[50];

	file = fopen("PhoneBookRecords.txt", "rb");
	if (!file)
	{
		printf("\nFile opening error...");
		exit(1);
	}

	temp_file = fopen("temp.txt", "wb+");
	if (!temp_file)
	{
		printf("\nFile opening error...");
		exit(1);
	}

	printf("\nEnter contact's name: ");
	get_input(name_to_delete);

	fflush(stdin);
	while (fread(&person, sizeof(person), 1, file) == 1)
	{
		if (strcmp(person.full_name, name_to_delete) != 0)
		{
			fwrite(&person, sizeof(person), 1, temp_file);
		}
		else // => name found (strcmp == 0)
		{
			found_name = 1;
		}
	}

	fclose(file);
	fclose(temp_file);

	if (found_name)
	{
		remove("PhoneBookRecords.txt");
		rename("temp.txt", "PhoneBookRecords.txt");
		printf("\nRECORD DELETED SUCCESSFULLY");
	}
	else
	{
		printf("\nNo contact record to delete...");
		remove("temp.txt");
	}

	ending_process();
}

void modify_record()
{
	// Line 227
}

void get_input(char* input)
{

}