#include<ESP8266WebServer.h>  
ESP8266WebServer server;
const char username[]="rishi";
const char password[]="rishi2001";
#define LEDPin1 12
#define LEDPin2 13
void setup()
{pinMode(LEDPin1,OUTPUT);
pinMode(LEDPin2,OUTPUT);
Serial.begin(115200);

WiFi.softAP(username,password);//create access point
Serial.println("connected");
IPAddress myIP=WiFi.softAPIP();
Serial.print("AP IP address: ");
Serial.println(myIP);
server.begin();
server.on("/led",led);
//server.on("/check",check);
}
void loop()
{server.handleClient();
}
void led()
{String myhtml="<!DOCTYPE html><html lang=\"en\" dir=\"ltr\"><head><meta charset=\"utf-8\"><title>Nodemcu local website</title><script type=\"text/javascript\">function addParagraphText1(){var x = document.getElementById(\"para1\");var y = document.getElementById(\"para2\");if (x.innerHTML === \"LED1 Status: OFF\") {x.innerHTML = \"LED1 Status: ON\";y.innerHTML = \"LED2 Status: OFF\";} }function addParagraphText2(){var x = document.getElementById(\"para1\");var y = document.getElementById(\"para2\");if (y.innerHTML === \"LED2 Status: OFF\") {y.innerHTML = \"LED2 Status: ON\";x.innerHTML = \"LED1 Status: OFF\";}        }</script></head><body style=\"background-color: #66ccff\"><div style=\"text-align: center;\"><h1>ESP8266 Web Server</h1><h2>Using Access Point(AP) Mode</h2><form><p id=\"para1\">LED1 Status: OFF</p><button onclick=\"addParagraphText1();\" id=\"button\" type=\"submit\" name=\"status1\" value=\"0\" style=\"background-color: green; color: white;\">ON</button><p id=\"para2\">LED2 Status: ON</p><button onclick=\"addParagraphText2();\" id=\"button\" type=\"submit\" name=\"status1\" value=\"1\" style=\"background-color: green; color: white;\">ON</button></form></div></body></html>";
   server.send(200,"text/html",myhtml);
   if(server.arg("status1")=="1")
    {
      digitalWrite(LEDPin1,LOW);
      digitalWrite(LEDPin2,HIGH);
    }
    else
    {
      digitalWrite(LEDPin1,HIGH);
      digitalWrite(LEDPin2,LOW);
    }
    
}
