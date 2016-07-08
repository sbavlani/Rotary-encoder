using SerialPorts
using ArduinoTools
ser=connectBoard(115200)
posCount=0
pinAlast=digiRead(ser,3)
for i=1:3000
  aVal=digiRead(ser,3)
  if (aVal!=pinAlast)
    bVal=digiRead(ser,4)
    if (bVal!=aVal)
      posCount=posCount+1
      print("clockwise  ")
      println(posCount)
    else
      posCount=posCount-1
      print("anti clockwise  ")
      println(posCount)
    end
  end
  pinAlast=aVal
end
close(ser)
