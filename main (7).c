// Berrak Yıldırım 2690964
// I used dummy node in this assignment
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 50

struct Node {
    char name[N];
    char surname[N];
    char birth[N];
    float height;
    int weight;
    char BMI[N];
    struct Node *next;
};

struct ListRecord {
    struct Node *head;
    struct Node *tail;
    int size;
};

typedef struct ListRecord *List;

// Functions
struct ListRecord*  InitialisePatients(char fileName[]);
void InsertNewPatient(List list);
void UpdateNutritionalStatus(List list);
void SearchPatient(List list, char name[]);
void InitialiseUnhealthyPatientList(List list, List unhealty);
void PrintPatients(List list);

// Additional Functions
void MakeEmpty(List list);
struct ListRecord* CreateList();
void InsertAlphabetically(List list, char name[], char surname[], char birth[], float height, int weight, char BMI[]);




int main(void)
{
    int choice = 0;
    char fileName[N];

    printf("\nEnter the name of the file:");
    scanf("%s", fileName); // patients.txt
    fflush(stdin);

    List list = InitialisePatients(fileName);
    List unhealthy = CreateList();

    while (choice != 6) {
        printf("\n\n----- MENU -----\n");
        printf("\n1. Add patient\n2. Show patients\n3. Search patient\n4. Create an unhealthy patient list \n5. Show unhealthy patients\n6. Exit");
        printf("\nEnter your option:");
        scanf("%d", &choice);

        while (choice>6 || choice<1) { // Not a valid choice
            printf("\nIt is not a valid option!\nEnter your option again:");
            scanf("%d", &choice);
        }

        if (choice==6) { // Exit
            return 0;
        }
        else if (choice == 1) { // Add patient
            InsertNewPatient(list);
            printf("\n\nThe patient has been added.");
        }
        else if (choice == 2) { // Show patients
            printf("\n\nPatients are as follows:\n");
            PrintPatients(list);
        }
        else if (choice == 3) { // Search patient
            char searchName[N];
            printf("\n\nEnter the name of the patient you want to search:");
            fflush(stdin);
            scanf("%s", searchName);
            printf("\nResults:");
            SearchPatient(list, searchName);
        }
        else if (choice == 4) { // Create a list for unhealthy patients
            InitialiseUnhealthyPatientList(list, unhealthy);
            printf("\nThe number of patients removed from the patient list and moved to the unhealthy patients list is 1.");
        }
        else if (choice == 5) { // Display unhealthy patients' list
            printf("\n\nResults:\n");
            PrintPatients(unhealthy);
        }
    }
    return 0;
}

struct ListRecord* CreateList() { // It creates a list with dummy node
    struct ListRecord *list;
    list = (struct ListRecord*) malloc(sizeof(struct ListRecord));

    if (list == NULL) {
        printf("\nOut of memory!");
    }
    else {
        MakeEmpty(list);
    }
    return list;
}

void MakeEmpty(struct ListRecord *list){
    list->head = (struct Node*) malloc(sizeof(struct Node));

    if (list->head == NULL)
        printf("\nOut of memory!");
    else {
        list->head->next = NULL;
        list->tail = list->head;
        list->size = 0;
    }
}

struct ListRecord* InitialisePatients(char fileName[]) { // It initialises patients to a linked list
    List list = CreateList();

    FILE *inFile;
    inFile = fopen(fileName, "r");

    if (inFile == NULL) {
        printf("\nError opening the file.");
        exit(-1);
    }

    printf("\nThe %s file has been loaded successfully.\n", fileName);
    rewind(inFile);

    int size = 0; // Size of the file is stored here

    while (!feof(inFile)) { // Read file until the end of it
        struct Node *patient = (struct Node *) malloc(sizeof(struct Node));
        fscanf(inFile, "%[^;];%[^;];%[^;];%f;%d;%[^\n]\n",
            // When i use "%s;%s;%s;%f;%d;%s\n" I am having issues with my fscanf
            // So i used %[^:] which means, take the string till the semicolon
            patient->name, patient->surname, patient->birth,
            &patient->height, &patient->weight, patient->BMI);

        // Insert them Alphabettically to the list
        InsertAlphabetically(list, patient->name, patient->surname, patient->birth, patient->height, patient->weight, patient->BMI);

        size++;
    }

    fclose(inFile);
    UpdateNutritionalStatus(list);
    return list;
}

