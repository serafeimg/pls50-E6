//*************************************************************
//*** ���50 "������� ������������� �� ������ ��� ���������" ***
//***                   ������� �02 - ���� 3                ***
//***                                                       ***
//***                   ��.���� 2016-17                     ***
//***              ��������: �������� ������                ***
//***                   AM: 123542                          ***
//*************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <time.h> // ��� ������������ ��� ���  srand(), rand()
#include <string.h>


/*���������� struct ��� ���� ������� �� ����� �����������*/
struct Player {
    char name[17];  //string ������� 17 ����������
    unsigned char score;    //�������� ������� �� �������� ���� 0 ��� ������� 255. ������ ���� 0
    char id;    //���������� ����������, ��������� ��� ���� ������
};

/*Struct ��� ��� ������ �� �������� ���������*/
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
struct Card cardPlex[3][4]; //�� ��������� ��� �� ������ ��� 12 ������
struct Player players[3];   //�� �������� ��� ���� 3 �������


/*�� ����� ���������*/
int main(){

    struct Player currentPlayer;
    struct Card cardA ;
    struct Card cardB ;
    struct Card cardC ;

    char choice; // ��� ��� ������� ��� id ��� ������ � ��� ����������

    srand(time(NULL)); //����������� ��� ��������� rand
    populatePlayers(); //�������������� ���� ������� ��� ����������.
    for (;;){ // ������� ������
        suffleCards(); //���������� �������� �� ��������� ������ ��� ���� 81 �������� �����������
        printCards(); // ����������� ���� ����� �� ������ �� ��� 12 ������ 3�4
        do {
            printf("Please enter player's id or 0 to exit:\n"); //������ ��� ������ �� ����� �� id ��� ������ � �� ������� 0 ��� �����
            scanf(" %c", &choice);
            if (choice == '0'){ // ��� �������� �����
                printScores();  // ��������� �� ���� ��� �������
                return 0;       // ��� ���������� �� ���������.
            }
            if (findPlayer(choice) == 0) break; //��� �� id ��� ������ ��� ������� ������� ��� ��� do ��� ���������� ���� ���� ��� for
            cardA = selectCard(0); // ��� ��� �������� �����, ������ ��� ��� ������ �� �������� ������, �������� ��� �������������
            cardB = selectCard(1);
            cardC = selectCard(2);

            switch (choice){ // ������� �� �� id ��� ������ ������������ �� ���� ��� ������� �� �� �� �� ������ ��� ������� ������ set � ���
                case 'a': saveScore(&players[0],cardA,cardB,cardC); break;
                case 'g': saveScore(&players[1],cardA,cardB,cardC); break;
                case 'p': saveScore(&players[2],cardA,cardB,cardC); break;
            }
            printf("\n"); // ������ ������� ��� ����������� ������ ���� �� ����� ��� �����
        }while (areCardsSet(cardA,cardB,cardC) == -1); //��� �� ������ ��� ����� set ������� ��� ���� 12��� ��� ���������� ���� do
    }

    return;
}


