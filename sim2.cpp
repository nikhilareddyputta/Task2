#include <bits/stdc++.h>
#include <iostream>     // Input Output functions 
#include <sstream>      // Converts a string into an integer
#include <vector>       // To use vectors
#include <windows.h>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

class VEHICLE{
    public: string type;
    public: string color;
    public: int Id;
    public: int length;
    public: int width;
    public: int speed; 
    public: int maxSpeed;
    public: int maxAcc;
    public: int x_pos;
    public: int y_pos;
    VEHICLE(string type,string color,int Id,int length,int width,int speed,int maxSpeed,int maxAcc,int x_pos,int y_pos){
        this->type = type;
        this->color = color;
        this->Id = Id;
        this->length = length;
        this->width = width;
        this->speed = speed;
        this->maxSpeed = maxSpeed;
        this->maxAcc = maxAcc;
        this->x_pos = x_pos;
        this->y_pos = y_pos;
    }
};

vector<VEHICLE> objects;   // Vector which contains all types of Vehicles
int roadLength,roadWidth,roadId,roadSignal;bool red = true;int cont =1;int gen = 0; //Variables to store the Road Parameters 
    string VehicleType;int parameter;int defaultSpeed=-1; int defaultAcc=-1;  //Variables to read the Vehicle Parameters
    bool readWord = true;bool overtake = true;bool infAcc = false;string filename,word,word1,word2;
    // We read Road and Vehicle Parameters here  
fstream inFile;
int time1=0;int id = 0;int c1=0;int c2=0;//int time = 0;
vector<vector<VEHICLE> > lane;
vector<VEHICLE> myVector;
        

int getIndex(vector<vector<VEHICLE> > lane,int k){
    unsigned int rows = lane.size();
    for(unsigned int i=0;i<=rows-k;i++){
        bool temp = true;
        for(unsigned int j=i;j<i+k;j++){
           if(lane[j].size() != 0) {
              VEHICLE v = (lane[j][(lane[j].size()-1)]);
              int x = v.x_pos - v.length;
              if(x<=0){
                 temp = false;
                 i = i+(v.width-1);
                 j = i+k;
              } 
           }
        }
        if(temp == true){ return ((int) i);}
    } 
    return (-1);
}
vector<int> getIndexVector(vector<vector<VEHICLE> > lane,int k){
    vector<int> Index;
    unsigned int rows = lane.size();
    for(unsigned int i=0;i<=rows-k;i++){
        bool temp = true;
        for(unsigned int j=i;j<i+k;j++){
           if(lane[j].size() != 0) {
              VEHICLE v = (lane[j][(lane[j].size()-1)]);
              int x = v.x_pos - v.length;
              if(x<=0){
                 temp = false;
                 i = i+(v.width-1);
                 j = i+k;
              } 
           }
        }
        if(temp == true){Index.push_back(((int) i));}
    }
    return Index; 
}
int distance(vector<vector<VEHICLE> > lane,int index,int maxSpeed,int k){
    int temp = (maxSpeed-1);
    for(unsigned int j=index;j<index+k;j++){
        if(lane[j].size() != 0){
            VEHICLE v = (lane[j][(lane[j].size()-1)]);
            int x = v.x_pos - v.length;
            if(x<temp) temp = x; 
        }
    }
    return temp;
}

vector<VEHICLE> sortVehicles(vector<vector<VEHICLE> > myVector){
    vector<VEHICLE> result;
    for(unsigned int i=0;i<myVector.size();i++){
        for(unsigned int j=0;j<myVector[i].size();j++){
            result.push_back(myVector[i][j]);
        }
    }
    if(result.size()>=1){
    int maxIndex;unsigned int j;unsigned int i;
    for(i=0;i<result.size()-1;i++){
        maxIndex = i;
        for(j=i+1;j<result.size();j++){
            if(result[maxIndex].x_pos < result[j].x_pos){
                maxIndex =  j;
            }
        }
        if(maxIndex != i){
        VEHICLE temp = result[i];
        result.erase(result.begin()+i);
        result.insert(result.begin()+i,result[maxIndex-1]);
        result.erase(result.begin()+maxIndex);
        result.insert(result.begin()+maxIndex,temp);
        }
    }
    }
    return result;
}

