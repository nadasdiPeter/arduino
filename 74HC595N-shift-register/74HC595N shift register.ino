#define DS_pin 8
#define STCP_pin 10
#define SHCP_pin 12

boolean registers[8] = {LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW};
int time1 = 100;

void writeReg() 
{
    digitalWrite(STCP_pin, LOW);
    for (int i = 7; i >= 0; i--)
    {
        digitalWrite(SHCP_pin, LOW);
        digitalWrite(DS_pin, registers[i]);
        digitalWrite(SHCP_pin, HIGH);
    }
    digitalWrite(STCP_pin, HIGH);
}

void setup() {
    pinMode(DS_pin, OUTPUT);
    pinMode(STCP_pin, OUTPUT);
    pinMode(SHCP_pin, OUTPUT);
    writeReg(); // write the default set of registers[] to DS_pin, one by one
}

void loop() {
    // put your main code here, to run repeatedly:

    /*for (int i = 0; i <= 7; i++) // fixed, i<=7 is a bit easier to understand than i<8
    {
        registers[i] = HIGH;
        delay(time1);
        writeReg();
    }*/

    for (int i = 0; i <= 7; i++) // fixed, i<=7 is a bit easier to understand than i<8
    {
        if (i % 2 == 0)
        {
            registers[i] = HIGH;
        }
        else
        {
            registers[i] = LOW;
        }
        delay(time1);
        writeReg();
    }

    for (int i = 7; i >= 0; i--) // fixed
    {
        if (i % 2 == 0)
        {
            registers[i] = LOW;
        }
        else
        {
            registers[i] = HIGH;
        }
        delay(time1);
        writeReg();
    }
    delay(time1);
}