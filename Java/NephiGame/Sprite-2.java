import java.awt.*;
import javax.swing.ImageIcon;


// General-purpose abstract Sprite class
public abstract class Sprite {
    protected Point absolutePosition;
    protected Point relativePosition;
    protected ImageIcon image;

    public Sprite(int x, int y) {
        absolutePosition = new Point(Main.CELL_SIZE * x, Main.CELL_SIZE * y);
        relativePosition = new Point(x, y);
        // Remove the line that loads the image in the constructor
    }

    public void setLocation(int x, int y) {
        relativePosition = new Point(x, y);
        absolutePosition = new Point(Main.CELL_SIZE * x, Main.CELL_SIZE * y);
    }

    public void setLocation(Point p) {
        if (p == null) {
            absolutePosition = null;
            relativePosition = null;
        } else {
            absolutePosition = new Point(Main.CELL_SIZE * p.x, Main.CELL_SIZE * p.y);
            relativePosition = p;
        }
    }

    // Declare the draw method as abstract
    public abstract void draw(Graphics g);

    public Point getLocation() {
        return relativePosition;
    }

    // New method to check if two sprites overlap
    public boolean overlaps(Sprite other) {
        return this.relativePosition.equals(other.relativePosition);
    }
}