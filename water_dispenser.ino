#include <HX711.h>
const int ld_cell2_dout = 40;
const int ld_cell2_sck = 42;

const int thresholdDwn = 300;
const int thresholdUp= 1500;
const int motorPin = 4;
//HX711 scale1;
HX711 scale2;
String input="";
int x = 0;
long t=0;
//int loadcell2();
int currentWeight = 0;  // loadcell2();
void setup() {
  Serial.begin(115200);
  pinMode(motorPin, OUTPUT);

  //scale1.begin(ld_cell1_dout,ld_cell1_sck);
  //scale1.set_scale();
  //scale1.tare();

  scale2.begin(ld_cell2_dout, ld_cell2_sck);
  scale2.set_scale();
  scale2.tare();
  currentWeight = waterLevel();
}

void loop() {
 
  currentWeight = waterLevel();
  delay(100);
  // Serial.print("currentWeight : ");
  // Serial.println(currentWeight);

  while (!Serial.available()) {
  }
  while (Serial.available()) {
    delay(3);
    char c1 = Serial.read();
    if (c1 == ' ') {
      break;
    }
    if (c1 == '[') {
      continue;
    }

    input += c1; 
  }
   //x = Serial.parseInt();
  x=input.toInt();
  if(currentWeight>thresholdDwn )
  {

 
  if(x>0){

    int y = 0.08*x - 0.8 ;// waterQty(x);
    digitalWrite(motorPin, HIGH);
     Serial.println("pump ON");
    delay(10);
    t = millis() / 500;
    while(y > (millis() / 500) - t)
    {
    }
    digitalWrite(motorPin, LOW);
    
    Serial.println("pump OFF");
  }
  
  
  currentWeight = waterLevel();
  input="";
  x = 0;
  }
else{
  Serial.Println("fill container");

}
}

//void loadcell1() {
//Serial.println("place weights on loadcell1");
//delay(1000);

//if(scale1.is_ready())
//{
//long reading1 = scale1.get_units(10);
//int weight1 = reading1/1800;
//Serial.print("weight on loadcell1");
//Serial.println(weight1);

//if (weight1>thresholdValue1)
//{
//Serial.println("weight on loadcell1 is greater than thresholdvalue1");
//}

//}
//}

int loadcell2() {
  // Serial.println("place weights on loadcell2");
  //delay(1000);

  if (scale2.is_ready()) {
    delay(50);
    long reading2 = scale2.get_units(10);
    int weight2 = (reading2 / 400) - 258;
    if (weight2 < 0) {
      weight2 = 0;
    }
    // return weight2;


    Serial.print("weight on loadcell2  ");
    Serial.println(weight2);

    if (weight2 < thresholdValue1) {
      Serial.println("please fill the container");
    }

    if (weight2 > thresholdValue2) {
      Serial.println("container is full");
    }
  }
  delay(10);
}
int waterQty(int qty)
{
  return (0.08*qty - 0.8);
}

int waterLevel() {
  delay(10);
  int weight2;
  if (scale2.is_ready()) {
    delay(50);
    long reading2 = scale2.get_units(10);
    int weight2 = (reading2 / 400) - 258;
    if (weight2 < 0) {
      weight2 = 0;
    }
    return weight2;
    // Serial.print("weight on loadcell2  ");
    // Serial.println(weight2);
  }
  // delay(10);
  // return weight2;
}