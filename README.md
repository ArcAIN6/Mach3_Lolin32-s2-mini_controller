# Mach3_Lolin32-s2-mini_controller
Mach3 Cycle control box

<strong><H3>Required Hardware:</H3></strong><br>
2x Esp32-S2 Mini <br>
3x Momentary Buttons<br>
1x E-Stop Latching Button<br>

<strong><H3>Optional Hardware:</H3></strong><br>
On/Off Rocker Switch.<br>
QI Charging Receiver<br>
LiPo Battery<br>

<strong><H3>Required Libraries:</H3></strong><br>
All part of the ESP32 Package: <br>
|-esp_now.h<br>
|-WiFi.h<br>
|-USB.h<br>
|-USBHIDKeyboard.h<br>

<strong><H2>-=[ IMPORTANT ]=-</H2></strong><br>
YOU MUST run the MAC sketch on your receiver ESP32-S2 Mini device, and record the mac address from serial output. This will be REQUIRED in the transmitter sketch. 

<H2>The Transmitter ESP32-S2 Mini</H2>
<p>The goal of this repository is to make life a little easier on those DIY'ers who want a wireless control box for Cycle Start, Cycle Stop, Cycle Pause, and E-Stop buttons. 

Using 2x Esp32-s2 mini's you'll be able to instantly trigger these buttons when pressed on ESP32-s2 Mini, and wirelessly send it to the other ESP32-S2 mini that's acting as an HID device. 
Essentially, what we're doing here is leveraging ESP-Now and the s2-mini's CDC to create a seamless wireless solution. 

I purchased the control box with 22mm buttons, and an estop from Amazon, you can source, or build your own however you like. </p>

![control_box_](https://github.com/ArcAIN6/Mach3_Lolin32-s2-mini_controller/assets/418929/f007b8de-da01-4f3c-9211-578105fc043f)

![S2_Mini](https://github.com/ArcAIN6/Mach3_Lolin32-s2-mini_controller/assets/418929/238d21a6-5887-4733-9def-c904566c034b)


<p>In order to fully realize a truely wireless solution here, i also incorporated a TP4056 LiPo battery charger, an ON/OFF rocker switch, LiPo 2500mAH battery, and a wireless QI charging receiver. (I used one of those cheap aliexpress QI cellphone usbc plugin types, but i peeled the sticker back, desoldered the USBC FFC, and just wired directly to it)

The way i wired these: </p><br>
![wiring](https://github.com/ArcAIN6/Mach3_Lolin32-s2-mini_controller/assets/418929/a2f911c2-eb78-4029-9750-974ba45becdf)

<p>as for the buttons, i daisy-chaned the ground from one button to the next, then to the ground on the ESP32-S2 Mini, then each button was wired to pins 2,3,4,5 respectively.  (See the "Transmitter" file for pin mapping)</p>

<H2>The Receiver ESP32-S2 Mini</H2>
The Receiver ESP32-S2 Mini doesn't really require much... Just edit your pins if you want LED's, and go.. (Be sure to check your specific Mach3 shortcuts to ensure the keyboard keys match the Mach3 shortcuts)
