# LED Control V2.0
#### ARM
#### Author: Team 1 - Sub team A
- #### Members:
    - Alaa Hisham
    - Hossam Elwahsh

## Brief
> Develop the GPIO Driver and use it to control RGB LED on the Tiva-C board using a push button.


## Quick Links
- `Video` 👉 Youtube - in progress
- `Project Hex` 👉 TBC
- `Documentation` 👉 [Google Docs](https://docs.google.com/document/d/11W93RY6OmI8ad2eAT02Lx71EFzYXv_iCN_bzJ6KNIy0/edit?usp=sharing) 👉 PDF - uploading
- `Team Backlog / Test Protocol` 👉 [Google Sheets](https://docs.google.com/spreadsheets/d/1NoLEc5Sk5aW1h5KqDCW50kSdbQppFpclcKfD8z8wE_4/edit?usp=sharing) 👉 Excel File - uploading 

----
## Requirements
### Hardware Requirements
- Use the TivaC board
- Use SW1 as an input button
- Use the RGB LED
### Software Requirements
**The RGB LED is OFF initially**
- Pressing SW1:
  - After the first press, the Red led is on for 1 second only
  - After the second press, the Green Led is on for 1 second only
  - After the third press, the Blue led is on for 1 second only
  - After the fourth press, all LEDs are on for 1 second only
  - After the fifth press, should disable all LEDs
  - After the sixth press, repeat steps from 1 to 6
### Implement your drivers
- Implement GPIO driver
- Implement LED driver
- Implement Button driver
- Implement Systick driver
