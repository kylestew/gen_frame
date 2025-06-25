# C Image Generator

A simple C project that generates images using a `setPixel` function passed to a sketch.

## Architecture

- **`main.c`**: Sets up the image buffer, provides `setPixel` function, calls the sketch, and writes PPM image to disk
- **`sketch.c`**: Contains the drawing logic (currently a radial gradient)
- **`Makefile`**: Compiles the project with math library support

## Features

- 800x600 image output
- PPM (Portable Pixmap) format - human-readable text format
- No external dependencies beyond standard C libraries
- Clean separation between buffer management and drawing logic

## Usage

### Compile
```bash
make
```

### Run
```bash
make run
```

Or directly:
```bash
./image_generator
```

### Clean
```bash
make clean
```

## Output

The program generates `output.ppm` which can be opened in most image viewers or converted to other formats.

## Customizing

To create your own sketch:

1. Modify the `drawSketch` function in `sketch.c`
2. Use the `setPixel(x, y, r, g, b)` function to draw pixels
3. The function receives the image dimensions as parameters

## Example Sketch

The current sketch creates a radial gradient from the center with:
- Red fading to green from center to edge
- Blue component using a sine wave pattern 