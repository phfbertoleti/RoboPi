//Codigo-fonte exemplo: Controle do robo
//Descrição: controle do robo (dois conjuntos de motores)
//Autor: Pedro Bertoleti
//Data: Dezembro/2016
//
//Importante: o GND do circuito de driver e da Raspberry Pi devem estar grampeados

#include <stdio.h>    
#include <wiringPi.h> //header para utilizar funções da wiringPi
#include <termios.h>    //termios, TCSANOW, ECHO, ICANON
#include <unistd.h>     //STDIN_FILENO


//defines
//numeros dos dos GPIOs!
#define PINO_OUTPUT_L1  23    //GPIO23
#define PINO_OUTPUT_L2  18    //GPIO18
#define TECLA_FRENTE    'w'
#define TECLA_ESQUERDA  'a' 
#define TECLA_DIREITA   'd' 
#define TECLA_PARAR     's' 
#define TECLA_SAIR      'x'

//variaveis globais

//prototypes
void ConfiguraIOs(void);

/**************
Implementacoes
***************/

//Funcao: configura os GPIO (I/Os) e inicializa motores em estado desligado
//Parâmetros: nenhum
//Retorno: nenhum
void ConfiguraIOs(void)
{
    //configura os I/O (GPIO) 
    pinMode(PINO_OUTPUT_L2, OUTPUT);     
    pinMode(PINO_OUTPUT_L1, OUTPUT);     

    digitalWrite(PINO_OUTPUT_L1, LOW); 
    digitalWrite(PINO_OUTPUT_L2, LOW); 
}

//Programa principal
int main( int argc, char *argv[] )
{
    char TeclaPressionada;
    char DeveSair;
    static struct termios oldt, newt;

    //Inicializacoes
    wiringPiSetupGpio();
    ConfiguraIOs();
    DeveSair=0;

    system("clear");

    printf("---Controle do robo ---\n");
    printf("\n x - Sair");
    printf("\n w - Frente");
    printf("\n a - Esquerda");
    printf("\n d - Direita");
     
    //loop principal   
    while(1)
    {
            //limpa buffer de teclado
            fflush(stdin);

            //obtem a atual configuracao do disp de entrada (teclado)
            tcgetattr( STDIN_FILENO, &oldt);
            newt = oldt;
            
            //reconfigura dispositivo de entrada (teclado) para ler mesmo
            //sem apertar a tecla enter
            newt.c_lflag &= ~(ICANON);
            tcsetattr( STDIN_FILENO, TCSANOW, &newt);

	    //aguarda tecla ser pressionada
            TeclaPressionada = 0;
            TeclaPressionada = getchar(); 

            //restaura as configuracoes do dispositivo de entrada (teclado)
            tcsetattr( STDIN_FILENO, TCSANOW, &oldt);

            //trata tecla
            switch(TeclaPressionada)
	    {
                 case TECLA_FRENTE:
                 {
                     digitalWrite(PINO_OUTPUT_L1, HIGH);   
                     digitalWrite(PINO_OUTPUT_L2, HIGH);			
                     break;
                 }

                 case TECLA_ESQUERDA:
                 {
                     digitalWrite(PINO_OUTPUT_L1, HIGH);   
                     digitalWrite(PINO_OUTPUT_L2, LOW);			
                     break;
                 }


                 case TECLA_DIREITA:
                 {
                     digitalWrite(PINO_OUTPUT_L1, LOW);   
                     digitalWrite(PINO_OUTPUT_L2, HIGH);			
                     break;
                 }


                 case TECLA_PARAR:                 
                 {
                     digitalWrite(PINO_OUTPUT_L1, LOW);   
                     digitalWrite(PINO_OUTPUT_L2, LOW);   
                     break;
                 }

	 	 case TECLA_SAIR:
                 {
                     DeveSair=1;
                     break;
                 } 

                case 0:
                {
                     digitalWrite(PINO_OUTPUT_L1, LOW);   
                     digitalWrite(PINO_OUTPUT_L2, LOW);			
                     break;
                } 

            }

       if (DeveSair == 1)
		return 0;


    }

    return 0;
}
