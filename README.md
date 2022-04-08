![Build](https://img.shields.io/badge/Build-passing-blue?style=for-the-badge&labelColor=ffffff&color=4EA94B)
![Version](https://img.shields.io/badge/Version-1.1-blue?style=for-the-badge&labelColor=ffffff&color=4EA94B)
![Arduino](https://img.shields.io/badge/Arduino-blue?style=for-the-badge&logo=arduino&labelColor=ffffff)
![ESP](https://img.shields.io/badge/ESP8266-blue?style=for-the-badge&logo=espressif&labelColor=ffffff)
![Stars](https://img.shields.io/github/stars/AlexOgn/all-in-one-weather?style=for-the-badge&labelColor=white&color=yellow)

# **All-in-one-weather**
<img src="https://user-images.githubusercontent.com/61375132/162498691-0b94da9b-4b73-4ad8-80f8-044e5a4a68f6.png" alt="All-in-one-weather" width="600"/>

All-in-one-weather е иновативна система, която включва сървър и устройство. Устройството използва сензори, за да обработи информация за околната си среда, след което изпраща информацията на сървър. С помощтта на сървъра, информацията може лесно да бъде визуализирана и обработвана и е достъпна за всички.

## Как да си сваля и използвам проекта?

### Инструкции за сваляне
1. Изтеглете git (Tutorial може да намерите [тук](https://github.com/git-guides/install-git#:~:text=To%20install%20Git%2C%20run%20the,installation%20by%20typing%3A%20git%20version%20.))
> Ако не желаете да конфигурирате git изтеглете .zip архив като натиснете зеленото копче `Code` и изберете `Download ZIP` и го разархивирайте
> Пропуснете стъпки 4 и 5
2. Изтеглете Arduino IDE (Tutorial за [Windows](https://docs.arduino.cc/software/ide-v1/tutorials/Windows), [MacOS](https://www.arduino.cc/en/Guide/macOS), [Linux](https://docs.arduino.cc/software/ide-v1/tutorials/Linux))
3. Отворете терминал (Command prompt)
4. Въведете следната команда:  `git clone https://github.com/AlexOgn/All-in-one-weather.git`

### Инструкции за инсталация
Как се инсталира библиотека в Arduino IDE?
1. Отворете Library Manager (Ctrl + Shift + I)
2. Напишете името на библиотеката в търсачката
3. Кликнете на копчето `Install` като изберете последната версия
4. Инсталирайте всички [външни библиотеки](https://github.com/AlexOgn/All-in-one-weather#%D0%B2%D1%8A%D0%BD%D1%88%D0%BD%D0%B8-%D0%BD%D1%83%D0%B6%D0%B4%D0%B0%D1%8F%D1%82-%D1%81%D0%B5-%D0%BE%D1%82-%D1%80%D1%8A%D1%87%D0%BD%D0%B0-%D0%B8%D0%BD%D1%81%D1%82%D0%B0%D0%BB%D0%B0%D1%86%D0%B8%D1%8F) за работата на проекта

### Инструкции за стартиране на проекта
1. Отидете в директорията, където изтеглихте кода
2. Свържете Ардуиното и сензорите както е показано на схемата:  
![Схема]()
3. Отворете `main.ino` файлът с Arduino IDE
4. Кликнете на копчето `Upload` след като сте избрали правилното Ардуино и порт (обяснение може да намерите [тук](https://support.arduino.cc/hc/en-us/articles/4406856349970-Select-board-and-port-in-Arduino-IDE))

## Използвани сензори и модули

* [Arduino Mega](http://store.arduino.cc/products/arduino-mega-2560-rev3) - основата на проекта (използването на Уно може да създаде проблеми при работата на Wi-Fi модулът)
* [DHT11](https://www.adafruit.com/product/386) - сензор за измерване на влажността на въздуха
* [DS1307 (използвана опростена версия)](https://www.adafruit.com/product/3296) - RTC(Real Time Clock) използван за определяне на времето
* [BMP180](https://eu.mouser.com/ProductDetail/Bosch-Sensortec/BMP180?qs=d72FGnIDsgTlLIC5YM2WKA%3D%3D) - сензор за измерване на налягане, надморска височина и температура
* [ESP8266](https://www.espressif.com/en/products/socs/esp8266) - Wi-Fi модулът, който създаде много проблеми при разработката. Използва се за изпращане на информация към сървъра
* [LCD екран](https://www.adafruit.com/product/181) - екран за показване на информацията в реално време
* [SD карта четец](https://www.adafruit.com/product/254) - четец и записвач на SD карта, който записва информацията в случай, че няма интернет връзка с цел минимизиране на загубата на информация

## Използвани библиотеки
### Външни (нуждаят се от ръчна инсталация)
* [DHT](https://github.com/adafruit/DHT-sensor-library) - нужна за работата на **DHT11** сензорът
* [RTCLib](https://github.com/adafruit/RTClib) - нужна за работата на **DS1307** модулът
* [SFE_BMP180](https://github.com/LowPowerLab/SFE_BMP180) - Нужна за работата на **bmp180** сензорът
* [WifiESP](https://github.com/bportaluri/WiFiEsp) - нужна за работата на **Wi-Fi** модулът
* [LiquidCrystal](https://github.com/arduino-libraries/LiquidCrystal) - нужна за работата на **LCD екранът**
* [SD](https://github.com/arduino-libraries/SD) - нужна за работата на **SD card** модулът

### Вградени
* [SPI](https://github.com/PaulStoffregen/SPI) - нужна за осъществяването на SPI комуникацията
* [Wire](https://github.com/PaulStoffregen/Wire) - нужна за осъществяването на I2C комукацията

## Автор на проекта

**Алекс Огнянов** - програмист, дизайнер и хардуерист - [AlexOgn](https://github.com/AlexOgn)


### Кодът за сървъра може да намерите **[тук](https://github.com/AlexOgn/All-in-one-weather-server "Server files")**
