
 #include "FastLED.h"
 
 #define NUM_STRIP 8                 // количество лент
 #define NUM_LEDS 36                  // количество светодиодов в каждой ленте
 #define NUM_METEORS 10               // длина МЕТЕОРА
 #define INCREASE_BRIGHTNESS (256/NUM_METEORS)
 #define TIME_MIN 5                   // максимальная скорость метеора
 #define TIME_MAX 10                  // минимальная скорость метеора
 
 #define DATA_PIN1 2                  // ноги по АРДУИНО ПРО МИНИ для каждой ленты
 #define DATA_PIN2 3                  // подключать через резистор 470 Ом
 #define DATA_PIN3 4                  // питание лент от отдельного стабилизированного
 #define DATA_PIN4 5                  // источника постоянного напряжения 5V
 #define DATA_PIN5 6                  // Земля общая с блоком питания Ардуино
 #define DATA_PIN6 7                  //
 #define DATA_PIN7 8                  // ВНИМАНИЕ: потребление каждого кусочка ленты
 #define DATA_PIN8 9                  // из 20 светтодиодов = 6 Ватт (ток 1,2А на канал)
 #define PIN_TRIG 12
 #define PIN_ECHO 11


 
 CRGB leds1[NUM_LEDS];                // первая лента
 CRGB leds2[NUM_LEDS];                // вторая лента
 CRGB leds3[NUM_LEDS];                // третья лента
 CRGB leds4[NUM_LEDS];                // четвертая лента
 CRGB leds5[NUM_LEDS];                // пятая лента
 CRGB leds6[NUM_LEDS];                // шестая лента
 CRGB leds7[NUM_LEDS];                // седьмая лента
 CRGB leds8[NUM_LEDS];                // восьмая лента

  
 CRGB meteors[NUM_METEORS];           // метеор
 CRGB etalone[NUM_METEORS+NUM_LEDS];  // эталонный массив метеор+лента
 CRGB rabochiy[NUM_METEORS+NUM_LEDS];
 CRGB cloud[8];// рабочий массив для расчета лент
 byte LENTA[NUM_STRIP];               // массив признаков работы лент (1-выполняется метеор, 0-выкл)
 byte PHASE[NUM_STRIP];               // массив значений состояния сдвига для каждой ленты 0 - NUM_METEORS+NUM_LEDS
 byte PAUSE[NUM_STRIP];               // массив значений циклов задержки между метеорами для каждой ленты
 byte COLOR[NUM_STRIP];               // массив значений цвета лент

 int theme = 10;
 int i,j,n = 0;
 int HSV, STAY_TIME;                  // цвет и скорость метеора если число + то скорость -
 float cm;
 float temp;

