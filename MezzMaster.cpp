//Plugins and Libraries------------------------------------------------------------------------------------------------------------------

#ifdef _WIN32   //Checks that this is running on windows, this is windows ultimate header tag.
#define WIN32_LEAN_AND_MEAN    //This is a windows header tag that reduces the size of the windows.h header file by excluding some of the less used APIs.
#define NOMINMAX    //This is a windows header tag that prevents the min and max macros from being defined in windows.h.  This is because we will calculate these an alternate way.
#include <windows.h>    //Includes the windows API.
#include <iostream>
#include <vector>
#include <fstream> // Include this header for std::ofstream
#include <ctime> // Include this header for date and time
#include <sstream> // Include this header for std::ostringstream
#include <algorithm> // Include this header for std::max
#include <string> // Include this header for std::string
#include <cmath> // Include this header for std::sqrt and other math functions
#include "hpdf.h" // Include the Haru PDF library header
#include <set> // Include this header for std::set
#include <iomanip> // Include this header for std::setprecision

//Global Variables------------------------------------------------------------------------------------------------------------------

//Variables related to UI elements
HWND hwnd;                                                          //This is a handle for the window.  Put here so it is "declared in scope" before its actually defined later.
std::string formattedDateTime;                                      //This is a string stream that will be used to format the date and time.
std::string softwareversion = "Build Version: 5-11-25";             //This is the version of the software.  This is a global variable that can be accessed anywhere in the program.
std::string outputpath = "C:\\Users\\Lando\\Desktop";               //This is the output path for the output file.  This is a global variable that can be accessed anywhere in the program.
static HWND window;                                                 //This is a global variable that contains windows variable window, which is the window we are creating.
bool platform_create_window(int width, int height, const char* title);
void platform_update_window();                                      
static bool running = true;
//Heading Items
HWND texttitle;                                             //Global Variable Text Field for the title of the software.
HWND textversion;                                           //Global Variable Text Field for the version of the software.
HWND textcreated;                                           //Global Variable "created by" text field.
HWND textreference;                                         //Global Variable for the ASCE label text field.
HWND textcurrentdate;                                       //Global Variable for the current date and time text field.
HWND textoutputlocation;                                    //Global Variable for the output location text box.
HWND boxoutputlocation;                                     //Global Variable for the output location text box.
//Generate Button
HWND buttongen;                                             //This is the global variable for the generate button
HWND buttondebug;                                           //This is the global variable for the debug button
//Load inputs
HWND textnumvertarraylabel;                                 //This is the global variable for the number of vertical bays text label.
HWND textnumhorizarraylabel;                                //This is the global variable for the number of horizontal bays text label.
HWND textbasedeadloadlabel;                                 //This is the global variable for the base dead load text label.
HWND textcollateralloadlabel;                               //This is the global variable for the collateral load text label.
HWND textliveloadlabel;                                     //This is the global variable for the live load text label.
HWND textroofliveloadlabel;                                 //This is the global variable for the roof live load text label.
HWND textflatroofsnowloadlabel;                             //This is the global variable for the flat roof snow load text label.
HWND textwindupliftlabel;                                   //This is the global variable for the wind uplift text label.
HWND textwinddownforcelabel;                                //This is the global variable for the wind downforce text label.
HWND boxnumvertarray;                                       //This is the global variable for the number of vertical bays text box.
HWND boxnumhorizarray;                                      //This is the global variable for the number of horizontal bays text box.
HWND boxbasedeadload;                                       //This is the global variable for the base dead load text box.
HWND boxcollateralload;                                     //This is the global variable for the collateral load text box.
HWND boxliveload;                                           //This is the global variable for the live load text box.
HWND boxroofliveload;                                       //This is the global variable for the roof live load text box.
HWND boxflatroofsnowload;                                   //This is the global variable for the flat roof snow load text box.
HWND boxwinduplift;                                         //This is the global variable for the wind uplift text box.
HWND boxwinddownforce;                                      //This is the global variable for the wind downforce text box.
//Foundation inputs
HWND textbearingpressurelabel;                              //This is the global variable for the bearing pressure text label.
HWND boxbearingpressure;                                    //This is the global variable for the bearing pressure text box.
//Bay Widths
HWND textbay1;                                              //This is the global variable for the width of bay 1 text label.
HWND textbay2;                                              //This is the global variable for the width of bay 2 text label.
HWND textbay3;                                              //This is the global variable for the width of bay 3 text label.
HWND textbay4;                                              //This is the global variable for the width of bay 4 text label.
HWND textbay5;                                              //This is the global variable for the width of bay 5 text label.
HWND textbay6;                                              //This is the global variable for the width of bay 6 text label.
HWND textbayHorizlabel;                                     //This is the global variable for the width of bay text label.
HWND textbayvertlabel;                                      //This is the global variable for the width of bay text label.
HWND boxHorizbay1;                                          //This is the global variable for the width of bay 1 text box.
HWND boxHorizbay2;                                          //This is the global variable for the width of bay 2 text box.
HWND boxHorizbay3;                                          //This is the global variable for the width of bay 3 text box.
HWND boxHorizbay4;                                          //This is the global variable for the width of bay 4 text box.
HWND boxHorizbay5;                                          //This is the global variable for the width of bay 5 text box.
HWND boxHorizbay6;                                          //This is the global variable for the width of bay 6 text box.
HWND boxVertbay1;                                           //This is the global variable for the width of bay 1 text box.
HWND boxVertbay2;                                           //This is the global variable for the width of bay 2 text box.
HWND boxVertbay3;                                           //This is the global variable for the width of bay 3 text box.
HWND boxVertbay4;                                           //This is the global variable for the width of bay 4 text box.
HWND boxVertbay5;                                           //This is the global variable for the width of bay 5 text box.
HWND boxVertbay6;                                           //This is the global variable for the width of bay 6 text box.
HBRUSH sharedbrush = NULL;                                  //This is a global variable that will be used to create a brush for the window.  This is used to set the background color of the window.
HBRUSH buttonBrush = NULL;                                  // Brush for button background color
HFONT hFontLarge = NULL;                                    //This is a global variable that will be used to create a font for the window.  This is used to set the font of the text in the window.

//Variables related to calculations
int v;                                                  //This is the number of vertical bays.  This is a global variable that can be accessed anywhere in the program.
int h;                                                  //This is the number of horizontal bays.  This is a global variable that can be accessed anywhere in the program.
int totalhorizontallength = 0;                          //This is the total width of the building.  This is a global variable that can be accessed anywhere in the program.
int totalverticallength = 0;                            //This is the total length of the building.  This is a global variable that can be accessed anywhere in the program.
int basedeadload;                                       //This is the dead load.  This is a global variable that can be accessed anywhere in the program.
int collateral;                                         //This is the collateral load.  This is a global variable that can be accessed anywhere in the program.
int liveload;                                           //This is the live load.  This is a global variable that can be accessed anywhere in the program.
int roofliveload;                                       //This is the roof live load.  This is a global variable that can be accessed anywhere in the program.
int flatroofsnowload;                                   //This is the flat roof snow load.  This is a global variable that can be accessed anywhere in the program.
int winduplift;                                         //This is the wind uplift.  This is a global variable that can be accessed anywhere in the program.
int winddownforce;                                      //This is the wind downforce.  This is a global variable that can be accessed anywhere in the program.
int bearingpressure;                                    //This is the bearing pressure.  This is a global variable that can be accessed anywhere in the program.
double drawingscaleinch = 0.125 ;                       //Drawing scale is set to 1/8" = 1'-0" by default.  This can be changed to any value.
bool debugtest = false;                                 //This is the debug mode.  This is a global variable that can be accessed anywhere in the program.
int DBdeadloadfudgefactor = 0.9;                        //This is the dead load fudge factor.  This is a global variable that can be accessed anywhere in the program.

//Variables Related to Concrete Design
int concretecompressivestrength = 4000;                //This is the concrete compressive strength.  This is a global variable that can be accessed anywhere in the program.
int concreteunitweight = 150;                          //This is the concrete unit weight.  This is a global variable that can be accessed anywhere in the program.
int baseplatedimension = 12;                           //This is the base plate dimension.  This is a global variable that can be accessed anywhere in the program.

// Global Matrices
std::vector<std::vector<double>> tributaryareamatrix;       // Matrix for tributary areas
std::vector<std::vector<double>> BaseDeadLoadMatrix;        // Matrix for base dead loads
std::vector<std::vector<double>> CollateralLoadMatrix;      // Matrix for collateral loads
std::vector<std::vector<double>> TotalDeadLoadMatrix;       // Matrix for total dead loads
std::vector<std::vector<double>> TotalLiveLoadMatrix;       // Matrix for total live loads
std::vector<std::vector<double>> TotalRoofLiveLoadMatrix;   // Matrix for total roof live loads
std::vector<std::vector<double>> TotalSnowLoadMatrix;       // Matrix for total snow loads
std::vector<std::vector<double>> TotalWindLoadMatrix;       // Matrix for total wind loads
std::vector<std::vector<double>> TotalWinddownForceMatrix;  // Matrix for total wind down forces
// Matrices for ASD combinations
std::vector<std::vector<double>> ASDCombo1;                 // ASD Combination 1
std::vector<std::vector<double>> ASDCombo2;                 // ASD Combination 2
std::vector<std::vector<double>> ASDCombo3;                 // ASD Combination 3
std::vector<std::vector<double>> ASDCombo4;                 // ASD Combination 4
std::vector<std::vector<double>> ASDCombo5;                 // ASD Combination 5
std::vector<std::vector<double>> ASDCombo6;                 // ASD Combination 6
std::vector<std::vector<double>> ASDCombo7;                 // ASD Combination 7
// Matrices for LRFD combinations
std::vector<std::vector<double>> LRFDCombo1;                // LRFD Combination 1
std::vector<std::vector<double>> LRFDCombo2;                // LRFD Combination 2
std::vector<std::vector<double>> LRFDCombo3;                // LRFD Combination 3
std::vector<std::vector<double>> LRFDCombo4;                // LRFD Combination 4
std::vector<std::vector<double>> LRFDCombo5;                // LRFD Combination 5
std::vector<std::vector<double>> LRFDCombo6;                // LRFD Combination 6
std::vector<std::vector<double>> LRFDCombo7;                // LRFD Combination 7
// Matrices for Service Load combinations
std::vector<std::vector<double>> ServiceLoadCombo1;        // Service Load Combination 1
std::vector<std::vector<double>> ServiceLoadCombo2;        // Service Load Combination 2
std::vector<std::vector<double>> ServiceLoadCombo3;        // Service Load Combination 3
std::vector<std::vector<double>> ServiceLoadCombo4;        // Service Load Combination 4
std::vector<std::vector<double>> ServiceLoadCombo5;        // Service Load Combination 5
std::vector<std::vector<double>> ServiceLoadCombo6;        // Service Load Combination 6
std::vector<std::vector<double>> ServiceLoadCombo7;        // Service Load Combination 7
std::vector<std::vector<double>> ServiceLoadCombo8;        // Service Load Combination 8
// Matrices for controlling loads
std::vector<std::vector<double>> ControllingBearingLoads;   // Matrix for controlling bearing loads
std::vector<std::vector<double>> ControllingUpliftLoads;    // Matrix for controlling uplift loads
// Matrices for Design Outputs
std::vector<std::vector<double>> FoundationSizeMatrix; // Matrix for foundation sizes
std::vector<std::vector<double>> FoundationSizeMatrixBearing ; 
std::vector<std::vector<double>> FoundationSizeMatrixUplift; // Matrix for foundation sizes
std::vector<std::vector<double>> FoundationThicknessMatrix; // Matrix for foundation thicknesses
std::vector<std::vector<std::string>> FoundationControlMatrix; // Matrix for foundation controlling load reference
//Bay Width variables
int bay1Horizwidth;                                     //This is the width of bay 1 in the horizontal direction.  This is a global variable that can be accessed anywhere in the program.
int bay2Horizwidth;                                     //This is the width of bay 2 in the horizontal direction.  This is a global variable that can be accessed anywhere in the program.
int bay3Horizwidth;                                     //This is the width of bay 3 in the horizontal direction.  This is a global variable that can be accessed anywhere in the program.
int bay4Horizwidth;                                     //This is the width of bay 4 in the horizontal direction.  This is a global variable that can be accessed anywhere in the program.
int bay5Horizwidth;                                     //This is the width of bay 5 in the horizontal direction.  This is a global variable that can be accessed anywhere in the program.
int bay6Horizwidth;                                     //This is the width of bay 6 in the horizontal direction.  This is a global variable that can be accessed anywhere in the program.
int bay1Vertwidth;                                      //This is the width of bay 1 in the vertical direction.  This is a global variable that can be accessed anywhere in the program.
int bay2Vertwidth;                                      //This is the width of bay 2 in the vertical direction.  This is a global variable that can be accessed anywhere in the program.
int bay3Vertwidth;                                      //This is the width of bay 3 in the vertical direction.  This is a global variable that can be accessed anywhere in the program.
int bay4Vertwidth;                                      //This is the width of bay 4 in the vertical direction.  This is a global variable that can be accessed anywhere in the program.
int bay5Vertwidth;                                      //This is the width of bay 5 in the vertical direction.  This is a global variable that can be accessed anywhere in the program.
int bay6Vertwidth;                                      //This is the width of bay 6 in the vertical direction.  This is a global variable that can be accessed anywhere in the program.
std::vector<int> horizontalbaywidthlist;                // Global variable for horizontal bay widths
std::vector<int> verticalbaywidthlist;                  // Global variable for vertical bay widths

