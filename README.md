# Version 1.0
First of many (jk, maybe 2 more)

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

refer to the following video to understand how to set up SFML in Visual studio: `https://www.youtube.com/watch?v=lFzpkvrscs4`

After compiling, in the x64/Release (or x64/Debug), Add these 2 folders (from the minesweeper folder): `ArialFont` and `Images`. These are for the font and the images of the game.

Now you can run the newly created `minesweeper.exe` in either the Release or Debug folders.

# Limitations
Runs only on Windows, obviously.
