/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 2
Full Name  : David Andres Sanchez Umbarila
Student ID#: 140273228
Email      : dasanchez-umbarila@myseneca.ca
Section    : NBB

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
/////////////////////////////////////////////////////////////////////////*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
               "Number: %05d\n"
               "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
               patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", (*patient).phone.description);    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
               "=========================\n"
               "1) PATIENT     Management\n"
               "2) APPOINTMENT Management\n"
               "-------------------------\n"
               "0) Exit System\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
               "=========================\n"
               "1) VIEW   Patient Data\n"
               "2) SEARCH Patients\n"
               "3) ADD    Patient\n"
               "4) EDIT   Patient\n"
               "5) REMOVE Patient\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
               "=========================\n"
               "1) NAME : %s\n"
               "2) PHONE: ", patient->patientNumber, patient->name);
        
        displayFormattedPhone(patient->phone.number);
        
        printf("\n"
               "-------------------------\n"
               "0) Previous menu\n"
               "-------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! Put all the remaining function definitions below !!!
// Note: Maintain the same order/sequence as it is listed in the header file
// ---------------------------------------------------------------------------

// Display's all patient data in the FMT_FORM | FMT_TABLE format
void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int noRecordsFound = 0, i;
    printf("Pat.# Name            Phone#\n"
           "----- --------------- --------------------\n");
    for (i = 0; i < max; i++)
    {
        if (patient[i].phone.number == 0)
        {
            noRecordsFound++;
        }
        else
        {
            if (patient[i].patientNumber != 0)
            {
                displayPatientData(&patient[i], fmt);
            }
        }   
    }
    if (noRecordsFound == max) printf("*** No records found ***");
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection, flag = 1;
    do
    {
        printf( "Search Options\n"
                "==========================\n"
                "1) By patient number\n"
                "2) By phone number\n"
                "..........................\n"
                "0) Previous menu\n"
                "..........................\n"
                "Selection: ");
        selection = inputInt();
        
        switch (selection)
        {
        case 1:
            putchar('\n');
            searchPatientByPatientNumber(patient,max);
	    suspend();
            break;
        
        case 2:
            putchar('\n');
            searchPatientByPhoneNumber(patient, max);
	    suspend();
            break;

        case 0:
	    putchar('\n');
            flag = 0;
            break;

        default:
            putchar('\n');
            printf("*** Invalid Input ***");
            break;
        }
    } while(flag);
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int emptyPos = -1, i;
    for (i = 0; i < max && emptyPos == -1; i++)
    {
        if (patient[i].patientNumber == 0){
            emptyPos = i;
        }
    }
    
    if (emptyPos == -1)
    {
        printf("ERROR: Patient listing is FULL!\n");
    }
    else
    {
        patient[emptyPos].patientNumber = nextPatientNumber(patient, max);
        inputPatient(&patient[emptyPos]);
        printf("*** New patient record added ***\n");
    }
}

// Edit a patient record from the patient array
void editPatient(struct Patient patient[], int max)
{
    int numberLookUp, patientIndex;
    printf("Enter the patient number: ");
    numberLookUp = inputInt();
    putchar('\n');
    patientIndex = findPatientIndexByPatientNum(numberLookUp, patient, max);
    if (patientIndex == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        menuPatientEdit(&patient[patientIndex]);
    }  
}

// Remove a patient record from the patient array
void removePatient(struct Patient patient[], int max)
{
    int numberLookUp, patientIndex;
    char selection;
    printf("Enter the patient number: ");
    numberLookUp = inputInt();
    putchar('\n');
    patientIndex = findPatientIndexByPatientNum(numberLookUp, patient, max);
    if (patientIndex == -1)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        displayPatientData(&patient[patientIndex], FMT_FORM);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        char option[2] = {'y', 'n'};
        selection = inputCharOption(option);
        if (selection == 'y')
        {
            struct Patient defaultP = {0};
            patient[patientIndex] = defaultP;
            printf("Patient record has been removed!\n");
        }
        else
        {
            printf("Operation aborted.\n");
        }
    }
}

//////////////////////////////////////
// UTILITY FUNCTIONS
//////////////////////////////////////

// Search and display patient record by patient number (form)
void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    int numberLookUp, patientIndex;
    printf("Search by patient number: ");
    numberLookUp = inputInt();
    putchar('\n');
    patientIndex = findPatientIndexByPatientNum(numberLookUp, patient, max);
    if (patientIndex == -1)
    {
        printf("*** No records found ***\n");
    }
    else
    {
        displayPatientData(&patient[patientIndex], FMT_FORM);
    }
    

}

// Search and display patient records by phone number (tabular)
void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    int matches = 0, i;
    char numberLookUp[PHONE_LEN+1];
    printf("Search by phone number: ");
    inputCString(numberLookUp,PHONE_LEN,PHONE_LEN);
    putchar('\n');
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp(patient[i].phone.number,numberLookUp) == 0)
        {
            displayPatientData(&patient[i], FMT_TABLE);
            matches++;
        }
    }
    if (matches == 0)
        printf("\n*** No records found ***\n");
}

// Get the next highest patient number
int nextPatientNumber(const struct Patient patient[], int max)
{
    int greatest = 0, i;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber > greatest)
        {
            greatest = patient[i].patientNumber;
        }
    }
    return ++greatest; 
}

// Find the patient array index by patient number (returns -1 if not found)
int findPatientIndexByPatientNum(int patientNumber,
                                 const struct Patient patient[], int max)
{
    int i;
    for (i = 0; i < max; i++)
    {
        if (patient[i].patientNumber == patientNumber) return i;
    }
    return -1;
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

// Get user input for a new patient record
void inputPatient(struct Patient *patient)
{
    printf("Patient Data Input\n"
           "------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name,1,NAME_LEN);
    putchar('\n');
    inputPhoneData(&(patient->phone));
}

// Get user input for phone contact information
void inputPhoneData(struct Phone *phone)
{
    int selection;
    struct Phone defaultPhone = {"TBD", {'\0'}};
    printf("Phone Information\n"
           "-----------------\n"
           "How will the patient like to be contacted?\n"
           "1. Cell\n"
           "2. Home\n"
           "3. Work\n"
           "4. TBD\n"
           "Selection: ");
    selection = inputInt();
    putchar('\n');
    switch (selection)
    {
    case 1:
        printf("Contact: CELL\n");
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        putchar('\n');
        strcpy(phone->description, "CELL");
        break;

    case 2:
        printf("Contact: HOME\n");
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        putchar('\n');
        strcpy(phone->description, "HOME");
        break;

    case 3:
        printf("Contact: WORK\n");
        printf("Number : ");
        inputCString(phone->number, PHONE_LEN, PHONE_LEN);
        putchar('\n');
        strcpy(phone->description, "WORK");
        break;

    case 4:
        *phone = defaultPhone;
        break;
    }
    
}
