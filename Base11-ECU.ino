#define SERIAL_FREQUENCY 57600
#define COMMAND_BOX 1 //sender 1
#define FLIGHT_COMPUTER 2 //sender 2
#define LENGTH_CHECKSUM 2 //checksum has 2 digits
#define PACKAGE_LENGTH 11 

//different IDs for the packages
#define REPEAT_ID "RP"
#define HEARTBEAT_ID "HB"
#define VALVE_STATE_ID "VS"
#define OK_ID "OK"

#define xDATA "xxxxx" //xData for REPEAT signal
#define READ_PTS_AND_TS_TIME_INTERVAL 1000 //1s time interval to read sensors
#define PACKAGE_DATA_LENGTH 5 //data of package has 5 digits

//PINS - subject to change depending on the needs of the other departments
//Pressure
#define P_0 A0
#define P_1 A1
#define P_2 A2

//temperature
#define T_0 A3
#define T_1 A4
#define T_2 A5

//Valves
#define V_0 7
#define V_1 6
#define V_2 5
#define V_3 4
#define V_4 3

//commandBox connect
#define AS 13

//global variables
//package components
String package;
String packageID;
String packageData;
String packageChecksum;

//who sent the package
int sender;

//other code specific globals
int decodeCount = 0;
boolean processPackage = false;
unsigned long time;
boolean commandBoxIsConnected = false;

/*
 * Function: setup
 * ---------------
 * sets up the pins and starts the Serial communication
 */
void setup() {
  
  // set up Serials
  Serial1.begin(SERIAL_FREQUENCY);
  Serial2.begin(SERIAL_FREQUENCY);

  //set up pins
  pinMode(V_0, OUTPUT);
  pinMode(V_1, OUTPUT);
  pinMode(V_2, OUTPUT);
  pinMode(V_3, OUTPUT);
  pinMode(V_4, OUTPUT);
  pinMode(P_0, INPUT);
  pinMode(P_1, INPUT);
  pinMode(P_2, INPUT);
  pinMode(T_0, INPUT);
  pinMode(T_1, INPUT);
  pinMode(T_2, INPUT);
  pinMode(AS, INPUT);
}

/*
 * Function: loop
 * --------------
 * main loop of the program
 * checks if a package is avaible from any sender, proccesses it if so and
 * takes actions accordingly
 */
void loop() {

  //check commandBox Serial until it is disconnected
  if (commandBoxIsConnected && Serial1.available() >= PACKAGE_LENGTH) {

    //assign sender to active serial port
    sender = COMMAND_BOX;

    //read package from Serial1
    package = Serial1.readStringUntil(';');

    //read rest to eliminate ';' in Serial1
    Serial1.readString();

    //check if package has required length, otherwise request repeat package
    if (package.length() != PACKAGE_LENGTH) {

      package = createPackage(REPEAT_ID, xDATA);
      sendPackage(package);
      return;
    }

    //package can be processed
    processPackage = true;

  //check if Flight computer sent a package
  } else if (Serial2.available() >= PACKAGE_LENGTH) {

    //assign sender to active serial port
    sender = FLIGHT_COMPUTER;

    //read package from Serial2
    package = Serial2.readStringUntil(';');

    //read rest to eliminate ';' in Serial2
    Serial2.readString();
    
    //check if package has required length, otherwise request repeat package
    if (package.length() != PACKAGE_LENGTH) {

      package = createPackage(REPEAT_ID, xDATA);
      sendPackage(package);
      return;
    }

    //package can be processed
    processPackage = true;
  }

  //process package
  if (processPackage) {

    //parse package
    parsePackage(package);

    //check if the calculated checksum equals the sent checksum, if not, request repeat package
    if (calculateChecksum(packageID + "," + packageData + ",") != packageChecksum.toInt()) {

      package = createPackage(REPEAT_ID, xDATA);
      sendPackage(package);
      return;
    }

    //take actions according to the packageID
    executePackage(packageID);

    //finished processing Package, set processPackage false for next package
    processPackage = false;
  }

  //read PTs and Ts
  time = millis();
  if (time > READ_PTS_AND_TS_TIME_INTERVAL) {

    //set sender to flightcomputer
    sender = FLIGHT_COMPUTER;

    //read and send PTs
    readPTs();
    //TODO read and send Ts
    //readTs();

    time = 0;
  }

  //check if command box is still connected
  if (digitalRead(AS) == LOW) {
      commandBoxIsConnected = true;
    } else {
      commandBoxIsConnected = false;
    }
}


/*
 * Function: calculateChecksum
 * ---------------------------
 * adds the ASCII values of the package characters(except the checksum) together and 
 * takes modulo 100. If the checksum sent differs to the one calculated, the package 
 * is corrupted and needs to be sent again
 * 
 * package: the package to check
 * 
 * returns: the calculated checksum
 */
int calculateChecksum(String package) {
  int addedASCII = 0;

  //loop through the package, but leave out the checksum for calculating the checksum
  for (int i = 0; i < package.length(); i++) {
    addedASCII += int(package.charAt(i));
  }

  //take modulo to calculated checksum
  int calculatedChecksum = addedASCII % 100;
  return calculatedChecksum;
}