//Functions------------------------------------------------------------------------------------------------------------------

//function declarations
void getintvalue();
void date_and_time();
void generatehandler();
void generateloads();
void generatefoundations();
void platform_update_window();
void generateoutputfile();
void pdfoutputfile();
void feetpointconversion(int dimension, double scale, int& output);

//This function grabs value from a text box and converts it to an integer
void getintvalue(HWND boxname, int& variable){
    char buffer[10];                                        //This creates a buffer to hold the string value of the text box.
    GetWindowTextA(boxname, buffer, sizeof(buffer));        //This gets the text from the text box and stores it in the buffer.
    variable = std::atoi(buffer);                           //This sets the global variable to the converted value.
};

//Date and Time format
void date_and_time() {
    // Get current date and time
    std::time_t now = std::time(nullptr);
    std::tm localTime;
    localtime_s(&localTime, &now);

    // Format time to 12-hour format with AM/PM
    char timeBuffer[100];
    std::strftime(timeBuffer, sizeof(timeBuffer), "%I:%M:%S %p", &localTime);

    // Manually format the date and time
    formattedDateTime = std::to_string(localTime.tm_mon + 1) + "-" +
                        std::to_string(localTime.tm_mday) + "-" +
                        std::to_string(localTime.tm_year + 1900) + " " +
                        timeBuffer;
};

//Mezzanine Generation Handler
void generatehandler(){
        
    if(debugtest == true){
        //Sets the values of the variables to test values.  This is used for debugging purposes.
        v = 5;                                                                                                  //This sets the number of vertical bays to 2.
        h = 3;                                                                                                  //This sets the number of horizontal bays to 2.
        basedeadload = 50;                                                                                      //This sets the base dead load to 20 psf.
        collateral = 8;                                                                                         //This sets the collateral load to 10 psf.
        liveload = 100;                                                                                         //This sets the live load to 40 psf.
        roofliveload = 20;                                                                                     //This sets the roof live load to 0 psf.
        flatroofsnowload = 15;                                                                                  //This sets the flat roof snow load to 30 psf.
        winduplift = 15;                                                                                        //This sets the wind uplift to 15 psf.
        winddownforce = 2;                                                                                      //This sets the wind downforce to 2 psf.
        bay1Horizwidth = 20;                                                                                    //This sets the width of bay 1 in the horizontal direction to 10 feet.
        bay2Horizwidth = 20;                                                                                    //This sets the width of bay 2 in the horizontal direction to 10 feet.
        bay3Horizwidth = 30;                                                                                    //This sets the width of bay 3 in the horizontal direction to 10 feet.
        bay4Horizwidth = 10;                                                                                    //This sets the width of bay 4 in the horizontal direction to 10 feet.
        bay5Horizwidth = 10;                                                                                    //This sets the width of bay 5 in the horizontal direction to 10 feet.
        bay6Horizwidth = 10;                                                                                    //This sets the width of bay 6 in the horizontal direction to 10 feet.
        bay1Vertwidth = 20;                                                                                     //This sets the width of bay 1 in the vertical direction to 20 feet.
        bay2Vertwidth = 20;                                                                                     //This sets the width of bay 2 in the vertical direction to 20 feet.
        bay3Vertwidth = 20;                                                                                     //This sets the width of bay 3 in the vertical direction to 20 feet.
        bay4Vertwidth = 20;                                                                                     //This sets the width of bay 4 in the vertical direction to 20 feet.
        bay5Vertwidth = 20;                                                                                     //This sets the width of bay 5 in the vertical direction to 20 feet.
        bay6Vertwidth = 20;                                                                                     //This sets the width
        bearingpressure = 2000 ;                                                                                //This sets the bearing pressure to 2 ksf.
    };                                                                                      
    if(debugtest == false){
    //Gets values from input boxes and converts them to integers.  Sets variables
        getintvalue(boxnumvertarray, v);                                                                            //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable v.
        getintvalue(boxnumhorizarray, h);                                                                           //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable h.
        getintvalue(boxbasedeadload, basedeadload);                                                                 //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable dead.
        getintvalue(boxcollateralload, collateral);                                                                 //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable collateral. 
        getintvalue(boxliveload, liveload);                                                                         //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable live.
        getintvalue(boxroofliveload, roofliveload);                                                               //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable roofliveload.
        getintvalue(boxflatroofsnowload, flatroofsnowload);                                                         //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable flatroofsnowload.
        getintvalue(boxwinduplift, winduplift);                                                                     //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable winduplift.
        getintvalue(boxwinddownforce, winddownforce);                                                             //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable winddownforce. 
        getintvalue(boxHorizbay1, bay1Horizwidth);                                                                  //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable bay1Horizwidth.
        getintvalue(boxHorizbay2, bay2Horizwidth);                                                                  //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable bay2Horizwidth.
        getintvalue(boxHorizbay3, bay3Horizwidth);                                                                  //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable bay3Horizwidth.
        getintvalue(boxHorizbay4, bay4Horizwidth);                                                                  //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable bay4Horizwidth.
        getintvalue(boxHorizbay5, bay5Horizwidth);                                                                  //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable bay5Horizwidth.
        getintvalue(boxHorizbay6, bay6Horizwidth);                                                                  //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable bay6Horizwidth.
        getintvalue(boxVertbay1, bay1Vertwidth);                                                                    //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable bay1Vertwidth.
        getintvalue(boxVertbay2, bay2Vertwidth);                                                                    //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable bay2Vertwidth.
        getintvalue(boxVertbay3, bay3Vertwidth);                                                                    //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable bay3Vertwidth.
        getintvalue(boxVertbay4, bay4Vertwidth);                                                                    //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable bay4Vertwidth.
        getintvalue(boxVertbay5, bay5Vertwidth);                                                                    //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable bay5Vertwidth.
        getintvalue(boxVertbay6, bay6Vertwidth);                                                                    //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable bay6Vertwidth.
        getintvalue(boxbearingpressure, bearingpressure);                                                           //This calls the getintvalue function below.  This gets the value from the text box and sets it to the global variable bearingpressure.     
        bearingpressure = bearingpressure * 1000;                                                                   //This converts the bearing pressure from kips to pounds.  This is done because the loads are in pounds.
    };
    
    //Input Error Tree
    int errorcode = 0;                                                                                          //This is the error code.  This is set to 0 by default.
    if(v == 0 || h == 0){                                                                                       //This checks if the number of vertical or horizontal bays is 0.  If it is, it will not run the program.
        errorcode = 1;                                                                                          //This sets the error code to 1.
    };
    if(v < 0 || h < 0){                                                                                         //This checks if the number of vertical or horizontal bays is less than 0.  If it is, it will not run the program.
        errorcode = 2;                                                                                          //This sets the error code to 1.
    };
    if(bearingpressure <= 0){                                                                                   //This checks if the bearing pressure is less than or equal to 0.  If it is, it will not run the program.
        errorcode = 3;                                                                                          //This sets the error code to 3.
    };
    switch (errorcode){                                                                                         //This is the switch statement for the error code.
        case 1:                                                                                                 //This is the case for error code 1.
            MessageBoxA(hwnd, "Please enter a value for the number of bays.", "Error", MB_ICONHAND);            //This creates a message box that says "Please enter a value for the number of bays." when the button is clicked.
            break;                                                                                              //This breaks out of the switch statement.
        case 2:
            MessageBoxA(hwnd, "Please enter a positive value for the number of bays.", "Error", MB_ICONHAND);   //This creates a message box that says "Please enter a positive value for the number of bays." when the button is clicked.
            break;
        case 3:
            MessageBoxA(hwnd, "Please enter a positive value for the bearing pressure.", "Error", MB_ICONHAND);   //This creates a message box that says "Please enter a positive value for the bearing pressure." when the button is clicked.
            break;
        default:                                                                                                //This is the default case.
            ::MessageBeep(MB_OK);                                                                               //Plays windows ERROR sound.  
            MessageBoxA(hwnd, "Designing Mezzanine...", "MezzMaster", MB_OK);                                   //This creates a message box that says "Designing Mezzanine..." when the button is clicked.
            generateloads();                                                                                    //This calls the generateloads function.  This is where the loads are generated.
            generatefoundations();                                                                              //This calls the generatefoundations function.  This is where the foundations are generated.
            generateoutputfile();                                                                               //This calls the generateoutputfile function.  This is where the output file is generated.
            pdfoutputfile();                                                                                    //This calls the pdfoutputfile function.  This is where the PDF output file is generated.
            break;                                                                                              //This breaks out of the switch statement.
    };
};

