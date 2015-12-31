// Jessica Drury 12/07/15 My First Web Sever

#include <SPI.h>
#include <Ethernet.h>

#define successPage 1
#define errorPage 2
#define menuPage 3
#define cssStyleSheet 4


// network configuration.  gateway and subnet are optional.

  // the media access control (ethernet hardware) address for the shield:
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0x11, 0xDF };  
//the IP address for the shield:
byte ip[] = { 192, 168, 0, 111 };    
// the router's gateway address:
byte gateway[] = { 192, 168, 0, 1 };
// the subnet:
byte subnet[] = { 255, 255, 255, 0 };

// webserver defaults to port 80 
 EthernetServer server = EthernetServer(80);

void setupNet(){
    Serial.begin(9600);
   // initialize the ethernet device
   Ethernet.begin(mac, ip, gateway, subnet);

   // start listening for clients
   server.begin();
}
void loopNet() {
   // if an incoming client connects, there will be bytes available to read:
    EthernetClient client = server.available();
    if (client) {
        char buff [101];
        //read the request into the buffer
        int charsRead = 0;
        int page = menuPage;
        char * p = buff;
        
        while(client.available() && charsRead < 100) {
            * p = client.read();
            p++;
            * p = 0;
            charsRead++;
        }
        
        Serial.println();
        Serial.println();
        Serial.print(buff);

        
        //find the request type
        //expecting POST /on
        if(buff [6] == 'o' && buff [7] == 'n' && buff [8] == ' ') {
            //It's a success!!! Turn the light on
            digitalWrite(BED_PIN, HIGH);
            page = successPage; 
            //expecting POST /off
        }else if(buff [6] == 'o' && buff [7] == 'f' && buff [8] == 'f' && buff [9] == ' ') {
            //It's a success!!! Turn the light off 
            digitalWrite(BED_PIN, LOW);
            page = successPage;
            //expecting POST /
        }else if(buff [6] == 'd' && buff [7] == 'o' && buff [8] == 'n' && buff [9] == ' ') {
            //It's a success!!! Turn the den on
            digitalWrite(DEN_PIN, HIGH);
            page = successPage;
            //expecting POST 
        }else if(buff [6] == 'd' && buff [7] == 'o' && buff [8] == 'f' && buff [9] == 'f') {
            //It's a success!!! Turn the den off
            digitalWrite(DEN_PIN, LOW);
            page = successPage;
            //expecting GET  
        }else if( buff [5] == ' ' || buff [5] == '?') {
            page = menuPage;  
        }else if(buff [5] == 'c' && buff [6] == 's' && buff [7] == 's' && buff [8] == ' ') {
            page = cssStyleSheet;
        }else {
            //ERROR. Oh no! I wonder what went wrong
            page = errorPage;   
            Serial.print("error"); 
        }

        
        int lightIsOn = digitalRead(BED_PIN);
        int denIsOn =digitalRead(DEN_PIN);        // read bytes from the incoming client and write them back
        // to any clients connected to the server:
        if(page == successPage) {
            char * msg = "<html><head><link rel='stylesheet' type='text/css' href='css'></head><body><h1>YAY!<h1>"
            "<form action ='/' method ='GET'><button type='submit'>Back</button></form></body></html>";
            client.println("HTTP/1.1 200 OK");
            client.print("Content-Length: ");
            client.println(strlen(msg));
            client.println();
            client.print(msg);
            client.stop();
        }else if(page == errorPage){
            char * msg = "The page you searched for cannot be found. Please try again.(And do it right this time dumbo!)";
            client.println("HTTP/1.1 404 Not Found");
            client.print("Content-Length: ");
            client.println(strlen(msg));
            client.println();
            client.print(msg);
            client.stop();
        }else if(page == menuPage) {
            char * msg = 
            "<html>"
            "<head><link rel='stylesheet' type='text/css' href='css'></head>"
            "<body><h1>Welcome to Jessicas Light Controller</h1>"
            "<form action ='/on' method ='POST'>"
            "<button type='submit'>Turn the light on</button></form>"
            "<form action ='/off' method ='POST'>"
            "<button type='submit'>Turn the light off</button></form>"
            "<form action ='/don' method ='POST'>"
            "<button type='submit'>Turn on the den</button></form>"
            "<form action ='/doff' method 'POST'>"
            "<button type='submit'>Turn off the den</button></form>"
            "</body></html>";

            client.println("HTTP/1.1 200 OK");
            client.println();
            client.println("<html><head><link rel='stylesheet' type='text/css' href='css'></head><body><h1>Welcome to Jessicas Light Controller</h1>");
            if(lightIsOn == false) {
                client.print("<p>The light is off</p>");  
            }else if(lightIsOn == true){
                client.print("<p>The light is on</p>");
            }if(denIsOn == false) {
                client.print("<p>The den is off</p>");
            }else if(denIsOn == true) {
                client.print("<p>The den is on</p>");
            }
            client.println("<form action ='/on' method ='POST'><button type='submit'>Turn the light on</button></form>"
            "<form action ='/off' method ='POST'><button type='submit'>Turn the light off</button></form>"
            "<form action ='/don' method ='POST'><button type='submit'>Turn on the den</button></form>"
            "<form action ='/doff' method = 'POST'><button type='submit'>Turn off the den</button></form>"
            "</body></html>");
            client.stop();   
        }else if(page == cssStyleSheet) {
            char * msg =
            "body {background-color: #d0e4fe;}"
            "h1 {color: orange; text-align: left;}"
            "button {display: block; width: 200px; height: 100px; margin: 25px;}";
            
            client.println("HTTP/1.1 200 OK");
            client.print("Content-Length: ");
            client.println(strlen(msg));
            client.println();
            client.print(msg);
            client.stop();
        }
    }
}
