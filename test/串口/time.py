import time
import serial
t=serial.Serial('com8',9600)
def get_Time:
	while(1):
		a=str(time.localtime()[3])
		b=str(time.localtime()[4])
		while len(b)<2:
		b='0'+b
		while len(a)<2:
			a='0'+a
		t.write(str(a)+str(b))
		time.sleep(120)
