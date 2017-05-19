//*************************************************************
//*** ΠΛΣ50 "Βασικές Εξειδικεύσεις σε Θεωρία και Λογισμικό" ***
//***                   Εργασία Ε01 - Θέμα 4                ***
//***                                                       ***
//***                   Ακ.έτος 2016-17                     ***
//***              Φοιτητής: Σεραφείμ Γκέκας                ***
//***                   AM: 123542                          ***
//*************************************************************

#include <stdio.h>  /*Θα την χρειαστούμε για την fopen(), fclose(), f/printf(), f/scanf(), switch() */
#include <stdlib.h> /*Θα την χρειαστούμε για την exit()*/

/*Δηλώνουμε τις global μεταβλητές που θα χρησιμοποιθούν σε περισσότερες από μια συναρτήσεις*/
char busname[8] = {' '}; /*Πίνακας 8 θέσεων για τους 7 χαρακτήρες και το '\0'. Αρχικοποιύμε τον πίνακα χαρακτήρα με καινούς χαρακτήρες*/
int seats[53] = {0};/*Πίνακας 53 θέσεων για τις 53 θέσεις του λεωφορείου. Αρχικοποιούμε όλες τις τιμές με το 0*/
int seatcount = 0; /*Ο αριθμός θέσεων από το αρχείο bus*/

/*Συνάρτηση για την ανάγνωση αρχείου*/
void openFile(){
    FILE *bus; /*Δήλωση δείκτη-μεταβλητή αρχείου*/

    bus = fopen ("./bus.txt", "r");/*Ανάγνωση (r) του αρχείου μας*/

    /*Έλεγχος λάθους κατά την ανάγνωση (π.χ. ανύπαρκτο αρχείο)*/
    if (bus == NULL){
        printf("Error: Couldn't read bus.txt file. Please make sure that the file is in the same directory with the program. Thank you.");
        exit(-1);}

    fscanf(bus, "%7c %i", busname, &seatcount);/*Ανάγνωση από το αρχείο*/

    /*Έλεγχος δεδομένων αρχείου, εάν ο αριθμός θέσεων συμβαδίζει με την επιτρεπτή κατανομή θέσεων*/
    if ((seatcount-5)%4 != 0 || seatcount>53){
        printf("Error: There soudn't be a bus with %d seats. Please check the data in bus.txt file. Thank you.", seatcount);
        exit(-2);}

    fclose(bus); /*Κλείσιμο αρχείου για απελευθέρωση μνήμης*/
    return;
}

/*Συνάρτηση για την προβολή του μενού στην οθόνη*/
void menu(){
    printf("\t**Menu**\n");
    printf("1. View all free seats\n");
    printf("2. Book seat\n");
    printf("3. Book window seat\n");
    printf("4. Cancel Booking\n");
    printf("5. Find Booking\n");
    printf("6. View all booked seats\n");
    printf("7. Print layout\n");
    printf("8. Save layout\n");
    printf("0. Exit\n");
    return;
}

/*Συνάρτηση για την προβολή των ελεύθερων θέσεων*/
void freeSeats(){
    int i, counter=0; /*Μεταβλητή i για τον βρόχο επανάληψης και counter για τον μετρητή ελεύθερων θέσεων*/

    printf("Free seat numbers: ");
    for (i=0; i<seatcount; i++){
        if (seats[i]==0){
            printf("%d, ", i+1);
            counter++;}
    }
    printf("\b\b "); /*Αυτό το κάνουμε για αισθητικούς λόγους για να μην υπάρχει το κόμμα στην τελευταία ελεύθερη θέση*/
    if (counter==0){
        printf("\b:\nThere isn't any seat booked yet.");}
    else printf("\nTotal number of free seats: %d", counter);
    return;
}

/*Συνάρτηση για κράτηση θέσης*/
void bookSeat(){
    int seatToBook=0;

    printf("Please enter seat number to book:");
    scanf ("%d", &seatToBook);

    /*Έλεγχος του αριθμού του χρήστη εάν είναι εντός ορίων και έλεγχος διαθεσιμότητας θέσης*/
    if (seatToBook>=1 && seatToBook<=seatcount){
        if (seats[seatToBook-1]==0){
            seats[seatToBook-1]= 1;
            printf("Seat number %d booked successfully!", seatToBook);}
        else printf("Seat number %d is already booked.", seatToBook);}
    else printf("Seat number %d is not valid. Please choose a seatnumber from 1 to %d.", seatToBook, seatcount);
    return;
}

/*Συνάρτηση κράτησης θέσης παραθύρου*/
void bookWindowSeat(){
    int i;

    /*Έλεγχος κεντρικής καμπίνας λεωφορείου*/
    for (i=0; i<(seatcount-2);){
        if (seats[i]!=1){
            seats[i]=1;
            printf("Window seat %d booked successfully!", i+1);
            return;}
        if ((i+1)%4==0){ /*αλγόριθμος για τις θέσης που είναι σε παράθυρο*/
            i++;}
        else i+=3;}

    /*Έλεγχος γαλαρίας*/
    if (seats[seatcount - 1] == 0){
        seats[seatcount - 1] = 1;
        printf("Window seat %d booked successfully!", seatcount);
        return;}

    printf("Unfortunately, no window seats left.");
    return;
}

