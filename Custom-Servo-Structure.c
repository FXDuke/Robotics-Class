// Not Finished
#include <Servo.h>
int ServoAmount = 0;

typedef struct ServoObject {
    Servo Instance;

    bool Active = true;

    int Id = ServoAmount++;

    float Rotation = 0.0;
    float TweenData[5] = {0,0.0,0.0,0.0,0.0}; // Active, Origin, Destination, Distance, Time

    void Rotate:Begin(float newRotation, int Time) {
        int time = (Time) ? Time : 0;
        if (TweenData[0]==1) {
            return;
        }
        TweenData[0] = 1;

        TweenData[1] = Rotation;
        TweenData[2] = newRotation;
        TweenData[3] = math.abs(newRotation-Rotation);
        TweenData[4] = time;
    }

    void Rotate:End() {
        TweenData[0] = 0;
    }

    bool Update(float DeltaTime) {
        delay(DeltaTime);
        if (TweenData[0]==1) {
            int Direction = (TweenData[1]>TweenData[2]) ? -1 : 1;
            float RotationChange = fabs(TweenData[3]/TweenData[4])*Direction;

            Rotation += RotationChange;

            if (TweenData[1]>TweenData[2] && Rotation<=TweenData[2] || TweenData[1]<TweenData[2] && Rotation>=TweenData[2]) {
                TweenData[0] = 0;
                Rotation = TweenData[2];
            }
        }
        

        return true;
    }
} newServo;

newServo _MicroServo;

void setup() {
  _MicroServo.Instance.attach(MicroServoPin);
  randomSeed(analogRead(0));
}

int DT = millis();

void loop() {
    DT = millis()-DT;

    _MicroServo.Update(DT);
}

