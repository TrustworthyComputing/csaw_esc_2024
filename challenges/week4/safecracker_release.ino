//Require Adafruit Motor Library V1
#include <AFMotor.h>

#define DELAY 1000
#define MULT 10

//phases
#define DEMO 0
#define SAFECRACKER_1 1
#define SAFECRACKER_2 2

#define SC1_NUM_STEPS 3
#define SC2_NUM_STEPS 5

//#define _RUN_

// Solve fore these values based on the recordings.
uint8_t steps1[SC1_NUM_STEPS] = {?,?,?} ;
uint8_t mode1[SC1_NUM_STEPS] = {SINGLE, SINGLE,SINGLE} ;   
uint8_t steps2[SC2_NUM_STEPS] = {?,?,?,?,?} ; 
uint8_t mode2[SC2_NUM_STEPS] = {?,?,?,?,?} ; 

#ifdef _RUN_
AF_DCMotor motor(1);
#endif

AF_Stepper stepper(360, 2);

void setup() 
{
  // Start serial communication at 9600 baud rate
  Serial.begin(115200);
  delay(DELAY*2);
  printChallengeHeadFoot() ;
  Serial.println("Welcome to Safecracker (1 & 2)!");
  printChallengeHeadFoot() ;
  randomSeed(analogRead(0));
}

void loop() 
{

  Serial.println(F("Enter Challenge Number (0-2): "));
  while(Serial.available() <= 0){   delay(DELAY);}
  char rc = Serial.read(); 
  uint8_t phase = rc - '0';
  
  if(phase >= DEMO && phase <= SAFECRACKER_2)
  {
    if(phase == DEMO)
    {
      Serial.println("Demo...");
      run_motor( 100, FORWARD, SINGLE);
      run_motor( 100, BACKWARD, SINGLE);
      run_motor( 100, FORWARD, DOUBLE);
      run_motor( 100, BACKWARD, DOUBLE);
      run_motor( 100, FORWARD, INTERLEAVE);
      run_motor( 100, BACKWARD, INTERLEAVE);
      run_motor( 100, FORWARD, MICROSTEP);
      run_motor( 100, BACKWARD, MICROSTEP);
    }
    else if (phase == SAFECRACKER_1)
    {
      Serial.println("Safecracker 1...");
#ifdef _RUN_
      run_motor( steps1[0], FORWARD,  SINGLE);
      run_motor( steps1[1], BACKWARD, SINGLE);
      run_motor( steps1[2], FORWARD,  SINGLE);
#endif
      combo_verify( steps1, mode1, SC1_NUM_STEPS);
    }
    else if(phase == SAFECRACKER_2)
    {
      Serial.println("Safecracker 2...");
#ifdef _RUN_

      motor.setSpeed(random(100,200));
      motor.run(FORWARD);
      run_motor( steps2[0], FORWARD,  mode2[0]);

      motor.setSpeed(random(100,200));
      run_motor( steps2[1], BACKWARD, mode2[1]);

      motor.setSpeed(random(100,200));
      run_motor( steps2[2], FORWARD,  mode2[2]);

      motor.setSpeed(random(100,200));
      run_motor( steps2[3], BACKWARD,  mode2[3]);

      motor.setSpeed(random(100,200));
      run_motor( steps2[4], FORWARD,  mode2[4]);
      motor.run(RELEASE);

#endif
      combo_verify( steps2, mode2, SC2_NUM_STEPS);
    }
    stepper.release();
  }
  delay(DELAY*2);
  while(Serial.available() > 0){  Serial.read(); }
}

void combo_verify(uint8_t* steps, uint8_t* mode, uint8_t len)
{
  Serial.println(F("Please enter your combo as the number of steps and letter indicating the mode."));
  Serial.println(F("\t S - Single; D - Double; I - Interleaved; M - Microstep"));
  bool correct_answer =true ; 
  for(uint8_t combo_i; combo_i < len ; combo_i++)
  {
    while(Serial.available() <= 0) { delay(DELAY); }
    int rsteps = Serial.parseInt();
    while(rsteps <= 0 || rsteps >255){rsteps = Serial.parseInt();}
    char rc = Serial.read();
    while(rc <= 'A' || rc >= 'Z'){ rc = Serial.read(); }
    uint8_t rmode = translate(rc);

    if(mode != NULL && rmode != mode[combo_i])
    {
      correct_answer = false ;
    }
    if(steps != NULL && rsteps != steps[combo_i])
    {
      correct_answer = false ;
    }
    Serial.print(F("Steps: ")); Serial.print(rsteps);  Serial.print(F(" Mode:"));  Serial.println(reverse_translate(rmode));
    run_motor( rsteps, combo_i%2?BACKWARD:FORWARD, rmode);
    
  }
  if(correct_answer)
  {
    printWinHead();
    Serial.println(F("You Cracked your own Combo!! Now verify on the official hex"));
    printWinFoot() ;
  }
  else
  {
    Serial.println(F("Incorrect Combo!! Try Again..."));
  }
}

uint8_t translate(char cmode)
{
  if(cmode == 'S'){ return SINGLE ; }
  else if(cmode == 'D'){ return DOUBLE ; }
  else if(cmode == 'I'){ return INTERLEAVE ; }
  else if(cmode == 'M'){ return MICROSTEP ; }
  return SINGLE ;
}


char reverse_translate(uint8_t rmode)
{
  if(rmode == SINGLE){ return 'S' ; }
  else if(rmode == DOUBLE){ return 'D' ; }
  else if(rmode ==INTERLEAVE ){ return 'I' ; }
  else if(rmode == MICROSTEP){ return 'M'; }
  return '?' ;
}

void run_motor(uint8_t steps, uint8_t dir, uint8_t mode)
{
    for(int j =0; j < steps*MULT; j++)
    {
      stepper.step(1, dir, mode);

      delay(3);
    }
    delay(DELAY);
}

void printChallengeHeadFoot()
{
  Serial.println(F("/************************************************************************/")) ;
}
void printWinHead()
{
  Serial.println() ;
  Serial.println() ;
  Serial.println(F("/********************  This will print when you beat the challenge!!!   ********************/")) ;
}

void printWinFoot()
{

  Serial.println(F("/********************          Congrats!!!         ********************/")) ;
  Serial.println() ;
  Serial.println() ;
}
