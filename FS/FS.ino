

// 发送设备代码
// 发送四个类型的数据
 
#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>
 
// CC:7B:5C:25:7B:BC
// 08:D1:F9:EB:52:E8

//A7:04:B9:75:E0
 
uint8_t broadcastAddress[] = {0xAC, 0xA7, 0x04, 0xB9, 0x75, 0xE0};
 
// 发送的数据结构
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
 
esp_now_peer_info_t peerInfo;
 
 
// 发送数据回调函数
void OnDataSent(const wifi_tx_info_t *info, esp_now_send_status_t status)
{
    // 打印消息是否成功传递
    //Serial.print("Last Packet Send Status:");
    //Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 

//读取电脑数据
using namespace std;
String str = "";

int num;

String readLine (){
  String str = "";
  while(Serial.available()){
    str += char(Serial.read());
    delay(2);
  }
  return str;
}

 
void setup()
{
    Serial.begin(9600);
 
    WiFi.mode(WIFI_STA);    // Wi-Fi Station
 
    if (esp_now_init() != ESP_OK)
    {
        Serial.println("Error initializing ESP-NOW");
        return;
    }
 
    esp_now_register_send_cb(OnDataSent);   // 注册发送数据的回调函数
 
    memcpy(peerInfo.peer_addr, broadcastAddress, 6);    // 复制 MAC 地址
    peerInfo.channel = 0;       // 使用当前打开的通道
    peerInfo.encrypt = false;   // 未加密
 
    // 添加以上列表
    if (esp_now_add_peer(&peerInfo) != ESP_OK)
    {
        Serial.println("Failed to add peer");
        return;
    }


}
 

int intz(char str){
    int t=0;
    for(int i=0;i<=9;i++){
        if(str==String(i)[0]){
        t=i;
        }
    }
    return t;
}

int intzz(String str){
    str+=";";
    int n=1;
    if(str[0]=="-"[0]){
        n=-1;
    }
    int t=0;
    for(int w=0;str[w]!=";"[0];w++){
        t=t*10+intz(str[w]);
    }
    return t*n;
}



int n=0;
void loop(){
    // str = readLine();
    // if(str.length() != 0){

    // }

    String z;
    String y;
    int n=1;
    String str=readLine();
    if(str.length() != 0){
        str+=";";
        for(int i=0;str[i]!=";"[0];i++){
            if(str[i]=="y"[0]){
                n=0;
            }
            else if(n){
                z+=str[i];
            }
            else{
                y+=str[i];
            }
        }
        myData.zu = intzz(z);
        myData.yo = intzz(y);
        // 设置发送信息
        //strcpy(myData.a, "THIS IS A CHAR");
        esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *)&myData, sizeof(myData));  // 发送
    }
    



 /*
    if (result == ESP_OK)
    {
        Serial.println("YES");
    }
    else 
    {
        Serial.println("NO");
    }
 */
}