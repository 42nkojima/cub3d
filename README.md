*This project has been created as part of the 42 curriculum by nkojima, tmase.*

# cub3D

## Description

cub3D is a small first-person 3D maze viewer inspired by Wolfenstein 3D.
It reads a scene description file (`.cub`) and renders the maze with the
raycasting technique, using the MiniLibX graphics library.

The program is split into three parts:

- **Parser** (`parser/`): reads the `.cub` file, stores the wall textures,
  the floor and ceiling colors, and the map, and checks that the map is
  closed by walls.
- **Raycasting** (`raycast/`): for each column of the screen, casts one ray
  with the DDA algorithm and finds the distance to the nearest wall.
- **Rendering** (`render/`): draws the floor and ceiling, then draws each wall
  column with the texture of the face that was hit (north, south, west or
  east), and handles the keyboard and window events.

### The `.cub` file

```
NO ./textures/north.xpm
SO ./textures/south.xpm
WE ./textures/west.xpm
EA ./textures/east.xpm

F 220,100,0
C 225,30,0

111111
100101
101001
1100N1
111111
```

- `NO` `SO` `WE` `EA`: path to the XPM texture of each wall face.
- `F` `C`: floor and ceiling colors in `R,G,B` (0-255).
- The map is the last element. `1` is a wall, `0` is an empty space,
  `N` `S` `E` `W` is the player's start position and direction.
  Spaces are allowed, but the map must be closed by walls.

If the file is invalid, the program prints `Error` followed by a message and
exits.

## Instructions

### Requirements

- `cc` and `make`
- MiniLibX for Linux (`minilibx-linux`), extracted at the root of the
  repository. It is not included in this repository.
- X11. On macOS, install [XQuartz](https://www.xquartz.org/).

### Build

```sh
tar xzf minilibx-linux.tgz
make
```

### Run

```sh
./cub3D maps/good/subject.cub
```

### Controls

| Key | Action |
| --- | --- |
| `W` `S` | Move forward / backward |
| `A` `D` | Move left / right |
| `←` `→` | Rotate the view |
| `ESC` or the window close button | Quit |

## Resources

- [Lode's Computer Graphics Tutorial - Raycasting](https://lodev.org/cgtutor/raycasting.html)
- [Rotation matrix (mathlandscape)](https://mathlandscape.com/rotation-matrix/)
- [MiniLibX documentation (42 Docs)](https://harm-smits.github.io/42docs/libs/minilibx)
- [cub3D slides (Google Slides, in Japanese)](https://docs.google.com/presentation/d/1dQrnEUmDkodlIC366O_YdLbO2-MBsuzEkgC8F2xjxOY/edit?usp=sharing)
- [ttranche/cub3D](https://github.com/ttranche/cub3D)

### Use of AI

We used AI as a learning and review assistant:

- **Understanding**: explaining the raycasting math (DDA, perpendicular
  distance, texture coordinates) and answering questions about our own code.
- **Code**: discussing implementation approaches and getting example code
  with explanations, which we reviewed and adapted.
- **Review and debugging**: finding bugs in pull requests (for example, the
  swapped player position that crashed the raycaster, and maps with an `N`
  player being rejected), and
  checking Norm and memory leaks.
- **Project management**: splitting the work into GitHub issues and writing
  pull request descriptions.
- **Test data**: generating test `.cub` maps and the placeholder XPM
  textures in `textures/`.
