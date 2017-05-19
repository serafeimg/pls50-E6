//*************************************************************
//*** ΠΛΣ50 "Βασικές Εξειδικεύσεις σε Θεωρία και Λογισμικό" ***
//***                   Εργασία Ε02 - Θέμα 1                ***
//***                                                       ***
//***                   Ακ.έτος 2016-17                     ***
//***              Φοιτητής: Σεραφείμ Γκέκας                ***
//***                   AM: 123542                          ***
//*************************************************************

#include <stdio.h>  //Θα την χρειαστούμε για την fopen(), fclose(), f/printf(), f/scanf()
#include <stdlib.h> //Θα την χρειαστούμε για την exit()
#include <string.h> //Θα την χρειασοτύμε για την strcat(), strcpy(), strcmp()


/*Δήλωση της Struct*/
struct passenger{
    char passName[40];
    unsigned short phoneNumber[10];
    unsigned int seatNumber;
};


/*Δηλώνουμε τις global μεταβλητές που θα χρησιμοποιθούν σε περισσότερες από μια συναρτήσεις*/
char busName[8]; //Πίνακας 8 θέσεων για τους 7 χαρακτήρες και το '\0'
int seatCount = 0; //Ο αριθμός θέσεων από το αρχείο bus
struct passenger seats[53]; //Δημιουργούμε struct array


/*Fuction prototypes*/
void openFile();
void menu();
void freeSeats();
void bookSeat();
void bookSeatMenu();
void findBooking();
void findBookingByPhone();
void findBookingByName();
void cancelBooking();
void cancelBookingMenu();
void viewBookedSeats();
void saveOnExit();


/*Κύριο πρόγραμμα*/
int main(){

    int i=0, choice=0;  //ματαβλητή μετρητή i και choice για την επιλογή του μενού

    for (i=0 ; i<53; i++){    //Αρχικοποίηση του πίνακα θέσεων struct
    seats[i].seatNumber= i+1;
    seats[i].passName[0] = '\0';
    }

    openFile();
    for (;;){   //ατέρμων βρόχος που θα διακοπεί μόνο με την εντολή return στην επιλογή 0
        menu(); //εκτύπωση του μενού στην οθόνη
        scanf(" %d", &choice);  //ανάγνωση επιλογής χρήστη
        printf("\n");
        switch(choice){ //βρόχος switch για την επιλογή του μενού
            case 1: freeSeats(); break;
            case 2: bookSeatMenu(); break;
            case 3: findBooking(); break;
            case 4: cancelBookingMenu(); break;
            case 5: viewBookedSeats(); break;
            case 0: saveOnExit(); return 0;
            default: printf("Please give a valid menu number");
            }
        printf("\n\n"); //αφήνουμε καινά για αισθητικούς λόγους
    }
}


/*Συνάρτηση για την ανάγνωση αρχείου*/
void openFile(){
    FILE *bus; //Δήλωση δείκτη-μεταβλητή αρχείου
    char surename[40], name[40];
    int seatnum, i;
    double phonenum;

    bus = fopen ("./bus.txt", "r");/*Ανάγνωση (r) του αρχείου μας*/

    if (bus == NULL){   //Έλεγχος λάθους κατά την ανάγνωση (π.χ. ανύπαρκτο αρχείο)
        printf("Error: Couldn't read bus.txt file. Please make sure that the file is in the same directory with the program. Thank you.");
        exit(1);}

    fscanf(bus, "%s %d", busName, &seatCount);//Ανάγνωση από το αρχείο

    if ((seatCount-5)%4 != 0 || seatCount>53){  //Έλεγχος δεδομένων αρχείου, εάν ο αριθμός θέσεων συμβαδίζει με την επιτρεπτή κατανομή θέσεων
        printf("Error: There soudn't be a bus with %d seats. Please check the data in bus.txt file. Thank you.", seatCount);
        exit(1);}

    while( !feof(bus) ) //Εισαγωγή των δεδομένων του αρχείου στην struct
    {
        fscanf(bus,"%s %s %d %lf\n",surename,name,&seatnum,&phonenum);
        strcat(surename, " ");
        strcat(surename, name);
        strcpy(seats[seatnum-1].passName, surename);
        seats[seatnum-1].seatNumber = seatnum;
        for (i=9 ; i>=0 ; i--){
            seats[seatnum-1].phoneNumber[i] = (long long int)phonenum%10;
            phonenum/=10;
        }
    }

    fclose(bus); //Κλείσιμο αρχείου για απελευθέρωση μνήμης

    return;
}


