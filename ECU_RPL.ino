#define SERIAL_FREQUENCY 57600
#define COMMAND_BOX 1 //Serial1
#define FLIGHT_COMPUTER 2 //Serial2
#define LENGTH_CHECKSUM 2
#define PACKAGE_LENGTH 11
#define REPEAT_ID "RP"
#define xDATA "xxxxx"

String package;
String packageID;
String packageData;
String packageChecksum;
int sender;
int decodeCount = 0;
boolean processPackage = false;

void setup() {
  // set up Serial
  Serial.begin(SERIAL_FREQUENCY);
  //Serial2.begin(SERIAL_FREQUENCY);
}

void loop() {
  //TODO checkSerial starts at beginning of package
  /*
  if (Serial1.available() >= PACKAGE_LENGTH) {

    //assign sender to active serial port
    sender = 1;

    //read package from Serial 1
    package = Serial1.readStringUntil('\n');
    Serial1.readString();

    if (package.length() != PACKAGE_LENGTH) {

      //request repeat package
      package = createPackage(REPEAT_ID, xDATA);
      sendPackage(package, sender);
      return;
    }

    processPackage = true;

  } else */ if (Serial.available() >= PACKAGE_LENGTH) {

    //assign sender to active serial port
    sender = 2;

    //read package from Serial 1
    package = Serial.readStringUntil(';');
    Serial.readString();
    //Serial.println(package);
    if (package.length() != PACKAGE_LENGTH) {

      //Serial2.readString();
      //request repeat package
      package = createPackage(REPEAT_ID, xDATA);
      sendPackage(package, sender);
      Serial.println("Package corrputed");
      return;
    }

    processPackage = true;
  }

  if (processPackage) {

    //parse package
    parsePackage(package);

    //check if the calculated checksum equals the sent checksum, if not, request repeat package
    if (calculateChecksum(packageID + "," + packageData + ",") != packageChecksum.toInt()) {

      //request repeat package
      package = createPackage(REPEAT_ID, xDATA);
      sendPackage(package, sender);
      return;
    }

    //take actions according to the packageID
    executePackage(packageID);

    processPackage = false;

    Serial.println("Package processed");
  }
}


//calculates the checksum and returns it
int calculateChecksum(String package) {
  int addedASCII = 0;

  //loop through the package, but leave out the checksum for calculating the checksum
  for (int i = 0; i < package.length(); i++) {
    addedASCII += int(package.charAt(i));
  }
  int calculatedChecksum = addedASCII % 100;
  return calculatedChecksum;
}

//take actions according to the packageID
void executePackage(String packageID) {
  if (packageID.equals("VS")) {

  } else if (packageID.equals("HB")) {

  } else if (packageID.equals("DS")) {

  } else if (packageID.equals("RP")) {

  } else if (packageID.equals("RS")) {

  } else if (packageID.equals("ER")) {

  } else if (packageID.equals("OK")) {

  } else {
    //TODO Package not identified
  }
}

//sends a package to a specified receiver one for each receiver
void sendPackage(String package, int sender) {

  if (sender == 1) {

    //send to command box
    //Serial.print(package);

  } else if (sender == 2) {

    //send to flight computer
    Serial.print(package);
  }
}

//assembles the different components to a package
String createPackage(String packageID, String packageData) {
  package = packageID + "," + packageData + ",";
  package += calculateChecksum(package);
  package += ';';
  return package;
}

void parsePackage(String package) {

  decodeCount = 0;
  packageID = "";
  packageData = "";
  packageChecksum = "";

  //decode the package to the different components
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
        //TODO Error
        break;
    }
  }
}
