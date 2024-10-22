#include <Arduino.h>

class Config {
private:
  int size;
  char* data;

public:
  Config(int size);
  ~Config();

  int Save();

  int Add(const char* newData, const char* name);

  const char* GetData() const { return data; }
};

Config::Config(int size) {
  this->size = size;
  data = new char[size];
  data[size - 1] = '\0';
}

Config::Save() {
  int index = 0;
  while (data[index] && index < size) {
    printf("%d\t%d\t%c\n", index, data[index], (char)data[index]);
    index++;
  }
  return size;
}

int Config::Add(const char* newData, const char* name) {
  int newDataLen = sizeof newData;

  if (strstr(data, name) == nullptr)
  {
    printf("none\n");
  }
  

  if (strlen(data) + newDataLen + strlen(name) + 3 >= size) {
    return -1;
  }
  strcat(data, "\t");
  strcat(data, name);
  strcat(data, "\t");

  strncat(data, newData, size - strlen(data) - 1);
  return 0;
}

Config::~Config() {
  delete[] data; // Free allocated memory
}

int main() {
  Config config(512);
//   int result = config.Add("dddddd", "SSid");
//   if (result == -1) {
//     std::cerr << "Error: Insufficient space for new data!" << std::endl;
//   } else {
//     config.Save();
//   }
    config.Add("dddddd", "SSid");
    config.Add("12345678", "pass");

    config.Save();


  return 0;
}