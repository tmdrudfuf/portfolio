import java.awt.*;
import javax.swing.ImageIcon;

// Nephi class extending Sprite
public class Nephi extends Sprite {
    private boolean hasBow;
    private boolean hasArrow;
    private ImageIcon hasBowIcon;
    private ImageIcon hasArrowIcon;
    private ImageIcon hasBowAndArrowIcon;
    private ImageIcon regularIcon;

    public Nephi(int x, int y) {
        super(x, y);

        // Initialize icons
        hasBowIcon = new ImageIcon("nephi_bow.png");
        hasArrowIcon = new ImageIcon("nephi_arrow.png");
        hasBowAndArrowIcon = new ImageIcon("nephi_bow_arrow.png");
        regularIcon = new ImageIcon("nephi.png");

        // Initialize item status
        hasBow = false;
        hasArrow = false;

        // Set the default image to regularIcon
        image = regularIcon;
    }

    // Provide the implementation of the draw method
    @Override
    public void draw(Graphics g) {
        if (absolutePosition != null && image != null) {
            Image img = image.getImage();
            g.drawImage(img, absolutePosition.x, absolutePosition.y, null);
        }
    }

    // Getter methods
    public boolean hasArrow() {
        return hasArrow;
    }

    public boolean hasBow() {
        return hasBow;
    }

    // Method to pick up an arrow
    public void pickUpArrow() {
        hasArrow = true;
        if (hasBow) {
            image = hasBowAndArrowIcon;
        } else {
            image = hasArrowIcon;
        }
    }

    // Method to pick up a bow
    public void pickUpBow() {
        hasBow = true;
        if (hasArrow) {
            image = hasBowAndArrowIcon;
        } else {
            image = hasBowIcon;
        }
    }
}