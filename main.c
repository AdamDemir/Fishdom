#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define structures for date, fish data, species data list, and species list
typedef struct Date Date;
typedef struct FishData FishData;
typedef struct Species Species;
typedef struct FishList FishList;
typedef struct SpeciesDataList SpeciesDataList;
#define MAX_Characters 80

// Structure to represent a date
struct Date {
    int day;
    int month;
    int year;
};
// Structure to represent details of a fish
struct FishData {
    char cityName[MAX_Characters];
    char speciesName[MAX_Characters];
    int weight;
    float vertical_length;
    float diagonal_length;
    float cross_length;
    float height;
    float fish_length;
    Date date;
    FishData *next;
};
// Structure to represent a list of fish data for a specific species
struct SpeciesDataList {
    FishData *head;
    FishData *tail;
    int size;
};
// Structure to represent a species
struct Species {
    char speciesName[MAX_Characters];
    SpeciesDataList *dataLink;
    Species *next;
};
// Structure to represent the main list of species
struct FishList {
    Species *head;
    Species *tail;
    int size;
};

// -------------------Main Functions-----------------
FishList *initializeFishing(char *FileName);

void addFishData(FishList *l);

void deleteFish(FishList *l, int threshold);

void printStatistic(FishList *l);

void SearchFishData(FishList *l);

void AddSpeciesList(FishList *l);

void saveUpdateList(FishList *l);


//----------------Helper Functions-------------------
void MakeEmptyFishList(FishList *l);

void MakeEmptySpeciesDataList(SpeciesDataList *s);

int PosForSpeciesGiven(FishList *l, char *SpeciesName);

Species *CreateNewSpecies(char *SpeciesName);

SpeciesDataList *createDataList();

int isSpeciesExist(FishList *l, char speciesName[MAX_Characters]);

// create an empty list
FishList *createList() {
    FishList *l;
    l = (FishList *) malloc(sizeof(FishList));
    if (l == NULL) {
        printf("Out of memory!\n");
        exit(1);
    } else {
        MakeEmptyFishList(l); // initialize the list
    }
    return l;
}

void MakeEmptyFishList(FishList *l) {
    l->head = (Species *) malloc(sizeof(Species));
    if (l->head == NULL) {
        printf("Out of memory!\n");
    } else {
        l->head->next = NULL;
        l->tail = l->head;
        l->size = 0;
    }
}
//initialize an Empty List
void MakeEmptySpeciesDataList(SpeciesDataList *s) {
    s->head = (FishData *) malloc(sizeof(FishData));
    if (s->head == NULL) {
        printf("Out of memory!\n");
    } else {
        s->head->next = NULL;
        s->tail = s->head;
        s->size = 0;
    }
}
// create the data list
SpeciesDataList *createDataList() {
    SpeciesDataList *s = (SpeciesDataList *) malloc(sizeof(SpeciesDataList));
    if (s == NULL) {
        printf("Out of memory!\n");
        exit(1);
    } else {
        MakeEmptySpeciesDataList(s);
    }
    return s;
}

// allocate a new species variable and return it
Species *CreateNewSpecies(char *SpeciesName) {
    Species *s = (Species *) malloc(sizeof(Species));
    if (s == NULL) {
        printf("Out of memory!\n");
    } else {
        strcpy(s->speciesName, SpeciesName);
        s->dataLink = createDataList();
        s->next = NULL;
    }
    return s;
}