void generateloads(){
    // Create a vector to hold the widths of vertical bays
    verticalbaywidthlist.clear(); // Clear the vector to ensure it's empty before adding new values
    for (int i = 1; i <= v; ++i) {
        switch (i) {
            case 1:
                verticalbaywidthlist.push_back(bay1Vertwidth);
                break;
            case 2:
                verticalbaywidthlist.push_back(bay2Vertwidth);
                break;
            case 3:
                verticalbaywidthlist.push_back(bay3Vertwidth);
                break;
            case 4:
                verticalbaywidthlist.push_back(bay4Vertwidth);
                break;
            case 5:
                verticalbaywidthlist.push_back(bay5Vertwidth);
                break;
            case 6:
                verticalbaywidthlist.push_back(bay6Vertwidth);
                break;
            default:
                MessageBoxA(hwnd, "Critical Error: Failed to Create Vertical Bay List. Did number of bays exceed maximum?", "Error", MB_ICONHAND);
                running = false; // Set running to false to exit the program
                break;
        }
    }

    // Create a vector to hold the widths of horizontal bays
    horizontalbaywidthlist.clear(); // Clear the vector to ensure it's empty before adding new values
    for (int i = 1; i <= h; ++i) {
        switch (i) {
            case 1:
                horizontalbaywidthlist.push_back(bay1Horizwidth);
                break;
            case 2:
                horizontalbaywidthlist.push_back(bay2Horizwidth);
                break;
            case 3:
                horizontalbaywidthlist.push_back(bay3Horizwidth);
                break;
            case 4:
                horizontalbaywidthlist.push_back(bay4Horizwidth);
                break;
            case 5:
                horizontalbaywidthlist.push_back(bay5Horizwidth);
                break;
            case 6:
                horizontalbaywidthlist.push_back(bay6Horizwidth);
                break;
            default:
                MessageBoxA(hwnd, "Critical Error: Failed to Create Horizontal Bay List. Did number of bays exceed maximum?", "Error", MB_ICONHAND);
                running = false; // Set running to false to exit the program
                break;
        }
    }

    // Clear global matrices
    tributaryareamatrix.clear();
    BaseDeadLoadMatrix.clear();
    CollateralLoadMatrix.clear();
    TotalDeadLoadMatrix.clear();
    TotalLiveLoadMatrix.clear();
    TotalRoofLiveLoadMatrix.clear();
    TotalSnowLoadMatrix.clear();
    TotalWindLoadMatrix.clear();
    TotalWinddownForceMatrix.clear();
    ASDCombo1.clear();
    ASDCombo2.clear();
    ASDCombo3.clear();
    ASDCombo4.clear();
    ASDCombo5.clear();
    ASDCombo6.clear();
    ASDCombo7.clear();
    LRFDCombo1.clear();
    LRFDCombo2.clear();
    LRFDCombo3.clear();
    LRFDCombo4.clear();
    LRFDCombo5.clear();
    LRFDCombo6.clear();
    LRFDCombo7.clear();
    ServiceLoadCombo1.clear();
    ServiceLoadCombo2.clear();
    ServiceLoadCombo3.clear();
    ServiceLoadCombo4.clear();
    ServiceLoadCombo5.clear();
    ServiceLoadCombo6.clear();
    ServiceLoadCombo7.clear();
    ServiceLoadCombo8.clear();
    ControllingBearingLoads.clear();
    ControllingUpliftLoads.clear();
    FoundationSizeMatrix.clear();
    FoundationSizeMatrixBearing.clear();
    FoundationSizeMatrixUplift.clear();
    FoundationThicknessMatrix.clear();
    FoundationControlMatrix.clear();

    // Resize global matrices to the correct dimensions
    tributaryareamatrix.resize(v + 1, std::vector<double>(h + 1, 0));
    BaseDeadLoadMatrix.resize(v + 1, std::vector<double>(h + 1, 0));
    CollateralLoadMatrix.resize(v + 1, std::vector<double>(h + 1, 0));
    TotalDeadLoadMatrix.resize(v + 1, std::vector<double>(h + 1, 0));
    TotalLiveLoadMatrix.resize(v + 1, std::vector<double>(h + 1, 0));
    TotalRoofLiveLoadMatrix.resize(v + 1, std::vector<double>(h + 1, 0));
    TotalSnowLoadMatrix.resize(v + 1, std::vector<double>(h + 1, 0));
    TotalWindLoadMatrix.resize(v + 1, std::vector<double>(h + 1, 0));
    TotalWinddownForceMatrix.resize(v + 1, std::vector<double>(h + 1, 0));
    ASDCombo1.resize(v + 1, std::vector<double>(h + 1, 0));
    ASDCombo2.resize(v + 1, std::vector<double>(h + 1, 0));
    ASDCombo3.resize(v + 1, std::vector<double>(h + 1, 0));
    ASDCombo4.resize(v + 1, std::vector<double>(h + 1, 0));
    ASDCombo5.resize(v + 1, std::vector<double>(h + 1, 0));
    ASDCombo6.resize(v + 1, std::vector<double>(h + 1, 0));
    ASDCombo7.resize(v + 1, std::vector<double>(h + 1, 0));
    LRFDCombo1.resize(v + 1, std::vector<double>(h + 1, 0));
    LRFDCombo2.resize(v + 1, std::vector<double>(h + 1, 0));
    LRFDCombo3.resize(v + 1, std::vector<double>(h + 1, 0));
    LRFDCombo4.resize(v + 1, std::vector<double>(h + 1, 0));
    LRFDCombo5.resize(v + 1, std::vector<double>(h + 1, 0));
    LRFDCombo6.resize(v + 1, std::vector<double>(h + 1, 0));
    LRFDCombo7.resize(v + 1, std::vector<double>(h + 1, 0));
    ServiceLoadCombo1.resize(v + 1, std::vector<double>(h + 1, 0));
    ServiceLoadCombo2.resize(v + 1, std::vector<double>(h + 1, 0));
    ServiceLoadCombo3.resize(v + 1, std::vector<double>(h + 1, 0));
    ServiceLoadCombo4.resize(v + 1, std::vector<double>(h + 1, 0));
    ServiceLoadCombo5.resize(v + 1, std::vector<double>(h + 1, 0));
    ServiceLoadCombo6.resize(v + 1, std::vector<double>(h + 1, 0));
    ServiceLoadCombo7.resize(v + 1, std::vector<double>(h + 1, 0));
    ServiceLoadCombo8.resize(v + 1, std::vector<double>(h + 1, 0));
    ControllingBearingLoads.resize(v + 1, std::vector<double>(h + 1, 0));
    ControllingUpliftLoads.resize(v + 1, std::vector<double>(h + 1, 0));
    FoundationSizeMatrix.resize(v + 1, std::vector<double>(h + 1, 0));
    FoundationSizeMatrixBearing.resize(v + 1, std::vector<double>(h + 1, 0));
    FoundationSizeMatrixUplift.resize(v + 1, std::vector<double>(h + 1, 0));
    FoundationThicknessMatrix.resize(v + 1, std::vector<double>(h + 1, 0));
    FoundationControlMatrix.resize(v + 1, std::vector<std::string>(h + 1, ""));

    // Calculate tributary area matrix
    for (int x = 0; x <= v; ++x) {
        for (int y = 0; y <= h; ++y) {
            double verticalContribution = 0;
            double horizontalContribution = 0;

            if (x - 1 >= 0) {
                verticalContribution += verticalbaywidthlist[x - 1] / 2.0;
            }
            if (x < v) {
                verticalContribution += verticalbaywidthlist[x] / 2.0;
            }

            if (y - 1 >= 0) {
                horizontalContribution += horizontalbaywidthlist[y - 1] / 2.0;
            }
            if (y < h) {
                horizontalContribution += horizontalbaywidthlist[y] / 2.0;
            }

            tributaryareamatrix[x][y] = verticalContribution * horizontalContribution;
        }
    }

    //Populate global matrices with calculated values
    for (int x = 0; x <= v; ++x) {
        for (int y = 0; y <= h; ++y) {
            //Base Loads for Tributary Area
            BaseDeadLoadMatrix[x][y] = tributaryareamatrix[x][y] * basedeadload;
            CollateralLoadMatrix[x][y] = tributaryareamatrix[x][y] * collateral;
            TotalDeadLoadMatrix[x][y] = (basedeadload + collateral) * tributaryareamatrix[x][y];
            TotalLiveLoadMatrix[x][y] = tributaryareamatrix[x][y] * liveload;
            TotalRoofLiveLoadMatrix[x][y] = tributaryareamatrix[x][y] * roofliveload;
            TotalSnowLoadMatrix[x][y] = tributaryareamatrix[x][y] * flatroofsnowload;
            TotalWindLoadMatrix[x][y] = tributaryareamatrix[x][y] * winduplift;
            TotalWinddownForceMatrix[x][y] = tributaryareamatrix[x][y] * winddownforce;
            //ASD Combo Loads
            ASDCombo1[x][y] = TotalDeadLoadMatrix[x][y] + TotalLiveLoadMatrix[x][y] ;
            ASDCombo2[x][y] = TotalDeadLoadMatrix[x][y] + std::max(TotalSnowLoadMatrix[x][y], TotalRoofLiveLoadMatrix[x][y]);
            ASDCombo3[x][y] = TotalDeadLoadMatrix[x][y] + 0.75 * TotalLiveLoadMatrix[x][y] + 0.75 * std::max(TotalSnowLoadMatrix[x][y], TotalRoofLiveLoadMatrix[x][y]);
            ASDCombo4[x][y] = TotalDeadLoadMatrix[x][y] + 0.6 * TotalWinddownForceMatrix[x][y];
            ASDCombo5[x][y] = TotalDeadLoadMatrix[x][y] + 0.75 * TotalLiveLoadMatrix[x][y] + 0.45 * TotalWinddownForceMatrix[x][y] + 0.75 * std::max(TotalSnowLoadMatrix[x][y], TotalRoofLiveLoadMatrix[x][y]);     
            ASDCombo6[x][y] = TotalDeadLoadMatrix[x][y] + 0.75 * TotalLiveLoadMatrix[x][y] + 0.75 * TotalSnowLoadMatrix[x][y];
            ASDCombo7[x][y] = (0.6 * BaseDeadLoadMatrix[x][y]) - (0.6 * TotalWindLoadMatrix[x][y]);
            //LRFD Combo Loads
            LRFDCombo1[x][y] = 1.4 * TotalDeadLoadMatrix[x][y];
            LRFDCombo2[x][y] = 1.2 * TotalDeadLoadMatrix[x][y] + 1.6 * TotalLiveLoadMatrix[x][y]; + 0.5 * std::max(TotalSnowLoadMatrix[x][y], TotalRoofLiveLoadMatrix[x][y]);
            LRFDCombo3[x][y] = 1.2 * TotalDeadLoadMatrix[x][y] + 1.6 * std::max(TotalSnowLoadMatrix[x][y], TotalRoofLiveLoadMatrix[x][y]) + 0.5 * std::max(TotalLiveLoadMatrix[x][y], TotalWinddownForceMatrix[x][y]);
            LRFDCombo4[x][y] = 1.2 * TotalDeadLoadMatrix[x][y] + 1.0 * TotalWinddownForceMatrix[x][y] + 0.5 * TotalLiveLoadMatrix[x][y] + std::max(TotalSnowLoadMatrix[x][y], TotalRoofLiveLoadMatrix[x][y]);
            LRFDCombo5[x][y] = 1.2 * TotalDeadLoadMatrix[x][y] + 0.5 * TotalLiveLoadMatrix[x][y] + 0.2 * TotalSnowLoadMatrix[x][y];
            LRFDCombo6[x][y] = DBdeadloadfudgefactor * BaseDeadLoadMatrix[x][y] + TotalWindLoadMatrix[x][y];
            //Service Load Combo Loads
            ServiceLoadCombo1[x][y] = TotalDeadLoadMatrix[x][y] + TotalLiveLoadMatrix[x][y];
            ServiceLoadCombo2[x][y] = TotalDeadLoadMatrix[x][y] + std::max(TotalSnowLoadMatrix[x][y], TotalRoofLiveLoadMatrix[x][y]);
            ServiceLoadCombo3[x][y] = TotalDeadLoadMatrix[x][y] + (0.75 * TotalLiveLoadMatrix[x][y]) + (0.75 * std::max(TotalSnowLoadMatrix[x][y], TotalRoofLiveLoadMatrix[x][y]));
            ServiceLoadCombo4[x][y] = TotalDeadLoadMatrix[x][y] + (0.6 * TotalWinddownForceMatrix[x][y]);
            ServiceLoadCombo5[x][y] = TotalDeadLoadMatrix[x][y] + (0.75 * TotalLiveLoadMatrix[x][y]) + (0.45 * TotalWinddownForceMatrix[x][y]) + (0.75 * std::max(TotalSnowLoadMatrix[x][y], TotalRoofLiveLoadMatrix[x][y]));     
            ServiceLoadCombo6[x][y] = TotalDeadLoadMatrix[x][y] + (0.75 * TotalLiveLoadMatrix[x][y]) + (0.75 * TotalSnowLoadMatrix[x][y]);
            ServiceLoadCombo7[x][y] = (DBdeadloadfudgefactor * BaseDeadLoadMatrix[x][y]) - (0.6 * TotalWindLoadMatrix[x][y]);
        
        }
    }
    
    // Calculate controlling Bearing Pressure
    for (int x = 0; x <= v; ++x) {
        for (int y = 0; y <= h; ++y) {
            ControllingBearingLoads[x][y] = std::max({
                ServiceLoadCombo1[x][y],
                ServiceLoadCombo2[x][y],
                ServiceLoadCombo3[x][y],
                ServiceLoadCombo4[x][y],
                ServiceLoadCombo5[x][y],
                ServiceLoadCombo6[x][y],
                ServiceLoadCombo7[x][y]
            });
        }
    }
    // Calculate controlling Uplift Loads
    for (int x = 0; x <= v; ++x) {
        for (int y = 0; y <= h; ++y) {
            double minValue = std::min({ASDCombo5[x][y], ASDCombo6[x][y], ASDCombo7[x][y]});
            ControllingUpliftLoads[x][y] = (minValue < 0) ? minValue : 0;
        }
    }

    // Calculate total horizontal length (sum of the first h widths)
    totalhorizontallength = 0;
    for (int i = 0; i < h; i++) {
        totalhorizontallength += horizontalbaywidthlist[i];
    }

    // Calculate total vertical length (sum of the first v widths)
    totalverticallength = 0;
    for (int i = 0; i < v; i++) {
        totalverticallength += verticalbaywidthlist[i];
    }

}

void generatefoundations() {
    
    std::string foundationcontrol = "Bearing"; // Default foundation control type

    // Set all cells in FoundationThicknessMatrix to 15
    for (int x = 0; x <= v; ++x) {
        for (int y = 0; y <= h; ++y) {
            FoundationThicknessMatrix[x][y] = 15;
        }
    }
    
    // Calculate minimum foundation size for controlling bearing loads
    for (int x = 0; x <= v; ++x) {
        for (int y = 0; y <= h; ++y) {
            if (bearingpressure > 0) { // Ensure bearing pressure is positive to avoid division by zero
                double rawValue = std::sqrt(ControllingBearingLoads[x][y] / bearingpressure);
                FoundationSizeMatrix[x][y] = std::ceil(rawValue); // Store the rounded-up value
                FoundationSizeMatrixBearing[x][y] = std::ceil(rawValue); // Store the foundation size for bearing loads
            } else {
                FoundationSizeMatrix[x][y] = 3; // Set to 0 if bearing pressure is invalid
            }
            FoundationControlMatrix[x][y] = foundationcontrol.c_str(); // Set the foundation control matrix to "Bearing"
        }
    }

    // Calculate minimum foundation size for controlling uplift loads
    for (int x = 0; x <= v; ++x) {
        for (int y = 0; y <= h; ++y) {
            if (ControllingUpliftLoads[x][y] < 0) { // Check if the controlling uplift load is negative
                double rawValue = sqrt(abs(ControllingUpliftLoads[x][y] / (150 * (FoundationThicknessMatrix[x][y]/12))));
                FoundationSizeMatrix[x][y] = std::max(FoundationSizeMatrix[x][y], std::ceil(rawValue)); // Store the maximum value
                FoundationSizeMatrixUplift[x][y] = std::ceil(rawValue); // Store the foundation size for uplift loads
                if (std::ceil(rawValue) > FoundationSizeMatrix[x][y]) {
                    FoundationControlMatrix[x][y] = "Uplift"; // Set the foundation control matrix to "Uplift"
                }
            } else {
                //FoundationSizeMatrix[x][y] = std::max(FoundationSizeMatrix[x][y], 0.0); // Ensure the foundation size is non-negative
            }
        }
    }
}

