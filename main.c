#include <msp430.h> 
#include <stdbool.h>

//defines leds
//(Name = Player Number + Spot (1-9) number)
//Player 1 (Pin 1.1 - 1.7 & Pin 2.0 - 2.1)
//Pin 1
#define P1S1 BIT1
#define P1S2 BIT2
#define P1S3 BIT3
#define P1S4 BIT4
#define P1S5 BIT5
#define P1S6 BIT6
#define P1S7 BIT7
//Pin 2
#define P1S8 BIT0
#define P1S9 BIT1

//Player 2 (Pin 6.0 - 6.4 & Pin 4.0, 4.4, 4.6, 4.7)
//Pin 6
#define P2S1 BIT0
#define P2S2 BIT1
#define P2S3 BIT2
#define P2S4 BIT3
#define P2S5 BIT4
//Pin 4
#define P2S6 BIT0
#define P2S7 BIT4
#define P2S8 BIT6
#define P2S9 BIT7

//Sets output for p1 bit 1-7
#define SETP1(a, b, c ,d ,e ,f, h) (P1DIR |= ((a) | (b) | (c)| (d) | (e) | (f) | (h)))
//Sets output for p2 bit 8-9
#define SETP2(a, b) (P2DIR |= ((a) | (b)))


//Sets output for p6 bit 1-5
#define SETP6(a, b, c, d, e) (P6DIR |= ((a) | (b) | (c) | (d)))
//Sets output for p4 bit 6-9
#define SETP4(a, b, c, d) (P4DIR |= ((a) | (b) | (c)))



//Player 1 spots 1-9 are covered by pins 1 and 2 P2.3 is unused
#define ONP1(x) (P1OUT |= (x))
#define OFFP1(x) (P1OUT &= ~(x))
#define ONP2(x) (P2OUT |= (x))
#define OFFP2(x) (P2OUT &= ~(x))

//Player 2 spots 1-9 are covered by pin 6 (bit 0-5) and pin 4 (bit 0 & 4 & 6 - 7)
#define ONP4(x) (P4OUT |= (x))
#define OFFP4(x) (P4OUT &= ~(x))
#define ONP6(x) (P6OUT |= (x))
#define OFFP6(x) (P6OUT &= ~(x))


void setup();
void allOff();


volatile int p1pos = 0;
volatile int p2pos = 0;
bool confrim = false;

