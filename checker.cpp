#include <assert.h>
#include <iostream>
using namespace std;

#define parameterstocheck 3

float upperlimits[parameterstocheck] = {45,80,0.8};
float lowerLimits[parameterstocheck] ={0,20,0};
float CurrentVal[parameterstocheck];
std::string warnings[parameterstocheck] = {"Temperature out of range!", "State of Charge out of range!","Charge Rate out of range!"};

enum batteryParameter
{
    TEMP,
    SOC1,
    CHARGERATE
};

bool isInRange(float CurrentVal, float UpperLimit, float LowerLimit)
{
    return (CurrentVal>=LowerLimit && CurrentVal<= UpperLimit)? true:false;
}
 
void assignCurrValue(int a, int b, int c)
{
    CurrentVal[TEMP] = a;
    CurrentVal[SOC1] = b;
    CurrentVal[CHARGERATE] =c;
}

void printwarning(bool retVal, int i)
{
    if (retVal != false)
    cout<<"all is well\n";
    else
    cout<<warnings[i-1]<<"\n";
}

bool batteryIsOk(float temperature, float soc, float chargeRate)
{
    int retValue; 
    int i=0;
   assignCurrValue(temperature,soc,chargeRate);
   
   while(retValue != false && i < parameterstocheck)
   {
       retValue = isInRange(CurrentVal[i],upperlimits[i],lowerLimits[i]);
       i++;
   }
   printwarning(retValue,i);
	
  return retValue;
}

int main() {
  assert(batteryIsOk(25, 70, 0.7) == true);
  assert(batteryIsOk(50, 85, 0) == false);
}
