//*************************************************************
//*** ΠΛΣ50 "Βασικές Εξειδικεύσεις σε Θεωρία και Λογισμικό" ***
//***                   Εργασία Ε02 - Θέμα 3                ***
//***                                                       ***
//***                   Ακ.έτος 2016-17                     ***
//***              Φοιτητής: Σεραφείμ Γκέκας                ***
//***                   AM: 123542                          ***
//*************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // Την χρειαζόμαστε για την  srand(), rand()
#include <string.h>


/*Δημιουργία struct για τους παίχτες με τρεις πληροφορίες*/
struct Player {
    char name[17];  //string μέγεθος 17 χαρακτήρων
    unsigned char score;    //ακέραιος αριθμός με ελάχιστη τιμή 0 και μέγιστη 255. Αρχική τιμή 0
    char id;    //χαρακτήρας αναγώρισης, μοναδικός για κάθε παίχτη
};

/*Struct για τις καρτες με τέσσερις ιδιότητες*/
struct Card {
    char color;
    char shape;
    int number;
    char texture;
};


/*Fuction prototypes*/
void populatePlayers();
int findPlayer(char id);
int  getRandomNumber();
char getRandomColor();
char getRandomShape();
char getRandomTexture();
void getNextCard(struct Card *card);
int  areCardsSame(struct Card cardA, struct Card cardB);
int  isCardUnique(struct Card card, int row, int column) ;
void suffleCards();
void printCards();
void printScores();
struct Card selectCard(int i);
int areColorsSame(struct Card cardA, struct Card cardB, struct Card cardC);
int areColorsDifferent(struct Card cardA, struct Card cardB, struct Card cardC);
int areShapesSame(struct Card cardA, struct Card cardB, struct Card cardC);
int areShapesDifferent(struct Card cardA, struct Card cardB, struct Card cardC);
int areNumbersSame(struct Card cardA, struct Card cardB, struct Card cardC);
int areNumbersDifferent(struct Card cardA, struct Card cardB, struct Card cardC);
int areTexturesSame(struct Card cardA, struct Card cardB, struct Card cardC);
int areTexturesDifferent(struct Card cardA, struct Card cardB, struct Card cardC);
int areCardsSet(struct Card cardA, struct Card cardB, struct Card cardC);
void saveScore(struct Player *I, struct Card cardA, struct Card cardB, struct Card cardC);


/*global variables*/
struct Card cardPlex[3][4]; //θα χρειαστεί για το πλέγμα των 12 καρτών
struct Player players[3];   //θα χρεαστεί για τους 3 παίκτες


/*Το κύριο πρόγραμμα*/
int main(){

    struct Player currentPlayer;
    struct Card cardA ;
    struct Card cardB ;
    struct Card cardC ;

    char choice; // Για την επιλογή του id του παίκτη ή τον τερματισμό

    srand(time(NULL)); //Αρχικοιούμε την συνάρτηση rand
    populatePlayers(); //Αρχικοποοιόυμε τους παίκτες του παιχνιδιού.
    for (;;){ // ατέρμων βρόχος
        suffleCards(); //Διαλέγουμε δωδεκάδα με μοναδικές κάρτες από τους 81 πιθανούς συνδυασμούς
        printCards(); // Εκτυπώνουμε στην οθόνη το πλέγμα με τις 12 κάρτες 3Χ4
        do {
            printf("Please enter player's id or 0 to exit:\n"); //Ζητάμε τον χρήστη να βάλει το id του παίχτη ή να πατήσει 0 για έξοδο
            scanf(" %c", &choice);
            if (choice == '0'){ // Εάν επιλέξει έξοδο
                printScores();  // Τυπώνουμε το σκορ των παικτών
                return 0;       // και τερματίζει το πρόγραμμα.
            }
            if (findPlayer(choice) == 0) break; //εάν το id του παίχτη δεν υπάρχει βγαίνει από την do και επιστρέφει στην αρχή της for
            cardA = selectCard(0); // Εάν δεν επιλέξει έξοδο, ζητάμε από τον παίχτη να επιλέξει κάρτες, βάζοντας τις συντεταγμένες
            cardB = selectCard(1);
            cardC = selectCard(2);

            switch (choice){ // ανάλογα με το id του παίκτη αποθηκεύουμε το σκορ του σύμφωνα με το αν οι κάρτες που επέλεξε κάνουν set ή όχι
                case 'a': saveScore(&players[0],cardA,cardB,cardC); break;
                case 'g': saveScore(&players[1],cardA,cardB,cardC); break;
                case 'p': saveScore(&players[2],cardA,cardB,cardC); break;
            }
            printf("\n"); // αλλαγή γραμμής για αισθητικούς λόγους μετά το τέλος του γύρου
        }while (areCardsSet(cardA,cardB,cardC) == -1); //εάν οι κάρτες δεν είναι set κρατάει τον ίδια 12άδα και επιστρέφει στην do
    }

    return;
}


