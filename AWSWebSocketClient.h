#ifndef WSCLIENT_H_
#define WSCLIENT_H_

#include <Arduino.h>
#include <Stream.h>
#include "Client.h"
#include "WebSocketsClient.h"
#include "ByteBuffer.h"
#include "sha256.h"
#include "Utils.h"
#include "AWSClient4.h"

  
#define DEBUG_WEBSOCKET_MQTT(...) os_printf( __VA_ARGS__ )

#ifndef DEBUG_WEBSOCKET_MQTT
#define DEBUG_WEBSOCKET_MQTT(...)
#define NODEBUG_WEBSOCKET_MQTT
#endif
  
class AWSWebSocketClient : public Client, private WebSocketsClient {
public:

	AWSWebSocketClient ();
	~AWSWebSocketClient();

	char* generateAWSPath ();
	
	int connect(IPAddress ip, uint16_t port);
	int connect(const char *host, uint16_t port);
	
	void putMessage (byte* buffer, int length);
  size_t write(uint8_t b);
  size_t write(const uint8_t *buf, size_t size);
  int available();
  int read();
  int read(uint8_t *buf, size_t size);
  
  int peek();
  void flush();
  void stop();
  uint8_t connected() ;
  operator bool();

  
  bool getUseSSL ();
  
  AWSWebSocketClient& setUseSSL (bool value);
  
  
  AWSWebSocketClient& setAWSRegion(const char * awsRegion);    
  AWSWebSocketClient& setAWSDomain(const char * awsDomain);
  AWSWebSocketClient& setAWSSecretKey(const char * awsSecKey);
  AWSWebSocketClient& setAWSKeyID(const char * awsKeyID);
  AWSWebSocketClient& setPath(const char * path);
  
  
	static AWSWebSocketClient* instance;
  private:
	
	//enable ssl... if your using mqtt over websockets at AWS IoT service, it must be enabled
	bool useSSL;
	
	//connection timeout (but it seems it is not working as I've expected... many I should control it by the receipt of the connection message)
	long connectionTimeout;	
	
	
	char* path;
	/* Name of region, eg. "us-east-1" in "kinesis.us-east-1.amazonaws.com". */
    char* awsRegion;    
    /* Domain, optional, eg. "A2MBBEONHC9LUG.iot.us-east-1.amazonaws.com". */
    char* awsDomain;   
    /* The user's AWS Secret Key for accessing the AWS Resource. */
    char* awsSecKey;
    /* The user's AWS Access Key ID for accessing the AWS Resource. */
    char* awsKeyID;
	
	
	//circular buffer to keep incoming messages from websocket
	ByteBuffer bb;
	
	



   
};



#endif
