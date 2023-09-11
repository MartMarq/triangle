#include "Watchy_triangle.h"

#define DARKMODE false


void Watchytriangle::drawWatchFace(){
    display.fillScreen(DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);
    display.setTextColor(DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    drawTime();
    }


void Watchytriangle::drawTime() {

   // reset step counter at midnight
    if (currentTime.Hour == 00 && currentTime.Minute == 00){
      sensor.resetStepCounter();
              //turn off radios
      WiFi.mode(WIFI_OFF);
      btStop();
    }
	// time adjustment of 15,5 seconds each day (Watchy runs too fast)

    if (currentTime.Hour == 00 && currentTime.Minute == 30){
        
        RTC.read(currentTime);
        int8_t sekunde = currentTime.Second;
        int8_t minute = currentTime.Minute;
        int8_t hour = currentTime.Hour;
        int8_t day = currentTime.Day;
        int8_t month = currentTime.Month;
        int8_t year = tmYearToY2k(currentTime.Year);

        delay(15500);

        tmElements_t tm;
        tm.Month = month;
        tm.Day = day;
        tm.Year = y2kYearToTm(year);
        tm.Hour = hour;
        tm.Minute = minute ;
        tm.Second = sekunde;

        RTC.set(tm);
                
         }
	// end of time adjustment, if you don't like a time adjustment, just delete above lines

    const uint8_t* tagx[] = { xsun, xmon, xtue, xwed, xthu, xfri, xsat, xsun };
    const uint8_t* monx[] = { xjan, xfeb, xmar, xapr, xmay, xjun, xjul, xaug, xsep, xoct, xnov, xdec };

    display.writeFastHLine(0, 100, 200, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.writeFastVLine(100, 0, 200, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.fillCircle(100, 100, 75, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.drawCircle(100, 100, 99, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.drawCircle(100, 100, 50, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);
    display.fillCircle(100, 100, 49, DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);

    float VBAT = getBatteryVoltage();
    int batLev = min<int>(100 - ((4.15 - VBAT) * 100), 100);
    batLev = max<int>(batLev, 0);
    display.fillCircle(100, 100, batLev / 2, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    int WTag = currentTime.Wday - 1;
    display.drawBitmap(0, 155, tagx[WTag], 45, 45, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    WTag = currentTime.Month - 1;
    display.drawBitmap(155, 155, monx[WTag], 45, 45, DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);

    display.setFont(&FreeMonoBold16pt7b);
    display.setCursor(5, 22);
    WTag = currentTime.Day;
    WTag = WTag / 10;
    display.println(WTag);
    WTag = currentTime.Day - (WTag * 10);
    display.setCursor(177, 22);
    display.println(WTag);

    int stundeA = ((currentTime.Hour + 11) % 12) + 1;
    int minuteA = currentTime.Minute;

    double winke = (stundeA * 30) + minuteA * 0.5;
    double lange = ((winke + 180) * 71) / 4068.0;
    double cx1 = 100 - (sin(lange) * 75);
    double cy1 = 100 + (cos(lange) * 75);
    double sitx = 100 - (sin(lange) * 47);
    double sity = 100 + (cos(lange) * 47);

    winke = winke - 90;
    lange = ((winke + 180) * 71) / 4068.0;
    double ax1 = sitx - (sin(lange) * 15);
    double ay1 = sity + (cos(lange) * 15);

    winke = winke + 180;
    lange = ((winke + 180) * 71) / 4068.0;
    double bx1 = sitx - (sin(lange) * 15);
    double by1 = sity + (cos(lange) * 15);

    display.fillTriangle((int)ax1, (int)ay1, (int)bx1, (int)by1, (int)cx1, int(cy1), DARKMODE ? GxEPD_BLACK : GxEPD_WHITE);

  
    double minke = minuteA * 6;
    double mange = ((minke + 180) * 71) / 4068.0;
    double cmx1 = 100 - (sin(mange) * 100);
    double cmy1 = 100 + (cos(mange) * 100);
    double mitx = 100 - (sin(mange) * 72);
    double mity = 100 + (cos(mange) * 72);

    minke = minke - 90;
    mange = ((minke + 180) * 71) / 4068.0;
    double amx1 = mitx - (sin(mange) * 15);
    double amy1 = mity + (cos(mange) * 15);
    
    minke = minke + 180;
    mange = ((minke + 180) * 71) / 4068.0;
    double bmx1 = mitx - (sin(mange) * 15);
    double bmy1 = mity + (cos(mange) * 15);

    display.fillTriangle((int)amx1, (int)amy1, (int)bmx1, (int)bmy1, (int)cmx1, int(cmy1), DARKMODE ? GxEPD_WHITE : GxEPD_BLACK);


}
