#ifndef OPTION_H
#define OPTION_H

class Option {
  private:
    uint16_t coordinateX;
    uint16_t coordinateY;
    uint16_t textX;
    uint16_t textY;
    uint16_t width;
    uint16_t height;
    uint16_t radius;
    const char* name;
    bool highlighted;

  public:
    Option(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t w, uint16_t h, uint16_t r, const char* n);

    uint16_t getCoordinateX() { return coordinateX; }
    uint16_t getCoordinateY() { return coordinateY; }
    uint16_t getTextX() { return textX; }
    uint16_t getTextY() { return textY; }
    uint16_t getWidth() { return width; }
    uint16_t getHeight() { return height; }
    uint16_t getRadius() { return radius; }
    const char* getName() { return name; }
    bool isHighlighted() { return highlighted; }

    void createOption();
    void unhighlight();
    void highlight();
};

#endif