void setup() { 
   //  pinMode( POWER_PIN, OUTPUT );
   //  digitalWrite( A0, HIGH );
   //  delay(2000);  
   Serial.begin(9600);  
   pinMode(PIN_TRIG, OUTPUT);  
   pinMode(PIN_ECHO, INPUT); 
   FastLED.addLeds<WS2812B, DATA_PIN1>(leds1, NUM_LEDS);
   FastLED.addLeds<WS2812B, DATA_PIN2>(leds2, NUM_LEDS);
   FastLED.addLeds<WS2812B, DATA_PIN3>(leds3, NUM_LEDS);
   FastLED.addLeds<WS2812B, DATA_PIN4>(leds4, NUM_LEDS);
   FastLED.addLeds<WS2812B, DATA_PIN5>(leds5, NUM_LEDS);
   FastLED.addLeds<WS2812B, DATA_PIN6>(leds6, NUM_LEDS);
   FastLED.addLeds<WS2812B, DATA_PIN7>(leds7, NUM_LEDS);
   FastLED.addLeds<WS2812B, DATA_PIN8>(leds8, NUM_LEDS);

   pinMode( A0, INPUT);
   pinMode( A1, INPUT);
   pinMode( A2, INPUT_PULLUP);
   HSV = GETCOLOR();
   STAY_TIME = map(analogRead(A1), 0, 1023, TIME_MIN, TIME_MAX);

   for ( i = 0; i < NUM_STRIP; i++) {
   LENTA[i] = 1;
   PHASE[i] = 0;
   PAUSE[i] = 0;
   COLOR[i] = HSV;}
   
}
 
 
void loop() {
    
     cloud[0].setHSV( COLOR[0], 255, 80 );
     cloud[1].setHSV( COLOR[1], 255, 80 );
     cloud[2].setHSV( COLOR[2], 255, 80 );
     cloud[3].setHSV( COLOR[3], 255, 80 );
     cloud[4].setHSV( COLOR[4], 255, 80 );
     cloud[5].setHSV( COLOR[5], 255, 80 );
     cloud[6].setHSV( COLOR[6], 255, 80 );
     cloud[7].setHSV( COLOR[7], 255, 80 );

    for(i=0;i<=4;i++){
     leds1[i]=(cloud[0]);
     leds2[i]=cloud[1];
     leds3[i]=cloud[2];
     leds4[i]=cloud[3];
     leds5[i]=cloud[4];
     leds6[i]=cloud[5];
     leds7[i]=cloud[6];
     leds8[i]=cloud[7];
     }
     //for( i = 50; i < 256; i += INCREASE_BRIGHTNESS )
   //breathe_light(1);
   leds1[random(0,5)] *= 2;
   leds1[random(0,5)] *= 2.5;
   leds1[random(0,5)] /= 2.5;
   leds1[random(0,5)] /= 2;
      leds2[random(0,5)] *= 2;
   leds2[random(0,5)] *= 2.5;
   leds2[random(0,5)] /= 2.5;
   leds2[random(0,5)] /= 2;
      leds3[random(0,5)] *= 2;
   leds3[random(0,5)] *= 2.5;
   leds3[random(0,5)] /= 2.5;
   leds3[random(0,5)] /= 2;
      leds4[random(0,5)] *= 2;
   leds4[random(0,5)] *= 2.5;
   leds4[random(0,5)] /= 2.5;
   leds4[random(0,5)] /= 2;
      leds5[random(0,5)] *= 2;
   leds5[random(0,5)] *= 2.5;
   leds5[random(0,5)] /= 2.5;
   leds5[random(0,5)] /= 2;
      leds6[random(0,5)] *= 2;
   leds6[random(0,5)] *= 2.5;
   leds6[random(0,5)] /= 2.5;
   leds6[random(0,5)] /= 2;
      leds7[random(0,5)] *= 2;
   leds7[random(0,5)] *= 2.5;
   leds7[random(0,5)] /= 2.5;
   leds7[random(0,5)] /= 2;
      leds8[random(0,5)] *= 2;
   leds8[random(0,5)] *= 2.5;
   leds8[random(0,5)] /= 2.5;
   leds8[random(0,5)] /= 2;
  
    for(int i=35;i>=31;i--){
     leds1[i]=(cloud[0]);
     leds2[i]=cloud[1];
     leds3[i]=cloud[2];
     leds4[i]=cloud[3];
     leds5[i]=cloud[4];
     leds6[i]=cloud[5];
     leds7[i]=cloud[6];
     leds8[i]=cloud[7];
    }
   leds1[random(31,35)] /= 2.5;
   leds1[random(31,35)] *= 2.5;
   leds1[random(31,35)] *= 2;
   leds1[random(31,35)] /= 2;
      leds2[random(31,35)] /= 2.5;
   leds2[random(31,35)] *= 2.5;
   leds2[random(31,35)] *= 2;
   leds2[random(31,35)] /= 2;
      leds3[random(31,35)] /= 2.5;
   leds3[random(31,35)] *= 2.5;
   leds3[random(31,35)] *= 2;
   leds3[random(31,35)] /= 2;
      leds4[random(31,35)] /= 2.5;
   leds4[random(31,35)] *= 2.5;
   leds4[random(31,35)] *= 2;
   leds4[random(31,35)] /= 2;
      leds5[random(31,35)] /= 2.5;
   leds5[random(31,35)] *= 2.5;
   leds5[random(31,35)] *= 2;
   leds5[random(31,35)] /= 2;
      leds6[random(31,35)] /= 2.5;
   leds6[random(31,35)] *= 2.5;
   leds6[random(31,35)] *= 2;
   leds6[random(31,35)] /= 2;
      leds7[random(31,35)] /= 2.5;
   leds7[random(31,35)] *= 2.5;
   leds7[random(31,35)] *= 2;
   leds7[random(31,35)] /= 2;
      leds8[random(31,35)] /= 2.5;
   leds8[random(31,35)] *= 2.5;
   leds8[random(31,35)] *= 2;
   leds8[random(31,35)] /= 2;


  digitalWrite(PIN_TRIG, LOW);
  //delayMicroseconds(2);
  digitalWrite(PIN_TRIG, HIGH);
  //delayMicroseconds(10);
  digitalWrite(PIN_TRIG, LOW);

  temp = float(pulseIn(PIN_ECHO, HIGH));
  cm = (temp * 17 )/1000;
  
  Serial.println(cm);
  if(cm<=10){
   for ( n = 0; n < NUM_STRIP; n++) 
   {                  
   if ( LENTA[n] == 1) {                            // если на ленте есть МЕТЕОР то обрабатываем
   
     if ( PHASE[n] == (NUM_LEDS+NUM_METEORS)){      // если МЕТЕОР "вылетел" то
         PHASE[n] = 0;                                 // сброс ленты на НОЛЬ
         LENTA[n] = 0;                                 // выключение ленты  
         if (digitalRead(A2)==HIGH) {                // если тумблер выключен, то работаем с резистором цвета
            HSV = GETCOLOR();                         // подготовка нового цвета к следующему включению
            COLOR[n] = random(HSV-5,HSV+5);
          }          // и установка коридора флюктуации цвета
         else {COLOR[n]++;}                          // если тумблер включен, то плавно меняем цвет        
         PAUSE[n] = random(5,30); 
      }                   // и задание паузы до следующего включения (в циклах)
      
   SHIFT_UP(n,PHASE[n]);
   delay(2);
   PHASE[n]++;
   }                                     // и сдвигаем фазу
   
   if (LENTA[n]==0) {                               // Если лента выключена
      if (PAUSE[n]>0) PAUSE[n]--;                   // то считаем длительность паузы
        if (PAUSE[n]==0) LENTA[n]=1;}               // и по окончании включаем ленту снова
  

   FastLED.show();                                  // засветка лвсех лент
 
   } // снятие показателя задержки
                              // задержка по уровню скорости МЕТЕОРА
  }
   
   else{
    for ( n = 0; n < NUM_STRIP; n++) 
   {                  
   if ( LENTA[n] == 1) {                            // если на ленте есть МЕТЕОР то обрабатываем
   
     if ( PHASE[n] == (NUM_LEDS+NUM_METEORS)){      // если МЕТЕОР "вылетел" то
      PHASE[n] = 0;                                 // сброс ленты на НОЛЬ
      LENTA[n] = 0;                                 // выключение ленты  
        if (digitalRead(A2)==HIGH) {                // если тумблер выключен, то работаем с резистором цвета
          HSV = GETCOLOR();                         // подготовка нового цвета к следующему включению
          COLOR[n] = random(HSV-5,HSV+5);}          // и установка коридора флюктуации цвета
        else {COLOR[n]++;}                          // если тумблер включен, то плавно меняем цвет        
      PAUSE[n] = random(5,20); }                   // и задание паузы до следующего включения (в циклах)
      
   SHIFT_DOWN(n,PHASE[n]);
   delay(5);
   
   PHASE[n]++;}                                     // и сдвигаем фазу
   
   if (LENTA[n]==0) {                               // Если лента выключена
      if (PAUSE[n]>0) PAUSE[n]--;                   // то считаем длительность паузы
        if (PAUSE[n]==0) LENTA[n]=1;}               // и по окончании включаем ленту снова
   FastLED.show();                                  // засветка лвсех лент
  
   } // снятие показателя задержки                

   }
   
}

