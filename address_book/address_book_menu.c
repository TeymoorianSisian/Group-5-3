#include <stdio.h>
//#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//#include "abk_fileops.h"
//#include "abk_log.h"
//#include "abk_menus.h"
//#include "abk.h"

#include "address_book_fops.h" //fileops
#include "address_book_menu.h"
#include "address_book.h"

extern AddressBook *newAddresses;
extern ContactInfo *contactinfo;

int get_option(int type, const char *msg)
{
	char option[10];
	char *ptr;
	int result = 0;
	printf("%s", msg);
	if (type != 0) {
		scanf("%s", option);
	}
	if (type == 1) {
    	result = atoi(option);
		printf("%d", result);
	}
	if (type == 2) {
    	result = strtol(option, &ptr, 10);
		printf("%d\n", result);
		printf("%s\n", ptr);
		return *ptr;
	} 
	return result;


	/*
	 * Mutilfuction user intractions like
	 * Just an enter key detection
	 * Read an number
	 * Read a charcter
	 */ 

	/* Fill the code to add above functionality */
}

Status save_prompt(AddressBook *address_book)
{
	char option;
	printf("test33");
	
	do
	{
		main_menu();
		printf("test33");
		option= get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");
		

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);
	free(contactinfo);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)  //i will do
{
	if (mode == e_list) {
		menu_header("Search Result:\n");
		printf("============================================================================================================================");
		printf("\n: S.No : Name                              : Phone No                          : Email ID                                  :");
		for (int i = 0; i < newAddresses->count; i++) {   
			char format[20] = " ";
			ContactInfo *ptr = newAddresses->list;
			printf("\n============================================================================================================================");
			printf("\n: %-4.4d : %-33.32s : %-33.32s : %-41.32s :", (i+ptr)->si_no, (i+ptr)->name, (i+ptr)->phone_numbers[0], (i+ptr)->email_addresses);
			for (int j = 1; j < 5; j++) {
				printf("\n: %-4.4s : %-33.32s : %-33.32s : %-41.32s :"
				,format, format,(i+ptr)->phone_numbers[j], (i+ptr)->email_addresses[j]);
			}
    	}
		printf("\n============================================================================================================================");
		char exit[10];
		while(strcmp(exit, "q") != 0) {
			printf("\nPress: [q] to Cancel: ");
			scanf("%s", exit);
		}
	}
	else if(mode == e_add) {
		menu_header("Add Contact: ");
		printf("\n0. Back");
		printf("\n1. Name        : %s", ((newAddresses->count)+contactinfo)->name);
		printf("\n2. Phone No 1  : %s",((newAddresses->count)+contactinfo)->phone_numbers[0]);
		printf("\n3. Email ID 1  : %s", ((newAddresses->count)+contactinfo)->email_addresses[0]);
	}
	else if(mode == e_search) {
		
		
		
	}
		
	
	/* 
	 * Add code to list all the contacts availabe in address_book.csv file
	 * Should be menu based
	 * The menu provide navigation option if the entries increase the page size
	 */ 

	return e_success;
}

void menu_header(const char *str)
{
	fflush(stdout);

	system("cls");  //changed from clear to cls

	printf("#######  Address Book  #######\n");
	if (*str != '\0')  //i added * in front of str
	{
		printf("#######  %s\n", str);
	}
}

void main_menu(void)
{
	menu_header("Features:\n");

	printf("0. Exit\n");
	printf("1. Add Contact\n");
	printf("2. Search Contact\n");
	printf("3. Edit Contact\n");
	printf("4. Delete Contact\n");
	printf("5. List Contacts\n");
	printf("6. Save\n");
	printf("\n");
	printf("Please select an option: ");

}

Status menu(AddressBook *address_book)
{
	ContactInfo backup;
	Status ret;
	int option;
	//MenuFeatures(e_exit) = 0;
	do
	{
		main_menu();

		option = get_option(NUM, "");
		//option = atoi(option);
		

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				add_contacts(address_book);
				break;
			case e_search_contact:
				search_contact(address_book);
				break;
			case e_edit_contact:
				edit_contact(address_book);
				break;
			case e_delete_contact:
				delete_contact(address_book);
				break;
			case e_list_contacts:
				list_contacts(address_book, "lister", 0, "list", e_list);
				break;
			case e_save:
				save_file(address_book);
				break;
			case e_exit:
				break;
		}
	} while (option != e_exit);

	return e_success;
}

