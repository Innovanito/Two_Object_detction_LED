#include <Pixy2.h>

#define LED_R 13
#define LED_G 7

#define Sig_1 1
#define Sig_2 4

#define Size 100 
Pixy2 pixy;

void setup() {
  Serial.begin(115200);
  Serial.print("Starting...\n");

  pixy.init();

  pinMode ( LED_R, OUTPUT);  // to set the OUTPUT mode of pin number 13.  
  pinMode ( LED_G, OUTPUT);  // to set the OUTPUT mode of pin number 7.  
}

void loop() {
  // put your main code here, to run repeatedly:

  int i;
  pixy.ccc.getBlocks();

  if(pixy.ccc.numBlocks) {
    Serial.print("Object detected ");
    Serial.print(pixy.ccc.numBlocks);
    Serial.print("\n");

    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      Serial.print("  block");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
    }

    // 사물이 계속 인식될 때 LED를 초기화 해주는 단
    digitalWrite (LED_R, LOW); 
    digitalWrite (LED_G, LOW); 
    
    for (i=0; i<pixy.ccc.numBlocks; i++)
    {
      if ( pixy.ccc.blocks[i].m_signature == Sig_1) {
        //if the object's width value is greater than SIZE blink faster
      digitalWrite (LED_G, HIGH);
      }
     else if ( pixy.ccc.blocks[i].m_signature == Sig_2) {
      digitalWrite (LED_R, HIGH);
      }
    }
  }
  else {
    digitalWrite (LED_R, LOW); 
    digitalWrite (LED_G, LOW); 
  }
}
