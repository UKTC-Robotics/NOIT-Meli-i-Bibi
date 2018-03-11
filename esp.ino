#include<SPI.h>
#include <ESP8266WiFi.h>

char ssid[] = "esp_ap";       //   SSID 
char pass[] = "12345678";    // паролааа

WiFiServer server(80);

char buff[]="F\n";
char buff1[]="S\n";

String header = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
String html_1 = "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'/><meta charset='utf-8'><style>body {font-size:140%;} #main {display: table; margin: auto;  padding: 0 10px 0 10px; } h2,{text-align:center; } .button { padding:10px 10px 10px 10px; width:100%;  background-color: #4CAF50; font-size: 120%;} .button1 { padding:100px 100px 100px 100px; width:100%;  background-color: #4CAF50; font-size: 120%;}</style><title>LED Control</title></head><body><div id='main'><h2>LED Control</h2>";
String html_2 = "<form id='F1' action='FORWARD'><input class='button' type='submit' value='move forward' ></form><br>";
String html_3 = "<form id='F1' action='STOP'><input class='button1' type='submit' value='stop' ></form><br>";
String html_4 = "</div></body></html>";

String request = "";

void setup() {
 Serial.begin(9600); /* begin serial with 9600 baud */
 SPI.begin();  /* begin SPI */

 WiFi.mode(WIFI_AP);         
 WiFi.softAP(ssid, pass);  
 IPAddress myIP = WiFi.softAPIP(); 
 Serial.print("HotSpt IP:");
 Serial.println(myIP);
 
  
 server.begin();              
 Serial.println("HTTP server started");
}

void loop() {
  WiFiClient client = server.available();
    if (!client)  {  return;  }
 
    request = client.readStringUntil('\r');
 
    if( request.indexOf("FORWARD") > 0 )  
    { 
      for(int i=0; i<sizeof buff; i++)  /* transfer buff data per second */
        SPI.transfer(buff[i]);
      delay(1000);  
      //html_2 = "<form id='F1' action='LEDOFF'><input class='button' type='submit' value='Turn off the LED' ></form><br>";
    }
    else if( request.indexOf("STOP") > 0 ) 
    { 
      for(int i=0; i<sizeof buff1; i++)  /* transfer buff data per second */
        SPI.transfer(buff1[i]);
      delay(1000);   
      //html_2 = "<form id='F1' action='LEDON'><input class='button' type='submit' value='Turn on the LED' ></form><br>";
    }

  client.flush();
 
    client.print( header );
    client.print( html_1 );    
    client.print( html_2 );
    client.print( html_3 );
    client.print( html_4);
 
    delay(5);
 //for(int i=0; i<sizeof buff; i++)  /* transfer buff data per second */
  //SPI.transfer(buff[i]);
 //delay(1000);  
}
