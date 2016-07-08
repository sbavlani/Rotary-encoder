import os
import sys
cwd=os.getcwd()  # Gets the current working directory of the file
(setpath,Examples)=os.path.split(cwd)  # Creates a tuple (head,tail) where tail is everything after the final slash
print setpath
sys.path.append(setpath)   #Appends the setpath to sys.path so as to provide a search path for the module Arduino

from Arduino.Arduino import Arduino    # Imports all the functions from module Arduino
from time import sleep 

class ENCODER:
    def __init__(self,baudrate):
        self.baudrate=baudrate
        self.setup()
        self.run()
        self.exit()

    def setup(self):
        self.obj_arduino=Arduino()
        self.port=self.obj_arduino.locateport()  #Locates the port 
        self.obj_arduino.open_serial(1,self.port,self.baudrate)

    def run(self):
        count=0;
        self.pwm1=9
        self.pwm2=10
        self.pin1=3
        self.pin2=4
        pinAlast=self.obj_arduino.cmd_digital_in(1,self.pin1)
        self.obj_arduino.cmd_dcmotor_setup(1,3,1,self.pwm1,self.pwm2)  # Initialize DC motor
        for i in range(2000):
            aVal=self.obj_arduino.cmd_digital_in(1,self.pin1)  
            if aVal!=pinAlast:                                   # To check whether encoder has rotated or not
                bVal=self.obj_arduino.cmd_digital_in(1,self.pin2)
                if bVal!=aVal:               # encoder has rotated in CW direction
                    count=count+1
                    print 'clockwise  ',count  
                    if count>0 and count<15:     # Speed control of DC motor
                        self.obj_arduino.cmd_dcmotor_run(1,1,40)
                        sleep(2)
                        self.obj_arduino.cmd_dcmotor_run(1,1,0)
                        sleep(1)
                    if count>=15 and count<30:
                        self.obj_arduino.cmd_dcmotor_run(1,1,80)
                        sleep(2)
                        self.obj_arduino.cmd_dcmotor_run(1,1,0)
                        sleep(1)
                    if count<0:
                        self.obj_arduino.cmd_dcmotor_run(1,1,120)
                        sleep(2)
                        self.obj_arduino.cmd_dcmotor_run(1,1,0)
                        sleep(1)
                else:                     # encoder has rotated in CCW direction
                    count=count-1
                    print 'anticlockwise  ',count
                    if count>-15 and count<0:    # Speed control of DC motor
                        self.obj_arduino.cmd_dcmotor_run(1,1,-40)
                        sleep(2)
                        self.obj_arduino.cmd_dcmotor_run(1,1,0)
                        sleep(1)
                    if count>-30 and count<=-15:
                        self.obj_arduino.cmd_dcmotor_run(1,1,-80)
                        sleep(2)
                        self.obj_arduino.cmd_dcmotor_run(1,1,0)
                        sleep(1)
                    if count>0:
                        self.obj_arduino.cmd_dcmotor_run(1,1,-120)
                        sleep(2)
                        self.obj_arduino.cmd_dcmotor_run(1,1,0)
                        sleep(1)
            pinAlast=aVal
        self.obj_arduino.cmd_dcmotor_release(1,1)
        
    def exit(self):
        self.obj_arduino.close_serial()

def main():
    obj_encoder=ENCODER(115200)

if __name__=='__main__':        # Execute the module as script file
    main()

        

                    
                        
                    
                        
                    
            