//Function that generates an output text file for testing purposes.
void generateoutputfile() {
    char filePathBuffer[260]; // Buffer to hold the file path (260 is the max path length in Windows)
    GetWindowTextA(boxoutputlocation, filePathBuffer, sizeof(filePathBuffer)); // Get the file path from the text box

    // Replace invalid characters in the formattedDateTime for file names
    std::string sanitizedDateTime = formattedDateTime;
    std::replace(sanitizedDateTime.begin(), sanitizedDateTime.end(), ':', '-'); // Replace ':' with '-'
    std::replace(sanitizedDateTime.begin(), sanitizedDateTime.end(), '/', '-'); // Replace '/' with '-'

    // Create the full file path with the current date and time in the file name
    std::string filePath = std::string(filePathBuffer) + "\\output - " + sanitizedDateTime + ".txt";

    // Create and write to the output file
    std::ofstream outputFile(filePath);
    if (outputFile.is_open()) {
        // Add header to the file
        outputFile << "MezzMaster Output File\n";
        outputFile << "=======================\n";
        outputFile << "Software Version: " << softwareversion << "\n";
        outputFile << "Generated on: " << formattedDateTime << "\n";
        outputFile << "Output Path: " << filePath << "\n\n";

        outputFile << "ASCE 7-16\n";
        outputFile << "ASD\n\n";
        
        //Indicate if debug mode is on
        if (debugtest == true){
            outputFile << "Debug Mode On\n\n";
        }

        // Output the foundation size matrix
        outputFile << "\nFoundation Size Matrix (" << v + 1 << " x " << h + 1 << ") (ft):\n";
        for (int x = 0; x <= v; ++x) {
            for (int y = 0; y <= h; ++y) {
                outputFile << FoundationSizeMatrix[x][y] << "x" << FoundationSizeMatrix[x][y] << "x1" << "\t"; // Write the pre-calculated foundation size to the file
            }
            outputFile << "\n\n"; // Newline after each row
        }        

        // Output the tributary area matrix
        outputFile << "Tributary Area (" << v + 1 << " x " << h + 1 << "):\n";
        for (const auto& row : tributaryareamatrix) {
            for (const auto& cell : row) {
                outputFile << cell << "\t";
            }
            outputFile << "\n";
        }

        // Output the base dead load matrix
        outputFile << "\nBase Dead Load Matrix (" << v + 1 << " x " << h + 1 << ") (kips):\n";
        for (const auto& row : BaseDeadLoadMatrix) {
            for (const auto& cell : row) {
                outputFile << cell / 1000.0 << "\t";
            }
            outputFile << "\n";
        }

        // Output the collateral load matrix
        outputFile << "\nCollateral Load Matrix (" << v + 1 << " x " << h + 1 << ") (kips):\n";
        for (const auto& row : CollateralLoadMatrix) {
            for (const auto& cell : row) {
                outputFile << cell / 1000.0 << "\t";
            }
            outputFile << "\n";
        }

        // Output the total dead load matrix
        outputFile << "\nTotal Dead Load Matrix (" << v + 1 << " x " << h + 1 << ") (kips):\n";
        for (const auto& row : TotalDeadLoadMatrix) {
            for (const auto& cell : row) {
                outputFile << cell / 1000.0 << "\t";
            }
            outputFile << "\n";
        }

        // Output the live load matrix
        outputFile << "\nLive Load Matrix (" << v + 1 << " x " << h + 1 << ") (kips):\n";
        for (const auto& row : TotalLiveLoadMatrix) {
            for (const auto& cell : row) {
                outputFile << cell / 1000.0 << "\t";
            }
            outputFile << "\n";
        }

        // Output the roof live load matrix
        outputFile << "\nRoof Live Load Matrix (" << v + 1 << " x " << h + 1 << ") (kips):\n";
        for (const auto& row : TotalRoofLiveLoadMatrix) {
            for (const auto& cell : row) {
                outputFile << cell / 1000.0 << "\t";
            }
            outputFile << "\n";
        }

        // Output the flat roof snow load matrix
        outputFile << "\nFlat Roof Snow Load Matrix (" << v + 1 << " x " << h + 1 << ") (kips):\n";
        for (const auto& row : TotalSnowLoadMatrix) {
            for (const auto& cell : row) {
                outputFile << cell / 1000.0 << "\t";
            }
            outputFile << "\n";
        }

        // Output the wind uplift matrix
        outputFile << "\nWind Uplift Matrix (" << v + 1 << " x " << h + 1 << ") (kips):\n";
        for (const auto& row : TotalWindLoadMatrix) {
            for (const auto& cell : row) {
                outputFile << cell / 1000.0 << "\t";
            }
            outputFile << "\n";
        }

        // Output the wind down force matrix
        outputFile << "\nWind Down Force Matrix (" << v + 1 << " x " << h + 1 << ") (kips):\n";
        for (const auto& row : TotalWinddownForceMatrix) {
            for (const auto& cell : row) {
                outputFile << cell / 1000.0 << "\t";
            }
            outputFile << "\n";
        }

        // Output the ASD combination matrices
        for (int combo = 1; combo <= 7; ++combo) {
            outputFile << "\nASDCombo" << combo << " Matrix (" << v + 1 << " x " << h + 1 << ") (kips):\n";
            const auto& matrix = (combo == 1) ? ASDCombo1 :
                                 (combo == 2) ? ASDCombo2 :
                                 (combo == 3) ? ASDCombo3 :
                                 (combo == 4) ? ASDCombo4 :
                                 (combo == 5) ? ASDCombo5 :
                                 (combo == 6) ? ASDCombo6 : ASDCombo7 ;
            for (const auto& row : matrix) {
                for (const auto& cell : row) {
                    outputFile << cell / 1000.0 << "\t";
                }
                outputFile << "\n";
            };
        }

        // Output the LRFD combination matrices
        for (int combo = 1; combo <= 7; ++combo) {
            outputFile << "\nLRFDCombo" << combo << " Matrix (" << v + 1 << " x " << h + 1 << ") (kips):\n";
            const auto& matrix = (combo == 1) ? LRFDCombo1 :
                                 (combo == 2) ? LRFDCombo2 :
                                 (combo == 3) ? LRFDCombo3 :
                                 (combo == 4) ? LRFDCombo4 :
                                 (combo == 5) ? LRFDCombo5 :
                                 (combo == 6) ? LRFDCombo6 : LRFDCombo7 ;
            for (const auto& row : matrix) {
                for (const auto& cell : row) {
                    outputFile << cell / 1000.0 << "\t";
                }
                outputFile << "\n";
            };
        }

        // Output the service load combination matrices
        for (int combo = 1; combo <= 8; ++combo) {
            outputFile << "\nServiceLoadCombo" << combo << " Matrix (" << v + 1 << " x " << h + 1 << ") (kips):\n";
            const auto& matrix = (combo == 1) ? ServiceLoadCombo1 :
                                 (combo == 2) ? ServiceLoadCombo2 :
                                 (combo == 3) ? ServiceLoadCombo3 :
                                 (combo == 4) ? ServiceLoadCombo4 :
                                 (combo == 5) ? ServiceLoadCombo5 :
                                 (combo == 6) ? ServiceLoadCombo6 :
                                 (combo == 7) ? ServiceLoadCombo7 : ServiceLoadCombo8 ;
            for (const auto& row : matrix) {
                for (const auto& cell : row) {
                    outputFile << cell / 1000.0 << "\t";
                }
                outputFile << "\n";
            };
        }

        // Output the controlling bearing loads matrix
        outputFile << "\nControlling Bearing Loads Matrix (" << v + 1 << " x " << h + 1 << ") (kips):\n";
        for (const auto& row : ControllingBearingLoads) {
            for (const auto& cell : row) {
                outputFile << cell / 1000.0 << "\t";
            }
            outputFile << "\n";
        }

        // Output the foundation size matrix for bearing loads
        outputFile << "\nFoundation Size Matrix for Bearing Loads (" << v + 1 << " x " << h + 1 << ") (ft):\n";
        for (const auto& row : FoundationSizeMatrixBearing) {
            for (const auto& cell : row) {
                outputFile << cell << "\t";
            }
            outputFile << "\n";
        }

        // Output the controlling uplift loads matrix
        outputFile << "\nControlling Uplift Loads Matrix (" << v + 1 << " x " << h + 1 << ") (kips):\n";
        for (const auto& row : ControllingUpliftLoads) {
            for (const auto& cell : row) {
                outputFile << cell / 1000.0 << "\t";
            }
            outputFile << "\n";
        }

        // Output the foundation size matrix for uplift loads
        outputFile << "\nFoundation Size Matrix for Uplift Loads (" << v + 1 << " x " << h + 1 << ") (ft):\n";
        for (const auto& row : FoundationSizeMatrixUplift) {
            for (const auto& cell : row) {
                outputFile << cell << "\t";
            }
            outputFile << "\n";
        }

        // Output of foundation control matrix
        outputFile << "\nFoundation Control Matrix (" << v + 1 << " x " << h + 1 << "):\n";
        for (int x = 0; x <= v; ++x) {
            for (int y = 0; y <= h; ++y) {
                outputFile << FoundationControlMatrix[x][y] << "\t"; // Write the foundation control type to the file
            }
            outputFile << "\n";
        }

        outputFile.close();

        // Notify the user that the file was created successfully
        MessageBoxA(hwnd, "Output file created successfully!", "Success", MB_OK);
    } else {
        // Notify the user if the file could not be created
        MessageBoxA(hwnd, "Failed to create the output file. Please check the file path.", "Error", MB_ICONHAND);
    }
}

//Error handler function for Haru PDF library
void error_handler(HPDF_STATUS error_no, HPDF_STATUS detail_no, void* user_data) {
    std::ostringstream errorMessage;
    errorMessage << "Haru PDF Error: " << error_no << ", Detail: " << detail_no;
    MessageBoxA(NULL, errorMessage.str().c_str(), "PDF Error", MB_ICONHAND);
}


