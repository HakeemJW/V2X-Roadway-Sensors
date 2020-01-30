import Adafruit_BBIO.ADC as ADC
import time
import math
import globals
sensor_pin = 'P9_36'

ADC.setup()

t_c = 0 #Temp in C
t_f = 0 # Temp in F
Bvalue = 3435 #FRom Thermistor Datasheet
r_alpha = 0.09919 # Ro * e^(-B/To) in K, To 298k
c2kelvin = 273.15 #Celsisus to Kelvin Offset
r_bias = 10000 #Bias Resistor
r_therm = 0 #Calculated thermistor resistance (to Vref)

def pulltemp():
    while True:
        reading = ADC.read(sensor_pin) #Analog Input
       # millivolts =round(reading * 100)  # 1.8V reference = 1800 mV
       # temp_c = (millivolts - 500) / 10
       # temp_f = (temp_c * 9/5) + 32

        r_therm =round(((1/reading)-1)*r_bias)
        t_c =round(10*((Bvalue/(math.log(r_therm/r_alpha)))-c2kelvin))/10
        t_f = (t_c * 9/5) +32
        globals.temperature_c = t_c
        globals.temperature_f = t_f
        print('C=%d F=%d' % (t_c, t_f))
        time.sleep(1)
