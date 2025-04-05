import java.awt.*;
import javax.swing.ImageIcon;

// Beast class extending Sprite
public class Beast extends Sprite {
    public Beast(int x, int y) {
        super(x, y);
        // Load the beast.png image
        image = new ImageIcon("beast.png");
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