//Function that generates a PDF output file for testing purposes.
void pdfoutputfile(){
       
	//Generate PDF dimensions automatically based off input DPI
	int DPI = 300 ;                                                                             //DPI is set to 300 by default.  This can be changed to any value.
	int PageWidthInch = 42 ;                                                                    //Page width is set to 42 inches by default.  This can be changed to any value. 
	int PageHeightInch = 30 ;                                                                   //Page height is set to 30 inches by default.  This can be changed to any value. 
	int PageWidthpoints = 72 * PageWidthInch ;                                                  //Page width in pixels is calculated by multiplying the DPI by the page width in inches.
	int PageHeightpoints = 72 * PageHeightInch ;                                                //Page height in pixels is calculated by multiplying the DPI by the page height in inches.

    // Create a new PDF document using the Haru PDF library
    HPDF_Doc pdf = HPDF_New(error_handler, NULL);                                               //Creates a new object "pdf" which is our pdf file.
    
    // Check if the PDF document was created successfully
    if (!pdf) {
        MessageBoxA(NULL, "Failed to initialize Haru PDF library.", "Error", MB_ICONHAND);
        return; // Exit the function if initialization fails
    }

    HPDF_Page page = HPDF_AddPage(pdf);                                                         //Create a new object "page" which is a new page in the pdf file.  "pdf" is the parent.
	HPDF_Page_SetWidth(page, PageWidthpoints);                                                      //Set the width of the page to the calculated width in pixels.
	HPDF_Page_SetHeight(page, PageHeightpoints);                                                    //Set the height of the page to the calculated height in pixels.

	//Pen and various graphics settings
        //Set pen color to black
	    HPDF_Page_SetRGBStroke(page, 0.0, 0.0, 0.0);
        //Load Arial font from windows fonts and check for errors.
        const char* fontname = HPDF_LoadTTFontFromFile(pdf, ".\\Misc\\arial.ttf", HPDF_TRUE);    // Load the font and set it to a const. character variable.
            if (!fontname) {                                                                                //Check if the font was loaded successfully.       
                MessageBoxA(NULL, "Failed to load TrueType font.", "Error", MB_ICONHAND);
                HPDF_Free(pdf);
                return;
            }            
        HPDF_Font font = HPDF_GetFont(pdf, "Helvetica", NULL);                                          //Get the font object from the font name.  This is used to set the font for the text.
        if (!font) {
            MessageBoxA(NULL, "Failed to get font object.", "Error", MB_ICONHAND);
            HPDF_Free(pdf);
            return;
        }
        const char* boldfontname = HPDF_LoadTTFontFromFile(pdf, ".\\Misc\\arialbd.ttf", HPDF_TRUE);             // Load Arial Bold
        if (!boldfontname) {                                                                                    //Check if the font was loaded successfully.       
            MessageBoxA(NULL, "Failed to load bold TrueType font.", "Error", MB_ICONHAND);
            HPDF_Free(pdf);
            return;
        } 
        HPDF_Font boldfont = HPDF_GetFont(pdf, boldfontname, NULL);
        if (!boldfont) {
            MessageBoxA(NULL, "Failed to get bold font object.", "Error", MB_ICONHAND);
            HPDF_Free(pdf);
            return;
        }

    //DRAW TITLE BLOCK AND PAGE BORDER-----------------------------------------------------------------------------------
	// Draw Page border
	HPDF_Page_SetLineWidth(page, 2);				                //Sets line width
	HPDF_Page_Rectangle(page, 72,36, 2701.2, 2088);		        //Generate page border box
	HPDF_Page_Stroke(page);						                    //End path and render
	//Draw Title Block
	HPDF_Page_SetLineWidth(page, 5);				                //Sets line width
		//Block outlines
		HPDF_Page_Rectangle(page, 2794.56, 36, 167.52, 412.8);	    //Draw Info Block	
		HPDF_Page_Stroke(page);					                    //End path and Render
		HPDF_Page_Rectangle(page, 2794.56, 466.8, 167.52, 470.4);	//Draw Stamp Block	
		HPDF_Page_Stroke(page);					                    //End path and Render
		HPDF_Page_Rectangle(page, 2794.56, 955.2, 167.52, 756);	    //Draw Client Info Block	
		HPDF_Page_Stroke(page);					                    //End path and Render
		HPDF_Page_Rectangle(page, 2794.56, 1729.2, 167.52, 394.8);	//Draw Extra Block
		HPDF_Page_Stroke(page);					                    //End path and Render
		//Separating Solid Boxes
		HPDF_Page_SetRGBFill(page, 0.0, 0.0, 0.0);		            //Set fill color to black
		HPDF_Page_Rectangle(page, 2812.6, 448.8, 131.5, 18);		//Create first rectangle
		HPDF_Page_Fill(page);					                    //End path and Render
		HPDF_Page_Rectangle(page, 2812.6, 937.2, 131.5, 18);		//Create second rectangle
		HPDF_Page_Fill(page);					                    //End path and Render
		HPDF_Page_Rectangle(page, 2812.6, 1711.2, 131.5, 18);		//Create third rectangle
		HPDF_Page_Fill(page);					                    //End path and Render

	//Draw Preliminary Info
		//Draw boxes
		HPDF_Page_SetLineWidth(page, 1);			                //Sets line width
		HPDF_Page_Rectangle(page, 2341.2, 139.4, 414, 31.68);	    //Draw sheet size box
		HPDF_Page_Stroke(page);					                    //End path and Render
		HPDF_Page_Rectangle(page, 2341.2, 97.92, 208.1, 31.68);		//Draw VIF box
		HPDF_Page_Stroke(page);					                    //End path and Render
		HPDF_Page_Rectangle(page, 2565.1, 97.92, 190.1, 31.68);		//Draw do not scale box
		HPDF_Page_Stroke(page);					                    //End path and Render
		//Draw under shadow
		HPDF_Page_SetLineWidth(page, 3);			                //Sets line width
			//Draw sheet size box undershadow
			HPDF_Page_MoveTo(page, 2353.2, 137.0);		            //Go to start
			HPDF_Page_LineTo(page, 2758.56, 137.0);		            //Draw line left
			HPDF_Page_LineTo(page, 2758.56, 164.2);		            //Draw line up
			HPDF_Page_Stroke(page);				                    //End path and Render
			//Draw VIF box undershadow
			HPDF_Page_MoveTo(page, 2353.2, 95.52);		            //Go to start
			HPDF_Page_LineTo(page, 2552.6, 95.52);		            //Draw line left
			HPDF_Page_LineTo(page, 2552.6, 122.6);		            //Draw line up
			HPDF_Page_Stroke(page);				                    //End path and Render	
			//Draw do not scale box undershadow
			HPDF_Page_MoveTo(page, 2576.16, 95.52);		            //Go to start
			HPDF_Page_LineTo(page, 2758.56, 95.52);		            //Draw line left
			HPDF_Page_LineTo(page, 2758.56, 122.64);		        //Draw line up
			HPDF_Page_Stroke(page);				                    //End path and Render
		//Draw Text
        HPDF_Page_SetHorizontalScalling(page, 140.0);                                                      //Set horizontal scaling to 110% for all text.
			//Draw 1/8" text (9 points)
			HPDF_Page_SetFontAndSize(page, font, 9);						                               //This sets font to variable "font" and text height to 37.5px.
			HPDF_Page_BeginText(page);
			HPDF_Page_TextOut(page, 2387.28, 150.72, "FULL SCALE DRAWING SHEET SIZE: 30X42 ARCH E1");
			HPDF_Page_TextOut(page, 2361.36, 115.92, "FIELD VERIFY ALL EXISTING");
			HPDF_Page_TextOut(page, 2407.44, 101.28, "CONDITIONS");
			HPDF_Page_TextOut(page, 2578.56, 109.2, "DO NOT SCALE DRAWINGS");
			HPDF_Page_EndText(page);
			//Draw 3/8" text (27 points)
			HPDF_Page_SetFontAndSize(page, font, 27);						                          //This sets font to variable "font" and text height to 112.5px.
			HPDF_Page_BeginText(page);
			HPDF_Page_TextOut(page, 2349.12, 56.16, "LOD 1 | PRELIMINARY");
			HPDF_Page_EndText(page);
        HPDF_Page_SetHorizontalScalling(page, 100.0);                                                     //Set horizontal scaling back to 100% for all text.

    HPDF_Page_Concat(page, 1.0, 0, 0, 1.0, 0, 0);                                                         //Set the scale back to 1 for the entire drawing.

    //DRAW FILE INFO---------------------------------------------------------------------------------------------------------------------------------------

        int fileinfotextsize = 10;                                                                                  //This sets the text size to 10 points.  This can be changed to any value.
        HPDF_Page_SetFontAndSize(page, font, fileinfotextsize);                                                     //This sets font to variable "font" and text height to 42px.
        HPDF_Page_BeginText(page);
        HPDF_Page_TextOut(page, 85, 2088, ("MezzMaster v: " + softwareversion).c_str());                                                //This sets the text to the software version.
        HPDF_Page_TextOut(page, 85, 2088 - (1 * fileinfotextsize), ("Generated on: " + formattedDateTime).c_str());                     //This sets the text to the date and time.
        HPDF_Page_TextOut(page, 85, 2088 - (2 * fileinfotextsize), ("Output Path: " + outputpath).c_str());                             //This sets the text to the output path.
        HPDF_Page_TextOut(page, 85, 2088 - (3 * fileinfotextsize), ("Debug Mode: " + std::string(debugtest ? "On" : "Off")).c_str());   //This sets the text to the debug mode status.   
        HPDF_Page_EndText(page);                                                                                                        //End text.

    //DRAW FOUNDATION---------------------------------------------------------------------------------------------------------------------------------------
    
    //Draw Grid Lines
        //Setup variables
        int totalVlengthpoints = 0;                                                                     //Total length in points is set to 0 by default.  This can be changed to any value.
        int totalHlengthpoints = 0;
        feetpointconversion(totalhorizontallength, drawingscaleinch, totalHlengthpoints);               //Convert total width from feet to points.  See function.
        feetpointconversion(totalverticallength, drawingscaleinch, totalVlengthpoints);                 //Convert total length from feet to points.  See function.
        int gridoverdraw = 72 ;                                                                         //Grid overdraw is set to 72 points by default.  This can be changed to any value.
        int gridzeroX = 2737.2 - (2 * gridoverdraw) - totalHlengthpoints ;                              //Grid zero X is located from right corner of the page.  This can be changed to any value.
        int gridzeroY = 2124 - (2 * gridoverdraw) - totalVlengthpoints ;                                //Grid zero Y is located at 108 points by default.  This can be changed to any value.

        //Drawing grid lines
        HPDF_Page_SetLineWidth(page, 1);				                                               //Sets line width
        
        // Set the dash pattern for the grid lines
        HPDF_REAL dashPattern[] = {40.0, 5.0, 10.0, 5.0}; // Define the dash pattern as HPDF_REAL (float)
        HPDF_Page_SetDash(page, dashPattern, 4, 0); // Apply the dash pattern (2 elements, phase = 0)

        // Draw Vertical grid lines
        for (int i = 0; i <= h; i++) { // Iterate through the number of horizontal bays (including the first line)
            int cumulativeWidth = 0; // Initialize cumulative width to 0
            for (int j = 0; j < i; j++) { // Sum up the scaled widths of all previous bays
                int scaledWidth = 0;
                feetpointconversion(horizontalbaywidthlist[j], drawingscaleinch, scaledWidth); // Scale the width
                cumulativeWidth += scaledWidth;
            }
            HPDF_Page_MoveTo(page, gridzeroX + cumulativeWidth, gridzeroY - gridoverdraw); // Start at (gridzeroX - gridoverdraw + cumulativeWidth, gridzeroY - gridoverdraw)
            HPDF_Page_LineTo(page, gridzeroX + cumulativeWidth, gridzeroY + totalVlengthpoints + gridoverdraw); // Extend to the top of the grid
            HPDF_Page_Stroke(page); // End path and render
        }
        // Draw Horizontal grid lines
        for (int i = 0; i <= v; i++) { // Iterate through the number of vertical bays (including the first line)
            int cumulativeHeight = 0; // Initialize cumulative height to 0
            for (int j = 0; j < i; j++) { // Sum up the scaled heights of all previous bays
                int scaledHeight = 0;
                feetpointconversion(verticalbaywidthlist[j], drawingscaleinch, scaledHeight); // Scale the height
                cumulativeHeight += scaledHeight;
            }
            HPDF_Page_MoveTo(page, gridzeroX - gridoverdraw, gridzeroY + cumulativeHeight); // Start at (gridzeroX - gridoverdraw, gridzeroY - gridoverdraw + cumulativeHeight)
            HPDF_Page_LineTo(page, gridzeroX + totalHlengthpoints + gridoverdraw, gridzeroY + cumulativeHeight); // Extend to the right of the grid
            HPDF_Page_Stroke(page); // End path and render
        }

        // Reset to solid line after drawing
        HPDF_Page_SetDash(page, NULL, 0, 0);

        // Draw foundations and tags
        for (int x = 0; x <= v; ++x) { // Iterate through vertical grid lines
            for (int y = 0; y <= h; ++y) { // Iterate through horizontal grid lines
                // Get the foundation size from the matrix
                double foundationSizeFeet = FoundationSizeMatrix[x][y];
                int foundationSizePoints = 0;
                feetpointconversion(foundationSizeFeet, drawingscaleinch, foundationSizePoints);

                // Calculate the center of the rectangle (grid intersection)
                int centerX = gridzeroX;
                for (int i = 0; i < y; ++i) { // Sum up horizontal bay widths to get the X position
                    int scaledWidth = 0;
                    feetpointconversion(horizontalbaywidthlist[i], drawingscaleinch, scaledWidth);
                    centerX += scaledWidth;
                }

                int centerY = gridzeroY;
                for (int i = 0; i < x; ++i) { // Sum up vertical bay widths to get the Y position
                    int scaledHeight = 0;
                    feetpointconversion(verticalbaywidthlist[i], drawingscaleinch, scaledHeight);
                    centerY += scaledHeight;
                }

                // Calculate the rectangle's corners
                int halfSize = foundationSizePoints / 2;
                int rectLeft = centerX - halfSize;
                int rectRight = centerX + halfSize;
                int rectBottom = centerY - halfSize;
                int rectTop = centerY + halfSize;

                // Draw the rectangle
                HPDF_Page_Rectangle(page, rectLeft, rectBottom, foundationSizePoints, foundationSizePoints);
                HPDF_Page_Stroke(page); // Render the rectangle
                
                // THIS CODE IS FOR 45 DEGREE FOUNDATION TAGS.  45 DEGREE TEXT CURRENTLY CRASHES LIBHARU LIBRARY ERROR CODE 4177, DETAIL: 0.  COMMENTED OUT FOR NOW.
                /*
                // Calculate the length foundation tag line
                int lineLength = 72;
                int offset = static_cast<int>(lineLength / std::sqrt(2)); // Calculate the offset for both x and y directions

                // Calculate the starting point of the line (top-right corner of the rectangle)
                int lineStartX = rectRight;
                int lineStartY = rectTop;

                // Calculate the ending point of the line
                int lineEndX = lineStartX + offset;
                int lineEndY = lineStartY + offset;

                // Draw the line
                HPDF_Page_MoveTo(page, lineStartX, lineStartY); // Move to the starting point
                HPDF_Page_LineTo(page, lineEndX, lineEndY);     // Draw the line to the calculated endpoint
                HPDF_Page_Stroke(page);                         // Render the line
                */

                // Draw the foundation size text
                // Generate the text for the foundation size
                std::ostringstream foundationTextStream;
                foundationTextStream << "F-" << foundationSizeFeet << ".0";
                std::string foundationText = foundationTextStream.str();

                // Calculate the text position (centered below the rectangle)
                HPDF_REAL textWidth = HPDF_Page_TextWidth(page, foundationText.c_str()); // Get the width of the text
                int textPosX = rectLeft + (foundationSizePoints / 2) - (textWidth / 2); // Center the text horizontally relative to the rectangle
                int textPosY = rectBottom - 10; // Position the text 10 points below the rectangle

                // Set the font and size for the text
                HPDF_Page_SetFontAndSize(page, font, 10); // Use a font size of 10 points

                //I have no idea why this is necessary, but if this check doesnt occur the bottom left foundation text is not centered.
                if (x == 0 && y == 0) {
                    textPosX = gridzeroX - 12;
                }
                // Draw the text
                HPDF_Page_BeginText(page);
                HPDF_Page_TextOut(page, textPosX, textPosY, foundationText.c_str());
                HPDF_Page_EndText(page);
        };
      };

    //Draw Dims
        // Draw lines
            HPDF_Page_MoveTo(page, gridzeroX + totalHlengthpoints + (gridoverdraw * 3 / 4), gridzeroY); // Move to the starting point of the dimension line
            HPDF_Page_LineTo(page, gridzeroX + totalHlengthpoints + (gridoverdraw * 3 / 4), gridzeroY + totalVlengthpoints); // Draw the vertical line
            HPDF_Page_Stroke(page); // Render the line
            HPDF_Page_MoveTo(page, gridzeroX, gridzeroY + totalVlengthpoints + (gridoverdraw * 3 / 4)); // Move to the starting point of the dimension line
            HPDF_Page_LineTo(page, gridzeroX + totalHlengthpoints, gridzeroY + totalVlengthpoints + (gridoverdraw * 3 / 4)); // Draw the horizontal line
            HPDF_Page_Stroke(page); // Render the line

            // Add arrows at intersections
            int arrowSize = 4; // Arrow size (half the original size)

            // Vertical dimension line arrows
            for (int i = 0; i <= v; i++) {
                int cumulativeHeight = 0;
                for (int j = 0; j < i; j++) {
                    int scaledHeight = 0;
                    feetpointconversion(verticalbaywidthlist[j], drawingscaleinch, scaledHeight);
                    cumulativeHeight += scaledHeight;
                }

                int intersectionY = gridzeroY + cumulativeHeight;

                // Top-facing arrow (only if not at the top boundary)
                if (intersectionY != gridzeroY + totalVlengthpoints) {
                    HPDF_Page_MoveTo(page, gridzeroX + totalHlengthpoints + (gridoverdraw * 3 / 4), intersectionY); // Base of the arrow
                    HPDF_Page_LineTo(page, gridzeroX + totalHlengthpoints + (gridoverdraw * 3 / 4) - arrowSize, intersectionY + arrowSize); // Left point
                    HPDF_Page_LineTo(page, gridzeroX + totalHlengthpoints + (gridoverdraw * 3 / 4) + arrowSize, intersectionY + arrowSize); // Right point
                    HPDF_Page_ClosePath(page);
                    HPDF_Page_Fill(page);
                }

                // Bottom-facing arrow (only if not at the bottom boundary)
                if (intersectionY != gridzeroY) {
                    HPDF_Page_MoveTo(page, gridzeroX + totalHlengthpoints + (gridoverdraw * 3 / 4), intersectionY); // Base of the arrow
                    HPDF_Page_LineTo(page, gridzeroX + totalHlengthpoints + (gridoverdraw * 3 / 4) - arrowSize, intersectionY - arrowSize); // Left point
                    HPDF_Page_LineTo(page, gridzeroX + totalHlengthpoints + (gridoverdraw * 3 / 4) + arrowSize, intersectionY - arrowSize); // Right point
                    HPDF_Page_ClosePath(page);
                    HPDF_Page_Fill(page);
                }
            }

        // Horizontal dimension line arrows
            for (int i = 0; i <= h; i++) {
                int cumulativeWidth = 0;
                for (int j = 0; j < i; j++) {
                    int scaledWidth = 0;
                    feetpointconversion(horizontalbaywidthlist[j], drawingscaleinch, scaledWidth);
                    cumulativeWidth += scaledWidth;
                }

                int intersectionX = gridzeroX + cumulativeWidth;

                // Right-facing arrow (only if not at the right boundary)
                if (intersectionX != gridzeroX + totalHlengthpoints) {
                    HPDF_Page_MoveTo(page, intersectionX, gridzeroY + totalVlengthpoints + (gridoverdraw * 3 / 4)); // Base of the arrow
                    HPDF_Page_LineTo(page, intersectionX + arrowSize, gridzeroY + totalVlengthpoints + (gridoverdraw * 3 / 4) - arrowSize); // Top point
                    HPDF_Page_LineTo(page, intersectionX + arrowSize, gridzeroY + totalVlengthpoints + (gridoverdraw * 3 / 4) + arrowSize); // Bottom point
                    HPDF_Page_ClosePath(page);
                    HPDF_Page_Fill(page);
                }

                // Left-facing arrow (only if not at the left boundary)
                if (intersectionX != gridzeroX) {
                    HPDF_Page_MoveTo(page, intersectionX, gridzeroY + totalVlengthpoints + (gridoverdraw * 3 / 4)); // Base of the arrow
                    HPDF_Page_LineTo(page, intersectionX - arrowSize, gridzeroY + totalVlengthpoints + (gridoverdraw * 3 / 4) - arrowSize); // Top point
                    HPDF_Page_LineTo(page, intersectionX - arrowSize, gridzeroY + totalVlengthpoints + (gridoverdraw * 3 / 4) + arrowSize); // Bottom point
                    HPDF_Page_ClosePath(page);
                    HPDF_Page_Fill(page);
                }
            }

// Draw horizontal bay widths (along the top)
for (int i = 0; i < h; i++) {
    int cumulativeWidth = 0;
    for (int j = 0; j < i; j++) {
        int scaledWidth = 0;
        feetpointconversion(horizontalbaywidthlist[j], drawingscaleinch, scaledWidth);
        cumulativeWidth += scaledWidth;
    }

    int bayCenterX = gridzeroX + cumulativeWidth + (horizontalbaywidthlist[i] * drawingscaleinch * 72) / 2; // Center of the bay
    int bayCenterY = gridzeroY + totalVlengthpoints + (gridoverdraw * 3 / 4) + 5; // Position closer to the dimension line

    // Convert the bay width to a string
    std::ostringstream bayWidthTextStream;
    bayWidthTextStream << horizontalbaywidthlist[i] << "'-0\"";
    std::string bayWidthText = bayWidthTextStream.str();

    // Draw the text
    HPDF_Page_SetFontAndSize(page, font, 10); // Set font and size
    HPDF_Page_BeginText(page);
    HPDF_Page_TextOut(page, bayCenterX - (HPDF_Page_TextWidth(page, bayWidthText.c_str()) / 2), bayCenterY, bayWidthText.c_str()); // Center the text
    HPDF_Page_EndText(page);
}

// Draw vertical bay widths (along the right side, rotated 90 degrees clockwise)
for (int i = 0; i < v; i++) {
    int cumulativeHeight = 0;
    for (int j = 0; j < i; j++) {
        int scaledHeight = 0;
        feetpointconversion(verticalbaywidthlist[j], drawingscaleinch, scaledHeight);
        cumulativeHeight += scaledHeight;
    }

    int bayCenterX = gridzeroX + totalHlengthpoints + (gridoverdraw * 3 / 4) + 5; // Position closer to the dimension line
    int bayCenterY = gridzeroY + cumulativeHeight + (verticalbaywidthlist[i] * drawingscaleinch * 72) / 2;

    // Convert the bay width to a string
    std::ostringstream bayWidthTextStream;
    bayWidthTextStream << verticalbaywidthlist[i] << "'-0\"";
    std::string bayWidthText = bayWidthTextStream.str();

    // Adjust for text height when rotated
    bayCenterY += HPDF_Page_TextWidth(page, bayWidthText.c_str()) / 2;

    // Draw the rotated text
    HPDF_Page_SetFontAndSize(page, font, 10); // Set font and size
    HPDF_Page_BeginText(page);
    HPDF_Page_SetTextMatrix(page, 0, -1, 1, 0, bayCenterX, bayCenterY); // Rotate text 90 degrees clockwise
    HPDF_Page_ShowText(page, bayWidthText.c_str());
    HPDF_Page_EndText(page);
}
    
    //Draw the title
        // Define the circle's properties
        int circleDiameter = 40;
        int circleRadius = circleDiameter / 2;

        // Calculate the center of the circle
        int circleCenterX = (gridzeroX - gridoverdraw) + circleRadius; // Offset by the radius to center the circle
        int circleCenterY = gridzeroY - gridoverdraw - 100;           // Y-coordinate remains the same

        // Draw the circle
        HPDF_Page_SetLineWidth(page, 1); // Set the line width for the circle
        HPDF_Page_Circle(page, circleCenterX, circleCenterY, circleRadius);
        HPDF_Page_Stroke(page); // Render the circle

        // Draw Title Line
        HPDF_Page_MoveTo(page, circleCenterX - circleRadius, circleCenterY); // Move to the starting point of the line
        HPDF_Page_LineTo(page, gridzeroX + totalHlengthpoints + gridoverdraw, circleCenterY); // Draw the line to the right side of the circle
        HPDF_Page_Stroke(page); // Render the line

        // Draw the title text
        std::string scaletext = R"("1/8" = 1'-0")"; // Title text
        HPDF_Page_SetFontAndSize(page, font, 15); // Set the font and size for the title text
        HPDF_Page_BeginText(page); // Begin text block
        HPDF_Page_TextOut(page, circleCenterX + circleRadius + 5, circleCenterY + 5, "FOUNDATION PLAN");    // Draw the title text
        HPDF_Page_TextOut(page, circleCenterX - 5, circleCenterY + 5, "1");                                 // Draw detail number text
        HPDF_Page_TextOut(page, circleCenterX + circleRadius + 5, circleCenterY - 16, scaletext.c_str());   // Draw the title text
        HPDF_Page_EndText(page); // End text block

        HPDF_Page_SetFontAndSize(page, font, 10);                                                           // Set the font and size for the page number text
        HPDF_Page_BeginText(page); // Begin text block
        HPDF_Page_TextOut(page, circleCenterX - 15, circleCenterY - 10, "SC100");                            // Draw page number text
        HPDF_Page_EndText(page); // End text block

    //Draw Foundation Schedule

        int tablepadding = 70; // Padding around the table
        int tableWidth = 0; // Initialize table width to 0
        int tableHeight = 0; // Initialize table height to 0
        const int numColumns = 7; // Define the number of columns in the table
        int tableTopRightX = gridzeroX + totalHlengthpoints + gridoverdraw; // Top-right corner X-coordinate
        int tableTopLeftY = gridzeroY - gridoverdraw - 200;  // Top-right corner Y-coordinate
        int rowHeight = 20; // Height of each row in points
        int titleHeight = 30; // Height of the title row in points
        int titleFontSize = 14; // Font size for the title text
        int tableFontSize = 10; // Font size for the table text
        HPDF_Page_SetLineWidth(page, 1); // Set the line width for schedule

        // Generate a sorted list of unique foundation sizes
        std::set<double> uniqueFoundationSizes; // Use a set to store unique values in sorted order
        for (const auto& row : FoundationSizeMatrix) {
            for (const auto& value : row) {
                uniqueFoundationSizes.insert(value); // Insert each value into the set
            }
        }

        // Convert the set to a vector for further processing if needed
        std::vector<double> sortedFoundationSizes(uniqueFoundationSizes.begin(), uniqueFoundationSizes.end());

        // Calculate the maximum text width for each column
        std::vector<int> columnWidths(numColumns, 0); // Initialize column widths to 0

        // Define the headings for the table
        std::vector<std::string> tableHeadings = {
            "MARK NO.", "T.O. FOOTING", "LENGTH", "WIDTH", "THICKNESS", "REINFORCEMENT", "COMMENTS"
        };
        
        //Column Widths
            // Include the header text in the column width calculation
            for (int j = 0; j < numColumns; ++j) {
                HPDF_REAL textWidth = HPDF_Page_TextWidth(page, tableHeadings[j].c_str());
                columnWidths[j] = std::max(columnWidths[j], static_cast<int>(textWidth) + tablepadding); // Add padding
            };
            // Include the data rows in the column width calculation
            for (size_t i = 0; i < sortedFoundationSizes.size(); ++i) {
                double size = sortedFoundationSizes[i];

                // Generate the text for each column
                std::ostringstream col1, col2, col3, col4, col5, col6, col7;
                col1 << "F-" << std::fixed << std::setprecision(1) << size; // Column 1: "F-<size>"
                col2 << "0'-0\""; // Column 2: "0'-0\""
                col3 << size << "'-0\""; // Column 3: "<size>'-0\""
                col4 << size << "'-0\""; // Column 4: "<size>'-0\""
                col5 << "1'-0\""; // Column 5: "1'-0\""
                col6 << "(2) MATS #5s @ 12\" OCEW"; // Column 6: "(2) MATS #5s @ 12\" OCEW"
                col7 << ""; // Column 7: Blank

                // Store the column texts in a vector for easier iteration
                std::vector<std::string> rowText = {
                    col1.str(), col2.str(), col3.str(), col4.str(), col5.str(), col6.str(), col7.str()
                };

                // Calculate the maximum text width for each column
                for (int j = 0; j < numColumns; ++j) {
                    HPDF_REAL textWidth = HPDF_Page_TextWidth(page, rowText[j].c_str());
                    columnWidths[j] = std::max(columnWidths[j], static_cast<int>(textWidth) + tablepadding); // Add padding
                }
            }
            // Calculate the total table width
            for (int width : columnWidths) {
                tableWidth += width;
            }
            tableHeight = rowHeight * sortedFoundationSizes.size(); // Total height of the table

        //Table Positioning
            int tableTopLeftX = tableTopRightX - tableWidth;                                    // Calculate the top-left corner of the table
            tableHeight = rowHeight * (sortedFoundationSizes.size() + 1) + titleHeight;         // Adjust the table height to include the heading row
        //Draw Title Text
        // Draw the title cell
            HPDF_Page_Rectangle(page, tableTopLeftX, tableTopLeftY, tableWidth, -titleHeight);
            HPDF_Page_Stroke(page); // Render the rectangle                   
        // Set the font and size for the title text
            HPDF_Page_SetFontAndSize(page, boldfont, titleFontSize);
            HPDF_Page_SetRGBFill(page, 0.0, 0.0, 0.0); // Set fill color to black
            // Calculate the position for the title text (centered in the title cell)
            HPDF_REAL titleTextWidth = HPDF_Page_TextWidth(page, "FOOTING SCHEDULE");
            int titleTextPosX = tableTopLeftX + (tableWidth / 2) - (titleTextWidth / 2); // Center horizontally
            int titleTextPosY = tableTopLeftY - (titleHeight / 2) - (titleFontSize / 2); // Center vertically
            // Draw the title text
            HPDF_Page_BeginText(page);
            HPDF_Page_TextOut(page, titleTextPosX, titleTextPosY, "FOOTING SCHEDULE");
            HPDF_Page_EndText(page);
            // Adjust the top-left Y position for the rest of the table
            tableTopLeftY -= titleHeight;           
        // Draw the heading row
            // Create gray fill behind heading row  
            HPDF_Page_SetRGBFill(page, 0.9, 0.9, 0.9); // Set fill color to light gray (RGB: 90% white)
            int currentX = tableTopLeftX;
            for (int j = 0; j < numColumns; ++j) {
                HPDF_Page_Rectangle(page, currentX, tableTopLeftY - rowHeight, columnWidths[j], rowHeight);
                HPDF_Page_Fill(page); // Fill the rectangle with the gray color
                currentX += columnWidths[j]; // Move to the next column
            };
            HPDF_Page_SetRGBFill(page, 0.0, 0.0, 0.0); // Set fill color to black
            HPDF_Page_SetFontAndSize(page, boldfont, tableFontSize); // Use a set font color and size for the headings
        // Add the heading row
            currentX = tableTopLeftX;
            for (int j = 0; j < numColumns; ++j) {
                // Calculate the position for the text (centered in the cell)
                HPDF_REAL textWidth = HPDF_Page_TextWidth(page, tableHeadings[j].c_str());
                int textPosX = currentX + (columnWidths[j] / 2) - (textWidth / 2); // Center horizontally
                int textPosY = tableTopLeftY - (rowHeight / 2) - 5; // Center vertically in the row
                // Draw the text
                HPDF_Page_BeginText(page);
                HPDF_Page_TextOut(page, textPosX, textPosY, tableHeadings[j].c_str());
                HPDF_Page_EndText(page);
                currentX += columnWidths[j]; // Move to the next column
            }
        // Adjust the top-left Y position for the data rows
        tableTopLeftY -= rowHeight;

        // Correct the table height to match the actual content
        tableHeight = rowHeight * (sortedFoundationSizes.size() + 1) + titleHeight; // Include title and heading row

        // Draw the outer border of the table
        HPDF_Page_Rectangle(page, tableTopLeftX, tableTopLeftY - tableHeight + rowHeight + titleHeight, tableWidth, tableHeight - titleHeight);
        HPDF_Page_Stroke(page); // Render the rectangle

        // Draw vertical lines for the headers
        currentX = tableTopLeftX;
        for (int i = 0; i < numColumns; ++i) {
            currentX += columnWidths[i];
            HPDF_Page_MoveTo(page, currentX, tableTopLeftY + rowHeight);
            HPDF_Page_LineTo(page, currentX, tableTopLeftY - rowHeight);
            HPDF_Page_Stroke(page); // Render the line
        }

        // Draw the table grid lines
        // Draw horizontal lines to separate rows (including the heading row)
        for (size_t i = 0; i <= sortedFoundationSizes.size(); ++i) {
            int lineY = tableTopLeftY - ((i + 1) * rowHeight); // Adjust to start immediately below the headers
            HPDF_Page_MoveTo(page, tableTopLeftX, lineY + rowHeight);
            HPDF_Page_LineTo(page, tableTopLeftX + tableWidth, lineY + rowHeight);
            HPDF_Page_Stroke(page); // Render the line
        }

        // Draw vertical lines to separate columns
        currentX = tableTopLeftX;
        for (int i = 0; i < numColumns; ++i) {
            currentX += columnWidths[i];
            HPDF_Page_MoveTo(page, currentX, tableTopLeftY);
            HPDF_Page_LineTo(page, currentX, tableTopLeftY - tableHeight + titleHeight + rowHeight);
            HPDF_Page_Stroke(page); // Render the line
        }

        // Add the data rows (starting immediately below the headers)
        HPDF_Page_SetFontAndSize(page, font, tableFontSize); // Use a font size of 10 points
        for (size_t i = 0; i < sortedFoundationSizes.size(); ++i) {
            double size = sortedFoundationSizes[i];

            // Generate the text for each column
            std::ostringstream col1, col2, col3, col4, col5, col6, col7;
            col1 << "F-" << std::fixed << std::setprecision(1) << size; // Column 1: "F-<size>"
            col2 << "0'-0\""; // Column 2: "0'-0\""
            col3 << size << "'-0\""; // Column 3: "<size>'-0\""
            col4 << size << "'-0\""; // Column 4: "<size>'-0\""
            col5 << "1'-0\""; // Column 5: "1'-0\""
            col6 << "(2) MATS #5s @ 12\" OCEW"; // Column 6: "(2) MATS #5s @ 12\" OCEW"
            col7 << ""; // Column 7: Blank

            // Store the column texts in a vector for easier iteration
            std::vector<std::string> rowText = {
                col1.str(), col2.str(), col3.str(), col4.str(), col5.str(), col6.str(), col7.str()
            };

            // Add the text for each column
            currentX = tableTopLeftX;
            for (int j = 0; j < numColumns; ++j) {
                // Calculate the position for the text (centered in the cell)
                HPDF_REAL textWidth = HPDF_Page_TextWidth(page, rowText[j].c_str());
                int textPosX = currentX + (columnWidths[j] / 2) - (textWidth / 2); // Center horizontally
                int textPosY = tableTopLeftY + rowHeight - ((i + 1) * rowHeight) - (rowHeight / 2) - 5; // Center vertically in the row

                // Draw the text
                HPDF_Page_BeginText(page);
                HPDF_Page_TextOut(page, textPosX, textPosY, rowText[j].c_str());
                HPDF_Page_EndText(page);

                currentX += columnWidths[j]; // Move to the next column
            }
        }

    //Output PDF--------------------------------------------------------------------------------------------------------------------------------------------
    
    // Retrieve the user-inputted path from the text box
    char filePathBuffer[260]; // Buffer to hold the file path (260 is the max path length in Windows)
    GetWindowTextA(boxoutputlocation, filePathBuffer, sizeof(filePathBuffer)); // Get the file path from the text box
    
    // Replace invalid characters in the formattedDateTime for file names
    std::string sanitizedDateTime = formattedDateTime;
    std::replace(sanitizedDateTime.begin(), sanitizedDateTime.end(), ':', '-'); // Replace ':' with '-'
    std::replace(sanitizedDateTime.begin(), sanitizedDateTime.end(), '/', '-'); // Replace '/' with '-'

    // Create the full file path for the PDF file
    std::string pdfFilePath = std::string(filePathBuffer) + "\\MezzMasterOutput - " + sanitizedDateTime + ".pdf";

    // Save the PDF to the specified location
    HPDF_SaveToFile(pdf, pdfFilePath.c_str());
    
    HPDF_Free(pdf);                                                             //End PDF generation, free "page" object.
};

