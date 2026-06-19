#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int patientID;
    char name[50];
    int age;
    char gender[10];
    char phone[15];
} Patient;

typedef struct
{
    int doctorID;
    char name[50];
    char specialization[50];
} Doctor;

typedef struct
{
    int appointmentID;
    int patientID;
    int doctorID;
    char date[20];
    char time[20];
} Appointment;

void addPatient();
void viewPatients();
void searchPatient();
void updatePatient();
void deletePatient();

void addDoctor();
void viewDoctors();

void bookAppointment();
void viewAppointments();

int main()
{
    int choice;

    do
    {
        printf("\n========================================");
        printf("\n MEDICAL APPOINTMENT MANAGEMENT SYSTEM");
        printf("\n========================================");

        printf("\n1. Add Patient");
        printf("\n2. View Patients");
        printf("\n3. Search Patient");
        printf("\n4. Update Patient");
        printf("\n5. Delete Patient");

        printf("\n6. Add Doctor");
        printf("\n7. View Doctors");

        printf("\n8. Book Appointment");
        printf("\n9. View Appointments");

        printf("\n10. Exit");

        printf("\n\nEnter Choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: updatePatient(); break;
            case 5: deletePatient(); break;
            case 6: addDoctor(); break;
            case 7: viewDoctors(); break;
            case 8: bookAppointment(); break;
            case 9: viewAppointments(); break;
            case 10: printf("\nGoodbye!\n"); break;
            default: printf("\nInvalid Choice!\n");
        }

    } while(choice != 10);

    return 0;
}

void addPatient()
{
    FILE *fp;
    Patient p;

    fp = fopen("patients.txt", "a");

    if(fp == NULL)
    {
        printf("\nError opening patients.txt!\n");
        return;
    }

    printf("\nPatient ID: ");
    scanf("%d", &p.patientID);

    printf("Name: ");
    scanf("%49s", p.name);

    printf("Age: ");
    scanf("%d", &p.age);

    printf("Gender: ");
    scanf("%9s", p.gender);

    printf("Phone: ");
    scanf("%14s", p.phone);

    fprintf(fp, "%d %s %d %s %s\n",
            p.patientID,
            p.name,
            p.age,
            p.gender,
            p.phone);

    fclose(fp);

    printf("\nPatient Added Successfully!\n");
}

void viewPatients()
{
    FILE *fp = fopen("patients.txt","r");
    Patient p;

    if(fp == NULL)
    {
        printf("\nNo patient records found.\n");
        return;
    }

    printf("\n===PATIENTS ====\n");

    while(fscanf(fp,"%d %s %d %s %s",
                 &p.patientID,
                 p.name,
                 &p.age,
                 p.gender,
                 p.phone) != EOF)
    {
        printf("\nID: %d",p.patientID);
        printf("\nName: %s",p.name);
        printf("\nAge: %d",p.age);
        printf("\nGender: %s",p.gender);
        printf("\nPhone: %s",p.phone);
        printf("\n-----------------------------");
    }

    fclose(fp);
}

void searchPatient()
{
    FILE *fp = fopen("patients.txt","r");

    Patient p;
    int id;
    int found = 0;

    if(fp == NULL)
    {
        printf("\nNo records found.\n");
        return;
    }

    printf("\nEnter Patient ID: ");
    scanf("%d",&id);

    while(fscanf(fp,"%d %s %d %s %s",
                 &p.patientID,
                 p.name,
                 &p.age,
                 p.gender,
                 p.phone) != EOF)
    {
        if(p.patientID == id)
        {
            found = 1;

            printf("\nPatient Found");
            printf("\nID: %d",p.patientID);
            printf("\nName: %s",p.name);
            printf("\nAge: %d",p.age);
            printf("\nGender: %s",p.gender);
            printf("\nPhone: %s\n",p.phone);
        }
    }

    if(!found)
        printf("\nPatient Not Found\n");

    fclose(fp);
}