/*Συνάρτηση ακύρωσης κράτησης*/
void cancelBooking(){
    int seatToCancel=0;
    printf("Please enter seat number to cancel booking:");
    scanf("%d", &seatToCancel);

    /*Έλεγχος του αριθμού του χρήστη εάν είναι εντός ορίων και έλεγχος διαθεσιμότητας θέσης*/
    if (seatToCancel>=1 && seatToCancel<=seatcount){
        if (seats[seatToCancel-1]==1){
            seats[seatToCancel-1]=0;
            printf("Seat number %d cancelled successfully!", seatToCancel);}
        else printf("Seat number %d is already free.", seatToCancel);}
    else printf("Seat number %d is not valid. Please choose a seat number from 1 to %d.", seatToCancel, seatcount);
    return;
}

/*Συνάρτηση ελέγχου κράτησης*/
void checkBooking(){
    int checkSeat=0;
    printf("Please enter seat number to check booking status:");
    scanf("%d", &checkSeat);

    /*Έλεγος του αριθμού του χρήστη εάν είναι εντός ορίων*/
    if (checkSeat>=1 && checkSeat<=seatcount){
        seats[checkSeat-1]==0 ? printf("The seat number %d is free.", checkSeat) : printf("\nThe seat number %d is booked.", checkSeat);}
    else printf("The seat number %d is not a valid seat. Please choose a seat number from 1 to %d.", checkSeat, seatcount);
    return;
}

/*Συνάρτηση προβολής κρατημένων θέσεων*/
void viewBookedSeats(){
    int i, counter=0;
    printf("Booked seat numbers: ");
    for (i=0; i<seatcount; i++){
        if (seats[i]==1){
            printf("%d, ", i+1);
            counter++;}
    }
    printf("\b\b "); /*Αυτό το κάνουμε για αισθητικούς λόγους για να μην υπάρχει το κόμμα στην τελευταία ελεύθερη θέση*/
    if (counter==0){
            printf("\b:\nThere isn't any booked seat yet.");}
    return;
}

/*Συνάρτηση προβολής αριθμού πινακίδας και σχεδιαγράμματος λεωφορείου*/
void printLayout(){
    int i;

    printf("%s\n\n", busname);

    for (i=0; i<seatcount; i++){
        printf("%c", seats[i] == 0 ? '_' : '*');
        if (i < seatcount - 5){ /*Για όσο διάστημα βρισκόμαστε στην κύρια καμπίνα του λεωφορείου ελέγχουμε εάν  έχει τελείωσε η τετράδα θέσεων για να αλλάξουμε σειρά
                                  ή εάν είμαστε σε δυάδα θέσεων για να εκτυπώσουμε τον διάδρομο.*/
            if ((i+1)%4 == 0){
                printf("\n");}
            else if ((i+1)%2 == 0){
                printf(" ");}
        }
    }
    return;
}

/*Συνάρτηση αποθήκευσης αριθμού πινακίδας και σχεδιαγράμματος λεωφορείου σε εξωτερικό αρχείο*/
void saveLayout(){
    FILE *layout;
    int i;

    layout = fopen("./layout.txt", "w"); /*Εγγραφή (w) στο αρχείο μας*/
    fprintf(layout, "%s\n\n", busname);
    for (i=0; i<seatcount; i++){
        fprintf(layout, "%c", seats[i] == 0 ? '_' : '*');
        if (i < seatcount-5){
            if ((i+1)%4 == 0){
                fprintf(layout, "\n");}
            else if ((i+1)%2 == 0){
                fprintf(layout, " ");}
        }
    }
    fclose(layout);
    printf ("Layout.txt saved successfully. Please check the program's directory.");
    return;
}

/*Το κύριο πρόγραμμα. Με την βοήθεια των παραπάνω συναρτήσεων είναι πολύ απλοποιημένο*/
int main(){
    int choice=0; /*Θα μας χρειαστεί για τον βρόχο switch του menu του προγράμματος*/

    openFile();
    for (;;){   /*ατέρμων βρόχος που θα διακοπεί μόνο με την εντολή return στην επιλογή 0*/
        menu();
        scanf(" %d", &choice);
        printf("\n");
        switch(choice){
            case 1: freeSeats(); break;
            case 2: bookSeat(); break;
            case 3: bookWindowSeat(); break;
            case 4: cancelBooking(); break;
            case 5: checkBooking(); break;
            case 6: viewBookedSeats(); break;
            case 7: printLayout(); break;
            case 8: saveLayout(); break;
            case 0: return 0;
            default: printf("Please give a valid menu number");
        }
        printf("\n\n");
    }
}

//Σύνοψη αποτελεσμάτων εξόδου
//0: Kανένα σφάλμα. Το πρόγραμμα εκτελέστηκε με επιτυχία.
//-1: Δεν βρέθηκε το αρχείο bus.txt
//-2: Δεν δηλώθηκαν σωστά οι θέσεις στο αρχείο bus.txt
