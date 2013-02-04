#ifndef OBJECT3D_H
#define OBJECT3D_H

#include "ofMain.h"
#include "constants.h"
#include "customevent.h"

class Object3D
{
public:
    Object3D();
    virtual ~Object3D();
    void setup(int x, int y, int z, int size, int id);
    void draw();
    void drawPortrait(int x, int y);
    void drawProjectImage(int x, int y, int projectImageNumber);
    void setZoomLevel(int zoomLevel);
    void setFont(ofTrueTypeFont &font1);
    void setClosestToCamera(bool closest);
    void loadProjectImages();
    int getProjectImageSize(int imageNumber);
    bool getClosestToCamera();
    std::string getFullName();

    ofVec3f getPosition();
    int id;
    int totalNumberProjectImages;
    std::string letter;
    std::string project_title;
    std::string description;
    vector<string> letters;

    ofImage image_portrait;
    ofImage image_project_01;
    ofImage image_project_02;
    ofImage image_project_03;
    ofImage image_project_04;
    bool isMaster;
    bool isABC;
    bool projectImagesLoaded;

private:

    int x;
    int y;
    int z;

    ofTrueTypeFont *font1;

    std::string first_name;
    std::string last_name;
    std::string fullName;
    std::string file_project_01;
    std::string file_project_02;
    std::string file_project_03;
    std::string file_project_04;
    std::string file_portrait;

    int size;
    int zoomLevel;
    float sphereColor_1;
    float sphereColor_2;

    bool closestToCamera;


};

#endif // OBJECT3D_H