void populatePlayers(){ //��������� void ������������� ��� struct ��� ������� ���� ��� ��������� ��� �������

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


int findPlayer(char id) { //��������� ��� ������� ��� ������� ��� ������ ��� ����������� �� ������ id ������.
    int i;
    for (i=0; i<3; i++) {
        if (players[i].id == id) return 1;   //��� ������� �� id, � ��������� ���������� 1
    }
    return 0;   //����������� ���������� 0
}


int getRandomNumber(){  //��������� �������� ������� ������� ��� �� 1 ��� �� 3
    return (rand()%3)+1;
}


char getRandomColor() { // ������������ ���� ������ ������ 1-3 �� ���� ��������
    int random = getRandomNumber();
    return random == 1 ? 'r' : random == 2 ? 'g' : 'b';
}


char getRandomShape() { // ������������ ���� ������ ������ 1-3 �� ���� ��������
    int random = getRandomNumber();
    return random == 1 ? 'c' : random == 2 ? 't' : 'r';
}


char getRandomTexture() { // ������������ ���� ������ ������ 1-3 �� ���� ����
    int random = getRandomNumber();
    return random == 1 ? 'b' : random == 2 ? 'h' : 'e';
}


void getNextCard(struct Card *card){ //��������� �� ������ struct ��� �� �������������� �� call by referance ��� ��� ������� ��� 12 ������

    (*card).color = getRandomColor();
    (*card).shape = getRandomShape();
    (*card).number = getRandomNumber();
    (*card).texture = getRandomTexture();

    return;
}


int areCardsSame(struct Card cardA, struct Card cardB){ // ��������� ��� ��������� �� ��� ������ ����� ����� ������������ ��� ���� ���� ��������
    if ((cardA.color == cardB.color) &&
        (cardA.number == cardB.number) &&
        (cardA.shape == cardB.shape) &&
        (cardA.texture == cardB.texture)) return 1;   //�� �� ������ ����� ����� ���������� ���
    return 0;                                  //����������� ���������� �����
}


int isCardUnique(struct Card card, int row, int column) { //��������� ��� ������� ��� � ����� ����� ��������

    int i, j;

    for (i=0; i<=row; i++) {
        for(j=0; j<=column; j++) { //������� ���� �������� ����� ��� ������� ��� ��� ������ ��� 12 ������
            if (areCardsSame(card, cardPlex[i][j])== 1) return 0;   //��� ��� ����� �������� ���������� 0
        }
    }
    return 1;   //��� ����� �������� ���������� 1
}


void suffleCards(){ //��������� ��� �������� ��� ���������� ������ ��������� ������ ���� ������ struct cardPlex[3][4]

    struct Card card;
    int i, j;

    for (i=0; i<3; i++) {
        for(j=0; j<4; j++) {
            getNextCard(&card); //������� call by referance ��� �� ���������� �����
            while(isCardUnique(card, i, j)!= 1) {
                getNextCard(&card); //��� � ����� ��� ���������� ��� ����� �������� �������� ����
            }
            cardPlex[i][j] = card; //��� ����� �������� ��������� ��� ��� ����� ��� ��� ������������ ��� ������ cardPlex[3][4]
        }
    }
}


void printCards() { //��������� ��� ��������� ���� ����� �� ������ ��� 12 ������ cardPlex[3][4]

    int i,j;

    for (i=0; i<3; i++) {
        for(j=0; j<4; j++) {    //� ���� ����� ���� ��� ���� \t ������ ���
            printf ("[%c,%c,%d,%c]\t", cardPlex[i][j].color, cardPlex[i][j].shape, cardPlex[i][j].number, cardPlex[i][j].texture);
        }
        printf("\n");   //���� ��� ��������� ����� ��������� ����� ��� ���� ���� ������� �������
    }
}


void printScores(){ //��������� ��� ��������� �� ���� ��� �������

    int i;

    for (i=0; i<3; i++){
        printf("Player's Name:%s\n", players[i].name);
        printf("Player's id:%c\n", players[i].id);
        printf("Player's score:%d\n\n", players[i].score);
    }

    return;
}


struct Card selectCard(int i){ //��������� ��� ���������� ��� ������� ��� ������ ��� ��� ������

    struct CardNumber{ //���� ��� struct ��� ������� ��� ���������� ������ ��� ��� printf ��� ���������
        char name[7];
    };
    struct CardNumber cardnum[3];
    int x,y;

    strcpy(cardnum[0].name, "first\0");
    strcpy(cardnum[1].name, "second\0");
    strcpy(cardnum[2].name, "third\0");

    printf("Please choose the %s card:", cardnum[i].name);
    scanf(" %d %d", &x, &y);
    while (x>2 || x<0 || y>3 || y<0){ // ������� ������ ��� � ����� ��� ������� � ������� ����� ����� ��� ���������
        printf("Please choose a valid card number, try again:");    //��� ��� ����� ��� ������ �� �������� ����
        scanf(" %d %d", &x, &y);
    }

    return cardPlex[x][y];  //��� ����� ��� ������� ��� ��� ������������
}


int areColorsSame(struct Card cardA, struct Card cardB, struct Card cardC){ //��������� ��� ������� �� �� ����� ����� ������ ����� ����
    return cardA.color == cardB.color &&
            cardB.color == cardC.color;
}


int areColorsDifferent(struct Card cardA, struct Card cardB, struct Card cardC) { //��������� ��� ������� �� �� ����� ����� ������ ��� ����� ����
    return cardA.color != cardB.color &&
            cardB.color != cardC.color &&
            cardC.color != cardA.color;
}

int areShapesSame(struct Card cardA, struct Card cardB, struct Card cardC) { //��������� ��� ������� �� �� ����� ����� ������ ����� ����
    return cardA.shape == cardB.shape &&
            cardB.shape == cardC.shape;
}

int areShapesDifferent(struct Card cardA, struct Card cardB, struct Card cardC) {//��������� ��� ������� �� �� ����� ����� ������ ��� ����� ����
    return cardA.shape != cardB.shape &&
            cardB.shape != cardC.shape &&
            cardC.shape != cardA.shape;
}


int areNumbersSame(struct Card cardA, struct Card cardB, struct Card cardC) { //��������� ��� ������� �� �� ������� ����� ������ ����� ����
    return cardA.number == cardB.number &&
            cardB.number == cardC.number;
}


int areNumbersDifferent(struct Card cardA, struct Card cardB, struct Card cardC) {//��������� ��� ������� �� �� ������� ����� ������ ��� ����� ����
    return cardA.number != cardB.number &&
            cardB.number != cardC.number &&
            cardC.number != cardA.number;
}


int areTexturesSame(struct Card cardA, struct Card cardB, struct Card cardC) {//��������� ��� ������� �� � ��� ����� ������ ����� ����
    return cardA.texture == cardB.texture &&
            cardB.texture == cardC.texture;
}


int areTexturesDifferent(struct Card cardA, struct Card cardB, struct Card cardC) {//��������� ��� ������� �� � ��� ����� ������ ��� ����� ����
    return cardA.texture != cardB.texture &&
            cardB.texture != cardC.texture &&
            cardC.texture != cardA.texture;
}


int areCardsSet(struct Card cardA, struct Card cardB, struct Card cardC){ // ��������� ��� ������� ��� ����� ������ ����� set

    if (areCardsSame(cardA,cardB) == 1 ||   //������� ��� ��� �� ��� � ������������ ������ ����� �����
        areCardsSame(cardA,cardC) == 1 ||
        areCardsSame(cardB,cardC) == 1
        ) return -1;  //��� ������� ����� ������ ���������� ��� ������� -1 (� ������ ���� �������� �� ��������� ��� �� ���� ��� ������)

    if ((areColorsSame(cardA, cardB, cardC) || areColorsDifferent(cardA, cardB, cardC)) && //�� �� ������ ����� set
        (areShapesSame(cardA, cardB, cardC) || areShapesDifferent(cardA, cardB, cardC)) &&
        (areNumbersSame(cardA, cardB, cardC) || areNumbersDifferent(cardA, cardB, cardC)) &&
        (areTexturesSame(cardA, cardB, cardC) ||areTexturesDifferent(cardA, cardB, cardC))
        ) return 2; //���������� ��� ������� 2 (�� ����� ���� �������� �� ��������� ��� ���� ��� ������)

    return -1;  //�� ����������� ��������� �� ������ ��� ����� set ��� ���������� ��� ������� -1 (� ������ ���� �������� �� ��������� ��� �� ���� ��� ������)
}


void saveScore(struct Player *I, struct Card cardA, struct Card cardB, struct Card cardC){//��������� struct ������ ��� �� ����� call by referance ��� �� ����������� �� score ��� ������

    areCardsSet(cardA, cardB,cardC) == -1 ? printf("Your cards aren't set\n") :  printf("Your cards are set!\n"); //����������� ���� ����� ��� ����� set � ������ � ���
    if ((*I).score>=0 && (*I).score<10)(*I).score+=(areCardsSet(cardA,cardB,cardC)); //��������� ��� ������� score ��� ������ �� ���������� ��� ������� ��� ������ ��� ����� set
    if ((*I).score==255)(*I).score=0; //��� �� score ���� ���� ����� ��� ��� ��� �������� ������ ����� ��� -1(255 �� unsigned char) �� ���������� ��� 0 ����� ��� ������� �������� score
    if ((*I).score>=10){    //��� �� score ������� ������ ����� 10 � ��������
            printf("The winner is: %s\n", (*I).name);   //��������� ���� ����� �� ����� ���
            printScores();  //����� ������ ��� �� ���� ���� ��� �������
            exit(0);}   //��� ���������� �� ���������

    return;
}
