// LCD Thermometer Project
// Hardware: PIC 16F877A with 4MHz crystal and LM35 sensor

//== Display LCD comunication with the PIC 16F877A microcontroller
sbit LCD_RS at RD2_bit;
sbit LCD_EN at RD3_bit;
sbit LCD_D4 at RD4_bit;
sbit LCD_D5 at RD5_bit;
sbit LCD_D6 at RD6_bit;
sbit LCD_D7 at RD7_bit;

sbit LCD_RS_Direction at TRISD2_bit;
sbit LCD_EN_Direction at TRISD3_bit;
sbit LCD_D4_Direction at TRISD4_bit;
sbit LCD_D5_Direction at TRISD5_bit;
sbit LCD_D6_Direction at TRISD6_bit;
sbit LCD_D7_Direction at TRISD7_bit;
//== End Comunication

//== Auxiliary Functions
void Celsius();                                              //  Function that calculate the temperature in Celsius
void degreeCharacterFunction(char pos_row, char pos_char);   //  Function to write the character "°" in the LCD display
//void caretCharacterFunction(char pos_row, char pos_char);    //! Function to write the character "ô" in the LCD display, this just makes sense when reading "Thermometer" in Portuguese (Termômetro)
long averageTemperature();                                   //  Function to calculate the average temperature of 100 temperature reading
void writeEEPROM();                                          //  Function to store in the EEPROM memory
void readEEPROM();                                           //  Function to read the EEPROM memory
void deleteEEPROM();                                         //  Function to delete the EEPROM memory
//== End Auxiliary Functions

//Defines
#define ad_resolution           1023 //! Resolution of the AD convertor
#define vdd                     5    //! Source in TTL (Transistor-Transistor Logic) levels
#define correctionFactor        100  //! LM35 sensor correction factor, just because 10mV * 100 = 1V -> Int valuer
#define flag                T0IF_bit //! Overflow flag don't forget this flag
#define butt                 RC3_bit //! Define the RC3 pin to be the Button 1 pin
#define butt2                RC2_bit //! Define the RC2 pin to be the Button 2 pin
//End Defines

//Macro function //?(the function concatenates each digit referring to the temperature read, precision to two decimal places)
                 //! +48 is the correction to ASCII chart
#define disp_t               lcd_chr(1,6,tenUnit+48);           lcd_chr_cp(unit+48);\
                             lcd_chr_cp('.');                   lcd_chr_cp(dec1+48);\
                             degreeCharacterFunction(1,10);
//End Macro function

//Variables //! as we are in a PIC microcontroller we don't have a lot of memory, so I will use the minimum amount of memory needed
unsigned long storeTemperature, temperatureCelsius;                                                                                     // variables to store temperature quantities
unsigned char tenUnit, unit, dec1, tenUnit_I, unit_I, dec1_I, tenUnit_II, unit_II, dec1_II, tenUnit_III, unit_III, dec1_III;            //  Digits to use in the macro and display on the display
unsigned char *text;                                                                                                                    //  Variable that stores texts to write on the display
const char character[] = {6,9,6,0,0,0,0,0};         //  "°" special character
const char character1[] = {4,10,0,14,17,17,14,0};   //  "ô" special character
unsigned char Button1 = 0x00;                       // Button 1
unsigned char Button2 = 0x00;                       // Button 2
int count = 0;                                      // Counter
unsigned char EEPROM1;                              // Variable to store temperature in the EEPROM memory
unsigned char EEPROM2;                              // Variable to store temperature in the EEPROM memory
unsigned char EEPROM3;                              // Variable to store temperature in the EEPROM memory
unsigned char readEEPROM1;                          // Variable to store the memory read from EEPROM
unsigned char readEEPROM2;                          // Variable to store the memory read from EEPROM
unsigned char readEEPROM3;                          // Variable to store the memory read from EEPROM
unsigned char readEEPROM4;                          // Variable to store the memory read from EEPROM
unsigned char readEEPROM5;                          // Variable to store the memory read from EEPROM
unsigned char readEEPROM6;                          // Variable to store the memory read from EEPROM
unsigned char readEEPROM7;                          // Variable to store the memory read from EEPROM
unsigned char readEEPROM8;                          // Variable to store the memory read from EEPROM
unsigned char readEEPROM9;                          // Variable to store the memory read from EEPROM
unsigned char memoryPositionCount = 0x00;           // Create the variable to store the memory position
//End Variables

//Interruption function
void interrupt(){
   if(flag){
        count++;         //? Increment the counter
        TMR0 = 0x06;     //? Reset the timer0 register
        flag = 0x00;     //? Clear the flag

        if(!butt){       //? See if the buttons are pressed
            Button1 = 0x01;
        } else if(!butt2){
            Button2 = 0x01;
        }
    }
}
//end Interruption function

