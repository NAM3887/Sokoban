# PS2a: Sokoban

## Contact
Name: Michael Stanley
Section: 202 
Time to Complete: 16 hours


## Description
Explain what the project does.

My Project creates the UI for my Sokoban game. It does this by reading information from a lvl file 
such as height, width, and the grid information to build the game.

### Features 
Describe what your major decisions were and why you did things that way.

To store my grid I decided to use a vector of (vector of Tiles). Tiles are a struct that I made to store information about each specific tile such as the tile type and grid position. 
### Memory
Describe how you decided to store the level data including whether you used smart pointers.

I decided to have the sokoban class store one of each of the textures that are going to be used. Originally I had each tile contain a texture but 
I decided that having them stored once would be better.
### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

I have not implemented any yet.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

I was confused for a while on what data I need and how to store it. Also, I had a lot of trouble with implementing the extraction operator but after some reading I figured it out.
I havent decided how I want to store the player, crate 

### Extra Credit
Anything special you did.  This is required to earn bonus points.

I added a clock to display the time elasped in the top right corner of the screen
this was done by getting the total time elapsed in seconds then getting the minutes by dividing total seconds by 60.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.
I referenced the example game programs done in class such as: Minesweeper, connect 4, and snake
Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban

 https://www.youtube.com/watch?v=Ko8X9Awfrqw
https://www.youtube.com/watch?v=TR82JAtFLYI
https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/
https://stackoverflow.com/questions/27553850/my-code-doesnt-work-with-stdmap-and-sfvector2i
https://www.w3schools.com/cpp/cpp_files.asp
SFML doccumentation 
https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Clock.php
https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Drawable.php
https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Sprite.php
https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Texture.php

https://stackoverflow.com/questions/17032970/clear-data-inside-text-file-in-c

https://www.dafont.com/alarm-clock.font