int findVehicleIndex(vector<VEHICLE> v,string type){
    for(unsigned int i=0;i<v.size();i++){
        if(v[i].type == type){
            return i;
        }
    }
    return (-1);
}

int findPositionInLanes(int* arr,int i,int width,int value){
    for(unsigned int j=i;j<i+width;j++){
        if(arr[j] < value) value = arr[j];
    }
    return value;
}
int overTakeNthLane(int* distSoFar,int max,int dist,int n,vector<VEHICLE> myVector,int index,int roadWidth){
    VEHICLE v = myVector[index];
    int w = v.width;
    bool flag = true;
    if(n >= 0 && n < roadWidth){
        for(int j=index+1;j<myVector.size();j++){
            if(myVector[j].y_pos == n){
                if(myVector[j].x_pos > v.x_pos-v.length) flag = false;  //Check >=
            }
        }
        int d0 = findPositionInLanes(distSoFar,n,w,max);
        
        if(flag == true && d0 > dist){
            return d0;
        }
        return (-1);
    }
    else return (-1);
}
int findPresentIndex(vector<VEHICLE> vec,int id){
    for(unsigned int i=0;i<vec.size();i++){
        if(vec[i].Id == id) return i;
    }
    return -1;
}
int findNewIndex(vector<VEHICLE> vec,int x){
    for(unsigned int i=0;i<vec.size();i++){
        if(vec[i].x_pos < x){
            return i;
        }
    }
    return 0;
}
vector<float> color_RGB(string colour)
{   
    vector<float> RGB;
    for(int i = 0; i<3; i++)
        RGB.push_back(0.0f);
    if(colour == "red" ||colour == "RED")
        {RGB[0] = 1.0f;RGB[1] = 0.0f;RGB[2] = 0.0f;}
    else if(colour == "green"||colour == "GREEN")
        {RGB[0] = 0.0f;RGB[1] = 1.0f;RGB[2] = 0.0f;}
    else if(colour == "blue"||colour == "BLUE")
        {RGB[0] = 0.0f;RGB[1] = 0.0f;RGB[2] = 1.0f;}
    return RGB; 
}


vector<VEHICLE>  myVectorCopy;;

