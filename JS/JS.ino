// 接收设备代码
 
#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
 
// 接收数据结构体
typedef struct struct_message
{
    //char a[32];
    int zu;
    int yo;
    //int an;
    //float c;
    //bool d;
} struct_message;
 
struct_message myData;
 
// 接收数据回调函数
int zu;
int yo;
void OnDataRecv(const esp_now_recv_info_t *recv_info, const uint8_t *incomingData, int len)
{
    memcpy(&myData, incomingData, sizeof(myData));
    Serial.print("Bytes received: ");
    Serial.println(len);
    Serial.print("zu: ");
    Serial.println(myData.zu);
    Serial.print("yo: ");
    Serial.println(myData.yo);
    zu=myData.zu;
    yo=myData.yo;

}
void setup(){
    pinMode(8,OUTPUT);
    pinMode(0,OUTPUT);
    pinMode(1,OUTPUT);
    pinMode(2,OUTPUT);
    pinMode(3,OUTPUT);
    pinMode(4,OUTPUT);
    pinMode(10,OUTPUT);
    Serial.begin(115200);
 
    WiFi.mode(WIFI_STA); // Wi-Fi Station
 
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
 
    // 注册接收数据回调函数
    esp_now_register_recv_cb(OnDataRecv);
}
 
 
void loop(){
    if(zu>0){
        analogWrite(2,zu);
        digitalWrite(0,1);
        digitalWrite(1,0);
    }
    else if(zu<0){
        analogWrite(2,zu*-1);
        digitalWrite(0,0);
        digitalWrite(1,1);
    }
    else{
        digitalWrite(0,1);
        digitalWrite(1,1);
    }
//-------------------------------------------------
    if(yo>0){
        analogWrite(10,yo);
        digitalWrite(3,1);
        digitalWrite(4,0);
    }
    else if(yo<0){
        analogWrite(10,yo*-1);
        digitalWrite(3,0);
        digitalWrite(4,1);
    }
    else{
        digitalWrite(3,1);
        digitalWrite(4,1);
    }
}