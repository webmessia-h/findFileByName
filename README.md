concurrent application to search file from "/" (root) by it's name 

execute:

 ```git clone https://github.com/webmessia-h/findFileByName.git``` to clone repository

```cd ~/findFileByName/src``` change directory to project's directory
 
 ```make``` to compile search library 

```make main``` ```chmod +x main``` to compile and make app executable

 ```sudo ./main``` to launch app

 ```./main``` to run search (if doesn't work execute ```sudo ./main``` instead

 consider that using 'sudo' may be dangerous for your system as it gives superuser privileges to executable, but searching without sudo not yet have been implemented in this app, so you don't have a choice if you want app to run :)

**output would look like this:**
```
╭─   ~/Path/findFileByName/src ───────────────────────────────────────────────────────────────────────────────────────────────
╰─ sudo ./main
file:  "findMe.txt" was found in "/home/webmessiah/findMe.txt"
```