/*Συνάρτηση για την προβολή του μενού στην οθόνη*/
void menu(){
    printf("Bus:%s Seats:%d\n", busName, seatCount);
    printf("\t**Menu**\n");
    printf("1. View all free seats\n");
    printf("2. Book seat\n");
    printf("3. Find booking\n");
    printf("4. Cancel Booking\n");
    printf("5. View all booked seats\n");
    printf("0. Save&Exit\n");
    return;
}


/*Συνάρτηση για την προβολή των ελεύθερων θέσεων*/
void freeSeats(){
    int i, counter=0; //Μεταβλητή μετρητή i για τον βρόχο επανάληψης και counter για τον μετρητή πλήθους ελεύθερων θέσεων

    printf("Free seat numbers: ");
    for (i=0; i<seatCount; i++){
        if (seats[i].passName[0]=='\0'){    //Με την συνθήκη αυτή εντοπίζουμε την ελεύθερη θέση
            printf("%d, ", i+1);
            counter++;}
    }
    printf("\b\b "); //Αυτό το κάνουμε για αισθητικούς λόγους για να μην υπάρχει το κόμμα στην τελευταία ελεύθερη θέση
    if (counter==0){
        printf("\b:\nThere isn't any seat booked yet.\n\n");}
    else printf("\nTotal number of free seats: %d\n\n", counter);
    return;
}


/*Συνάρτηση για κράτηση θέσης*/
void bookSeat(struct passenger *seat){
    int i=0;
    char name[40];
    double phonenum;

    if ((*seat).passName[0]=='\0'){ //Έλεγχος εάν η θέση που μας έδωσε ο χρήστης είναι κενή.
        printf("Please enter Passenger's full name:");
        scanf(" %[^\n]s", name); //Χρησιμοποιούμε το [^\n] για να αγνοήσουμε το καινό ανάμεσα σε επίθετο και όνομα
        strcpy((*seat).passName, name); //Αποθηκεύουμε το Ονοματεπώνυμο στον πίνακα μας με στοιχεία struct
        printf("Please enter Passenger's phone number:");
        scanf(" %lf", &phonenum);
        for (i=9 ; i>=0 ; i--){ //Με αντίστοιχο τρόπο όπως και στην ανάγνωση του αρχείου περνάμε την μεταβλητή double σε πίνακα  unsigned short
            (*seat).phoneNumber[i] = (long long int)phonenum%10;
            phonenum/=10;
        }
        printf("Seat number %d booked successfully!\n\n", (*seat).seatNumber);
    } else{
        printf("Seat number %d is already booked.\n\n", (*seat).seatNumber);    //μήνυμα σφάλματος εάν η θέση είναι ήδη κρατημένη
    }

    return;
}


/*Συνάρτηση προβολής του μενού για την κράτηση θέσης*/
void bookSeatMenu(){

    int seatToBook=0;
    printf("Please enter seat number to book: ");
    scanf(" %d", &seatToBook);    //επιλογή χρήστη της θέσης
    if (seatToBook>=1 && seatToBook<=seatCount) {   //Έλεγχος του αριθμού του χρήστη εάν είναι εντός ορίων και έλεγχος διαθεσιμότητας θέσης
        bookSeat(&seats[seatToBook -1]); //κλήση συνάρτησης με by reference
    } else printf("Seat number %d is not valid. Please choose a seatNumber from 1 to %d.", seatToBook, seatCount);

    return;
}


/*Συνάρτηση εύρεσης κρατημένης θέσης*/
void findBooking() {
    int choice;
    printf("1. Find by name\n");    //Εκύπτωση υπομενού
    printf("2. Find by phone number\n");
    scanf(" %d", &choice);

    if (choice == 1){   //Ανάλογα την επιλογή του χρήστη καλεί την αντίστοιχη συνάρτηση
        findBookingByName();
    } else if (choice == 2){
        findBookingByPhone();
    }
    else{
        printf("No valide choice.");  //Εκτύπωση σφάλματος σε περίπωση λάθος επιλογής
    }
    return;
}