void populatePlayers(){ //συνάρτηση void αρχικοποίησης της struct των παικτών βάση των δεδομένων της άσκησης

    strcpy(players[0].name, "Marina Andreou\0");
    players[0].score = 0;
    players[0].id = 'a';

    strcpy(players[1].name, "Kostas Grammenos\0");
    players[1].score = 0;
    players[1].id = 'g';

    strcpy(players[2].name, "Maria Perdika\0");
    players[2].score = 0;
    players[2].id = 'p';

    return;
}


int findPlayer(char id) { //συνάρτηση που ελέγχει την επιλογή του χρήστη εάν αντιστοιχεί σε κάποιο id παίχτη.
    int i;
    for (i=0; i<3; i++) {
        if (players[i].id == id) return 1;   //εάν υπάρχει το id, η συνάρτηση επιστρέφει 1
    }
    return 0;   //διαφορετικά επιστρέφει 0
}


int getRandomNumber(){  //συνάρτηση επιλογής τυχαίου αριθμού από το 1 έως το 3
    return (rand()%3)+1;
}


char getRandomColor() { // Ζευγαρώνουμε κάθε τυχαίο αριθμό 1-3 με τιμή χρώματος
    int random = getRandomNumber();
    return random == 1 ? 'r' : random == 2 ? 'g' : 'b';
}


char getRandomShape() { // Ζευγαρώνουμε κάθε τυχαίο αριθμό 1-3 με τιμή σχήματος
    int random = getRandomNumber();
    return random == 1 ? 'c' : random == 2 ? 't' : 'r';
}


char getRandomTexture() { // Ζευγαρώνουμε κάθε τυχαίο αριθμό 1-3 με τιμή υφής
    int random = getRandomNumber();
    return random == 1 ? 'b' : random == 2 ? 'h' : 'e';
}


void getNextCard(struct Card *card){ //συνάρτηση με δείκτη struct που θα χρησιμοποιηθεί με call by referance για την επιλογή των 12 καρτών

    (*card).color = getRandomColor();
    (*card).shape = getRandomShape();
    (*card).number = getRandomNumber();
    (*card).texture = getRandomTexture();

    return;
}


int areCardsSame(struct Card cardA, struct Card cardB){ // συνάρτηση που συγκρίνει αν δύο κάρτες είναι ίδιες συγκρίνοντας της κάθε τους ιδιότητα
    if ((cardA.color == cardB.color) &&
        (cardA.number == cardB.number) &&
        (cardA.shape == cardB.shape) &&
        (cardA.texture == cardB.texture)) return 1;   //αν οι κάρτες είναι ίδιες επιστρέφει ένα
    return 0;                                  //διαφορετικά επιστρέφει μηδέν
}


int isCardUnique(struct Card card, int row, int column) { //συνάρτηση που ελέγχει εάν η κάρτα είναι μονάδική

    int i, j;

    for (i=0; i<=row; i++) {
        for(j=0; j<=column; j++) { //ελέγχει κάθε τρέχουσα κάρτα εάν υπάρχει ήδη στο πλέγμα των 12 καρτών
            if (areCardsSame(card, cardPlex[i][j])== 1) return 0;   //εάν δεν είναι μοναδική επιστρέφει 0
        }
    }
    return 1;   //εάν είναι μοναδική επιστρέφει 1
}


