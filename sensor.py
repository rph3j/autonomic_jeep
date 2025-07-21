from gpiozero import DistanceSensor
from time import sleep

# technical note:
# yellow wire is Trigger
# green wire is Echo

LeftSensor = DistanceSensor(trigger=5,echo=0)
RightSensor = DistanceSensor(trigger=15,echo=14)
BackSensor = DistanceSensor(trigger=24,echo=23)

def raportDistance():
    Left = LeftSensor.distance * 100 #distance in cm
    Right = RightSensor.distance * 100
    Back =  BackSensor.distance * 100
    return [("Left",Left),("Right",Right),("Back",Back)]

def raportFreeSpace():
    array = raportDistance()
    D_array = dict(array)
    LeftIsFree = False
    RightIsFree = False
    BackIsFree = False
    if D_array['Left'] > 26:
        LeftIsFree = True
    if D_array['Right'] > 26:
        RightIsFree = True
    if D_array['Back'] > 26:
        BackIsFree = True
    return [("Left",LeftIsFree),("Right",RightIsFree),("Back",BackIsFree)]    

array = raportFreeSpace()
D_array = dict(array)

print("Lewy ", D_array['Left'])
print("Prawy ", D_array['Right'])
print("Back ", D_array['Back'])