Status add_contacts(AddressBook *address_book)
{
	char response[255];
	contactinfo = (ContactInfo*) realloc(contactinfo, ((newAddresses->count + 1) * sizeof(ContactInfo)));
    newAddresses->list = contactinfo;
	strcpy( *((newAddresses->count)+contactinfo)->name, " ");
	strcpy(((newAddresses->count)+contactinfo)->phone_numbers[0], " ");
	strcpy(((newAddresses->count)+contactinfo)->email_addresses[0], " ");
	int addedData = 1; //not added data yet
	while (strcmp(response, "0") != 0) {
		list_contacts(address_book, "lister", 0, "list", e_add);
		printf("\n\nPlease select an option for add: ");
		scanf("%s", response);
		if (strcmp(response, "1") == 0){
			printf("\nEnter name: ");
			scanf("%s", ((newAddresses->count)+contactinfo)->name);
			addedData = 0; //added data;
		}
		if (strcmp(response, "2") == 0){
			printf("\nEnter Phone No 1: ");
			scanf("%s", ((newAddresses->count)+contactinfo)->phone_numbers[0]);
			addedData = 0; //added data;
		}
		if (strcmp(response, "3") == 0){
			printf("\nEnter Email ID 1: ");
			scanf("%s", ((newAddresses->count)+contactinfo)->email_addresses[0]);
			addedData = 0; //added data;
		}
	}
	if (addedData == 0) {
		 ((newAddresses->count)+contactinfo)->si_no= newAddresses->count + 1;
		 for (int j = 1; j < 5; j++) {
            strcpy(((newAddresses->count)+contactinfo)->phone_numbers[j], " ");
        }
        for (int j = 1; j < 5; j++) {
            strcpy(((newAddresses->count)+contactinfo)->email_addresses[j], " ");
        }
		newAddresses->count++;
	}
	else if (addedData == 1) {
		
	}

}

Status search(char keyword[], AddressBook *address_book, int loop_count, int field, char searchBy[], Modes mode)
{

	for (int i = loop_count; i < loop_count+1; i++) {   
        ContactInfo *ptr = newAddresses->list;
		if (strcmp(searchBy, "Serial") == 0) {
			if ((i+ptr)->si_no != atoi(keyword)) {
				return e_no_match;
			}
			return e_success;
		}
		if (strcmp(searchBy, "Name") == 0) {
			if (strcmp(*(i+ptr)->name, keyword) != 0) {
				return e_no_match;
			}
			return e_success;
		}
		if (strcmp(searchBy, "Phone") == 0) {
			for (int j = 0; j < 5; j++) {
				if (strcmp((i+ptr)->phone_numbers[j], keyword) == 0) {
					return e_success;
				}
			}
		}
        if (strcmp(searchBy, "Email") == 0) {
			for (int j = 0; j < 5; j++) {
				if (strcmp((i+ptr)->email_addresses[j], keyword) == 0) {
					return e_success;
				}
			}
		}
		return e_no_match;
    }
}