// link the data of the fishes with the species
void
LinkFishData(Species *s, char *speciesName, char *cityName, int weight, float vertical_length, float diagonal_length,
             float cross_length, float height, float fish_length, int day, int month, int year) {

    FishData *tmp = s->dataLink->head;
    if (tmp->next == NULL) {
        tmp->next = (FishData *) malloc(sizeof(FishData));
        tmp = tmp->next;
        strcpy(tmp->speciesName, speciesName);
        strcpy(tmp->cityName, cityName);
        tmp->weight = weight;
        tmp->vertical_length = vertical_length;
        tmp->diagonal_length = diagonal_length;
        tmp->cross_length = cross_length;
        tmp->height = height;
        tmp->fish_length = fish_length;
        tmp->date.day = day;
        tmp->date.month = month;
        tmp->date.year = year;
        tmp->next = NULL;
        s->dataLink->size++;
    } else {
        while (tmp->next != NULL) {
            tmp = tmp->next;
        }
        tmp->next = (FishData *) malloc(sizeof(FishData));

        if (tmp->next == NULL) {
            printf("Out of memory!\n");
            exit(1);
        }

        tmp = tmp->next;
        strcpy(tmp->speciesName, speciesName);
        strcpy(tmp->cityName, cityName);
        tmp->weight = weight;
        tmp->vertical_length = vertical_length;
        tmp->diagonal_length = diagonal_length;
        tmp->cross_length = cross_length;
        tmp->height = height;
        tmp->fish_length = fish_length;
        tmp->date.day = day;
        tmp->date.month = month;
        tmp->date.year = year;
        s->dataLink->tail = tmp;
        tmp->next = NULL;
        s->dataLink->size++;
    }

}
//check whether species exist
int isSpeciesExist(FishList *l, char speciesName[MAX_Characters]) {
    int isExist = 0;
    Species *SpeciesTmp = l->head->next;
    while (!isExist && SpeciesTmp != NULL) {
        if (strcmp(speciesName, SpeciesTmp->speciesName) == 0)
            isExist = 1;
        SpeciesTmp = SpeciesTmp->next;
    }
    return isExist;
}
//  return the pos of species given its name
int PosForSpeciesGiven(FishList *l, char *SpeciesName) {
    int pos = 0;
    int found = 0;
    Species *tmp = l->head->next;
    while (tmp != NULL && strcmp(tmp->speciesName, SpeciesName) != 0) {
        tmp = tmp->next;
        pos++;
    }
    if (tmp == NULL) {
        printf("Didn't find the pos for the element given! Logic Problem\n\n\n");
        exit(1);
    } else
        return pos + 1;

}