void suffleCards(){ //Συνάρτηση που επιλέγει και αποθηκεύει δώδεκα μοναδικές κάρτες στην πίνακα struct cardPlex[3][4]

    struct Card card;
    int i, j;

    for (i=0; i<3; i++) {
        for(j=0; j<4; j++) {
            getNextCard(&card); //κάνουμε call by referance για να επιλέξουμε κάρτα
            while(isCardUnique(card, i, j)!= 1) {
                getNextCard(&card); //όσο η κάρτα που επιλέγουμε δεν είναι μοναδική πέρνουμε άλλη
            }
            cardPlex[i][j] = card; //εάν είναι μοναδική βγαίνουμε από την βρόχο και την αποθηκεύουμε στο πλέγμα cardPlex[3][4]
        }
    }
}


void printCards() { //συνάρτηση που εκτυπώνει στην οθόνη το πλέγμα των 12 καρτών cardPlex[3][4]

    int i,j;

    for (i=0; i<3; i++) {
        for(j=0; j<4; j++) {    //η κάθε στήλη έχει ένα κενό \t μεταξύ της
            printf ("[%c,%c,%d,%c]\t", cardPlex[i][j].color, cardPlex[i][j].shape, cardPlex[i][j].number, cardPlex[i][j].texture);
        }
        printf("\n");   //μετά την τελευταία στήλη αλλάζουμε σειρά και πάμε στην επόμενη τετράδα
    }
}


void printScores(){ //συνάρτηση που εκτυπώνει το σκορ των παικτών

    int i;

    for (i=0; i<3; i++){
        printf("Player's Name:%s\n", players[i].name);
        printf("Player's id:%c\n", players[i].id);
        printf("Player's score:%d\n\n", players[i].score);
    }

    return;
}


struct Card selectCard(int i){ //συνάρτηση που αποθηκεύει την επιλογή της κάρτας από τον παίκτη

    struct CardNumber{ //αυτή την struct την κάνουμε για αισθητικού λόγους για την printf που ακολουθεί
        char name[7];
    };
    struct CardNumber cardnum[3];
    int x,y;

    strcpy(cardnum[0].name, "first\0");
    strcpy(cardnum[1].name, "second\0");
    strcpy(cardnum[2].name, "third\0");

    printf("Please choose the %s card:", cardnum[i].name);
    scanf(" %d %d", &x, &y);
    while (x>2 || x<0 || y>3 || y<0){ // κάνουμε έλεγχο εάν η κάρτα που επέλεξε ο παίκτης είναι εντός του πλέγματος
        printf("Please choose a valid card number, try again:");    //όσο δεν είναι του ζητάμε να επιλέξει ξανά
        scanf(" %d %d", &x, &y);
    }

    return cardPlex[x][y];  //εάν είναι την γυρνάμε και την αποθηκεύουμε
}


int areColorsSame(struct Card cardA, struct Card cardB, struct Card cardC){ //συνάρτηση που ελέγχει αν το χρώμα τριών καρτών είναι ίδιο
    return cardA.color == cardB.color &&
            cardB.color == cardC.color;
}


int areColorsDifferent(struct Card cardA, struct Card cardB, struct Card cardC) { //συνάρτηση που ελέγχει αν το χρώμα τριών καρτών δεν είναι ίδιο
    return cardA.color != cardB.color &&
            cardB.color != cardC.color &&
            cardC.color != cardA.color;
}

int areShapesSame(struct Card cardA, struct Card cardB, struct Card cardC) { //συνάρτηση που ελέγχει αν το σχήμα τριών καρτών είναι ίδιο
    return cardA.shape == cardB.shape &&
            cardB.shape == cardC.shape;
}

int areShapesDifferent(struct Card cardA, struct Card cardB, struct Card cardC) {//συνάρτηση που ελέγχει αν το σχήμα τριών καρτών δεν είναι ίδιο
    return cardA.shape != cardB.shape &&
            cardB.shape != cardC.shape &&
            cardC.shape != cardA.shape;
}