// Main
void main()
{
    GIE_bit = 0x01;                     //? Enable global interrupt
    PEIE_bit = 0x01;                    //? Allow interruption by other sources
    TMR0IE_bit = 0x01;                  //? Enable global timer0 overflow interrupt
    TMR0 = 0x06;                        //? Start a count at 6
    OPTION_REG = 0x81;                  //? Set timer0, disable pull up resistors, and select prescaler at 1:4

    adcon0 = 0b00000001;                //? Selects the analog pin AN0
    TRISA = 0xFF;                       //? Configure all PORTA as input
    TRISC = 0x0C;                       //? Sets all PORTC as output except RC3 AND RC2
    TRISD = 0x00;                       //? Sets all PORTD as output
    PORTA = 0x00;                       //? Initialize bits to low
    PORTD = 0x00;                       //? Initialize bits to low
    PORTC = 0x00;                       //? Initialize bits to low

    Lcd_Init();                         // Initialize the display
    Lcd_Cmd(_LCD_CLEAR);                // Clear the LCD display
    Lcd_Cmd(_Lcd_Cursor_Off);           // Erase the cursor
    text=("TERM");                      // Store the text "TERM" in the text variable
    lcd_out(1,4,text);                  //? Writes the text once in the display, row 1, column 4
    caretCharacterFunction(1,8);        //? Write the text once on display, line 1, column 8
    text=("METRO");                     // Store the text "METRO" in the text variable
    lcd_out(1,9,text);                  //? Write the text once on display, line 1, column 9
    text=("DIGITAL");                   // Store the text "DIGITAL" in the text variable
    lcd_out(2,6,text);                  //? Writes the text once on display, line 2, column 6
    Delay_ms(1000);
    Lcd_Cmd(_LCD_CLEAR);                // Clear the LCD display
    Delay_ms(500);

    // Loop
    while(1){
        if(Button1 == 0x01){                                            //! Read temperature button
            readEEPROM();                                               // Call the function to read the temperature in the EEPROM memory
            writeEEPROM ();                                             // Call the function to store the temperature in the EEPROM memory
            Delay_ms(5000);                                             // 5-sec screen off time (Scale 1:1000)
            Lcd_Cmd(_LCD_CLEAR);                                        // Clear the LCD display
            count = 0;                                                  // Reset counter
            memoryPositionCount++;                                      // Increment the memory positions counter
            if(memoryPositionCount==0x03){memoryPositionCount=0x00;}       // Reset the memory positions counter
            Button1 == 0x00;                                            // Reset Button 1
            Button2 == 0x00;                                            // Reset Button 2
        }else if(Button2 == 0x01){                                      //! Delete temperature button
            deleteEEPROM();                                             // Call the function to delete the temperature in the EEPROM memory
            Delay_ms(5000);                                             // 5-sec screen off time (Scale 1:1000)
            Lcd_Cmd(_LCD_CLEAR);                                        // Clear the LCD display
            count = 0;                                                  // Reset counter
            memoryPositionCount++;                                      // Increment the memory positions counter
            if(memoryPositionCount==0x03){memoryPositionCount=0x00;}       // Reset the memory positions counter
            Button1 == 0x00;                                            // Reset Button 1
            Button2 == 0x00;                                            // Reset Button 2
        }else if(cont == 20000){                                        //! read the temperature every 20 seconds (Scale 1:1000)
            readEEPROM();                                               // Call the function to read the temperature in the EEPROM memory
            writeEEPROM ();                                             // Call the function to store the temperature in the EEPROM memory
            Delay_ms(5000);                                             // 5-sec screen off time (Scale 1:1000)
            Lcd_Cmd(_LCD_CLEAR);                                        // Clear the LCD display
            count = 0;                                                  // Reset counter
            memoryPositionCount++;                                      // Increment the memory positions counter
            if(memoryPositionCount==0x03){memoryPositionCount=0x00;}       // Reset the memory positions counter
            Button1 == 0x00;                                            // Reset Button 1
            Button2 == 0x00;                                            // Reset Button 2
        }
      } //End loop
} //End Main

void Celsius(){
    Lcd_Out(1,1,"Temp:");
    storeTemperature = averageTemperature();                                                   // Call the function to calculate the average temperature of 100 temperature reading
    temperatureCelsius = (storeTemperature*vdd*correctionFactor)/ad_resolution;                // Convert the value to Celsius scale
    //! the next 4 lines separate the value digits into tens unit, unit, and one decimal place
    tenUnit = t_Celsius/10;
    unit = t_Celsius % 10;
    dec1 = (((storeTemperature*vdd*correctionFactor)%ad_resolution)*10)/ad_resolution;
    disp_t;                                                                                     // Call macro function
    Lcd_Out(1,11,"C");                                                                          // Write "C" on the LCD display
    delay_ms(800);       
}

long averageTemperature(){
    unsigned char i;                                    // create a index
    unsigned long temp_store = 0;                       // create a temporary store
    for(i=0;i<100;i++){temp_store += ADC_Read(0);}      //temp_store = temp_store + ADC_Read(0) (makes the sum of the 100 interactions )
    return(temp_store/100);                             //return the average temperature
}