Status search_contact(AddressBook *address_book)
{
	char response[255];
	char searchword[255];
	char searchBy[255];
	char exit[10];
	while (strcmp(response, "0") != 0) {
		menu_header("Search Contact by:");
		strcpy(exit, "noexit");
		printf("\n0. Back");
		printf("\n1. Name");
		printf("\n2. Phone No 1");
		printf("\n3. Email ID 1");
		printf("\n4. Serial No");
		printf("\n\nPlease select an option for search: ");
		scanf("%s", response);
		while (strcmp(response, "0") != 0 && strcmp(response, "1") != 0 && strcmp(response, "2") != 0 && strcmp(response, "3") != 0 && 
			strcmp(response, "4") != 0) {
					menu_header("Search Contact by:");
					strcpy(exit, "noexit");
					printf("\n0. Back");
					printf("\n1. Name");
					printf("\n2. Phone No 1");
					printf("\n3. Email ID 1");
					printf("\n4. Serial No");
					printf("\n\nPlease select an option for search: ");
					scanf("%s", response);
		}
		if (strcmp(response, "0") == 0){
			break;
		}
	if (strcmp(response, "1") == 0){
		printf("\nEnter name: ");
		scanf("%s", searchword);
		strcpy(searchBy, "Name");
	}
	if (strcmp(response, "2") == 0){
		printf("\nEnter Phone No 1: ");
		scanf("%s", searchword);
		strcpy(searchBy, "Phone");
	}
	if (strcmp(response, "3") == 0){
		printf("\nEnter Email ID 1: ");
		scanf("%s", searchword);
		strcpy(searchBy, "Email");
	}
	if (strcmp(response, "4") == 0){
		printf("\nEnter Serial No: ");
		scanf("%s", searchword);
		strcpy(searchBy, "Serial");
	}
	menu_header("Search Result:\n");
	printf("============================================================================================================================");
	printf("\n: S.No : Name                              : Phone No                          : Email ID                                  :");
	for (int i = 0; i < newAddresses->count; i++) {   

		if (search(searchword, address_book, i, 0, searchBy, e_search) == e_success) {
		char format[20] = " ";
		ContactInfo *ptr = newAddresses->list;
		printf("\n============================================================================================================================");
		printf("\n: %-4.4d : %-33.32s : %-33.32s : %-41.32s :", (i+ptr)->si_no, (i+ptr)->name, (i+ptr)->phone_numbers[0], (i+ptr)->email_addresses);
		for (int j = 1; j < 5; j++) {
			printf("\n: %-4.4s : %-33.32s : %-33.32s : %-41.32s :"
			,format, format,(i+ptr)->phone_numbers[j], (i+ptr)->email_addresses[j]);
			
		}

		}
    }
	printf("\n============================================================================================================================");
	
	while(strcmp(exit, "q") != 0) {
		
		printf("\nPress: [q] to Cancel: ");
		scanf("%s", exit);
	}
		

	}
}

