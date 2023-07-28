#ifndef INPUT_H
#define INPUT_H
#include <string>
struct Input
{
    bool cameraLeft, cameraRight, cameraUp, cameraDown;
    std::string playerMove;
    int MAX_CAM_X_PAN;
    int MAX_CAM_Y_PAN;
    Input()
        : cameraLeft(false), cameraRight(false), cameraUp(false), cameraDown(false), playerMove("None"),
          MAX_CAM_X_PAN(0), MAX_CAM_Y_PAN(0)
    {

    }
};

#endif // INPUT_H
