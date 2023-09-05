/*
 * send string command program: 2023/9/5
 * you can modify it to be suitable for your project requirement
 * any questions, feel free contact me at www.khphan.com 
 */
// Command processing
bool inputStrComplete = false;
String inputString = "";

void setup() {
  // Hardware serial
  Serial.begin(9600);
  
  while (!Serial) {
    ; // Wait for the serial port to connect (needed for native USB)
  }
  delay(100);
}

void loop() {
  // Listening
  if (inputStrComplete) {
    ProcessCommand(inputString); // Updated to process the entire string
    inputString = "";
    inputStrComplete = false;
    delay(100);
  }
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      delay(10);
      inputStrComplete = true;
    }
  }
}

void ProcessCommand(String strCmd) {
  int idx;
  int idx1;
  Serial.print("Command: ");
  Serial.println(strCmd);

  // Simple one, easy to call a function
  //demo: "testA"
  if (strCmd.substring(0, 5).equals("testA")) {
    Serial.println("Hello World, Yeah...!");
  }

  // Complicated, call functions with one or more parameters
  //demo: "callfunc XYZ ABC"
  else if (strCmd.substring(0, 8).equals("callfunc")) {
    int lenCMD = 8; // Length of the command string
    idx = strCmd.indexOf(' ', lenCMD + 1);
    String para = strCmd.substring(lenCMD + 1, idx);

    idx1 = strCmd.indexOf(' ', idx + 1);
    String para1 = strCmd.substring(idx + 1, idx1);

    // Call your function with two parameters (you can uncomment this)
    Serial.print("Parameter inputs: ");
    Serial.print(para);
    Serial.print(", ");
    Serial.println(para1);
    // call_func1(para, para1);
  } else {
    Serial.println("NO COMMAND");
  }
}
