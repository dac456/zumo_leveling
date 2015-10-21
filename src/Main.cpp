#include "AlgorithmHillClimb.h"
#include "Logger.h"

ZumoHardware* hwd;
AlgorithmHillClimb* alg;

Zumo32U4ButtonA buttonA;
Logger logger;

void initialize(){
    init(); //AVR init - timers and things
    
    Serial1.begin(57600);
    Wire.begin(); //Initialize I2C bus for compass/gyro
    
    hwd = new ZumoHardware;
    alg = new AlgorithmHillClimb(hwd, 100, 400);
    
    hwd->proxSensors->initThreeSensors(); //Initialize proximity sensors
    
    hwd->compass->init();
    hwd->compass->enableDefault();
    
    hwd->gyro->init();
    
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
            
            //Dump the XYmag reading from the accelerometer for debugging            
            logger.printXYAccelMag(sqrt(alg->getAccelXf()*alg->getAccelXf() + alg->getAccelYf()*alg->getAccelYf()));
            logger.printPitch(alg->pitchFiltered());
            
            last_time = millis();
        }
    }
    
    delete alg;
    delete hwd;
}