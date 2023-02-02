// Not Finished
#include <Servo.h>
int ServoAmount = 0;

unsigned long DT = millis();

typedef struct ServoObject {
    Servo Instance;

    bool Active = true;

    int Id = ServoAmount++;

    float Rotation = 0.0;
    float TweenData[5] = {0,0.0,0.0,0.0,0.0}; // Active, Origin, Destination, Distance, Time
    float RotationMultiplier = 1.0;
    
    void (*Attach)(int) = (void (*)(int))Instance.attach; 

    void Begin(float newRotation, int Time) {
        int time = (Time) ? Time : 0;
        if (TweenData[0]==1) {
            return;
        }
        TweenData[0] = 1;

        TweenData[1] = Rotation;
        TweenData[2] = newRotation;
        TweenData[3] = fabs(newRotation-Rotation);
        TweenData[4] = time;
    }

    void End() {
        TweenData[0] = 0;
    }

    bool Update() {
        if (TweenData[0]==1) {
            int Direction = (TweenData[1]>TweenData[2]) ? -1 : 1;
            float RotationChange = fabs(TweenData[3]/(TweenData[4]*RotationMultiplier))*Direction;

            Rotation += RotationChange;

            if (TweenData[1]>TweenData[2] && Rotation<=TweenData[2] || TweenData[1]<TweenData[2] && Rotation>=TweenData[2]) {
                TweenData[0] = 0;
                Rotation = TweenData[2];
            }
        }
        

        return true;
    }
} newServo;

bool UpdateServo(newServo Object) {
    if (Object.Active==false) {
        return false;
    }
    int TimeBegan = millis();
    bool Result = Object.Update();
    Object.RotationMultiplier = millis()-TimeBegan;
    return Result;
}

newServo _MicroServo;

void setup() {
  _MicroServo.Attach(MicroServoPin);
  randomSeed(analogRead(0));
}

void loop() {
    DT = millis()-DT;

    bool _MicroServoSuccess = UpdateServo(_MicroServo);
    
    delay(DT);
}