void feetpointconversion(int dimension, double scale, int& output){
    output = dimension * scale * 72;
};


//Window Action tree
LRESULT CALLBACK windows_window_callback(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
    LRESULT result = 0;
    switch(msg){
        case WM_CREATE:{        
            //Header items
            texttitle = CreateWindowExA(0,"STATIC","MezzMaster",WS_VISIBLE | WS_CHILD,10,10,200,40,hwnd,NULL,NULL,NULL);                                                                                                                      
            textversion = CreateWindowExA(0,"STATIC",softwareversion.c_str(),WS_VISIBLE | WS_CHILD,10,60,200,20,hwnd,NULL,NULL,NULL);
            textcreated = CreateWindowExA(0,"STATIC","Created by Ryan Kodura for Denham Blythe Company Inc.",WS_VISIBLE | WS_CHILD,10,90,400,20,hwnd,NULL,NULL,NULL);              
            textreference = CreateWindowExA(0,"STATIC","Reference: ASCE 7-16 ASD, AISC360-10, ACI318-10",WS_VISIBLE | WS_CHILD,10,120,350,20,hwnd,NULL,NULL,NULL);
            textcurrentdate = CreateWindowExA(0,"STATIC",formattedDateTime.c_str(),WS_VISIBLE | WS_CHILD,10,150,350,20,hwnd,NULL,NULL,NULL);
            textoutputlocation = CreateWindowExA(0,"STATIC","Output Location: ",WS_VISIBLE | WS_CHILD,10,180,150,20,hwnd,NULL,NULL,NULL);
            boxoutputlocation = CreateWindowExA(0,"EDIT","C:\\Users\\Lando\\Desktop",WS_VISIBLE | WS_CHILD | WS_BORDER,150,180,570,20,hwnd,NULL,NULL,NULL);
            //Loading Inputs
            textnumvertarraylabel = CreateWindowExA(0,"STATIC","# Vertical Bays: ",WS_VISIBLE | WS_CHILD,10,230,150,20,hwnd,NULL,NULL,NULL);
            boxnumvertarray = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,200,230,100,20,hwnd,NULL,NULL,NULL);
            textnumhorizarraylabel = CreateWindowExA(0,"STATIC","# Horizontal Bays: ",WS_VISIBLE | WS_CHILD,10,260,150,20,hwnd,NULL,NULL,NULL);
            boxnumhorizarray = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,200,260,100,20,hwnd,NULL,NULL,NULL);
            textbasedeadloadlabel = CreateWindowExA(0,"STATIC","Base Dead Load (psf): ",WS_VISIBLE | WS_CHILD,10,290,150,20,hwnd,NULL,NULL,NULL);
            boxbasedeadload = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,200,290,100,20,hwnd,NULL,NULL,NULL);
            textcollateralloadlabel = CreateWindowExA(0,"STATIC","Collateral Load (psf): ",WS_VISIBLE | WS_CHILD,10,320,150,20,hwnd,NULL,NULL,NULL);
            boxcollateralload = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,200,320,100,20,hwnd,NULL,NULL,NULL);
            textliveloadlabel = CreateWindowExA(0,"STATIC","Live Load (psf): ",WS_VISIBLE | WS_CHILD,10,350,150,20,hwnd,NULL,NULL,NULL);
            boxliveload = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,200,350,100,20,hwnd,NULL,NULL,NULL);
            textroofliveloadlabel = CreateWindowExA(0,"STATIC","Roof Live Load (psf): ",WS_VISIBLE | WS_CHILD,10,380,150,20,hwnd,NULL,NULL,NULL);
            boxroofliveload = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,200,380,100,20,hwnd,NULL,NULL,NULL);
            textflatroofsnowloadlabel = CreateWindowExA(0,"STATIC","Snow Load (psf): ",WS_VISIBLE | WS_CHILD,10,410,150,20,hwnd,NULL,NULL,NULL);
            boxflatroofsnowload = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,200,410,100,20,hwnd,NULL,NULL,NULL);
            textwindupliftlabel = CreateWindowExA(0,"STATIC","Wind Uplift (psf): ",WS_VISIBLE | WS_CHILD,10,440,150,20,hwnd,NULL,NULL,NULL);
            boxwinduplift = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,200,440,100,20,hwnd,NULL,NULL,NULL);
            textwinddownforcelabel = CreateWindowExA(0,"STATIC","Wind Downforce (psf): ",WS_VISIBLE | WS_CHILD,10,470,150,20,hwnd,NULL,NULL,NULL);
            boxwinddownforce = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,200,470,100,20,hwnd,NULL,NULL,NULL);
            //Foundation Inputs
            textbearingpressurelabel = CreateWindowExA(0,"STATIC","Bearing Pressure (ksf): ",WS_VISIBLE | WS_CHILD,10,500,150,20,hwnd,NULL,NULL,NULL);
            boxbearingpressure = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,200,500,100,20,hwnd,NULL,NULL,NULL);
            //Generate Button                     
            buttongen = CreateWindowExA(0, "BUTTON", "Design", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 10, 530, 100, 30, hwnd, (HMENU)1, NULL, NULL);
            buttondebug = CreateWindowExA(0, "BUTTON", "Debug", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 120, 530, 100, 30, hwnd, (HMENU)2, NULL, NULL);                                                              
            //Bay Inputs
            textbay1 = CreateWindowExA(0,"STATIC","Bay 1",WS_VISIBLE | WS_CHILD,400,260,100,20,hwnd,NULL,NULL,NULL);
            textbay2 = CreateWindowExA(0,"STATIC","Bay 2",WS_VISIBLE | WS_CHILD,400,290,100,20,hwnd,NULL,NULL,NULL);
            textbay3 = CreateWindowExA(0,"STATIC","Bay 3",WS_VISIBLE | WS_CHILD,400,320,100,20,hwnd,NULL,NULL,NULL);
            textbay4 = CreateWindowExA(0,"STATIC","Bay 4",WS_VISIBLE | WS_CHILD,400,350,100,20,hwnd,NULL,NULL,NULL);
            textbay5 = CreateWindowExA(0,"STATIC","Bay 5",WS_VISIBLE | WS_CHILD,400,380,100,20,hwnd,NULL,NULL,NULL);
            textbay6 = CreateWindowExA(0,"STATIC","Bay 6",WS_VISIBLE | WS_CHILD,400,410,100,20,hwnd,NULL,NULL,NULL);
            textbayHorizlabel = CreateWindowExA(0,"STATIC","Horiz. (ft): ",WS_VISIBLE | WS_CHILD,500,230,100,20,hwnd,NULL,NULL,NULL);
            textbayvertlabel = CreateWindowExA(0,"STATIC","Vert. (ft): ",WS_VISIBLE | WS_CHILD,620,230,100,20,hwnd,NULL,NULL,NULL);
            boxHorizbay1 = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,500,260,100,20,hwnd,NULL,NULL,NULL);
            boxHorizbay2 = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,500,290,100,20,hwnd,NULL,NULL,NULL);
            boxHorizbay3 = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,500,320,100,20,hwnd,NULL,NULL,NULL);
            boxHorizbay4 = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,500,350,100,20,hwnd,NULL,NULL,NULL);
            boxHorizbay5 = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,500,380,100,20,hwnd,NULL,NULL,NULL);
            boxHorizbay6 = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,500,410,100,20,hwnd,NULL,NULL,NULL);
            boxVertbay1 = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,620,260,100,20,hwnd,NULL,NULL,NULL);
            boxVertbay2 = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,620,290,100,20,hwnd,NULL,NULL,NULL);
            boxVertbay3 = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,620,320,100,20,hwnd,NULL,NULL,NULL);
            boxVertbay4 = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,620,350,100,20,hwnd,NULL,NULL,NULL);
            boxVertbay5 = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,620,380,100,20,hwnd,NULL,NULL,NULL);
            boxVertbay6 = CreateWindowExA(0,"EDIT","",WS_VISIBLE | WS_CHILD | WS_BORDER,620,410,100,20,hwnd,NULL,NULL,NULL);
            //Windows Brushes, Fonts, and Colors
            sharedbrush = CreateSolidBrush(RGB(31, 31, 31));
            hFontLarge = CreateFontA(32,0,0,0,FW_NORMAL,FALSE,FALSE,FALSE,ANSI_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH | FF_SWISS, "Arial");
            SendMessage(texttitle, WM_SETFONT, (WPARAM)hFontLarge, TRUE); // Set the font for the title
            buttonBrush = CreateSolidBrush(RGB(0, 128, 255)); // Blue background for buttons
            break;                                                           
        };
        case WM_CTLCOLORSTATIC: {                                                       
            HDC hdcStatic = (HDC)wParam;                                                       
            HWND hwndStatic = (HWND)lParam;
            SetBkMode(hdcStatic, TRANSPARENT);   
            if (hwndStatic == textversion || hwndStatic == textcreated || hwndStatic == textreference || hwndStatic == textcurrentdate){
                SetTextColor(hdcStatic, RGB(90, 90, 90));                                      
            } 
            else {
                SetTextColor(hdcStatic, RGB(14, 138, 132));                                      
            } ;                                  
            return (LRESULT)sharedbrush;
            break;                                                
        };
        case WM_DRAWITEM: {
            LPDRAWITEMSTRUCT pDIS = (LPDRAWITEMSTRUCT)lParam;
            if (pDIS->hwndItem == buttongen || pDIS->hwndItem == buttondebug) {
                bool isPressed = (pDIS->itemState & ODS_SELECTED);                                                  // Button is being clicked
                bool isFocused = (pDIS->itemState & ODS_FOCUS);                                                     // Button has focus                
                if (pDIS->hwndItem == buttongen) {                                                                  // IF Design button    
                    buttonBrush = CreateSolidBrush(isPressed ? RGB(7, 70, 67) : RGB(14, 138, 132));                     // Green background Darker Green when pressed
                };
                if(pDIS->hwndItem == buttondebug) {                                                                 // IF Debug button
                    buttonBrush = CreateSolidBrush(isPressed ? RGB(50, 2, 30) : RGB(100, 3, 58));                       // Maroon background Darker Maroon when pressed
                };
                FillRect(pDIS->hDC, &pDIS->rcItem, buttonBrush);
                DeleteObject(buttonBrush);
                SetTextColor(pDIS->hDC, RGB(255, 255, 255));                                                       // Button text color - white
                SetBkMode(pDIS->hDC, TRANSPARENT);
                const char* buttonText = (pDIS->hwndItem == buttongen) ? "Design" : "Debug";
                DrawTextA(pDIS->hDC, buttonText, -1, &pDIS->rcItem, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                return TRUE;     
                break;
            }
        };
        case WM_COMMAND:{                                                                   
            switch (LOWORD(wParam)){
                case 1:                                                                 //Case for button 1 (design button) when clicked.                                                                 
                debugtest = false;                                                      //Set debug test to false.
                generatehandler();                                                      //Calls the function to generate the design.
                break;
                case 2:                                                                 //Case for button 2 (debug button) when clicked.
                debugtest = true;                                                       //Set debug test to true.
                generatehandler();                                                      //Calls the function to generate the debug output.
                break;
            };
            break;
        };
        case WM_CLOSE: {                                                                    
            if (sharedbrush) { DeleteObject(sharedbrush); };      // Delete the shared brush  
            if (buttonBrush) { DeleteObject(buttonBrush); };      // Delete the button brush
            if (hFontLarge) { DeleteObject(hFontLarge); };        // Delete the font
            running = false;                                                                
            break;                                                                        
        };
        default:{result = DefWindowProcA(hwnd, msg, wParam, lParam);};
    };
    return result;
};


