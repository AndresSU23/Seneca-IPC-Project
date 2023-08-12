/*/////////////////////////////////////////////////////////////////////////
                        Assignment 1 - Milestone 3
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
        printf(" (%s)\n", patient->phone.description);
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's appointment schedule headers (date-specific or all records)
void displayScheduleTableHeader(const struct Date* date, int isAllRecords)
{
    printf("Clinic Appointments for the Date: ");

    if (isAllRecords)
    {
        printf("<ALL>\n\n");
        printf("Date       Time  Pat.# Name            Phone#\n"
               "---------- ----- ----- --------------- --------------------\n");
    }
    else
    {
        printf("%04d-%02d-%02d\n\n", date->year, date->month, date->day);
        printf("Time  Pat.# Name            Phone#\n"
               "----- ----- --------------- --------------------\n");
    }
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display a single appointment record with patient info. in tabular format
void displayScheduleData(const struct Patient* patient,
                         const struct Appointment* appoint,
                         int includeDateField)
{
    if (includeDateField)
    {
        printf("%04d-%02d-%02d ", appoint->date.year, appoint->date.month,
               appoint->date.day);
    }
    printf("%02d:%02d %05d %-15s ", appoint->time.hour, appoint->time.min,
           patient->patientNumber, patient->name);

    displayFormattedPhone(patient->phone.number);

    printf(" (%s)\n", patient->phone.description);
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
            menuAppointment(data);
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


// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Appointment Management
void menuAppointment(struct ClinicData* data)
{
    int selection;

    do {
        printf("Appointment Management\n"
               "==============================\n"
               "1) VIEW   ALL Appointments\n"
               "2) VIEW   Appointments by DATE\n"
               "3) ADD    Appointment\n"
               "4) REMOVE Appointment\n"
               "------------------------------\n"
               "0) Previous menu\n"
               "------------------------------\n"
               "Selection: ");
        selection = inputIntRange(0, 4);
        putchar('\n');
        switch (selection)
        {
        case 1:
            viewAllAppointments(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 2:
            viewAppointmentSchedule(data);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 3:
            addAppointment(data->appointments, data->maxAppointments,
                           data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        case 4:
            removeAppointment(data->appointments, data->maxAppointments,
                              data->patients, data->maxPatient);  // ToDo: You will need to create this function!
            suspend();
            break;
        }
    } while (selection);
}


// ---------------------------------------------------------------------------
// !!! INSERT/COPY YOUR MS#2 FUNCTION DEFINITIONS BELOW... !!!
// Note: Maintain the same order/sequence as it is listed in the header file
//       Properly organize/categorize any new functions accordingly
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
    if (noRecordsFound == max)
        printf("*** No records found ***");
}

// Search for a patient record based on patient number or phone number
void searchPatientData(const struct Patient patient[], int max)
{
    int selection, flag = 1;
    do
    {
        printf("Search Options\n"
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
            searchPatientByPatientNumber(patient, max);
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
    } while (flag);
}

// Add a new patient record to the patient array
void addPatient(struct Patient patient[], int max)
{
    int emptyPos = -1, i;
    for (i = 0; i < max && emptyPos == -1; i++)
    {
        if (patient[i].patientNumber == 0)
        {
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
    char option[] = {'y', 'n', '\0'};
    printf("Enter the patient number: ");
    numberLookUp = inputInt();
    patientIndex = findPatientIndexByPatientNum(numberLookUp, patient, max);
    if (patientIndex == -1)
    {
        putchar('\n');
	printf("ERROR: Patient record not found!\n");
    }
    else
    {
        putchar('\n');
	displayPatientData(&patient[patientIndex], FMT_FORM);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
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

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
// Milestone #3 mandatory functions...
// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

// View ALL scheduled appointments
void viewAllAppointments(struct ClinicData *data)
{
    int i, posPatient;
    
    displayScheduleTableHeader(NULL, 1);
    selectionSort(data->appointments, data->maxAppointments);
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].date.year != 0)
        {
            posPatient = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
            displayScheduleData(&data->patients[posPatient], &data->appointments[i], 1);
        }
    }      
}

// View appointment schedule for the user input date
void viewAppointmentSchedule(struct ClinicData *data)
{
    struct Date searchDate = {0};
    int i, posPatient;

    printf("Year        : ");
    searchDate.year = inputIntPositive();

    printf("Month (%d-%d): ", MIN_MONTH, MAX_MONTH);
    searchDate.month = inputIntRange(MIN_MONTH, MAX_MONTH);

    int maxDay = maxDayByDate(data->appointments, data->maxAppointments, &searchDate);
    printf("Day (%d-%d)  : ", MIN_DAY, maxDay);
    searchDate.day = inputIntRange(MIN_DAY, maxDay);
    putchar('\n');

    displayScheduleTableHeader(&searchDate, 0);
    selectionSort(data->appointments, data->maxAppointments);
    for (i = 0; i < data->maxAppointments; i++)
    {
        if (data->appointments[i].date.year == searchDate.year &&
            data->appointments[i].date.month == searchDate.month &&
            data->appointments[i].date.day == searchDate.day)
        {
            posPatient = findPatientIndexByPatientNum(data->appointments[i].patientNumber, data->patients, data->maxPatient);
            displayScheduleData(&data->patients[posPatient], &data->appointments[i], 0);
        }
    }
}

// Add an appointment record to the appointment array
void addAppointment(struct Appointment* appointments, int maxAppointments,
                    struct Patient* patients, int maxPatient)
{
    int i, j, flag = 1, exists = 0;
    for (i = 0; i < maxAppointments && appointments[i].date.year!=0; i++);
    if (i+1 == maxAppointments)
    {
        printf("The appointment list is full.\n\n");
    }
    else
    {
        printf("Patient Number: ");
        appointments[i].patientNumber = inputIntPositive();

        do
        {
            flag = 1;
            printf("Year        : ");
            appointments[i].date.year = inputIntPositive();

            printf("Month (%d-%d): ", MIN_MONTH, MAX_MONTH);
            appointments[i].date.month = inputIntRange(MIN_MONTH, MAX_MONTH);

            int maxDay = maxDayByDate(appointments, maxAppointments, &appointments[i].date);
            printf("Day (%d-%d)  : ", MIN_DAY, maxDay);
            appointments[i].date.day = inputIntRange(MIN_DAY, maxDay);

            do
            {
                printf("Hour (%d-%d)  : ", MIN_HOUR, MAX_HOUR);
                appointments[i].time.hour = inputIntRange(MIN_HOUR, MAX_HOUR);

                printf("Minute (%d-%d): ", MIN_MIN, MAX_MIN);
                appointments[i].time.min = inputIntRange(MIN_MIN, MAX_MIN);

                if (appointments[i].time.hour<OPEN_HOUR_BOTTOM || 
                    appointments[i].time.hour>OPEN_HOUR_TOP ||
                   (appointments[i].time.hour==OPEN_HOUR_TOP && appointments[i].time.min > 0) ||
                    appointments[i].time.min%30 != 0)
                {
                    printf("ERROR: Time must be between %d:00 and %d:00 in 30 minute intervals.\n\n", OPEN_HOUR_BOTTOM, OPEN_HOUR_TOP);
                }
                else
                {
                    flag = 0; 
                }
                
            } while (flag);
            exists = 0;
            for (j = 0; j < maxAppointments && !exists; j++)
            {
                if (i != j &&
                    appointments[j].date.year == appointments[i].date.year &&
                    appointments[j].date.month == appointments[i].date.month &&
                    appointments[j].date.day == appointments[i].date.day &&
                    appointments[j].time.hour == appointments[i].time.hour &&
                    appointments[j].time.min == appointments[i].time.min)
                {
                    exists = 1;
                    printf("\nERROR: Appointment timeslot is not available!\n");
                }
            }

            putchar('\n');
        }while (exists);
        printf("*** Appointment scheduled! ***\n");
    }
}

// Remove an appointment record from the appointment array
void removeAppointment(struct Appointment *appointments, int maxAppointments,
                       struct Patient *patients, int maxPatient)
{
    int i, j, patientNumber, flag = 1, appExists = -1;
    char options[] = {'y','n'};
    struct Appointment defaultAppointment = {0};
    struct Date removedDate = {0};

    printf("Patient Number: ");
    patientNumber = inputIntPositive();
    for (i = 0; i < maxAppointments; i++)
    {
        if (appointments[i].patientNumber == patientNumber) flag = 0;
    }

    if (flag)
    {
        printf("ERROR: Patient record not found!\n");
    }
    else
    {
        do
        {
            appExists = 1;
            printf("Year        : ");
            removedDate.year = inputIntPositive();

            printf("Month (%d-%d): ", MIN_MONTH, MAX_MONTH);
            removedDate.month = inputIntRange(MIN_MONTH, MAX_MONTH);

            int maxDay = maxDayByDate(appointments, maxAppointments, &removedDate);
            printf("Day (%d-%d)  : ", MIN_DAY, maxDay);
            removedDate.day = inputIntRange(MIN_DAY, maxDay);

            for (j = 0; j < maxAppointments; j++)
            {
                if (appointments[j].date.year == removedDate.year &&
                    appointments[j].date.month == removedDate.month &&
                    appointments[j].date.day == removedDate.day &&
                    appointments[j].patientNumber == patientNumber)
                    {
                        appExists = 0;
                        putchar('\n');
                        displayPatientData(&patients[
                                            findPatientIndexByPatientNum(patientNumber, patients, maxPatient)
                                                    ], FMT_FORM);

                        printf("Are you sure you want to remove this appointment (y,n): ");
                        if (inputCharOption(options) == 'y')
                        {
                            putchar('\n');
                            appointments[j] = defaultAppointment;
                            printf("Appointment record has been removed!\n");
                        }
                        else
                        {
                            printf("The Appointment record was not removed!\n");
                        }
                    } 
            }
            if (appExists == 1)
            {
                printf("Appointment time does not exist\n");
            }
            
        } while(appExists == 1);
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
    char numberLookUp[PHONE_LEN + 1];
    printf("Search by phone number: ");
    inputCString(numberLookUp, PHONE_LEN, PHONE_LEN);
    putchar('\n');
    displayPatientTableHeader();
    for (i = 0; i < max; i++)
    {
        if (strcmp(patient[i].phone.number, numberLookUp) == 0)
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
        if (patient[i].patientNumber == patientNumber)
            return i;
    }
    return -1;
}

int compareAppointment(const struct Appointment *app1, const struct Appointment *app2)
{
    if (app1->date.year<app2->date.year)
    {
        return 1;
    }
    else if (app1->date.year>app2->date.year)
    {
        return 0;
    }
    else
    {
        if (app1->date.month<app2->date.month)
        {
            return 1;
        }
        else if (app1->date.month>app2->date.month)
        {
            return 0;
        }
        else
        {
            if (app1->date.month<app2->date.month)
            {
                return 1;
            }
            else if (app1->date.month>app2->date.month)
            {
                return 0;
            }
            else
            {
		if (app1->date.day<app2->date.day)
		{
		    return 1;
		}
		else if (app1->date.day>app2->date.day)
		{
		    return 0;
		}
		else
		{
                if (app1->time.hour<app2->time.hour)
                {
                    return 1;
                }
                else if (app1->time.hour>app2->time.hour)
                {
                    return 0;
                }
                else
                {
                    if (app1->time.min<app2->time.min)
                    {
                        return 1;
                    }
                    else
                    {
                        return 0;
                    }
                }
            }  
        }
    }
    }
    return 0;
}

void swap(struct Appointment *appointment1, struct Appointment *appointment2)
{
    struct Appointment temp = *appointment1;
    *appointment1 = *appointment2;
    *appointment2 = temp;
}

// Function to perform Selection Sort
void selectionSort(struct Appointment *appointments, int maxAppointments)
{
    int i, j, min_idx;

    // One by one move boundary of
    // unsorted sub-array
    for (i = 0; i < maxAppointments - 1; i++)
    {
        // Find the minimum element in
        // unsorted array
        min_idx = i;
        for (j = i + 1; j < maxAppointments; j++)
            if (compareAppointment(&appointments[j],&appointments[min_idx]))
            {
                min_idx = j;
            }

        // Swap the found minimum element
        // with the first element
        swap(&appointments[min_idx], &appointments[i]);
    }
}

int maxDayByDate(struct Appointment *appointments, int maxAppointments, struct Date *date)
{
    if (date->month == 1 || date->month == 3 ||
        date->month == 5 || date->month == 7 ||
        date->month == 8 || date->month == 10 ||
        date->month == 12)
    {
        return 31;
    }
    else if (date->month == 4 || date->month == 6 ||
             date->month == 9 || date->month == 11)
    {
        return 30;
    }
    else
    {
        if (date->year % 4 == 0)
            return 29;
        return 28;
    }
}

//////////////////////////////////////
// USER INPUT FUNCTIONS
//////////////////////////////////////

void inputPatient(struct Patient *patient)
{
    printf("Patient Data Input\n"
           "------------------\n");
    printf("Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
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
//////////////////////////////////////
// FILE FUNCTIONS
//////////////////////////////////////

// Import patient data from file into a Patient array (returns # of records read)
int importPatients(const char *datafile, struct Patient patients[], int max)
{
    FILE *patientsFile;
    int i=0, flag = 1;
    
    patientsFile = fopen(datafile, "r");
    if (patientsFile == NULL) {
        printf("no such file.");
        return 0;
    }

    while (i < max && fscanf(patientsFile, "%d|%[^|]|%[^|]|%[^\n]\n", &patients[i].patientNumber,
                             patients[i].name,
                             patients[i].phone.description,
                             patients[i].phone.number) != EOF)
    {
        flag = 0;
        /*
        printf("%d|%s|%s|%s\n", patients[i].patientNumber,
               patients[i].name,
               patients[i].phone.description,
               patients[i].phone.number);
        */
        i++;
    }
    fclose(patientsFile);

    if (flag)
    {
        return 0;
    }
    else
    {
        return i;
    }
}

// Import appointment data from file into an Appointment array (returns # of records read)
int importAppointments(const char *datafile, struct Appointment appoints[], int max)
{
    FILE *patientsFile;
    int i = 0, flag = 1;

    patientsFile = fopen(datafile, "r");
    if (patientsFile == NULL)
    {
        printf("no such file.");
        return 0;
    }

    while (i < max && fscanf(patientsFile, "%d,%d,%d,%d,%d,%d\n", &appoints[i].patientNumber,
                                                                  &appoints[i].date.year,
                                                                  &appoints[i].date.month,
                                                                  &appoints[i].date.day,
                                                                  &appoints[i].time.hour,
                                                                  &appoints[i].time.min) != EOF)
    {
        flag = 0;
        /*
        printf("%d,%d,%d,%d,%d,%d\n", appoints[i].patientNumber,
               appoints[i].date.year,
               appoints[i].date.month,
               appoints[i].date.day,
               appoints[i].time.hour,
               appoints[i].time.min);
        */
        i++;
    }
    fclose(patientsFile);

    if (flag)
    {
        return 0;
    }
    else
    {
        return i;
    }
}
