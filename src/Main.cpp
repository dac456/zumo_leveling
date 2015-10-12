#include "AlgorithmHillClimb.h"

ZumoHardware* hwd;
AlgorithmHillClimb* alg;

Zumo32U4ButtonA buttonA;

void initialize(){
    init(); //AVR init - timers and things
    
    Serial1.begin(57600);
    Wire.begin(); //Initialize I2C bus for compass/gyro
    
    hwd = new ZumoHardware;
    alg = new AlgorithmHillClimb(hwd, 100, 400);
    
    hwd->proxSensors->initThreeSensors(); //Initialize proximity sensors
    
    hwd->compass->init();
    hwd->compass->enableDefault();
    
    randomSeed(analogRead(0));
    
    //hwd->lcd->gotoXY(0,0);
    //hwd->lcd->print(alg->getName());
    
    hwd->buzzer->playMode(PLAY_AUTOMATIC);
}



int main(int argc, char* argv[])
{
    initialize();
    
    static uint16_t last_time = 0;
    static bool stop = false;
    
    buttonA.waitForButton();
    
    while(1){
        uint16_t dt = millis() - last_time;
        if(dt >= 100){
            alg->step(dt);         
            
            //Dump the Z reading from the accelerometer for debugging            
            char buf[8];
            sprintf(buf, "%8.6f", sqrt(alg->getAccelXf()*alg->getAccelXf() + alg->getAccelYf()*alg->getAccelYf()));
            Serial1.print('a');
            Serial1.println(buf);
            //hwd->lcd->gotoXY(0,1);
            //hwd->lcd->print(buf);
            
            
            last_time = millis();
        }
    }
    
    delete alg;
    delete hwd;
}