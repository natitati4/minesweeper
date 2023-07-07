# Description
A minesweeper game that is a bit more extendible than the original Winmine by microsoft. Made using SFML (my first SFML project).

# Version 1.2.1
Added option to choose custom rows, columns and mines count.
Added icon

# In the next version
Not sure there will be one.\
In case there will be (i.e I will have the will to do it), maybe: \
-Add a feature to remember user choices via registry.\
-Make adjcency logic work through the edges (like a 1 at the bottom line mine point to a mine at the top line).
-Add sounds

# How to run

```
git clone https://github.com/natitati4/minesweeper
cd minesweeper/x64/release
minesweeper.exe
```

# How to compile yourself
You can compile it yourself using Visual Studio 2019 (probably higher versions too)

```
git clone https://github.com/natitati4/minesweeper
cd minesweeper
minesweeper.sln
```

Refer to the following video to understand how to set up SFML in Visual Studio: `https://www.youtube.com/watch?v=lFzpkvrscs4`.

After compiling, in the x64/Release (or x64/Debug), Add these 2 folders (from the minesweeper folder): `ArialFont` and `Images`. These are for the font and the images of the game.

Now you can run the newly created `minesweeper.exe` in either the Release or Debug folders.

# Limitations
Runs only on Windows, obviously.
