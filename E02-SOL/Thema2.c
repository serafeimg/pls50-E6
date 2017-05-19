//*************************************************************
//*** ���50 "������� ������������� �� ������ ��� ���������" ***
//***                   ������� �02 - ���� 2                ***
//***                                                       ***
//***                   ��.���� 2016-17                     ***
//***              ��������: �������� ������                ***
//***                   AM: 123542                          ***
//*************************************************************

#include <stdio.h>  //�� ��� ����������� ��� ��� fopen(), fclose(), f/printf(), f/scanf()
#include <stdlib.h> //�� ��� ����������� ��� ��� exit(), malloc()
#include <string.h> //�� ��� ����������� ��� ��� strcat(), strcpy(), strcmp()


/*������ ��� Struct*/
struct passenger{
    char passName[40];
    unsigned short phoneNumber[10];
    unsigned int seatNumber;
};


/*������ ������ ������*/
struct Node {
    struct passenger data; //�������� ��� ������
    struct Node *next; //������� ���������� ��� �������� ������
};


/*��������� ��� global ���������� ��� �� �������������� �� ������������ ��� ��� �����������*/
char busname[8]; //������� 8 ������ ��� ���� 7 ���������� ��� ��������� ��� �� '\0'.
int seatCount = 0; //� ������� ������ ��� �� ������ bus
struct passenger *seats; // ������� ������ �� struct ��� ��� �������� ������ ������
struct Node *head = NULL; //������� ������ ��������� ��� ������������ ��� �� ��� �������� ��������� NULL


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
void sortSeats();
void sortByNumber();
void sortByName();
struct Node *insert(struct Node *p, struct passenger n);
void createList();
void saveOnExit();


/*����� ���������*/
int main(){

    int i=0, choice=0;  //��������� ������� i ��� choice ��� ��� ������� ��� �����

    openFile(); //�������� �������
    for (;;){   //������� ������ ��� �� �������� ���� �� ��� ������ return ���� ������� 0
        menu(); //�������� ��� ����� ���� �����
        scanf(" %d", &choice);  //�������� �������� ������
        printf("\n");
        switch(choice){ //������ switch ��� ��� ������� ��� �����
            case 1: freeSeats(); break;
            case 2: bookSeatMenu(); break;
            case 3: findBooking(); break;
            case 4: cancelBookingMenu(); break;
            case 5: sortSeats(); break;
            case 0: saveOnExit(); return 0; //���������� �� ������ ��� ���������� �� ���������
            default: printf("Please give a valid menu number"); //�� �� ������ ������� ������� ��� ��� switch ��� �������� � for
        }
        printf("\n\n"); //�������� ����� ��� ����������� ������
    }

}


/*��������� ��� ��� �������� �������*/
void openFile(){
    FILE *bus; //������ ������-��������� �������
    char surename[40], name[40];
    int seatnum, i;
    double phonenum;

    bus = fopen ("./bus.txt", "r");//�������� (r) ��� ������� ���

    if (bus == NULL){   //������� ������ ���� ��� �������� (�.�. ��������� ������)
        printf("Error: Couldn't read bus.txt file. Please make sure that the file is in the same directory with the program. Thank you.");
        exit(1);}

    fscanf(bus, "%s %i", busname, &seatCount);//�������� ��� �� ������

    /*���� �� ������� ��� ������� ��� ���������� �� ���� �� ���� ����� � ������� ��� ����� ���������*/
    /*if ((seatCount-5)%4 != 0 || seatCount>53){ //������� ��������� �������, ��� � ������� ������ ���������� �� ��� ��������� �������� ������
        printf("Error: There soudn't be a bus with %d seats. Please check the data in bus.txt file. Thank you.", seatCount);
        exit(1);}*/

    seats = (struct passenger *) malloc(seatCount*sizeof(struct passenger)); //�������� �������� ������ ��� ��� ������ ��� ������

    for (i=0; i<seatCount; i++) { //������������ ��� ������ ������
        seats[i].passName[0] = '\0';
        seats[i].seatNumber = i + 1;
    }

    /*�������� ��� ��������� ��� ������� ���� struct*/
    while( !feof(bus) ) //��� ��� ������� ��� ����� ��� �������
    {
        fscanf(bus,"%s %s %d %lf\n",surename,name,&seatnum,&phonenum);  //��� ���� ����� ������������ �� �������� �� ���������� ����������
        strcat(surename, " ");  //�������� �� ����� �� �� ������� �� ��� ����� ������� ����
        strcat(surename, name);
        strcpy(seats[seatnum-1].passName, surename);
        seats[seatnum-1].seatNumber = seatnum;
        for (i=9 ; i>=0 ; i--){ //������� ��� ���������� ��� ������ ���� ��������� unsigned short ������
            seats[seatnum-1].phoneNumber[i] = (long long int)phonenum%10;   //������������ �� typecast ��� �� ������������ ����� �� modulo %
            phonenum/=10;
        }
    }

    fclose(bus); //�������� ������� ��� ������������ ������

    return;
}