int areNumbersSame(struct Card cardA, struct Card cardB, struct Card cardC) { //συνάρτηση που ελέγχει αν το νούμερο τριών καρτών είναι ίδιο
    return cardA.number == cardB.number &&
            cardB.number == cardC.number;
}


int areNumbersDifferent(struct Card cardA, struct Card cardB, struct Card cardC) {//συνάρτηση που ελέγχει αν το νούμερο τριών καρτών δεν είναι ίδιο
    return cardA.number != cardB.number &&
            cardB.number != cardC.number &&
            cardC.number != cardA.number;
}


int areTexturesSame(struct Card cardA, struct Card cardB, struct Card cardC) {//συνάρτηση που ελέγχει αν η υφή τριών καρτών είναι ίδια
    return cardA.texture == cardB.texture &&
            cardB.texture == cardC.texture;
}


int areTexturesDifferent(struct Card cardA, struct Card cardB, struct Card cardC) {//συνάρτηση που ελέγχει αν η υφή τριών καρτών δεν είναι ίδια
    return cardA.texture != cardB.texture &&
            cardB.texture != cardC.texture &&
            cardC.texture != cardA.texture;
}


int areCardsSet(struct Card cardA, struct Card cardB, struct Card cardC){ // συνάρτηση που ελέγχει εάν τρεις κάρτες είναι set

    if (areCardsSame(cardA,cardB) == 1 ||   //έλεγχος για τον αν δύο ή περισσότερες κάρτες είναι ίδιες
        areCardsSame(cardA,cardC) == 1 ||
        areCardsSame(cardB,cardC) == 1
        ) return -1;  //εάν βρεθούν ίδιες κάρτες επιστρέφει τον ακέραιο -1 (ο οποίος στην συνέχεια θα αφαιρεθεί από το σκορ του παίκτη)

    if ((areColorsSame(cardA, cardB, cardC) || areColorsDifferent(cardA, cardB, cardC)) && //αν οι κάρτες είναι set
        (areShapesSame(cardA, cardB, cardC) || areShapesDifferent(cardA, cardB, cardC)) &&
        (areNumbersSame(cardA, cardB, cardC) || areNumbersDifferent(cardA, cardB, cardC)) &&
        (areTexturesSame(cardA, cardB, cardC) ||areTexturesDifferent(cardA, cardB, cardC))
        ) return 2; //επιστρέφει τον ακέραιο 2 (το οποίο στην συνέχεια θα προστεθεί στο σκορ του παίκτη)

    return -1;  //σε διαφορετική περίπτωση οι κάρτες δεν είναι set και επιστρέφει τον ακέραιο -1 (ο οποίος στην συνέχεια θα αφαιρεθεί από το σκορ του παίκτη)
}


void saveScore(struct Player *I, struct Card cardA, struct Card cardB, struct Card cardC){//συνάρτηση struct δείκτη που θα γίνει call by referance για να αποθηκεύσει το score του παίχτη

    areCardsSet(cardA, cardB,cardC) == -1 ? printf("Your cards aren't set\n") :  printf("Your cards are set!\n"); //εκτυπώνουμε στην οθόνη εάν είναι set η κάρτες ή όχι
    if ((*I).score>=0 && (*I).score<10)(*I).score+=(areCardsSet(cardA,cardB,cardC)); //προσθέτει στο υπάρχον score του παίχτη το αποτέλεσμα του ελέγχου των καρτών εάν είναι set
    if ((*I).score==255)(*I).score=0; //εάν το score ήταν είδη μηδέν και από τον παραπάνω έλεγχο έπεσε στο -1(255 σε unsigned char) το επαναφέρει στο 0 γιατί δεν υπάρχει αρνητικό score
    if ((*I).score>=10){    //εάν το score κάποιου παίχτη γίνει 10 ή παραπάνω
            printf("The winner is: %s\n", (*I).name);   //εκτυπώνει στην οθόνη το όνομά του
            printScores();  //καθώς επίσης και το σκορ όλων των παικτών
            exit(0);}   //και τερματίζει το πρόγραμμα

    return;
}
