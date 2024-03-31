#define pot 0
#define BUZZER 1

int latchPin = 8;     //Пин "защелки" первого регистра подключен к ST_CP входу первого регистра отвечающего за сегменты 
int clockPin = 12;    //Пин подключен к SH_CP входу 74HC595
int dataPin = 11;     //Пин подключен к DS входу 74HC595

int TimeLight = 5;  //время для разогрева сегментов
int sensorPin=A0;

byte SegDisplay; // переменная для вывода символов на индикаторе
byte RazrDisplay; // переменная для включения разрядов

// Настройка комбинации для отображения каждого номера на дисплее.
// Комбинация выбрана на основе таблицы отображаемого знака данным порта
// Соответственно { 0 , 1 , 2 , 3 , 4 , 5 , 6 , 7 , 8 , 9 , dp, - }
byte g_digits[12]={192,249,164,176,153,146,130,248,128,144,127,255}; //массив цифр, генерирующий из сегментов цифры
byte g_registerArray[4]={1,2,4,8}; //массив цифр, указывающий разряды


void setup() {
// обозначаем все пины как выходы
  pinMode(latchPin, OUTPUT); 
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
}

void loop() {
  int disp = 0; //создаем переменную для вывода на экран

  int analogueValue = analogRead(sensorPin);  // читаем аналоговый пин A0
  analogueValue = map(analogueValue, 0, 1023, 0, 8888); //преобразуем диапазон с А0 (0-1023) в нужный нам (0-8888)

  disp = analogueValue; // записываем получившуюся после преобразования цифру в переменну для вывода на экран
  
 // Разбиваем цифру по разрядам индикатора
  if (disp < 10) // если наша цифра меньше 10, то
  {
    Indicate(0, 11); // пишем в первый разряд пусто
    Indicate(1, 11); // пишем во второй разряд пусто
    Indicate(2, 11); // пишем в третий разряд пусто
    Indicate(3, disp); // пишем в четвертый разряд нашу цифру
  }
  else if (disp < 100) // если наша цифра меньше 100, то
  {
    Indicate(0, 11); // пишем в первый разряд пусто
    Indicate(1, 11); // пишем во второй разряд пусто
    Indicate(2, disp / 10); // пишем в третий разряд - цифру делёную на 10
    Indicate(3, disp % 10); // пишем в четвертый разряд цифру оставшуюся от деления на 10
/*
 Допустим наша цифра 25. 
  Если мы ее поделим на 10, то у нас получится 2,5. Цифры после запятой, в данном случае,
 у нас не остаются. Таким образом мы имеем в третем разряде цифру 2.
  В чевертый разряд мы, как раз и записываем цифру-остаток полученную в результате деления. 
В нашем случае это и есть та самая 5.
Аналогичным образом разбивается наша цифра и далее.
*/
  }
  else if (disp < 1000)
  {
    Indicate(0, 11);
    Indicate(1, disp / 100);    
    Indicate(2, (disp % 100) / 10);
    Indicate(3, disp % 10); 
  }
  else
  {
    Indicate(0, disp / 1000);
    Indicate(1, (disp % 1000) / 100);    
    Indicate(2, (disp % 100) / 10);
    Indicate(3, disp % 10);
  }
 }

void Indicate(int r,int x)
{
SegDisplay=g_digits[x]; // получаем цифру и выводим символ, из массива цифр, соответствующий этой цифре.
RazrDisplay=g_registerArray[r];  // получаем цифру и выводим номер регистра, из массива цифр, соответствующий этой цифре.
  digitalWrite(latchPin, LOW);  // устанавливаем синхронизацию "защелки" на LOW
      shiftOut(dataPin, clockPin, MSBFIRST, RazrDisplay); // Записываем информацию для второго регистра (Номер разряда)
      shiftOut(dataPin, clockPin, MSBFIRST, SegDisplay);  // Записываем информацию для первого регистра (Номер символа)
  digitalWrite(latchPin, HIGH);  //"защелкиваем" регистр, тем самым устанавливая значения на выходах

   delay(TimeLight); // пауза, чтобы сегменты "разгорелись"
}