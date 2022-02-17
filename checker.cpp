
#include <assert.h>
#include <iostream>
using namespace std;

#define parameterstocheck 3
#define tolerance 0.05

float upperLimits[parameterstocheck] = {45,80,0.8};
float lowerLimits[parameterstocheck] = {0,20,0};

std::string *validnoticestring;
std::string *validLowerlimitAproachString;
std::string *validPeakAproachString;

std::string noticeInEngish[parameterstocheck] = {"Temperature out of range!", "State of Charge out of range!","Charge Rate out of range!"};
std::string noticeInGerman[parameterstocheck] = {"Temperatur außerhalb des Bereichs!", "Ladezustand außerhalb des Bereichs!","Laderate außerhalb des Bereichs!"};
std::string aproachingLowerWarnInEngish[parameterstocheck] = {"Temperature aproaching lower limit!", "SOC aproaching lower limit!","Charge Rate aproaching lower limit!"};
std::string aproachingLowerWarnInGerman[parameterstocheck] = {"Temperatur nähert sich dem unteren Grenzwert!", "SOC nähert sich der Untergrenze!","Laderate nähert sich der Untergrenze!"};
std::string aproachingPeakWarnInEngish[parameterstocheck] = {"Temperature aproaching peak!", "SOC aproaching peak!","Charge Rate aproaching peak!"};
std::string aproachingPeakWarnInGerman[parameterstocheck] = {"Temperatur nähert sich dem Höhepunkt!", "SOC nähert sich dem Höhepunkt!","Laderate nähert sich dem Höhepunkt!"};

enum batteryParameter
{
    TEMP,
    SOC,
    CHARGERATE
};

enum countryList
{
    English,
    German
};

void selectLanguage(int Language)
{
    if(Language == English)
    {
    validnoticestring = noticeInEngish;
    validLowerlimitAproachString = aproachingLowerWarnInEngish;
    validPeakAproachString = aproachingPeakWarnInEngish;
    }
    else
    {
    validnoticestring = noticeInGerman;
    validLowerlimitAproachString =aproachingLowerWarnInGerman;
    validPeakAproachString =aproachingPeakWarnInGerman;
    }
    
}

void notifyOwner(int batParameterIndex)
{
    cout<< validnoticestring[batParameterIndex]<<"\n";
}

void alertOwnerAproachingLowerlimit(int batParameterIndex)
{
    cout<< validLowerlimitAproachString[batParameterIndex]<<"\n";
}

void alertOwnerAproachingPeak(int batParameterIndex)
{
   cout<< validPeakAproachString[batParameterIndex]<<"\n"; 
}

bool notRchdLowerRange(int batParameterIndex, float *currentReading)
{
    bool retVal= true;
    if(currentReading[batParameterIndex] <= lowerLimits[batParameterIndex])
    {
        retVal =false;
        notifyOwner(batParameterIndex);
    }
    else if((currentReading[batParameterIndex] <= ((tolerance*upperLimits[batParameterIndex])+lowerLimits[batParameterIndex])))
    {
        alertOwnerAproachingLowerlimit(batParameterIndex);
    }
    return retVal;
}

bool notRchdUpperRange(int batParameterIndex, float *currentReading)
{
    bool retVal= true;
    if(currentReading[batParameterIndex] >= upperLimits[batParameterIndex])
    {
        retVal =false;
        notifyOwner(batParameterIndex);
    }
    else if(currentReading[batParameterIndex] >= ((tolerance*upperLimits[batParameterIndex])+upperLimits[batParameterIndex]))
    {
        alertOwnerAproachingPeak(batParameterIndex);
    }
    return retVal;
}


bool reportBatteryHlth(int batParameterIndex, float *currentReading)
{
    bool retVal =true;
   if((retVal = notRchdLowerRange(batParameterIndex,currentReading)))
   {
        retVal = notRchdUpperRange(batParameterIndex,currentReading);    
   }
   return retVal;
}

bool batteryIsOk(float *currentReading)
{
    int retValue; 
    int batParameterIndex=0;

   while(batParameterIndex < parameterstocheck)
   {
       retValue = retValue && reportBatteryHlth(batParameterIndex, currentReading);
       batParameterIndex++;
   }
	
  return retValue;
}

int main() 
{
    
  float currentReading[parameterstocheck];

  selectLanguage(English);
  currentReading[TEMP] = 2.25;
  currentReading[SOC] = 24;
  currentReading[CHARGERATE] = 0.04;
  assert(batteryIsOk(currentReading) == true);
  
  selectLanguage(German);
  assert(batteryIsOk(currentReading) == true);
  
}
