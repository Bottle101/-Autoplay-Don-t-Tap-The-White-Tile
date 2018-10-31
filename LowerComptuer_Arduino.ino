// Visual Micro is in vMicro>General>Tutorial Mode
// 
/*
    Name:       Piano.ino
    Created:	2018/10/25 15:04:00
    Author:     LAPTOP-LJV5SFTU\ASUS
*/

int i = 0;

void setup()
{
	Serial.begin(115200);
	pinMode(2, OUTPUT);/*4������ˣ��ߵ�λ���£��͵�λ̧��*/
	pinMode(3, OUTPUT);
	pinMode(4, OUTPUT);
	pinMode(5, OUTPUT);

}


void loop()
{
	/*����һ��2��3��4��5������*/
	char agt = Serial.read();
	int wait;

 wait = 15;
	/*switch (i / 100)
	{
	case 0:wait = 15; break;
	case 1:wait = 14; break;
	case 2:wait = 13; break;
	case 3:wait = 12; break;
	case 4:wait = 11; break;
	case 5:wait = 10; break;
	case 6:wait = 9; break;
	case 7:wait = 8; break;
	case 8:wait = 7; break;
	case 9:wait = 6; break;
	case 10:wait = 5; break;
	case 11:wait = 4; break;
	case 12:wait = 3; break;
	case 13:wait = 2; break;
	case 14:wait = 1; break;
	case 15:wait = 0; break;
	default:break;
	}*/

 if(agt == 2)
 {
  delay(wait);
    digitalWrite(2, HIGH);
    delay(50);
    digitalWrite(2, LOW);
    i++;
  }
  if(agt == 3)
 {
  delay(wait);
    digitalWrite(3, HIGH);
    delay(50);
    digitalWrite(3, LOW);
    i++;
  }
  if(agt == 4)
 {
  delay(wait);
    digitalWrite(4, HIGH);
    delay(50);
    digitalWrite(4, LOW);
    i++;
  }
  if(agt == 5)
 {
  delay(wait);
    digitalWrite(5, HIGH);
    delay(50);
    digitalWrite(5, LOW);
    i++;
  }
	/*switch (agt)
	{
	case 2:
		Serial.print("2");
		delay(wait);
		digitalWrite(2, HIGH);
		delay(2000);
		digitalWrite(2, LOW);
		i++;
		break;
	case 3:
		Serial.print("3");
		delay(wait);
		digitalWrite(3, HIGH);
		delay(2000);
		digitalWrite(3, LOW);
		i++;
		break;
	case 4:
		Serial.print("4");
		delay(wait);
		digitalWrite(4, HIGH);
		delay(2000);
		digitalWrite(4, LOW);
		i++;
		break;
	case 5:
		Serial.print("5");
		delay(wait);
		digitalWrite(5, HIGH);
		delay(1000);
		digitalWrite(5, LOW);
		i++;
		break;
	
	default: 
		digitalWrite(2, LOW);
		digitalWrite(3, LOW);
		digitalWrite(4, LOW);
		digitalWrite(5, LOW);
		break;
	}*/
	/*if (agt == 0)
	{

	}*/

}
