const int LEDPIN = 13;

String commandString = "";
String inputData = "";

bool isDataComplete = false;

void setup()
{
    pinMode(LEDPIN, OUTPUT);

    Serial.begin(9600);
}

void loop()
{
    serialDataEvents();

    if (isDataComplete == true)
    {
        if (commandString == "on")
        {
            digitalWrite(LEDPIN, HIGH);
        }
        else if (commandString == "off")
        {
            digitalWrite(LEDPIN, LOW);
        }

        // Reset for next command
        isDataComplete = false;
        commandString = "";
        inputData = "";
    }
}

void serialDataEvents()
{
    while (Serial.available())
    {
        char inChar = (char)Serial.read();

        if (inChar == '\n')
        {
            isDataComplete = true;
            commandString = inputData;

            // Remove extra spaces or \r
            commandString.trim();
        }
        else
        {
            inputData += inChar;
        }
    }
}