int main() {
    printf("Hello, World!\n");
    char FileName[MAX_Characters] = "fishingArchive.txt";
    int option = 0;
    FishList *l = initializeFishing(FileName);
    do {
        printf("-----MENU----------------------------------------\n"
               "1. Add Fish Data\n"
               "2. Delete Fish Data\n"
               "3. Print Fish Statistics\n"
               "4. Search Fish Data\n"
               "5. Add Species List\n"
               "6. Exit\n\n"
               "Enter your option:");
        scanf("%d", &option);

        switch (option) {
            case 1:
                addFishData(l);
                break;
            case 2: {
                int threshold = 0;
                printf("Enter a threshold:");
                scanf("%d", &threshold);
                deleteFish(l, threshold);
            }
                break;
            case 3:
                printStatistic(l);
                break;
            case 4:
                SearchFishData(l);
                break;
            case 5:
                AddSpeciesList(l);
                break;
            case 6:
                saveUpdateList(l);
                break;
            default:
                printf("Enter a valid value please!");
        }
    } while (option != 6);
    return 0;
}
// add fish data after FishInitializing
void addFishData(FishList *l) {
    char speciesName[MAX_Characters];
    char cityName[MAX_Characters];
    int weight = 0;
    float vertical_length = 0;
    float diagonal_length = 0;
    float cross_length = 0;
    float height = 0;
    float fish_length = 0;
    int day;
    int month;
    int year;

    printf("Species:");
    scanf("%s", speciesName);

    printf("Weight of the fish in grams:");
    scanf("%d", &weight);

    printf("Vertical length in CM:");
    scanf("%f", &vertical_length);

    printf("Diagonal length in CM:");
    scanf("%f", &diagonal_length);

    printf("Cross length in CM:");
    scanf("%f", &cross_length);

    printf("Height in CM:");
    scanf("%f", &height);

    printf("Fish Length in CM:");
    scanf("%f", &fish_length);

    printf("Fishing date:");
    scanf("%d/%d/%d", &day, &month, &year);

    printf("City:");
    scanf("%s", cityName);

    if (!isSpeciesExist(l, speciesName)) {
        Species *SpeciesTmp = CreateNewSpecies(speciesName);
        strcpy(SpeciesTmp->speciesName, speciesName);
        LinkFishData(SpeciesTmp, speciesName, cityName, weight, vertical_length, diagonal_length,
                     cross_length,
                     height, fish_length, day, month, year);
        l->tail->next = SpeciesTmp;
        l->tail = SpeciesTmp;
        l->size++;
    } else {
        Species *tmp = l->head; // I changed from  l->head
        for (int i = 0; i < PosForSpeciesGiven(l, speciesName); ++i) {
            tmp = tmp->next;
        }

        LinkFishData(tmp, speciesName, cityName, weight, vertical_length, diagonal_length,
                     cross_length,
                     height, fish_length, day, month, year);

    }
    printf("The data has been added, successfully!\n");
}
//Add new species
void AddSpeciesList(FishList *l) {
    char speciesName[MAX_Characters];
    char cityName[MAX_Characters];
    int weight = 0;
    float vertical_length = 0;
    float diagonal_length = 0;
    float cross_length = 0;
    float height = 0;
    float fish_length = 0;
    int day;
    int month;
    int year;
    char ch = 'Y';
    while (ch != 'N') {

        do {
            printf("The new species is: ");
            scanf("%s", speciesName);

            if (isSpeciesExist(l, speciesName))
                printf("The species already exist! add a new species please!\n");
        } while (isSpeciesExist(l, speciesName));

        Species *SpeciesTmp = CreateNewSpecies(speciesName);
        if (SpeciesTmp == NULL) {
            printf("Out of memory");
            exit(1);
        }
        printf("Weight of the fish in grams:");
        scanf("%d", &weight);

        printf("Vertical length in CM:");
        scanf("%f", &vertical_length);

        printf("Diagonal length in CM:");
        scanf("%f", &diagonal_length);

        printf("Cross length in CM:");
        scanf("%f", &cross_length);

        printf("Height in CM:");
        scanf("%f", &height);

        printf("Fish Length in CM:");
        scanf("%f", &fish_length);

        printf("Fishing date:");
        scanf("%d/%d/%d", &day, &month, &year);

        printf("City:");
        scanf("%s", cityName);
        strcpy(SpeciesTmp->speciesName, speciesName);
        LinkFishData(SpeciesTmp, speciesName, cityName, weight, vertical_length, diagonal_length,
                     cross_length,
                     height, fish_length, day, month, year);
        l->tail->next = SpeciesTmp;
        l->tail = SpeciesTmp;
        l->size++;

        printf("Do you want to add more fish (Y/N): ");
        scanf("%c", &ch);
    }
}
// load the data into a structure and continue on
FishList *initializeFishing(char *FileName) {
    FILE *inFile;
    FishList *l;
    inFile = fopen(FileName, "r");
    if (inFile == NULL) {
        printf("Error while opening the file");
        exit(1);
    } else {
        l = createList();

        char speciesName[MAX_Characters];
        char cityName[MAX_Characters];
        int weight = 0;
        float vertical_length = 0;
        float diagonal_length = 0;
        float cross_length = 0;
        float height = 0;
        float fish_length = 0;
        int day;
        int month;
        int year;


        while (fscanf(inFile, "%79[^;];%d;%f;%f;%f;%f;%f;%d/%d/%d;%s\n", speciesName, &weight,
                      &vertical_length, &diagonal_length, &cross_length, &height, &fish_length, &day, &month, &year,
                      &cityName) != EOF) {


            if (l->size == 0) {
                Species *SpeciesTmp = CreateNewSpecies(speciesName);
                if (SpeciesTmp == NULL) {
                    printf("Out of memory");
                    exit(1);
                }
                strcpy(SpeciesTmp->speciesName, speciesName);
                LinkFishData(SpeciesTmp, speciesName, cityName, weight, vertical_length, diagonal_length,
                             cross_length,
                             height, fish_length, day, month, year);
                l->head->next = SpeciesTmp;
                l->tail = l->head->next;
                l->size++;

            } else if (!isSpeciesExist(l, speciesName)) {
                Species *SpeciesTmp = CreateNewSpecies(speciesName);
                if (SpeciesTmp == NULL) {
                    printf("Out of memory");
                    exit(1);
                }
                strcpy(SpeciesTmp->speciesName, speciesName);
                LinkFishData(SpeciesTmp, speciesName, cityName, weight, vertical_length, diagonal_length,
                             cross_length,
                             height, fish_length, day, month, year);
                l->tail->next = SpeciesTmp;
                l->tail = SpeciesTmp;
                l->size++;
            } else {
                Species *tmp = l->head;
                for (int i = 0; i < PosForSpeciesGiven(l, speciesName); ++i) {
                    tmp = tmp->next;
                }

                LinkFishData(tmp, speciesName, cityName, weight, vertical_length, diagonal_length,
                             cross_length,
                             height, fish_length, day, month, year);

            }

        }

        printf("\nThe fishingArchive.txt file has been loaded successfully!\n\n");

    }
    return l;
}
// print the num of fishes with given Species name
void printStatistic(FishList *l) {
    int fishNum = 0;
    char SpeciesName[80];
    do {
        printf("Provide the species:");
        scanf("%s", SpeciesName);

        if (!isSpeciesExist(l, SpeciesName)) {
            printf("The Species doesn't exist, try again!\n");
        }

    } while (!isSpeciesExist(l, SpeciesName));
    Species *tmp = l->head->next;
    while (tmp != NULL) {
        FishData *DataTmp = tmp->dataLink->head->next;
        while (DataTmp != NULL) {
            if (!strcmp(DataTmp->speciesName, SpeciesName)) {
                fishNum++;
            }
            DataTmp = DataTmp->next;
        }
        tmp = tmp->next;
    }
    printf("The number of available fish data is %d\n", fishNum);
}
// Delete a fish given a threshold
void deleteFish(FishList *l, int threshold) {
    Species *tmp = l->head->next;
    int deletedFish = 0;
    while (tmp != NULL) {
        FishData *DataTmp = tmp->dataLink->head;
        while (DataTmp->next != NULL) {
            if (DataTmp->next->weight <= threshold) {
                FishData *deleteTmp = DataTmp->next;
                DataTmp->next = deleteTmp->next;
                free(deleteTmp);
                tmp->dataLink->size--;
                deletedFish++;
            } else {
                DataTmp = DataTmp->next;
            }
        }
        tmp = tmp->next;
    }
    printf("\n%d fish data was deleted from your list!\n\n", deletedFish);
}
// search for fish with either month or city name as a filter
void SearchFishData(FishList *l) {
    char ch = 'C';
    int month = 0;
    char cityName[MAX_Characters];
    do {
        printf("Enter your search option (C for city/M for month): ");
        scanf("%c", &ch);
        if (ch != 'C' && ch != 'M')
            printf("Wrong Character, Enter again!\n");
    } while (ch != 'C' && ch != 'M');
    if (ch == 'M') {

        do {
            printf("Enter the month number:");
            scanf("%d", &month);
            if (month <= 0 || month > 12)
                printf("You entered the wrong number! Enter again!\n");
        } while (month <= 0 || month > 12);

    } else {

        printf("Enter the city name:");
        scanf("%s", cityName);


    }

    Species *tmp = l->head->next;
    int found = 0;
    while (tmp != NULL) {
        FishData *DataTmp = tmp->dataLink->head->next;
        while (DataTmp != NULL) {
            if (ch == 'M') {
                if (DataTmp->date.month == month) {
                    printf("\n%-10s %-5d %-5.2f %-5.2f %-5.2f %-5.2f %-5.2f %d/%d/%d %-10s\n", DataTmp->speciesName,
                           DataTmp->weight,
                           DataTmp->vertical_length, DataTmp->diagonal_length, DataTmp->cross_length, DataTmp->height,
                           DataTmp->fish_length, DataTmp->date.day, DataTmp->date.month, DataTmp->date.year,
                           DataTmp->cityName);
                    found++;
                }
            } else {
                if (!strcmp(DataTmp->cityName, cityName)) {
                    printf("\n%-10s %-5d %-5.2f %-5.2f %-5.2f %-5.2f %-5.2f %d/%d/%d %-10s\n", DataTmp->speciesName,
                           DataTmp->weight,
                           DataTmp->vertical_length, DataTmp->diagonal_length, DataTmp->cross_length, DataTmp->height,
                           DataTmp->fish_length, DataTmp->date.day, DataTmp->date.month, DataTmp->date.year,
                           DataTmp->cityName);
                    found++;
                }
            }
            DataTmp = DataTmp->next;
        }


        tmp = tmp->next;
    }
    if (!found)
        printf("\nNo fish satisfying the condition given was found\n");

}
// Overwrite the existing file
void saveUpdateList(FishList *l) {
    char FileName[MAX_Characters] = "fishingArchive.txt";
    FILE *outFile;
    outFile = fopen(FileName, "w");
    if (outFile == NULL) {
        printf("Error while opening the file");
        exit(1);
    } else {
        Species *tmp = l->head->next;
        while (tmp != NULL) {
            FishData *DataTmp = tmp->dataLink->head->next;
            while (DataTmp != NULL) {
                fprintf(outFile, "%-10s %-5d %-5.2f %-5.2f %-5.2f %-5.2f %-5.2f %d/%d/%d %-10s\n", DataTmp->speciesName,
                        DataTmp->weight,
                        DataTmp->vertical_length, DataTmp->diagonal_length, DataTmp->cross_length, DataTmp->height,
                        DataTmp->fish_length, DataTmp->date.day, DataTmp->date.month, DataTmp->date.year,
                        DataTmp->cityName);
                DataTmp = DataTmp->next;
            }
            tmp = tmp->next;
        }
    }
    printf("The FishingArchive.txt file has been updated successfully!!");
}

