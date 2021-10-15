#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <ctype.h>

#include "address_book.h"

AddressBook *newAddresses;
ContactInfo *contactinfo;

Status load_file(AddressBook *address_book)
{
	int ret;
	
	ret = access(DEFAULT_FILE, F_OK);

	/* 
	 * Check for file existance
	 */
	if (ret == 0)
	{	
		
    char buff[255];
    int numOfLines=0; 
    char ch;
    address_book->fp = fopen(DEFAULT_FILE, "r");
    newAddresses = (AddressBook*) malloc(1 * sizeof(AddressBook));
    contactinfo = (ContactInfo*) malloc(1 * sizeof(ContactInfo));
    newAddresses->list = contactinfo;
    newAddresses->count = 0;
    while(!feof(address_book->fp)) {
        numOfLines++;
        fgets(buff, 255, (FILE*)address_book->fp);
        char *individualData;
        individualData = strtok (buff,",");
        int counter = 0;
        while (individualData != NULL) {
            counter++;
            if (counter == 1) {
                ((newAddresses->count)+contactinfo)->si_no= atoi(individualData);
            }
            if (counter == 2) {
                strcpy(*((newAddresses->count)+contactinfo)->name, individualData);
            }
            if (counter == 3) {
                strcpy( ((newAddresses->count)+contactinfo)->phone_numbers[0], individualData);
            }
            if (counter == 4) {
                strcpy(((newAddresses->count)+contactinfo)->phone_numbers[1], individualData);
            }
            if (counter == 5) {
                strcpy(((newAddresses->count)+contactinfo)->phone_numbers[2], individualData);
            }
            if (counter == 6) {
                strcpy(((newAddresses->count)+contactinfo)->phone_numbers[3], individualData);
            }
            if (counter == 7) {
                strcpy(((newAddresses->count)+contactinfo)->phone_numbers[4], individualData);
            }
            if (counter == 8) {
                strcpy(((newAddresses->count)+contactinfo)->email_addresses[0], individualData);
            }
            if (counter == 9) {
                strcpy(((newAddresses->count)+contactinfo)->email_addresses[1], individualData);
            }
            if (counter == 10) {
                strcpy(((newAddresses->count)+contactinfo)->email_addresses[2], individualData);
            }
            if (counter == 11) {
                strcpy(((newAddresses->count)+contactinfo)->email_addresses[3], individualData);
            }
            if (counter == 12) {
                strcpy(((newAddresses->count)+contactinfo)->email_addresses[4], individualData);
                newAddresses->count++;
            } 
            individualData = strtok (NULL, ",");
            contactinfo = (ContactInfo*) realloc(contactinfo, ((numOfLines+1) * sizeof(ContactInfo)));
            newAddresses->list = contactinfo;
        }
        
   }
   
	fclose(address_book->fp);
	}
	else
	{
		address_book->fp = fopen(DEFAULT_FILE, "w");
        fclose(address_book->fp);
	}

	return e_success;
}

Status save_file(AddressBook *address_book)
{
	/*
	 * Write contacts back to file.
	 * Re write the complete file currently
	 */ 
	//printf("saving");
	//address_book->fp = fopen(DEFAULT_FILE, "w");

	if (address_book->fp == NULL)
	{
		return e_fail;
	}

	/* 
	 * Add the logic to save the file
	 * Make sure to do error handling
	 */ 
    address_book->fp = fopen("address_book.csv", "w");
    for (int i = 0; i < newAddresses->count; i++) {   
        ContactInfo *ptr = newAddresses->list;
        //printf("\ni: %d", i);
        fprintf(address_book->fp, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,\n", 
        (i+ptr)->si_no, (i+ptr)->name, (i+ptr)->phone_numbers[0],(i+ptr)->phone_numbers[1],(i+ptr)->phone_numbers[2],
        (i+ptr)->phone_numbers[3],(i+ptr)->phone_numbers[4],(i+ptr)->email_addresses[0],(i+ptr)->email_addresses[1],(i+ptr)->email_addresses[2],
        (i+ptr)->email_addresses[3], (i+ptr)->email_addresses[4]);
    }
    fclose(address_book->fp);
    //free(newAddresses);
    //free(contactinfo);

	return e_success;
}