/*Συνάρτηση αναζήτησης θέσης βάση τηλεφώνου*/
void findBookingByPhone(){
    int i, temp[10], counter, j;
    double cnum, cnum2;

    printf("Please enter passenger's phone number:");
    scanf(" %lf", &cnum);
    cnum2=cnum; //κρατάμε την τιμή για την εκτύπωση του τελικού μηνύματος

    for (i=9 ; i>=0 ; i--){
            temp[i]= (long long int)cnum%10;
            cnum/=10;
    }

    for (i=0 ; i<seatCount ; i++){
        counter = 0;
        for (j=0 ; j<10 ; j++){
            if (seats[i].phoneNumber[j] == temp[j]){
                    counter++;
            }
        }
        if (counter==10){
            printf("The seat %d is booked with the phone number %0.lf", i+1, cnum2);
            return;
        }
    }
    printf("The is not any seat number booked with the phone number %0.lf", cnum2);
    return;
}


/*Συνάρτηση αναζήτησης θέσης βάση Ονοματεπώνυμου*/
void findBookingByName(){

    char name[40];
    int i;

    printf("Please enter passenger's name:");
    scanf(" %[^\n]s", name);
    for (i=0 ; i<seatCount ; i++){
        if (strcmp(seats[i].passName, name) == 0){
            printf("The seat number %d is booked with the customer name %s\n\n", i+1, name);
            return;
        }
    }
    printf("There is not any seat booked with the name s%", name);
    return;
}


/*Συνάρτηση ακύρωσης κράτησης*/
void cancelBooking(struct passenger *seat){

    if((*seat).passName[0] == '\0'){
        printf("The seat number %d is not booked.", (*seat).seatNumber );
    } else {
        (*seat).passName[0] = '\0';
        printf("The seat number %d cancelled succesfully.", (*seat).seatNumber );
    }
    return;
}


/*Συνάρτηση προβολής μενού για την ακύρωση κράτησης*/
void cancelBookingMenu(){
    int seatToCancel=0;
    printf("Please enter seat number to cancel: ");
    scanf(" %d", &seatToCancel); //επιλογή χρήστη της θέσης
    if (seatToCancel>=1 && seatToCancel<=seatCount) {    //Έλεγχος του αριθμού του χρήστη εάν είναι εντός ορίων και έλεγχος διαθεσιμότητας θέσης
        cancelBooking(&seats[seatToCancel -1]);
    } else printf("Seat number %d is not valid. Please choose a seatNumber from 1 to %d.", seatToCancel, seatCount); //μήνυμα σφάλματος εάν μας δόσει μη έγκυρο αριθμό θέσης

    return;
}


/*Συνάρτηση προβολής κρατήσεων*/
void viewBookedSeats(){
    int i, j;

    for (i=0 ; i<seatCount ; i++ ){
        if (seats[i].passName[0] != '\0'){
            printf("%s ", seats[i].passName);
            for (j=0 ; j<10 ; j++){
                printf("%d", seats[i].phoneNumber[j]);
            }
            printf(", %d\n", seats[i].seatNumber);
        }
    }
    return;
}


/*Συνάρτηση αποθήκευσης αρχείου και τερματισμού του προγράμματος*/
void saveOnExit(){

    FILE *bus;  //Δήλωση δείκτη-μεταβλητή αρχείου
    int i, j;

    bus = fopen("./bus.txt", "w"); //Εγγραφή (w) στο αρχείο μας
    fprintf(bus, "%s %d\n", busName, seatCount);

    for (i=0 ; i<seatCount ; i++ ){
        if (seats[i].passName[0] != '\0'){
            fprintf(bus, "%s ", seats[i].passName);
            fprintf(bus, "%d ", seats[i].seatNumber);
            for (j=0 ; j<10 ; j++){
                fprintf(bus, "%d", seats[i].phoneNumber[j]);
            }
            fprintf(bus, "\n" ); //Αυτό το κάνουμε για να αλλάξει γραμμή στο τελευταίο ψηφίο του αριθμού τηλεφώνου
        }
    }
    fclose(bus);    //Κλείσιμο αρχείου για επελευθέρωση μνήμης

    printf ("Bus.txt saved successfully. Please check the program's directory. Thank you!\n\n");
    return;
}
