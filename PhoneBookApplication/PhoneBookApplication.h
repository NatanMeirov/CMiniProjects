#ifndef _PHONEBOOKAPPLICATION_H_
#define _PHONEBOOKAPPLICATION_H_

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

typedef struct person
{
	char full_name[50];
	char id[15];
	char address[50];
	char father_name[50];
	char mother_name[50];
	char phone_number[20];
	char gender[8];
	char email[100];
} Person;

void menu();
void get_input(char* input);
void display_person_info(Person person);
void ending_process();
void start();
void back();
void add_record();
void list_records();
void modify_record();
void delete_record();
void search_record();

#endif // _PHONEBOOKAPPLICATION_H_

