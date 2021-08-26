/***********************************************************************
 * Programa que calcula mediante el metodo de regresion
 * lineal los parametros a y b de la recta y=a+bx
 * El programa lee el archivo data.txt que tiene un formato CSV para
 * separar los datos x y y. 
 * Autor: Ernesto Carrillo
 * *********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char linea[100], ch, numero1[50], numero2[50];
    int linesCount,i,j=0,k=0;
    double  sumX=0, sumX2=0, sumY=0, sumXY=0, a, b;
    double *x, *y;

    /*Apuntador *datos al primer caracter del archivo data.txt*/
    FILE *datos=fopen("data.txt","r");

    /*Esta seccion contabiliza el numero de lineas del archivo data.txt
    para estimar asi el numero de pares de datos x,y con los que se va a realizar la 
    regresion, el numero de lineas se almacena en la variable linesCount y al finalizar
    el conteo se regresa a la posici[on 1 del archivo data.txt*/
    while((ch=fgetc(datos))!=EOF) {
      if(ch=='\n')
         linesCount++;
    }
    rewind(datos);

    /*Arreglos X y X de tamano dinamico*/
    x  = (double *)malloc(linesCount * sizeof(double));
    y  = (double *)malloc(linesCount * sizeof(double));

    /* Leemos linea por linea el archivo data.txt, durante cada lectura la linea se separa en dos cadenas de caracteres
    , numero 1 y numero2 al finalizar la lectura de una linea las cadenas numero 1 y numero 2 son convertidas a numeros tipo 
    double y almacenados en los arreglos x y y*/
    for (i = 0; i < linesCount; i++)
    {
        fgets(linea,100,datos);
        j=0;
        /*Se busca en la cadena caracteres 'linea' el caracter ',' que indica la separacion de los datos, durante el recorrido se
        asignan los caracteres leidos a la cadena numero1*/
        while (linea[j]!=',')
        {
            numero1[j]=linea[j];
            j++;
        }
        k=0;
        j++;
        /*Una vez encontrada la cadena asociada al numero1, se continua la busqueda del caracter '\n' que indica el fin del segundo numero,
        durante el recorrido de busqueda en linea, se van asignando los caracteres al arreglo numero2*/
        while (linea[j]!='\n')
        {
            numero2[k]=linea[j];
            j++;
            k++;
        }
        /*Las cadenas numero1 y numero2 son convertidas a numeros flotantes y se agregan a los arreglos x y y respectivamente*/
        x[i] = atof(numero1);
        y[i] = atof(numero2);
    }

    /* x y y contienen los datos en formato double y con ellos se procede a calcular las sumatorias necesarias
    para la regresion lineal, se recorren los arreglos x y y desde la localidad 0 hasta la localidad lonesCount*/
    for(i = 0; i < linesCount; i++)
    {
        sumX = sumX + x[i];
        sumX2 = sumX2 + x[i]*x[i];
        sumY = sumY + y[i];
        sumXY = sumXY + x[i]*y[i];
    }
     
    /* Con las sumatorias calculadas se procede a obtener el valor de b y a*/
    b = (linesCount*sumXY-sumX*sumY)/(linesCount*sumX2-sumX*sumX);
    a = (sumY - b*sumX)/linesCount;

    /*Al finalizar el progama se imprime en pantana los valores a y b obtenidos por el metodo de regresion */
    printf("Los resultados son: a=%0.3f y b = %0.3f",a,b);
    printf("\nLa ecuacion lineal es: y = %0.3f + %0.3fx",a,b);
    
    /*Se cierrra el archivo apuntado por *datos, en otras palabras el archivo datos..txt*/
    fclose(datos);
    return 0;
}