// #include <ESP8266WiFi.h>


// const char* ssid = "Aula_AP";
// const char* password = "12345678";
// WiFiServer server(80);

// void setup() {
//   // put your setup code here, to run once:
//   Serial.begin(9600); 
  
//   IPAddress staticIP(192, 168, 4, 2); // IP set to Static
//   IPAddress gateway(192, 168, 4, 1);// gateway set to Static
//   IPAddress subnet(255, 255, 255, 0);// subnet set to Static

//   WiFi.mode(WIFI_AP);// Working mode only as Acess Point 

//   WiFi.softAP(ssid, password, 2, 0);
//   WiFi.config(staticIP, gateway, subnet);

//   server.begin();

//   Serial.println("Server started"); 
//   Serial.println(WiFi.softAPIP());
// }

// void loop() {
  
//   WiFiClient client = server.available();
//   if (!client) {
//     return;
//   }

//   // Wait until the client sends some data
//   while (!client.available()) {
//     delay(1);
//   }

//   String req = client.readStringUntil('\r');
//   req = req.substring(req.indexOf("/") + 1, req.indexOf("HTTP") - 1);
//   Serial.println(req);
//   client.flush();

//   // Match the request

//   if (req.indexOf("D") != -1)// 192.168.4.1/600
//   {
//     client.print("REcebido seu dado D   ");
//   }
//   else if (req.indexOf("R") != -1)
//   {
//     client.print("REcebido seu dado R   ");
//   }  
//   else {
//     client.print("Invalid Request");
//     client.flush();
//     client.stop();
//     return;
//   }

//   client.print("HTTP/1.1 200 OK\n\n");
//   client.flush();
  

// }

// info part 1 https://www.youtube.com/watch?v=P7zbMjrBehg&ab_channel=GRFTutoriais 
// info part 2 https://www.youtube.com/watch?v=PjgxQv9blxo&ab_channel=GRFTutoriais
// info part 3 https://www.youtube.com/watch?v=70SZfrT8x98&list=PL7x6QVHr5kzBBFKt9FodOQRAvC548_A4A&index=3&ab_channel=GRFTutoriais