void update(int value){
      //UPDATING TIME AND PRINTING BOUNDARIES
        if(readWord == true) inFile >> word;
        if(word != "Signal")
        time1 = time1 + 1;
        for(int i=0;i<roadLength;i++){
            cout << "-";
        }
        cout << "\n";
      //END OF TIME UPDATION AND PRINTING BOUNDARIES
        int distSoFar[roadWidth];
        if(word == "Signal"){
            inFile >> word1;
            if(word1 == "RED") red = true;
            else red = false;
        }
        if(word == "Pass"){
            inFile >> word1;
            stringstream temp(word1);
            temp >> c1;c2 = 0;word = "xxx";readWord=false;
            c1 = c1-1;
        }
        if(word == "xxx"){
           if(c2 == c1){
            c2=0;c1;0;readWord=true;
           }else c2=c2+1;
        }
        // Updation of positions of Vehicles when it is not a signal turn off/on command
        if(word != "Signal"){
        // myVector has all the vehicles sorted by their x position
        vector<VEHICLE> myVector = sortVehicles(lane);  
        //It keeps track of the updated length of road in different lanes
        for(int i=0;i<roadWidth;i++){
            distSoFar[i] = 2*roadLength;         
        }
        //Updating the position of each Vehicle one by one with the farthest first
        for(unsigned int i=0;i<myVector.size();i++){
            VEHICLE v=myVector[i];
            if(v.x_pos+v.maxSpeed-v.length >= roadLength){
                int laneNum = v.y_pos;int num = v.Id;
                for(unsigned int k=0;k<lane[laneNum].size();k++){
                    if(lane[laneNum][k].Id == num){
                        lane[laneNum].erase(lane[laneNum].begin()+k);
                    }
                }
                distSoFar[laneNum] = 2*roadLength;  
            }else{                                              /// int temp1 = v.x_pos + v.maxSpeed;
                int laneNum = v.y_pos;int w = v.width;          /// v.speed = v.speed + v.maxAcc or v.speed = v.maxSpeed
                int temp1;int num = v.Id;int temp;              /// temp1 = v.x_pos+(v.speed+(v.maxAcc)/2) or v.xpos + v.MaxSpeed
                if(v.speed+v.maxAcc>=v.maxSpeed||infAcc == true) temp1 = v.x_pos+v.maxSpeed;
                else temp1 = v.x_pos+(v.speed+(v.maxAcc)/2);
                int max = temp1;
                //Finding the max x position that a vehicle v can move.The x position is in temp1
                int newYPOS = v.y_pos;int newIndex;int presentIndex;
                for(unsigned int j=v.y_pos;j<v.y_pos+w;j++){
                    if(distSoFar[j] < temp1) temp1 = distSoFar[j];
                }
                if(v.y_pos+1 < roadWidth){
                    int d = overTakeNthLane(distSoFar,max,temp1,v.y_pos+1,myVector,i,roadWidth);   //int overTakeNthLane(int* distSoFar,int dist,int n,vector<VEHICLE> myVector,int index,int roadWidth)
                    if(d != (-1) && d > temp1){
                        temp1 = d;
                        newYPOS = v.y_pos+1;
                        newIndex = findNewIndex(lane[v.y_pos+1],v.x_pos);
                        presentIndex = findPresentIndex(lane[v.y_pos],v.Id);
                    }
                }
                if(v.y_pos-1 >= 0){
                    int d = overTakeNthLane(distSoFar,max,temp1,v.y_pos-1,myVector,i,roadWidth);
                    if(d != (-1) && d > temp1){
                        temp1 = d;
                        newYPOS = v.y_pos-1;
                        newIndex = findNewIndex(lane[v.y_pos-1],v.x_pos);
                        presentIndex = findPresentIndex(lane[v.y_pos],v.Id);
                    }
                }
                //Updating the x position such thst it does not cross the signal when signal is red.
                if(red ==true && (temp1>=roadSignal-1 && v.x_pos<roadSignal-1)) temp = roadSignal-2;   //Should I have <= or <
                else temp = temp1;
                //Updating the length of the road covered till now among different lanes
                if(newYPOS == v.y_pos || overtake == false){
                   for(unsigned int j=v.y_pos;j<v.y_pos+w;j++){
                    distSoFar[j] = temp - v.length;
                   }
                   for(unsigned int k=0;k<lane[laneNum].size();k++){
                      if(lane[laneNum][k].Id == num){
                          lane[laneNum][k].speed = temp - lane[laneNum][k].x_pos;
                          lane[laneNum][k].x_pos = temp;
                      }
                   }
                }else{
                    lane[v.y_pos].erase(lane[v.y_pos].begin()+presentIndex);
                    v.x_pos = temp;v.y_pos=newYPOS;v.speed=temp-v.x_pos;
                    lane[newYPOS].insert(lane[newYPOS].begin()+newIndex,v);
                }
                
                //Finding the vehicle on the road with VehicleId = num and updating its x position
            }
        }
        }
        // Generation of Cars, Buses, bikes, Trucks and other Vehicles
        if(findVehicleIndex(objects,word) != -1){
            int index = findVehicleIndex(objects,word);
            int length = objects[index].length;int width = objects[index].width;
            int maxSpeed = objects[index].maxSpeed;int maxAcc = objects[index].maxAcc;
            int y_pos=-1;vector<int> IndexVector = getIndexVector(lane,width);int initPos=-1; // What if ypos is -1 ?If ypos = -1 then vehicle will not be generated.It will be ignored
            for(unsigned int i=0;i<IndexVector.size();i++){
                int temp1 = IndexVector[i];
                int temp2 = distSoFar[temp1];
                if(initPos<temp2){
                    y_pos = temp1;initPos = temp2;
                }
            }
            if(y_pos>=0){
                int x_pos;
                inFile >> word1;  //Color of the vehicle is stored in word1
                if(gen == 1) x_pos = distance(lane,y_pos,maxSpeed,width);
                else{
                    x_pos = distance(lane,IndexVector[0],maxSpeed,width);
                    y_pos = IndexVector[0];
                } 
                VEHICLE temp(word,word1,id,length,width,(x_pos+1),maxSpeed,maxAcc,x_pos,y_pos);
                lane[y_pos].push_back(temp);
                id = id+1;
                readWord = true;
            }
            else{
                if(cont == 1){
                    readWord = false;
                }
                else{
                    inFile >> word1;readWord = true;
                }
            }
        }
        //Encoding the signal as '|' in a 2D Matrix at the correct position
        char mat[roadWidth][roadLength];
        for(int i=0;i<roadWidth;i++){
            for(int j=0;j<roadLength;j++){
                mat[i][j] = ' ';
            }
            if(red == true) mat[i][roadSignal-1] = '|';
        }
        //Encoding the objects as Characters in a 2D Matrix
        for(unsigned int i=0;i<roadWidth;i++){
          if(lane[i].size()>=1){
            for(unsigned int j=0;j<lane[i].size();j++){
                VEHICLE v = lane[i][j];
                int x1;int x2= (v.x_pos)%roadLength;int y = v.y_pos; //If we want a smooth change remove %roadLength and simulate it 
                int length = v.length; int width = v.width;
                if(v.x_pos-length <= -1){ x1=0;}
                else x1 = v.x_pos+1-length;
                for(int i1=y;i1<y+width;i1++){
                    for(int j1=x1;j1<=x2;j1++){
                        if(j1<roadLength) 
                        mat[i1][j1] = (v.type)[0];
                    }
                }
            }
          }
        }
        //Printing the answer to the terminal and checking for end of simulation(road is clear)
        bool clear = true;
        for(int i=0;i<roadWidth;i++){
            for(int j=0;j<roadLength;j++){
                if(mat[i][j] != ' ') clear = false;
                cout << mat[i][j];
            }
            cout << "\n";
        }
        for(int i=0;i<roadLength;i++){
            cout << "-";
        }
        cout << "\n";
        cout << "Time = " << time1<<" "<<"word: "<<word<<"\n";
        if(word == "END" && clear == true) return;
        
        //copy(myVector.begin(), myVector.end(), back_inserter(myVectorCopy));
        myVectorCopy = myVector; 
        update(0);
        //glutPostRedisplay(); // Inform GLUT that the display has changed
        //glutTimerFunc(500,update,0);//Call update after each 25 millisecond
}