/*��������� ��� ��� ������� ��� ����� ���� �����*/
void menu(){
    printf("Bus:%s Seats:%d\n", busname, seatCount);    //�� �������� ���� �� ������ �������� ��� �� ������. ����� global �� ���������� ��� ���������� �� ��� ��������.
    printf("\t**Menu**\n");
    printf("1. View all free seats\n");
    printf("2. Book seat\n");
    printf("3. Find booking\n");
    printf("4. Cancel Booking\n");
    printf("5. View all booked seats\n");
    printf("0. Save&Exit\n");
    return;
}


/*��������� ��� ��� ������� ��� ��������� ������*/
void freeSeats(){
    int i, counter=0; //��������� ������� i ��� ��� ����� ���������� ��� counter ��� ��� ������� ������� ��������� ������

    printf("Free seat numbers: ");
    for (i=0; i<seatCount; i++){
        if (seats[i].passName[0]=='\0'){    //�� ��� ������� ���� ����������� ��� �������� ����
            printf("%d, ", i+1);
            counter++;}
    }
    printf("\b\b "); //���� �� ������� ��� ����������� ������ ��� �� ��� ������� �� ����� ���� ��������� �������� ����
    if (counter==0){
        printf("\b:\nThere isn't any seat booked yet\n.");}
    else printf("\nTotal number of free seats: %d\n", counter);
    return;
}


/*��������� ��� ������� �����*/
void bookSeat(struct passenger *seat){
    int i=0;
    char name[40];
    double phonenum;

    if ((*seat).passName[0]=='\0'){ //������� ��� � ���� ��� ��� ����� � ������� ����� ����.
        printf("Please enter Passenger's full name:");
        scanf(" %[^\n]s", name); //�������������� �� [^\n] ��� �� ���������� �� ����� ������� �� ������� ��� �����
        strcpy((*seat).passName, name); //������������ �� ������������� ���� ������ ��� �� �������� struct
        printf("Please enter Passenger's phone number:");
        scanf(" %lf", &phonenum);
        for (i=9 ; i>=0 ; i--){ //�� ���������� ����� ���� ��� ���� �������� ��� ������� ������� ��� ��������� double �� ������  unsigned short
            (*seat).phoneNumber[i] = (long long int)phonenum%10;
            phonenum/=10;
        }
        printf("Seat number %d booked successfully!\n\n", (*seat).seatNumber);
    } else{
        printf("Seat number %d is already booked.\n\n", (*seat).seatNumber);    //������ ��������� ��� � ���� ����� ��� ���������
    }

    return;
}


/*��������� �������� ��� ����� ��� ��� ������� �����*/
void bookSeatMenu(){

    int seatToBook=0;
    printf("Please enter seat number to book: ");
    scanf("%d", &seatToBook);    //������� ������ ��� �����
    if (seatToBook>=1 && seatToBook<=seatCount) {   //������� ��� ������� ��� ������ ��� ����� ����� ����� ��� ������� �������������� �����
        bookSeat(&seats[seatToBook -1]); //����� ���������� �� by reference
    } else printf("Seat number %d is not valid. Please choose a seatNumber from 1 to %d.", seatToBook, seatCount);

    return;
}


/*��������� ������� ���������� �����*/
void findBooking() {
    int choice;
    printf("1. Find by name\n");    //�������� ��������
    printf("2. Find by phone number\n");
    scanf(" %d", &choice);

    if (choice == 1){   //������� ��� ������� ��� ������ ����� ��� ���������� ���������
        findBookingByName();
    } else if (choice == 2){
        findBookingByPhone();
    }
    else{
        printf("No valide choice.");  //�������� ��������� �� �������� ����� ��������
    }
    return;
}