int breathe_light(int led){

   if(led==1){
      for(i=0;i<6;i++){
         leds1[random(0,6)].addToRGB(5);
         leds1[random(0,6)].addToRGB(5);
         leds1[random(0,6)].addToRGB(5);
         leds1[random(31,36)].addToRGB(5);
         leds1[random(31,36)].addToRGB(5);
         leds1[random(31,36)].addToRGB(5);
         delay(2);
      }
      for(i=0;i<6;i++){
         leds1[random(0,6)].subtractFromRGB(5);
         leds1[random(0,6)].subtractFromRGB(5);
         leds1[random(0,6)].subtractFromRGB(5);
         leds1[random(31,36)].subtractFromRGB(5);
         leds1[random(31,36)].subtractFromRGB(5);
         leds1[random(31,36)].subtractFromRGB(5);
         delay(2);
      }
   }
}

// Подпрограмма настройки диапазона цвета метеора по регулятору, подключенному к A0
int GETCOLOR()
   {
   theme += 2;
   theme %= 255;
   // цветовой ряд HSV описывается в диапазоне от 0 до 255
   return random(theme-2,theme+2);                                      // поскольку корридор +-45 то масштабирование аналогового входа
   }                                                // делается в диапазоне от 45 до 315


// подпрограмма формирование метеора заданной длины и цвета и заливка его в эталонный массив
void METEOR(int color)
   {
   i = 0;
   j = 0;
   for( i = INCREASE_BRIGHTNESS-1; i < 256; i += INCREASE_BRIGHTNESS ){
     meteors[j].setHSV( color, 255, i );
     meteors[j++] += CRGB(0,0,20);
    }     // создание МЕТЕОРА
                                          // заданного цвета
   for( i = 0; i < NUM_METEORS ; i++)                                         // и сброс его в эталонный массив
      etalone[i] = meteors[i];
   for( i = NUM_METEORS; i < (NUM_LEDS + NUM_METEORS); i ++ )                // остальное заполняем "черным"
      etalone[i] = CRGB::Black;
   }
   

