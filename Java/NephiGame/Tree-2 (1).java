import java.awt.*;
import javax.swing.ImageIcon;

// Tree class extending Sprite
public class Tree extends Sprite {
    public Tree(int x, int y) {
        super(x, y);
        // Load the tree.png image
        image = new ImageIcon("tree.png");
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