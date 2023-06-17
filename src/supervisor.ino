#include <SPI.h>
#include <SD.h>

class Supervisor{
  bool node[30]; //tells the node is occupied or not and index tells the pin number
  bool node_status[30]; //tells whether the node is active or not
  int any_active_pin = -1; //is any device is active? 
  //if read is HIGH then device is active otherwise LOW
  //if read is LOW then device is deactivate otherwise HIGH
public: 
  bool activate(int device_pin){
    if(isAvailable(device_pin)){
      node[device_pin] = true;
      return true;
    }
    else{
      return false;
    }
  }
  bool isAvailable(int device_pin){
    if(node[device_pin] == true && device_pin >= 0){
      return true; //node available
    }
    else{
      return false; //node not available
    }
  }
  bool isActive(int device_pin){
    if(node_status[device_pin]==true){
      return true; //node is active
    }
    else{
      return false; //node is not active
    }
  }
  bool begin(){
    for(int i=0; i<30; i++){
      //run server if have;
      if(any_active_pin >= 0){
        if(digitalRead(any_active_pin) == LOW){
          any_active_pin = -1; make_every_node_LOW();
        }
      }
      else if(digitalRead(i) > 0){
        any_active_pin = i; make_else_node_HIGH(i);
      }
    }
  }
  void make_else_node_HIGH(int device_pin){
    for(int j=0; j<30; j++){
      if(j != device_pin){
        node_status[j] = HIGH;
      }
    }
  }
  void make_every_node_LOW(){
    for(int j=0; j<30; j++){
      node_status[j] = LOW;
    }
  }
  void write_logs(int device_pin){
    File file;
    file = SD.open("read_write_log.txt", FILE_WRITE);
    file.print(device_pin);file.println("True");
    file.close();
  }
  bool read();
  bool write();
};
