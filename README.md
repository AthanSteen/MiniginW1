## Game Engine

## Student

Name: Van den Steen Athan
Group: 2GD10E

## Source Control

**Repository URL:**  
[PeterPepper on GitHub](https://github.com/AthanSteen/MiniginW1)  

---

## Project Overview

This project exist of a Gameengine and a PeterPepper game. The engine and game feature:

- **Dynamic Level Management:** The level is managed via a Level class, supporting burger piece interactions and win conditions.
- **Component-Based Entities:** GameObjects are composed of modular components (e.g., SpriteSheetComponent, PlayerComponent, LevelComponent).
- **State Machines:** Player behavior is implemented using state machines for maintainable logic.
- **Input System:** Supports keyboard and controller input, with command pattern bindings.
- **Resource Management:** Assets like textures and spritesheets are easy loaded and managed
- **Audio Integration:** Sound effects are played via a service locator pattern.
- **Score System:** A really simple score system using Observers, Events and Commands

---

## Engine Architecture & Design Choices

### Component-Based Architecture

- **GameObject-Component System:** Entities are built from reusable components (e.g., PlayerComponent, SpriteSheetComponent), promoting modularity and code reuse.
- **Minimal Trivial Getters/Setters:** The codebase avoids unnecessary functions, exposing only meaningful interfaces.

### Player State Machine

- PlayerState use the State pattern for behaviors (e.g., Idle, Walking, Winning).

### Data-Driven Design

- **Level Configuration:** Level data can be loaded from external sources, making it easy to tweak gameplay without code changes. Also you can now build multiple levels really easy.

### Patterns Used

- **Component Pattern:** For entity composition.
- **Observer Pattern:** For UI.
- **State Pattern:** For player states.
- **Command Pattern:** For input handling.
- **Singleton Pattern:** For managers like SceneManager and InputManager.
- **Service Locator:** For audio.

---

## C++20 Features Utilized

- **std::unique_ptr:** Used for resource ownership and memory safety.
- **Structured Bindings:** For clean iteration and tuple unpacking.
- **Less Use of Trivial Getters/Setters:** Code is designed to expose only meaningful interfaces.

---

## License

This project uses third-party libraries (SDL2, XInput, nlohmann/json)