void PrintPatients(List list) { // It prints the list
    struct Node *p;
    p = list->head->next;

    if (p == NULL) {
        printf("\nThe list is empty!");
    }

    while (p != NULL) { // While list is not empty print the list
        printf("--> %s;%s;%s;%.2f;%d;%s\n", p->name, p->surname, p->birth, p->height, p->weight, p->BMI);
        p = p->next;
    }
    printf("\n");
}

void UpdateNutritionalStatus(List list) { // It updates their BMI
    struct Node *tmp;
    tmp = list->head->next;

    float status; // Nutritional status

    while (tmp != NULL) {
        status = tmp->weight / pow(tmp->height, 2);

        if (status<18.5)
            strcpy(tmp->BMI, "Underweight");

        else if (status>18.5 && status<24.9)
            strcpy(tmp->BMI, "Normal Weight");

        else if (status>25.0 && status<29.9)
            strcpy(tmp->BMI, "Pre-Obesity");

        else if (status>30.0 && status<34.9)
            strcpy(tmp->BMI, "Obese Class 1");

        else if (status>35.0 && status<39.9)
            strcpy(tmp->BMI, "Obese Class 2");

        else if (status>=40.0)
            strcpy(tmp->BMI, "Obese Class 3");

        tmp = tmp->next;
    }
}


void InsertNewPatient(List list) { // It inserts a new patient to the list
    char name[N], surname[N], birth[N], BMI[N];
    float height;
    int weight;

    fflush(stdin);
    printf("\n\nEnter patient's first name:");
    fflush(stdin);
    scanf("%s", name);
    printf("\nEnter patient's last name:");
    fflush(stdin);
    scanf("%s", surname);
    printf("\nEnter patient's date of birth:");
    fflush(stdin);
    scanf("%s", birth);
    printf("\nEnter patient's height (m):");
    scanf("%f", &height);
    printf("\nEnter patient's weight (kg):");
    fflush(stdin);
    scanf("%d",&weight);

    InsertAlphabetically(list, name, surname, birth, height,weight, "NA"); // Insert new patient to the list alphabetically
    UpdateNutritionalStatus(list); // After inserting update its BMI
}

void InsertAlphabetically(List list, char name[], char surname[], char birth[], float height, int weight, char BMI[]) { // It inserts a given patient alphabetically
    struct Node *newNode = (struct Node*) malloc(sizeof(struct Node)); // Initilaztion of newNode
    strcpy(newNode->name, name);
    strcpy(newNode->surname, surname);
    strcpy(newNode->birth, birth);
    newNode->height = height;
    newNode->weight = weight;
    strcpy(newNode->BMI, BMI);
    newNode->next = NULL;

    struct Node *current = list->head;

    while (current->next != NULL && strcmp(current->next->name, name) < 0) { // While next node is not NULL and its name is alphabetically smaller than new node's name
        current = current->next; // Move to the next node
    }

    // When new node name is greater than current next name, insert new node
    newNode->next = current->next;
    current->next = newNode;
    list->size++;
}

void SearchPatient(List list, char name[]) { // It is a linear search function
    struct Node *tmp;
    tmp = list->head->next;

    int found = 0;
    while (tmp != NULL) {
        if (strcmp(name, tmp->name) == 0) {
            printf("\n%s;%s;%s;%.2f;%d;%s", tmp->name, tmp->surname, tmp->birth, tmp->height, tmp->weight, tmp->BMI);
            found++;
        }
        tmp = tmp->next;
    }
    if (found == 0) {
        printf("\nPatient not found!");
    }
}



void InitialiseUnhealthyPatientList(List list, List unhealty) { //It moves unhealty patients to a new linked list (first inserts then deletes the patient from the previous list)
    if (list->head == NULL || list->head->next == NULL) {
        printf("\nList is empty.");
        return;
    }

    struct Node *current;
    current = list->head->next;
    struct Node *previous;
    previous = list->head;

    while (current != NULL) {
        if (strcmp(current->BMI, "Obese Class 1") == 0 || strcmp(current->BMI, "Obese Class 2") == 0 || strcmp(current->BMI, "Obese Class 3") == 0) {
            // If they are in an obese class it inserts them in a new linked list alphabetically
            InsertAlphabetically(unhealty, current->name, current->surname, current->birth, current->height, current->weight, current->BMI);

            previous->next = current->next; // Removes patient

            if (current == list->tail) { // If tail removed from the list, new tail is the previous patient
                list->tail = previous;

                struct Node *temp = current;
                current = current->next;
                free(temp);
            }
            else { // Move to the next patient
                previous = current;
                current = current->next;
            }
        }

        // Move to the next patient
        else {
            current = current->next;
            previous = previous->next;
        }
    }
}