void drawScene() {
glClear(GL_COLOR_BUFFER_BIT);

float signalX = roadSignal/roadLength, signalY = 0.75;
//green signal
if(red)
glColor3f(1,0,0);
else glColor3f(0.5,0,0);
glBegin(GL_POLYGON);
glVertex3f(signalX+0.05,0.875,0);
glVertex3f(signalX+0.05,0.775,0);
glVertex3f(signalX-0.05,0.775,0);
glVertex3f(signalX-0.05,0.875,0);
glEnd();
//red signal
if(red)
glColor3f(0,0.25,0);
else glColor3f(0,1,0);
glBegin(GL_POLYGON);
glVertex3f(signalX+0.05,0.725,0);
glVertex3f(signalX+0.05,0.625,0);
glVertex3f(signalX-0.05,0.625,0);
glVertex3f(signalX-0.05,0.725,0);
glEnd();

for(int i=0; i < myVectorCopy.size(); i++)
{ //cout <<myVectorCopy[i].color<<" ";
    //    cout << color_RGB(  )[0] << " " << color_RGB( myVectorCopy[i].color )[1] << " " << color_RGB( myVectorCopy[i].color )[2] << "\n"; 
        string color = myVectorCopy[i].color;
        float fact1 = roadLength/2, fact2 = 2*roadWidth;
        //vector<float> color = color_RGB( myVectorCopy[i].color);
        float x =(float) myVectorCopy[i].x_pos - roadLength/2, y = (float)myVectorCopy[i].y_pos - roadWidth/2, w = (float) myVectorCopy[i].width, lt = myVectorCopy[i].length;
       // cout << color << color_RGB(color)[0] << " "<< color_RGB(color)[1] << " "<< color_RGB(color)[2] << "\n";
        glBegin(GL_POLYGON);
        glColor3f(color_RGB(color)[0], color_RGB(color)[1], color_RGB(color)[2]);
        glVertex3f(x/fact1, -y/fact2,0);
        glVertex3f((x-lt)/fact1,-y/fact2,0);
        glVertex3f((x-lt)/fact1, -(y+w)/fact2,0);
        glVertex3f(x/fact1, -(y+w)/fact2,0);
        glEnd();
        //cout << x << " " << y << " " << x-lt << " " << y+w << "\n";;
}
glFlush();
glutSwapBuffers(); //Send the 3D scene to the screen
}


