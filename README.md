<h1 align="center">Snoopy Game in C</h1>

<p align="center">
  <img src="https://github.com/ysfelhamri/Snoopy/assets/103438312/9eb63188-710f-4ccf-8392-d65a40a0c1e0">
</p>

___

## Introduction

The main idea for this project was to recreate the classic game Snoopy in C.


The focal points while creating this are :

1. Have a play area surronded by borders.
2. Have a player character that can move in all the four directions of the play area.
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

| Data in the Matrix | Symbol | Description |
| :---: | :---: | :---: |
| 0 | \[space\] | Empty space. |
| 1 | ☻ | Player. |
| 2 | # or ▀ or ▄ or █ | Impassable obstacle. |
| 3 | ♂ | Ball. |
| 4 | ♫ | Bird. |
| 8 | ◙ | Teleportation block number 1. |
| 9 | ◙ | Teleportation block number 2. |

Here is an example matrix : 

| 2 | 2 | 2 | 2 | 2 | 2 | 2 |
| - | - | - | - | - | - | - |
| 2 | 4 | 0 | 0 | 0 | 0 | 2 |
| 2 | 9 | 0 | 1 | 0 | 0 | 2 |
| 2 | 0 | 2 | 2 | 0 | 0 | 2 |
| 2 | 0 | 0 | 0 | 0 | 0 | 2 |
| 2 | 8 | 0 | 0 | 0 | 3 | 2 |
| 2 | 2 | 2 | 2 | 2 | 2 | 2 |

It is going to be shown as this : 

<pre>
▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄▄
█ ♫                         █
█ ◙           ☻             █
█          ####             █
█                           █
█ ◙                       ♂ █
▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀▀
</pre>

> Impassable obstacles are shown as "█" if used as a vertical border, "▄" if used as a horizontal top border, "▀" if used as a horizontal bottom border and "#" otherwise.

Here is the list of possible interactions :

1. The player cannot go through impassable obstacles.
2. The player can collect birds and the score increases.
3. When to ball touches the player his health points decrease.
4. The ball bounces off obstacles, birds, teleportation blocks and the player if he still has enough health points.

___

## Graphical user interface

<p align="center">
  <img src="https://github.com/ysfelhamri/Snoopy/assets/103438312/9eb63188-710f-4ccf-8392-d65a40a0c1e0">
</p>

This is the main menu shown when the game is started

___

<p align="center">
  <img src="https://github.com/ysfelhamri/Snoopy/assets/103438312/1cc156be-2035-4fb6-9d63-7e380aa13afd">
</p>

This is the start menu. It has three options :

1. Start the game and go the first level.
2. View score statistics.
3. Quit the game.

___

<p align="center">
  <img src="https://github.com/ysfelhamri/Snoopy/assets/103438312/fabdb41e-0a4a-43db-823b-4a70064bddb7">
</p>

This is the statistics menu. Last attempt score and High score are shown here.

___

<p align="center">
  <img src="https://github.com/ysfelhamri/Snoopy/assets/103438312/564d8f9a-33e2-48c9-8e91-54dfb43512c7">
</p>

This is the first level of the game. Health, score and time left are shown in the bottom left. Health decreases when the ball touches the player, score increases when the player collects birds and time decreases every second.

>The vertical blocks besides each vertical border also change to represent the passing of time.

The player loses when he has no health left and/or when the time reaches zero and gets sent back to start menu.

The level can be paused.

___