/*��������� ���������� ����� ���� ���������*/
void findBookingByPhone(){
    int i, temp[10], counter, j;
    double cnum, cnum2;

    printf("Please enter passenger's phone number:");
    scanf(" %lf", &cnum);
    cnum2=cnum; //������� ��� ���� ��� ��� �������� ��� ������� ���������

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


/*��������� ���������� ����� ���� ��������������*/
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


/*��������� �������� ��������*/
void cancelBooking(struct passenger *seat){

    if((*seat).passName[0] == '\0'){
        printf("The seat number %d is not booked.", (*seat).seatNumber );
    } else {
        (*seat).passName[0] = '\0';
        printf("The seat number %d cancelled succesfully.", (*seat).seatNumber );
    }
    return;
}


/*��������� �������� ����� ��� ��� ������� ��������*/
void cancelBookingMenu(){
    int seatToCancel=0;
    printf("Please enter seat number to cancel: ");
    scanf(" %d", &seatToCancel);  //������� ������ ��� �����
    if (seatToCancel>=1 && seatToCancel<=seatCount) {   //������� ��� ������� ��� ������ ��� ����� ����� ����� ��� ������� �������������� �����
        cancelBooking(&seats[seatToCancel -1]);
    } else printf("Seat number %d is not valid. Please choose a seatNumber from 1 to %d.", seatToCancel, seatCount); //������ ��������� ��� ��� ����� �� ������ ������ �����

    return;
}


/*��������� �������� ���������*/
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

//��� �������� ��������� ��� ����� ������ ��� ��� ���������� bubble sort ����� ������ ��� ������ ���� �������� ��� struct �� �� ������� swap ���-���
//���� ������� ��� ������� swap ���� ��� struct ����� ������� ��� ������������ �����. ������� ��� �� ���� ��� �������
/*void swapThem(int i, int j, struct passenger swap){

    int k;

    strcpy(swap.passName, seats[j].passName);
    swap.seatNumber = seats[j].seatNumber;
    for (k=0; k<10; k++){
        swap.phoneNumber[k] = seats[j].phoneNumber[k];
    }

    strcpy(seats[j].passName, seats[j+1].passName);
    seats[j].seatNumber = seats[j+1].seatNumber;
    for (k=0; k<10; k++){
    seats[j].phoneNumber[k] = seats[j+1].phoneNumber[k];
    }

    strcpy(seats[j+1].passName,swap.passName);
    seats[j+1].seatNumber = swap.seatNumber;
    for (k=0; k<10; k++){
    seats[j+1].phoneNumber[k] = swap.phoneNumber[k];
    }

    return;
}*/


/*��������� �������� ����� ��� ��� ������� ������������� ������*/
void sortSeats(){
    int choice=0;

    printf("Please choose:\n"); //�������� �������� ��� �������� 5 ���� �����
    printf("1.View sorted by seat number\n");
    printf("2.View sorted by passenger's name\n");
    scanf(" %d", &choice);   //������� ������
    if (choice == 1){
        sortByNumber();
    } else if (choice == 2){
        sortByName();
    }
    else{
        printf("No valide choice.\n");  //������ ��������� �� �� ������ �������
        return;
    }
    viewBookedSeats();  //��������� ��� ������ ���� �����
    sortByNumber();     //������������ ��� ������ ���� ������ ��������� ���� ��� �������

    return;
}


/*��������� ����������� ������ �� struct �������� ���� ������� �����*/
void sortByNumber(){
    int i, j;
    struct passenger swap;

    for (i=0 ; i<(seatCount-1); i++){   //����� ��������� bubble sort
        for (j=0 ; j<(seatCount-i-1); j++){
            if (seats[j].seatNumber > seats[j+1].seatNumber){
                swap = seats[j];
                seats[j] = seats[j+1];
                seats[j+1] = swap;
                //swapThem(i, j, swap); ���� ���������� ���� ��������� ��� ������ swap ���-��� �� �������� ��� �����. ���� ������ �� �� ���������� ����� �������� ������� swap ��������� ��� ��� ����.
            }
        }
    }
    return;
}


/*��������� ����������� ������ �� struct �������� ���� ��������������*/
void sortByName(){
    int i, j;
    struct passenger swap;

    for (i=0; i<(seatCount-1); i++){    //����� ��������� bubble sort
        for (j=0; j<(seatCount-i-1); j++){
            if (strcmp(seats[j].passName,seats[j+1].passName) > 0){
                swap = seats[j];
                seats[j] = seats[j+1];
                seats[j+1] = swap;
               // swapThem(i, j, swap);���� ���������� ���� ��������� ��� ������ swap ���-��� �� �������� ��� �����. ���� ������ �� �� ���������� ����� �������� ������� swap ��������� ��� ��� ����.
            }
        }
    }
    return;
}

//���� ���� ����� ��� ����������� ��� ������������ ������ �� ��� �������� �����.
//�� ���������� ���� ����� ���� ��� ���� �� ����� recursively
/*void getNextNode(struct passenger seat){

    if (head == NULL) {
        head = malloc(sizeof(struct Node));
        head->data = seat;
        head->next = NULL;
        return;
    }

    struct Node *currentNode = head;    //���������� ������ ����� ��� �������� ��� ��� ������ ������ head
    while (currentNode->next != NULL) { //�������� ��� ������ ��� ����� �� ���� ��� ������ ����� ��� ������� ��� 0
        currentNode = currentNode->next;
    }

    /*�������� ���� ������ ��� ����� ��� �����*/
/*    struct Node *newNode;//���������� ������ ���� ������
    newNode=malloc(sizeof(struct Node)); //+������� ��� ������������� ������

    currentNode->next = newNode; //� ���������� ������ ������� ���� ���� ���
    newNode->data = seat;   //������� ���� ��� ����� �� ��������
    newNode->next = NULL; //������� ��� ��� ����� �� ������� ���� ��� ������� � ���������� ������ ��� NULL

    return;
}
*/
struct Node *insert(struct Node *p, struct passenger n){

    if(p==NULL){//�� �� node ����� �� ���������, ������ ������� ��� NULL
        p=(struct Node *)malloc(sizeof(struct Node));   //������������� ��� node
        if(p==NULL){    //������� �������������� ������ ��� �� ��� node
            printf("*Error*\nNo free memory\n");
            exit(0);    //�� ��������� �� ���������� ������ ������������ �� ���������
        }
        p->data = n;    //������� �� �������� ��� ��� node
        p->next = NULL; //�� ��� node ������� ��� NULL ��� �� ����� ���� ���� �� ��������� ���� �����
    }else{
        p->next = insert(p->next,n);    //��� ����� � ��������������, �� ��� ����� ���� ���������� ��� while loop. �������� ��� ���� ��������� ���� ���� ���������. ���� ������� ����� �� �������� ��� ��������� node ���� �� ��������� �� ���.
    }

    return p;
}


/*��������� ����������� ��� ������������ ������*/
void createList() {

    sortByName();   //�� ���������� ������� �� ����� ������������ ���� ��������
    int i;  //��������� ������� i

    for (i=0; i<seatCount; i++) {
        if (seats[i].passName[0] != '\0') {
                head =insert(head, seats[i]);   //�������� ��� ��� ������ ��� ������������ ��� ����� �� ����� ���������� ����� �� �������� �� ������ ��� ���������
        }
    }

    return;
}


/*��������� ����������� ������� ��� ����������� ��� ������������*/
void saveOnExit(){

    FILE *bus;  //������ ������-��������� �������
    int i;

    bus = fopen("./bus.txt", "w"); //������� (w) ��� ������ ���
    fprintf(bus, "%s %d\n", busname, seatCount);

    createList();
    struct Node *currentNode = head; //�������� ��� ���������� ��� ��� ������ ������ head

    while (currentNode != NULL) {   //��� � ����� ��� ���� ������ ��� �����
        fprintf(bus, "%s ", currentNode->data.passName);    //������� �� �������� ��� ������
        fprintf(bus, "%d ", currentNode->data.seatNumber);
        for (i=0 ; i<10 ; i++){
            fprintf(bus, "%d", currentNode->data.phoneNumber[i]);
        }
        fprintf(bus, "\n" ); //���� �� ������� ��� �� ������� ������ ��� ��������� ����� ��� ������� ���������
        currentNode = currentNode->next;    //������� ��� ������� Node
    }

    fclose(bus);    //�������� ������� ��� ������������ ������
    free(seats);    //������������ ������ ��� ���� �������� ��� ��� �������� ������.

    printf ("Bus.txt saved successfully. Please check the program's directory. Thank you.\n\n");
    return;
}
