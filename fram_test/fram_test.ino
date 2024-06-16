// пример использования FRAM FM24Cxx для любых типов данных включая массивы и структуры
// проверено на FM24CL16

#include <Wire.h>

#define disk 0x50   //адрес чипа FM24C

struct vvv {
  byte a;
  int b;
  long c;
};
struct vvv abc;
struct vvv cab;

void setup(void) {
  Wire.begin();
  Serial.begin(9600);

  // пишем данные (раскомментировать для первого запуска)
  /*int a = -5432;
  FM24C_write(10, &a, sizeof(a));       // адрес 10
  unsigned long aa = 12345678;
  FM24C_write(100, &aa, sizeof(aa));    // адрес 100
  abc.a = 10;
  abc.b = 100;
  abc.c = 1000;
  FM24C_write(300, &abc, sizeof(abc));  // адрес 300*/

  // читаем данные
  int b;
  FM24C_read(10, &b, sizeof(b));        // из тех же адресов, что записывали!
  Serial.println(b);
  unsigned long bb;
  FM24C_read(100, &bb, sizeof(bb));
  Serial.println(bb);
  FM24C_read(300, &cab, sizeof(cab));
  Serial.println(cab.a);
  Serial.println(cab.b);
  Serial.println(cab.c);


  // пишем массив (раскомментировать для первого запуска)
  /*char hello[] = "hello, 3d-diy.ru";
  FM24C_write(1500, &hello, sizeof(hello) + 1);   // записываем по адресу 1500*/
  // читаем массив
  char hhh[16];
  FM24C_read(1000, &hhh, sizeof(hhh) + 1);        // считываем из того же адреса
  Serial.println(hhh);
    
  FM24C_read(2000, &hhh, sizeof(hhh) + 1);        // считываем из того же адреса
  Serial.println(hhh);
}

void loop() {}

// -------------- функции чтение-запись ------------
/*
void FM24C_write(unsigned int startAddress, void *data, unsigned int len) { // адрес, указатель на первый байт, длина в байтах
  Wire.beginTransmission(disk);
  Wire.write((byte*)&startAddress,2);
  Wire.write((byte*)data, len);
  Wire.endTransmission(true);
  delay(1);
}*/

int FM24C_read(unsigned int startAddress, void *data, unsigned int len) { // возвращаем кол-во считанных байт
  byte rdata;
  byte *p;
  Wire.beginTransmission(disk);
  Wire.write((byte*)&startAddress,2);
  Wire.endTransmission();
  //Wire.beginTransmission(disk);
  Wire.requestFrom(disk, len);
  for (rdata = 0, p = (byte*)data; Wire.available() && rdata < len; rdata++, p++) {
    *p = Wire.read();
  }
  return (rdata);
}