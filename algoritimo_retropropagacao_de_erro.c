#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define ncesc  4
#define entrada 4
#define saida 2
#define exemplos 10


void main(){
 float w[saida][ncesc];
 float W[ncesc][entrada];
 float errodes;
 float Erroinst;
 float Erromg = 0;
 float erro[saida];
 float niesc[ncesc];
 float ni[saida];
 float biascec[ncesc];
 float biass [saida];
 float eta;
 float phiesc [ncesc];
 float phi[saida];
 float philesc[ncesc];
 float phil[saida];
 float delta[saida];
 float deltaesc[ncesc];
 int x;
 int y;
 int cont2;
 int contt;
 int epocas;
 int funcao;
 float entradas[entrada][exemplos];
 float saidas[saida][exemplos];
 system("clear");

 printf("[ 1 ] - Bias e Pesos iniciais: \n");
 for (y = 0 ; y < ncesc; y ++){
   for (x = 0 ; x < saida; x++);
     w[ x ] [ y ] = rand()%2 +.5;
   for (x = 0 ; x < entrada ; x++);
     W[y][x] = rand()%2 + .5;
   biascec[ y ] = rand()%2 + .5;
   }

 for (x = 0 ; x < saida; x++)
   biass[ x ] =  rand()%2 + .5;
 for (y = 0 ; x < saida ; y++)
   printf("[ 2 ] -  Neuronio de saida :\n[ bias ] - %d = %f",y,biass[y]);

 for (y = 0 ; y < ncesc; y++)
   printf("\n[ 2.1 ] - Neuronio da camada oculta:\n[ b ] - %d = %f",y,biass[y]);

 printf("\n\n[ 3 ] - Numeros de epocas de treinamento\n");
 printf("---------------------------------------------------\n");
 scanf("%d", &epocas);
 printf("\n[ 4 ] - Vetores de exemplo de TREINAMENTO de entrada\n");
 printf("---------------------------------------------------\n");
 for(x = 0; x <  entrada; x++)
   for (y = 0 ; y < exemplos; y++)
     scanf("%f", &entradas[x] [y]);
 printf("---------------------------------------------------\n");
 printf("\n[ 5 ] - Vetores de exemplo de TREINAMENTO de saida\n");
 for(x = 0 ; x < saida; x++)
   for(y = 0 ; y < exemplos; y++)
     scanf("%f", &saidas[x] [y]);

 printf("\n\n---------------------------------------------------\n");
 printf("\n[ 6 ] - Taxa de aprendizagem \n");
 scanf("%f", &eta);
 printf("\n---------------------------------------------------\n");
 printf("\n[ 7 ] - Erro toleravel \n");
 scanf("%f", &errodes);
 printf("\n\n---------------------------------------------------\n");
 printf("\n Funcao\n[ 1 ] -Sigmoid\n[ 2 ] - Degrau\n");
 scanf("%d", &funcao);

 system("clear");

 printf("\n\nPesos Iniciais\n");
 for ( y = 0 ; y <  ncesc; y++){
   for( x = 0 ; x < saida; x++)
     printf("w[%d][%d] = %f\n",x,y, w[x] [y]);
   for(x = 0 ; x < entrada ; x++)
     printf("W[%d][%d] = %f\n",x,y, W[x] [y]);
  }
 printf("INICIANDO processo iterativo\n\n");
 for(x = 0 ; x < epocas; x++){
   for(y = 0 ; y < exemplos ; y++){
     for(contt  = 0 ; contt < ncesc; contt++){
       niesc[contt] = 0; //
       for(cont2 = 0 ; cont2 < entrada; cont2++)
         niesc[contt] = niesc[contt] + W[contt] [cont2] * entradas[cont2][y];
       niesc[contt] = niesc[contt] + biascec[contt];
       switch(funcao){
         case 1:
          if (niesc[contt] > 0 ) phiesc[contt] = 1;
          else phiesc[contt] = 0;
          break;
         case 2:
          phiesc[contt]  = 1/ (1 + exp(-niesc[contt]));
          break;
       }
     }

 for( contt = 0 ; contt <  saida; contt++){
   ni[contt] =0;
   for( cont2 = 0 ; cont2 < ncesc; cont2++)
     ni[contt] = ni[contt] + w[contt][cont2] * phiesc[cont2];
   ni[contt] = ni[contt] + biass[contt];
      switch(funcao){
        case 1:
         if (ni[contt] > 0) phi[contt] = 1;
         else phi[contt] = 0;
         break;
       case 2:
        phi[contt] = 1/(1+ exp(-ni[contt]));
        break;
        }
      }



 for(contt = 0 ; contt < saida; contt++){
   erro[contt] = saidas[contt][y] - phi[contt];
 Erroinst = 0;
 for( contt = 0 ; contt < saida;  contt++)
   Erroinst = Erroinst + erro[contt] * erro[contt] / 2;
 Erromg = (Erromg * (x * exemplos + y) + Erroinst) / (x *  exemplos + (y + 1));
 if(Erromg < errodes)
   break;

 for(cont2 = 0 ; cont2 < saida ; cont2++){
   phil[cont2] = exp(- ni[cont2] ) / ((1 + exp(- ni[cont2] )) * (1 +exp(- ni[cont2])));
   delta[cont2] = -erro[cont2] * phil[cont2];
   }

 for(cont2 = 0 ; cont2 < ncesc; cont2++){
   philesc[cont2] = exp(- niesc[cont2]/ ((1 + exp(- niesc[cont2])) * (1 + exp(niesc[cont2]))));
   deltaesc[cont2] = 0;
   for(contt = 0 ; contt < saida ; contt++)
     deltaesc[cont2] = deltaesc[cont2] + philesc[cont2] * delta[contt] * w[contt][cont2];
     }


 for(cont2 = 0 ; cont2 < saida ;  cont2++){
   for(contt = 0 ; contt < ncesc ; contt++)
     w[cont2][contt] = w[cont2][contt] - eta * delta[cont2] * phiesc[contt];

   biass[cont2] = biass[cont2] - eta * delta[cont2] * phiesc[contt];
   }

 for(cont2 = 0 ; cont2 < ncesc ; cont2++){
   for(contt = 0 ; contt < entrada ; contt++)
     W[cont2][contt] = W[cont2][contt] - eta * deltaesc[cont2] * entradas[contt][y];
   biascec[cont2] = biascec[cont2] - eta * delta[cont2] * entradas[contt][y];
   }
  }



 if(Erromg < errodes){
   printf("FINALIZADO, pelo erro em %d epocas de treinamento!\n",x);
   break;

   }
  }


  printf("Bias finais:\n");
 for(y = 0 ; y < ncesc ; y++)
   printf("%f ", biascec[y]);
   printf("\n");
 for(y = 0 ; y < saida; y++)
   printf("%f ",biass[y]);
   printf("\nPeso finais :\n");
 for(y = 0 ; y < ncesc ; y++){
   for(x = 0 ; x < saida; x++)
     printf("w[%d][%d] = %f\n",x,y,w[x] [y]);
   for( x = 0 ; x < entrada ; x++)
     printf("W[%d][%d] = %f\n",x,y,W[y] [x]);
     }


 printf("FINALIZANDO\n\n");

 for(x = 0 ; x < exemplos ;x++){
   printf("\nEntradas :");
   for(y = 0 ; y < entrada ; y++)
    printf("%f",entradas[y][x]);
 printf("\nSaidas esperadas");
 for(y = 0 ; y < saida ; y++)
   printf("%f",saidas[y][x]);
 printf("\nSaidas da rede");
 for(contt = 0 ; contt < ncesc; contt++){
   niesc[contt] = 0;
   for(cont2 = 0 ; cont2 < entrada ; cont2++)
     niesc[contt] = niesc[contt] + W[contt][cont2] * entradas[cont2][x];
 niesc[contt] = niesc[contt] + biascec[contt];

 switch(funcao){
   case 1:
     if (niesc[contt] > 0) phiesc[contt] = 1;
     else phiesc[contt] = 0;
     break;
   case 2:
     phiesc[contt] = 1 / (1 + exp(- niesc[contt]));
     break;
     }
   }


  for(contt = 0 ; contt < saida ; contt++){
    ni[contt] = 0 ;
    for(cont2 = 0 ; cont2 < ncesc ; cont2++)
      ni[contt] = ni[contt] + w[contt][cont2] * phiesc[cont2];
    ni[contt] = ni[contt] + biass[contt];
    switch (funcao){
      case 1:
        if(ni[contt] > 0 ) phi[contt] = 1;
        else phi[contt] = 0 ;
      case 2:
        phi[contt] = 1 / (1 + exp(- ni[contt]));
        break;
        }
    printf("%f",phi[contt]);
    }
   }
   printf("Erro Medio GLOBAL  %f", Erromg);





}

