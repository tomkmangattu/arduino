char digits_equvalent[10][8] = {"1111110", "0110000", "1101101", "1111001", "0110011", "1011011", "1011111", "1110000", "1111111", "1111011"};

// For accurate Time reading, use Arduino Real Time Clock and not just delay()
static uint32_t last_time, now = 0; // RTC

enum DisplayMode{
  hour,
  minute,
  second
};

// initial Time display is 12:59:45 PM
int h=11;
int m=22;
int s=0;

int d = 0;
DisplayMode displayMode = second;




void setup() {
  for(int i = 0; i < 14; i++){
    pinMode(i, OUTPUT);
  }
  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, OUTPUT);
}

void loop() {
  
  if(s == 60){
    m++;
    s = 0;
  }
  if( m == 60){
    h++;
    m = 0;
  }if( h == 13){
    h = 1;
  }
  

  change_display_name();
  
  if(displayMode == second){
    d = s;
    digitalWrite(A2, HIGH);
  }else if(displayMode == minute){
    digitalWrite(A2, LOW);
    d = m;
  }else{
    d = h;
    digitalWrite(A2, LOW);
  }

  display2(digits_equvalent[d % 10]);
  display1(digits_equvalent[d / 10]);
  

  while((now - last_time)< 1000){
    now = millis();
  }
  last_time = now;
  s++;
}

void change_display_name(){
  if(displayMode == second){
    displayMode = hour;
  }else if(displayMode == minute){
    displayMode = second;
  }else{
    displayMode = minute;
  }
}

void display1(char *digit){

  for(int i = 0; i< 7; i++){
    if( i == 6){
      if(digit[i] == '0'){
       digitalWrite(A0, HIGH);
      }else{
       digitalWrite(A0, LOW); 
      }
    }else if( i == 5){
      if(digit[i] == '0'){
       digitalWrite(A1, HIGH);
      }else{
       digitalWrite(A1, LOW); 
      }
    }else{
      if(digit[i] == '0'){
       digitalWrite(6 - i, HIGH);
      }else{
       digitalWrite(6 - i, LOW); 
      }
    }
    
  }
}

void display2(char *digit){
//  Serial.println(digit);
 
  for(int i = 0; i < 7; i++){
    if(digit[i] == '0'){
      digitalWrite(13 - i, HIGH);
    }else{
      digitalWrite(13 - i, LOW); 
    }
  }
}
