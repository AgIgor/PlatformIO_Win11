#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9
#define BTN_PIN_UP 2
#define BTN_PIN_DOWN 3
#define BTN_PIN_SELECT 4

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

void addCard();
void removeCard(byte index);
bool isCardDuplicate();
bool isCardAdmin();
void addCardAdmin();
void printCard(byte index);
byte getNumberOfCards();



enum MenuState {
  MENU_MAIN,
  MENU_ADD,
  MENU_REMOVE,
  MENU_EXIT
};

MenuState menuState = MENU_MAIN;
byte selectedMenuOption = 0;
byte adminCard[4] = {0xFA, 0x73, 0x08, 0x2E}; // UID da tag do administrador

void setup() {
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  lcd.init();
  lcd.backlight();
  pinMode(BTN_PIN_UP, INPUT_PULLUP);
  pinMode(BTN_PIN_DOWN, INPUT_PULLUP);
  pinMode(BTN_PIN_SELECT, INPUT_PULLUP);
}

void loop() {
  mfrc522.PCD_AntennaOff();
  mfrc522.PCD_AntennaOn();
  //lcd.clear();
  lcd.setCursor(0, 0);
  delay(150);

  switch (menuState) {
    case MENU_MAIN:
      lcd.print("1. Cadastrar ID");
      lcd.setCursor(0, 1);
      lcd.print("2. Gerenciar IDs");
      break;

    case MENU_ADD:
      lcd.print("Aproxime a tag");
      lcd.setCursor(0, 1);
      lcd.print("para cadastrar");
      if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
        if (isCardAdmin()) {
          lcd.clear();
          lcd.print("Tag de admin");
          lcd.setCursor(0, 1);
          lcd.print("não permitida!");
          delay(2000);
        } else if (!isCardDuplicate()) {
          addCard();
          lcd.clear();
          lcd.print("ID cadastrado!");
          delay(2000);
        } else {
          lcd.clear();
          lcd.print("ID já existe!");
          delay(2000);
        }
        mfrc522.PICC_HaltA();
      }
      break;

    case MENU_REMOVE:
      lcd.print("Selecione o ID");
      lcd.setCursor(0, 1);
      lcd.print("para remover");

      if (digitalRead(BTN_PIN_UP) == LOW) {
        selectedMenuOption--;
        if (selectedMenuOption < 0)
          selectedMenuOption = getNumberOfCards() - 1;
        delay(200);
      }

      if (digitalRead(BTN_PIN_DOWN) == LOW) {
        selectedMenuOption++;
        if (selectedMenuOption >= getNumberOfCards())
          selectedMenuOption = 0;
        delay(200);
      }

      if (digitalRead(BTN_PIN_SELECT) == LOW) {
        removeCard(selectedMenuOption);
        lcd.clear();
        lcd.print("ID removido!");
        delay(2000);
      }

      for (byte i = 0; i < getNumberOfCards(); i++) {
        lcd.setCursor(0, i);
        if (i == selectedMenuOption) {
          lcd.print(">");
        } else {
          lcd.print(" ");
        }
        printCard(i);
      }
      break;

    case MENU_EXIT:
      lcd.print("Sistema encerrado");
      break;
  }

  if (menuState != MENU_EXIT) {
    if (digitalRead(BTN_PIN_UP) == LOW) {
      selectedMenuOption--;
      if (selectedMenuOption < 0)
        selectedMenuOption = 1;
      delay(200);
    }

    if (digitalRead(BTN_PIN_DOWN) == LOW) {
      selectedMenuOption++;
      if (selectedMenuOption > 1)
        selectedMenuOption = 0;
      delay(200);
    }

    if (digitalRead(BTN_PIN_SELECT) == LOW) {
      switch (menuState) {
        case MENU_MAIN:
          if (selectedMenuOption == 0)
            menuState = MENU_ADD;
          else
            menuState = MENU_REMOVE;
          break;

        case MENU_ADD:
          if (selectedMenuOption == 0)
            addCardAdmin();
          else
            menuState = MENU_MAIN;
          break;

        case MENU_REMOVE:
          menuState = MENU_MAIN;
          break;
      }
      selectedMenuOption = 0;
      delay(200);
    }

    lcd.setCursor(0, selectedMenuOption);
    lcd.print(">");
  }
}

void addCard() {
  byte cardData[4];
  for (byte i = 0; i < 4; i++) {
    cardData[i] = mfrc522.uid.uidByte[i];
  }
  // Salvar o ID do cartão em algum lugar (por exemplo, EEPROM)
}

void removeCard(byte index) {
  // Remover o ID do cartão do local de armazenamento (por exemplo, EEPROM)
}

bool isCardDuplicate() {
  // Verificar se o ID do cartão já está cadastrado (por exemplo, verificar na EEPROM)
  return false;
}

bool isCardAdmin() {
  for (byte i = 0; i < 4; i++) {
    if (mfrc522.uid.uidByte[i] != adminCard[i])
      return false;
  }
  return true;
}

void addCardAdmin() {
  lcd.clear();
  lcd.print("Aproxime a tag");
  lcd.setCursor(0, 1);
  lcd.print("de admin");
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    for (byte i = 0; i < 4; i++) {
      adminCard[i] = mfrc522.uid.uidByte[i];
    }
    lcd.clear();
    lcd.print("Tag de admin");
    lcd.setCursor(0, 1);
    lcd.print("cadastrada!");
    delay(2000);
    mfrc522.PICC_HaltA();
  }
}

void printCard(byte index) {
  // Imprimir o ID do cartão no display (por exemplo, recuperar da EEPROM)
}

byte getNumberOfCards() {
  // Retornar o número de IDs cadastrados (por exemplo, verificar na EEPROM)
  return 0;
}
