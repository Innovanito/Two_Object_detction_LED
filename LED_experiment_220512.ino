#include <Pixy2.h>

#define LED_R 13
#define LED_G 7

#define Sig_1 1
#define Sig_2 3

#define Size_1 80
#define Size_2 30

#define delayTime_1 20
#define delayTime_2 80

Pixy2 pixy;

void setup()
{
  Serial.begin(115200);
  Serial.print("Starting...\n");

  pixy.init();

  pinMode(LED_R, OUTPUT); // to set the OUTPUT mode of pin number 13.
  pinMode(LED_G, OUTPUT); // to set the OUTPUT mode of pin number 7.
}

void loop()
{
  // put your main code here, to run repeatedly:

  int i;
  pixy.ccc.getBlocks();

  if (pixy.ccc.numBlocks)
  {
    Serial.print("Object detected ");
    Serial.print(pixy.ccc.numBlocks);
    Serial.print("\n");

    for (i = 0; i < pixy.ccc.numBlocks; i++)
    {
      Serial.print("  block");
      Serial.print(i);
      Serial.print(": ");
      pixy.ccc.blocks[i].print();
    }

    // 사물이 계속 인식될 때 LED를 초기화 해주는 단
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);

    for (i = 0; i < pixy.ccc.numBlocks; i++)
    {
      if (pixy.ccc.blocks[i].m_signature == Sig_1)
      {
        // if the object_1's width value is greater than Size_1, LED_G blink faster
        if (pixy.ccc.blocks[i].m_width > Size_1)
        {
          digitalWrite(LED_G, HIGH);
          delay(delayTime_1);
          digitalWrite(LED_G, LOW);
          delay(delayTime_1);
        }
        else
        {
          digitalWrite(LED_G, HIGH);
          delay(delayTime_2);
          digitalWrite(LED_G, LOW);
          delay(delayTime_2);
        }
      }
      else if (pixy.ccc.blocks[i].m_signature == Sig_2)
      {
        // if the object_2's width value is greater than Size_2, LED_R blink faster
        if (pixy.ccc.blocks[i].m_width > Size_2)
        {
          digitalWrite(LED_R, HIGH);
          delay(delayTime_1);
          digitalWrite(LED_R, LOW);
          delay(delayTime_1);
        }
        else
        {
          digitalWrite(LED_R, HIGH);
          delay(delayTime_2);
          digitalWrite(LED_R, LOW);
          delay(delayTime_2);
        }
      }
    }
  }
  else
  {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
  }
}