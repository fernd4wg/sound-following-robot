// Motor Pin Declaration
// Right side motors
int s1p1 = 2;
int s1p2 = 3;

// Left side motors
int s2p1 = 12;
int s2p2 = 13;

// LED Pin Declaration
int LedReady = A1;
int LedMove = A0;

// Variable Declaration
bool left = 0;
bool right = 0;
bool back = 0;
bool front = 0;
bool ready = 0;
String order = "";

void setup() {
  // Pin Modes for the Wheel Drives
  pinMode(s1p1, OUTPUT); //Right side 1
  pinMode(s1p2, OUTPUT);  //Right side 2
  pinMode(s2p1,  OUTPUT); //Left side 1
  pinMode(s2p2, OUTPUT);  //Left side 2

  // Pin Modes for the Sensors
  pinMode(4,INPUT); // left
  pinMode(5, INPUT); // right
  pinMode(7, INPUT); //back
  pinMode(8, INPUT); // front

  //Pin Modes for the Speed Controllers
  pinMode(9,  OUTPUT); 
  pinMode(10, OUTPUT);
  pinMode(6,  OUTPUT); 
  pinMode(11, OUTPUT);

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);

  Serial.begin(9600);
}

// Function to make 2 motors go forward
void forward (int w11, int w12) {
  digitalWrite(w11,  HIGH);
  digitalWrite(w12, LOW);
}

// Function to make 2 motors to go backward
void backward (int w21, int w22) {
  digitalWrite(w21,  LOW);
  digitalWrite(w22, HIGH);
}

void loop() {

  //Controlling speed (0  = off and 255 = max speed): 
  //Setting Speeds
  analogWrite(9, 100); //ENA  pin
  analogWrite(10, 100); //ENB pin
  analogWrite(6, 100); //ENA  pin
  analogWrite(11, 100); //ENB pin

  // Set ready status LED on
  digitalWrite(LedReady, HIGH);

  // While robot is not ready
  while (ready==0){
    // Get readings from the 4 sound sensors
    // Left sound sensor
    if ((digitalRead(4) == 1) && (left == 0)){
      left = 1;
      order += "l";
    }
    // Right sound sensor
    if ((digitalRead(5) == 1) && (right == 0)){
      right = 1;
      order += "r";
    }
    // Back sound sensor
    if ((digitalRead(7) == 1) && (back == 0)){
      back = 1;
      order += "b";
    }
    // Front sound sensor
    if ((digitalRead(8) == 1) && (front == 0)){
      front = 1;
      order += "f";
    }
    // if all LED's were activated
    if ((left == 1) && (right == 1) && (front == 1) && (back == 1)){
      // set ready status to 1
      ready = 1;
    }
  }

// Set ready LED OFF to indicate robot is not reading sound
digitalWrite(LedReady, LOW);
// Set LED indicating movement to ON to indicate movement
digitalWrite(LedMove, HIGH);


  // Dont turn
  // if the order of the speaker activation was Forward, Left, Right, Back 
  // or Front Right, Left, Back go forward
  if ((order == "flrb") || (order == "frlb")) {
    // All 4 motors are set to go forward
    forward(s1p1, s1p2);
    forward(s2p1, s2p2);
    // Go forward for 3 seconds
    delay(3000);
  }

  // Turn front left
  // if order of activation is Front, Left, Back, Right or 
  // Left, Front, Right, Back turn left
  if ((order == ("flbr")) || (order == "lfrb")) {
    // Sets right side motors forward
    forward(s1p1, s1p2);
    // Sets left side motors backwards causing left turn
    backward(s2p1, s2p2);
    // Do this for 750ms
    delay(750);
    // Go forward for 3s
    forward(s1p1, s1p2);
    forward(s2p1, s2p2);
    delay(3000);
  }

  // Turn front right
  // if order of acivation is Front, Right, Back, Left or
  // Right, Front, Left, Back turn right
  if ((order == "frbl") || (order == "rflb")) {
    // Set left motors to go forward
    forward(s2p1, s2p2);
    // Set right motors to go backward causing right turn
    backward(s1p1, s1p2);
    // Do this for 750ms
    delay(750);
    // Go forward for 3s
    forward(s1p1, s1p2);
    forward(s2p1, s2p2);
    delay(3000);
  }

  // Go back
  // if order of activation is Back, Left, Right, Front or
  // Back, Right, Left, Front go backward
  if ((order == "blrf") || (order == "brlf")) {
    // Set all mortors to backward for 3s
    backward(s1p1, s1p2);
    backward(s2p1, s2p2);
    delay(3000);
  }

  // Turn back left
  // if activation order is Back, Left, Front, Right or
  // Left, Back, Right, Front turn rear end left
  if ((order == "blfr") || (order == "lbrf")) {
    // Set left side motors to go forward
    forward(s1p1, s1p2);
    // Set right side motors to go backward
    backward(s2p1, s2p2);
    // Do this for 2s
    delay(2000);
    // Go forward for 3s
    forward(s1p1, s1p2);
    forward(s2p1, s2p2);
    delay(3000);
  }

  // Turn back right
  // if activation order is Back, Right, Front, Left or
  // Right, Back, Left, Front turn rear rightward
  if ((order == "brfl") || (order == "rblf")) {
    // Set right side motors to go forward
    forward(s2p1, s2p2);
    // Set left side motors to go backward
    backward(s1p1, s1p2);
    // Do this for 2s
    delay(2000);
    // Go forward for 3s
    forward(s1p1, s1p2);
    forward(s2p1, s2p2);
    delay(3000);
  }

  // Turn right
  // if activation order is Right, Back, Front, Left or
  // Right, Front, Back, Left
  if ((order == "rbfl") || (order == "rfbl")) {
    // Set left motors to go forward
    forward(s2p1, s2p2);
    // Set right motors to go backward
    backward(s1p1, s1p2);
    // Do this for 1.25s
    delay(1250);
    // Go forward for 3s
    forward(s1p1, s1p2);
    forward(s2p1, s2p2);
    delay(3000);
  }

  // Turn left 
  // if activation record is Left, Front, Back, Right or
  // Left, Back, Front, Right
  if ((order == "lfbr") || (order == "lbfr")) {
    // Set right side motors to go forward
    forward(s1p1, s1p2);
    // Set left side motors to go backward
    backward(s2p1, s2p2);
    // do this for 1.25s
    delay(1250);
    // Go forward for 3s
    forward(s1p1, s1p2);
    forward(s2p1, s2p2);
    delay(3000);
  }

  // When robot done moving reset all variables to get ready to move again
  digitalWrite(s1p1, LOW);
  digitalWrite(s1p2, LOW);  
  digitalWrite(s2p1, LOW);
  digitalWrite(s2p2, LOW);
  digitalWrite(LedMove, LOW);

  // Serial.println(order);
  ready = 0;
  right = 0;
  left = 0;
  front = 0;
  back = 0;
  order = "";
  delay(500);
}

