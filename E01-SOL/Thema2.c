//*************************************************************
//*** ΠΛΣ50 "Βασικές Εξειδικεύσεις σε Θεωρία και Λογισμικό" ***
//***                Εργασία Ε01 - Θέμα 2                   ***
//***                                                       ***
//***                   Ακ.έτος 2016-17                     ***
//***                Φοιτητής: Σεραφείμ Γκέκας              ***
//***                     AM: 123542                        ***
//*************************************************************

#include <stdio.h>  /*Την χρειαζόμαστε για την printf() και scanf()*/
#include <math.h>   /*Την χρειαζόμαστε για την sqrt()*/

/*Δηλώνουμε την μεταβλητή π σε περίπτωση που δεν υπάρχει στην βιβλιοθήκη <math.h>
για να εξασφαλίσουμε πως ο κώδικας θα περνάει από οποιονδήποτε μεταγλωτιστή*/
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*Συναρτήσεις υπολογισμού περιμέτρων για το κάθε σχήμα*/

/*Για το τετράγωνο*/
float square (float a){
    return 4*a
}

/*Παραλληλόγραμμο*/
float paral (float a, float b){
    return 2*a+2*b;}

/*Τρίγωνο*/
float tria (float a, float b){
    return a+b+sqrt(a*a+b*b);
}

/*Κύκλο*/
float circle (float a){
    return 2*M_PI*a
}

/*Το κύριο μας πρόγραμμα, ανάλογα την επιλογή του μενού καλούμε την αντίστοιχη συνάρτηση*/
int main()
{
/*Δήλωση σταθερών*/
    char choice; /*Τύπου χαρακτήρα για την επιλογή του μενού*/
    float side,width,sidea,sideb,rad; /*Σταθερές για τον υπολογισμο των περιμέτρων*/

    do {
        printf("\t*Menu*\nPlease choose:\n");
        printf("1.Square\n2.Parallelogram\n3.Right triangle\n4.Circle\n0.Exit\n\n");
        scanf(" %c", &choice);          /*Ζητάμε από το χρήστη να επιλέξει από το μενού και ανάλογα τι θα μας δώσει μπένουμε στην αντίστοιχη if.
                                          Το πρόγραμμα τερματίζει μόνο εάν ο χρήστης δώσει 0, διαφορετικά επαναλαμβάνεται*/
        if (choice == '1'){
            printf("Please give side's length:\n");
            scanf(" %f", &side);
            printf("The square's perimeter is: %0.3f\n", square(side));
            printf("Let's go again!\n\n");}
        if (choice == '2'){
            printf("Please give Parallelogram's base length:\n");
            scanf(" %f", &side);
            printf("Please give Parallelogram's side length:\n");
            scanf(" %f", &width);
            printf("The Parallelogram's perimeter is: %0.3f\n", paral(side,width));
            printf("Let's go again!\n\n");}
        if (choice == '3'){
            printf("Please give triangles's first vertical side length:\n");
            scanf(" %f", &sidea);
            printf("Please give triangles's second vertical side length:\n");
            scanf(" %f", &sideb);
            printf("The Right Triangle's perimeter is: %0.3f\n", tria (sidea,sideb));
            printf("Let's go again!\n\n");}
        if (choice == '4'){
            printf("Please give circle's radius:\n");
            scanf(" %f", &rad);
            printf("The circle's perimeter is: %0.3f\n", circle(rad));
            printf("Let's go again!\n\n");}
    } while (choice != '0');

    printf("\nThank you. Goodbye!\n"); /*Τελικό μήνυμα μετά την έξοδο*/

return 0;
}
