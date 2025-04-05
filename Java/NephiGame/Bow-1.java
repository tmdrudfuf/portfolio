import java.awt.*;
import javax.swing.ImageIcon;

// Bow class extending Sprite
public class Bow extends Sprite {
    public Bow(int x, int y) {
        super(x, y);
        // Load the bow.png image
        image = new ImageIcon("bow.png");
    }

    // Provide the implementation of the draw method
    @Override
    public void draw(Graphics g) {
        if (absolutePosition != null && image != null) {
            Image img = image.getImage();
            g.drawImage(img, absolutePosition.x, absolutePosition.y, null);
        }
    }
}