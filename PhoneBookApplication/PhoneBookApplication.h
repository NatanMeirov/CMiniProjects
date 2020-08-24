#ifndef _PHONEBOOKAPPLICATION_H_
#define _PHONEBOOKAPPLICATION_H_

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <windows.h>

#define NAME_LIMIT  50
#define ID_LIMIT  15
#define ADDRESS_LIMIT 50
#define PHONE_NUMBER_LIMIT  20
#define GENDER_LIMIT  8
#define EMAIL_LIMIT  100

typedef struct person
{
	char full_name[NAME_LIMIT];
	char id[ID_LIMIT];
	char address[ADDRESS_LIMIT];
	char father_name[NAME_LIMIT];
	char mother_name[NAME_LIMIT];
	char phone_number[PHONE_NUMBER_LIMIT];
	char gender[GENDER_LIMIT];
	char email[EMAIL_LIMIT];

} Person;

void start();
void menu();
void get_person_info(Person* person_ptr);
void get_input(char* input_buffer, int limit);
void display_person_info(Person* person_ptr);
void ending_process();
void add_record();
void list_records();
void modify_record();
void delete_record();
void search_record();

#endif // _PHONEBOOKAPPLICATION_H_

