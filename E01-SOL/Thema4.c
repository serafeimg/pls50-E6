//*************************************************************
//*** ���50 "������� ������������� �� ������ ��� ���������" ***
//***                   ������� �01 - ���� 4                ***
//***                                                       ***
//***                   ��.���� 2016-17                     ***
//***              ��������: �������� ������                ***
//***                   AM: 123542                          ***
//*************************************************************

#include <stdio.h>  /*�� ��� ����������� ��� ��� fopen(), fclose(), f/printf(), f/scanf(), switch() */
#include <stdlib.h> /*�� ��� ����������� ��� ��� exit()*/

/*��������� ��� global ���������� ��� �� �������������� �� ������������ ��� ��� �����������*/
char busname[8] = {' '}; /*������� 8 ������ ��� ���� 7 ���������� ��� �� '\0'. ������������ ��� ������ ��������� �� ������� ����������*/
int seats[53] = {0};/*������� 53 ������ ��� ��� 53 ������ ��� ����������. ������������� ���� ��� ����� �� �� 0*/
int seatcount = 0; /*� ������� ������ ��� �� ������ bus*/

/*��������� ��� ��� �������� �������*/
void openFile(){
    FILE *bus; /*������ ������-��������� �������*/

    bus = fopen ("./bus.txt", "r");/*�������� (r) ��� ������� ���*/

    /*������� ������ ���� ��� �������� (�.�. ��������� ������)*/
    if (bus == NULL){
        printf("Error: Couldn't read bus.txt file. Please make sure that the file is in the same directory with the program. Thank you.");
        exit(-1);}

    fscanf(bus, "%7c %i", busname, &seatcount);/*�������� ��� �� ������*/

    /*������� ��������� �������, ��� � ������� ������ ���������� �� ��� ��������� �������� ������*/
    if ((seatcount-5)%4 != 0 || seatcount>53){
        printf("Error: There soudn't be a bus with %d seats. Please check the data in bus.txt file. Thank you.", seatcount);
        exit(-2);}

    fclose(bus); /*�������� ������� ��� ������������ ������*/
    return;
}

/*��������� ��� ��� ������� ��� ����� ���� �����*/
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

/*��������� ��� ��� ������� ��� ��������� ������*/
void freeSeats(){
    int i, counter=0; /*��������� i ��� ��� ����� ���������� ��� counter ��� ��� ������� ��������� ������*/

    printf("Free seat numbers: ");
    for (i=0; i<seatcount; i++){
        if (seats[i]==0){
            printf("%d, ", i+1);
            counter++;}
    }
    printf("\b\b "); /*���� �� ������� ��� ����������� ������ ��� �� ��� ������� �� ����� ���� ��������� �������� ����*/
    if (counter==0){
        printf("\b:\nThere isn't any seat booked yet.");}
    else printf("\nTotal number of free seats: %d", counter);
    return;
}

/*��������� ��� ������� �����*/
void bookSeat(){
    int seatToBook=0;

    printf("Please enter seat number to book:");
    scanf ("%d", &seatToBook);

    /*������� ��� ������� ��� ������ ��� ����� ����� ����� ��� ������� �������������� �����*/
    if (seatToBook>=1 && seatToBook<=seatcount){
        if (seats[seatToBook-1]==0){
            seats[seatToBook-1]= 1;
            printf("Seat number %d booked successfully!", seatToBook);}
        else printf("Seat number %d is already booked.", seatToBook);}
    else printf("Seat number %d is not valid. Please choose a seatnumber from 1 to %d.", seatToBook, seatcount);
    return;
}

/*��������� �������� ����� ���������*/
void bookWindowSeat(){
    int i;

    /*������� ��������� �������� ����������*/
    for (i=0; i<(seatcount-2);){
        if (seats[i]!=1){
            seats[i]=1;
            printf("Window seat %d booked successfully!", i+1);
            return;}
        if ((i+1)%4==0){ /*���������� ��� ��� ����� ��� ����� �� ��������*/
            i++;}
        else i+=3;}

    /*������� ��������*/
    if (seats[seatcount - 1] == 0){
        seats[seatcount - 1] = 1;
        printf("Window seat %d booked successfully!", seatcount);
        return;}

    printf("Unfortunately, no window seats left.");
    return;
}

/*��������� �������� ��������*/
void cancelBooking(){
    int seatToCancel=0;
    printf("Please enter seat number to cancel booking:");
    scanf("%d", &seatToCancel);

    /*������� ��� ������� ��� ������ ��� ����� ����� ����� ��� ������� �������������� �����*/
    if (seatToCancel>=1 && seatToCancel<=seatcount){
        if (seats[seatToCancel-1]==1){
            seats[seatToCancel-1]=0;
            printf("Seat number %d cancelled successfully!", seatToCancel);}
        else printf("Seat number %d is already free.", seatToCancel);}
    else printf("Seat number %d is not valid. Please choose a seat number from 1 to %d.", seatToCancel, seatcount);
    return;
}

/*��������� ������� ��������*/
void checkBooking(){
    int checkSeat=0;
    printf("Please enter seat number to check booking status:");
    scanf("%d", &checkSeat);

    /*������ ��� ������� ��� ������ ��� ����� ����� �����*/
    if (checkSeat>=1 && checkSeat<=seatcount){
        seats[checkSeat-1]==0 ? printf("The seat number %d is free.", checkSeat) : printf("\nThe seat number %d is booked.", checkSeat);}
    else printf("The seat number %d is not a valid seat. Please choose a seat number from 1 to %d.", checkSeat, seatcount);
    return;
}

/*��������� �������� ���������� ������*/
void viewBookedSeats(){
    int i, counter=0;
    printf("Booked seat numbers: ");
    for (i=0; i<seatcount; i++){
        if (seats[i]==1){
            printf("%d, ", i+1);
            counter++;}
    }
    printf("\b\b "); /*���� �� ������� ��� ����������� ������ ��� �� ��� ������� �� ����� ���� ��������� �������� ����*/
    if (counter==0){
            printf("\b:\nThere isn't any booked seat yet.");}
    return;
}

/*��������� �������� ������� ��������� ��� ��������������� ����������*/
void printLayout(){
    int i;

    printf("%s\n\n", busname);

    for (i=0; i<seatcount; i++){
        printf("%c", seats[i] == 0 ? '_' : '*');
        if (i < seatcount - 5){ /*��� ��� �������� ����������� ���� ����� ������� ��� ���������� ��������� ���  ���� �������� � ������� ������ ��� �� ��������� �����
                                  � ��� ������� �� ����� ������ ��� �� ����������� ��� ��������.*/
            if ((i+1)%4 == 0){
                printf("\n");}
            else if ((i+1)%2 == 0){
                printf(" ");}
        }
    }
    return;
}

/*��������� ����������� ������� ��������� ��� ��������������� ���������� �� ��������� ������*/
void saveLayout(){
    FILE *layout;
    int i;

    layout = fopen("./layout.txt", "w"); /*������� (w) ��� ������ ���*/
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

/*�� ����� ���������. �� ��� ������� ��� �������� ����������� ����� ���� ������������*/
int main(){
    int choice=0; /*�� ��� ��������� ��� ��� ����� switch ��� menu ��� ������������*/

    openFile();
    for (;;){   /*������� ������ ��� �� �������� ���� �� ��� ������ return ���� ������� 0*/
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

//������ ������������� ������
//0: K����� ������. �� ��������� ����������� �� ��������.
//-1: ��� ������� �� ������ bus.txt
//-2: ��� ��������� ����� �� ������ ��� ������ bus.txt
