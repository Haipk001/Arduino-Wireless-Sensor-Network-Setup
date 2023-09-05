/*
 * send char array command program: 2023/9/5
 * you can modify it to be suitable for your project requirement
 * any questions, feel free contact me at www.khphan.com 
 */

char getChars[100];
bool inputDataOK;

void setup() {
  // Hardware serial
  Serial.begin(9600);
  
  while (!Serial) {
    ; // Wait for the serial port to connect (needed for native USB)
  }
  delay(100);
}

void ProcessCommand(char *chrCmd) {
  Serial.print(F("Command : "));
  Serial.println(chrCmd);

  // Simple one, easy to call a function
  // demo: "testA"
  if (!strncmp(chrCmd, "testA", 5)) {
    Serial.println("Hello World, Yeah...!");
  }

  // Complicated, call functions with one or more parameters
  // demo: "<callfunc XYZ ABC>" 
  else if (!strncmp(chrCmd, "callfunc", 8)) {
    char command[50];
    char var1[50];
    char var2[50];
    sscanf(chrCmd, "callfunc %s %s", var1, var2); // use strtok to achieve the same result too!

    // Call your function with two parameters (you can uncomment this)
    Serial.print("Parameter inputs: ");
    Serial.print(var1);
    Serial.print(", ");
    Serial.println(var2);
    // call_func1(var1, var2);     
  }
}

void loop() {
  // Listening
  receiveEvents();
  dotaskEvents();
}

void receiveEvents() {
  byte chrno  = 100;
  char cmdser[chrno];
  static boolean serProc = false;
  static boolean serOK = false;
  static byte ndx = 0;
  char startMarker = '<';
  char endMarker = '>';
  char ser;
        
  while (Serial.available() > 0 && inputDataOK == false) { 
    if (Serial.available() > 0) {
      ser  = Serial.read();
      if (serProc == true) {
        if (ser != endMarker) {
          cmdser[ndx] = ser;
          ndx++;
          if (ndx >= chrno) {
            ndx = chrno - 1;
          }
        }
        else {
          cmdser[ndx] = '\0'; // terminate the string
          serProc = false;
          ndx = 0;
          serOK = true;
        }
      }
      else if (ser == startMarker) {
        serProc = true;
      }
    }

    if (serOK == true) {
      strncpy(getChars, cmdser, strlen(cmdser));
      getChars[strlen(cmdser)] = '\0';
      inputDataOK = true;
      serOK = false;
    }
  }
}


void dotaskEvents() {
  if (inputDataOK) {
    Serial.println(getChars);
    ProcessCommand(getChars);
    inputDataOK = false;
  } 
}
