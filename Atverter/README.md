# Setup Instructions
Provision Instructions:

1. Flash Pi with BerryLan
Download BerryLan enabled Raspbian image from URL:
https://berrylan.org/

Flash BerryLan image to micro SD card using Raspberry Pi Imager:
https://www.raspberrypi.com/software/

Put micro SD card in Pi and power it up.

2. Connect Pi to WiFi network

Get the BerryLan app for your phone.

Follow the directions on the app to connect the Pi to WiFi.

Record the IP Address the app displays when done.


3. SSH into your Pi

Using the IP Address you recorded, SSH into your Pi using the terminal command:

ssh pi@[IP Address]

The default password is "raspberry".

4. Use these commands to download the code base:

cd ~
  
sudo apt update

sudo apt upgrade -y
  
sudo apt install -y git
  
git clone https://github.com/dgerb/RayOnPi.git

When prompted, enter these credentials:
  
Username: dgerb
  
Password/Token: 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

5. Run provisioning scripts

Run the basic provisioning script. Use this command:
  
~/RayOnPi/Scripts/Provision/AllPiProvision.sh

If you want Remote Desktop and/or Remote.it, run this provisioning script:

~/RayOnPi/Scripts/Provision/AllRemotePiProvision.sh

Depending on what type of provision, choose one of the following:
  
~/RayOnPi/Scripts/Provision/GreenhousePiProvision.sh
  
~/RayOnPi/Scripts/Provision/LightPiProvision.sh
  
~/RayOnPi/Scripts/Provision/MotorPiProvision.sh

Note: if creating a new Greenhouse project, you'll need to create the control sheet. Follow "Task 1" in these instructions:

https://chem.libretexts.org/Courses/Intercollegiate_Courses/Internet_of_Science_Things_(2020)/1%3A_IOST_Modules/1.6%3A_Writing_to_Google_Sheets

Name the controls google sheets workbook "GREENHOUSENAME_Controls". Rename the google cloud project service account credentials file "GREENHOUSENAME_Credentials.json".
