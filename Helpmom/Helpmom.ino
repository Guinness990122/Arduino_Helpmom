#include <SoftwareSerial.h>

#define pinRX 12          //rx pin 번호
#define pinTX 13          //tx pin 번호 
#define pinBuzzer 6             //부저가 연결된 pin 번호
SoftwareSerial swSerial(pinRX, pinTX);  //블루투스와 연결

int TrigPin = 9;
int EchoPin  = 8;
int state = 1; // state of buzzer, 1: on 0: off  
char rcv_data;
float duration;
float distance;
float empty_distance = 30.0;
 
void setup() {
  Serial.begin(9600);
  swSerial.begin(9600); // 통신속도는 9600으로 한다.
  pinMode(pinBuzzer,OUTPUT);
  pinMode(TrigPin, OUTPUT); 
  pinMode(EchoPin, INPUT);

}
 
void loop() {  
digitalWrite(TrigPin, HIGH); 
delay(10);  
digitalWrite(TrigPin, LOW);  
duration = pulseIn(EchoPin, HIGH) / 58.0; 
distance = (float(duration * 100.0)) / 100.0; 
Serial.print(distance); 
Serial.print("cm"); 
Serial.println(); 
  
    if(state==1 && distance < empty_distance){
      tone(pinBuzzer, 262, 500);
      delay(100);
      tone(pinBuzzer, 294, 500);
      delay(100);
   }
  if(swSerial.available()) { // 만약 블루투스에서 온 데이터가 있다면 아래 구문을 실행
    rcv_data = swSerial.read();     // 블루투스에서 온 값을 data에 저장
    switch(rcv_data){
      case '1':   //스마트폰 정보가 1이면 부저 활성화
        state = 1;
        digitalWrite(pinBuzzer, HIGH);
        break;
      case '0':             // 스마트폰에서 온 정보가 0이라면 부저 비활성화.
        state = 0 ;
        digitalWrite(pinBuzzer, LOW);   
        break;
    }
  }     
  delay(500);
}
