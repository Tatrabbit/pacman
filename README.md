# stupid pac-man clone.

## what.
I'm learning to work with SDL, with an emphasis on scalability. I want to scale it up to my own engine, a sidescroller I've always wanted.

## why.
I want to make/finish Nipio's Adventure, a small piece of large bloatware that skyrocketed in scope creep when I was a young adult. Using Godot would come closest to how it originally felt like to play, but if I don't use C++, it won't really fulfill its artistic purpose. I need to close that chapter of my life and complete what I started then. It was originally written in Allegro 4 with TileStudio for map editing, and blew up into an egregious playground of project mismanagement. By the time I decided to stop, it was capable of general-purpose game dev with live editing via Lua (while the game was running, no less), and had HTML rendering capabilities... and worse.

## how.
Linux and MacOS only. Windows isn't supported because my gaming rig is annoying to go program at.

VS Code folder settings are included.

### get proprietery sprites.
Arcade - Pac-Man - All AssetsPalettes.png:
https://www.spriters-resource.com/arcade/pacman/sheet/159361/

Delete the background of all sprites. Just select "black" with a non-contiguous wand, no anti-alising, delete it/make transparent, save as atlas.png. You can use your favorite image tool, but everyone will judge you if you use Gimp. We will judge you harshly.

### run make.
Assuming you have the sprite sheet ready, just run make. You'll need sdl2, and the image addon. I intend to do without the image addon, and instead load images in a custom format, with a custom binary format for the image and palette system I so like.

### board_data.h
This is built from a csv file using `board_data.py`. If python is available, make will handle this as part of the build process.
As for source of the CSV itself, it's Tiled Map Editor. I'll add a project for editing that later. I don't want to push any .png stuff to the repository for file size reasons, so please wait on that until I know it's pretty much dusted off.

## dedicating this garbage to two pupils.
* A very longime friend I met on some furry site, whose recent desire to learn Allegro 5 got me thinking about once again continuing that Nipio game he once did music for, long ago.
* A fairly recent friend I met on a YTP server, whose interest in linux and C programming reminds me of my own when I was their age.

these two know who they are.