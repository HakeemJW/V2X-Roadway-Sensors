import Adafruit_BBIO.ADC as ADC
import time
import math
from socket import *

#Pin Setup
sensor_pin = 'P9_36'
ADC.setup()

#Thermistor Calibrations
t_c = 0 #Temp in C
t_f = 0 # Temp in F
Bvalue = 3435 #FRom Thermistor Datasheet
r_alpha = 0.09919 # Ro * e^(-B/To) in K, To 298k
c2kelvin = 273.15 #Celsisus to Kelvin Offset
r_bias = 10000 #Bias Resistor
r_therm = 0 #Calculated thermistor resistance (to Vref)

#Ethernet Socket Setup
def sendeth(src, dst, eth_type, payload, interface = "eth0"):
  """Send raw Ethernet packet on interface."""

  assert(len(src) == len(dst) == 6) # 48-bit ethernet addresses
  assert(len(eth_type) == 2) # 16-bit ethernet type

  s = socket(AF_PACKET, SOCK_RAW)

  # From the docs: "For raw packet
  # sockets the address is a tuple (ifname, proto [,pkttype [,hatype]])"
  s.bind((interface, 0))
  return s.send(src + dst + eth_type + payload)

while True:
        reading = ADC.read(sensor_pin) #Analog Input
        # millivolts =round(reading * 100)  # 1.8V reference = 1800 mV
        r_therm =round(((1/reading)-1)*r_bias)
        t_c =round(10*((Bvalue/(math.log(r_therm/r_alpha)))-c2kelvin))/10
        t_f = (t_c * 9/5) +32
        print('C=%d F=%d' % (t_c, t_f))
        time.sleep(0.05)

        print("Sent %d-byte Ethernet packet on eth0" %
    	sendeth("\xbb\x40\x20\x00\x00\x00",
            "\x00\x50\xb6\x27\x93\x73",
            "\x7A\x05",
            "\x40\x20"))
#ya boi marquis has come to save the day