//This is the function that creates the window.
bool platform_create_window(int width, int height, const char* title){
    
    HINSTANCE instance = GetModuleHandleA(0);                   //This calls to windows to prepare the module in ANSI format.
    WNDCLASSA wc = {};                                          //This creates a new class for the window in ANSI format.
    wc.hInstance = instance;                                    //This sets the instance of the window to the current instance.
    wc.hIcon = LoadIcon(instance, IDI_APPLICATION);             //This loads the default icon for the window.
    wc.hCursor = LoadCursor(0, IDC_ARROW);                      //This loads the default cursor for the window.
    wc.lpszClassName = "ClassName";                             //This sets the class name of the window.  This is different from the title of the window.
    wc.lpfnWndProc = windows_window_callback;                   //This defines what happens when an event such as moving the cursor, clicking a key, etc. occurs.  (alternatively, use = DefWindowProcA for default)
    wc.hbrBackground = CreateSolidBrush(RGB(31, 31, 31));       //This sets the background color of the window to white.

    if(!RegisterClassA(&wc)){                                   //This registers the ANSI window class with windows.  If it fails, it returns false.
        return false;                                           //If the window class fails to register, return false.
    }

    int dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;        //We must set visual details uch as border thickness, color etc.  This is a built in default set of properties for the window.

    window = CreateWindowExA(0,"ClassName",title,dwStyle,100,100,width,height,NULL,NULL,instance,NULL);

    if(window == NULL){                                    //If the window fails to create, return false.
        return false;                                      //If the window fails to create, return false.
    }

    ShowWindow(window, SW_SHOW);                          //This tells windows to show the window we just created.
    return true;                                          //If the window was created successfully, return true.
};


