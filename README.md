application to search file from ```"/"``` (root) by it's name in multithreading mode

 but better change starting directory in ```findByName.cpp``` **Line 30** to ```/home/username``` for security reasons (don't forget to change ```username``` to your actual username)

execute:

 ```git clone https://github.com/webmessia-h/findFileByName.git``` to clone repository

```cd ~/findFileByName/src``` change directory to project's directory
 
 ```make``` to compile search library 

```make main``` ```chmod +x main``` to compile and make app executable

 ```sudo ./main``` to launch app

 consider that using 'sudo' may be dangerous for your system as it gives superuser privileges to executable,
 but running app without sudo will throw a bunch of scarry errors in console log, as app won't have permissions to enter certain directories :)

**output will look like this:**
```
╭─   ~/Path/findFileByName/src ───────────────────────────────────────────────────────────────────────────────────────────────
╰─ sudo ./main
file:  "findMe.txt" was found in "/home/webmessiah/findMe.txt"
```
