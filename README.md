I wrote this game as a tribute to all those amphibians out there: I wish I could use both of my hands just like you.

The game runs on an MGBA emulator. Everything is written in C, except for the makefile used to run the application.
For more direct information on how to run the application, please contact the CS2110 TAs.

Start:

To run, open a docker image using the command
./cs2110docker.sh
in the terminal. A link with your ip address should be given. Open this in your browser, and click connect. Once running the image,
open the project folder in the terminal (it should be inside the host folder). Run 
make mgba
to run the game.


Gameplay:
The user controls a frog sprite whose objective is to eat dragonflies and reach the end of the map (notated by a zone labeled end).
To move the frog around, use the arrow keys. Careful for the lilypads, though! You can't swim under them.

End:
Once the frog reaches the end of the map, the user is congratulated. Be sure to click Select/Backspace to return to the home screen.

Happy swimming!