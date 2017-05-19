//*************************************************************
//*** ���50 "������� ������������� �� ������ ��� ���������" ***
//***                ������� �01 - ���� 2                   ***
//***                                                       ***
//***                   ��.���� 2016-17                     ***
//***                ��������: �������� ������              ***
//***                     AM: 123542                        ***
//*************************************************************

#include <stdio.h>  /*��� ������������ ��� ��� printf() ��� scanf()*/
#include <math.h>   /*��� ������������ ��� ��� sqrt()*/

/*��������� ��� ��������� � �� ��������� ��� ��� ������� ���� ���������� <math.h>
��� �� ������������� ��� � ������� �� ������� ��� ������������ ������������*/
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/*����������� ����������� ���������� ��� �� ���� �����*/

/*��� �� ���������*/
float square (float a){
    return 4*a
}

/*���������������*/
float paral (float a, float b){
    return 2*a+2*b;}

/*�������*/
float tria (float a, float b){
    return a+b+sqrt(a*a+b*b);
}

/*�����*/
float circle (float a){
    return 2*M_PI*a
}

/*�� ����� ��� ���������, ������� ��� ������� ��� ����� ������� ��� ���������� ���������*/
int main()
{
/*������ ��������*/
    char choice; /*����� ��������� ��� ��� ������� ��� �����*/
    float side,width,sidea,sideb,rad; /*�������� ��� ��� ���������� ��� ����������*/

    do {
        printf("\t*Menu*\nPlease choose:\n");
        printf("1.Square\n2.Parallelogram\n3.Right triangle\n4.Circle\n0.Exit\n\n");
        scanf(" %c", &choice);          /*������ ��� �� ������ �� �������� ��� �� ����� ��� ������� �� �� ��� ����� �������� ���� ���������� if.
                                          �� ��������� ���������� ���� ��� � ������� ����� 0, ����������� ���������������*/
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

    printf("\nThank you. Goodbye!\n"); /*������ ������ ���� ��� �����*/

return 0;
}