Status edit_contact(AddressBook *address_book)
{
	char response[255];
	char searchword[255];
	char searchBy[255];
	char selection[10];
	while (strcmp(response, "0") != 0) {
		menu_header("Search Contact to Edit by:");
		strcpy(selection, "select");
		printf("\n0. Back");
		printf("\n1. Name");
		printf("\n2. Phone No 1");
		printf("\n3. Email ID 1");
		printf("\n4. Serial No");
		printf("\n\nPlease select an option for search: ");
		scanf("%s", response);
		while (strcmp(response, "0") != 0 && strcmp(response, "1") != 0 && strcmp(response, "2") != 0 && strcmp(response, "3") != 0 && 
			strcmp(response, "4") != 0) {
					menu_header("Search Contact by:");
					strcpy(selection, "noexit");
					printf("\n0. Back");
					printf("\n1. Name");
					printf("\n2. Phone No 1");
					printf("\n3. Email ID 1");
					printf("\n4. Serial No");
					printf("\n\nPlease select an option for search: ");
					scanf("%s", response);
		}
		if (strcmp(response, "0") == 0){
			break;
		}
	if (strcmp(response, "1") == 0){
		printf("\nEnter name: ");
		scanf("%s", searchword);
		strcpy(searchBy, "Name");
	}
	if (strcmp(response, "2") == 0){
		printf("\nEnter Phone No 1: ");
		scanf("%s", searchword);
		strcpy(searchBy, "Phone");
	}
	if (strcmp(response, "3") == 0){
		printf("\nEnter Email ID 1: ");
		scanf("%s", searchword);
		strcpy(searchBy, "Email");
	}
	if (strcmp(response, "4") == 0){
		printf("\nEnter Serial No: ");
		scanf("%s", searchword);
		strcpy(searchBy, "Serial");
	}
	menu_header("Search Result:\n");
	printf("============================================================================================================================");
	printf("\n: S.No : Name                              : Phone No                          : Email ID                                  :");
	for (int i = 0; i < newAddresses->count; i++) {   

		if (search(searchword, address_book, i, 0, searchBy, e_search) == e_success) {

			char format[20] = " ";
			ContactInfo *ptr = newAddresses->list;
			printf("\n============================================================================================================================");
			printf("\n: %-4.4d : %-33.32s : %-33.32s : %-41.32s :", (i+ptr)->si_no, (i+ptr)->name, (i+ptr)->phone_numbers[0], (i+ptr)->email_addresses);
			for (int j = 1; j < 5; j++) {
				printf("\n: %-4.4s : %-33.32s : %-33.32s : %-41.32s :"
				,format, format,(i+ptr)->phone_numbers[j], (i+ptr)->email_addresses[j]);
			}

		}
    }
	printf("\n============================================================================================================================");
	while(strcmp(selection, "q") != 0) {
		printf("\nPress: [s] = Select, [q] to Cancel: ");
		scanf("%s", selection);
		if (strcmp(selection, "q") != 0) {
			printf("\nSelect a Serial Number (S.No) to Edit: ");
			scanf("%s", searchword);
			menu_header("Edit Contact: ");

			for (int i = 0; i < newAddresses->count; i++) {
				if (search(searchword, address_book, i, 0, "Serial", e_search) == e_success) {
					while (strcmp(response, "0") != 0) {
						menu_header("Edit Contact: ");
						printf("\n0. Back");
						printf("\n1. Name        : %s", ((i)+contactinfo)->name);
						printf("\n2. Phone No 1  : %s",((i)+contactinfo)->phone_numbers[0]);
						int counter = 3;
						int amtOfEmails = 1;
						int amtOfPhones = 1;
						for (int j= 1; j < 5; j++) {
							if (strcmp((i+contactinfo)->phone_numbers[j], " ") != 0) {
								printf("\n   Phone No %d  : %s", j+1,(i+contactinfo)->phone_numbers[j]);
								counter++;
								amtOfPhones++;
							}
						}
						printf("\n3. Email ID 1  : %s", ((i)+contactinfo)->email_addresses[0]);
						for (int j= 1; j < 5; j++) {
							if (strcmp((i+contactinfo)->email_addresses[j], " ") != 0) {
								printf("\n   Email No %d  : %s", j+1,(i+contactinfo)->email_addresses[j]);
								amtOfEmails++;
								counter++;
							}
						}
						int index;
						printf("\n\nPlease select an option for edit: ");
						scanf("%s", response);
						if (strcmp(response, "0") == 0) {
							strcpy(selection, "q");
						}
						if (strcmp(response, "1") == 0){
							printf("\nEnter name: ");
							scanf("%s", ((i)+contactinfo)->name);
						}
						if (strcmp(response, "2") == 0){
							printf("\nEnter Phone Number index to be changed [Max 5]: ");
							scanf("%d", &index);
							printf("\nEnter Phone Number %d: ", index);
							scanf("%s", ((i)+contactinfo)->phone_numbers[index-1]);
						}
						if (strcmp(response, "3") == 0){
							printf("\nEnter Email index to be changed [Max 5]: ");
							scanf("%d", &index);
							printf("\nEnter Email %d: ", index);
							scanf("%s", ((i)+contactinfo)->email_addresses[index-1]);
						}
					}
			}	}
	
		}
	}
	
	

	}
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	char response[255];
	char searchword[255];
	char searchBy[255];
	char selection[10];
	while (strcmp(response, "0") != 0) {
		menu_header("Search Contact to Delete by:");
		strcmp(selection, "select");
		printf("\n0. Back");
		printf("\n1. Name");
		printf("\n2. Phone No 1");
		printf("\n3. Email ID 1");
		printf("\n4. Serial No");
		printf("\n\nPlease select an option for search: ");
		scanf("%s", response);
		while (strcmp(response, "0") != 0 && strcmp(response, "1") != 0 && strcmp(response, "2") != 0 && strcmp(response, "3") != 0 && 
			strcmp(response, "4") != 0) {
					menu_header("Search Contact by:");
					strcpy(selection, "noexit");
					printf("\n0. Back");
					printf("\n1. Name");
					printf("\n2. Phone No 1");
					printf("\n3. Email ID 1");
					printf("\n4. Serial No");
					printf("\n\nPlease select an option for search: ");
					scanf("%s", response);
		}
		if (strcmp(response, "0") == 0){
			break;
		}
	if (strcmp(response, "1") == 0){
		printf("\nEnter name: ");
		scanf("%s", searchword);
		strcpy(searchBy, "Name");
	}
	if (strcmp(response, "2") == 0){
		printf("\nEnter Phone No 1: ");
		scanf("%s", searchword);
		strcpy(searchBy, "Phone");
	}
	if (strcmp(response, "3") == 0){
		printf("\nEnter Email ID 1: ");
		scanf("%s", searchword);
		strcpy(searchBy, "Email");
	}
	if (strcmp(response, "4") == 0){
		printf("\nEnter Serial No: ");
		scanf("%s", searchword);
		strcpy(searchBy, "Serial");
	}
	menu_header("Search Result:\n");
	printf("============================================================================================================================");
	printf("\n: S.No : Name                              : Phone No                          : Email ID                                  :");
	for (int i = 0; i < newAddresses->count; i++) {   

		if (search(searchword, address_book, i, 0, searchBy, e_search) == e_success) {

			char format[20] = " ";
			ContactInfo *ptr = newAddresses->list;
			printf("\n============================================================================================================================");
			printf("\n: %-4.4d : %-33.32s : %-33.32s : %-41.32s :", (i+ptr)->si_no, (i+ptr)->name, (i+ptr)->phone_numbers[0], (i+ptr)->email_addresses);
			for (int j = 1; j < 5; j++) {
				printf("\n: %-4.4s : %-33.32s : %-33.32s : %-41.32s :"
				,format, format,(i+ptr)->phone_numbers[j], (i+ptr)->email_addresses[j]);
			}

		}
    }

	while(strcmp(selection, "q") != 0) {
		printf("\nPress: [s] = Select, [q] to Cancel: ");
		scanf("%s", selection);
		if (strcmp(selection, "q") != 0) {
			printf("\nSelect a Serial Number (S.No) to Edit: ");
			scanf("%s", searchword);
			menu_header("Edit Contact: ");

			for (int i = 0; i < newAddresses->count; i++) {
				if (search(searchword, address_book, i, 0, "Serial", e_search) == e_success) {
					while (strcmp(response, "0") != 0) {
						menu_header("Edit Contact: ");
						printf("\n0. Back");
						printf("\n1. Name        : %s", ((i)+contactinfo)->name);
						printf("\n2. Phone No 1  : %s",((i)+contactinfo)->phone_numbers[0]);
						int counter = 3;
						int amtOfEmails = 1;
						int amtOfPhones = 1;
						for (int j= 1; j < 5; j++) {
							if (strcmp((i+contactinfo)->phone_numbers[j], " ") != 0) {
								printf("\n   Phone No %d: %s", j+1,(i+contactinfo)->phone_numbers[1]);
								counter++;
								amtOfPhones++;
							}
						}
						printf("\n3. Email ID 1  : %s", ((i)+contactinfo)->email_addresses[0]);
						for (int j= 1; j < 5; j++) {
							if (strcmp((i+contactinfo)->email_addresses[j], " ") != 0) {
								printf("\n   Email No %d  : %s", j+1,(i+contactinfo)->email_addresses[j]);
								amtOfEmails++;
								counter++;
							}
						}
						printf("\n\nPress 'Y' to delete. [Press any key to ignore]: ");
						scanf("%s", response);
						if (strcmp(response, "Y") == 0) {
							
							ContactInfo *ptr = newAddresses->list;
							printf("\nSerial: %d", (i+ptr)->si_no);
							strcpy(*(i+ptr)->name, *((newAddresses->count - 1)+ptr)->name);
							for (int j = 0; j < 5; j++) {
								strcpy((i+ptr)->phone_numbers[j], ((newAddresses->count - 1)+ptr)->phone_numbers[j]);
							}
							for (int j = 0; j < 5; j++) {
								strcpy((i+ptr)->email_addresses[j], ((newAddresses->count - 1)+ptr)->email_addresses[j]);
							}
							contactinfo = (ContactInfo*) realloc(contactinfo, ((newAddresses->count - 1) * sizeof(ContactInfo)));
							newAddresses->list = contactinfo;
							newAddresses->count--;
						}	
						strcpy(response, "0");
						strcpy(selection, "q");
					}
			}	}
	
		}
	}
	
	
	}
	
}
