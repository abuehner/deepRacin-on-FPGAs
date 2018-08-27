from spidev import SpiDev
import RPi.GPIO as GPIO           # import RPi.GPIO module  
GPIO.setmode(GPIO.BOARD)            # choose BCM or BOARD  
GPIO.setup(11, GPIO.OUT) # set a port/pin as an output   

channel = 0
bus = 0

bus, device = bus, device
spi = SpiDev()
spi.open(bus, device

# xfer2(list of values[, speed_hz, delay_usec, bits_per_word])
	#s
adc = spi.xfer2([1, (8 + channel) << 4, 0])

voltages = []
powerSum = 0


GPIO.output(11, 1)       # set port/pin value to 1/GPIO.HIGH/True  


for i in range(0, 10):
   if (i == 8):
      GPIO.output(11,0)
   voltages[i] = ((adc[1] & 3) << 8) + adc[2]
   power = math.pow(voltages[i]/1023.0 * 3.3, 2)* ((voltages[i]/1023.0 * 3.3)/100
   powerSum += power
   print("power: %.2f" % power)


print("energy: %.2f" % (powerSum/10))

spi.close()
GPIO.cleanup()
