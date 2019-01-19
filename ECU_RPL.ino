#define SERIAL_FREQUENCY 57600

String package;
String packageID;
String packageData;
int packageSequence;
int packageChecksum;
int decodeCount = 0;
int lastPackageSequence;

void setup() {
  // set up Serial
  Serial1.begin(SERIAL_FREQUENCY);
}

void loop() {
  //TODO checkSerial starts at beginning of package
  if (Serial1.available() > 0) {
    int checkSumIndex = 0;
    
    package = Serial1.readString();
    
    //decode the package to the different components
    for(int i = 0; i < package.length(); i++) {
      if(package.charAt(i) == ',') {
        decodeCount++;
        continue;
      }
      switch(decodeCount) {
        case 0:
        packageID += package.charAt(i); 
        break;

        case 1:
        packageData += package.charAt(i); 
        break;

        case 2:
        packageSequence = int(package.charAt(i));
        break;

        case 3:
        packageChecksum = int(package.charAt(i));
        if(checkSumIndex == 0) {
          packageChecksum *= 10; 
          checkSumIndex++;
        } else {
          packageChecksum += int(package.charAt(i));
          
        }
        break;

        default:
        //TODO Error
        break;
      }
    }
  }

  //check if the calculated checksum equals the sent checksum, if not, request repeat package
  if(calculateChecksum(package) != packageChecksum) {
    //TODO: request repeat package
  }

  //check if the sequence is consistent, if not, request repeat package
  if(!checkPackageSequence(packageSequence)) {
    //TODO: request repeat package
  }

  //take actions according to the packageID
  executePackage(packageID);
}

//calculates the checksum and returns it
int calculateChecksum(String package) {
  int addedASCII = 0;
  for(int i = 0; i < package.length(); i++) {
    addedASCII += int(package.charAt(i));
  }
  int calculatedChecksum = addedASCII % 100;
  return calculatedChecksum;
}

//evaluates if the sequence is consistent
boolean checkPackageSequence(int packageSequence) {
  if(packageSequence == 0) {
    if(packageSequence == (lastPackageSequence - 9) {
      lastPackageSequence = 0;
      return true;
    } else {
      return false;
    }
  } else {
    if(packageSequence == (lastPackageSequence + 1)) {
      lastPackageSequence++;
      return true; 
    } else {
      return false;
    }
  }
}

boolean executePackage(String packageID) {
  switch(packageID) {
    case VS:
    //TODO:
    break;

    case HB:
    //TODO:
    break;

    case DS:
    //TODO:
    break;

    case RP:
    //TODO:
    break;

    case RS:
    //TODO:
    break;

    case ER:
    //TODO:
    break;

    case OK:
    //TODO:
    break;
  }
}