int main(void)
{
    //bool gameOver = 0;
    //bool player = 0;      // 0 is player one, 1 is player two

    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer

    __enable_interrupt();

    setup();

    //ONP1(P1S7);
    while (1){
        allOff();
        //player 1 led pos logic
        if(p1pos < 1){
            p1pos = 1;
        }
        if(p1pos > 9){
            p1pos = 9;
        }
        switch(p1pos){
        case 1:
            ONP1(P1S1);
            break;
        case 2:
            ONP1(P1S2);
            break;
        case 3:
            ONP1(P1S3);
            break;
        case 4:
            ONP1(P1S4);
            break;
        case 5:
            ONP1(P1S5);
            break;
        case 6:
            ONP1(P1S6);
            break;
        case 7:
            ONP1(P1S7);
            break;
        case 8:
            ONP2(P1S8);
            break;
        case 9:
            ONP2(P1S9);
            break;
        }

        //player 2 led pos logic
        if(p2pos < 1){
            p2pos = 1;
        }
        if(p2pos > 9){
            p2pos = 9;
        }
        switch(p2pos){
        case 1:
            ONP6(P2S1);
            break;
        case 2:
            ONP6(P2S2);
            break;
        case 3:
            ONP6(P2S3);
            break;
        case 4:
            ONP6(P2S4);
            break;
        case 5:
            ONP6(P2S5);
            break;
        case 6:
            ONP4(P2S6);
            break;
        case 7:
            ONP4(P2S7);
            break;
        case 8:
            ONP4(P2S8);
            break;
        case 9:
            ONP4(P2S9);
            break;
        }


        //if (gameOver == 0){

        //}
        //else{

        //}
    }
    return 0;
}
void setup(){

    PM5CTL0 &= ~LOCKLPM5;

    //Set output
    SETP1(P1S1, P1S2, P1S3, P1S4, P1S5, P1S6, P1S7);
    SETP2(P1S8, P1S9);

    SETP6(P2S1, P2S2, P2S3, P2S4, P2S5);
    SETP4(P2S6, P2S7, P2S8, P2S9);


    //Button Pin 3.1
    P3DIR |= ~BIT1;
    P3OUT |= BIT1;
    P3IES |= BIT1;
    P3IFG &= ~BIT1;
    P3IE |= BIT1;

    //Button Pin 3.2
    P3DIR |= ~BIT2;
    P3OUT |= BIT2;
    P3IES |= BIT2;
    P3IFG &= ~BIT2;
    P3IE |= BIT2;

    //Button Pin 3.3
    P3DIR |= ~BIT3;
    P3OUT |= BIT3;
    P3IES |= BIT3;
    P3IFG &= ~BIT3;
    P3IE |= BIT3;

    //Button Pin 3.4
    P3DIR |= ~BIT4;
    P3OUT |= BIT4;
    P3IES |= BIT4;
    P3IFG &= ~BIT4;
    P3IE |= BIT4;

    //Button Pin 3.5
    P3DIR |= ~BIT5;
    P3OUT |= BIT5;
    P3IES |= BIT5;
    P3IFG &= ~BIT5;
    P3IE |= BIT5;

    //Button Pin 3.6
    P3DIR |= ~BIT6;
    P3OUT |= BIT6;
    P3IES |= BIT6;
    P3IFG &= ~BIT6;
    P3IE |= BIT6;


    // Setup Timer0_B   (this was fun, thanks msp430fr2355.h)
    TB0CTL = TBSSEL_1 | CNTL_1 | MC_2 | ID_3 | TBCLR | TBIE;

    /*
        Timer B = ACLK (32khz) | Count (0FFFh) | Continuous mode | Divider (8) | Clear Timer Value | Interrupt Enable (might need to move this later to when the game starts)

        MATH!!!!

        ACLK (32khz) = 32768 | Count (0FFFh) = 4096 | Divider = 8

        Count / (ACLK / Divider)

        4096 / (32768 / 8)

        4096 / 4096 = 1 second ???

    */

    allOff();
}

void allOff(){
    //Player 1
    OFFP1(P1S1);
    OFFP1(P1S2);
    OFFP1(P1S3);
    OFFP1(P1S4);
    OFFP1(P1S5);
    OFFP1(P1S6);
    OFFP1(P1S7);
    OFFP2(P1S8);
    OFFP2(P1S9);

    //Player 2
    OFFP6(P2S1);
    OFFP6(P2S2);
    OFFP6(P2S3);
    OFFP6(P2S4);
    OFFP6(P2S5);
    OFFP4(P2S6);
    OFFP4(P2S7);
    OFFP4(P2S8);
    OFFP4(P2S9);
}

// Pin 3 button interrupts bit 1-6
#pragma vector = PORT3_VECTOR;
__interrupt void P5_ISR(void){
    if (P3IFG & BIT1){
        p1pos++;         // increment position on the board (no variable yet)
        P3IFG &= ~BIT1;
    }
    if (P3IFG & BIT2){
        p1pos--;
        P3IFG &= ~BIT2;
    }
    if (P3IFG & BIT3){
        confrim = true;
        P3IFG &= ~BIT3;
    }
    if (P3IFG & BIT4){
        p2pos--;
        P3IFG &= ~BIT4;
    }
    if (P3IFG & BIT5){
        p2pos--;
        P3IFG &= ~BIT6;
    }
    if (P3IFG & BIT6){
        confrim = true;
        P3IFG &= ~BIT6;
    }
}

// Timer0_B interrupt
#pragma vector = TIMER0_B1_VECTOR
__interrupt void ISR_TB0_Overflow(void){

   // add code here later for when 1 second happens

   TB0CTL &= ~TBIFG;             // Clear IRQ Flag
}
