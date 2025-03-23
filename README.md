Hi! This is a beginner level first-person project made in **Unreal Engine 5.3** where you need to use your axe to escape from some... underground cave place... filled with archers for some reason?

Developed in Spring 2024, updated in Spring 2025 (minor improvements and config changes).

## Character controls

- WASD - movement
- Left Mouse Button - axe attack
- Space - jump
- CTRL - crouch (or accelerate downwards if used midair)
- LShift - sprint

## Contents of the project:

### Functional

- Mechanics written in C++
- A first-person character able to run, crouch smoothly, jump, sprint, attack/block, take damage, interact with environment
- Object pools for arrows for every actor that can shoot
- Attack system
- Block system
  - Damage an arrow to start blocking
  - Any arrow that gets into your attack range while deflecting gets destroyed and resets the block animation
- A somewhat flexible interaction system
  - Any object can have default interaction behaviour
  - Custom interaction behaviour can be added in the level blueprint
  - Uses delegates
- Custom core classes such as PlayerController, HUD, Camera Manager
- Main menu and UI with animations
- W/L conditions with multiple ending sequences
- A custom world subsystem

### Visual

- A rigged first-person character that can hold a weapon
  - The character + animations and the weapon made from scratch in Blender
- Animated enemies able to locate the player, forget the player, attack, take damage
  - Enemy model and animations taken from Mixamo
- A simple environment modeled from scratch in Blender
- Emissive and world-aligned materials
