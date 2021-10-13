#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "abk_fileops.h"
#include "abk_log.h"
#include "abk_menus.h"
#include "abk.h"

int get_option(int type, const char *msg)
{
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

	do
	{
		main_menu();

		option = get_option(CHAR, "\rEnter 'N' to Ignore and 'Y' to Save: ");

		if (option == 'Y')
		{
			save_file(address_book);
			printf("Exiting. Data saved in %s\n", DEFAULT_FILE);

			break;
		}
	} while (option != 'N');

	free(address_book->list);

	return e_success;
}

Status list_contacts(AddressBook *address_book, const char *title, int *index, const char *msg, Modes mode)
{
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

	system("clear");

	printf("#######  Address Book  #######\n");
	if (str != '\0')
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

	do
	{
		main_menu();

		option = get_option(NUM, "");

		if ((address_book-> count == 0) && (option != e_add_contact))
		{
			get_option(NONE, "No entries found!!. Would you like to add? Use Add Contacts");

			continue;
		}

		switch (option)
		{
			case e_add_contact:
				/* Add your implementation to call add_contacts function here */
				address_book -> list = malloc(sizeof(ContactInfo));
			        for (int i = 0; i < PHONE_NUMBER_COUNT; i++)
				{
						strcpy(address_book -> list -> phone_numbers[i], "");
				}
				add_contacts(address_book);
				return save_prompt(address_book);
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
				break;
				/* Add your implementation to call list_contacts function here */
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
    /* Add the functionality for adding contacts here */
    int option;
            do
            {
                    menu_header("Please select an option:\n ");
                    show_menu();
                    option = get_option(NUM, "");              
                    if (option != e_second_opt && !AddName)
                    {
                            get_option(NONE, "Add a name!\n");
                            continue;
                    }
                    switch (option)
                    {
                            case e_second_opt://Name
                                    char name[NAME_LEN] = 0;
                                    printf("Enter the Name: ");
                                    scanf("%32[^\n]", name);
                                    break;
                            case e_third_opt://Phone Number
                                    char phoneNumber[NUMBER_LEN] = 0;
                                    int i=0;
                                    printf("Enter Phone Number %d: ", i + 1);
                                    scanf("%[^\n]", phoneNumber);
                                    break;
                            case e_fourth_opt://Email address
                                    char email[EMAIL_ID_LEN] = 0;
                                    int i = 0;
                                    printf("Enter Email Address %d: ", i + 1);
                                    scanf("%32[^\n]", email);
                                    break;
                            case e_fifth_opt://Back
                                    break;
                            case e_no_opt://Just enter
                                    break;
                            default://Invalid option
                                    printf("Invalid option!!\n");
                    }
            } while (option != e_fifth_opt);
            return e_success;
}

Status search(const char *str, AddressBook *address_book, int loop_count, int field, const char *msg, Modes mode)
{
	/* Add the functionality for adding contacts here */
}

Status search_contact(AddressBook *address_book)
{
	/* Add the functionality for search contacts here */
}

Status edit_contact(AddressBook *address_book)
{
	/* Add the functionality for edit contacts here */
	int option;
	char str[EMAIL_ID_LEN];
	do
	{
		menu_header("Which of the following would you like to edit?\n");
		show_menu();
		option = get_option(NUM, "");
		switch (option)
		{
			case e_second_opt://Name
				printf("Enter the name you want to edit: ");
				scanf("%[^\n]", str);
				
				if (search_serial_num(address_book, str, 0) > 0)
				{
					printf("Name %s is found in the Addressbook to be edited!\n", str);
					printf("Enter a new name: ");
					scanf("%[^\n]", str);
					edit_content(address_book, str);
				}
				else
				{
					printf("Name is not found! Fail to edit!!\n");
				}
								
				break;
			case e_third_opt://Phone Number
				printf("Enter the phone no. you want to edit: ");
				scanf("%[^\n]", str);
				
				if (search_serial_num(address_book, str, 0) > 0)
				{
					printf("Phone no. %s is found in the Addressbook\n", str);
					printf("Enter a new phone no: ");
					scanf("%[^\n]", str);
					edit_content(address_book, str);
				}
				else
				{
					printf("Phone np. is not found! Fail to edit!\n");
				}
				break;
			case e_fourth_opt://Email address
				printf("Enter the email address you want to edit: ");
				scanf("%[^\n]", str);
				if (search_serial_num(address_book, str, 0) > 0)
				{
					printf("Email Id %s is found in the Addressbook!\n", str);
					printf("Enter a new email id: ");
					scanf("%[^\n]", str);
					edit_content(address_book, str);
				}
				else
				{
					
					printf("Email Id is not found! Fail to edit!!\n");
				}
								
				break;
			case e_fifth_opt://Back
				break;
			case e_no_opt://Just enter
				break;
			default://Invalid option
                                    printf("Invalid option!!\n");		
	} while (option != e_fifth_opt);
	return e_success;
}

Status delete_contact(AddressBook *address_book)
{
	/* Add the functionality for delete contacts here */
	int option, sr_no;
	char str[EMAIL_ID_LEN];
	do
	{
		menu_header("Choose the way you want to delete a contact?\n\n0. S. No");
		show_menu();
		option = get_option(NUM, "");
		switch (option)
		{
			case e_first_opt://Sr. No.
				printf("Enter the sr no: ");
				scanf("%d", &sr_no);
				if (search_serial_num(address_book, "**", sr_no) > 0)
				{
					printf("Sr No. %d is found in the Addressbook\nThe entire contact is deleted.\n", sr_no);
					delete_contact(address_book);
				}
				else
				{
					printf("Sr No. not found!\nFail to delete the entered name!\n");
				}
				break;
			case e_second_opt://Name
				printf("Enter the name you want to delete: ");
				scanf("%[^\n]", str);
				if (search_serial_num(address_book, str, 0) > 0)
				{
					printf("Name %s is found in the Addressbook\nThe entire contact is deleted..\n", str);
					delete_contact(address_book);
				}
				else
				{
					printf("Name is not found!\nFail to delete the entered name!!\n");
				}
				break;
			case e_third_opt://Phone Number
				printf("Enter the phone no. you want to delete: ");
				scanf("%[^\n]", str);
				if (search_serial_num(address_book, str, 0) > 0)
				{
					printf("Phone no. %s is found in the Addressbook\nThe entire contact is deleted..\n", str);
					delete_contact(address_book);
				}
				else
				{
					printf("Phone no. is not found!\nFail to delete the entered phone number!\n");
				}
				break;
			case e_fourth_opt://Email address
				printf("Enter the email address you want to delete: ");
				scanf("%[^\n]", str);
				if (search_serial_num(address_book, str, 0) > 0)
				{
					printf("Email Id %s is found in the Addressbook\nThe entire contact is deleted!\n", str);
					delete_contact(address_book);
				}
				else
				{
					printf("Email Id is not found!\nFail to delete the given email Id!!\n");
				}
				break;
			case e_fifth_opt://Back
				break;
			case e_no_opt:
				break;
			default://Invalid option
                                    printf("Invalid option!!\n");
						
		}		
	} while (option != e_fifth_opt);
	return e_success;
}

void show_menu(void)
{
		printf("1. Name\n");
		printf("2. Phone Number\n");
		printf("3. Email Address\n");
		printf("4. Back\n\n");
		printf("Please select an option: ");
}