void CustomChar1(char pos_row, char pos_char){    //? Function generated by mikroC to print special characters
    char i;
    Lcd_Cmd(64);
    for (i=0;i<=7;i++){Lcd_Chr_CP(character[i]);}
    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(pos_row, pos_char, 0);
}



void CustomChar(char pos_row, char pos_char){  //? Function generated by mikroC to print special characters
    char i;
    Lcd_Cmd(64);
    for (i=0;i<=7;i++){Lcd_Chr_CP(character1[i]);}
    Lcd_Cmd(_LCD_RETURN_HOME);
    Lcd_Chr(pos_row, pos_char, 0);
}

void writeEEPROM(){ //! Write EEPROM memory                     
    if(memoryPositionCount==0x00){
        Celsius();                      // Call the function Celsius
        EEPROM1 = tenUnit;              // Store the Ten Unit
        EEPROM2 = unit;                 // Store the Unit
        EEPROM3 = dec1;                 // Store the decimal
        EEPROM_Write(0x00,EEPROM1);     // write in the memory
        delay_ms(10);
        EEPROM_Write(0x01,EEPROM2);     // write in the memory
        delay_ms(10);
        EEPROM_Write(0x02,EEPROM3);     // write in the memory
        delay_ms(10);
    }else if(memoryPositionCount==0x01){
        Celsius();
        Celsius();                      // Call the function Celsius
        EEPROM1 = tenUnit;              // Store the Ten Unit
        EEPROM2 = unit;                 // Store the Unit
        EEPROM3 = dec1;                 // Store the decimal
        EEPROM_Write(0x03,EEPROM1);     // write in the memory
        delay_ms(10);
        EEPROM_Write(0x04,EEPROM2);     // write in the memory
        delay_ms(10);
        EEPROM_Write(0x05,EEPROM3);     // write in the memory
        delay_ms(10);
    }else if(memoryPositionCount==0x02){
        Celsius();                      // Call the function Celsius
        EEPROM1 = tenUnit;              // Store the Ten Unit
        EEPROM2 = unit;                 // Store the Unit
        EEPROM3 = dec1;                 // Store the decimal
        EEPROM_Write(0x06,EEPROM1);     // write in the memory
        delay_ms(10);
        EEPROM_Write(0x07,EEPROM2);     // write in the memory
        delay_ms(10);
        EEPROM_Write(0x08,EEPROM3);     // write in the memory
        delay_ms(10);
    }
  }

void readEEPROM(){ //! Read EEPROM memory
    readEEPROM1 = EEPROM_Read(0x08);
    readEEPROM2 = EEPROM_Read(0x07);
    readEEPROM3 = EEPROM_Read(0x06);
    readEEPROM4 = EEPROM_Read(0x05);
    readEEPROM5 = EEPROM_Read(0x04);
    readEEPROM6 = EEPROM_Read(0x03);
    readEEPROM7 = EEPROM_Read(0x02);
    readEEPROM8 = EEPROM_Read(0x01);
    readEEPROM9 = EEPROM_Read(0x00);
    tenUnit_I = readEEPROM9;            // Stores the ten unit value of the first thermometer reading in tenUnit_I
    unit_I = readEEPROM8;               // Stores the unit value of the first thermometer reading in unit_I
    dec1_I = readEEPROM7;               // Stores the dec1 value of the first thermometer reading in dec1_I
    lcd_chr(2,1,tenUnit_I+48);
    lcd_chr_cp(unit_I+48);
    lcd_chr_cp('.');
    lcd_chr_cp(dec1_I+48);
    CustomChar1(2,5);
    tenUnit_II = readEEPROM6;            // Stores the ten unit value of the second thermometer reading in tenUnit_II
    unit_II = readEEPROM5;               // Stores the unit value of the second thermometer reading in unit_II
    dec1_II = readEEPROM4;               // Stores the dec1 value of the second thermometer reading in dec1_II
    lcd_chr(2,7,tenUnit_II+48);
    lcd_chr_cp(tenUnit_II+48);
    lcd_chr_cp('.');
    lcd_chr_cp(dec1_II+48);
    CustomChar1(2,11);
    tenUnit_III = readEEPROM3;            // Stores the ten unit value of the third thermometer reading in tenUnit_III
    unit_III = readEEPROM2;               // Stores the unit value of the third thermometer reading in unit_III
    dec1_III = readEEPROM1;               // Stores the dec1 value of the third thermometer reading in dec1_III
    lcd_chr(2,12,tenUnit_III+48);
    lcd_chr_cp(tenUnit_III+48);
    lcd_chr_cp('.');
    lcd_chr_cp(dec1_III+48);
    CustomChar1(2,16);    
  }

void deleteEEPROM(){ //! Delete EEPROM memory
    for(int i=0; i<8; i++){
        EEPROM_Write(0x00+i,0x00);
        delay_ms(10);
    }
  }
