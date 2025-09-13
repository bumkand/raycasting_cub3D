# cub3D

🔭 **cub3D** – A raycaster project in C using the **mlx42** library.  
Turns a 2D map into a 3D-like first-person view. Player moves, collision, sprite/texture rendering, and exit goals implemented.

## Features

- Ray-casting algorithm for 3D view from 2D map  
- Texture support for walls, floor, ceiling, and sprites  
- Keyboard controls for movement and rotation  
- Map parsing with validation (walls, characters, shape)  
- Real-time rendering with frame updates  
- Proper memory and resource cleanup  

## Build & Run

```bash
make
./cub3D path/to/map.cub
