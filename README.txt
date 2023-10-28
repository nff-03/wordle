README for building and running the wordle application
-----------------------------------------------------

Ensure that your laptop has the make, boost, and Wt library installed before trying to build the application. It is fairly easy to build the wordle application using the makefile provided with it. The make file assumes your Wt path is /usr/local.

When you plan on building the application, simply write the command 
	- make 
in terminal

For running the application after building it simply use the command:
	- ./wordle --docroot . --http-listen 0.0.0.0:8080

The "--docroot" command tells the compiler to look for files it might need to run the application in the current directory. The "--http-listen 0.0.0.0:8080" configure the server to listen for incoming HTTP requests on all available network interfaces of the system, specifically on port number 8080. (Feel free to use any port number to run the application!)

After running that command line on terminal navigate to your web browser and search "localhost:8080" or "localhost:port number you used" or "http://127.0.0.1:8080" to access the application on the web browser. 

To clean the directory after running the application, you can use the command: 
	- make clean

Hope you enjoy the game and good luck guessing the words!!!