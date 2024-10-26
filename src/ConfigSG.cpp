#include <Arduino.h>




class Config {
private:
  int size;
  char* data;



  int IndexOf(const char* String, const char* SubString){
    int index = -1;
    int len = strlen(String) - strlen(SubString);
    if (len < 0) return -1;
    for (int i = 0; i < len; i++)
    {
      if (String[i] == SubString[0]){
        char* buffer = new char[strlen(SubString)];
        buffer[strlen(buffer)] = '\0';
        for (int i2 = 0; i2 < (int)strlen(SubString); i2++)
          buffer[i2] = String[i + i2];
        bool same = 1;
        for (int i2 = 0; i2 < (int)strlen(SubString); i2++)
        {
          if (SubString[i2] != buffer[i2]){
              same = 0;
              break;
          }
        }
        delete[] buffer;
        if (same) return i;
      }
    } 
    return index;
  }



public:



  Config(int size){
  this->size = size;
  data = new char[size];

  for (int i = 0; i < size; i++){
    data[i] = '\1';
    data[i] = '\0';
    //Serial.printf("%d\t%d\t%c\n", i, data[i], (char)data[i]);
  }
  strcat(data, "\t");
  };



  ~Config(){
  delete[] data; // Free allocated memory
  };



  int Save(){
  int index = 0;
  while (index < 50) {
    Serial.printf("%d\t%d\t%c\n", index, data[index], (char)data[index]);
    index++;
  }
  return size;
  };



  int Add(const int8_t* newData, const char* name){

  int newDataLen = sizeof(newData+1)+1;

  for (int i = 0; i < newDataLen; i++)
    Serial.printf("newData[%d] :  \t%c\n", i, (int)newData[i]);


  Serial.println(name);
  Serial.printf("newData :  \t%s\n", newData);
  Serial.printf("newDataLen :  \t%d\n", newDataLen);

   if (newDataLen > 255) return -2;
   if ((int)strlen(data) + newDataLen + (int)strlen(name) + 4 >= size) return -1;

  int indexNewData = IndexOf(data, name);
  
  if (indexNewData == -1)
  {
  strcat(data, name);
  strcat(data, "\t");
  strcat(data, "\1");

  data[strlen(data) - 1] = (char)newDataLen;
  strcat(data, "\t");

  for (int i = 0; i < newDataLen - 2; i++)
    strcat(data, "\1");
  strcat(data, "\t");

  indexNewData = IndexOf(data, name);
  }

  for (int i = 0; i < newDataLen; i++)
  {
    Serial.printf("newData[%d] :  \t%c\n", i, (int)newData[i]);
    data[strlen(name) + i + 1 + indexNewData] = newData[i];
  }

  return 0;
  };



  const char* GetData() const { return data; }
};
