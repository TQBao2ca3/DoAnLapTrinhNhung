#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Khởi tạo LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Điều chỉnh địa chỉ dựa trên bộ mở rộng I2C của bạn

const int nutTraiPin = 13;
const int nutGiuaPin = 12; // Nút giữa cho menu
const int nutPhaiPin = 11;
const int den1Pin = 2;
const int den2Pin = 3;
const int den3Pin = 4;

bool trangThaiNutTraiCu = LOW;
bool trangThaiNutPhaiCu = LOW;
bool trangThaiNutGiuaCu = LOW;

const long doTreDebounce = 200; // Độ trễ loại bỏ tiếng lắc
unsigned long thoiGianBamNut = 0;
int trangThaiMenu = 0;
int trangThaiMenuCon = 0;
bool trongMenu = false;
bool trongMenuCon = false;

void setup() {
  pinMode(nutTraiPin, INPUT);
  pinMode(nutGiuaPin, INPUT);
  pinMode(nutPhaiPin, INPUT);
  pinMode(den1Pin, OUTPUT);
  pinMode(den2Pin, OUTPUT);
  pinMode(den3Pin, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("XIN CHAO");
}

void loop() {
  unsigned long thoiGianHienTai = millis();

  bool trangThaiNutGiuaHienTai = digitalRead(nutGiuaPin);
  bool trangThaiNutPhaiHienTai = digitalRead(nutPhaiPin);
  bool trangThaiNutTraiHienTai = digitalRead(nutTraiPin);

  if (trangThaiNutGiuaHienTai == LOW && trangThaiNutGiuaCu == HIGH && thoiGianHienTai - thoiGianBamNut >= doTreDebounce) {
    thoiGianBamNut = thoiGianHienTai;
    if (!trongMenu) {
      trongMenu = true;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Menu:");
      hienThiMenu();
    } else if (trangThaiMenu == 1 && !trongMenuCon) {
      trongMenuCon = true;
      lcd.setCursor(0, 0);
      lcd.print("LED Control:");
      hienThiMenuCon();
    }
  }

  if (trongMenu) {
    if (trangThaiNutPhaiHienTai == LOW && trangThaiNutPhaiCu == HIGH && thoiGianHienTai - thoiGianBamNut >= doTreDebounce) {
      thoiGianBamNut = thoiGianHienTai;
      if (trongMenuCon) {
        if (trangThaiMenuCon < 2) trangThaiMenuCon++;
        hienThiMenuCon();
      } else {
        if (trangThaiMenu < 2) trangThaiMenu++;
        hienThiMenu();
      }
    } else if (trangThaiNutTraiHienTai == LOW && trangThaiNutTraiCu == HIGH && thoiGianHienTai - thoiGianBamNut >= doTreDebounce) {
      thoiGianBamNut = thoiGianHienTai;
      if (trongMenuCon) {
        if (trangThaiMenuCon > 0) trangThaiMenuCon--;
        hienThiMenuCon();
      } else {
        if (trangThaiMenu > 0) trangThaiMenu--;
        hienThiMenu();
      }
    }
  }

  trangThaiNutGiuaCu = trangThaiNutGiuaHienTai;
  trangThaiNutPhaiCu = trangThaiNutPhaiHienTai;
  trangThaiNutTraiCu = trangThaiNutTraiHienTai;
}

void hienThiMenu() {
  lcd.setCursor(0, 1);
  switch (trangThaiMenu) {
    case 0:
      lcd.print("Mini game     ");
      break;
    case 1:
      lcd.print("LED control   ");
      break;
    case 2:
      lcd.print("Exit          ");
      break;
  }
}

void hienThiMenuCon() {
  lcd.setCursor(0, 1);
  switch (trangThaiMenuCon) {
    case 0:
      lcd.print("Flashing      ");
      break;
    case 1:
      lcd.print("Fading        ");
      break;
    case 2:
      lcd.print("Led by Led    ");
      break;
  }
}

void thucHienMenu() {
  switch (trangThaiMenu) {
    case 0:
      miniGame();
      break;
    case 1:
      trongMenuCon = true;
      trangThaiMenuCon = 0;
      lcd.setCursor(0, 0);
      lcd.print("LED Control:");
      hienThiMenuCon();
      break;
    case 2:
      trongMenu = false;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("XIN CHAO");
      break;
  }
}

void thucHienMenuCon() {
  lcd.clear();
  switch (trangThaiMenuCon) {
    case 0:
      flashing();
      break;
    case 1:
      fading();
      break;
    case 2:
      ledByLed();
      break;
  }
  trongMenuCon = false;
  lcd.setCursor(0, 0);
  lcd.print("LED Control:");
  hienThiMenuCon();
}

void miniGame() {
  lcd.setCursor(0, 0);
  lcd.print("Mini Game");
  // Thêm mã mini game của bạn ở đây
}

void flashing() {
  lcd.setCursor(0, 0);
  lcd.print("Flashing");
  // Thêm mã đèn flashing của bạn ở đây
}

void fading() {
  lcd.setCursor(0, 0);
  lcd.print("Fading");
  // Thêm mã đèn fading của bạn ở đây
}

void ledByLed() {
  lcd.setCursor(0, 0);
  lcd.print("Led by Led");
  // Thêm mã led by led của bạn ở đây
}