//This function updates the window continously.
void platform_update_window(){                            
    MSG msg;                                                //This creates a queue of messages to the OS where a message is an event such as key press, mouse click, etc.
    while(PeekMessageA(                                     //This checks if there are messages in the queue and processes them.
        &msg,                                               //This references the default callback.
        window,                                             //This references our global variable static HWND window.
        0,                                                  //This is for setting a filter.  Set to 0 for no filter.
        0,                                                  //This is for setting filter length/  Set to 0 for no max.  
        PM_REMOVE                                           //This tells windows to remove the message from the queue after processing it.
    )){
        TranslateMessage(&msg);                             //This translates the message into a format that can be processed by windows.
        DispatchMessageA(&msg);                             //This dispatches the message to the window procedure.
    };
};



#endif                                                      //This closes out the define override we started in the library section of the header.

//Main Function------------------------------------------------------------------------------------------------------------------

int main() {

    SetDllDirectoryA(".\\library - zlib");
    SetDllDirectoryA(".\\library - lpng");
    SetDllDirectoryA(".\\library - libharu\\src");

    date_and_time();                                       //This calls the date and time function we created earlier.  This is a function that gets the current date and time.
    platform_create_window(750,700,"Mezz Master");        //This creates a window with width 1200 by 720.

    while(running){                                       //This is the main loop of the program.  It will run until the program is closed.
        platform_update_window();                         //This calls the update window function we created earlier.
    };

    return 0;
}