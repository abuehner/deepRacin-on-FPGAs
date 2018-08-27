from spidev import SpiDev

channel = 0
bus = 0

bus, device = bus, device
spi = SpiDev()
spi.open(bus, device

# xfer2(list of values[, speed_hz, delay_usec, bits_per_word])
	#s
adc = spi.xfer2([1, (8 + channel) << 4, 0])
data = ((adc[1] & 3) << 8) + adc[2]

print("Anliegende Spannung: %.2f" % (data/1023.0 * 3.3))

spi.close()