/*
 * Function: exectuePackage
 * ------------------------
 * takes actions according to the package ID and data
 * i.e. toggling the valves, responding to heartbeat or if the ID is not
 * identified, repeat package request
 * 
 * packageID: the package ID to respond to
 */
void executePackage(String packageID) {

  //package reagards valve states, set valves accordingly
  if (packageID.equals("VS")) {

    if (packageData.charAt(0) == '1') {
      digitalWrite(V_0, HIGH);
    } else {
      digitalWrite(V_0, LOW);
    }

    if (packageData.charAt(1) == '1') {
      digitalWrite(V_1, HIGH);
    } else {
      digitalWrite(V_1, LOW);
    }

    if (packageData.charAt(2) == '1') {
      digitalWrite(V_2, HIGH);
    } else {
      digitalWrite(V_2, LOW);
    }

    if (packageData.charAt(3) == '1') {
      digitalWrite(V_3, HIGH);
    } else {
      digitalWrite(V_3, LOW);
    }

    if (packageData.charAt(4) == '1') {
      digitalWrite(V_4, HIGH);
    } else {
      digitalWrite(V_4, LOW);
    }

    //confirm change of the valves by sending OK package with valve States
    sendPackage(createPackage(OK_ID, packageData));

    //package regards heartbeat, send heartbeat back
  } else if (packageID.equals(HEARTBEAT_ID)) {
    sendPackage(createPackage(HEARTBEAT_ID, packageData));

    //package could not be identified, request repeat package
    //this branch should never be executed
  } else {
    package = createPackage(REPEAT_ID, xDATA);
    sendPackage(package);
  }
}

/*
 * Function: sendPackage
 * ---------------------
 * writes to the serial of the wanted sender, here only the flight computer
 * since the commandbox does not receive packages from the ECU
 * 
 * package: the package to send
 */
void sendPackage(String package) {

  if (sender == FLIGHT_COMPUTER) {

    //send to flight computer
    Serial.println(package);
  }
}

/*
 * Function: createPackage
 * -----------------------
 * assembles the different components to a package
 * 
 * packageID: the package ID
 * PackageData: the package Data
 * 
 * return: the assembled package
 */
String createPackage(String packageID, String packageData) {
  package = packageID + "," + packageData + ",";

  //calculated checksum
  String calculatedChecksum = String(calculateChecksum(package));

  //if necessary add a digit to the checksum
  if(calculatedChecksum.length() == 1) {
    calculatedChecksum = "0" + calculatedChecksum;
  }
  
  package += calculateChecksum(package);
  package += ';';
  return package;
}

/*
 * Function: parsePackage
 * ----------------------
 * gets passed in the received string from serial and parses it to the different
 * package components
 * 
 * pakcage: the passed in String
 */
void parsePackage(String package) {

  //reset globals for the package
  decodeCount = 0;
  packageID = "";
  packageData = "";
  packageChecksum = "";

  //assign values to the globals
  for (int i = 0; i < package.length(); i++) {
    if (package.charAt(i) == ',') {
      decodeCount++;
      continue;
    }
    switch (decodeCount) {
      case 0:
        packageID += package.charAt(i);
        break;

      case 1:
        packageData += package.charAt(i);
        break;

      case 2:
        packageChecksum += package.charAt(i);
        break;

      default:
        //if package is corrupted, checksum test will request repeat package
        break;
    }
  }
}

/*
 * Function readPTs
 * ----------------
 * reads the analog signal from the PTs and formats it to a 5 digit string with 0s in front.
 * Here there are only three PTs, more can be added if needed
 */
void readPTs() {

  //read analog Data from pressure transducer
  //and format data to 5 digit string with 0s in front
  String P_0_Data = String(analogRead(P_0));
  String P_0_Data_Formatted = "0";
  for (int i = P_0_Data.length(); i < PACKAGE_DATA_LENGTH - 1; i++) {
    P_0_Data_Formatted += "0";
  }
  P_0_Data_Formatted += P_0_Data;

  //send package to flightcomputer
  sendPackage(createPackage("P0", P_0_Data_Formatted));

  //repeat for other sensors
  
  String P_1_Data = String(analogRead(P_1));
  String P_1_Data_Formatted = "0";
  for (int i = P_1_Data.length(); i < PACKAGE_DATA_LENGTH - 1; i++) {
    P_1_Data_Formatted += "0";
  }
  P_1_Data_Formatted += P_1_Data;

  sendPackage(createPackage("P1", P_1_Data_Formatted));

  String P_2_Data = String(analogRead(P_2));
  String P_2_Data_Formatted = "0";
  for (int i = P_2_Data.length(); i < PACKAGE_DATA_LENGTH - 1; i++) {
    P_2_Data_Formatted += "0";
  }
  P_2_Data_Formatted += P_2_Data;
  
  sendPackage(createPackage("P2", P_2_Data_Formatted));
}

//TODO: there is no read of the temperature sensors so far, but this is can be implemented in a 
//similiar style as the PTs
