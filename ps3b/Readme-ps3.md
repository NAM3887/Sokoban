# PS2a: Sokoban

## Contact
Name: Michael Stanley
Section: 202 
Time to Complete: 31 hours


## Description
Explain what the project does.

My Project creates a Sokoban game from a lvl file.
In the game the player is supposed to push the Crates on 
the Storage spaces. When all the crates are on storage the game is won.
Time elsapsed is also shown in the top right corner and 
the time it took you to win is displayed.


### Features 
Describe what your major decisions were and why you did things that way.

To store my grid I decided to use a vector of (vector of Tiles). Tiles are a struct that I made to store information about each specific tile such as the tile type and grid position. 
I did it this way because I have expierence with objects similar to 2d arrays.

For the player I made a stuct to be used for storing what tileType the player is on 
and the previous one. This is used to replace the tile type with the playertype in the _tiles vector.

Crates are stored in a vector of Crate. Crate is a struct that is similar to player but has a gridposition aswell.

### Memory
Describe how you decided to store the level data including whether you used smart pointers.

I decided to have the sokoban class store one of each of the textures that are going to be used. Originally I had each tile contain a texture but 
I decided that having them stored once would be better.

When making my tiles struct I wanted to make it low cost for memory because I knew I was making a vector of vector of tiles.

Thinking of how I wanted to store crates took me a lot of trial and error but I ended up making a vector of crates.
This is why the crates stuct has a grid position so I can find a crate at a position.

I did not use smart pointers.
### Lambdas
Describe what <algorithm> functions you used and what lambda expressions you wrote.

I have a labmda expression to initalize my vector of crates.

I used std::find_if to find if there tiles with the tiletype crate
In the find_if I have a lambda that compares the tile types and returns 
iterator pointing to the tile

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

I was confused for a while on what data I need and how to store it. Also, I had a lot of trouble with implementing the extraction operator but after some reading I figured it out.
I had issues with trying to figure out how to initialize my _crates vector 
the problem was solved with a lambda that returns a crate using a value constuctor with position as the parameter.


### Extra Credit
Anything special you did.  This is required to earn bonus points.

I added a clock to display the time elasped in the top right corner of the screen
this was done by getting the total time elapsed in seconds then getting the minutes by dividing total seconds by 60.
I made it so the player changes direction with movement.
When you win the player faces the user and text saying "You Win!" is displayed as long as the time it took to complete
Also I added a victory sound to be played when the player wins.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.
If you used images or other resources than the ones provided, list them here.
I referenced the example game programs done in class such as: Minesweeper, connect 4, and snake

Kenney Sokoban Pack (CC0): https://kenney.nl/assets/sokoban

https://www.boost.org/doc/libs/1_84_0/libs/test/doc/html/boost_test/tests_organization/fixtures.html
https://www.boost.org/doc/libs/1_84_0/libs/test/doc/html/boost_test/tests_organization/fixtures/case.html

 https://www.youtube.com/watch?v=Ko8X9Awfrqw
https://www.youtube.com/watch?v=TR82JAtFLYI
https://www.geeksforgeeks.org/unordered_map-in-cpp-stl/
https://stackoverflow.com/questions/27553850/my-code-doesnt-work-with-stdmap-and-sfvector2i
https://stackoverflow.com/questions/4494170/grouping-switch-statement-cases-together
https://www.w3schools.com/cpp/cpp_files.asp
SFML doccumentation 

https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Clock.php
https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Drawable.php
https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Sprite.php
https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Texture.php
https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1Sound.php#a36ab74beaaa953d9879c933ddd246282
https://www.sfml-dev.org/documentation/2.6.1/classsf_1_1SoundBuffer.php

https://stackoverflow.com/questions/17032970/clear-data-inside-text-file-in-c
https://stackoverflow.com/questions/8382110/stdfor-each-and-two-dimensional-array

https://mixkit.co/free-sound-effects/game/
https://www.1001fonts.com/open-sans-font.html
https://www.dafont.com/alarm-clock.font