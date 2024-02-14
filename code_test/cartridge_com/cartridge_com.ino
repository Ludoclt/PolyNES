#define SYSTEM_CLK PC8
#define M2 D2
#define CPU_RW D3
#define ROMSEL D4
#define IRQ D5
#define PPU_WR D6
#define PPU_RD D7
#define PPU_IA13 D8
#define CIRAM_CE D9
#define CIRAM_A10 PC8

#define CPU_ADDR_PORT GPIOA
#define CPU_DATA_PORT GPIOB

#define PPU_ADDR_PORT GPIOE
#define PPU_DATA_PORT GPIOF

#define OE PC10

void setup()
{
  // Level shifter control pin
  pinMode(OE, OUTPUT);
  digitalWrite(OE, HIGH);

  pinMode(SYSTEM_CLK, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(CPU_RW, OUTPUT);
  pinMode(ROMSEL, OUTPUT);
  pinMode(IRQ, INPUT);
  pinMode(PPU_WR, OUTPUT);
  pinMode(PPU_RD, OUTPUT);
  // unknown mode for PPU_IA13
  // pinMode(PPU_IA13, INPUT);
  pinMode(CIRAM_CE, INPUT);
  pinMode(CIRAM_A10, INPUT);

  pinMode(PA0, OUTPUT);
  pinMode(PA1, OUTPUT);
  pinMode(PA2, OUTPUT);
  pinMode(PA3, OUTPUT);
  pinMode(PA4, OUTPUT);
  pinMode(PA5, OUTPUT);
  pinMode(PA6, OUTPUT);
  pinMode(PA7, OUTPUT);
  pinMode(PA8, OUTPUT);
  pinMode(PA9, OUTPUT);
  pinMode(PA10, OUTPUT);
  pinMode(PA11, OUTPUT);
  pinMode(PA12, OUTPUT);
  pinMode(PA13, OUTPUT);
  pinMode(PA14, OUTPUT);

  pinMode(PE0, OUTPUT);
  pinMode(PE1, OUTPUT);
  pinMode(PE2, OUTPUT);
  pinMode(PE3, OUTPUT);
  pinMode(PE4, OUTPUT);
  pinMode(PE5, OUTPUT);
  pinMode(PE6, OUTPUT);
  pinMode(PE7, OUTPUT);
  pinMode(PE8, OUTPUT);
  pinMode(PE9, OUTPUT);
  pinMode(PE10, OUTPUT);
  pinMode(PE11, OUTPUT);
  pinMode(PE12, OUTPUT);
  pinMode(PE13, OUTPUT);

  LL_GPIO_WriteOutputPort(CPU_ADDR_PORT, 0x0000);
  LL_GPIO_WriteOutputPort(PPU_ADDR_PORT, 0x0000);

  setBusInactive();
  setCPUModeRead();
  setPPUModeRead();

  Serial.begin(9600);
}

void loop()
{
  if (Serial.available())
  {
    uint16_t addr = Serial.readString().toInt();
    if (addr >= 0x8000 && addr <= 0xFFFF)
    {
      Serial.print("Reading data at address : ");
      Serial.println(addr, HEX);
      Serial.print("Result : ");
      Serial.println(readPRGByte(addr), HEX);
    }
  }
}

void setBusActive()
{
  digitalWrite(M2, HIGH);
  digitalWrite(ROMSEL, LOW);
}

void setBusInactive()
{
  digitalWrite(M2, LOW);
  digitalWrite(ROMSEL, HIGH);
}

void setCPUModeRead()
{
  digitalWrite(CPU_RW, HIGH);
  pinMode(PB0, INPUT);
  pinMode(PB1, INPUT);
  pinMode(PB2, INPUT);
  pinMode(PB3, INPUT);
  pinMode(PB4, INPUT);
  pinMode(PB5, INPUT);
  pinMode(PB6, INPUT);
  pinMode(PB7, INPUT);
}

void setCPUModeWrite()
{
  digitalWrite(CPU_RW, LOW);
  pinMode(PB0, OUTPUT);
  pinMode(PB1, OUTPUT);
  pinMode(PB2, OUTPUT);
  pinMode(PB3, OUTPUT);
  pinMode(PB4, OUTPUT);
  pinMode(PB5, OUTPUT);
  pinMode(PB6, OUTPUT);
  pinMode(PB7, OUTPUT);
}

void setPPUModeRead()
{
  digitalWrite(PPU_WR, HIGH);
  digitalWrite(PPU_RD, LOW);
  pinMode(PF0, INPUT);
  pinMode(PF1, INPUT);
  pinMode(PF2, INPUT);
  pinMode(PF3, INPUT);
  pinMode(PF4, INPUT);
  pinMode(PF5, INPUT);
  pinMode(PF6, INPUT);
  pinMode(PF7, INPUT);
}

void setPPUModeWrite()
{
  digitalWrite(PPU_RD, HIGH);
  digitalWrite(PPU_WR, LOW);
  pinMode(PF0, OUTPUT);
  pinMode(PF1, OUTPUT);
  pinMode(PF2, OUTPUT);
  pinMode(PF3, OUTPUT);
  pinMode(PF4, OUTPUT);
  pinMode(PF5, OUTPUT);
  pinMode(PF6, OUTPUT);
  pinMode(PF7, OUTPUT);
}

uint8_t readPRGByte(uint16_t addr)
{
  LL_GPIO_WriteOutputPort(CPU_ADDR_PORT, addr);
  setCPUModeRead();
  setBusActive();
  delayMicroseconds(1);
  uint8_t data = LL_GPIO_ReadInputPort(CPU_DATA_PORT) & 0xFF;
  setBusInactive();
  return data;
}

void writePRGByte(uint16_t addr, uint8_t data)
{
  LL_GPIO_WriteOutputPort(CPU_ADDR_PORT, addr);
  setCPUModeWrite();
  LL_GPIO_WriteOutputPort(CPU_DATA_PORT, data);
  setBusActive();
  delayMicroseconds(1);
  setBusInactive();
}

uint8_t readCHRByte(uint16_t addr)
{
  LL_GPIO_WriteOutputPort(PPU_ADDR_PORT, addr);
  setPPUModeRead();
  delayMicroseconds(1);
  return LL_GPIO_ReadInputPort(PPU_DATA_PORT) & 0xFF;
}

void writeCHRByte(uint16_t addr, uint8_t data)
{
  LL_GPIO_WriteOutputPort(PPU_ADDR_PORT, addr);
  setPPUModeWrite();
  LL_GPIO_WriteOutputPort(PPU_DATA_PORT, data);
  delayMicroseconds(1);
}