int main(int argc, char** argv){
    filename = "f.txt";
    inFile.open(filename.c_str());
    while(inFile >> word){
        if(word == "GenerateAtBestLane"){
            gen = 1;        //gen = 1 makes the vehicle generates the vehicle in the best possible
        }
        if(word == "Ignore"){
            cont = 0;       //cont = 1 generates the vehicles in the order specified by the config file.It doesnot ignore any vehicle if there is no space   
        }
        if(word == "NoOvertaking"){
            overtake = false;
        }
        if(word == "InfiniteAcceleration"){
            infAcc = true;
        }
        //Road Parametrs are read here
        if(word == "Road_Id" || word == "Road_Length" || word == "Road_Width" || word == "Road_Signal"){
            inFile >> word1;inFile >> word2;
            stringstream temp(word2);
            if(word == "Road_Id"){
                temp >> roadId;
            }else if(word == "Road_Length"){
                temp >> roadLength;
            }else if(word == "Road_Width"){
                temp >> roadWidth;
            }else{
                temp >> roadSignal;
            }
        }
        //Default values of MaxSpeed and MaxAcceleration are read here
        if(word == "Default_MaxSpeed" || word == "Default_Acceleration"){
            inFile >> word1;inFile >> word2;
            stringstream temp(word2);
            if(word == "Default_MaxSpeed"){
                temp >> defaultSpeed;
            }else{
                temp >> defaultAcc;
            }
        }
        //The type of Vehicle whose parametrs are to be read is determined here.We create a VEHICLE object with default parameters and push it on the vector
        if(word == "Vehicle_Type"){
            inFile >> word1;inFile >> word2;
            stringstream temp(word2);
            temp >> VehicleType;
            VEHICLE v(VehicleType,"GREEN",-1,0,0,0,defaultSpeed,defaultAcc,0,0);
            //VEHICLE temp("Bus",word1,id,busLength,busWidth,busMaxSpeed,busAcc,x_pos,y_pos);
            objects.push_back(v);
        }
        //The parametrs of the Vehicles which are on the vector are updated here
        if(word == "Vehicle_Length" || word == "Vehicle_Width" || word == "Vehicle_MaxSpeed" || word == "Vehicle_Acceleration"){
            inFile >> word1;inFile >> word2;
            stringstream temp(word2);
            temp >> parameter;
            int index = findVehicleIndex(objects,VehicleType);
            if(word == "Vehicle_Length"){
                objects[index].length = parameter;
            }else if(word == "Vehicle_Width"){
                objects[index].width = parameter;
            }else if(word == "Vehicle_MaxSpeed"){
                objects[index].maxSpeed = parameter;
            }else{
                objects[index].maxAcc = parameter;
            }
        }
        if(word == "START") break;
    }
    //lane is a 2d vector containing the vehicles in the lanes
    for(int i=0;i<roadWidth;i++){
        vector<VEHICLE> temp;
        lane.push_back(temp);
    } 
    update(0);
    //lane is a 2d vector containing the vehicles in the lanes
/*        glutInit(&argc, argv);
        glutInitWindowPosition(0,0);
        glutInitWindowSize(1000, 800);
        glClearColor (0.0, 0.0, 0.0, 0.0);
 //initialize viewing values 
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
     //   glOrtho(0, roadLength,-roadWidth,0.0, 0, 0);
        glutCreateWindow("two_dimension");
        
        glutDisplayFunc(drawScene);
    //  glutReshapeFunc(handleResize);
        glutTimerFunc(500,update,0);
        glutMainLoop(); */
    return 0; /* ISO C requires main to return int. */
}


//CHECK WHEN THE WORD IS SIGNAL
