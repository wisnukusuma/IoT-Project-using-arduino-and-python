import json
import httplib
import urllib2
import serial

ser = serial.Serial('/dev/ttyACM0')
ser.baudrate = 9600
READ_API_KEY='V4MCLJ1NHGND65A5'
WRITE_API_KEY='4XVH3FDKH4TRDBN5'
CHANNEL_ID=205976

while True:
 campur=ser.readline()
 if campur.find('_')!=(-1):
	lembab, suhu = campur.rstrip().split("_")
	print ("suhu = %s kelembaban= %s"%(suhu,lembab))
	uplot = httplib.HTTPConnection('api.thingspeak.com')
	uplot.request("GET", "https://api.thingspeak.com/update?api_key=%s&field1=%s&field2=%s\n"%(WRITE_API_KEY,suhu,lembab))
	uplot.close()

	donlot = urllib2.urlopen("http://api.thingspeak.com/channels/%s/feeds/last.json?api_key=%s" \
                           % (CHANNEL_ID,READ_API_KEY))
    	response = donlot.read()
	stts=donlot.getcode()
	if donlot.getcode()==200:
    		data=json.loads(response)
		lempar,koma=data['field1'].encode().split(".")
		print lempar
    		print data['field2']
    		print data['created_at']
    		donlot.close()
		efbe=lempar+"\n"
		ser.write(efbe)
	else:
		ser.write("ggl\n")
 else:
	print campur
 campur=""
	