void updatePatient()
{
    FILE *fp;
    FILE *temp;

    Patient p;
    int id;
    int found = 0;

    fp = fopen("patients.txt","r");

    if(fp == NULL)
    {
        printf("\nNo records found.\n");
        return;
    }

    temp = fopen("temp.txt","w");

    printf("\nEnter Patient ID to Update: ");
    scanf("%d",&id);

    while(fscanf(fp,"%d %s %d %s %s",
                 &p.patientID,
                 p.name,
                 &p.age,
                 p.gender,
                 p.phone) != EOF)
    {
        if(p.patientID == id)
        {
            found = 1;

            printf("New Name: ");
            scanf("%s",p.name);

            printf("New Age: ");
            scanf("%d",&p.age);

            printf("New Gender: ");
            scanf("%s",p.gender);

            printf("New Phone: ");
            scanf("%s",p.phone);
        }

        fprintf(temp,"%d %s %d %s %s\n",
                p.patientID,
                p.name,
                p.age,
                p.gender,
                p.phone);
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt","patients.txt");

    if(found)
        printf("\nPatient Updated Successfully!\n");
    else
        printf("\nPatient Not Found!\n");
}

void deletePatient()
{
    FILE *fp;
    FILE *temp;

    Patient p;
    int id;
    int found = 0;

    fp = fopen("patients.txt","r");

    if(fp == NULL)
    {
        printf("\nNo records found.\n");
        return;
    }

    temp = fopen("temp.txt","w");

    printf("\nEnter Patient ID to Delete: ");
    scanf("%d",&id);

    while(fscanf(fp,"%d %s %d %s %s",
                 &p.patientID,
                 p.name,
                 &p.age,
                 p.gender,
                 p.phone) != EOF)
    {
        if(p.patientID == id)
        {
            found = 1;
            continue;
        }

        fprintf(temp,"%d %s %d %s %s\n",
                p.patientID,
                p.name,
                p.age,
                p.gender,
                p.phone);
    }

    fclose(fp);
    fclose(temp);

    remove("patients.txt");
    rename("temp.txt","patients.txt");

    if(found)
        printf("\nPatient Deleted Successfully!\n");
    else
        printf("\nPatient Not Found!\n");
}

void addDoctor()
{
    FILE *fp;
    Doctor d, temp;
    int duplicate = 0;

    printf("\nDoctor ID: ");
    scanf("%d",&d.doctorID);

    fp = fopen("doctors.txt","r");

    if(fp != NULL)
    {
        while(fscanf(fp,"%d %s %s",
                     &temp.doctorID,
                     temp.name,
                     temp.specialization) != EOF)
        {
            if(temp.doctorID == d.doctorID)
            {
                duplicate = 1;
                break;
            }
        }

        fclose(fp);
    }

    if(duplicate)
    {
        printf("\nDoctor ID already exists!\n");
        return;
    }

    printf("Doctor Name: ");
    scanf("%s",d.name);

    printf("Specialization: ");
    scanf("%s",d.specialization);

    fp = fopen("doctors.txt","a");

    fprintf(fp,"%d %s %s\n",
            d.doctorID,
            d.name,
            d.specialization);

    fclose(fp);

    printf("\nDoctor Added Successfully!\n");
}

void viewDoctors()
{
    FILE *fp = fopen("doctors.txt","r");

    Doctor d;

    if(fp == NULL)
    {
        printf("\nNo doctor records found.\n");
        return;
    }

    printf("\n========== DOCTORS ==========\n");

    while(fscanf(fp,"%d %s %s",
                 &d.doctorID,
                 d.name,
                 d.specialization) != EOF)
    {
        printf("\nDoctor ID: %d",d.doctorID);
        printf("\nName: %s",d.name);
        printf("\nSpecialization: %s",d.specialization);
        printf("\n-----------------------------");
    }

    fclose(fp);
}

void bookAppointment()
{
    FILE *fp = fopen("appointments.txt","a");

    Appointment a;

    printf("\nAppointment ID: ");
    scanf("%d",&a.appointmentID);

    printf("Patient ID: ");
    scanf("%d",&a.patientID);

    printf("Doctor ID: ");
    scanf("%d",&a.doctorID);

    printf("Date (DD/MM/YYYY): ");
    scanf("%s",a.date);

    printf("Time: ");
    scanf("%s",a.time);

    fprintf(fp,"%d %d %d %s %s\n",
            a.appointmentID,
            a.patientID,
            a.doctorID,
            a.date,
            a.time);

    fclose(fp);

    printf("\nAppointment Booked Successfully!\n");
}

void viewAppointments()
{
    FILE *fp = fopen("appointments.txt","r");

    Appointment a;

    if(fp == NULL)
    {
        printf("\nNo appointments found.\n");
        return;
    }

    printf("\n======= APPOINTMENTS =======\n");

    while(fscanf(fp,"%d %d %d %s %s",
                 &a.appointmentID,
                 &a.patientID,
                 &a.doctorID,
                 a.date,
                 a.time) != EOF)
    {
        printf("\nAppointment ID: %d",a.appointmentID);
        printf("\nPatient ID: %d",a.patientID);
        printf("\nDoctor ID: %d",a.doctorID);
        printf("\nDate: %s",a.date);
        printf("\nTime: %s",a.time);
        printf("\n-----------------------------");
    }

    fclose(fp);
}
