//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<math.h>
//
//
//int main(void) {
//     
//    int headW;
//    int headW2;
//    int baseH;
//    int baseW;
//    int i;
//    int ii = 0;
//
//    printf("Enter arrow base height and width: ");
//    scanf("%d %d", &baseH, &baseW);
//
//    printf("Enter arrow head width: ");
//    scanf("%d", &headW);
//
//
//
//    if (headW < baseW) {
//        printf("head width must be > base width\n");
//    }
//    else {
//
//        while (ii < baseH) {
//            
//            
//
//            for (i = 0; i < baseW; ++i) {
//                printf("*");
//            }
//           
//            printf("\n");
//            ii = ii + 1;
//        }
//        ii = 0;
//        headW2 = headW;
//
//        while (ii < headW2) {
//
//            headW = headW - 1;
//
//            for (i = 0; i <= headW; ++i) {
//                printf("*");
//            }
//         
//
//            printf("\n");
//            ii = ii + 1;
//        }
//
//
//    }
//
//   
//
//    return(0);
//}