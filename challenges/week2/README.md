## Week 2 Challenges

Welcome to Week 2! For this week, you will be given a meta challenge for side channels on 3D printers. 

In this scenario, you gained physical access to KeyCorp, a key manufacturing site.
There, you were able to embed a microphone and vibration sensor, which you can remote into, to collect information on their 3D printers.
You also were able to collect several known prints before evacuating the scene.
Can you leak information about what is being printed based on the remote sensor readings?

The files you will need for both challenges are located [here](https://drive.google.com/drive/folders/14gBlku2bCVUA2k1cQIpFVMTqTW1WjPwP). You do not need the arduino hardware for this week's challenges. 


<img src="https://github.com/TrustworthyComputing/csaw_esc_2024/blob/main/challenges/week2/3dPrinters.jpg" alt="" align="left" width="250" height="240" title="KeyRing">


### KeyRing 1 (400 points)

In this challenge, your goal is to deduce which key is currently being printed at KeyCorp. For each of the 40 samples, classify them belonging to Key A, B, C, or D. The data you collected onsite will be helpful.

###  KeyRing 2 (600 points)

Now the key manufacturing is producing a new key that does not match any of your current samples. However, you were able to get several recording samples of this key across two different printers. Can you reproduce an image of the key and the bitting information? Use the data form KeyRing 1 to help you out.
