using SerialPorts
include("ArduinoTools.jl")
ser=connectBoard(115200)
posCount=0
DCMotorSetup(ser,3,1,9,10)
pinAlast=digiRead(ser,3)
for i=1:1000
  aVal=digiRead(ser,3)
  if (aVal!=pinAlast)
    bVal=digiRead(ser,4)
    if (bVal!=aVal)
      posCount=posCount+1
      print("clockwise  ")
      println(posCount)
      if (posCount>0 && posCount<15)
        DCMotorRun(ser,1,40)
        sleep(2)
        DCMotorRun(ser,1,0)
        sleep(1)
      end
      if (posCount>=15 && posCount>30)
        DCMotorRun(ser,1,80)
        sleep(2)
        DCMotorRun(ser,1,0)
        sleep(1)
      end
      if (posCount<0)
        DCMotorRun(ser,1,120)
        sleep(2)
        DCMotorRun(ser,1,0)
        sleep(1)
      end
    else
      posCount=posCount-1
      print("anticloskwise")
      println(posCount)
      if (posCount>-15 && posCount<0)
        DCMotorRun(ser,1,-40)
        sleep(2)
        DCMotorRun(ser,1,0)
        sleep(1)
      end
      if (posCount>-30 && posCount<=-15)
        DCMotorRun(ser,1,-80)
        sleep(2)
        DCMotorRun(ser,1,0)
        sleep(1)
      end
      if (posCount>0)
        DCMotorRun(ser,1,-120)
        sleep(2)
        DCMotorRun(ser,1,0)
        sleep(1)
      end
    end
  end
  pinAlast=aVal
end
close(ser)
