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
    alg = new AlgorithmHillClimb(hwd);
    
    hwd->proxSensors->initThreeSensors(); //Initialize proximity sensors
    
    hwd->compass->init();
    hwd->compass->enableDefault();
    
    hwd->compass->m_min = (LSM303::vector<int16_t>){-5450, -5633, -1190};
    hwd->compass->m_max = (LSM303::vector<int16_t>){-912, -2516, +1164};    
    
    hwd->gyro->init();
    hwd->gyro->enableDefault();
    
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
    
    LowpassFilter<float> xyMag(0.9f);
    
    while(1){
        uint16_t dt = millis() - last_time;
        if(dt >= 100){
            alg->step(dt);         
            
            //Dump the XYmag reading from the accelerometer for debugging            
            logger.printXYAccelMag(xyMag.getFilteredValue(sqrt(alg->getAccelXf()*alg->getAccelXf() + alg->getAccelYf()*alg->getAccelYf())));
            //logger.printXYAccelMag(xyMag.getFilteredValue(alg->getAccelX()));
            logger.printPitch(alg->pitchFiltered());
            logger.printHeading(alg->yawFiltered());
            
            last_time = millis();
        }
    }
    
    delete alg;
    delete hwd;
}