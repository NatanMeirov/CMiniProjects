#define _CRT_SECURE_NO_WARNINGS
#include "PhoneBookApplication.h"

int main()
{
	start();

	return 0;
}

void start()
{
	system("color 5f");
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
		list_records();
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
		printf("\nEnter 1 to 6 only");
		ending_process();
	}
}

void display_person_info(Person* person_ptr)
{
	printf("\nFull Name: %s \nID: %s \nAddress: %s \nFather Name: %s \nMother Name: %s \nPhone Number: %s \nGender: %s \nE-mail: %s ", person_ptr->full_name, person_ptr->id, person_ptr->address, person_ptr->father_name, person_ptr->mother_name, person_ptr->phone_number, person_ptr->gender, person_ptr->email);
}

void ending_process()
{
	printf("\n\nEnter any key...");
	_getch(); // getch()
	system("cls");
	menu();
}

void get_person_info(Person* person_ptr)
{
	printf("\nEnter Full Name:");
	get_input(person_ptr->full_name, NAME_LIMIT);

	printf("\nEnter ID:");
	get_input(person_ptr->id, ID_LIMIT);

	printf("\nEnter Address:");
	get_input(person_ptr->address, ADDRESS_LIMIT);

	printf("\nEnter Father Name:");
	get_input(person_ptr->father_name, NAME_LIMIT);

	printf("\nEnter Mother Name:");
	get_input(person_ptr->mother_name, NAME_LIMIT);

	printf("\nEnter Phone Number:");
	get_input(person_ptr->phone_number, PHONE_NUMBER_LIMIT);

	printf("\nEnter Gender:");
	get_input(person_ptr->gender, GENDER_LIMIT);

	printf("\nEnter E-mail:");
	get_input(person_ptr->email, EMAIL_LIMIT);
}

void add_record()
{
	FILE* file;
	Person person;

	system("cls");

	file = fopen("PhoneBookRecords.txt", "ab+");
	
	get_person_info(&person);

	fwrite(&person, sizeof(Person), 1, file);

	fflush(stdin);
	printf("\nRecord Saved!");
	fclose(file);
	
	ending_process();
}

void list_records()
{
	Person person;
	FILE* file;

	system("cls");

	file = fopen("PhoneBookRecords.txt", "rb");
	
	if (!file)
	{
		printf("\nFile opening error...");
		exit(1);
	}

	printf("\n\nYOUR RECORDS\n\n");
	fflush(stdin);
	while (fread(&person, sizeof(Person), 1, file) == 1)
	{
		display_person_info(&person);
		printf("\n\n");

		fflush(stdin);
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

	system("cls");

	file = fopen("PhoneBookRecords.txt", "rb");
	if (!file)
	{
		printf("\nFile opening error...");
		exit(1);
	}

	printf("\nEnter name of person to search in the record:\n");
	get_input(name_to_search, NAME_LIMIT);

	fflush(stdin);
	while (fread(&person, sizeof(Person), 1, file) == 1)
	{
		if (strcmp(person.full_name, name_to_search) == 0)
		{
			printf("\n\t Detail Information About %s: ", person.full_name);
			display_person_info(&person);
			found_name = 1;
		}

		fflush(stdin);
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

	system("cls");

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
	get_input(name_to_delete, NAME_LIMIT);

	fflush(stdin);
	while (fread(&person, sizeof(Person), 1, file) == 1)
	{
		if (strcmp(person.full_name, name_to_delete) != 0)
		{
			fwrite(&person, sizeof(Person), 1, temp_file);
		}
		else // => name found (strcmp == 0)
		{
			found_name = 1;
		}

		fflush(stdin);
	}

	fclose(file);
	fclose(temp_file);

	if (found_name)
	{
		remove("PhoneBookRecords.txt");
		rename("temp.txt", "PhoneBookRecords.txt");
		printf("\nCONTACT RECORD DELETED SUCCESSFULLY");
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
	FILE* file;
	int found_name = 0;
	Person person, temp_person;
	char name_to_modify[50];

	system("cls");

	file = fopen("PhoneBookRecords.txt", "rb+");
	if (!file)
	{
		printf("\nFile opening error...");
		exit(1);
	}

	printf("\nEnter contact's name to modify: ");
	get_input(name_to_modify, NAME_LIMIT);

	fflush(stdin);
	while (fread(&person, sizeof(Person), 1, file) == 1)
	{
		if (strcmp(name_to_modify, person.full_name) == 0)
		{
			get_person_info(&temp_person);
			fseek(file, -(int)sizeof(Person), SEEK_CUR);
			fwrite(&temp_person, sizeof(Person), 1, file);
			found_name = 1;
			break;
		}

		fflush(stdin);
	}

	if (found_name)
	{
		printf("\nCONTACT MODIFIED SUCCESSFULLY");
	}
	else
	{
		printf("\nNo contact record to modify...");
	}

	fclose(file);

	ending_process();
}

void get_input(char* input_buffer, int limit)
{
	int i = 0, counter = 1;
	char input_char, display_char;

	do
	{
		input_char = _getch(); // getch()

		if (input_char != 8 && input_char != 13)
		{
			*(input_buffer + i) = input_char;
			_putch(input_char); // putch(input_char)
			i++;
			counter++;
		}

		if (counter + 1 == limit) 
		{
			break;
		}

	} while (input_char != 13);

	*(input_buffer + i) = '\0';
}
