# Flock Simulation Project

## Overview
This project simulates flocking behavior using **C++** and **SDL2**. The simulation consists of three main classes:

- **Bird**: Represents an individual bird in the flock.
- **Flock**: Manages a group of birds and applies the flocking algorithm.
- **Screen**: Handles the SDL2 window and rendering for the simulation.

### UML Diagram
Below is a UML diagram illustrating the relationship between the classes:

![UML Diagram](docs/images/uml_diag.png)

- **Bird Class**:  
  - Attributes: `x`, `y` (position) and `direction`.  
  - Methods: Functions to set and get location and direction.  
  - Used in the `Flock` class through composition.

- **Flock Class**:  
  - Attributes: `birds` (a vector of `Bird` objects) and `dt` (time step).  
  - Manages bird movement and applies flocking behaviors like separation, cohesion, and alignment.

- **Screen Class**:  
  - Attributes: `window`, `renderer`, `points`, `width (w)`, and `height (h)`.  
  - Manages rendering of the birds and handles events like quitting the simulation.

---

## How to Clone and Build the Project

### Step 1: Clone the Repository
To clone the repository, use the following command in your terminal or command prompt:

```bash
git clone https://github.com/your-username/your-repo-name.git
cd your-repo-name