// подпрограмма копирования эталонного массива со сдвигом в рабочую область   
void SHIFT_DOWN(int LED, int shift)
   {
   // подготовка своего цвета для каждой ленты
   if (LED==0) METEOR(COLOR[0]);        
   if (LED==1) METEOR(COLOR[1]);
   if (LED==2) METEOR(COLOR[2]);
   if (LED==3) METEOR(COLOR[3]);
   if (LED==4) METEOR(COLOR[4]);
   if (LED==5) METEOR(COLOR[5]);
   if (LED==6) METEOR(COLOR[6]);
   if (LED==7) METEOR(COLOR[7]);


   for(i=0;i<NUM_LEDS+NUM_METEORS-shift;i++)
      rabochiy[i] = etalone[NUM_LEDS+NUM_METEORS-shift-i];
   for(i=NUM_LEDS+NUM_METEORS-shift;i<NUM_LEDS+NUM_METEORS;i++)
      rabochiy[i] = CRGB::Black;
   // и заливаем его на соответствующую ленту
   if (LED==0)   for( i = 5; i < NUM_LEDS-5; i++ ) leds1[i] = rabochiy[i]; 
   if (LED==1)   for( i = 5; i < NUM_LEDS-5; i++ ) leds2[i] = rabochiy[i]; 
   if (LED==2)   for( i = 5; i < NUM_LEDS-5; i++ ) leds3[i] = rabochiy[i]; 
   if (LED==3)   for( i = 5; i < NUM_LEDS-5; i++ ) leds4[i] = rabochiy[i]; 
   if (LED==4)   for( i = 5; i < NUM_LEDS-5; i++ ) leds5[i] = rabochiy[i]; 
   if (LED==5)   for( i = 5; i < NUM_LEDS-5; i++ ) leds6[i] = rabochiy[i]; 
   if (LED==6)   for( i = 5; i < NUM_LEDS-5; i++ ) leds7[i] = rabochiy[i]; 
   if (LED==7)   for( i = 5; i < NUM_LEDS-5; i++ ) leds8[i] = rabochiy[i]; 

   }

void SHIFT_UP(int LED, int shift)
   {
   // подготовка своего цвета для каждой ленты
   if (LED==0) METEOR(COLOR[0]);        
   if (LED==1) METEOR(COLOR[1]);
   if (LED==2) METEOR(COLOR[2]);
   if (LED==3) METEOR(COLOR[3]);
   if (LED==4) METEOR(COLOR[4]);
   if (LED==5) METEOR(COLOR[5]);
   if (LED==6) METEOR(COLOR[6]);
   if (LED==7) METEOR(COLOR[7]);
   if (LED==8) METEOR(COLOR[8]);
   if (LED==9) METEOR(COLOR[9]);
   if (LED==10) METEOR(COLOR[10]);
   if (LED==11) METEOR(COLOR[11]);
    
   // переписываем эталон с указанным сдвигом в рабочий массив      
   for( i = (NUM_LEDS+NUM_METEORS-1); i > shift; i-- ) 
   rabochiy[i] = etalone[i-shift];
   for ( i = shift; i > 0; i--)
   rabochiy[i] = CRGB::Black;
   
   // и заливаем его на соответствующую ленту
   if (LED==0)   for( i = 5; i < NUM_LEDS-5; i++ ) leds1[i] = rabochiy[i+NUM_METEORS];    
   if (LED==1)   for( i = 5; i < NUM_LEDS-5; i++ ) leds2[i] = rabochiy[i+NUM_METEORS];
   if (LED==2)   for( i = 5; i < NUM_LEDS-5; i++ ) leds3[i] = rabochiy[i+NUM_METEORS]; 
   if (LED==3)   for( i = 5; i < NUM_LEDS-5; i++ ) leds4[i] = rabochiy[i+NUM_METEORS]; 
   if (LED==4)   for( i = 5; i < NUM_LEDS-5; i++ ) leds5[i] = rabochiy[i+NUM_METEORS]; 
   if (LED==5)   for( i = 5; i < NUM_LEDS-5; i++ ) leds6[i] = rabochiy[i+NUM_METEORS]; 
   if (LED==6)   for( i = 5; i < NUM_LEDS-5; i++ ) leds7[i] = rabochiy[i+NUM_METEORS]; 
   if (LED==7)   for( i = 5; i < NUM_LEDS-5; i++ ) leds8[i] = rabochiy[i+NUM_METEORS]; 
  
   }
