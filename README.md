<h1 align="center">Snoopy Game in C</h1>

<p align="center">
  ![Start Menu](https://github.com/ysfelhamri/Snoopy/assets/103438312/9eb63188-710f-4ccf-8392-d65a40a0c1e0)
</p>
___

The main idea for this project was to recreate the classic game Snoopy in C.


The focal points while creating this are :

1. Have a play area surronded by borders.
2. Have a player character that can move in all four directions of the play area.
3. Have collectibles in form of birds.
4. Have a ball enemy that moves in diagonals pseudo-randomly but has collision physics.
5. Have impassable obstacles and special blocks.
6. Have a score system.
7. Have a health system.
8. Have a timer.
9. Have a level system.
10. Have a graphical user interface in the console.

___

## Handling Interactions

In order to handle interaction between the different entities in the game their data is stored into a two dimensional array and replaced with spacial symbols for the graphical interface :

| Data in the matrix | Symbol | Description |
| :---: | :---: | :---: |
| 0 | \[space\] | Empty space. |
| 1 | ☻  | Player. |
| 2 | # or ▀ or ▄ or █ | Impassable obstacle. |
| 3 | ♂  | Ball. |
| 4 | ♫  | Bird. |
| 8 | ◙ | Teleportation block number 1. |
| 9 | ◙ | Teleportation block number 2. |
