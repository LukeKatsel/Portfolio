#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<math.h>

#define PI 3.14159265
 
typedef struct Complex_ { 
    double RealPart; 
    double ImagPart; 
} Complex;

Complex read_complex(void);

void print_complex(Complex Z);

Complex add_complex(Complex Z1, Complex Z2);

Complex mul_complex(Complex Z1, Complex Z2);

void par_complex(Complex Z, double* mag_z, double* Angle_z);


int main(void) {
    char op[5];
    Complex num1;
    Complex num2;
    Complex Re;
    int i;
    double mag;
    double angle;


    printf("*** Complex Number Calculator ***\n");

    do {

        printf("\n");
        printf("Enter \"Add\" for addition, \"Mult\" for multiplication, \"MA\" for magnitude and angle, or \"Exit\" to quit: ");
        scanf("%s", op);
        

        if (op[1] == 'd') {

           num1 = read_complex();
           num2 = read_complex();

           Re = add_complex(num1, num2);

           print_complex(num1);
           printf("+");
           print_complex(num2);
           printf("=");
           print_complex(Re);
           printf("\n");

        }

        else if (op[1] == 'u') {

            num1 = read_complex();
            num2 = read_complex();

            Re = mul_complex(num1, num2);

            print_complex(num1);
            printf("*");
            print_complex(num2);
            printf("=");
            print_complex(Re);
            printf("\n");
        }

        else if (op[1] == 'A') {
            
            num1 = read_complex();

            par_complex(num1, &mag, &angle);

            print_complex(num1);
            printf(" has a magnitude of %.3lf at an angle of %.3lf degrees", mag, angle);

        }


    } while (op[1] != 'x');


    return;
}

Complex read_complex(void) {
    Complex t;

    printf("Enter a complex number: ");

    scanf("%lf %lf", &t.RealPart, &t.ImagPart);

    return(t);
}

void print_complex(Complex Z) {

    if (Z.ImagPart > 0) 
        printf("(%.3lf+%.3lfi)", Z.RealPart, Z.ImagPart);

    else if(Z.ImagPart < 0)
        printf("(%.3lf%.3lfi)", Z.RealPart, Z.ImagPart);

    return;
}

Complex add_complex(Complex Z1, Complex Z2) {
    Complex R;

    R.RealPart = Z1.RealPart + Z2.RealPart;
    R.ImagPart = Z1.ImagPart + Z2.ImagPart;

    return(R);
}

Complex mul_complex(Complex Z1, Complex Z2) {
    Complex R;

    R.RealPart = (Z1.RealPart * Z2.RealPart) - (Z1.ImagPart * Z2.ImagPart);
    R.ImagPart = (Z1.RealPart * Z2.ImagPart) + (Z1.ImagPart * Z2.RealPart);

    return(R);
}

void par_complex(Complex Z, double* mag_z, double* Angle_z) {
    double tempmag;
    double tempangle;
    double temp;

    temp = pow(Z.RealPart, 2) + pow(Z.ImagPart, 2);
    tempmag = abs(sqrt(temp));
    tempangle = atan2(Z.ImagPart, Z.RealPart);


    *Angle_z = tempangle * 180 / PI;
    *mag_z = tempmag;

    return;
}
